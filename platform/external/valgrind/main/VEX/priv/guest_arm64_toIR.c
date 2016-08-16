

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2013-2013 OpenWorks
      info@open-works.net

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.

   The GNU General Public License is contained in the file COPYING.
*/




#include "libvex_basictypes.h"
#include "libvex_ir.h"
#include "libvex.h"
#include "libvex_guest_arm64.h"

#include "main_util.h"
#include "main_globals.h"
#include "guest_generic_bb_to_IR.h"
#include "guest_arm64_defs.h"




static Bool host_is_bigendian;

static Addr64 guest_PC_curr_instr;

static IRSB* irsb;



#define DIP(format, args...)           \
   if (vex_traceflags & VEX_TRACE_FE)  \
      vex_printf(format, ## args)

#define DIS(buf, format, args...)      \
   if (vex_traceflags & VEX_TRACE_FE)  \
      vex_sprintf(buf, format, ## args)



static inline UInt getUIntLittleEndianly ( UChar* p )
{
   UInt w = 0;
   w = (w << 8) | p[3];
   w = (w << 8) | p[2];
   w = (w << 8) | p[1];
   w = (w << 8) | p[0];
   return w;
}

static ULong sx_to_64 ( ULong x, UInt n )
{
   vassert(n > 1 && n < 64);
   Long r = (Long)x;
   r = (r << (64-n)) >> (64-n);
   return (ULong)r;
}


#define BITS2(_b1,_b0)  \
   (((_b1) << 1) | (_b0))

#define BITS3(_b2,_b1,_b0)  \
  (((_b2) << 2) | ((_b1) << 1) | (_b0))

#define BITS4(_b3,_b2,_b1,_b0)  \
   (((_b3) << 3) | ((_b2) << 2) | ((_b1) << 1) | (_b0))

#define BITS8(_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   ((BITS4((_b7),(_b6),(_b5),(_b4)) << 4)  \
    | BITS4((_b3),(_b2),(_b1),(_b0)))

#define BITS5(_b4,_b3,_b2,_b1,_b0)  \
   (BITS8(0,0,0,(_b4),(_b3),(_b2),(_b1),(_b0)))
#define BITS6(_b5,_b4,_b3,_b2,_b1,_b0)  \
   (BITS8(0,0,(_b5),(_b4),(_b3),(_b2),(_b1),(_b0)))
#define BITS7(_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   (BITS8(0,(_b6),(_b5),(_b4),(_b3),(_b2),(_b1),(_b0)))

#define BITS9(_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   (((_b8) << 8)  \
    | BITS8((_b7),(_b6),(_b5),(_b4),(_b3),(_b2),(_b1),(_b0)))

#define BITS10(_b9,_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   (((_b9) << 9) | ((_b8) << 8)  \
    | BITS8((_b7),(_b6),(_b5),(_b4),(_b3),(_b2),(_b1),(_b0)))

#define BITS11(_b10,_b9,_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   (((_b10) << 10)  \
    | BITS10(_b9,_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0))

#define BITS12(_b11, _b10,_b9,_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0) \
   (((_b11) << 11)  \
    | BITS11(_b10,_b9,_b8,_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0))

#define SLICE_UInt(_uint,_bMax,_bMin)  \
   (( ((UInt)(_uint)) >> (_bMin))  \
    & (UInt)((1ULL << ((_bMax) - (_bMin) + 1)) - 1ULL))



static IRExpr* mkV128 ( UShort w )
{
   return IRExpr_Const(IRConst_V128(w));
}

static IRExpr* mkU64 ( ULong i )
{
   return IRExpr_Const(IRConst_U64(i));
}

static IRExpr* mkU32 ( UInt i )
{
   return IRExpr_Const(IRConst_U32(i));
}

static IRExpr* mkU8 ( UInt i )
{
   vassert(i < 256);
   return IRExpr_Const(IRConst_U8( (UChar)i ));
}

static IRExpr* mkexpr ( IRTemp tmp )
{
   return IRExpr_RdTmp(tmp);
}

static IRExpr* unop ( IROp op, IRExpr* a )
{
   return IRExpr_Unop(op, a);
}

static IRExpr* binop ( IROp op, IRExpr* a1, IRExpr* a2 )
{
   return IRExpr_Binop(op, a1, a2);
}

static IRExpr* triop ( IROp op, IRExpr* a1, IRExpr* a2, IRExpr* a3 )
{
   return IRExpr_Triop(op, a1, a2, a3);
}

static IRExpr* loadLE ( IRType ty, IRExpr* addr )
{
   return IRExpr_Load(Iend_LE, ty, addr);
}

static void stmt ( IRStmt* st )
{
   addStmtToIRSB( irsb, st );
}

static void assign ( IRTemp dst, IRExpr* e )
{
   stmt( IRStmt_WrTmp(dst, e) );
}

static void storeLE ( IRExpr* addr, IRExpr* data )
{
   stmt( IRStmt_Store(Iend_LE, addr, data) );
}


static IRTemp newTemp ( IRType ty )
{
   vassert(isPlausibleIRType(ty));
   return newIRTemp( irsb->tyenv, ty );
}


static IROp mkAND ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_And32;
      case Ity_I64: return Iop_And64;
      default: vpanic("mkAND");
   }
}

static IROp mkOR ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Or32;
      case Ity_I64: return Iop_Or64;
      default: vpanic("mkOR");
   }
}

static IROp mkXOR ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Xor32;
      case Ity_I64: return Iop_Xor64;
      default: vpanic("mkXOR");
   }
}

static IROp mkSHL ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Shl32;
      case Ity_I64: return Iop_Shl64;
      default: vpanic("mkSHL");
   }
}

static IROp mkSHR ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Shr32;
      case Ity_I64: return Iop_Shr64;
      default: vpanic("mkSHR");
   }
}

static IROp mkSAR ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Sar32;
      case Ity_I64: return Iop_Sar64;
      default: vpanic("mkSAR");
   }
}

static IROp mkNOT ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Not32;
      case Ity_I64: return Iop_Not64;
      default: vpanic("mkNOT");
   }
}

static IROp mkADD ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Add32;
      case Ity_I64: return Iop_Add64;
      default: vpanic("mkADD");
   }
}

static IROp mkSUB ( IRType ty ) {
   switch (ty) {
      case Ity_I32: return Iop_Sub32;
      case Ity_I64: return Iop_Sub64;
      default: vpanic("mkSUB");
   }
}

static IROp mkADDF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_AddF32;
      case Ity_F64: return Iop_AddF64;
      default: vpanic("mkADDF");
   }
}

static IROp mkSUBF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_SubF32;
      case Ity_F64: return Iop_SubF64;
      default: vpanic("mkSUBF");
   }
}

static IROp mkMULF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_MulF32;
      case Ity_F64: return Iop_MulF64;
      default: vpanic("mkMULF");
   }
}

static IROp mkDIVF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_DivF32;
      case Ity_F64: return Iop_DivF64;
      default: vpanic("mkMULF");
   }
}

static IROp mkNEGF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_NegF32;
      case Ity_F64: return Iop_NegF64;
      default: vpanic("mkNEGF");
   }
}

static IROp mkABSF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_AbsF32;
      case Ity_F64: return Iop_AbsF64;
      default: vpanic("mkNEGF");
   }
}

static IROp mkSQRTF ( IRType ty ) {
   switch (ty) {
      case Ity_F32: return Iop_SqrtF32;
      case Ity_F64: return Iop_SqrtF64;
      default: vpanic("mkNEGF");
   }
}

static IRExpr* mkU ( IRType ty, ULong imm ) {
   switch (ty) {
      case Ity_I32: return mkU32((UInt)(imm & 0xFFFFFFFFULL));
      case Ity_I64: return mkU64(imm);
      default: vpanic("mkU");
   }
}

static IRTemp mathROR ( IRType ty, IRTemp arg, UInt imm )
{
   UInt w = 0;
   if (ty == Ity_I64) {
      w = 64;
   } else {
      vassert(ty == Ity_I32);
      w = 32;
   }
   vassert(w != 0);
   vassert(imm < w);
   if (imm == 0) {
      return arg;
   }
   IRTemp res = newTemp(ty);
   assign(res, binop(mkOR(ty),
                     binop(mkSHL(ty), mkexpr(arg), mkU8(w - imm)),
                     binop(mkSHR(ty), mkexpr(arg), mkU8(imm)) ));
   return res;
}

static IRTemp mathREPLICATE ( IRType ty, IRTemp arg, UInt imm )
{
   UInt w = 0;
   if (ty == Ity_I64) {
      w = 64;
   } else {
      vassert(ty == Ity_I32);
      w = 32;
   }
   vassert(w != 0);
   vassert(imm < w);
   IRTemp res = newTemp(ty);
   assign(res, binop(mkSAR(ty),
                     binop(mkSHL(ty), mkexpr(arg), mkU8(w - 1 - imm)),
                     mkU8(w - 1)));
   return res;
}

static IRExpr* widenUto64 ( IRType srcTy, IRExpr* e )
{
   switch (srcTy) {
      case Ity_I64: return e;
      case Ity_I32: return unop(Iop_32Uto64, e);
      case Ity_I16: return unop(Iop_16Uto64, e);
      case Ity_I8:  return unop(Iop_8Uto64, e);
      default: vpanic("widenUto64(arm64)");
   }
}

static IRExpr* narrowFrom64 ( IRType dstTy, IRExpr* e )
{
   switch (dstTy) {
      case Ity_I64: return e;
      case Ity_I32: return unop(Iop_64to32, e);
      case Ity_I16: return unop(Iop_64to16, e);
      case Ity_I8:  return unop(Iop_64to8, e);
      default: vpanic("narrowFrom64(arm64)");
   }
}



#define OFFB_X0       offsetof(VexGuestARM64State,guest_X0)
#define OFFB_X1       offsetof(VexGuestARM64State,guest_X1)
#define OFFB_X2       offsetof(VexGuestARM64State,guest_X2)
#define OFFB_X3       offsetof(VexGuestARM64State,guest_X3)
#define OFFB_X4       offsetof(VexGuestARM64State,guest_X4)
#define OFFB_X5       offsetof(VexGuestARM64State,guest_X5)
#define OFFB_X6       offsetof(VexGuestARM64State,guest_X6)
#define OFFB_X7       offsetof(VexGuestARM64State,guest_X7)
#define OFFB_X8       offsetof(VexGuestARM64State,guest_X8)
#define OFFB_X9       offsetof(VexGuestARM64State,guest_X9)
#define OFFB_X10      offsetof(VexGuestARM64State,guest_X10)
#define OFFB_X11      offsetof(VexGuestARM64State,guest_X11)
#define OFFB_X12      offsetof(VexGuestARM64State,guest_X12)
#define OFFB_X13      offsetof(VexGuestARM64State,guest_X13)
#define OFFB_X14      offsetof(VexGuestARM64State,guest_X14)
#define OFFB_X15      offsetof(VexGuestARM64State,guest_X15)
#define OFFB_X16      offsetof(VexGuestARM64State,guest_X16)
#define OFFB_X17      offsetof(VexGuestARM64State,guest_X17)
#define OFFB_X18      offsetof(VexGuestARM64State,guest_X18)
#define OFFB_X19      offsetof(VexGuestARM64State,guest_X19)
#define OFFB_X20      offsetof(VexGuestARM64State,guest_X20)
#define OFFB_X21      offsetof(VexGuestARM64State,guest_X21)
#define OFFB_X22      offsetof(VexGuestARM64State,guest_X22)
#define OFFB_X23      offsetof(VexGuestARM64State,guest_X23)
#define OFFB_X24      offsetof(VexGuestARM64State,guest_X24)
#define OFFB_X25      offsetof(VexGuestARM64State,guest_X25)
#define OFFB_X26      offsetof(VexGuestARM64State,guest_X26)
#define OFFB_X27      offsetof(VexGuestARM64State,guest_X27)
#define OFFB_X28      offsetof(VexGuestARM64State,guest_X28)
#define OFFB_X29      offsetof(VexGuestARM64State,guest_X29)
#define OFFB_X30      offsetof(VexGuestARM64State,guest_X30)

#define OFFB_XSP      offsetof(VexGuestARM64State,guest_XSP)
#define OFFB_PC       offsetof(VexGuestARM64State,guest_PC)

#define OFFB_CC_OP    offsetof(VexGuestARM64State,guest_CC_OP)
#define OFFB_CC_DEP1  offsetof(VexGuestARM64State,guest_CC_DEP1)
#define OFFB_CC_DEP2  offsetof(VexGuestARM64State,guest_CC_DEP2)
#define OFFB_CC_NDEP  offsetof(VexGuestARM64State,guest_CC_NDEP)

#define OFFB_TPIDR_EL0 offsetof(VexGuestARM64State,guest_TPIDR_EL0)
#define OFFB_NRADDR   offsetof(VexGuestARM64State,guest_NRADDR)

#define OFFB_Q0       offsetof(VexGuestARM64State,guest_Q0)
#define OFFB_Q1       offsetof(VexGuestARM64State,guest_Q1)
#define OFFB_Q2       offsetof(VexGuestARM64State,guest_Q2)
#define OFFB_Q3       offsetof(VexGuestARM64State,guest_Q3)
#define OFFB_Q4       offsetof(VexGuestARM64State,guest_Q4)
#define OFFB_Q5       offsetof(VexGuestARM64State,guest_Q5)
#define OFFB_Q6       offsetof(VexGuestARM64State,guest_Q6)
#define OFFB_Q7       offsetof(VexGuestARM64State,guest_Q7)
#define OFFB_Q8       offsetof(VexGuestARM64State,guest_Q8)
#define OFFB_Q9       offsetof(VexGuestARM64State,guest_Q9)
#define OFFB_Q10      offsetof(VexGuestARM64State,guest_Q10)
#define OFFB_Q11      offsetof(VexGuestARM64State,guest_Q11)
#define OFFB_Q12      offsetof(VexGuestARM64State,guest_Q12)
#define OFFB_Q13      offsetof(VexGuestARM64State,guest_Q13)
#define OFFB_Q14      offsetof(VexGuestARM64State,guest_Q14)
#define OFFB_Q15      offsetof(VexGuestARM64State,guest_Q15)
#define OFFB_Q16      offsetof(VexGuestARM64State,guest_Q16)
#define OFFB_Q17      offsetof(VexGuestARM64State,guest_Q17)
#define OFFB_Q18      offsetof(VexGuestARM64State,guest_Q18)
#define OFFB_Q19      offsetof(VexGuestARM64State,guest_Q19)
#define OFFB_Q20      offsetof(VexGuestARM64State,guest_Q20)
#define OFFB_Q21      offsetof(VexGuestARM64State,guest_Q21)
#define OFFB_Q22      offsetof(VexGuestARM64State,guest_Q22)
#define OFFB_Q23      offsetof(VexGuestARM64State,guest_Q23)
#define OFFB_Q24      offsetof(VexGuestARM64State,guest_Q24)
#define OFFB_Q25      offsetof(VexGuestARM64State,guest_Q25)
#define OFFB_Q26      offsetof(VexGuestARM64State,guest_Q26)
#define OFFB_Q27      offsetof(VexGuestARM64State,guest_Q27)
#define OFFB_Q28      offsetof(VexGuestARM64State,guest_Q28)
#define OFFB_Q29      offsetof(VexGuestARM64State,guest_Q29)
#define OFFB_Q30      offsetof(VexGuestARM64State,guest_Q30)
#define OFFB_Q31      offsetof(VexGuestARM64State,guest_Q31)

#define OFFB_FPCR     offsetof(VexGuestARM64State,guest_FPCR)
#define OFFB_FPSR     offsetof(VexGuestARM64State,guest_FPSR)

#define OFFB_CMSTART  offsetof(VexGuestARM64State,guest_CMSTART)
#define OFFB_CMLEN    offsetof(VexGuestARM64State,guest_CMLEN)



static Int offsetIReg64 ( UInt iregNo )
{
   switch (iregNo) {
      case 0:  return OFFB_X0;
      case 1:  return OFFB_X1;
      case 2:  return OFFB_X2;
      case 3:  return OFFB_X3;
      case 4:  return OFFB_X4;
      case 5:  return OFFB_X5;
      case 6:  return OFFB_X6;
      case 7:  return OFFB_X7;
      case 8:  return OFFB_X8;
      case 9:  return OFFB_X9;
      case 10: return OFFB_X10;
      case 11: return OFFB_X11;
      case 12: return OFFB_X12;
      case 13: return OFFB_X13;
      case 14: return OFFB_X14;
      case 15: return OFFB_X15;
      case 16: return OFFB_X16;
      case 17: return OFFB_X17;
      case 18: return OFFB_X18;
      case 19: return OFFB_X19;
      case 20: return OFFB_X20;
      case 21: return OFFB_X21;
      case 22: return OFFB_X22;
      case 23: return OFFB_X23;
      case 24: return OFFB_X24;
      case 25: return OFFB_X25;
      case 26: return OFFB_X26;
      case 27: return OFFB_X27;
      case 28: return OFFB_X28;
      case 29: return OFFB_X29;
      case 30: return OFFB_X30;
      
      default: vassert(0);
   }
}

static Int offsetIReg64orSP ( UInt iregNo )
{
   return iregNo == 31  ? OFFB_XSP  : offsetIReg64(iregNo);
}

static const HChar* nameIReg64orZR ( UInt iregNo )
{
   vassert(iregNo < 32);
   static const HChar* names[32]
      = { "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7", 
          "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15", 
          "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", 
          "x24", "x25", "x26", "x27", "x28", "x29", "x30", "xzr" };
   return names[iregNo];
}

static const HChar* nameIReg64orSP ( UInt iregNo )
{
   if (iregNo == 31) {
      return "sp";
   }
   vassert(iregNo < 31);
   return nameIReg64orZR(iregNo);
}

static IRExpr* getIReg64orSP ( UInt iregNo )
{
   vassert(iregNo < 32);
   return IRExpr_Get( offsetIReg64orSP(iregNo), Ity_I64 );
}

static IRExpr* getIReg64orZR ( UInt iregNo )
{
   if (iregNo == 31) {
      return mkU64(0);
   }
   vassert(iregNo < 31);
   return IRExpr_Get( offsetIReg64orSP(iregNo), Ity_I64 );
}

static void putIReg64orSP ( UInt iregNo, IRExpr* e ) 
{
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I64);
   stmt( IRStmt_Put(offsetIReg64orSP(iregNo), e) );
}

static void putIReg64orZR ( UInt iregNo, IRExpr* e ) 
{
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I64);
   if (iregNo == 31) {
      return;
   }
   vassert(iregNo < 31);
   stmt( IRStmt_Put(offsetIReg64orSP(iregNo), e) );
}

static const HChar* nameIReg32orZR ( UInt iregNo )
{
   vassert(iregNo < 32);
   static const HChar* names[32]
      = { "w0",  "w1",  "w2",  "w3",  "w4",  "w5",  "w6",  "w7", 
          "w8",  "w9",  "w10", "w11", "w12", "w13", "w14", "w15", 
          "w16", "w17", "w18", "w19", "w20", "w21", "w22", "w23", 
          "w24", "w25", "w26", "w27", "w28", "w29", "w30", "wzr" };
   return names[iregNo];
}

static const HChar* nameIReg32orSP ( UInt iregNo )
{
   if (iregNo == 31) {
      return "wsp";
   }
   vassert(iregNo < 31);
   return nameIReg32orZR(iregNo);
}

static IRExpr* getIReg32orSP ( UInt iregNo )
{
   vassert(iregNo < 32);
   return unop(Iop_64to32,
               IRExpr_Get( offsetIReg64orSP(iregNo), Ity_I64 ));
}

static IRExpr* getIReg32orZR ( UInt iregNo )
{
   if (iregNo == 31) {
      return mkU32(0);
   }
   vassert(iregNo < 31);
   return unop(Iop_64to32,
               IRExpr_Get( offsetIReg64orSP(iregNo), Ity_I64 ));
}

static void putIReg32orSP ( UInt iregNo, IRExpr* e ) 
{
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I32);
   stmt( IRStmt_Put(offsetIReg64orSP(iregNo), unop(Iop_32Uto64, e)) );
}

static void putIReg32orZR ( UInt iregNo, IRExpr* e ) 
{
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I32);
   if (iregNo == 31) {
      return;
   }
   vassert(iregNo < 31);
   stmt( IRStmt_Put(offsetIReg64orSP(iregNo), unop(Iop_32Uto64, e)) );
}

static const HChar* nameIRegOrSP ( Bool is64, UInt iregNo )
{
   vassert(is64 == True || is64 == False);
   return is64 ? nameIReg64orSP(iregNo) : nameIReg32orSP(iregNo);
}

static const HChar* nameIRegOrZR ( Bool is64, UInt iregNo )
{
   vassert(is64 == True || is64 == False);
   return is64 ? nameIReg64orZR(iregNo) : nameIReg32orZR(iregNo);
}

static IRExpr* getIRegOrZR ( Bool is64, UInt iregNo )
{
   vassert(is64 == True || is64 == False);
   return is64 ? getIReg64orZR(iregNo) : getIReg32orZR(iregNo);
}

static void putIRegOrZR ( Bool is64, UInt iregNo, IRExpr* e )
{
   vassert(is64 == True || is64 == False);
   if (is64) putIReg64orZR(iregNo, e); else putIReg32orZR(iregNo, e);
}

static void putPC ( IRExpr* e )
{
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I64);
   stmt( IRStmt_Put(OFFB_PC, e) );
}



static Int offsetQReg128 ( UInt qregNo )
{
   switch (qregNo) {
      case 0:  return OFFB_Q0;
      case 1:  return OFFB_Q1;
      case 2:  return OFFB_Q2;
      case 3:  return OFFB_Q3;
      case 4:  return OFFB_Q4;
      case 5:  return OFFB_Q5;
      case 6:  return OFFB_Q6;
      case 7:  return OFFB_Q7;
      case 8:  return OFFB_Q8;
      case 9:  return OFFB_Q9;
      case 10: return OFFB_Q10;
      case 11: return OFFB_Q11;
      case 12: return OFFB_Q12;
      case 13: return OFFB_Q13;
      case 14: return OFFB_Q14;
      case 15: return OFFB_Q15;
      case 16: return OFFB_Q16;
      case 17: return OFFB_Q17;
      case 18: return OFFB_Q18;
      case 19: return OFFB_Q19;
      case 20: return OFFB_Q20;
      case 21: return OFFB_Q21;
      case 22: return OFFB_Q22;
      case 23: return OFFB_Q23;
      case 24: return OFFB_Q24;
      case 25: return OFFB_Q25;
      case 26: return OFFB_Q26;
      case 27: return OFFB_Q27;
      case 28: return OFFB_Q28;
      case 29: return OFFB_Q29;
      case 30: return OFFB_Q30;
      case 31: return OFFB_Q31;
      default: vassert(0);
   }
}

static void putQReg128 ( UInt qregNo, IRExpr* e )
{
   vassert(qregNo < 32);
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_V128);
   stmt( IRStmt_Put(offsetQReg128(qregNo), e) );
}

static IRExpr* getQReg128 ( UInt qregNo )
{
   vassert(qregNo < 32);
   return IRExpr_Get(offsetQReg128(qregNo), Ity_V128);
}

static IRType preferredVectorSubTypeFromSize ( UInt szB )
{
   switch (szB) {
      case 1:  return Ity_I8;
      case 2:  return Ity_I16;
      case 4:  return Ity_I32; 
      case 8:  return Ity_F64;
      case 16: return Ity_V128;
      default: vassert(0);
   }
}

static Int offsetQRegLane ( UInt qregNo, IRType laneTy, UInt laneNo )
{
   vassert(!host_is_bigendian);
   Int base = offsetQReg128(qregNo);
   UInt laneSzB = 0;
   switch (laneTy) {
      case Ity_I8:                 laneSzB = 1;  break;
      case Ity_I16:                laneSzB = 2;  break;
      case Ity_F32: case Ity_I32:  laneSzB = 4;  break;
      case Ity_F64: case Ity_I64:  laneSzB = 8;  break;
      case Ity_V128:               laneSzB = 16; break;
      default: break;
   }
   vassert(laneSzB > 0);
   UInt minOff = laneNo * laneSzB;
   UInt maxOff = minOff + laneSzB - 1;
   vassert(maxOff < 16);
   return base + minOff;
}

static void putQRegLO ( UInt qregNo, IRExpr* e )
{
   IRType ty  = typeOfIRExpr(irsb->tyenv, e);
   Int    off = offsetQRegLane(qregNo, ty, 0);
   switch (ty) {
      case Ity_I8:  case Ity_I16: case Ity_I32: case Ity_I64:
      case Ity_F32: case Ity_F64: case Ity_V128:
         break;
      default:
         vassert(0); 
   }
   stmt(IRStmt_Put(off, e));
}

static IRExpr* getQRegLO ( UInt qregNo, IRType ty )
{
   Int off = offsetQRegLane(qregNo, ty, 0);
   switch (ty) {
      case Ity_I8:
      case Ity_I16:
      case Ity_I32: case Ity_I64:
      case Ity_F32: case Ity_F64: case Ity_V128:
         break;
      default:
         vassert(0); 
   }
   return IRExpr_Get(off, ty);
}

static const HChar* nameQRegLO ( UInt qregNo, IRType laneTy )
{
   static const HChar* namesQ[32]
      = { "q0",  "q1",  "q2",  "q3",  "q4",  "q5",  "q6",  "q7", 
          "q8",  "q9",  "q10", "q11", "q12", "q13", "q14", "q15", 
          "q16", "q17", "q18", "q19", "q20", "q21", "q22", "q23", 
          "q24", "q25", "q26", "q27", "q28", "q29", "q30", "q31" };
   static const HChar* namesD[32]
      = { "d0",  "d1",  "d2",  "d3",  "d4",  "d5",  "d6",  "d7", 
          "d8",  "d9",  "d10", "d11", "d12", "d13", "d14", "d15", 
          "d16", "d17", "d18", "d19", "d20", "d21", "d22", "d23", 
          "d24", "d25", "d26", "d27", "d28", "d29", "d30", "d31" };
   static const HChar* namesS[32]
      = { "s0",  "s1",  "s2",  "s3",  "s4",  "s5",  "s6",  "s7", 
          "s8",  "s9",  "s10", "s11", "s12", "s13", "s14", "s15", 
          "s16", "s17", "s18", "s19", "s20", "s21", "s22", "s23", 
          "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31" };
   static const HChar* namesH[32]
      = { "h0",  "h1",  "h2",  "h3",  "h4",  "h5",  "h6",  "h7", 
          "h8",  "h9",  "h10", "h11", "h12", "h13", "h14", "h15", 
          "h16", "h17", "h18", "h19", "h20", "h21", "h22", "h23", 
          "h24", "h25", "h26", "h27", "h28", "h29", "h30", "h31" };
   static const HChar* namesB[32]
      = { "b0",  "b1",  "b2",  "b3",  "b4",  "b5",  "b6",  "b7", 
          "b8",  "b9",  "b10", "b11", "b12", "b13", "b14", "b15", 
          "b16", "b17", "b18", "b19", "b20", "b21", "b22", "b23", 
          "b24", "b25", "b26", "b27", "b28", "b29", "b30", "b31" };
   vassert(qregNo < 32);
   switch (sizeofIRType(laneTy)) {
      case 1:  return namesB[qregNo];
      case 2:  return namesH[qregNo];
      case 4:  return namesS[qregNo];
      case 8:  return namesD[qregNo];
      case 16: return namesQ[qregNo];
      default: vassert(0);
   }
   
}

static const HChar* nameQReg128 ( UInt qregNo )
{
   return nameQRegLO(qregNo, Ity_V128);
}

static Int offsetQRegHI64 ( UInt qregNo )
{
   return offsetQRegLane(qregNo, Ity_I64, 1);
}

static IRExpr* getQRegHI64 ( UInt qregNo )
{
   return IRExpr_Get(offsetQRegHI64(qregNo), Ity_I64);
}

static void putQRegHI64 ( UInt qregNo, IRExpr* e )
{
   IRType ty  = typeOfIRExpr(irsb->tyenv, e);
   Int    off = offsetQRegHI64(qregNo);
   switch (ty) {
      case Ity_I64: case Ity_F64:
         break;
      default:
         vassert(0); 
   }
   stmt(IRStmt_Put(off, e));
}

static void putQRegLane ( UInt qregNo, UInt laneNo, IRExpr* e )
{
   IRType laneTy  = typeOfIRExpr(irsb->tyenv, e);
   Int    off     = offsetQRegLane(qregNo, laneTy, laneNo);
   switch (laneTy) {
      case Ity_F64: case Ity_I64:
      case Ity_I32: case Ity_F32:
      case Ity_I16:
      case Ity_I8:
         break;
      default:
         vassert(0); 
   }
   stmt(IRStmt_Put(off, e));
}

static IRExpr* getQRegLane ( UInt qregNo, UInt laneNo, IRType laneTy )
{
   Int off = offsetQRegLane(qregNo, laneTy, laneNo);
   switch (laneTy) {
      case Ity_I64: case Ity_I32: case Ity_I16: case Ity_I8:
      case Ity_F64:
         break;
      default:
         vassert(0); 
   }
   return IRExpr_Get(off, laneTy);
}





static IRTemp  mk_get_IR_rounding_mode ( void )
{
   IRTemp armEncd = newTemp(Ity_I32);
   IRTemp swapped = newTemp(Ity_I32);
   assign(armEncd,
          binop(Iop_Shr32, IRExpr_Get(OFFB_FPCR, Ity_I32), mkU8(22)));
   
   assign(swapped,
          binop(Iop_Or32,
                binop(Iop_And32,
                      binop(Iop_Shl32, mkexpr(armEncd), mkU8(1)),
                      mkU32(2)),
                binop(Iop_And32,
                      binop(Iop_Shr32, mkexpr(armEncd), mkU8(1)),
                      mkU32(1))
         ));
   return swapped;
}



static const HChar* nameARM64Condcode ( ARM64Condcode cond )
{
   switch (cond) {
      case ARM64CondEQ:  return "eq";
      case ARM64CondNE:  return "ne";
      case ARM64CondCS:  return "cs";  
      case ARM64CondCC:  return "cc";  
      case ARM64CondMI:  return "mi";
      case ARM64CondPL:  return "pl";
      case ARM64CondVS:  return "vs";
      case ARM64CondVC:  return "vc";
      case ARM64CondHI:  return "hi";
      case ARM64CondLS:  return "ls";
      case ARM64CondGE:  return "ge";
      case ARM64CondLT:  return "lt";
      case ARM64CondGT:  return "gt";
      case ARM64CondLE:  return "le";
      case ARM64CondAL:  return "al";
      case ARM64CondNV:  return "nv";
      default: vpanic("name_ARM64Condcode");
   }
}

static const HChar* nameCC ( ARM64Condcode cond ) {
   return nameARM64Condcode(cond);
}


static IRExpr* mk_arm64g_calculate_condition_dyn ( IRExpr* cond )
{
   vassert(typeOfIRExpr(irsb->tyenv, cond) == Ity_I64);

   IRExpr** args
      = mkIRExprVec_4(
           binop(Iop_Or64, IRExpr_Get(OFFB_CC_OP, Ity_I64), cond),
           IRExpr_Get(OFFB_CC_DEP1, Ity_I64),
           IRExpr_Get(OFFB_CC_DEP2, Ity_I64),
           IRExpr_Get(OFFB_CC_NDEP, Ity_I64)
        );
   IRExpr* call
      = mkIRExprCCall(
           Ity_I64,
           0, 
           "arm64g_calculate_condition", &arm64g_calculate_condition,
           args
        );

   call->Iex.CCall.cee->mcx_mask = (1<<0) | (1<<3);
   return call;
}


static IRExpr* mk_arm64g_calculate_condition ( ARM64Condcode cond )
{
   vassert(cond >= 0 && cond <= 15);
   return mk_arm64g_calculate_condition_dyn( mkU64(cond << 4) );
}


static IRExpr* mk_arm64g_calculate_flag_c ( void )
{
   IRExpr** args
      = mkIRExprVec_4( IRExpr_Get(OFFB_CC_OP,   Ity_I64),
                       IRExpr_Get(OFFB_CC_DEP1, Ity_I64),
                       IRExpr_Get(OFFB_CC_DEP2, Ity_I64),
                       IRExpr_Get(OFFB_CC_NDEP, Ity_I64) );
   IRExpr* call
      = mkIRExprCCall(
           Ity_I64,
           0,
           "arm64g_calculate_flag_c", &arm64g_calculate_flag_c,
           args
        );
   call->Iex.CCall.cee->mcx_mask = (1<<0) | (1<<3);
   return call;
}




static IRExpr* mk_arm64g_calculate_flags_nzcv ( void )
{
   IRExpr** args
      = mkIRExprVec_4( IRExpr_Get(OFFB_CC_OP,   Ity_I64),
                       IRExpr_Get(OFFB_CC_DEP1, Ity_I64),
                       IRExpr_Get(OFFB_CC_DEP2, Ity_I64),
                       IRExpr_Get(OFFB_CC_NDEP, Ity_I64) );
   IRExpr* call
      = mkIRExprCCall(
           Ity_I64,
           0, 
           "arm64g_calculate_flags_nzcv", &arm64g_calculate_flags_nzcv,
           args
        );
   call->Iex.CCall.cee->mcx_mask = (1<<0) | (1<<3);
   return call;
}


static
void setFlags_D1_D2_ND ( UInt cc_op,
                         IRTemp t_dep1, IRTemp t_dep2, IRTemp t_ndep )
{
   vassert(typeOfIRTemp(irsb->tyenv, t_dep1 == Ity_I64));
   vassert(typeOfIRTemp(irsb->tyenv, t_dep2 == Ity_I64));
   vassert(typeOfIRTemp(irsb->tyenv, t_ndep == Ity_I64));
   vassert(cc_op >= ARM64G_CC_OP_COPY && cc_op < ARM64G_CC_OP_NUMBER);
   stmt( IRStmt_Put( OFFB_CC_OP,   mkU64(cc_op) ));
   stmt( IRStmt_Put( OFFB_CC_DEP1, mkexpr(t_dep1) ));
   stmt( IRStmt_Put( OFFB_CC_DEP2, mkexpr(t_dep2) ));
   stmt( IRStmt_Put( OFFB_CC_NDEP, mkexpr(t_ndep) ));
}

static
void setFlags_ADD_SUB ( Bool is64, Bool isSUB, IRTemp argL, IRTemp argR )
{
   IRTemp argL64 = IRTemp_INVALID;
   IRTemp argR64 = IRTemp_INVALID;
   IRTemp z64    = newTemp(Ity_I64);
   if (is64) {
      argL64 = argL;
      argR64 = argR;
   } else {
      argL64 = newTemp(Ity_I64);
      argR64 = newTemp(Ity_I64);
      assign(argL64, unop(Iop_32Uto64, mkexpr(argL)));
      assign(argR64, unop(Iop_32Uto64, mkexpr(argR)));
   }
   assign(z64, mkU64(0));
   UInt cc_op = ARM64G_CC_OP_NUMBER;
    if ( isSUB &&  is64) { cc_op = ARM64G_CC_OP_SUB64; }
   else if ( isSUB && !is64) { cc_op = ARM64G_CC_OP_SUB32; }
   else if (!isSUB &&  is64) { cc_op = ARM64G_CC_OP_ADD64; }
   else if (!isSUB && !is64) { cc_op = ARM64G_CC_OP_ADD32; }
   else                      { vassert(0); }
   setFlags_D1_D2_ND(cc_op, argL64, argR64, z64);
}

static
void setFlags_ADC_SBC(Bool is64, Bool isSBC, IRTemp argL, IRTemp argR, IRTemp oldC)
{
   IRTemp argL64 = IRTemp_INVALID;
   IRTemp argR64 = IRTemp_INVALID;
   IRTemp oldC64 = IRTemp_INVALID;
   if (is64) {
      argL64 = argL;
      argR64 = argR;
      oldC64 = oldC;
   } else {
      argL64 = newTemp(Ity_I64);
      argR64 = newTemp(Ity_I64);
      oldC64 = newTemp(Ity_I64);
      assign(argL64, unop(Iop_32Uto64, mkexpr(argL)));
      assign(argR64, unop(Iop_32Uto64, mkexpr(argR)));
      assign(oldC64, unop(Iop_32Uto64, mkexpr(oldC)));
   }
   UInt cc_op = ARM64G_CC_OP_NUMBER;
    if ( isSBC &&  is64) { cc_op = ARM64G_CC_OP_SBC64; }
   else if ( isSBC && !is64) { cc_op = ARM64G_CC_OP_SBC32; }
   else if (!isSBC &&  is64) { cc_op = ARM64G_CC_OP_ADC64; }
   else if (!isSBC && !is64) { cc_op = ARM64G_CC_OP_ADC32; }
   else                      { vassert(0); }
   setFlags_D1_D2_ND(cc_op, argL64, argR64, oldC64);
}

static
void setFlags_ADD_SUB_conditionally (
        Bool is64, Bool isSUB,
        IRTemp cond, IRTemp argL, IRTemp argR, UInt nzcv
     )
{

   IRTemp z64 = newTemp(Ity_I64);
   assign(z64, mkU64(0));

   
   IRTemp t_dep1 = IRTemp_INVALID;
   IRTemp t_dep2 = IRTemp_INVALID;
   UInt   t_op   = ARM64G_CC_OP_NUMBER;
    if ( isSUB &&  is64) { t_op = ARM64G_CC_OP_SUB64; }
   else if ( isSUB && !is64) { t_op = ARM64G_CC_OP_SUB32; }
   else if (!isSUB &&  is64) { t_op = ARM64G_CC_OP_ADD64; }
   else if (!isSUB && !is64) { t_op = ARM64G_CC_OP_ADD32; }
   else                      { vassert(0); }
   
   if (is64) {
      t_dep1 = argL;
      t_dep2 = argR;
   } else {
      t_dep1 = newTemp(Ity_I64);
      t_dep2 = newTemp(Ity_I64);
      assign(t_dep1, unop(Iop_32Uto64, mkexpr(argL)));
      assign(t_dep2, unop(Iop_32Uto64, mkexpr(argR)));
   }

   
   IRTemp f_dep1 = newTemp(Ity_I64);
   IRTemp f_dep2 = z64;
   UInt   f_op   = ARM64G_CC_OP_COPY;
   assign(f_dep1, mkU64(nzcv << 28));

   
   IRTemp dep1 = newTemp(Ity_I64);
   IRTemp dep2 = newTemp(Ity_I64);
   IRTemp op   = newTemp(Ity_I64);

   assign(op,   IRExpr_ITE(mkexpr(cond), mkU64(t_op), mkU64(f_op)));
   assign(dep1, IRExpr_ITE(mkexpr(cond), mkexpr(t_dep1), mkexpr(f_dep1)));
   assign(dep2, IRExpr_ITE(mkexpr(cond), mkexpr(t_dep2), mkexpr(f_dep2)));

   
   stmt( IRStmt_Put( OFFB_CC_OP,   mkexpr(op) ));
   stmt( IRStmt_Put( OFFB_CC_DEP1, mkexpr(dep1) ));
   stmt( IRStmt_Put( OFFB_CC_DEP2, mkexpr(dep2) ));
   stmt( IRStmt_Put( OFFB_CC_NDEP, mkexpr(z64) ));
}

static
void setFlags_LOGIC ( Bool is64, IRTemp res )
{
   IRTemp res64 = IRTemp_INVALID;
   IRTemp z64   = newTemp(Ity_I64);
   UInt   cc_op = ARM64G_CC_OP_NUMBER;
   if (is64) {
      res64 = res;
      cc_op = ARM64G_CC_OP_LOGIC64;
   } else {
      res64 = newTemp(Ity_I64);
      assign(res64, unop(Iop_32Uto64, mkexpr(res)));
      cc_op = ARM64G_CC_OP_LOGIC32;
   }
   assign(z64, mkU64(0));
   setFlags_D1_D2_ND(cc_op, res64, z64, z64);
}

static
void setFlags_COPY ( IRTemp nzcv_28x0 )
{
   IRTemp z64 = newTemp(Ity_I64);
   assign(z64, mkU64(0));
   setFlags_D1_D2_ND(ARM64G_CC_OP_COPY, nzcv_28x0, z64, z64);
}





static IRTemp math_SWAPHELPER ( IRTemp x, ULong mask, Int sh )
{
   IRTemp maskT = newTemp(Ity_I64);
   IRTemp res   = newTemp(Ity_I64);
   vassert(sh >= 1 && sh <= 63);
   assign(maskT, mkU64(mask));
   assign( res,
           binop(Iop_Or64,
                 binop(Iop_Shr64,
                       binop(Iop_And64,mkexpr(x),mkexpr(maskT)),
                       mkU8(sh)),
                 binop(Iop_And64,
                       binop(Iop_Shl64,mkexpr(x),mkU8(sh)),
                       mkexpr(maskT))
                 ) 
           );
   return res;
}

static IRTemp math_UINTSWAP64 ( IRTemp src )
{
   IRTemp res;
   res = math_SWAPHELPER(src, 0xFF00FF00FF00FF00ULL, 8);
   res = math_SWAPHELPER(res, 0xFFFF0000FFFF0000ULL, 16);
   return res;
}

static IRTemp math_USHORTSWAP64 ( IRTemp src )
{
   IRTemp res;
   res = math_SWAPHELPER(src, 0xFF00FF00FF00FF00ULL, 8);
   return res;
}

static IRTemp math_BYTESWAP64 ( IRTemp src )
{
   IRTemp res;
   res = math_SWAPHELPER(src, 0xFF00FF00FF00FF00ULL, 8);
   res = math_SWAPHELPER(res, 0xFFFF0000FFFF0000ULL, 16);
   res = math_SWAPHELPER(res, 0xFFFFFFFF00000000ULL, 32);
   return res;
}

static IRTemp math_BITSWAP64 ( IRTemp src )
{
   IRTemp res;
   res = math_SWAPHELPER(src, 0xAAAAAAAAAAAAAAAAULL, 1);
   res = math_SWAPHELPER(res, 0xCCCCCCCCCCCCCCCCULL, 2);
   res = math_SWAPHELPER(res, 0xF0F0F0F0F0F0F0F0ULL, 4);
   return math_BYTESWAP64(res);
}

static IRTemp math_DUP_TO_64 ( IRTemp src, IRType srcTy )
{
   if (srcTy == Ity_I8) {
      IRTemp t16 = newTemp(Ity_I64);
      assign(t16, binop(Iop_Or64, mkexpr(src),
                                  binop(Iop_Shl64, mkexpr(src), mkU8(8))));
      IRTemp t32 = newTemp(Ity_I64);
      assign(t32, binop(Iop_Or64, mkexpr(t16),
                                  binop(Iop_Shl64, mkexpr(t16), mkU8(16))));
      IRTemp t64 = newTemp(Ity_I64);
      assign(t64, binop(Iop_Or64, mkexpr(t32),
                                  binop(Iop_Shl64, mkexpr(t32), mkU8(32))));
      return t64;
   }
   if (srcTy == Ity_I16) {
      IRTemp t32 = newTemp(Ity_I64);
      assign(t32, binop(Iop_Or64, mkexpr(src),
                                  binop(Iop_Shl64, mkexpr(src), mkU8(16))));
      IRTemp t64 = newTemp(Ity_I64);
      assign(t64, binop(Iop_Or64, mkexpr(t32),
                                  binop(Iop_Shl64, mkexpr(t32), mkU8(32))));
      return t64;
   }
   if (srcTy == Ity_I32) {
      IRTemp t64 = newTemp(Ity_I64);
      assign(t64, binop(Iop_Or64, mkexpr(src),
                                  binop(Iop_Shl64, mkexpr(src), mkU8(32))));
      return t64;
   }
   if (srcTy == Ity_I64) {
      return src;
   }
   vassert(0);
}



static
IRTemp mk_convert_IRCmpF64Result_to_NZCV ( IRTemp irRes32 )
{
   IRTemp ix       = newTemp(Ity_I64);
   IRTemp termL    = newTemp(Ity_I64);
   IRTemp termR    = newTemp(Ity_I64);
   IRTemp nzcv     = newTemp(Ity_I64);
   IRTemp irRes    = newTemp(Ity_I64);

   
   assign(irRes, unop(Iop_32Uto64, mkexpr(irRes32)));

   assign(
      ix,
      binop(Iop_Or64,
            binop(Iop_And64,
                  binop(Iop_Shr64, mkexpr(irRes), mkU8(5)),
                  mkU64(3)),
            binop(Iop_And64, mkexpr(irRes), mkU64(1))));

   assign(
      termL,
      binop(Iop_Add64,
            binop(Iop_Shr64,
                  binop(Iop_Sub64,
                        binop(Iop_Shl64,
                              binop(Iop_Xor64, mkexpr(ix), mkU64(1)),
                              mkU8(62)),
                        mkU64(1)),
                  mkU8(61)),
            mkU64(1)));

   assign(
      termR,
      binop(Iop_And64,
            binop(Iop_And64,
                  mkexpr(ix),
                  binop(Iop_Shr64, mkexpr(ix), mkU8(1))),
            mkU64(1)));

   assign(nzcv, binop(Iop_Sub64, mkexpr(termL), mkexpr(termR)));
   return nzcv;
}




static ULong dbm_ROR ( Int width, ULong x, Int rot )
{
   vassert(width > 0 && width <= 64);
   vassert(rot >= 0 && rot < width);
   if (rot == 0) return x;
   ULong res = x >> rot;
   res |= (x << (width - rot));
   if (width < 64)
     res &= ((1ULL << width) - 1);
   return res;
}

static ULong dbm_RepTo64( Int esize, ULong x )
{
   switch (esize) {
      case 64:
         return x;
      case 32:
         x &= 0xFFFFFFFF; x |= (x << 32);
         return x;
      case 16:
         x &= 0xFFFF; x |= (x << 16); x |= (x << 32);
         return x;
      case 8:
         x &= 0xFF; x |= (x << 8); x |= (x << 16); x |= (x << 32);
         return x;
      case 4:
         x &= 0xF; x |= (x << 4); x |= (x << 8);
         x |= (x << 16); x |= (x << 32);
         return x;
      case 2:
         x &= 0x3; x |= (x << 2); x |= (x << 4); x |= (x << 8);
         x |= (x << 16); x |= (x << 32);
         return x;
      default:
         break;
   }
   vpanic("dbm_RepTo64");
   
   return 0;
}

static Int dbm_highestSetBit ( ULong x )
{
   Int i;
   for (i = 63; i >= 0; i--) {
      if (x & (1ULL << i))
         return i;
   }
   vassert(x == 0);
   return -1;
}

static
Bool dbm_DecodeBitMasks ( ULong* wmask, ULong* tmask, 
                          ULong immN, ULong imms, ULong immr, Bool immediate,
                          UInt M )
{
   vassert(immN < (1ULL << 1));
   vassert(imms < (1ULL << 6));
   vassert(immr < (1ULL << 6));
   vassert(immediate == False || immediate == True);
   vassert(M == 32 || M == 64);

   Int len = dbm_highestSetBit( ((immN << 6) & 64) | ((~imms) & 63) );
   if (len < 1) {  return False; }
   vassert(len <= 6);
   vassert(M >= (1 << len));

   vassert(len >= 1 && len <= 6);
   ULong levels = 
                  (1 << len) - 1;
   vassert(levels >= 1 && levels <= 63);

   if (immediate && ((imms & levels) == levels)) { 
      
      return False;
   }

   ULong S = imms & levels;
   ULong R = immr & levels;
   Int   diff = S - R;
   diff &= 63;
   Int esize = 1 << len;
   vassert(2 <= esize && esize <= 64);

   vassert(S >= 0 && S <= 63);
   vassert(esize >= (S+1));
   ULong elem_s = 
                  
                  ((1ULL << S) - 1) + (1ULL << S);

   Int d = 
           diff & ((1 << len)-1);
   vassert(esize >= (d+1));
   vassert(d >= 0 && d <= 63);

   ULong elem_d = 
                  
                  ((1ULL << d) - 1) + (1ULL << d);

   if (esize != 64) vassert(elem_s < (1ULL << esize));
   if (esize != 64) vassert(elem_d < (1ULL << esize));

   if (wmask) *wmask = dbm_RepTo64(esize, dbm_ROR(esize, elem_s, R));
   if (tmask) *tmask = dbm_RepTo64(esize, elem_d);

   return True;
}


static
Bool dis_ARM64_data_processing_immediate(DisResult* dres,
                                         UInt insn)
{
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))


   
   if (INSN(28,24) == BITS5(1,0,0,0,1)) {
      Bool is64   = INSN(31,31) == 1;
      Bool isSub  = INSN(30,30) == 1;
      Bool setCC  = INSN(29,29) == 1;
      UInt sh     = INSN(23,22);
      UInt uimm12 = INSN(21,10);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      const HChar* nm = isSub ? "sub" : "add";
      if (sh >= 2) {
         
      } else {
         vassert(sh <= 1);
         uimm12 <<= (12 * sh);
         if (is64) {
            IRTemp argL  = newTemp(Ity_I64);
            IRTemp argR  = newTemp(Ity_I64);
            IRTemp res   = newTemp(Ity_I64);
            assign(argL, getIReg64orSP(nn));
            assign(argR, mkU64(uimm12));
            assign(res,  binop(isSub ? Iop_Sub64 : Iop_Add64,
                               mkexpr(argL), mkexpr(argR)));
            if (setCC) {
               putIReg64orZR(dd, mkexpr(res));
               setFlags_ADD_SUB(True, isSub, argL, argR);
               DIP("%ss %s, %s, 0x%x\n",
                   nm, nameIReg64orZR(dd), nameIReg64orSP(nn), uimm12);
            } else {
               putIReg64orSP(dd, mkexpr(res));
               DIP("%s %s, %s, 0x%x\n",
                   nm, nameIReg64orSP(dd), nameIReg64orSP(nn), uimm12);
            }
         } else {
            IRTemp argL  = newTemp(Ity_I32);
            IRTemp argR  = newTemp(Ity_I32);
            IRTemp res   = newTemp(Ity_I32);
            assign(argL, getIReg32orSP(nn));
            assign(argR, mkU32(uimm12));
            assign(res,  binop(isSub ? Iop_Sub32 : Iop_Add32,
                               mkexpr(argL), mkexpr(argR)));
            if (setCC) {
               putIReg32orZR(dd, mkexpr(res));
               setFlags_ADD_SUB(False, isSub, argL, argR);
               DIP("%ss %s, %s, 0x%x\n",
                   nm, nameIReg32orZR(dd), nameIReg32orSP(nn), uimm12);
            } else {
               putIReg32orSP(dd, mkexpr(res));
               DIP("%s %s, %s, 0x%x\n",
                   nm, nameIReg32orSP(dd), nameIReg32orSP(nn), uimm12);
            }
         }
         return True;
      }
   }

   
   if (INSN(28,24) == BITS5(1,0,0,0,0)) {
      UInt  bP    = INSN(31,31);
      UInt  immLo = INSN(30,29);
      UInt  immHi = INSN(23,5);
      UInt  rD    = INSN(4,0);
      ULong uimm  = (immHi << 2) | immLo;
      ULong simm  = sx_to_64(uimm, 21);
      ULong val;
      if (bP) {
         val = (guest_PC_curr_instr & 0xFFFFFFFFFFFFF000ULL) + (simm << 12);
      } else {
         val = guest_PC_curr_instr + simm;
      }
      putIReg64orZR(rD, mkU64(val));
      DIP("adr%s %s, 0x%llx\n", bP ? "p" : "", nameIReg64orZR(rD), val);
      return True;
   }

   
   if (INSN(28,23) == BITS6(1,0,0,1,0,0)) {
      Bool  is64 = INSN(31,31) == 1;
      UInt  op   = INSN(30,29);
      UInt  N    = INSN(22,22);
      UInt  immR = INSN(21,16);
      UInt  immS = INSN(15,10);
      UInt  nn   = INSN(9,5);
      UInt  dd   = INSN(4,0);
      ULong imm  = 0;
      Bool  ok;
      if (N == 1 && !is64) 
         goto after_logic_imm; 
      ok = dbm_DecodeBitMasks(&imm, NULL,
                              N, immS, immR, True, is64 ? 64 : 32);
      if (!ok)
         goto after_logic_imm;

      const HChar* names[4] = { "and", "orr", "eor", "ands" };
      const IROp   ops64[4] = { Iop_And64, Iop_Or64, Iop_Xor64, Iop_And64 };
      const IROp   ops32[4] = { Iop_And32, Iop_Or32, Iop_Xor32, Iop_And32 };

      vassert(op < 4);
      if (is64) {
         IRExpr* argL = getIReg64orZR(nn);
         IRExpr* argR = mkU64(imm);
         IRTemp  res  = newTemp(Ity_I64);
         assign(res, binop(ops64[op], argL, argR));
         if (op < 3) {
            putIReg64orSP(dd, mkexpr(res));
            DIP("%s %s, %s, 0x%llx\n", names[op],
                nameIReg64orSP(dd), nameIReg64orZR(nn), imm);
         } else {
            putIReg64orZR(dd, mkexpr(res));
            setFlags_LOGIC(True, res);
            DIP("%s %s, %s, 0x%llx\n", names[op],
                nameIReg64orZR(dd), nameIReg64orZR(nn), imm);
         }
      } else {
         IRExpr* argL = getIReg32orZR(nn);
         IRExpr* argR = mkU32((UInt)imm);
         IRTemp  res  = newTemp(Ity_I32);
         assign(res, binop(ops32[op], argL, argR));
         if (op < 3) {
            putIReg32orSP(dd, mkexpr(res));
            DIP("%s %s, %s, 0x%x\n", names[op],
                nameIReg32orSP(dd), nameIReg32orZR(nn), (UInt)imm);
         } else {
            putIReg32orZR(dd, mkexpr(res));
            setFlags_LOGIC(False, res);
            DIP("%s %s, %s, 0x%x\n", names[op],
                nameIReg32orZR(dd), nameIReg32orZR(nn), (UInt)imm);
         }
      }
      return True;
   }
   after_logic_imm:

   
   if (INSN(28,23) == BITS6(1,0,0,1,0,1)) {
      Bool is64   = INSN(31,31) == 1;
      UInt subopc = INSN(30,29);
      UInt hw     = INSN(22,21);
      UInt imm16  = INSN(20,5);
      UInt dd     = INSN(4,0);
      if (subopc == BITS2(0,1) || (!is64 && hw >= 2)) {
         
      } else {
         ULong imm64 = ((ULong)imm16) << (16 * hw);
         if (!is64)
            vassert(imm64 < 0x100000000ULL);
         switch (subopc) {
            case BITS2(1,0): 
               putIRegOrZR(is64, dd, is64 ? mkU64(imm64) : mkU32((UInt)imm64));
               DIP("movz %s, 0x%llx\n", nameIRegOrZR(is64, dd), imm64);
               break;
            case BITS2(0,0): 
               imm64 = ~imm64;
               if (!is64)
                  imm64 &= 0xFFFFFFFFULL;
               putIRegOrZR(is64, dd, is64 ? mkU64(imm64) : mkU32((UInt)imm64));
               DIP("movn %s, 0x%llx\n", nameIRegOrZR(is64, dd), imm64);
               break;
            case BITS2(1,1): 
               if (is64) {
                  IRTemp old = newTemp(Ity_I64);
                  assign(old, getIReg64orZR(dd));
                  ULong mask = 0xFFFFULL << (16 * hw);
                  IRExpr* res
                     = binop(Iop_Or64, 
                             binop(Iop_And64, mkexpr(old), mkU64(~mask)),
                             mkU64(imm64));
                  putIReg64orZR(dd, res);
                  DIP("movk %s, 0x%x, lsl %u\n",
                      nameIReg64orZR(dd), imm16, 16*hw);
               } else {
                  IRTemp old = newTemp(Ity_I32);
                  assign(old, getIReg32orZR(dd));
                  vassert(hw <= 1);
                  UInt mask = 0xFFFF << (16 * hw);
                  IRExpr* res
                     = binop(Iop_Or32, 
                             binop(Iop_And32, mkexpr(old), mkU32(~mask)),
                             mkU32((UInt)imm64));
                  putIReg32orZR(dd, res);
                  DIP("movk %s, 0x%x, lsl %u\n",
                      nameIReg32orZR(dd), imm16, 16*hw);
               }
               break;
            default:
               vassert(0);
         }
         return True;
      }
   }

   
   if (INSN(28,23) == BITS6(1,0,0,1,1,0)) {
      UInt sf     = INSN(31,31);
      UInt opc    = INSN(30,29);
      UInt N      = INSN(22,22);
      UInt immR   = INSN(21,16);
      UInt immS   = INSN(15,10);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool inZero = False;
      Bool extend = False;
      const HChar* nm = "???";
      
      switch (opc) {
         case BITS2(0,0):
            inZero = True; extend = True; nm = "sbfm"; break;
         case BITS2(0,1):
            inZero = False; extend = False; nm = "bfm"; break;
         case BITS2(1,0):
            inZero = True; extend = False; nm = "ubfm"; break;
         case BITS2(1,1):
            goto after_bfm; 
         default:
            vassert(0);
      }
      if (sf == 1 && N != 1) goto after_bfm;
      if (sf == 0 && (N != 0 || ((immR >> 5) & 1) != 0
                             || ((immS >> 5) & 1) != 0)) goto after_bfm;
      ULong wmask = 0, tmask = 0;
      Bool ok = dbm_DecodeBitMasks(&wmask, &tmask,
                                   N, immS, immR, False, sf == 1 ? 64 : 32);
      if (!ok) goto after_bfm; 

      Bool   is64 = sf == 1;
      IRType ty   = is64 ? Ity_I64 : Ity_I32;

      IRTemp dst = newTemp(ty);
      IRTemp src = newTemp(ty);
      IRTemp bot = newTemp(ty);
      IRTemp top = newTemp(ty);
      IRTemp res = newTemp(ty);
      assign(dst, inZero ? mkU(ty,0) : getIRegOrZR(is64, dd));
      assign(src, getIRegOrZR(is64, nn));
      
      assign(bot, binop(mkOR(ty),
                        binop(mkAND(ty), mkexpr(dst), mkU(ty, ~wmask)),
                        binop(mkAND(ty), mkexpr(mathROR(ty, src, immR)),
                                         mkU(ty, wmask))));
      
      assign(top, mkexpr(extend ? mathREPLICATE(ty, src, immS) : dst));
      
      assign(res, binop(mkOR(ty),
                        binop(mkAND(ty), mkexpr(top), mkU(ty, ~tmask)),
                        binop(mkAND(ty), mkexpr(bot), mkU(ty, tmask))));
      putIRegOrZR(is64, dd, mkexpr(res));
      DIP("%s %s, %s, immR=%u, immS=%u\n",
          nm, nameIRegOrZR(is64, dd), nameIRegOrZR(is64, nn), immR, immS);
      return True;
   }
   after_bfm:

   
   if (INSN(30,23) == BITS8(0,0,1,0,0,1,1,1) && INSN(21,21) == 0) {
      Bool is64  = INSN(31,31) == 1;
      UInt mm    = INSN(20,16);
      UInt imm6  = INSN(15,10);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      Bool valid = True;
      if (INSN(31,31) != INSN(22,22))
        valid = False;
      if (!is64 && imm6 >= 32)
        valid = False;
      if (!valid) goto after_extr;
      IRType ty    = is64 ? Ity_I64 : Ity_I32;
      IRTemp srcHi = newTemp(ty);
      IRTemp srcLo = newTemp(ty);
      IRTemp res   = newTemp(ty);
      assign(srcHi, getIRegOrZR(is64, nn));
      assign(srcLo, getIRegOrZR(is64, mm));
      if (imm6 == 0) {
        assign(res, mkexpr(srcLo));
      } else {
        UInt szBits = 8 * sizeofIRType(ty);
        vassert(imm6 > 0 && imm6 < szBits);
        assign(res, binop(mkOR(ty),
                          binop(mkSHL(ty), mkexpr(srcHi), mkU8(szBits-imm6)),
                          binop(mkSHR(ty), mkexpr(srcLo), mkU8(imm6))));
      }
      putIRegOrZR(is64, dd, mkexpr(res));
      DIP("extr %s, %s, %s, #%u\n",
          nameIRegOrZR(is64,dd),
          nameIRegOrZR(is64,nn), nameIRegOrZR(is64,mm), imm6);
      return True;
   }
  after_extr:

   vex_printf("ARM64 front end: data_processing_immediate\n");
   return False;
#  undef INSN
}



static const HChar* nameSH ( UInt sh ) {
   switch (sh) {
      case 0: return "lsl";
      case 1: return "lsr";
      case 2: return "asr";
      case 3: return "ror";
      default: vassert(0);
   }
}

static IRTemp getShiftedIRegOrZR ( Bool is64,
                                   UInt sh_how, UInt sh_amt, UInt regNo,
                                   Bool invert )
{
   vassert(sh_how < 4);
   vassert(sh_amt < (is64 ? 64 : 32));
   IRType ty = is64 ? Ity_I64 : Ity_I32;
   IRTemp t0 = newTemp(ty);
   assign(t0, getIRegOrZR(is64, regNo));
   IRTemp t1 = newTemp(ty);
   switch (sh_how) {
      case BITS2(0,0):
         assign(t1, binop(mkSHL(ty), mkexpr(t0), mkU8(sh_amt)));
         break;
      case BITS2(0,1):
         assign(t1, binop(mkSHR(ty), mkexpr(t0), mkU8(sh_amt)));
         break;
      case BITS2(1,0):
         assign(t1, binop(mkSAR(ty), mkexpr(t0), mkU8(sh_amt)));
         break;
      case BITS2(1,1):
         assign(t1, mkexpr(mathROR(ty, t0, sh_amt)));
         break;
      default:
         vassert(0);
   }
   if (invert) {
      IRTemp t2 = newTemp(ty);
      assign(t2, unop(mkNOT(ty), mkexpr(t1)));
      return t2;
   } else {
      return t1;
   }
}


static
Bool dis_ARM64_data_processing_register(DisResult* dres,
                                        UInt insn)
{
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))

   
   if (INSN(28,24) == BITS5(0,1,0,1,1) && INSN(21,21) == 0) {
      UInt   bX    = INSN(31,31);
      UInt   bOP   = INSN(30,30); 
      UInt   bS    = INSN(29, 29); 
      UInt   sh    = INSN(23,22);
      UInt   rM    = INSN(20,16);
      UInt   imm6  = INSN(15,10);
      UInt   rN    = INSN(9,5);
      UInt   rD    = INSN(4,0);
      Bool   isSUB = bOP == 1;
      Bool   is64  = bX == 1;
      IRType ty    = is64 ? Ity_I64 : Ity_I32;
      if ((!is64 && imm6 > 31) || sh == BITS2(1,1)) {
         
      } else {
         IRTemp argL = newTemp(ty);
         assign(argL, getIRegOrZR(is64, rN));
         IRTemp argR = getShiftedIRegOrZR(is64, sh, imm6, rM, False);
         IROp   op   = isSUB ? mkSUB(ty) : mkADD(ty);
         IRTemp res  = newTemp(ty);
         assign(res, binop(op, mkexpr(argL), mkexpr(argR)));
         if (rD != 31) putIRegOrZR(is64, rD, mkexpr(res));
         if (bS) {
            setFlags_ADD_SUB(is64, isSUB, argL, argR);
         }
         DIP("%s%s %s, %s, %s, %s #%u\n",
             bOP ? "sub" : "add", bS ? "s" : "",
             nameIRegOrZR(is64, rD), nameIRegOrZR(is64, rN),
             nameIRegOrZR(is64, rM), nameSH(sh), imm6);
         return True;
      }
   }

   

   if (INSN(28,21) == BITS8(1,1,0,1,0,0,0,0) && INSN(15,10) == 0 ) {
      UInt   bX    = INSN(31,31);
      UInt   bOP   = INSN(30,30); 
      UInt   bS    = INSN(29,29); 
      UInt   rM    = INSN(20,16);
      UInt   rN    = INSN(9,5);
      UInt   rD    = INSN(4,0);

      Bool   isSUB = bOP == 1;
      Bool   is64  = bX == 1;
      IRType ty    = is64 ? Ity_I64 : Ity_I32;

      IRTemp oldC = newTemp(ty);
      assign(oldC,
             is64 ? mk_arm64g_calculate_flag_c()
                  : unop(Iop_64to32, mk_arm64g_calculate_flag_c()) );

      IRTemp argL = newTemp(ty);
      assign(argL, getIRegOrZR(is64, rN));
      IRTemp argR = newTemp(ty);
      assign(argR, getIRegOrZR(is64, rM));

      IROp   op   = isSUB ? mkSUB(ty) : mkADD(ty);
      IRTemp res  = newTemp(ty);
      if (isSUB) {
         IRExpr* one = is64 ? mkU64(1) : mkU32(1);
         IROp xorOp = is64 ? Iop_Xor64 : Iop_Xor32;
         assign(res,
                binop(op,
                      binop(op, mkexpr(argL), mkexpr(argR)),
                      binop(xorOp, mkexpr(oldC), one)));
      } else {
         assign(res,
                binop(op,
                      binop(op, mkexpr(argL), mkexpr(argR)),
                      mkexpr(oldC)));
      }

      if (rD != 31) putIRegOrZR(is64, rD, mkexpr(res));

      if (bS) {
         setFlags_ADC_SBC(is64, isSUB, argL, argR, oldC);
      }

      DIP("%s%s %s, %s, %s\n",
          bOP ? "sbc" : "adc", bS ? "s" : "",
          nameIRegOrZR(is64, rD), nameIRegOrZR(is64, rN),
          nameIRegOrZR(is64, rM));
      return True;
   }



      
   if (INSN(28,24) == BITS5(0,1,0,1,0)) {
      UInt   bX   = INSN(31,31);
      UInt   sh   = INSN(23,22);
      UInt   bN   = INSN(21,21);
      UInt   rM   = INSN(20,16);
      UInt   imm6 = INSN(15,10);
      UInt   rN   = INSN(9,5);
      UInt   rD   = INSN(4,0);
      Bool   is64 = bX == 1;
      IRType ty   = is64 ? Ity_I64 : Ity_I32;
      if (!is64 && imm6 > 31) {
         
      } else {
         IRTemp argL = newTemp(ty);
         assign(argL, getIRegOrZR(is64, rN));
         IRTemp argR = getShiftedIRegOrZR(is64, sh, imm6, rM, bN == 1);
         IROp   op   = Iop_INVALID;
         switch (INSN(30,29)) {
            case BITS2(0,0): case BITS2(1,1): op = mkAND(ty); break;
            case BITS2(0,1):                  op = mkOR(ty);  break;
            case BITS2(1,0):                  op = mkXOR(ty); break;
            default: vassert(0);
         }
         IRTemp res = newTemp(ty);
         assign(res, binop(op, mkexpr(argL), mkexpr(argR)));
         if (INSN(30,29) == BITS2(1,1)) {
            setFlags_LOGIC(is64, res);
         }
         putIRegOrZR(is64, rD, mkexpr(res));

         static const HChar* names_op[8]
            = { "and", "orr", "eor", "ands", "bic", "orn", "eon", "bics" };
         vassert(((bN << 2) | INSN(30,29)) < 8);
         const HChar* nm_op = names_op[(bN << 2) | INSN(30,29)];
         
         if (rN == 31 && sh == 0 && imm6 == 0 && bN == 0) {
            DIP("mov %s, %s\n", nameIRegOrZR(is64, rD),
                                nameIRegOrZR(is64, rM));
         } else {
            DIP("%s %s, %s, %s, %s #%u\n", nm_op,
                nameIRegOrZR(is64, rD), nameIRegOrZR(is64, rN),
                nameIRegOrZR(is64, rM), nameSH(sh), imm6);
         }
         return True;
      }
   }

      
   if (INSN(31,24) == BITS8(1,0,0,1,1,0,1,1)
       && INSN(22,21) == BITS2(1,0) && INSN(15,10) == BITS6(0,1,1,1,1,1)) {
      Bool isU = INSN(23,23) == 1;
      UInt mm  = INSN(20,16);
      UInt nn  = INSN(9,5);
      UInt dd  = INSN(4,0);
      putIReg64orZR(dd, unop(Iop_128HIto64,
                             binop(isU ? Iop_MullU64 : Iop_MullS64,
                                   getIReg64orZR(nn), getIReg64orZR(mm))));
      DIP("%cmulh %s, %s, %s\n", 
          isU ? 'u' : 's',
          nameIReg64orZR(dd), nameIReg64orZR(nn), nameIReg64orZR(mm));
      return True;
   }

      
   if (INSN(30,21) == BITS10(0,0,1,1,0,1,1,0,0,0)) {
      Bool is64  = INSN(31,31) == 1;
      UInt mm    = INSN(20,16);
      Bool isAdd = INSN(15,15) == 0;
      UInt aa    = INSN(14,10);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      if (is64) {
         putIReg64orZR(
            dd,
            binop(isAdd ? Iop_Add64 : Iop_Sub64,
                  getIReg64orZR(aa),
                  binop(Iop_Mul64, getIReg64orZR(mm), getIReg64orZR(nn))));
      } else {
         putIReg32orZR(
            dd,
            binop(isAdd ? Iop_Add32 : Iop_Sub32,
                  getIReg32orZR(aa),
                  binop(Iop_Mul32, getIReg32orZR(mm), getIReg32orZR(nn))));
      }
      DIP("%s %s, %s, %s, %s\n",
          isAdd ? "madd" : "msub",
          nameIRegOrZR(is64, dd), nameIRegOrZR(is64, nn),
          nameIRegOrZR(is64, mm), nameIRegOrZR(is64, aa));
      return True;
   }

      
   if (INSN(29,21) == BITS9(0, 1,1,0,1, 0,1,0,0) && INSN(11,11) == 0) {
      Bool    is64 = INSN(31,31) == 1;
      UInt    b30  = INSN(30,30);
      UInt    mm   = INSN(20,16);
      UInt    cond = INSN(15,12);
      UInt    b10  = INSN(10,10);
      UInt    nn   = INSN(9,5);
      UInt    dd   = INSN(4,0);
      UInt    op   = (b30 << 1) | b10; 
      IRType  ty   = is64 ? Ity_I64 : Ity_I32;
      IRExpr* argL = getIRegOrZR(is64, nn);
      IRExpr* argR = getIRegOrZR(is64, mm);
      switch (op) {
         case BITS2(0,0):
            break;
         case BITS2(0,1):
            argR = binop(mkADD(ty), argR, mkU(ty,1));
            break;
         case BITS2(1,0):
            argR = unop(mkNOT(ty), argR);
            break;
         case BITS2(1,1):
            argR = binop(mkSUB(ty), mkU(ty,0), argR);
            break;
         default:
            vassert(0);
      }
      putIRegOrZR(
         is64, dd,
         IRExpr_ITE(unop(Iop_64to1, mk_arm64g_calculate_condition(cond)),
                    argL, argR)
      );
      const HChar* op_nm[4] = { "csel", "csinc", "csinv", "csneg" };
      DIP("%s %s, %s, %s, %s\n", op_nm[op],
          nameIRegOrZR(is64, dd), nameIRegOrZR(is64, nn),
          nameIRegOrZR(is64, mm), nameCC(cond));
      return True;
   }

      
   if (INSN(28,21) == BITS8(0,1,0,1,1,0,0,1) && INSN(12,10) <= 4) {
      Bool is64  = INSN(31,31) == 1;
      Bool isSub = INSN(30,30) == 1;
      Bool setCC = INSN(29,29) == 1;
      UInt mm    = INSN(20,16);
      UInt opt   = INSN(15,13);
      UInt imm3  = INSN(12,10);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      const HChar* nameExt[8] = { "uxtb", "uxth", "uxtw", "uxtx",
                                  "sxtb", "sxth", "sxtw", "sxtx" };
      
      IRTemp xN = newTemp(Ity_I64);
      IRTemp xM = newTemp(Ity_I64);
      assign(xN, getIReg64orSP(nn));
      assign(xM, getIReg64orZR(mm));
      IRExpr* xMw  = mkexpr(xM); 
      Int     shSX = 0;
      
      switch (opt) {
         case BITS3(0,0,0): 
            xMw = binop(Iop_And64, xMw, mkU64(0xFF)); break;
         case BITS3(0,0,1): 
            xMw = binop(Iop_And64, xMw, mkU64(0xFFFF)); break;
         case BITS3(0,1,0): 
            if (is64) {
               xMw = unop(Iop_32Uto64, unop(Iop_64to32, xMw));
            }
            break;
         case BITS3(0,1,1): 
            break;
         case BITS3(1,0,0): 
            shSX = 56; goto sxTo64;
         case BITS3(1,0,1): 
            shSX = 48; goto sxTo64;
         case BITS3(1,1,0): 
            if (is64) {
               shSX = 32; goto sxTo64;
            }
            break;
         case BITS3(1,1,1): 
            break;
         sxTo64:
            vassert(shSX >= 32);
            xMw = binop(Iop_Sar64, binop(Iop_Shl64, xMw, mkU8(shSX)),
                        mkU8(shSX));
            break;
         default:
            vassert(0);
      }
      
      IRTemp argL = xN;
      IRTemp argR = newTemp(Ity_I64);
      assign(argR, binop(Iop_Shl64, xMw, mkU8(imm3)));
      IRTemp res = newTemp(Ity_I64);
      assign(res, binop(isSub ? Iop_Sub64 : Iop_Add64,
                        mkexpr(argL), mkexpr(argR)));
      if (is64) {
         if (setCC) {
            putIReg64orZR(dd, mkexpr(res));
            setFlags_ADD_SUB(True, isSub, argL, argR);
         } else {
            putIReg64orSP(dd, mkexpr(res));
         }
      } else {
         if (setCC) {
            IRTemp argL32 = newTemp(Ity_I32);
            IRTemp argR32 = newTemp(Ity_I32);
            putIReg32orZR(dd, unop(Iop_64to32, mkexpr(res)));
            assign(argL32, unop(Iop_64to32, mkexpr(argL)));
            assign(argR32, unop(Iop_64to32, mkexpr(argR)));
            setFlags_ADD_SUB(False, isSub, argL32, argR32);
         } else {
            putIReg32orSP(dd, unop(Iop_64to32, mkexpr(res)));
         }
      }
      DIP("%s%s %s, %s, %s %s lsl %u\n",
          isSub ? "sub" : "add", setCC ? "s" : "",
          setCC ? nameIRegOrZR(is64, dd) : nameIRegOrSP(is64, dd),
          nameIRegOrSP(is64, nn), nameIRegOrSP(is64, mm),
          nameExt[opt], imm3);
      return True;
   }

   
   if (INSN(29,21) == BITS9(1,1,1,0,1,0,0,1,0)
       && INSN(11,10) == BITS2(1,0) && INSN(4,4) == 0) {
      Bool is64  = INSN(31,31) == 1;
      Bool isSUB = INSN(30,30) == 1;
      UInt imm5  = INSN(20,16);
      UInt cond  = INSN(15,12);
      UInt nn    = INSN(9,5);
      UInt nzcv  = INSN(3,0);

      IRTemp condT = newTemp(Ity_I1);
      assign(condT, unop(Iop_64to1, mk_arm64g_calculate_condition(cond)));

      IRType ty   = is64 ? Ity_I64 : Ity_I32;
      IRTemp argL = newTemp(ty);
      IRTemp argR = newTemp(ty);

      if (is64) {
         assign(argL, getIReg64orZR(nn));
         assign(argR, mkU64(imm5));
      } else {
         assign(argL, getIReg32orZR(nn));
         assign(argR, mkU32(imm5));
      }
      setFlags_ADD_SUB_conditionally(is64, isSUB, condT, argL, argR, nzcv);

      DIP("ccm%c %s, #%u, #%u, %s\n",
          isSUB ? 'p' : 'n', nameIRegOrZR(is64, nn),
          imm5, nzcv, nameCC(cond));
      return True;
   }

   
   if (INSN(29,21) == BITS9(1,1,1,0,1,0,0,1,0)
       && INSN(11,10) == BITS2(0,0) && INSN(4,4) == 0) {
      Bool is64  = INSN(31,31) == 1;
      Bool isSUB = INSN(30,30) == 1;
      UInt mm    = INSN(20,16);
      UInt cond  = INSN(15,12);
      UInt nn    = INSN(9,5);
      UInt nzcv  = INSN(3,0);

      IRTemp condT = newTemp(Ity_I1);
      assign(condT, unop(Iop_64to1, mk_arm64g_calculate_condition(cond)));

      IRType ty   = is64 ? Ity_I64 : Ity_I32;
      IRTemp argL = newTemp(ty);
      IRTemp argR = newTemp(ty);

      if (is64) {
         assign(argL, getIReg64orZR(nn));
         assign(argR, getIReg64orZR(mm));
      } else {
         assign(argL, getIReg32orZR(nn));
         assign(argR, getIReg32orZR(mm));
      }
      setFlags_ADD_SUB_conditionally(is64, isSUB, condT, argL, argR, nzcv);

      DIP("ccm%c %s, %s, #%u, %s\n",
          isSUB ? 'p' : 'n', nameIRegOrZR(is64, nn),
          nameIRegOrZR(is64, mm), nzcv, nameCC(cond));
      return True;
   }


      
   if (INSN(30,21) == BITS10(1,0,1,1,0,1,0,1,1,0)
       && INSN(20,12) == BITS9(0,0,0,0,0,0,0,0,0)) {
      UInt b31 = INSN(31,31);
      UInt opc = INSN(11,10);

      UInt ix = 0;
       if (b31 == 1 && opc == BITS2(1,1)) ix = 1; 
      else if (b31 == 0 && opc == BITS2(1,0)) ix = 2; 
      else if (b31 == 1 && opc == BITS2(0,0)) ix = 3; 
      else if (b31 == 0 && opc == BITS2(0,0)) ix = 4; 
      else if (b31 == 1 && opc == BITS2(0,1)) ix = 5; 
      else if (b31 == 0 && opc == BITS2(0,1)) ix = 6; 
      else if (b31 == 1 && opc == BITS2(1,0)) ix = 7; 
      if (ix >= 1 && ix <= 7) {
         Bool   is64  = ix == 1 || ix == 3 || ix == 5 || ix == 7;
         UInt   nn    = INSN(9,5);
         UInt   dd    = INSN(4,0);
         IRTemp src   = newTemp(Ity_I64);
         IRTemp dst   = IRTemp_INVALID;
         IRTemp (*math)(IRTemp) = NULL;
         switch (ix) {
            case 1: case 2: math = math_BYTESWAP64;   break;
            case 3: case 4: math = math_BITSWAP64;    break;
            case 5: case 6: math = math_USHORTSWAP64; break;
            case 7:         math = math_UINTSWAP64;   break;
            default: vassert(0);
         }
         const HChar* names[7]
           = { "rev", "rev", "rbit", "rbit", "rev16", "rev16", "rev32" };
         const HChar* nm = names[ix-1];
         vassert(math);
         if (ix == 6) {
            assign(src, getIReg64orZR(nn));
            dst = math(src);
            putIReg64orZR(dd,
                          unop(Iop_32Uto64, unop(Iop_64to32, mkexpr(dst))));
         } else if (is64) {
            assign(src, getIReg64orZR(nn));
            dst = math(src);
            putIReg64orZR(dd, mkexpr(dst));
         } else {
            assign(src, binop(Iop_Shl64, getIReg64orZR(nn), mkU8(32)));
            dst = math(src);
            putIReg32orZR(dd, unop(Iop_64to32, mkexpr(dst)));
         }
         DIP("%s %s, %s\n", nm,
             nameIRegOrZR(is64,dd), nameIRegOrZR(is64,nn));
         return True;
      }
      
   }

      
   if (INSN(30,21) == BITS10(1,0,1,1,0,1,0,1,1,0)
       && INSN(20,11) == BITS10(0,0,0,0,0,0,0,0,1,0)) {
      Bool   is64  = INSN(31,31) == 1;
      Bool   isCLS = INSN(10,10) == 1;
      UInt   nn    = INSN(9,5);
      UInt   dd    = INSN(4,0);
      IRTemp src   = newTemp(Ity_I64);
      IRTemp dst   = newTemp(Ity_I64);
      if (!isCLS) { 
         if (is64) {
            assign(src, getIReg64orZR(nn));
            assign(dst, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(src), mkU64(0)),
                                   mkU64(64),
                                   unop(Iop_Clz64, mkexpr(src))));
            putIReg64orZR(dd, mkexpr(dst));
         } else {
            assign(src, binop(Iop_Shl64,
                              unop(Iop_32Uto64, getIReg32orZR(nn)), mkU8(32)));
            assign(dst, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(src), mkU64(0)),
                                   mkU64(32),
                                   unop(Iop_Clz64, mkexpr(src))));
            putIReg32orZR(dd, unop(Iop_64to32, mkexpr(dst)));
         }
         DIP("cl%c %s, %s\n",
             isCLS ? 's' : 'z', nameIRegOrZR(is64, dd), nameIRegOrZR(is64, nn));
         return True;
      }
   }

      
   if (INSN(30,21) == BITS10(0,0,1,1,0,1,0,1,1,0)
       && INSN(15,12) == BITS4(0,0,1,0) && INSN(11,10) < BITS2(1,1)) {
      Bool   is64 = INSN(31,31) == 1;
      UInt   mm   = INSN(20,16);
      UInt   op   = INSN(11,10);
      UInt   nn   = INSN(9,5);
      UInt   dd   = INSN(4,0);
      IRType ty   = is64 ? Ity_I64 : Ity_I32;
      IRTemp srcL = newTemp(ty);
      IRTemp srcR = newTemp(Ity_I8);
      IRTemp res  = newTemp(ty);
      IROp   iop  = Iop_INVALID;
      assign(srcL, getIRegOrZR(is64, nn));
      assign(srcR,
             unop(Iop_64to8,
                  binop(Iop_And64,
                        getIReg64orZR(mm), mkU64(is64 ? 63 : 31))));
      switch (op) {
         case BITS2(0,0): iop = mkSHL(ty); break;
         case BITS2(0,1): iop = mkSHR(ty); break;
         case BITS2(1,0): iop = mkSAR(ty); break;
         default: vassert(0);
      }
      assign(res, binop(iop, mkexpr(srcL), mkexpr(srcR)));
      putIRegOrZR(is64, dd, mkexpr(res));
      vassert(op < 3);
      const HChar* names[3] = { "lslv", "lsrv", "asrv" };
      DIP("%s %s, %s, %s\n",
          names[op], nameIRegOrZR(is64,dd),
                     nameIRegOrZR(is64,nn), nameIRegOrZR(is64,mm));
      return True;
   }

      
   if (INSN(30,21) == BITS10(0,0,1,1,0,1,0,1,1,0)
       && INSN(15,11) == BITS5(0,0,0,0,1)) {
      Bool is64 = INSN(31,31) == 1;
      UInt mm   = INSN(20,16);
      Bool isS  = INSN(10,10) == 1;
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);
      if (isS) {
         putIRegOrZR(is64, dd, binop(is64 ? Iop_DivS64 : Iop_DivS32,
                                     getIRegOrZR(is64, nn),
                                     getIRegOrZR(is64, mm)));
      } else {
         putIRegOrZR(is64, dd, binop(is64 ? Iop_DivU64 : Iop_DivU32,
                                     getIRegOrZR(is64, nn),
                                     getIRegOrZR(is64, mm)));
      }
      DIP("%cdiv %s, %s, %s\n", isS ? 's' : 'u',
          nameIRegOrZR(is64, dd),
          nameIRegOrZR(is64, nn), nameIRegOrZR(is64, mm));
      return True;
   }

      
   if (INSN(31,24) == BITS8(1,0,0,1,1,0,1,1) && INSN(22,21) == BITS2(0,1)) {
      Bool   isU   = INSN(23,23) == 1;
      UInt   mm    = INSN(20,16);
      Bool   isAdd = INSN(15,15) == 0;
      UInt   aa    = INSN(14,10);
      UInt   nn    = INSN(9,5);
      UInt   dd    = INSN(4,0);
      IRTemp wN    = newTemp(Ity_I32);
      IRTemp wM    = newTemp(Ity_I32);
      IRTemp xA    = newTemp(Ity_I64);
      IRTemp muld  = newTemp(Ity_I64);
      IRTemp res   = newTemp(Ity_I64);
      assign(wN, getIReg32orZR(nn));
      assign(wM, getIReg32orZR(mm));
      assign(xA, getIReg64orZR(aa));
      assign(muld, binop(isU ? Iop_MullU32 : Iop_MullS32,
                         mkexpr(wN), mkexpr(wM)));
      assign(res, binop(isAdd ? Iop_Add64 : Iop_Sub64,
                        mkexpr(xA), mkexpr(muld)));
      putIReg64orZR(dd, mkexpr(res));
      DIP("%cm%sl %s, %s, %s, %s\n", isU ? 'u' : 's', isAdd ? "add" : "sub",
          nameIReg64orZR(dd), nameIReg32orZR(nn),
          nameIReg32orZR(mm), nameIReg64orZR(aa));
      return True;
   }
   vex_printf("ARM64 front end: data_processing_register\n");
   return False;
#  undef INSN
}



static IRTemp gen_indexed_EA ( HChar* buf, UInt insn, Bool isInt )
{
   UInt    optS  = SLICE_UInt(insn, 15, 12);
   UInt    mm    = SLICE_UInt(insn, 20, 16);
   UInt    nn    = SLICE_UInt(insn, 9, 5);
   UInt    szLg2 = (isInt ? 0 : (SLICE_UInt(insn, 23, 23) << 2))
                   | SLICE_UInt(insn, 31, 30); 

   buf[0] = 0;

   
   if (SLICE_UInt(insn, 11, 10) != BITS2(1,0))
      goto fail;

   if (isInt
       && SLICE_UInt(insn, 29, 21) != BITS9(1,1,1,0,0,0,0,1,1)
       && SLICE_UInt(insn, 29, 21) != BITS9(1,1,1,0,0,0,0,0,1)
       && SLICE_UInt(insn, 29, 21) != BITS9(1,1,1,0,0,0,1,0,1)
       && SLICE_UInt(insn, 29, 21) != BITS9(1,1,1,0,0,0,1,1,1))
      goto fail;

   if (!isInt
       && SLICE_UInt(insn, 29, 24) != BITS6(1,1,1,1,0,0)) 
      goto fail;

   
   switch (szLg2) {
      case BITS3(0,0,0): break; 
      case BITS3(0,0,1): break; 
      case BITS3(0,1,0): break; 
      case BITS3(0,1,1): break; 
      case BITS3(1,0,0): 
                         if (isInt) goto fail; else goto fail;
      case BITS3(1,0,1): 
      case BITS3(1,1,0):
      case BITS3(1,1,1): goto fail;

      default: vassert(0);
   }

   IRExpr* rhs  = NULL;
   switch (optS) {
      case BITS4(1,1,1,0): goto fail; 
      case BITS4(0,1,1,0):
         rhs = getIReg64orZR(mm);
         vex_sprintf(buf, "[%s, %s]",
                     nameIReg64orZR(nn), nameIReg64orZR(mm));
         break;
      case BITS4(1,1,1,1): goto fail; 
      case BITS4(0,1,1,1):
         rhs = binop(Iop_Shl64, getIReg64orZR(mm), mkU8(szLg2));
         vex_sprintf(buf, "[%s, %s lsl %u]",
                     nameIReg64orZR(nn), nameIReg64orZR(mm), szLg2);
         break;
      case BITS4(0,1,0,0):
         rhs = unop(Iop_32Uto64, getIReg32orZR(mm));
         vex_sprintf(buf, "[%s, %s uxtx]",
                     nameIReg64orZR(nn), nameIReg32orZR(mm));
         break;
      case BITS4(0,1,0,1):
         rhs = binop(Iop_Shl64,
                     unop(Iop_32Uto64, getIReg32orZR(mm)), mkU8(szLg2));
         vex_sprintf(buf, "[%s, %s uxtx, lsl %u]",
                     nameIReg64orZR(nn), nameIReg32orZR(mm), szLg2);
         break;
      case BITS4(1,1,0,0):
         rhs = unop(Iop_32Sto64, getIReg32orZR(mm));
         vex_sprintf(buf, "[%s, %s sxtx]",
                     nameIReg64orZR(nn), nameIReg32orZR(mm));
         break;
      case BITS4(1,1,0,1):
         rhs = binop(Iop_Shl64,
                     unop(Iop_32Sto64, getIReg32orZR(mm)), mkU8(szLg2));
         vex_sprintf(buf, "[%s, %s sxtx, lsl %u]",
                     nameIReg64orZR(nn), nameIReg32orZR(mm), szLg2);
         break;
      default:
         
         goto fail;
   }

   vassert(rhs);
   IRTemp res = newTemp(Ity_I64);
   assign(res, binop(Iop_Add64, getIReg64orSP(nn), rhs));
   return res;

  fail:
   vex_printf("gen_indexed_EA: unhandled case optS == 0x%x\n", optS);
   return IRTemp_INVALID;
}


static void gen_narrowing_store ( UInt szB, IRTemp addr, IRExpr* dataE )
{
   IRExpr* addrE = mkexpr(addr);
   switch (szB) {
      case 8:
         storeLE(addrE, dataE);
         break;
      case 4:
         storeLE(addrE, unop(Iop_64to32, dataE));
         break;
      case 2:
         storeLE(addrE, unop(Iop_64to16, dataE));
         break;
      case 1:
         storeLE(addrE, unop(Iop_64to8, dataE));
         break;
      default:
         vassert(0);
   }
}


static IRTemp gen_zwidening_load ( UInt szB, IRTemp addr )
{
   IRTemp  res   = newTemp(Ity_I64);
   IRExpr* addrE = mkexpr(addr);
   switch (szB) {
      case 8:
         assign(res, loadLE(Ity_I64,addrE));
         break;
      case 4:
         assign(res, unop(Iop_32Uto64, loadLE(Ity_I32,addrE)));
         break;
      case 2:
         assign(res, unop(Iop_16Uto64, loadLE(Ity_I16,addrE)));
         break;
      case 1:
         assign(res, unop(Iop_8Uto64, loadLE(Ity_I8,addrE)));
         break;
      default:
         vassert(0);
   }
   return res;
}


static
Bool dis_ARM64_load_store(DisResult* dres, UInt insn)
{
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,1,0)) {
      UInt   szLg2 = INSN(31,30);
      UInt   szB   = 1 << szLg2;
      Bool   isLD  = INSN(22,22) == 1;
      UInt   offs  = INSN(21,10) * szB;
      UInt   nn    = INSN(9,5);
      UInt   tt    = INSN(4,0);
      IRTemp ta    = newTemp(Ity_I64);
      assign(ta, binop(Iop_Add64, getIReg64orSP(nn), mkU64(offs)));
      if (nn == 31) {  }
      vassert(szLg2 < 4);
      if (isLD) {
         putIReg64orZR(tt, mkexpr(gen_zwidening_load(szB, ta)));
      } else {
         gen_narrowing_store(szB, ta, getIReg64orZR(tt));
      }
      const HChar* ld_name[4] = { "ldrb", "ldrh", "ldr", "ldr" };
      const HChar* st_name[4] = { "strb", "strh", "str", "str" };
      DIP("%s %s, [%s, #%u]\n", 
          (isLD ? ld_name : st_name)[szLg2], nameIRegOrZR(szB == 8, tt),
          nameIReg64orSP(nn), offs);
      return True;
   }

   
   if ((INSN(29,21) & BITS9(1,1,1, 1,1,1,1,0, 1))
       == BITS9(1,1,1, 0,0,0,0,0, 0)) {
      UInt szLg2  = INSN(31,30);
      UInt szB    = 1 << szLg2;
      Bool isLoad = INSN(22,22) == 1;
      UInt imm9   = INSN(20,12);
      UInt nn     = INSN(9,5);
      UInt tt     = INSN(4,0);
      Bool wBack  = INSN(10,10) == 1;
      UInt how    = INSN(11,10);
      if (how == BITS2(1,0) || (wBack && nn == tt && tt != 31)) {
         
      } else {
         if (nn == 31) {  }

         
         IRTemp tRN = newTemp(Ity_I64);
         assign(tRN, getIReg64orSP(nn));
         IRTemp tEA = newTemp(Ity_I64);
         Long simm9 = (Long)sx_to_64(imm9, 9);
         assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm9)));

         IRTemp tTA = newTemp(Ity_I64);
         IRTemp tWA = newTemp(Ity_I64);
         switch (how) {
            case BITS2(0,1):
               assign(tTA, mkexpr(tRN)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(1,1):
               assign(tTA, mkexpr(tEA)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(0,0):
               assign(tTA, mkexpr(tEA));  break;
            default:
               vassert(0); 
         }

         Bool earlyWBack
           = wBack && simm9 < 0 && szB == 8
             && how == BITS2(1,1) && nn == 31 && !isLoad && tt != nn;

         if (wBack && earlyWBack)
            putIReg64orSP(nn, mkexpr(tEA));

         if (isLoad) {
            putIReg64orZR(tt, mkexpr(gen_zwidening_load(szB, tTA)));
         } else {
            gen_narrowing_store(szB, tTA, getIReg64orZR(tt));
         }

         if (wBack && !earlyWBack)
            putIReg64orSP(nn, mkexpr(tEA));

         const HChar* ld_name[4] = { "ldurb", "ldurh", "ldur", "ldur" };
         const HChar* st_name[4] = { "sturb", "sturh", "stur", "stur" };
         const HChar* fmt_str = NULL;
         switch (how) {
            case BITS2(0,1):
               fmt_str = "%s %s, [%s], #%lld (at-Rn-then-Rn=EA)\n";
               break;
            case BITS2(1,1):
               fmt_str = "%s %s, [%s, #%lld]! (at-EA-then-Rn=EA)\n";
               break;
            case BITS2(0,0):
               fmt_str = "%s %s, [%s, #%lld] (at-Rn)\n";
               break;
            default:
               vassert(0);
         }
         DIP(fmt_str, (isLoad ? ld_name : st_name)[szLg2],
                      nameIRegOrZR(szB == 8, tt),
                      nameIReg64orSP(nn), simm9);
         return True;
      }
   }

   

   UInt insn_30_23 = INSN(30,23);
   if (insn_30_23 == BITS8(0,1,0,1,0,0,0,1) 
       || insn_30_23 == BITS8(0,1,0,1,0,0,1,1)
       || insn_30_23 == BITS8(0,1,0,1,0,0,1,0)) {
      UInt bL     = INSN(22,22);
      UInt bX     = INSN(31,31);
      UInt bWBack = INSN(23,23);
      UInt rT1    = INSN(4,0);
      UInt rN     = INSN(9,5);
      UInt rT2    = INSN(14,10);
      Long simm7  = (Long)sx_to_64(INSN(21,15), 7);
      if ((bWBack && (rT1 == rN || rT2 == rN) && rN != 31)
          || (bL && rT1 == rT2)) {
         
      } else {
         if (rN == 31) {  }

         
         IRTemp tRN = newTemp(Ity_I64);
         assign(tRN, getIReg64orSP(rN));
         IRTemp tEA = newTemp(Ity_I64);
         simm7 = (bX ? 8 : 4) * simm7;
         assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm7)));

         IRTemp tTA = newTemp(Ity_I64);
         IRTemp tWA = newTemp(Ity_I64);
         switch (INSN(24,23)) {
            case BITS2(0,1):
               assign(tTA, mkexpr(tRN)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(1,1):
               assign(tTA, mkexpr(tEA)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(1,0):
               assign(tTA, mkexpr(tEA));  break;
            default:
               vassert(0); 
         }

         Bool earlyWBack
           = bWBack && simm7 < 0
             && INSN(24,23) == BITS2(1,1) && rN == 31 && bL == 0;

         if (bWBack && earlyWBack)
            putIReg64orSP(rN, mkexpr(tEA));

          if (bL == 1 && bX == 1) {
            
            putIReg64orZR(rT1, loadLE(Ity_I64,
                                      binop(Iop_Add64,mkexpr(tTA),mkU64(0))));
            putIReg64orZR(rT2, loadLE(Ity_I64, 
                                      binop(Iop_Add64,mkexpr(tTA),mkU64(8))));
         } else if (bL == 1 && bX == 0) {
            
            putIReg32orZR(rT1, loadLE(Ity_I32,
                                      binop(Iop_Add64,mkexpr(tTA),mkU64(0))));
            putIReg32orZR(rT2, loadLE(Ity_I32, 
                                      binop(Iop_Add64,mkexpr(tTA),mkU64(4))));
         } else if (bL == 0 && bX == 1) {
            
            storeLE(binop(Iop_Add64,mkexpr(tTA),mkU64(0)),
                    getIReg64orZR(rT1));
            storeLE(binop(Iop_Add64,mkexpr(tTA),mkU64(8)),
                    getIReg64orZR(rT2));
         } else {
            vassert(bL == 0 && bX == 0);
            
            storeLE(binop(Iop_Add64,mkexpr(tTA),mkU64(0)),
                    getIReg32orZR(rT1));
            storeLE(binop(Iop_Add64,mkexpr(tTA),mkU64(4)),
                    getIReg32orZR(rT2));
         }

         if (bWBack && !earlyWBack)
            putIReg64orSP(rN, mkexpr(tEA));

         const HChar* fmt_str = NULL;
         switch (INSN(24,23)) {
            case BITS2(0,1):
               fmt_str = "%sp %s, %s, [%s], #%lld (at-Rn-then-Rn=EA)\n";
               break;
            case BITS2(1,1):
               fmt_str = "%sp %s, %s, [%s, #%lld]! (at-EA-then-Rn=EA)\n";
               break;
            case BITS2(1,0):
               fmt_str = "%sp %s, %s, [%s, #%lld] (at-Rn)\n";
               break;
            default:
               vassert(0);
         }
         DIP(fmt_str, bL == 0 ? "st" : "ld",
                      nameIRegOrZR(bX == 1, rT1),
                      nameIRegOrZR(bX == 1, rT2),
                      nameIReg64orSP(rN), simm7);
         return True;
      }
   }

   
   if (INSN(29,24) == BITS6(0,1,1,0,0,0) && INSN(31,31) == 0) {
      UInt  imm19 = INSN(23,5);
      UInt  rT    = INSN(4,0);
      UInt  bX    = INSN(30,30);
      ULong ea    = guest_PC_curr_instr + sx_to_64(imm19 << 2, 21);
      if (bX) {
         putIReg64orZR(rT, loadLE(Ity_I64, mkU64(ea)));
      } else {
         putIReg32orZR(rT, loadLE(Ity_I32, mkU64(ea)));
      }
      DIP("ldr %s, 0x%llx (literal)\n", nameIRegOrZR(bX == 1, rT), ea);
      return True;
   }

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,0,0)
       && INSN(21,21) == 1 && INSN(11,10) == BITS2(1,0)) {
      HChar  dis_buf[64];
      UInt   szLg2 = INSN(31,30);
      Bool   isLD  = INSN(22,22) == 1;
      UInt   tt    = INSN(4,0);
      IRTemp ea    = gen_indexed_EA(dis_buf, insn, True);
      if (ea != IRTemp_INVALID) {
         switch (szLg2) {
            case 3: 
               if (isLD) {
                  putIReg64orZR(tt, loadLE(Ity_I64, mkexpr(ea)));
                  DIP("ldr %s, %s\n", nameIReg64orZR(tt), dis_buf);
               } else {
                  storeLE(mkexpr(ea), getIReg64orZR(tt));
                  DIP("str %s, %s\n", nameIReg64orZR(tt), dis_buf);
               }
               break;
            case 2: 
               if (isLD) {
                  putIReg32orZR(tt, loadLE(Ity_I32, mkexpr(ea)));
                  DIP("ldr %s, %s\n", nameIReg32orZR(tt), dis_buf);
               } else {
                  storeLE(mkexpr(ea), getIReg32orZR(tt));
                  DIP("str %s, %s\n", nameIReg32orZR(tt), dis_buf);
               }
               break;
            case 1: 
               if (isLD) {
                  putIReg64orZR(tt, unop(Iop_16Uto64,
                                         loadLE(Ity_I16, mkexpr(ea))));
                  DIP("ldruh %s, %s\n", nameIReg32orZR(tt), dis_buf);
               } else {
                  storeLE(mkexpr(ea), unop(Iop_64to16, getIReg64orZR(tt)));
                  DIP("strh %s, %s\n", nameIReg32orZR(tt), dis_buf);
               }
               break;
            case 0: 
               if (isLD) {
                  putIReg64orZR(tt, unop(Iop_8Uto64,
                                         loadLE(Ity_I8, mkexpr(ea))));
                  DIP("ldrub %s, %s\n", nameIReg32orZR(tt), dis_buf);
               } else {
                  storeLE(mkexpr(ea), unop(Iop_64to8, getIReg64orZR(tt)));
                  DIP("strb %s, %s\n", nameIReg32orZR(tt), dis_buf);
               }
               break;
            default:
               vassert(0);
         }
         return True;
      }
   }

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,1,1)) {
      
      Bool valid = False;
      switch ((INSN(31,30) << 1) | INSN(22,22)) {
         case BITS3(1,0,0):
         case BITS3(0,1,0): case BITS3(0,1,1):
         case BITS3(0,0,0): case BITS3(0,0,1):
            valid = True;
            break;
      }
      if (valid) {
         UInt    szLg2 = INSN(31,30);
         UInt    bitX  = INSN(22,22);
         UInt    imm12 = INSN(21,10);
         UInt    nn    = INSN(9,5);
         UInt    tt    = INSN(4,0);
         UInt    szB   = 1 << szLg2;
         IRExpr* ea    = binop(Iop_Add64,
                               getIReg64orSP(nn), mkU64(imm12 * szB));
         switch (szB) {
            case 4:
               vassert(bitX == 0);
               putIReg64orZR(tt, unop(Iop_32Sto64, loadLE(Ity_I32, ea)));
               DIP("ldrsw %s, [%s, #%u]\n", nameIReg64orZR(tt),
                   nameIReg64orSP(nn), imm12 * szB);
               break;
            case 2:
               if (bitX == 1) {
                  putIReg32orZR(tt, unop(Iop_16Sto32, loadLE(Ity_I16, ea)));
               } else {
                  putIReg64orZR(tt, unop(Iop_16Sto64, loadLE(Ity_I16, ea)));
               }
               DIP("ldrsh %s, [%s, #%u]\n",
                   nameIRegOrZR(bitX == 0, tt),
                   nameIReg64orSP(nn), imm12 * szB);
               break;
            case 1:
               if (bitX == 1) {
                  putIReg32orZR(tt, unop(Iop_8Sto32, loadLE(Ity_I8, ea)));
               } else {
                  putIReg64orZR(tt, unop(Iop_8Sto64, loadLE(Ity_I8, ea)));
               }
               DIP("ldrsb %s, [%s, #%u]\n",
                   nameIRegOrZR(bitX == 0, tt),
                   nameIReg64orSP(nn), imm12 * szB);
               break;
            default:
               vassert(0);
         }
         return True;
      }
      
   }

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,0,1)
       && INSN(21,21) == 0 && INSN(10,10) == 1) {
      
      Bool valid = False;
      switch ((INSN(31,30) << 1) | INSN(22,22)) {
         case BITS3(1,0,0):                    
         case BITS3(0,1,0): case BITS3(0,1,1): 
         case BITS3(0,0,0): case BITS3(0,0,1): 
            valid = True;
            break;
      }
      if (valid) {
         UInt   szLg2 = INSN(31,30);
         UInt   imm9  = INSN(20,12);
         Bool   atRN  = INSN(11,11) == 0;
         UInt   nn    = INSN(9,5);
         UInt   tt    = INSN(4,0);
         IRTemp tRN   = newTemp(Ity_I64);
         IRTemp tEA   = newTemp(Ity_I64);
         IRTemp tTA   = IRTemp_INVALID;
         ULong  simm9 = sx_to_64(imm9, 9);
         Bool   is64  = INSN(22,22) == 0;
         assign(tRN, getIReg64orSP(nn));
         assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm9)));
         tTA = atRN ? tRN : tEA;
         HChar ch = '?';
         if (szLg2 == 0) {
            ch = 'b';
            if (is64) {
               putIReg64orZR(tt, unop(Iop_8Sto64,
                                      loadLE(Ity_I8, mkexpr(tTA))));
            } else {
               putIReg32orZR(tt, unop(Iop_8Sto32,
                                      loadLE(Ity_I8, mkexpr(tTA))));
            }
         }
         else if (szLg2 == 1) {
            ch = 'h';
            if (is64) {
               putIReg64orZR(tt, unop(Iop_16Sto64,
                                      loadLE(Ity_I16, mkexpr(tTA))));
            } else {
               putIReg32orZR(tt, unop(Iop_16Sto32,
                                      loadLE(Ity_I16, mkexpr(tTA))));
            }
         }
         else if (szLg2 == 2 && is64) {
            ch = 'w';
            putIReg64orZR(tt, unop(Iop_32Sto64,
                                   loadLE(Ity_I32, mkexpr(tTA))));
         }
         else {
            vassert(0);
         }
         putIReg64orSP(nn, mkexpr(tEA));
         DIP(atRN ? "ldrs%c %s, [%s], #%lld\n" : "ldrs%c %s, [%s, #%lld]!",
             ch, nameIRegOrZR(is64, tt), nameIReg64orSP(nn), simm9);
         return True;
      }
      
   }

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,0,1)
       && INSN(21,21) == 0 && INSN(11,10) == BITS2(0,0)) {
      
      Bool valid = False;
      switch ((INSN(31,30) << 1) | INSN(22,22)) {
         case BITS3(1,0,0):                    
         case BITS3(0,1,0): case BITS3(0,1,1): 
         case BITS3(0,0,0): case BITS3(0,0,1): 
            valid = True;
            break;
      }
      if (valid) {
         UInt   szLg2 = INSN(31,30);
         UInt   imm9  = INSN(20,12);
         UInt   nn    = INSN(9,5);
         UInt   tt    = INSN(4,0);
         IRTemp tRN   = newTemp(Ity_I64);
         IRTemp tEA   = newTemp(Ity_I64);
         ULong  simm9 = sx_to_64(imm9, 9);
         Bool   is64  = INSN(22,22) == 0;
         assign(tRN, getIReg64orSP(nn));
         assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm9)));
         HChar ch = '?';
         if (szLg2 == 0) {
            ch = 'b';
            if (is64) {
               putIReg64orZR(tt, unop(Iop_8Sto64,
                                      loadLE(Ity_I8, mkexpr(tEA))));
            } else {
               putIReg32orZR(tt, unop(Iop_8Sto32,
                                      loadLE(Ity_I8, mkexpr(tEA))));
            }
         }
         else if (szLg2 == 1) {
            ch = 'h';
            if (is64) {
               putIReg64orZR(tt, unop(Iop_16Sto64,
                                      loadLE(Ity_I16, mkexpr(tEA))));
            } else {
               putIReg32orZR(tt, unop(Iop_16Sto32,
                                      loadLE(Ity_I16, mkexpr(tEA))));
            }
         }
         else if (szLg2 == 2 && is64) {
            ch = 'w';
            putIReg64orZR(tt, unop(Iop_32Sto64,
                                   loadLE(Ity_I32, mkexpr(tEA))));
         }
         else {
            vassert(0);
         }
         DIP("ldurs%c %s, [%s, #%lld]",
             ch, nameIRegOrZR(is64, tt), nameIReg64orSP(nn), simm9);
         return True;
      }
      
   }

   

   UInt insn_29_23 = INSN(29,23);
   if (insn_29_23 == BITS7(1,0,1,1,0,0,1) 
       || insn_29_23 == BITS7(1,0,1,1,0,1,1)
       || insn_29_23 == BITS7(1,0,1,1,0,1,0)) {
      UInt szSlg2 = INSN(31,30); 
      Bool isLD   = INSN(22,22) == 1;
      Bool wBack  = INSN(23,23) == 1;
      Long simm7  = (Long)sx_to_64(INSN(21,15), 7);
      UInt tt2    = INSN(14,10);
      UInt nn     = INSN(9,5);
      UInt tt1    = INSN(4,0);
      if (szSlg2 == BITS2(1,1) || (isLD && tt1 == tt2)) {
         
      } else {
         if (nn == 31) {  }

         
         UInt   szB = 4 << szSlg2; 
         IRTemp tRN = newTemp(Ity_I64);
         assign(tRN, getIReg64orSP(nn));
         IRTemp tEA = newTemp(Ity_I64);
         simm7 = szB * simm7;
         assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm7)));

         IRTemp tTA = newTemp(Ity_I64);
         IRTemp tWA = newTemp(Ity_I64);
         switch (INSN(24,23)) {
            case BITS2(0,1):
               assign(tTA, mkexpr(tRN)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(1,1):
               assign(tTA, mkexpr(tEA)); assign(tWA, mkexpr(tEA)); break;
            case BITS2(1,0):
               assign(tTA, mkexpr(tEA));  break;
            default:
               vassert(0); 
         }

         IRType ty = Ity_INVALID;
         switch (szB) {
            case 4:  ty = Ity_F32;  break;
            case 8:  ty = Ity_F64;  break;
            case 16: ty = Ity_V128; break;
            default: vassert(0);
         }

         Bool earlyWBack
           = wBack && simm7 < 0
             && INSN(24,23) == BITS2(1,1) && nn == 31 && !isLD;

         if (wBack && earlyWBack)
            putIReg64orSP(nn, mkexpr(tEA));

         if (isLD) {
            if (szB < 16) {
               putQReg128(tt1, mkV128(0x0000));
            }
            putQRegLO(tt1,
                      loadLE(ty, binop(Iop_Add64, mkexpr(tTA), mkU64(0))));
            if (szB < 16) {
               putQReg128(tt2, mkV128(0x0000));
            }
            putQRegLO(tt2,
                      loadLE(ty, binop(Iop_Add64, mkexpr(tTA), mkU64(szB))));
         } else {
            storeLE(binop(Iop_Add64, mkexpr(tTA), mkU64(0)),
                    getQRegLO(tt1, ty));
            storeLE(binop(Iop_Add64, mkexpr(tTA), mkU64(szB)),
                    getQRegLO(tt2, ty));
         }

         if (wBack && !earlyWBack)
            putIReg64orSP(nn, mkexpr(tEA));

         const HChar* fmt_str = NULL;
         switch (INSN(24,23)) {
            case BITS2(0,1):
               fmt_str = "%sp %s, %s, [%s], #%lld (at-Rn-then-Rn=EA)\n";
               break;
            case BITS2(1,1):
               fmt_str = "%sp %s, %s, [%s, #%lld]! (at-EA-then-Rn=EA)\n";
               break;
            case BITS2(1,0):
               fmt_str = "%sp %s, %s, [%s, #%lld] (at-Rn)\n";
               break;
            default:
               vassert(0);
         }
         DIP(fmt_str, isLD ? "ld" : "st",
                      nameQRegLO(tt1, ty), nameQRegLO(tt2, ty),
                      nameIReg64orSP(nn), simm7);
         return True;
      }
   }

   
   if (INSN(29,24) == BITS6(1,1,1,1,0,0)
       && INSN(21,21) == 1 && INSN(11,10) == BITS2(1,0)) {
      HChar  dis_buf[64];
      UInt   szLg2 = (INSN(23,23) << 2) | INSN(31,30);
      Bool   isLD  = INSN(22,22) == 1;
      UInt   tt    = INSN(4,0);
      if (szLg2 >= 4) goto after_LDR_STR_vector_register;
      IRTemp ea    = gen_indexed_EA(dis_buf, insn, False);
      if (ea == IRTemp_INVALID) goto after_LDR_STR_vector_register;
      switch (szLg2) {
         case 0: 
            if (isLD) {
               putQReg128(tt, mkV128(0x0000));
               putQRegLO(tt, loadLE(Ity_I8, mkexpr(ea)));
               DIP("ldr %s, %s\n", nameQRegLO(tt, Ity_I8), dis_buf);
            } else {
               vassert(0); 
               storeLE(mkexpr(ea), getQRegLO(tt, Ity_I8));
               DIP("str %s, %s\n", nameQRegLO(tt, Ity_I8), dis_buf);
            }
            break;
         case 1:
            if (isLD) {
               putQReg128(tt, mkV128(0x0000));
               putQRegLO(tt, loadLE(Ity_I16, mkexpr(ea)));
               DIP("ldr %s, %s\n", nameQRegLO(tt, Ity_I16), dis_buf);
            } else {
               vassert(0); 
               storeLE(mkexpr(ea), getQRegLO(tt, Ity_I16));
               DIP("str %s, %s\n", nameQRegLO(tt, Ity_I16), dis_buf);
            }
            break;
         case 2: 
            if (isLD) {
               putQReg128(tt, mkV128(0x0000));
               putQRegLO(tt, loadLE(Ity_I32, mkexpr(ea)));
               DIP("ldr %s, %s\n", nameQRegLO(tt, Ity_I32), dis_buf);
            } else {
               storeLE(mkexpr(ea), getQRegLO(tt, Ity_I32));
               DIP("str %s, %s\n", nameQRegLO(tt, Ity_I32), dis_buf);
            }
            break;
         case 3: 
            if (isLD) {
               putQReg128(tt, mkV128(0x0000));
               putQRegLO(tt, loadLE(Ity_I64, mkexpr(ea)));
               DIP("ldr %s, %s\n", nameQRegLO(tt, Ity_I64), dis_buf);
            } else {
               storeLE(mkexpr(ea), getQRegLO(tt, Ity_I64));
               DIP("str %s, %s\n", nameQRegLO(tt, Ity_I64), dis_buf);
            }
            break;
         case 4:  return False; 
         default: vassert(0);
      }
      return True;
   }
  after_LDR_STR_vector_register:

   
   if (INSN(29,23) == BITS7(1,1,1,0,0,0,1)
       && INSN(21,21) == 1 && INSN(11,10) == BITS2(1,0)) {
      HChar  dis_buf[64];
      UInt   szLg2  = INSN(31,30);
      Bool   sxTo64 = INSN(22,22) == 0; 
      UInt   tt     = INSN(4,0);
      if (szLg2 == 3) goto after_LDRS_integer_register;
      IRTemp ea     = gen_indexed_EA(dis_buf, insn, True);
      if (ea == IRTemp_INVALID) goto after_LDRS_integer_register;
      
      if (szLg2 == 2 && sxTo64) {
         putIReg64orZR(tt, unop(Iop_32Sto64, loadLE(Ity_I32, mkexpr(ea))));
         DIP("ldrsw %s, %s\n", nameIReg64orZR(tt), dis_buf);
         return True;
      }
      else
      if (szLg2 == 1) {
         if (sxTo64) {
            putIReg64orZR(tt, unop(Iop_16Sto64, loadLE(Ity_I16, mkexpr(ea))));
            DIP("ldrsh %s, %s\n", nameIReg64orZR(tt), dis_buf);
         } else {
            putIReg32orZR(tt, unop(Iop_16Sto32, loadLE(Ity_I16, mkexpr(ea))));
            DIP("ldrsh %s, %s\n", nameIReg32orZR(tt), dis_buf);
         }
         return True;
      }
      else
      if (szLg2 == 0) {
         if (sxTo64) {
            putIReg64orZR(tt, unop(Iop_8Sto64, loadLE(Ity_I8, mkexpr(ea))));
            DIP("ldrsb %s, %s\n", nameIReg64orZR(tt), dis_buf);
         } else {
            putIReg32orZR(tt, unop(Iop_8Sto32, loadLE(Ity_I8, mkexpr(ea))));
            DIP("ldrsb %s, %s\n", nameIReg32orZR(tt), dis_buf);
         }
         return True;
      }
      
   }
  after_LDRS_integer_register:

   
   if (INSN(29,24) == BITS6(1,1,1,1,0,1)
       && ((INSN(23,23) << 2) | INSN(31,30)) <= 4) {
      UInt   szLg2  = (INSN(23,23) << 2) | INSN(31,30);
      Bool   isLD   = INSN(22,22) == 1;
      UInt   pimm12 = INSN(21,10) << szLg2;
      UInt   nn     = INSN(9,5);
      UInt   tt     = INSN(4,0);
      IRTemp tEA    = newTemp(Ity_I64);
      IRType ty     = preferredVectorSubTypeFromSize(1 << szLg2);
      assign(tEA, binop(Iop_Add64, getIReg64orSP(nn), mkU64(pimm12)));
      if (isLD) {
         if (szLg2 < 4) {
            putQReg128(tt, mkV128(0x0000));
         }
         putQRegLO(tt, loadLE(ty, mkexpr(tEA)));
      } else {
         storeLE(mkexpr(tEA), getQRegLO(tt, ty));
      }
      DIP("%s %s, [%s, #%u]\n",
          isLD ? "ldr" : "str",
          nameQRegLO(tt, ty), nameIReg64orSP(nn), pimm12);
      return True;
   }

   
   if (INSN(29,24) == BITS6(1,1,1,1,0,0)
       && ((INSN(23,23) << 2) | INSN(31,30)) <= 4
       && INSN(21,21) == 0 && INSN(10,10) == 1) {
      UInt   szLg2  = (INSN(23,23) << 2) | INSN(31,30);
      Bool   isLD   = INSN(22,22) == 1;
      UInt   imm9   = INSN(20,12);
      Bool   atRN   = INSN(11,11) == 0;
      UInt   nn     = INSN(9,5);
      UInt   tt     = INSN(4,0);
      IRTemp tRN    = newTemp(Ity_I64);
      IRTemp tEA    = newTemp(Ity_I64);
      IRTemp tTA    = IRTemp_INVALID;
      IRType ty     = preferredVectorSubTypeFromSize(1 << szLg2);
      ULong  simm9  = sx_to_64(imm9, 9);
      assign(tRN, getIReg64orSP(nn));
      assign(tEA, binop(Iop_Add64, mkexpr(tRN), mkU64(simm9)));
      tTA = atRN ? tRN : tEA;
      if (isLD) {
         if (szLg2 < 4) {
            putQReg128(tt, mkV128(0x0000));
         }
         putQRegLO(tt, loadLE(ty, mkexpr(tTA)));
      } else {
         storeLE(mkexpr(tTA), getQRegLO(tt, ty));
      }
      putIReg64orSP(nn, mkexpr(tEA));
      DIP(atRN ? "%s %s, [%s], #%lld\n" : "%s %s, [%s, #%lld]!\n",
          isLD ? "ldr" : "str",
          nameQRegLO(tt, ty), nameIReg64orSP(nn), simm9);
      return True;
   }

   
   if (INSN(29,24) == BITS6(1,1,1,1,0,0)
       && ((INSN(23,23) << 2) | INSN(31,30)) <= 4
       && INSN(21,21) == 0 && INSN(11,10) == BITS2(0,0)) {
      UInt   szLg2  = (INSN(23,23) << 2) | INSN(31,30);
      Bool   isLD   = INSN(22,22) == 1;
      UInt   imm9   = INSN(20,12);
      UInt   nn     = INSN(9,5);
      UInt   tt     = INSN(4,0);
      ULong  simm9  = sx_to_64(imm9, 9);
      IRTemp tEA    = newTemp(Ity_I64);
      IRType ty     = preferredVectorSubTypeFromSize(1 << szLg2);
      assign(tEA, binop(Iop_Add64, getIReg64orSP(nn), mkU64(simm9)));
      if (isLD) {
         if (szLg2 < 4) {
            putQReg128(tt, mkV128(0x0000));
         }
         putQRegLO(tt, loadLE(ty, mkexpr(tEA)));
      } else {
         storeLE(mkexpr(tEA), getQRegLO(tt, ty));
      }
      DIP("%s %s, [%s, #%lld]\n",
          isLD ? "ldur" : "stur",
          nameQRegLO(tt, ty), nameIReg64orSP(nn), (Long)simm9);
      return True;
   }

   
   if (INSN(29,24) == BITS6(0,1,1,1,0,0) && INSN(31,30) < BITS2(1,1)) {
      UInt   szB   = 4 << INSN(31,30);
      UInt   imm19 = INSN(23,5);
      UInt   tt    = INSN(4,0);
      ULong  ea    = guest_PC_curr_instr + sx_to_64(imm19 << 2, 21);
      IRType ty    = preferredVectorSubTypeFromSize(szB);
      putQReg128(tt, mkV128(0x0000));
      putQRegLO(tt, loadLE(ty, mkU64(ea)));
      DIP("ldr %s, 0x%llx (literal)\n", nameQRegLO(tt, ty), ea);
      return True;
   }

   

   if ((insn & 0xBFBF2000) == 0x0D000000) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      UInt   q    = INSN(30, 30);
      UInt   xx   = INSN(15, 14);
      UInt   opcode = INSN(15, 13);
      UInt   s    = INSN(12, 12);
      UInt   sz   = INSN(11, 10);

      UInt   index = (q << 3) | (s << 2) | sz;
      const HChar* name = "";
      Bool   valid = False;
      IRType laneTy = Ity_I8;

      if (opcode == 0x0) { 
         name = "b";
         valid = True;
      } else if (opcode == 0x2 && (sz & 1) == 0) { 
         name = "h";
         laneTy = Ity_I16;
         index >>= 1;
         valid = True;
      } else if (opcode == 0x4 && sz == 0x0) { 
         name = "s";
         laneTy = Ity_I32;
         index >>= 2;
         valid = True;
      } else if (opcode == 0x4 && sz == 0x1 && s == 0) { 
         name = "d";
         laneTy = Ity_I64;
         index >>= 3;
         valid = True;
      }

      if (valid) {
         IRTemp tEA  = newTemp(Ity_I64);
         assign(tEA, getIReg64orSP(rN));
         if (rN == 31) {  }
         if (isLD) {
            putQRegLane(vT, index, loadLE(laneTy, mkexpr(tEA)));
         } else {
            storeLE(mkexpr(tEA), getQRegLane(vT, index, laneTy));
         }

         DIP("%s {v%u.%s}[%d], [%s]\n", isLD ? "ld1" : "st1",
             vT, name, index, nameIReg64orSP(rN));
         return True;
      }

   }


   
   if (   (insn & 0xFFFFF000) == 0x4C407000 
       || (insn & 0xFFFFF000) == 0x4C007000 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      IRTemp tEA  = newTemp(Ity_I64);
      const HChar* names[4] = { "2d", "4s", "8h", "16b" };
      const HChar* name = names[INSN(11,10)];
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      if (isLD) {
         putQReg128(vT, loadLE(Ity_V128, mkexpr(tEA)));
      } else {
         storeLE(mkexpr(tEA), getQReg128(vT));
      }
      DIP("%s {v%u.%s}, [%s]\n", isLD ? "ld1" : "st1",
          vT, name, nameIReg64orSP(rN));
      return True;
   }

   if (   (insn & 0xFFFFF000) == 0x0C407000 
       || (insn & 0xFFFFF000) == 0x0C007000 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      IRTemp tEA  = newTemp(Ity_I64);
      const HChar* names[4] = { "1d", "2s", "4h", "8b" };
      const HChar* name = names[INSN(11,10)];
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      if (isLD) {
         putQRegLane(vT, 0, loadLE(Ity_I64, mkexpr(tEA)));
         putQRegLane(vT, 1, mkU64(0));
      } else {
         storeLE(mkexpr(tEA), getQRegLane(vT, 0, Ity_I64));
      }
      DIP("%s {v%u.%s}, [%s]\n", isLD ? "ld1" : "st1",
          vT, name, nameIReg64orSP(rN));
      return True;
   }

   
   if (   (insn & 0xFFFFF000) == 0x4CDF7000 
       || (insn & 0xFFFFF000) == 0x4C9F7000 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      IRTemp tEA  = newTemp(Ity_I64);
      const HChar* names[4] = { "2d", "4s", "8h", "16b" };
      const HChar* name = names[INSN(11,10)];
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      if (isLD) {
         putQReg128(vT, loadLE(Ity_V128, mkexpr(tEA)));
      } else {
         storeLE(mkexpr(tEA), getQReg128(vT));
      }
      putIReg64orSP(rN, binop(Iop_Add64, mkexpr(tEA), mkU64(16)));
      DIP("%s {v%u.%s}, [%s], #16\n", isLD ? "ld1" : "st1",
          vT, name, nameIReg64orSP(rN));
      return True;
   }

   if (   (insn & 0xFFFFF000) == 0x0CDF7000 
       || (insn & 0xFFFFF000) == 0x0C9F7000 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN  = INSN(9,5);
      UInt   vT  = INSN(4,0);
      IRTemp tEA = newTemp(Ity_I64);
      const HChar* names[4] = { "1d", "2s", "4h", "8b" };
      const HChar* name = names[INSN(11,10)];
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      if (isLD) {
         putQRegLane(vT, 0, loadLE(Ity_I64, mkexpr(tEA)));
         putQRegLane(vT, 1, mkU64(0));
      } else {
         storeLE(mkexpr(tEA), getQRegLane(vT, 0, Ity_I64));
      }
      putIReg64orSP(rN, binop(Iop_Add64, mkexpr(tEA), mkU64(8)));
      DIP("%s {v%u.%s}, [%s], #8\n",  isLD ? "ld1" : "st1",
          vT, name, nameIReg64orSP(rN));
      return True;
   }

   
   
   if (   (insn & 0xFFFFFC00) == 0x4CDF8C00 
       || (insn & 0xFFFFFC00) == 0x4C9F8C00 
       || (insn & 0xFFFFFC00) == 0x4CDF8800 
       || (insn & 0xFFFFFC00) == 0x4C9F8800 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      IRTemp tEA  = newTemp(Ity_I64);
      UInt   sz   = INSN(11,10);
      const HChar* name = "??";
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      IRExpr* tEA_0  = binop(Iop_Add64, mkexpr(tEA), mkU64(0));
      IRExpr* tEA_8  = binop(Iop_Add64, mkexpr(tEA), mkU64(8));
      IRExpr* tEA_16 = binop(Iop_Add64, mkexpr(tEA), mkU64(16));
      IRExpr* tEA_24 = binop(Iop_Add64, mkexpr(tEA), mkU64(24));
      if (sz == BITS2(1,1)) {
         name = "2d";
         if (isLD) {
            putQRegLane((vT+0) % 32, 0, loadLE(Ity_I64, tEA_0));
            putQRegLane((vT+0) % 32, 1, loadLE(Ity_I64, tEA_16));
            putQRegLane((vT+1) % 32, 0, loadLE(Ity_I64, tEA_8));
            putQRegLane((vT+1) % 32, 1, loadLE(Ity_I64, tEA_24));
         } else {
            storeLE(tEA_0,  getQRegLane((vT+0) % 32, 0, Ity_I64));
            storeLE(tEA_16, getQRegLane((vT+0) % 32, 1, Ity_I64));
            storeLE(tEA_8,  getQRegLane((vT+1) % 32, 0, Ity_I64));
            storeLE(tEA_24, getQRegLane((vT+1) % 32, 1, Ity_I64));
         }
      }
      else if (sz == BITS2(1,0)) {
         
         name = "4s";
         IRExpr* tEA_4  = binop(Iop_Add64, mkexpr(tEA), mkU64(4));
         IRExpr* tEA_12 = binop(Iop_Add64, mkexpr(tEA), mkU64(12));
         IRExpr* tEA_20 = binop(Iop_Add64, mkexpr(tEA), mkU64(20));
         IRExpr* tEA_28 = binop(Iop_Add64, mkexpr(tEA), mkU64(28));
         if (isLD) {
            putQRegLane((vT+0) % 32, 0, loadLE(Ity_I32, tEA_0));
            putQRegLane((vT+0) % 32, 1, loadLE(Ity_I32, tEA_8));
            putQRegLane((vT+0) % 32, 2, loadLE(Ity_I32, tEA_16));
            putQRegLane((vT+0) % 32, 3, loadLE(Ity_I32, tEA_24));
            putQRegLane((vT+1) % 32, 0, loadLE(Ity_I32, tEA_4));
            putQRegLane((vT+1) % 32, 1, loadLE(Ity_I32, tEA_12));
            putQRegLane((vT+1) % 32, 2, loadLE(Ity_I32, tEA_20));
            putQRegLane((vT+1) % 32, 3, loadLE(Ity_I32, tEA_28));
         } else {
            storeLE(tEA_0,  getQRegLane((vT+0) % 32, 0, Ity_I32));
            storeLE(tEA_8,  getQRegLane((vT+0) % 32, 1, Ity_I32));
            storeLE(tEA_16, getQRegLane((vT+0) % 32, 2, Ity_I32));
            storeLE(tEA_24, getQRegLane((vT+0) % 32, 3, Ity_I32));
            storeLE(tEA_4,  getQRegLane((vT+1) % 32, 0, Ity_I32));
            storeLE(tEA_12, getQRegLane((vT+1) % 32, 1, Ity_I32));
            storeLE(tEA_20, getQRegLane((vT+1) % 32, 2, Ity_I32));
            storeLE(tEA_28, getQRegLane((vT+1) % 32, 3, Ity_I32));
         }
      }
      else {
         vassert(0); 
      }
      putIReg64orSP(rN, binop(Iop_Add64, mkexpr(tEA), mkU64(32)));
      DIP("%s {v%u.%s, v%u.%s}, [%s], #32\n", isLD ? "ld2" : "st2",
          (vT+0) % 32, name, (vT+1) % 32, name, nameIReg64orSP(rN));
      return True;
   }

   
   
   if (   (insn & 0xFFFFFC00) == 0x4C40A000 
       || (insn & 0xFFFFFC00) == 0x4C00A000 
      ) {
      Bool   isLD = INSN(22,22) == 1;
      UInt   rN   = INSN(9,5);
      UInt   vT   = INSN(4,0);
      IRTemp tEA  = newTemp(Ity_I64);
      const HChar* name = "16b";
      assign(tEA, getIReg64orSP(rN));
      if (rN == 31) {  }
      IRExpr* tEA_0  = binop(Iop_Add64, mkexpr(tEA), mkU64(0));
      IRExpr* tEA_16 = binop(Iop_Add64, mkexpr(tEA), mkU64(16));
      if (isLD) {
         putQReg128((vT+0) % 32, loadLE(Ity_V128, tEA_0));
         putQReg128((vT+1) % 32, loadLE(Ity_V128, tEA_16));
      } else {
         storeLE(tEA_0,  getQReg128((vT+0) % 32));
         storeLE(tEA_16, getQReg128((vT+1) % 32));
      }
      DIP("%s {v%u.%s, v%u.%s}, [%s], #32\n", isLD ? "ld1" : "st1",
          (vT+0) % 32, name, (vT+1) % 32, name, nameIReg64orSP(rN));
      return True;
   }

   
   
   if (INSN(29,23) == BITS7(0,0,1,0,0,0,0)
       && (INSN(23,21) & BITS3(1,0,1)) == BITS3(0,0,0)
       && INSN(14,10) == BITS5(1,1,1,1,1)) {
      UInt szBlg2     = INSN(31,30);
      Bool isLD       = INSN(22,22) == 1;
      Bool isAcqOrRel = INSN(15,15) == 1;
      UInt ss         = INSN(20,16);
      UInt nn         = INSN(9,5);
      UInt tt         = INSN(4,0);

      vassert(szBlg2 < 4);
      UInt   szB = 1 << szBlg2; 
      IRType ty  = integerIRTypeOfSize(szB);
      const HChar* suffix[4] = { "rb", "rh", "r", "r" };

      IRTemp ea = newTemp(Ity_I64);
      assign(ea, getIReg64orSP(nn));
      

      if (isLD && ss == BITS5(1,1,1,1,1)) {
         IRTemp res = newTemp(ty);
         stmt(IRStmt_LLSC(Iend_LE, res, mkexpr(ea), NULL));
         putIReg64orZR(tt, widenUto64(ty, mkexpr(res)));
         if (isAcqOrRel) {
            stmt(IRStmt_MBE(Imbe_Fence));
         }
         DIP("ld%sx%s %s, [%s]\n", isAcqOrRel ? "a" : "", suffix[szBlg2],
             nameIRegOrZR(szB == 8, tt), nameIReg64orSP(nn));
         return True;
      }
      if (!isLD) {
         if (isAcqOrRel) {
            stmt(IRStmt_MBE(Imbe_Fence));
         }
         IRTemp  res  = newTemp(Ity_I1);
         IRExpr* data = narrowFrom64(ty, getIReg64orZR(tt));
         stmt(IRStmt_LLSC(Iend_LE, res, mkexpr(ea), data));
         putIReg64orZR(ss, binop(Iop_Xor64, unop(Iop_1Uto64, mkexpr(res)),
                                            mkU64(1)));
         DIP("st%sx%s %s, %s, [%s]\n", isAcqOrRel ? "a" : "", suffix[szBlg2],
             nameIRegOrZR(False, ss),
             nameIRegOrZR(szB == 8, tt), nameIReg64orSP(nn));
         return True;
      }
      
   }

   
   
   if (INSN(29,23) == BITS7(0,0,1,0,0,0,1)
       && INSN(21,10) == BITS12(0,1,1,1,1,1,1,1,1,1,1,1)) {
      UInt szBlg2 = INSN(31,30);
      Bool isLD   = INSN(22,22) == 1;
      UInt nn     = INSN(9,5);
      UInt tt     = INSN(4,0);

      vassert(szBlg2 < 4);
      UInt   szB = 1 << szBlg2; 
      IRType ty  = integerIRTypeOfSize(szB);
      const HChar* suffix[4] = { "rb", "rh", "r", "r" };

      IRTemp ea = newTemp(Ity_I64);
      assign(ea, getIReg64orSP(nn));
      

      if (isLD) {
         IRTemp res = newTemp(ty);
         assign(res, loadLE(ty, mkexpr(ea)));
         putIReg64orZR(tt, widenUto64(ty, mkexpr(res)));
         stmt(IRStmt_MBE(Imbe_Fence));
         DIP("lda%s %s, [%s]\n", suffix[szBlg2],
             nameIRegOrZR(szB == 8, tt), nameIReg64orSP(nn));
      } else {
         stmt(IRStmt_MBE(Imbe_Fence));
         IRExpr* data = narrowFrom64(ty, getIReg64orZR(tt));
         storeLE(mkexpr(ea), data);
         DIP("stl%s %s, [%s]\n", suffix[szBlg2],
             nameIRegOrZR(szB == 8, tt), nameIReg64orSP(nn));
      }
      return True;
   }

   

   if (INSN(31, 22) == BITS10(1,1,1,1,1,0,0,1,1,0)) {
      
      DIP("prfm ??? (imm)");
      return True;
   }

   vex_printf("ARM64 front end: load_store\n");
   return False;
#  undef INSN
}



static
Bool dis_ARM64_branch_etc(DisResult* dres, UInt insn,
                          VexArchInfo* archinfo)
{
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))

   
   if (INSN(31,24) == BITS8(0,1,0,1,0,1,0,0) && INSN(4,4) == 0) {
      UInt  cond   = INSN(3,0);
      ULong uimm64 = INSN(23,5) << 2;
      Long  simm64 = (Long)sx_to_64(uimm64, 21);
      vassert(dres->whatNext    == Dis_Continue);
      vassert(dres->len         == 4);
      vassert(dres->continueAt  == 0);
      vassert(dres->jk_StopHere == Ijk_INVALID);
      stmt( IRStmt_Exit(unop(Iop_64to1, mk_arm64g_calculate_condition(cond)),
                        Ijk_Boring,
                        IRConst_U64(guest_PC_curr_instr + simm64),
                        OFFB_PC) );
      putPC(mkU64(guest_PC_curr_instr + 4));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_Boring;
      DIP("b.%s 0x%llx\n", nameCC(cond), guest_PC_curr_instr + simm64);
      return True;
   }

   
   if (INSN(30,26) == BITS5(0,0,1,0,1)) {
      UInt  bLink  = INSN(31,31);
      ULong uimm64 = INSN(25,0) << 2;
      Long  simm64 = (Long)sx_to_64(uimm64, 28);
      if (bLink) {
         putIReg64orSP(30, mkU64(guest_PC_curr_instr + 4));
      }
      putPC(mkU64(guest_PC_curr_instr + simm64));
      dres->whatNext = Dis_StopHere;
      dres->jk_StopHere = Ijk_Call;
      DIP("b%s 0x%llx\n", bLink == 1 ? "l" : "",
                          guest_PC_curr_instr + simm64);
      return True;
   }

   
   if (INSN(31,23) == BITS9(1,1,0,1,0,1,1,0,0)
       && INSN(20,16) == BITS5(1,1,1,1,1)
       && INSN(15,10) == BITS6(0,0,0,0,0,0)
       && INSN(4,0) == BITS5(0,0,0,0,0)) {
      UInt branch_type = INSN(22,21);
      UInt nn          = INSN(9,5);
      if (branch_type == BITS2(1,0) ) {
         putPC(getIReg64orZR(nn));
         dres->whatNext = Dis_StopHere;
         dres->jk_StopHere = Ijk_Ret;
         DIP("ret %s\n", nameIReg64orZR(nn));
         return True;
      }
      if (branch_type == BITS2(0,1) ) {
         IRTemp dst = newTemp(Ity_I64);
         assign(dst, getIReg64orZR(nn));
         putIReg64orSP(30, mkU64(guest_PC_curr_instr + 4));
         putPC(mkexpr(dst));
         dres->whatNext = Dis_StopHere;
         dres->jk_StopHere = Ijk_Call;
         DIP("blr %s\n", nameIReg64orZR(nn));
         return True;
      }
      if (branch_type == BITS2(0,0) ) {
         putPC(getIReg64orZR(nn));
         dres->whatNext = Dis_StopHere;
         dres->jk_StopHere = Ijk_Boring;
         DIP("jmp %s\n", nameIReg64orZR(nn));
         return True;
      }
   }

   
   if (INSN(30,25) == BITS6(0,1,1,0,1,0)) {
      Bool    is64   = INSN(31,31) == 1;
      Bool    bIfZ   = INSN(24,24) == 0;
      ULong   uimm64 = INSN(23,5) << 2;
      UInt    rT     = INSN(4,0);
      Long    simm64 = (Long)sx_to_64(uimm64, 21);
      IRExpr* cond   = NULL;
      if (is64) {
         cond = binop(bIfZ ? Iop_CmpEQ64 : Iop_CmpNE64,
                      getIReg64orZR(rT), mkU64(0));
      } else {
         cond = binop(bIfZ ? Iop_CmpEQ32 : Iop_CmpNE32,
                      getIReg32orZR(rT), mkU32(0));
      }
      stmt( IRStmt_Exit(cond,
                        Ijk_Boring,
                        IRConst_U64(guest_PC_curr_instr + simm64),
                        OFFB_PC) );
      putPC(mkU64(guest_PC_curr_instr + 4));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_Boring;
      DIP("cb%sz %s, 0x%llx\n",
          bIfZ ? "" : "n", nameIRegOrZR(is64, rT),
          guest_PC_curr_instr + simm64);
      return True;
   }

   
   if (INSN(30,25) == BITS6(0,1,1,0,1,1)) {
      UInt    b5     = INSN(31,31);
      Bool    bIfZ   = INSN(24,24) == 0;
      UInt    b40    = INSN(23,19);
      UInt    imm14  = INSN(18,5);
      UInt    tt     = INSN(4,0);
      UInt    bitNo  = (b5 << 5) | b40;
      ULong   uimm64 = imm14 << 2;
      Long    simm64 = sx_to_64(uimm64, 16);
      IRExpr* cond 
         = binop(bIfZ ? Iop_CmpEQ64 : Iop_CmpNE64,
                 binop(Iop_And64,
                       binop(Iop_Shr64, getIReg64orZR(tt), mkU8(bitNo)),
                       mkU64(1)),
                 mkU64(0));
      stmt( IRStmt_Exit(cond,
                        Ijk_Boring,
                        IRConst_U64(guest_PC_curr_instr + simm64),
                        OFFB_PC) );
      putPC(mkU64(guest_PC_curr_instr + 4));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_Boring;
      DIP("tb%sz %s, #%u, 0x%llx\n",
          bIfZ ? "" : "n", nameIReg64orZR(tt), bitNo,
          guest_PC_curr_instr + simm64);
      return True;
   }

   
   if (INSN(31,0) == 0xD4000001) {
      putPC(mkU64(guest_PC_curr_instr + 4));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_Sys_syscall;
      DIP("svc #0\n");
      return True;
   }

   
   if (   (INSN(31,0) & 0xFFFFFFE0) == 0xD51BD040 
       || (INSN(31,0) & 0xFFFFFFE0) == 0xD53BD040 ) {
      Bool toSys = INSN(21,21) == 0;
      UInt tt    = INSN(4,0);
      if (toSys) {
         stmt( IRStmt_Put( OFFB_TPIDR_EL0, getIReg64orZR(tt)) );
         DIP("msr tpidr_el0, %s\n", nameIReg64orZR(tt));
      } else {
         putIReg64orZR(tt, IRExpr_Get( OFFB_TPIDR_EL0, Ity_I64 ));
         DIP("mrs %s, tpidr_el0\n", nameIReg64orZR(tt));
      }
      return True;
   }
   if (   (INSN(31,0) & 0xFFFFFFE0) == 0xD51B4400 
       || (INSN(31,0) & 0xFFFFFFE0) == 0xD53B4400 ) {
      Bool toSys = INSN(21,21) == 0;
      UInt tt    = INSN(4,0);
      if (toSys) {
         stmt( IRStmt_Put( OFFB_FPCR, getIReg32orZR(tt)) );
         DIP("msr fpcr, %s\n", nameIReg64orZR(tt));
      } else {
         putIReg32orZR(tt, IRExpr_Get(OFFB_FPCR, Ity_I32));
         DIP("mrs %s, fpcr\n", nameIReg64orZR(tt));
      }
      return True;
   }
   if (   (INSN(31,0) & 0xFFFFFFE0) == 0xD51B4420 
       || (INSN(31,0) & 0xFFFFFFE0) == 0xD53B4420 ) {
      Bool toSys = INSN(21,21) == 0;
      UInt tt    = INSN(4,0);
      if (toSys) {
         stmt( IRStmt_Put( OFFB_FPSR, getIReg32orZR(tt)) );
         DIP("msr fpsr, %s\n", nameIReg64orZR(tt));
      } else {
         putIReg32orZR(tt, IRExpr_Get(OFFB_FPSR, Ity_I32));
         DIP("mrs %s, fpsr\n", nameIReg64orZR(tt));
      }
      return True;
   }
   if (   (INSN(31,0) & 0xFFFFFFE0) == 0xD51B4200 
       || (INSN(31,0) & 0xFFFFFFE0) == 0xD53B4200 ) {
      Bool  toSys = INSN(21,21) == 0;
      UInt  tt    = INSN(4,0);
      if (toSys) {
         IRTemp t = newTemp(Ity_I64);
         assign(t, binop(Iop_And64, getIReg64orZR(tt), mkU64(0xF0000000ULL)));
         setFlags_COPY(t);
         DIP("msr %s, nzcv\n", nameIReg32orZR(tt));
      } else {
         IRTemp res = newTemp(Ity_I64);
         assign(res, mk_arm64g_calculate_flags_nzcv());
         putIReg32orZR(tt, unop(Iop_64to32, mkexpr(res)));
         DIP("mrs %s, nzcv\n", nameIReg64orZR(tt));
      }
      return True;
   }
   if ((INSN(31,0) & 0xFFFFFFE0) == 0xD53B00E0) {
      UInt tt = INSN(4,0);
      putIReg64orZR(tt, mkU64(1<<4));
      DIP("mrs %s, dczid_el0 (FAKED)\n", nameIReg64orZR(tt));
      return True;
   }
   if ((INSN(31,0) & 0xFFFFFFE0) == 0xD53B0020) {
      UInt tt = INSN(4,0);
      vassert(archinfo->arm64_dMinLine_lg2_szB >= 2
              && archinfo->arm64_dMinLine_lg2_szB <= 17
              && archinfo->arm64_iMinLine_lg2_szB >= 2
              && archinfo->arm64_iMinLine_lg2_szB <= 17);
      UInt val
         = 0x8440c000 | ((0xF & (archinfo->arm64_dMinLine_lg2_szB - 2)) << 16)
                      | ((0xF & (archinfo->arm64_iMinLine_lg2_szB - 2)) << 0);
      putIReg64orZR(tt, mkU64(val));
      DIP("mrs %s, ctr_el0\n", nameIReg64orZR(tt));
      return True;
   }

   
   if ((INSN(31,0) & 0xFFFFFFE0) == 0xD50B7520) {
      
      vassert(archinfo->arm64_iMinLine_lg2_szB >= 2
              && archinfo->arm64_iMinLine_lg2_szB <= 17);
      UInt   tt      = INSN(4,0);
      ULong  lineszB = 1ULL << archinfo->arm64_iMinLine_lg2_szB;
      IRTemp addr    = newTemp(Ity_I64);
      assign( addr, binop( Iop_And64,
                           getIReg64orZR(tt),
                           mkU64(~(lineszB - 1))) );
      stmt(IRStmt_Put(OFFB_CMSTART, mkexpr(addr)));
      stmt(IRStmt_Put(OFFB_CMLEN,   mkU64(lineszB)));
      
      stmt( IRStmt_MBE(Imbe_Fence) );
      putPC(mkU64( guest_PC_curr_instr + 4 ));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_InvalICache;
      DIP("ic ivau, %s\n", nameIReg64orZR(tt));
      return True;
   }

   
   if ((INSN(31,0) & 0xFFFFFFE0) == 0xD50B7B20) {
      
      vassert(archinfo->arm64_dMinLine_lg2_szB >= 2
              && archinfo->arm64_dMinLine_lg2_szB <= 17);
      UInt   tt      = INSN(4,0);
      ULong  lineszB = 1ULL << archinfo->arm64_dMinLine_lg2_szB;
      IRTemp addr    = newTemp(Ity_I64);
      assign( addr, binop( Iop_And64,
                           getIReg64orZR(tt),
                           mkU64(~(lineszB - 1))) );
      stmt(IRStmt_Put(OFFB_CMSTART, mkexpr(addr)));
      stmt(IRStmt_Put(OFFB_CMLEN,   mkU64(lineszB)));
      
      stmt( IRStmt_MBE(Imbe_Fence) );
      putPC(mkU64( guest_PC_curr_instr + 4 ));
      dres->whatNext    = Dis_StopHere;
      dres->jk_StopHere = Ijk_FlushDCache;
      DIP("dc cvau, %s\n", nameIReg64orZR(tt));
      return True;
   }

   
   if (INSN(31,0) == 0xD5033FDF) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("isb\n");
      return True;
   }
   if (INSN(31,0) == 0xD5033BBF) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("dmb ish\n");
      return True;
   }
   if (INSN(31,0) == 0xD5033ABF) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("dmb ishst\n");
      return True;
   }
   if (INSN(31,0) == 0xD50339BF) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("dmb ishld\n");
      return True;
   }
   if (INSN(31,0) == 0xD5033B9F) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("dsb ish\n");
      return True;
   }
   if (INSN(31,0) == 0xD5033F9F) {
      stmt(IRStmt_MBE(Imbe_Fence));
      DIP("dsb sy\n");
      return True;
   }

   
   if (INSN(31,0) == 0xD503201F) {
      DIP("nop\n");
      return True;
   }

  
   vex_printf("ARM64 front end: branch_etc\n");
   return False;
#  undef INSN
}



static IRExpr* mk_CatEvenLanes64x2 ( IRTemp, IRTemp );
static IRExpr* mk_CatOddLanes64x2  ( IRTemp, IRTemp );

static IRExpr* mk_CatEvenLanes32x4 ( IRTemp, IRTemp );
static IRExpr* mk_CatOddLanes32x4  ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveLO32x4 ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveHI32x4 ( IRTemp, IRTemp );

static IRExpr* mk_CatEvenLanes16x8 ( IRTemp, IRTemp );
static IRExpr* mk_CatOddLanes16x8  ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveLO16x8 ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveHI16x8 ( IRTemp, IRTemp );

static IRExpr* mk_CatEvenLanes8x16 ( IRTemp, IRTemp );
static IRExpr* mk_CatOddLanes8x16  ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveLO8x16 ( IRTemp, IRTemp );
static IRExpr* mk_InterleaveHI8x16 ( IRTemp, IRTemp );

static ULong Replicate ( ULong bit, Int N )
{
   vassert(bit <= 1 && N >= 1 && N < 64);
   if (bit == 0) {
      return 0;
    } else {
      
      return (1ULL << N) - 1;
   }
}

static ULong Replicate32x2 ( ULong bits32 )
{
   vassert(0 == (bits32 & ~0xFFFFFFFFULL));
   return (bits32 << 32) | bits32;
}

static ULong Replicate16x4 ( ULong bits16 )
{
   vassert(0 == (bits16 & ~0xFFFFULL));
   return Replicate32x2((bits16 << 16) | bits16);
}

static ULong Replicate8x8 ( ULong bits8 )
{
   vassert(0 == (bits8 & ~0xFFULL));
   return Replicate16x4((bits8 << 8) | bits8);
}

static ULong VFPExpandImm ( ULong imm8, Int N )
{
   vassert(imm8 <= 0xFF);
   vassert(N == 32 || N == 64);
   Int E = ((N == 32) ? 8 : 11) - 2; 
   Int F = N - E - 1;
   ULong imm8_6 = (imm8 >> 6) & 1;
   
   
   
   ULong sign = (imm8 >> 7) & 1;
   ULong exp  = ((imm8_6 ^ 1) << (E-1)) | Replicate(imm8_6, E-1);
   ULong frac = ((imm8 & 63) << (F-6)) | Replicate(0, F-6);
   vassert(sign < (1ULL << 1));
   vassert(exp  < (1ULL << E));
   vassert(frac < (1ULL << F));
   vassert(1 + E + F == N);
   ULong res = (sign << (E+F)) | (exp << F) | frac;
   return res;
}

static Bool AdvSIMDExpandImm ( ULong* res,
                               UInt op, UInt cmode, UInt imm8 )
{
   vassert(op <= 1);
   vassert(cmode <= 15);
   vassert(imm8 <= 255);

   *res = 0; 

   ULong imm64    = 0;
   Bool  testimm8 = False;

   switch (cmode >> 1) {
      case 0:
         testimm8 = False; imm64 = Replicate32x2(imm8); break;
      case 1:
         testimm8 = True; imm64 = Replicate32x2(imm8 << 8); break;
      case 2:
         testimm8 = True; imm64 = Replicate32x2(imm8 << 16); break;
      case 3:
         testimm8 = True; imm64 = Replicate32x2(imm8 << 24); break;
      case 4:
          testimm8 = False; imm64 = Replicate16x4(imm8); break;
      case 5:
          testimm8 = True; imm64 = Replicate16x4(imm8 << 8); break;
      case 6:
          testimm8 = True;
          if ((cmode & 1) == 0)
              imm64 = Replicate32x2((imm8 << 8) | 0xFF);
          else
              imm64 = Replicate32x2((imm8 << 16) | 0xFFFF);
          break;
      case 7:
         testimm8 = False;
         if ((cmode & 1) == 0 && op == 0)
             imm64 = Replicate8x8(imm8);
         if ((cmode & 1) == 0 && op == 1) {
             imm64 = 0;   imm64 |= (imm8 & 0x80) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x40) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x20) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x10) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x08) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x04) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x02) ? 0xFF : 0x00;
             imm64 <<= 8; imm64 |= (imm8 & 0x01) ? 0xFF : 0x00;
         }
         if ((cmode & 1) == 1 && op == 0) {
            ULong imm8_7  = (imm8 >> 7) & 1;
            ULong imm8_6  = (imm8 >> 6) & 1;
            ULong imm8_50 = imm8 & 63;
            ULong imm32 = (imm8_7                 << (1 + 5 + 6 + 19))
                          | ((imm8_6 ^ 1)         << (5 + 6 + 19))
                          | (Replicate(imm8_6, 5) << (6 + 19))
                          | (imm8_50              << 19);
            imm64 = Replicate32x2(imm32);
         }
         if ((cmode & 1) == 1 && op == 1) {
            
            
            ULong imm8_7  = (imm8 >> 7) & 1;
            ULong imm8_6  = (imm8 >> 6) & 1;
            ULong imm8_50 = imm8 & 63;
            imm64 = (imm8_7 << 63) | ((imm8_6 ^ 1) << 62)
                    | (Replicate(imm8_6, 8) << 54)
                    | (imm8_50 << 48);
         }
         break;
      default:
        vassert(0);
   }

   if (testimm8 && imm8 == 0)
      return False;

   *res = imm64;
   return True;
}


static Bool getLaneInfo_Q_SZ ( IRType* tyI,  IRType* tyF,
                               UInt* nLanes, Bool* zeroUpper,
                               const HChar** arrSpec,
                               Bool bitQ, Bool bitSZ )
{
   vassert(bitQ == True || bitQ == False);
   vassert(bitSZ == True || bitSZ == False);
   if (bitQ && bitSZ) { 
      if (tyI)       *tyI       = Ity_I64;
      if (tyF)       *tyF       = Ity_F64;
      if (nLanes)    *nLanes    = 2;
      if (zeroUpper) *zeroUpper = False;
      if (arrSpec)   *arrSpec   = "2d";
      return True;
   }
   if (bitQ && !bitSZ) { 
      if (tyI)       *tyI       = Ity_I32;
      if (tyF)       *tyF       = Ity_F32;
      if (nLanes)    *nLanes    = 4;
      if (zeroUpper) *zeroUpper = False;
      if (arrSpec)   *arrSpec   = "4s";
      return True;
   }
   if (!bitQ && !bitSZ) { 
      if (tyI)       *tyI       = Ity_I32;
      if (tyF)       *tyF       = Ity_F32;
      if (nLanes)    *nLanes    = 2;
      if (zeroUpper) *zeroUpper = True;
      if (arrSpec)   *arrSpec   = "2s";
      return True;
   }
   
   return False;
}

static Bool getLaneInfo_SIMPLE ( Bool* zeroUpper,
                                 const HChar** arrSpec,
                                 Bool bitQ, UInt szBlg2 )
{
   vassert(bitQ == True || bitQ == False);
   vassert(szBlg2 < 4);
   Bool zu = False;
   const HChar* as = NULL;
   switch ((szBlg2 << 1) | (bitQ ? 1 : 0)) {
      case 0: zu = True;  as = "8b";  break;
      case 1: zu = False; as = "16b"; break;
      case 2: zu = True;  as = "4h";  break;
      case 3: zu = False; as = "8h";  break;
      case 4: zu = True;  as = "2s";  break;
      case 5: zu = False; as = "4s";  break;
      case 6: return False; 
      case 7: zu = False; as = "2d";  break;
      default: vassert(0);
   }
   vassert(as);
   if (arrSpec)   *arrSpec = as;
   if (zeroUpper) *zeroUpper = zu;
   return True;
}


static Bool getLaneInfo_IMMH_IMMB ( UInt* shift, UInt* szBlg2,
                                    UInt immh, UInt immb )
{
   vassert(immh < (1<<4));
   vassert(immb < (1<<3));
   UInt immhb = (immh << 3) | immb;
   if (immh & 8) {
      if (shift)  *shift  = 128 - immhb;
      if (szBlg2) *szBlg2 = 3;
      return True;
   }
   if (immh & 4) {
      if (shift)  *shift  = 64 - immhb;
      if (szBlg2) *szBlg2 = 2;
      return True;
   }
   if (immh & 2) {
      if (shift)  *shift  = 32 - immhb;
      if (szBlg2) *szBlg2 = 1;
      return True;
   }
   if (immh & 1) {
      if (shift)  *shift  = 16 - immhb;
      if (szBlg2) *szBlg2 = 0;
      return True;
   }
   return False;
}


static IRTemp math_MINMAXV ( IRTemp src, IROp op )
{
   switch (op) {
      case Iop_Min8Sx16: case Iop_Min8Ux16:
      case Iop_Max8Sx16: case Iop_Max8Ux16: {
         IRTemp x76543210 = src;
         IRTemp x76547654 = newTemp(Ity_V128);
         IRTemp x32103210 = newTemp(Ity_V128);
         assign(x76547654, mk_CatOddLanes64x2 (x76543210, x76543210));
         assign(x32103210, mk_CatEvenLanes64x2(x76543210, x76543210));
         IRTemp x76767676 = newTemp(Ity_V128);
         IRTemp x54545454 = newTemp(Ity_V128);
         IRTemp x32323232 = newTemp(Ity_V128);
         IRTemp x10101010 = newTemp(Ity_V128);
         assign(x76767676, mk_CatOddLanes32x4 (x76547654, x76547654));
         assign(x54545454, mk_CatEvenLanes32x4(x76547654, x76547654));
         assign(x32323232, mk_CatOddLanes32x4 (x32103210, x32103210));
         assign(x10101010, mk_CatEvenLanes32x4(x32103210, x32103210));
         IRTemp x77777777 = newTemp(Ity_V128);
         IRTemp x66666666 = newTemp(Ity_V128);
         IRTemp x55555555 = newTemp(Ity_V128);
         IRTemp x44444444 = newTemp(Ity_V128);
         IRTemp x33333333 = newTemp(Ity_V128);
         IRTemp x22222222 = newTemp(Ity_V128);
         IRTemp x11111111 = newTemp(Ity_V128);
         IRTemp x00000000 = newTemp(Ity_V128);
         assign(x77777777, mk_CatOddLanes16x8 (x76767676, x76767676));
         assign(x66666666, mk_CatEvenLanes16x8(x76767676, x76767676));
         assign(x55555555, mk_CatOddLanes16x8 (x54545454, x54545454));
         assign(x44444444, mk_CatEvenLanes16x8(x54545454, x54545454));
         assign(x33333333, mk_CatOddLanes16x8 (x32323232, x32323232));
         assign(x22222222, mk_CatEvenLanes16x8(x32323232, x32323232));
         assign(x11111111, mk_CatOddLanes16x8 (x10101010, x10101010));
         assign(x00000000, mk_CatEvenLanes16x8(x10101010, x10101010));
         
         IRTemp xAllF = newTemp(Ity_V128);
         IRTemp xAllE = newTemp(Ity_V128);
         IRTemp xAllD = newTemp(Ity_V128);
         IRTemp xAllC = newTemp(Ity_V128);
         IRTemp xAllB = newTemp(Ity_V128);
         IRTemp xAllA = newTemp(Ity_V128);
         IRTemp xAll9 = newTemp(Ity_V128);
         IRTemp xAll8 = newTemp(Ity_V128);
         IRTemp xAll7 = newTemp(Ity_V128);
         IRTemp xAll6 = newTemp(Ity_V128);
         IRTemp xAll5 = newTemp(Ity_V128);
         IRTemp xAll4 = newTemp(Ity_V128);
         IRTemp xAll3 = newTemp(Ity_V128);
         IRTemp xAll2 = newTemp(Ity_V128);
         IRTemp xAll1 = newTemp(Ity_V128);
         IRTemp xAll0 = newTemp(Ity_V128);
         assign(xAllF, mk_CatOddLanes8x16 (x77777777, x77777777));
         assign(xAllE, mk_CatEvenLanes8x16(x77777777, x77777777));
         assign(xAllD, mk_CatOddLanes8x16 (x66666666, x66666666));
         assign(xAllC, mk_CatEvenLanes8x16(x66666666, x66666666));
         assign(xAllB, mk_CatOddLanes8x16 (x55555555, x55555555));
         assign(xAllA, mk_CatEvenLanes8x16(x55555555, x55555555));
         assign(xAll9, mk_CatOddLanes8x16 (x44444444, x44444444));
         assign(xAll8, mk_CatEvenLanes8x16(x44444444, x44444444));
         assign(xAll7, mk_CatOddLanes8x16 (x33333333, x33333333));
         assign(xAll6, mk_CatEvenLanes8x16(x33333333, x33333333));
         assign(xAll5, mk_CatOddLanes8x16 (x22222222, x22222222));
         assign(xAll4, mk_CatEvenLanes8x16(x22222222, x22222222));
         assign(xAll3, mk_CatOddLanes8x16 (x11111111, x11111111));
         assign(xAll2, mk_CatEvenLanes8x16(x11111111, x11111111));
         assign(xAll1, mk_CatOddLanes8x16 (x00000000, x00000000));
         assign(xAll0, mk_CatEvenLanes8x16(x00000000, x00000000));
         IRTemp maxFE = newTemp(Ity_V128);
         IRTemp maxDC = newTemp(Ity_V128);
         IRTemp maxBA = newTemp(Ity_V128);
         IRTemp max98 = newTemp(Ity_V128);
         IRTemp max76 = newTemp(Ity_V128);
         IRTemp max54 = newTemp(Ity_V128);
         IRTemp max32 = newTemp(Ity_V128);
         IRTemp max10 = newTemp(Ity_V128);
         assign(maxFE, binop(op, mkexpr(xAllF), mkexpr(xAllE)));
         assign(maxDC, binop(op, mkexpr(xAllD), mkexpr(xAllC)));
         assign(maxBA, binop(op, mkexpr(xAllB), mkexpr(xAllA)));
         assign(max98, binop(op, mkexpr(xAll9), mkexpr(xAll8)));
         assign(max76, binop(op, mkexpr(xAll7), mkexpr(xAll6)));
         assign(max54, binop(op, mkexpr(xAll5), mkexpr(xAll4)));
         assign(max32, binop(op, mkexpr(xAll3), mkexpr(xAll2)));
         assign(max10, binop(op, mkexpr(xAll1), mkexpr(xAll0)));
         IRTemp maxFEDC = newTemp(Ity_V128);
         IRTemp maxBA98 = newTemp(Ity_V128);
         IRTemp max7654 = newTemp(Ity_V128);
         IRTemp max3210 = newTemp(Ity_V128);
         assign(maxFEDC, binop(op, mkexpr(maxFE), mkexpr(maxDC)));
         assign(maxBA98, binop(op, mkexpr(maxBA), mkexpr(max98)));
         assign(max7654, binop(op, mkexpr(max76), mkexpr(max54)));
         assign(max3210, binop(op, mkexpr(max32), mkexpr(max10)));
         IRTemp maxFEDCBA98 = newTemp(Ity_V128);
         IRTemp max76543210 = newTemp(Ity_V128);
         assign(maxFEDCBA98, binop(op, mkexpr(maxFEDC), mkexpr(maxBA98)));
         assign(max76543210, binop(op, mkexpr(max7654), mkexpr(max3210)));
         IRTemp maxAllLanes = newTemp(Ity_V128);
         assign(maxAllLanes, binop(op, mkexpr(maxFEDCBA98),
                                       mkexpr(max76543210)));
         IRTemp res = newTemp(Ity_V128);
         assign(res, unop(Iop_ZeroHI120ofV128, mkexpr(maxAllLanes)));
         return res;
      }
      case Iop_Min16Sx8: case Iop_Min16Ux8:
      case Iop_Max16Sx8: case Iop_Max16Ux8: {
         IRTemp x76543210 = src;
         IRTemp x76547654 = newTemp(Ity_V128);
         IRTemp x32103210 = newTemp(Ity_V128);
         assign(x76547654, mk_CatOddLanes64x2 (x76543210, x76543210));
         assign(x32103210, mk_CatEvenLanes64x2(x76543210, x76543210));
         IRTemp x76767676 = newTemp(Ity_V128);
         IRTemp x54545454 = newTemp(Ity_V128);
         IRTemp x32323232 = newTemp(Ity_V128);
         IRTemp x10101010 = newTemp(Ity_V128);
         assign(x76767676, mk_CatOddLanes32x4 (x76547654, x76547654));
         assign(x54545454, mk_CatEvenLanes32x4(x76547654, x76547654));
         assign(x32323232, mk_CatOddLanes32x4 (x32103210, x32103210));
         assign(x10101010, mk_CatEvenLanes32x4(x32103210, x32103210));
         IRTemp x77777777 = newTemp(Ity_V128);
         IRTemp x66666666 = newTemp(Ity_V128);
         IRTemp x55555555 = newTemp(Ity_V128);
         IRTemp x44444444 = newTemp(Ity_V128);
         IRTemp x33333333 = newTemp(Ity_V128);
         IRTemp x22222222 = newTemp(Ity_V128);
         IRTemp x11111111 = newTemp(Ity_V128);
         IRTemp x00000000 = newTemp(Ity_V128);
         assign(x77777777, mk_CatOddLanes16x8 (x76767676, x76767676));
         assign(x66666666, mk_CatEvenLanes16x8(x76767676, x76767676));
         assign(x55555555, mk_CatOddLanes16x8 (x54545454, x54545454));
         assign(x44444444, mk_CatEvenLanes16x8(x54545454, x54545454));
         assign(x33333333, mk_CatOddLanes16x8 (x32323232, x32323232));
         assign(x22222222, mk_CatEvenLanes16x8(x32323232, x32323232));
         assign(x11111111, mk_CatOddLanes16x8 (x10101010, x10101010));
         assign(x00000000, mk_CatEvenLanes16x8(x10101010, x10101010));
         IRTemp max76 = newTemp(Ity_V128);
         IRTemp max54 = newTemp(Ity_V128);
         IRTemp max32 = newTemp(Ity_V128);
         IRTemp max10 = newTemp(Ity_V128);
         assign(max76, binop(op, mkexpr(x77777777), mkexpr(x66666666)));
         assign(max54, binop(op, mkexpr(x55555555), mkexpr(x44444444)));
         assign(max32, binop(op, mkexpr(x33333333), mkexpr(x22222222)));
         assign(max10, binop(op, mkexpr(x11111111), mkexpr(x00000000)));
         IRTemp max7654 = newTemp(Ity_V128);
         IRTemp max3210 = newTemp(Ity_V128);
         assign(max7654, binop(op, mkexpr(max76), mkexpr(max54)));
         assign(max3210, binop(op, mkexpr(max32), mkexpr(max10)));
         IRTemp max76543210 = newTemp(Ity_V128);
         assign(max76543210, binop(op, mkexpr(max7654), mkexpr(max3210)));
         IRTemp res = newTemp(Ity_V128);
         assign(res, unop(Iop_ZeroHI112ofV128, mkexpr(max76543210)));
         return res;
      }
      case Iop_Min32Sx4: case Iop_Min32Ux4:
      case Iop_Max32Sx4: case Iop_Max32Ux4: {
         IRTemp x3210 = src;
         IRTemp x3232 = newTemp(Ity_V128);
         IRTemp x1010 = newTemp(Ity_V128);
         assign(x3232, mk_CatOddLanes64x2 (x3210, x3210));
         assign(x1010, mk_CatEvenLanes64x2(x3210, x3210));
         IRTemp x3333 = newTemp(Ity_V128);
         IRTemp x2222 = newTemp(Ity_V128);
         IRTemp x1111 = newTemp(Ity_V128);
         IRTemp x0000 = newTemp(Ity_V128);
         assign(x3333, mk_CatOddLanes32x4 (x3232, x3232));
         assign(x2222, mk_CatEvenLanes32x4(x3232, x3232));
         assign(x1111, mk_CatOddLanes32x4 (x1010, x1010));
         assign(x0000, mk_CatEvenLanes32x4(x1010, x1010));
         IRTemp max32 = newTemp(Ity_V128);
         IRTemp max10 = newTemp(Ity_V128);
         assign(max32, binop(op, mkexpr(x3333), mkexpr(x2222)));
         assign(max10, binop(op, mkexpr(x1111), mkexpr(x0000)));
         IRTemp max3210 = newTemp(Ity_V128);
         assign(max3210, binop(op, mkexpr(max32), mkexpr(max10)));
         IRTemp res = newTemp(Ity_V128);
         assign(res, unop(Iop_ZeroHI96ofV128, mkexpr(max3210)));
         return res;
      }
      default:
         vassert(0);
   }
}


static IRTemp math_TBL_TBX ( IRTemp tab[4], UInt len, IRTemp src,
                             IRTemp oor_values )
{
   vassert(len >= 0 && len <= 3);

   
   IRTemp half15 = newTemp(Ity_I64);
   assign(half15, mkU64(0x0F0F0F0F0F0F0F0FULL));
   IRTemp half16 = newTemp(Ity_I64);
   assign(half16, mkU64(0x1010101010101010ULL));

   
   IRTemp allZero = newTemp(Ity_V128);
   assign(allZero, mkV128(0x0000));
   
   IRTemp all15 = newTemp(Ity_V128);
   assign(all15, binop(Iop_64HLtoV128, mkexpr(half15), mkexpr(half15)));
   
   IRTemp all16 = newTemp(Ity_V128);
   assign(all16, binop(Iop_64HLtoV128, mkexpr(half16), mkexpr(half16)));
   
   IRTemp all32 = newTemp(Ity_V128);
   assign(all32, binop(Iop_Add8x16, mkexpr(all16), mkexpr(all16)));
   
   IRTemp all48 = newTemp(Ity_V128);
   assign(all48, binop(Iop_Add8x16, mkexpr(all16), mkexpr(all32)));
   
   IRTemp all64 = newTemp(Ity_V128);
   assign(all64, binop(Iop_Add8x16, mkexpr(all32), mkexpr(all32)));

   
   IRTemp allXX[4] = { all16, all32, all48, all64 };

   IRTemp running_result = newTemp(Ity_V128);
   assign(running_result, mkV128(0));

   UInt tabent;
   for (tabent = 0; tabent <= len; tabent++) {
      vassert(tabent >= 0 && tabent < 4);
      IRTemp bias = newTemp(Ity_V128);
      assign(bias,
             mkexpr(tabent == 0 ? allZero : allXX[tabent-1]));
      IRTemp biased_indices = newTemp(Ity_V128);
      assign(biased_indices,
             binop(Iop_Sub8x16, mkexpr(src), mkexpr(bias)));
      IRTemp valid_mask = newTemp(Ity_V128);
      assign(valid_mask,
             binop(Iop_CmpGT8Ux16, mkexpr(all16), mkexpr(biased_indices)));
      IRTemp safe_biased_indices = newTemp(Ity_V128);
      assign(safe_biased_indices,
             binop(Iop_AndV128, mkexpr(biased_indices), mkexpr(all15)));
      IRTemp results_or_junk = newTemp(Ity_V128);
      assign(results_or_junk,
             binop(Iop_Perm8x16, mkexpr(tab[tabent]),
                                 mkexpr(safe_biased_indices)));
      IRTemp results_or_zero = newTemp(Ity_V128);
      assign(results_or_zero,
             binop(Iop_AndV128, mkexpr(results_or_junk), mkexpr(valid_mask)));
      
      IRTemp tmp = newTemp(Ity_V128);
      assign(tmp, binop(Iop_OrV128, mkexpr(results_or_zero),
                        mkexpr(running_result)));
      running_result = tmp;
   }

   IRTemp overall_valid_mask = newTemp(Ity_V128);
   assign(overall_valid_mask,
          binop(Iop_CmpGT8Ux16, mkexpr(allXX[len]), mkexpr(src)));
   IRTemp result = newTemp(Ity_V128);
   assign(result,
          binop(Iop_OrV128,
                mkexpr(running_result),
                binop(Iop_AndV128,
                      mkexpr(oor_values),
                      unop(Iop_NotV128, mkexpr(overall_valid_mask)))));
   return result;      
}


static
Bool dis_ARM64_simd_and_fp(DisResult* dres, UInt insn)
{
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))

   
   if (INSN(30,24) == BITS7(0,0,1,1,1,1,0)
       && INSN(21,21) == 1 && INSN(15,10) == BITS6(0,0,0,0,0,0)) {
      UInt sf = INSN(31,31);
      UInt ty = INSN(23,22); 
      UInt rm = INSN(20,19); 
      UInt op = INSN(18,16); 
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      UInt ix = 0; 
      if (sf == 0) {
         if (ty == BITS2(0,0) && rm == BITS2(0,0) && op == BITS3(1,1,1))
            ix = 1;
         else
         if (ty == BITS2(0,0) && rm == BITS2(0,0) && op == BITS3(1,1,0))
            ix = 4;
      } else {
         vassert(sf == 1);
         if (ty == BITS2(0,1) && rm == BITS2(0,0) && op == BITS3(1,1,1))
            ix = 2;
         else
         if (ty == BITS2(0,1) && rm == BITS2(0,0) && op == BITS3(1,1,0))
            ix = 5;
         else
         if (ty == BITS2(1,0) && rm == BITS2(0,1) && op == BITS3(1,1,1))
            ix = 3;
         else
         if (ty == BITS2(1,0) && rm == BITS2(0,1) && op == BITS3(1,1,0))
            ix = 6;
      }
      if (ix > 0) {
         switch (ix) {
            case 1:
               putQReg128(dd, mkV128(0));
               putQRegLO(dd, getIReg32orZR(nn));
               DIP("fmov s%u, w%u\n", dd, nn);
               break;
            case 2:
               putQReg128(dd, mkV128(0));
               putQRegLO(dd, getIReg64orZR(nn));
               DIP("fmov d%u, x%u\n", dd, nn);
               break;
            case 3:
               putQRegHI64(dd, getIReg64orZR(nn));
               DIP("fmov v%u.d[1], x%u\n", dd, nn);
               break;
            case 4:
               putIReg32orZR(dd, getQRegLO(nn, Ity_I32));
               DIP("fmov w%u, s%u\n", dd, nn);
               break;
            case 5:
               putIReg64orZR(dd, getQRegLO(nn, Ity_I64));
               DIP("fmov x%u, d%u\n", dd, nn);
               break;
            case 6:
               putIReg64orZR(dd, getQRegHI64(nn));
               DIP("fmov x%u, v%u.d[1]\n", dd, nn);
               break;
            default:
               vassert(0);
         }
         return True;
      }
      
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,0,0)
       && INSN(21,21) == 1 && INSN(12,5) == BITS8(1,0,0,0,0,0,0,0)) {
      Bool  isD  = INSN(22,22) == 1;
      UInt  imm8 = INSN(20,13);
      UInt  dd   = INSN(4,0);
      ULong imm  = VFPExpandImm(imm8, isD ? 64 : 32);
      if (!isD) {
         vassert(0 == (imm & 0xFFFFFFFF00000000ULL));
      }
      putQReg128(dd, mkV128(0));
      putQRegLO(dd, isD ? mkU64(imm) : mkU32(imm & 0xFFFFFFFFULL));
      DIP("fmov %s, #0x%llx\n",
          nameQRegLO(dd, isD ? Ity_F64 : Ity_F32), imm);
      return True;
   }

   
   if (INSN(31,31) == 0
       && INSN(28,19) == BITS10(0,1,1,1,1,0,0,0,0,0)
       && INSN(11,10) == BITS2(0,1)) {
      UInt  bitQ     = INSN(30,30);
      UInt  bitOP    = INSN(29,29);
      UInt  cmode    = INSN(15,12);
      UInt  imm8     = (INSN(18,16) << 5) | INSN(9,5);
      UInt  dd       = INSN(4,0);
      ULong imm64lo  = 0;
      UInt  op_cmode = (bitOP << 4) | cmode;
      Bool  ok       = False;
      switch (op_cmode) {
         case BITS5(1,1,1,1,1): 
         case BITS5(0,0,0,0,0): case BITS5(0,0,1,0,0):
         case BITS5(0,1,0,0,0): case BITS5(0,1,1,0,0): 
         case BITS5(1,0,0,0,0): case BITS5(1,0,1,0,0): 
         case BITS5(1,1,0,0,0): case BITS5(1,1,0,1,0): 
         case BITS5(1,1,1,0,0): case BITS5(1,1,1,0,1): 
         case BITS5(1,1,1,1,0): case BITS5(0,1,1,1,0): 
            ok = True; break;
         default:
           break;
      }
      if (ok) {
         ok = AdvSIMDExpandImm(&imm64lo, bitOP, cmode, imm8);
      }
      if (ok) {
         ULong imm64hi = (bitQ == 0 && bitOP == 0)  ? 0  : imm64lo;
         putQReg128(dd, binop(Iop_64HLtoV128, mkU64(imm64hi), mkU64(imm64lo)));
         DIP("mov %s, #0x%016llx'%016llx\n", nameQReg128(dd), imm64hi, imm64lo);
         return True;
      }
      
   }

   
   if (INSN(31,30) == BITS2(0,1) && INSN(28,23) == BITS6(1,1,1,1,0,0)
       && INSN(21, 10) == BITS12(1,0,0,0,0,1,1,1,0,1,1,0)) {
      Bool is64 = INSN(22,22);
      Bool isU  = INSN(29,29);
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);

      UInt ix   = (INSN(29,29) << 1) | INSN(22,22);

      const IROp ops[4]
        = { Iop_I32StoF32, Iop_I64StoF64,
            Iop_I32UtoF32, Iop_I64UtoF64 };

      putQReg128(dd, mkV128(0));
      putQRegLO(dd, binop(ops[ix], mkexpr(mk_get_IR_rounding_mode()), getQRegLO(nn, is64 ? Ity_I64 : Ity_I32)));

      DIP("%ccvtf %s, %s\n",
          isU ? 'u' : 's', nameQRegLO(dd, is64 ? Ity_F64 : Ity_F32),
          nameQRegLO(nn, is64 ? Ity_I64 : Ity_I32));

      return True;
   }
   
   if (INSN(30,23) == BITS8(0,0,1,1,1,1,0,0) && INSN(21,17) == BITS5(1,0,0,0,1)
       && INSN(15,10) == BITS6(0,0,0,0,0,0)) {
      Bool isI64 = INSN(31,31) == 1;
      Bool isF64 = INSN(22,22) == 1;
      Bool isU   = INSN(16,16) == 1;
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      UInt ix    = (isU ? 4 : 0) | (isI64 ? 2 : 0) | (isF64 ? 1 : 0);
      const IROp ops[8]
        = { Iop_I32StoF32, Iop_I32StoF64, Iop_I64StoF32, Iop_I64StoF64,
            Iop_I32UtoF32, Iop_I32UtoF64, Iop_I64UtoF32, Iop_I64UtoF64 };
      IRExpr* src = getIRegOrZR(isI64, nn);
      IRExpr* res = (isF64 && !isI64) 
                       ? unop(ops[ix], src)
                       : binop(ops[ix], mkexpr(mk_get_IR_rounding_mode()), src);
      putQReg128(dd, mkV128(0));
      putQRegLO(dd, res);
      DIP("%ccvtf %s, %s\n",
          isU ? 'u' : 's', nameQRegLO(dd, isF64 ? Ity_F64 : Ity_F32), 
          nameIRegOrZR(isI64, nn));
      return True;
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,0,0)
       && INSN(21,21) == 1 && INSN(11,10) == BITS2(1,0)) {
      Bool   isD = INSN(22,22) == 1;
      UInt   mm  = INSN(20,16);
      UInt   op  = INSN(15,12);
      UInt   nn  = INSN(9,5);
      UInt   dd  = INSN(4,0);
      IROp   iop = Iop_INVALID;
      IRType ty  = isD ? Ity_F64 : Ity_F32;
      Bool   neg = False;
      const HChar* nm = "???";
      switch (op) {
         case BITS4(0,0,0,0): nm = "fmul";  iop = mkMULF(ty); break;
         case BITS4(0,0,0,1): nm = "fdiv";  iop = mkDIVF(ty); break;
         case BITS4(0,0,1,0): nm = "fadd";  iop = mkADDF(ty); break;
         case BITS4(0,0,1,1): nm = "fsub";  iop = mkSUBF(ty); break;
         case BITS4(1,0,0,0): nm = "fnmul"; iop = mkMULF(ty);
                              neg = True; break;
         default:             return False;
      }
      vassert(iop != Iop_INVALID);
      IRExpr* resE = triop(iop, mkexpr(mk_get_IR_rounding_mode()),
                           getQRegLO(nn, ty), getQRegLO(mm, ty));
      IRTemp res = newTemp(ty);
      assign(res, neg ? unop(mkNEGF(ty),resE) : resE);
      putQReg128(dd, mkV128(0));
      putQRegLO(dd, mkexpr(res));
      DIP("%s %s, %s, %s\n",
          nm, nameQRegLO(dd, ty), nameQRegLO(nn, ty), nameQRegLO(mm, ty));
      return True;
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,0,0)
       && INSN(21,17) == BITS5(1,0,0,0,0)
       && INSN(14,10) == BITS5(1,0,0,0,0)) {
      Bool   isD = INSN(22,22) == 1;
      UInt   opc = INSN(16,15);
      UInt   nn  = INSN(9,5);
      UInt   dd  = INSN(4,0);
      IRType ty  = isD ? Ity_F64 : Ity_F32;
      IRTemp res = newTemp(ty);
      if (opc == BITS2(0,0)) {
         assign(res, getQRegLO(nn, ty));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(res));
         DIP("fmov %s, %s\n",
             nameQRegLO(dd, ty), nameQRegLO(nn, ty));
         return True;
      }
      if (opc == BITS2(1,0) || opc == BITS2(0,1)) {
         Bool isAbs = opc == BITS2(0,1);
         IROp op    = isAbs ? mkABSF(ty) : mkNEGF(ty);
         assign(res, unop(op, getQRegLO(nn, ty)));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(res));
         DIP("%s %s, %s\n", isAbs ? "fabs" : "fneg",
             nameQRegLO(dd, ty), nameQRegLO(nn, ty));
         return True;
      }
      if (opc == BITS2(1,1)) {
         assign(res,
                binop(mkSQRTF(ty),
                      mkexpr(mk_get_IR_rounding_mode()), getQRegLO(nn, ty)));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(res));
         DIP("fsqrt %s, %s\n", nameQRegLO(dd, ty), nameQRegLO(nn, ty));
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(28,23) == BITS6(0,1,1,1,0,1)
       && INSN(21,17) == BITS5(1,0,0,0,0)
       && INSN(16,10) == BITS7(0,1,1,1,1,1,0)) {
      UInt bitQ   = INSN(30,30);
      UInt bitSZ  = INSN(22,22);
      Bool isFNEG = INSN(29,29) == 1;
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      const HChar* ar = "??";
      IRType tyF    = Ity_INVALID;
      Bool   zeroHI = False;
      Bool   ok     = getLaneInfo_Q_SZ(NULL, &tyF, NULL, &zeroHI, &ar,
                                       (Bool)bitQ, (Bool)bitSZ);
      if (ok) {
         vassert(tyF == Ity_F64 || tyF == Ity_F32);
         IROp op = (tyF == Ity_F64) ? (isFNEG ? Iop_Neg64Fx2 : Iop_Abs64Fx2)
                                    : (isFNEG ? Iop_Neg32Fx4 : Iop_Abs32Fx4);
         IRTemp res = newTemp(Ity_V128);
         assign(res, unop(op, getQReg128(nn)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(res))
                               : mkexpr(res));
         DIP("%s %s.%s, %s.%s\n", isFNEG ? "fneg" : "fabs",
             nameQReg128(dd), ar, nameQReg128(nn), ar);
         return True;
      }
      
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,0,0) && INSN(21,21) == 1 
       && INSN(15,10) == BITS6(0,0,1,0,0,0) && INSN(2,0) == BITS3(0,0,0)) {
      Bool   isD     = INSN(22,22) == 1;
      UInt   mm      = INSN(20,16);
      UInt   nn      = INSN(9,5);
      Bool   isCMPE  = INSN(4,4) == 1;
      Bool   cmpZero = INSN(3,3) == 1;
      IRType ty      = isD ? Ity_F64 : Ity_F32;
      Bool   valid   = True;
      if (cmpZero && mm != 0) valid = False;
      if (valid) {
         IRTemp argL  = newTemp(ty);
         IRTemp argR  = newTemp(ty);
         IRTemp irRes = newTemp(Ity_I32);
         assign(argL, getQRegLO(nn, ty));
         assign(argR,
                cmpZero 
                   ? (IRExpr_Const(isD ? IRConst_F64i(0) : IRConst_F32i(0)))
                   : getQRegLO(mm, ty));
         assign(irRes, binop(isD ? Iop_CmpF64 : Iop_CmpF32,
                             mkexpr(argL), mkexpr(argR)));
         IRTemp nzcv = mk_convert_IRCmpF64Result_to_NZCV(irRes);
         IRTemp nzcv_28x0 = newTemp(Ity_I64);
         assign(nzcv_28x0, binop(Iop_Shl64, mkexpr(nzcv), mkU8(28)));
         setFlags_COPY(nzcv_28x0);
         DIP("fcmp%s %s, %s\n", isCMPE ? "e" : "", nameQRegLO(nn, ty),
             cmpZero ? "#0.0" : nameQRegLO(mm, ty));
         return True;
      }
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,1,0)) {
      Bool    isD   = INSN(22,22) == 1;
      UInt    mm    = INSN(20,16);
      UInt    aa    = INSN(14,10);
      UInt    nn    = INSN(9,5);
      UInt    dd    = INSN(4,0);
      UInt    ix    = (INSN(21,21) << 1) | INSN(15,15);
      IRType  ty    = isD ? Ity_F64 : Ity_F32;
      IROp    opADD = mkADDF(ty);
      IROp    opSUB = mkSUBF(ty);
      IROp    opMUL = mkMULF(ty);
      IROp    opNEG = mkNEGF(ty);
      IRTemp  res   = newTemp(ty);
      IRExpr* eA    = getQRegLO(aa, ty);
      IRExpr* eN    = getQRegLO(nn, ty);
      IRExpr* eM    = getQRegLO(mm, ty);
      IRExpr* rm    = mkexpr(mk_get_IR_rounding_mode());
      IRExpr* eNxM  = triop(opMUL, rm, eN, eM);
      switch (ix) {
         case 0:  assign(res, triop(opADD, rm, eA, eNxM)); break;
         case 1:  assign(res, triop(opSUB, rm, eA, eNxM)); break;
         case 2:  assign(res, unop(opNEG, triop(opADD, rm, eA, eNxM))); break;
         case 3:  assign(res, unop(opNEG, triop(opSUB, rm, eA, eNxM))); break;
         default: vassert(0);
      }
      putQReg128(dd, mkV128(0x0000));
      putQRegLO(dd, mkexpr(res));
      const HChar* names[4] = { "fmadd", "fmsub", "fnmadd", "fnmsub" };
      DIP("%s %s, %s, %s, %s\n",
          names[ix], nameQRegLO(dd, ty), nameQRegLO(nn, ty),
                     nameQRegLO(mm, ty), nameQRegLO(aa, ty));
      return True;
   }

   
   if (INSN(30,23) == BITS8(0,0,1,1,1,1,0,0) && INSN(21,21) == 1
       && INSN(18,17) == BITS2(0,0) && INSN(15,10) == BITS6(0,0,0,0,0,0)) {
      Bool isI64 = INSN(31,31) == 1;
      Bool isF64 = INSN(22,22) == 1;
      UInt rm    = INSN(20,19);
      Bool isU   = INSN(16,16) == 1;
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      
      IRRoundingMode irrm = 8; 
      HChar ch = '?';
      switch (rm) {
         case BITS2(0,0): ch = 'n'; irrm = Irrm_NEAREST; break;
         case BITS2(0,1): ch = 'p'; irrm = Irrm_PosINF; break;
         case BITS2(1,0): ch = 'm'; irrm = Irrm_NegINF; break;
         case BITS2(1,1): ch = 'z'; irrm = Irrm_ZERO; break;
         default: vassert(0);
      }
      vassert(irrm != 8);
      UInt ix = (isF64 ? 4 : 0) | (isI64 ? 2 : 0) | (isU ? 1 : 0);
      vassert(ix < 8);
      const IROp ops[8] 
         = { Iop_F32toI32S, Iop_F32toI32U, Iop_F32toI64S, Iop_F32toI64U,
             Iop_F64toI32S, Iop_F64toI32U, Iop_F64toI64S, Iop_F64toI64U };
      IROp op = ops[ix];
      
      if (
             (op == Iop_F32toI32S && irrm == Irrm_ZERO)   
          || (op == Iop_F32toI32S && irrm == Irrm_NegINF) 
          || (op == Iop_F32toI32S && irrm == Irrm_PosINF) 
          
          || (op == Iop_F32toI32U && irrm == Irrm_ZERO)   
          || (op == Iop_F32toI32U && irrm == Irrm_NegINF) 
          
          || (op == Iop_F32toI64S && irrm == Irrm_ZERO)   
          
          || (op == Iop_F32toI64U && irrm == Irrm_ZERO)   
          || (op == Iop_F32toI64U && irrm == Irrm_PosINF) 
          
          || (op == Iop_F64toI32S && irrm == Irrm_ZERO)   
          || (op == Iop_F64toI32S && irrm == Irrm_NegINF) 
          || (op == Iop_F64toI32S && irrm == Irrm_PosINF) 
          
          || (op == Iop_F64toI32U && irrm == Irrm_ZERO)   
          || (op == Iop_F64toI32U && irrm == Irrm_NegINF) 
          || (op == Iop_F64toI32U && irrm == Irrm_PosINF) 
          
          || (op == Iop_F64toI64S && irrm == Irrm_ZERO)   
          || (op == Iop_F64toI64S && irrm == Irrm_NegINF) 
          || (op == Iop_F64toI64S && irrm == Irrm_PosINF) 
          
          || (op == Iop_F64toI64U && irrm == Irrm_ZERO)   
          || (op == Iop_F64toI64U && irrm == Irrm_PosINF) 
         ) {
        
      } else {
        return False;
      }
      IRType srcTy  = isF64 ? Ity_F64 : Ity_F32;
      IRType dstTy  = isI64 ? Ity_I64 : Ity_I32;
      IRTemp src    = newTemp(srcTy);
      IRTemp dst    = newTemp(dstTy);
      assign(src, getQRegLO(nn, srcTy));
      assign(dst, binop(op, mkU32(irrm), mkexpr(src)));
      putIRegOrZR(isI64, dd, mkexpr(dst));
      DIP("fcvt%c%c %s, %s\n", ch, isU ? 'u' : 's',
          nameIRegOrZR(isI64, dd), nameQRegLO(nn, srcTy));
      return True;
   }

   
   if (INSN(30,23) == BITS8(0,0,1,1,1,1,0,0)
       && INSN(21,16) == BITS6(1,0,0,1,0,0)
       && INSN(15,10) == BITS6(0,0,0,0,0,0)) {
      Bool isI64 = INSN(31,31) == 1;
      Bool isF64 = INSN(22,22) == 1;
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      
      
      IRRoundingMode irrm = Irrm_NEAREST;
      
      IROp   op    = isI64 ? (isF64 ? Iop_F64toI64S :  Iop_F32toI64S)
                           : (isF64 ? Iop_F64toI32S :  Iop_F32toI32S);
      IRType srcTy = isF64 ? Ity_F64 : Ity_F32;
      IRType dstTy = isI64 ? Ity_I64 : Ity_I32;
      IRTemp src   = newTemp(srcTy);
      IRTemp dst   = newTemp(dstTy);
      assign(src, getQRegLO(nn, srcTy));
      assign(dst, binop(op, mkU32(irrm), mkexpr(src)));
      putIRegOrZR(isI64, dd, mkexpr(dst));
      DIP("fcvtas %s, %s (KLUDGED)\n",
          nameIRegOrZR(isI64, dd), nameQRegLO(nn, srcTy));
      return True;
   }

   
   if (INSN(31,23) == BITS9(0,0,0,1,1,1,1,0,0)
       && INSN(21,18) == BITS4(1,0,0,1) && INSN(14,10) == BITS5(1,0,0,0,0)) {
      Bool    isD   = INSN(22,22) == 1;
      UInt    rm    = INSN(17,15);
      UInt    nn    = INSN(9,5);
      UInt    dd    = INSN(4,0);
      IRType  ty    = isD ? Ity_F64 : Ity_F32;
      IRExpr* irrmE = NULL;
      UChar   ch    = '?';
      switch (rm) {
         case BITS3(0,1,1): ch = 'z'; irrmE = mkU32(Irrm_ZERO); break;
         case BITS3(0,1,0): ch = 'm'; irrmE = mkU32(Irrm_NegINF); break;
         case BITS3(0,0,1): ch = 'p'; irrmE = mkU32(Irrm_PosINF); break;
         
         case BITS3(1,0,0): ch = 'a'; irrmE = mkU32(Irrm_NEAREST); break;
         default: break;
      }
      if (irrmE) {
         IRTemp src = newTemp(ty);
         IRTemp dst = newTemp(ty);
         assign(src, getQRegLO(nn, ty));
         assign(dst, binop(isD ? Iop_RoundF64toInt : Iop_RoundF32toInt,
                           irrmE, mkexpr(src)));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(dst));
         DIP("frint%c %s, %s\n",
             ch, nameQRegLO(dd, ty), nameQRegLO(nn, ty));
         return True;
      }
      
   }

   
   if (INSN(31,24) == BITS8(0,0,0,1,1,1,1,0)
       && INSN(21,17) == BITS5(1,0,0,0,1) 
       && INSN(14,10) == BITS5(1,0,0,0,0)) {
      UInt b2322 = INSN(23,22);
      UInt b1615 = INSN(16,15);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      if (b2322 == BITS2(0,0) && b1615 == BITS2(0,1)) {
         
         IRTemp res = newTemp(Ity_F64);
         assign(res, unop(Iop_F32toF64, getQRegLO(nn, Ity_F32)));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(res));
         DIP("fcvt %s, %s\n",
             nameQRegLO(dd, Ity_F64), nameQRegLO(nn, Ity_F32));
         return True;
      }
      if (b2322 == BITS2(0,1) && b1615 == BITS2(0,0)) {
         
         IRTemp res = newTemp(Ity_F32);
         assign(res, binop(Iop_F64toF32, mkexpr(mk_get_IR_rounding_mode()),
                                         getQRegLO(nn, Ity_F64)));
         putQReg128(dd, mkV128(0x0000));
         putQRegLO(dd, mkexpr(res));
         DIP("fcvt %s, %s\n",
             nameQRegLO(dd, Ity_F32), nameQRegLO(nn, Ity_F64));
         return True;
      }
      
   }

   
   if (INSN(31,23) == BITS9(0,1,1,1,1,1,1,0,1) && INSN(21,21) == 1
       && INSN(15,10) == BITS6(1,1,0,1,0,1)) {
      Bool   isD = INSN(22,22) == 1;
      UInt   mm  = INSN(20,16);
      UInt   nn  = INSN(9,5);
      UInt   dd  = INSN(4,0);
      IRType ty  = isD ? Ity_F64 : Ity_F32;
      IRTemp res = newTemp(ty);
      assign(res, unop(mkABSF(ty),
                       triop(mkSUBF(ty),
                             mkexpr(mk_get_IR_rounding_mode()),
                             getQRegLO(nn,ty), getQRegLO(mm,ty))));
      putQReg128(dd, mkV128(0x0000));
      putQRegLO(dd, mkexpr(res));
      DIP("fabd %s, %s, %s\n",
          nameQRegLO(dd, ty), nameQRegLO(nn, ty), nameQRegLO(mm, ty));
      return True;
   }

   
   if (INSN(31,31) == 0 && INSN(28,23) == BITS6(0,1,1,1,0,0)
       && INSN(21,16) == BITS6(1,0,0,0,0,1)
       && INSN(15,10) == BITS6(1,1,0,1,1,0)) {
      Bool isQ   = INSN(30,30) == 1;
      Bool isU   = INSN(29,29) == 1;
      Bool isF64 = INSN(22,22) == 1;
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      if (isQ || !isF64) {
         IRType tyF = Ity_INVALID, tyI = Ity_INVALID;
         UInt   nLanes = 0;
         Bool   zeroHI = False;
         const HChar* arrSpec = NULL;
         Bool   ok = getLaneInfo_Q_SZ(&tyI, &tyF, &nLanes, &zeroHI, &arrSpec,
                                      isQ, isF64 );
         IROp   op = isU ? (isF64 ? Iop_I64UtoF64 : Iop_I32UtoF32)
                         : (isF64 ? Iop_I64StoF64 : Iop_I32StoF32);
         IRTemp rm = mk_get_IR_rounding_mode();
         UInt   i;
         vassert(ok); 
         for (i = 0; i < nLanes; i++) {
            putQRegLane(dd, i,
                        binop(op, mkexpr(rm), getQRegLane(nn, i, tyI)));
         }
         if (zeroHI) {
            putQRegLane(dd, 1, mkU64(0));
         }
         DIP("%ccvtf %s.%s, %s.%s\n", isU ? 'u' : 's',
             nameQReg128(dd), arrSpec, nameQReg128(nn), arrSpec);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0
       && INSN(28,24) == BITS5(0,1,1,1,0) && INSN(21,21) == 1) {
      Bool isQ   = INSN(30,30) == 1;
      UInt b29   = INSN(29,29);
      UInt b23   = INSN(23,23);
      Bool isF64 = INSN(22,22) == 1;
      UInt mm    = INSN(20,16);
      UInt b1510 = INSN(15,10);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      UInt ix    = 0;
       if (b29 == 0 && b23 == 0 && b1510 == BITS6(1,1,0,1,0,1)) ix = 1;
      else if (b29 == 0 && b23 == 1 && b1510 == BITS6(1,1,0,1,0,1)) ix = 2;
      else if (b29 == 1 && b23 == 0 && b1510 == BITS6(1,1,0,1,1,1)) ix = 3;
      else if (b29 == 1 && b23 == 0 && b1510 == BITS6(1,1,1,1,1,1)) ix = 4;
      else if (b29 == 0 && b23 == 0 && b1510 == BITS6(1,1,0,0,1,1)) ix = 5;
      else if (b29 == 0 && b23 == 1 && b1510 == BITS6(1,1,0,0,1,1)) ix = 6;
      else if (b29 == 1 && b23 == 1 && b1510 == BITS6(1,1,0,1,0,1)) ix = 7;
      IRType laneTy = Ity_INVALID;
      Bool   zeroHI = False;
      const HChar* arr = "??";
      Bool ok
         = getLaneInfo_Q_SZ(NULL, &laneTy, NULL, &zeroHI, &arr, isQ, isF64);
      
      if (ok && ix >= 1 && ix <= 4) {
         const IROp ops64[4]
            = { Iop_Add64Fx2, Iop_Sub64Fx2, Iop_Mul64Fx2, Iop_Div64Fx2 };
         const IROp ops32[4]
            = { Iop_Add32Fx4, Iop_Sub32Fx4, Iop_Mul32Fx4, Iop_Div32Fx4 };
         const HChar* names[4]
            = { "fadd", "fsub", "fmul", "fdiv" };
         IROp   op = laneTy==Ity_F64 ? ops64[ix-1] : ops32[ix-1];
         IRTemp rm = mk_get_IR_rounding_mode();
         IRTemp t1 = newTemp(Ity_V128);
         IRTemp t2 = newTemp(Ity_V128);
         assign(t1, triop(op, mkexpr(rm), getQReg128(nn), getQReg128(mm)));
         assign(t2, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t1))
                           : mkexpr(t1));
         putQReg128(dd, mkexpr(t2));
         DIP("%s %s.%s, %s.%s, %s.%s\n", names[ix-1],
             nameQReg128(dd), arr, nameQReg128(nn), arr, nameQReg128(mm), arr);
         return True;
      }
      if (ok && ix >= 5 && ix <= 6) {
         IROp opADD = laneTy==Ity_F64 ? Iop_Add64Fx2 : Iop_Add32Fx4;
         IROp opSUB = laneTy==Ity_F64 ? Iop_Sub64Fx2 : Iop_Sub32Fx4;
         IROp opMUL = laneTy==Ity_F64 ? Iop_Mul64Fx2 : Iop_Mul32Fx4;
         IRTemp rm = mk_get_IR_rounding_mode();
         IRTemp t1 = newTemp(Ity_V128);
         IRTemp t2 = newTemp(Ity_V128);
         
         assign(t1, triop(opMUL,
                          mkexpr(rm), getQReg128(nn), getQReg128(mm)));
         assign(t2, triop(ix == 5 ? opADD : opSUB,
                          mkexpr(rm), getQReg128(dd), mkexpr(t1)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t2))
                               : mkexpr(t2));
         DIP("%s %s.%s, %s.%s, %s.%s\n", ix == 5 ? "fmla" : "fmls",
             nameQReg128(dd), arr, nameQReg128(nn), arr, nameQReg128(mm), arr);
         return True;
      }
      if (ok && ix == 7) {
         IROp opSUB = laneTy==Ity_F64 ? Iop_Sub64Fx2 : Iop_Sub32Fx4;
         IROp opABS = laneTy==Ity_F64 ? Iop_Abs64Fx2 : Iop_Abs32Fx4;
         IRTemp rm = mk_get_IR_rounding_mode();
         IRTemp t1 = newTemp(Ity_V128);
         IRTemp t2 = newTemp(Ity_V128);
         
         assign(t1, triop(opSUB,
                          mkexpr(rm), getQReg128(nn), getQReg128(mm)));
         assign(t2, unop(opABS, mkexpr(t1)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t2))
                               : mkexpr(t2));
         DIP("fabd %s.%s, %s.%s, %s.%s\n",
             nameQReg128(dd), arr, nameQReg128(nn), arr, nameQReg128(mm), arr);
         return True;
      }
   }

   
   if (INSN(31,31) == 0 && INSN(28,24) == BITS5(0,1,1,1,0) && INSN(21,21) == 1
       && INSN(15,12) == BITS4(1,1,1,0) && INSN(10,10) == 1) {
      Bool isQ   = INSN(30,30) == 1;
      UInt U     = INSN(29,29);
      UInt E     = INSN(23,23);
      Bool isF64 = INSN(22,22) == 1;
      UInt ac    = INSN(11,11);
      UInt mm    = INSN(20,16);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      
      UInt   EUac   = (E << 2) | (U << 1) | ac;
      IROp   opABS  = Iop_INVALID;
      IROp   opCMP  = Iop_INVALID;
      IRType laneTy = Ity_INVALID;
      Bool   zeroHI = False;
      Bool   swap   = True;
      const HChar* arr = "??";
      const HChar* nm  = "??";
      Bool ok
         = getLaneInfo_Q_SZ(NULL, &laneTy, NULL, &zeroHI, &arr, isQ, isF64);
      if (ok) {
         vassert((isF64 && laneTy == Ity_F64) || (!isF64 && laneTy == Ity_F32));
         switch (EUac) {
            case BITS3(0,0,0):
               nm    = "fcmeq";
               opCMP = isF64 ? Iop_CmpEQ64Fx2 : Iop_CmpEQ32Fx4;
               swap  = False;
               break;
            case BITS3(0,1,0):
               nm    = "fcmge";
               opCMP = isF64 ? Iop_CmpLE64Fx2 : Iop_CmpLE32Fx4;
               break;
            case BITS3(0,1,1):
               nm    = "facge";
               opCMP = isF64 ? Iop_CmpLE64Fx2 : Iop_CmpLE32Fx4;
               opABS = isF64 ? Iop_Abs64Fx2 : Iop_Abs32Fx4;
               break;
            case BITS3(1,1,0):
               nm    = "fcmgt";
               opCMP = isF64 ? Iop_CmpLT64Fx2 : Iop_CmpLT32Fx4;
               break;
            case BITS3(1,1,1):
               nm    = "fcagt";
               opCMP = isF64 ? Iop_CmpLE64Fx2 : Iop_CmpLE32Fx4;
               opABS = isF64 ? Iop_Abs64Fx2 : Iop_Abs32Fx4;
               break;
            default:
               break;
         }
      }
      if (opCMP != Iop_INVALID) {
         IRExpr* argN = getQReg128(nn);
         IRExpr* argM = getQReg128(mm);
         if (opABS != Iop_INVALID) {
            argN = unop(opABS, argN);
            argM = unop(opABS, argM);
         }
         IRExpr* res = swap ? binop(opCMP, argM, argN)
                            : binop(opCMP, argN, argM);
         if (zeroHI) {
            res = unop(Iop_ZeroHI64ofV128, res);
         }
         putQReg128(dd, res);
         DIP("%s %s.%s, %s.%s, %s.%s\n", nm,
             nameQReg128(dd), arr, nameQReg128(nn), arr, nameQReg128(mm), arr);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(29,23) == BITS7(0,0,1,1,1,0,0)
       && INSN(21,10) == BITS12(1,0,0,0,0,1,0,1,1,0,1,0)) {
      UInt bQ = INSN(30,30);
      UInt bS = INSN(22,22);
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      if (bS == 1) {
         IRTemp  rm    = mk_get_IR_rounding_mode();
         IRExpr* srcLo = getQRegLane(nn, 0, Ity_F64);
         IRExpr* srcHi = getQRegLane(nn, 1, Ity_F64);
         putQRegLane(dd, 2 * bQ + 0, binop(Iop_F64toF32, mkexpr(rm), srcLo));
         putQRegLane(dd, 2 * bQ + 1, binop(Iop_F64toF32, mkexpr(rm), srcHi));
         if (bQ == 0) {
            putQRegLane(dd, 1, mkU64(0));
         }
         DIP("fcvtn%s %s.%s, %s.2d\n", bQ ? "2" : "",
             nameQReg128(dd), bQ ? "4s" : "2s", nameQReg128(nn));
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(28,24) == BITS5(0,1,1,1,0)
       && INSN(21,21) == 1 && INSN(15,10) == BITS6(1,0,0,0,0,1)) {
      Bool isQ    = INSN(30,30) == 1;
      UInt szBlg2 = INSN(23,22);
      Bool isSUB  = INSN(29,29) == 1;
      UInt mm     = INSN(20,16);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool zeroHI = False;
      const HChar* arrSpec = "";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2 );
      if (ok) {
         const IROp opsADD[4]
            = { Iop_Add8x16, Iop_Add16x8, Iop_Add32x4, Iop_Add64x2 };
         const IROp opsSUB[4]
            = { Iop_Sub8x16, Iop_Sub16x8, Iop_Sub32x4, Iop_Sub64x2 };
         vassert(szBlg2 < 4);
         IROp   op = isSUB ? opsSUB[szBlg2] : opsADD[szBlg2];
         IRTemp t  = newTemp(Ity_V128);
         assign(t, binop(op, getQReg128(nn), getQReg128(mm)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t))
                               : mkexpr(t));
         const HChar* nm = isSUB ? "sub" : "add";
         DIP("%s %s.%s, %s.%s, %s.%s\n", nm,
             nameQReg128(dd), arrSpec, 
             nameQReg128(nn), arrSpec, nameQReg128(mm), arrSpec);
         return True;
      }
      
   }

   
   if (INSN(31,30) == BITS2(0,1) && INSN(28,21) == BITS8(1,1,1,1,0,1,1,1)
       && INSN(15,10) == BITS6(1,0,0,0,0,1)) {
      Bool isSUB = INSN(29,29) == 1;
      UInt mm    = INSN(20,16);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      IRTemp res = newTemp(Ity_I64);
      assign(res, binop(isSUB ? Iop_Sub64 : Iop_Add64,
                        getQRegLane(nn, 0, Ity_I64),
                        getQRegLane(mm, 0, Ity_I64)));
      putQRegLane(dd, 0, mkexpr(res));
      putQRegLane(dd, 1, mkU64(0));
      DIP("%s %s, %s, %s\n", isSUB ? "sub" : "add",
          nameQRegLO(dd, Ity_I64),
          nameQRegLO(nn, Ity_I64), nameQRegLO(mm, Ity_I64));
      return True;
   }

   
   if (INSN(31,31) == 0 && INSN(28,24) == BITS5(0,1,1,1,0)
       && INSN(21,21) == 1 
       && (INSN(15,10) & BITS6(1,1,1,1,0,1)) == BITS6(1,0,0,1,0,1)) {
      Bool isQ    = INSN(30,30) == 1;
      UInt szBlg2 = INSN(23,22);
      UInt bit29  = INSN(29,29);
      UInt mm     = INSN(20,16);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool isMLAS = INSN(11,11) == 0;
      const IROp opsADD[4]
         = { Iop_Add8x16, Iop_Add16x8, Iop_Add32x4, Iop_INVALID };
      const IROp opsSUB[4]
         = { Iop_Sub8x16, Iop_Sub16x8, Iop_Sub32x4, Iop_INVALID };
      const IROp opsMUL[4]
         = { Iop_Mul8x16, Iop_Mul16x8, Iop_Mul32x4, Iop_INVALID };
      const IROp opsPMUL[4]
         = { Iop_PolynomialMul8x16, Iop_INVALID, Iop_INVALID, Iop_INVALID };
      Bool zeroHI = False;
      const HChar* arrSpec = "";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2 );
      vassert(szBlg2 < 4);
      IROp opACC = Iop_INVALID;
      IROp opMUL = Iop_INVALID;
      if (ok) {
         opMUL = (bit29 == 1 && !isMLAS) ? opsPMUL[szBlg2]
                                         : opsMUL[szBlg2];
         opACC = isMLAS ? (bit29 == 1 ? opsSUB[szBlg2] : opsADD[szBlg2])
                        : Iop_INVALID;
      }
      if (ok && opMUL != Iop_INVALID) {
         IRTemp t1 = newTemp(Ity_V128);
         assign(t1, binop(opMUL, getQReg128(nn), getQReg128(mm)));
         IRTemp t2 = newTemp(Ity_V128);
         assign(t2, opACC == Iop_INVALID
                       ? mkexpr(t1)
                       : binop(opACC, getQReg128(dd), mkexpr(t1)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t2))
                               : mkexpr(t2));
         const HChar* nm = isMLAS ? (bit29 == 1 ? "mls" : "mla")
                                  : (bit29 == 1 ? "pmul" : "mul");
         DIP("%s %s.%s, %s.%s, %s.%s\n", nm,
             nameQReg128(dd), arrSpec, 
             nameQReg128(nn), arrSpec, nameQReg128(mm), arrSpec);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(28,24) == BITS5(0,1,1,1,0)
       && INSN(21,21) == 1
       && ((INSN(15,10) & BITS6(1,1,1,1,0,1)) == BITS6(0,1,1,0,0,1))) {
      Bool isQ    = INSN(30,30) == 1;
      Bool isU    = INSN(29,29) == 1;
      UInt szBlg2 = INSN(23,22);
      Bool isMAX  = INSN(11,11) == 0;
      UInt mm     = INSN(20,16);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool zeroHI = False;
      const HChar* arrSpec = "";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2 );
      if (ok) {
         const IROp opMINS[4]
            = { Iop_Min8Sx16, Iop_Min16Sx8, Iop_Min32Sx4, Iop_Min64Sx2 };
         const IROp opMINU[4]
            = { Iop_Min8Ux16, Iop_Min16Ux8, Iop_Min32Ux4, Iop_Min64Ux2 };
         const IROp opMAXS[4]
            = { Iop_Max8Sx16, Iop_Max16Sx8, Iop_Max32Sx4, Iop_Max64Sx2 };
         const IROp opMAXU[4]
            = { Iop_Max8Ux16, Iop_Max16Ux8, Iop_Max32Ux4, Iop_Max64Ux2 };
         vassert(szBlg2 < 4);
         IROp op = isMAX ? (isU ? opMAXU[szBlg2] : opMAXS[szBlg2])
                         : (isU ? opMINU[szBlg2] : opMINS[szBlg2]);
         IRTemp t = newTemp(Ity_V128);
         assign(t, binop(op, getQReg128(nn), getQReg128(mm)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(t))
                               : mkexpr(t));
         const HChar* nm = isMAX ? (isU ? "umax" : "smax")
                                 : (isU ? "umin" : "smin");
         DIP("%s %s.%s, %s.%s, %s.%s\n", nm,
             nameQReg128(dd), arrSpec, 
             nameQReg128(nn), arrSpec, nameQReg128(mm), arrSpec);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(28,24) == BITS5(0,1,1,1,0)
       && INSN(21,17) == BITS5(1,1,0,0,0)
       && INSN(15,10) == BITS6(1,0,1,0,1,0)) {
      Bool isQ    = INSN(30,30) == 1;
      Bool isU    = INSN(29,29) == 1;
      UInt szBlg2 = INSN(23,22);
      Bool isMAX  = INSN(16,16) == 0;
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool zeroHI = False;
      const HChar* arrSpec = "";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2);
      if (ok) {
         if (szBlg2 == 3)         ok = False;
         if (szBlg2 == 2 && !isQ) ok = False;
      }
      if (ok) {
         const IROp opMINS[3]
            = { Iop_Min8Sx16, Iop_Min16Sx8, Iop_Min32Sx4 };
         const IROp opMINU[3]
            = { Iop_Min8Ux16, Iop_Min16Ux8, Iop_Min32Ux4 };
         const IROp opMAXS[3]
            = { Iop_Max8Sx16, Iop_Max16Sx8, Iop_Max32Sx4 };
         const IROp opMAXU[3]
            = { Iop_Max8Ux16, Iop_Max16Ux8, Iop_Max32Ux4 };
         vassert(szBlg2 < 3);
         IROp op = isMAX ? (isU ? opMAXU[szBlg2] : opMAXS[szBlg2])
                         : (isU ? opMINU[szBlg2] : opMINS[szBlg2]);
         IRTemp tN1 = newTemp(Ity_V128);
         assign(tN1, getQReg128(nn));
         IRTemp tN2 = newTemp(Ity_V128);
         assign(tN2, zeroHI ? mk_CatEvenLanes64x2(tN1,tN1) : mkexpr(tN1));
         IRTemp res = math_MINMAXV(tN2, op);
         if (res == IRTemp_INVALID)
            return False; 
         putQReg128(dd, mkexpr(res));
         const HChar* nm = isMAX ? (isU ? "umaxv" : "smaxv")
                                 : (isU ? "uminv" : "sminv");
         const IRType tys[3] = { Ity_I8, Ity_I16, Ity_I32 };
         IRType laneTy = tys[szBlg2];
         DIP("%s %s, %s.%s\n", nm,
             nameQRegLO(dd, laneTy), nameQReg128(nn), arrSpec);
         return True;
      }
      
   }
   
   if (INSN(31,24) == BITS8(0,0,1,0,1,1,1,0) && INSN(23,22) != BITS2(1,1)
       && INSN(21,21) == 1 && INSN(15,10) == BITS6(1,1,0,0,0,0)) {
      UInt mm = INSN(20,16);
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      UInt sz = INSN(23,22);

      const HChar* nameTa[3] = { "8h", "4s", "2d" };
      const HChar* nameTb[3] = { "8b", "4h", "2s" };
      const IROp ops[3] = { Iop_Mull8Ux8, Iop_Mull16Ux4, Iop_Mull32Ux2 };

      putQReg128(dd, binop(ops[sz], getQRegLO(nn, Ity_I64), getQRegLO(mm, Ity_I64)));

      DIP("umull %s.%s, %s.%s, %s.%s\n", nameQReg128(dd), nameTa[sz],
          nameQReg128(nn), nameTb[sz], nameQReg128(mm), nameTb[sz]);
      return True;
   }


   
   if (INSN(31,31) == 0 && INSN(29,24) == BITS6(0,0,1,1,1,0)
       && INSN(21,21) == 1 && INSN(15,10) == BITS6(0,0,0,1,1,1)) {
      Bool   isQ    = INSN(30,30) == 1;
      Bool   isORR  = INSN(23,23) == 1;
      Bool   invert = INSN(22,22) == 1;
      UInt   mm     = INSN(20,16);
      UInt   nn     = INSN(9,5);
      UInt   dd     = INSN(4,0);
      IRTemp res    = newTemp(Ity_V128);
      assign(res, binop(isORR ? Iop_OrV128 : Iop_AndV128,
                        getQReg128(nn),
                        invert ? unop(Iop_NotV128, getQReg128(mm))
                               : getQReg128(mm)));
      putQReg128(dd, isQ ? mkexpr(res)
                         : unop(Iop_ZeroHI64ofV128, mkexpr(res)));
      const HChar* names[4] = { "and", "bic", "orr", "orn" };
      const HChar* ar = isQ ? "16b" : "8b";
      DIP("%s %s.%s, %s.%s, %s.%s\n", names[INSN(23,22)],
          nameQReg128(dd), ar, nameQReg128(nn), ar, nameQReg128(mm), ar);
      return True;
   }

   
   if (INSN(31,31) == 0
       && INSN(28,24) == BITS5(0,1,1,1,0) && INSN(21,21) == 1) {
      Bool isQ    = INSN(30,30) == 1;
      UInt bit29  = INSN(29,29);
      UInt szBlg2 = INSN(23,22);
      UInt mm     = INSN(20,16);
      UInt b1510  = INSN(15,10);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      const IROp opsEQ[4]
         = { Iop_CmpEQ8x16,  Iop_CmpEQ16x8,  Iop_CmpEQ32x4,  Iop_CmpEQ64x2 };
      const IROp opsGTS[4]
         = { Iop_CmpGT8Sx16, Iop_CmpGT16Sx8, Iop_CmpGT32Sx4, Iop_CmpGT64Sx2 };
      const IROp opsGTU[4]
         = { Iop_CmpGT8Ux16, Iop_CmpGT16Ux8, Iop_CmpGT32Ux4, Iop_CmpGT64Ux2 };
      Bool zeroHI = False;
      const HChar* arrSpec = "??";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2);
      UInt ix = 0;
      if (ok) {
         switch (b1510) {
            case BITS6(1,0,0,0,1,1): ix = bit29 ? 1 : 2; break;
            case BITS6(0,0,1,1,0,1): ix = bit29 ? 3 : 4; break;
            case BITS6(0,0,1,1,1,1): ix = bit29 ? 5 : 6; break;
            case BITS6(1,0,0,0,1,0):
               if (mm == 0) { ix = bit29 ? 7 : 8; }; break;
            case BITS6(1,0,0,1,1,0):
               if (mm == 0) { ix = bit29 ? 9 : 10; }; break;
            case BITS6(1,0,1,0,1,0):
               if (mm == 0 && bit29 == 0) { ix = 11; }; break;
            default: break;
         }
      }
      if (ix != 0) {
         vassert(ok && szBlg2 < 4);
         IRExpr* argL = getQReg128(nn);
         IRExpr* argR = (ix <= 6) ? getQReg128(mm) : mkV128(0x0000);
         IRExpr* res  = NULL;
         switch (ix) {
            case 1: res = binop(opsEQ[szBlg2], argL, argR); break;
            case 2: res = unop(Iop_NotV128, binop(opsEQ[szBlg2],
                                            binop(Iop_AndV128, argL, argR), 
                                                  mkV128(0x0000)));
                    break;
            case 3: res = binop(opsGTU[szBlg2], argL, argR); break;
            case 4: res = binop(opsGTS[szBlg2], argL, argR); break;
            case 5: res = unop(Iop_NotV128, binop(opsGTU[szBlg2], argR, argL));
                    break;
            case 6: res = unop(Iop_NotV128, binop(opsGTS[szBlg2], argR, argL));
                    break;
            case 7: res = unop(Iop_NotV128, binop(opsGTS[szBlg2], argR, argL));
                    break;
            case 8: res = binop(opsGTS[szBlg2], argL, argR); break;
            case 9: res = unop(Iop_NotV128,
                               binop(opsGTS[szBlg2], argL, argR));
                    break;
            case 10: res = binop(opsEQ[szBlg2],  argL, argR); break;
            case 11: res = binop(opsGTS[szBlg2], argR, argL); break;
            default: vassert(0);
         }
         vassert(res);
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, res) : res);
         const HChar* nms[11] = { "eq", "tst", "hi", "gt", "hs", "ge",
                                  "ge", "gt", "le", "eq", "lt" };
         if (ix <= 6) {
            DIP("cm%s %s.%s, %s.%s, %s.%s\n", nms[ix-1],
                nameQReg128(dd), arrSpec,
                nameQReg128(nn), arrSpec, nameQReg128(mm), arrSpec);
         } else {
            DIP("cm%s %s.%s, %s.%s, #0\n", nms[ix-1],
                nameQReg128(dd), arrSpec, nameQReg128(nn), arrSpec);
         }
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(29,24) == BITS6(1,0,1,1,1,0)
       && INSN(21,21) == 1 && INSN(15,10) == BITS6(0,0,0,1,1,1)) {
      Bool   isQ  = INSN(30,30) == 1;
      UInt   op   = INSN(23,22);
      UInt   mm   = INSN(20,16);
      UInt   nn   = INSN(9,5);
      UInt   dd   = INSN(4,0);
      IRTemp argD = newTemp(Ity_V128);
      IRTemp argN = newTemp(Ity_V128);
      IRTemp argM = newTemp(Ity_V128);
      assign(argD, getQReg128(dd));
      assign(argN, getQReg128(nn));
      assign(argM, getQReg128(mm));
      const IROp opXOR = Iop_XorV128;
      const IROp opAND = Iop_AndV128;
      const IROp opNOT = Iop_NotV128;
      IRExpr* res = NULL;
      switch (op) {
         case BITS2(0,0): 
            res = binop(opXOR, mkexpr(argM), mkexpr(argN));
            break;
         case BITS2(0,1): 
            res = binop(opXOR, mkexpr(argM),
                               binop(opAND,
                                     binop(opXOR, mkexpr(argM), mkexpr(argN)),
                                     mkexpr(argD)));
            break;
         case BITS2(1,0): 
            res = binop(opXOR, mkexpr(argD),
                               binop(opAND,
                                     binop(opXOR, mkexpr(argD), mkexpr(argN)),
                                     mkexpr(argM)));
            break;
         case BITS2(1,1): 
            res = binop(opXOR, mkexpr(argD),
                               binop(opAND,
                                     binop(opXOR, mkexpr(argD), mkexpr(argN)),
                                     unop(opNOT, mkexpr(argM))));
            break;
         default:
            vassert(0);
      }
      vassert(res);
      putQReg128(dd, isQ ? res : unop(Iop_ZeroHI64ofV128, res));
      const HChar* nms[4] = { "eor", "bsl", "bit", "bif" };
      const HChar* arr = isQ ? "16b" : "8b";
      vassert(op < 4);
      DIP("%s %s.%s, %s.%s, %s.%s\n", nms[op],
          nameQReg128(dd), arr, nameQReg128(nn), arr, nameQReg128(mm), arr);
      return True;
   }

   
   if (INSN(31,23) == BITS9(0,1,1, 1,1,1,1,1,0)
       && INSN(15,10) == BITS6(0,0,0,0,0,1)) {
      UInt immh = INSN(22,19);
      UInt immb = INSN(18,16);
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);

      UInt szBlg2 = 0;
      UInt shift  = 0;
      Bool ok     = getLaneInfo_IMMH_IMMB(&shift, &szBlg2, immh, immb);

      if (szBlg2 == 3) {
         putQRegHI64(dd, mkU64(0x0));
         putQRegLO(dd, binop(Iop_Shr64, getQRegLO(nn, Ity_I64), mkU8(shift)));
         DIP("ushr %s, %s\n", nameQRegLO(dd, Ity_I64), nameQRegLO(nn, Ity_I64));
         return True;
      }
   }
   
   if (INSN(31,31) == 0 && INSN(28,23) == BITS6(0,1,1,1,1,0)
       && INSN(10,10) == 1) {
      UInt ix = 0;
       if (INSN(29,29) == 1 && INSN(15,11) == BITS5(0,0,0,0,0)) ix = 1;
      else if (INSN(29,29) == 1 && INSN(15,11) == BITS5(0,1,0,0,0)) ix = 1;
      else if (INSN(29,29) == 0 && INSN(15,11) == BITS5(0,0,0,0,0)) ix = 2;
      else if (                    INSN(15,11) == BITS5(0,1,0,1,0)) ix = 3;
      if (ix > 0) {
         Bool isQ  = INSN(30,30) == 1;
         UInt immh = INSN(22,19);
         UInt immb = INSN(18,16);
         UInt nn   = INSN(9,5);
         UInt dd   = INSN(4,0);
         Bool isInsert = (ix == 3 && INSN(29,29) == 1)
                         || (INSN(29,29) == 1 && INSN(15,11) == BITS5(0,1,0,0,0));

         const IROp opsSHRN[4]
            = { Iop_ShrN8x16, Iop_ShrN16x8, Iop_ShrN32x4, Iop_ShrN64x2 };
         const IROp opsSARN[4]
            = { Iop_SarN8x16, Iop_SarN16x8, Iop_SarN32x4, Iop_SarN64x2 };
         const IROp opsSHLN[4]
            = { Iop_ShlN8x16, Iop_ShlN16x8, Iop_ShlN32x4, Iop_ShlN64x2 };
         UInt szBlg2 = 0;
         UInt shift  = 0;
         Bool ok     = getLaneInfo_IMMH_IMMB(&shift, &szBlg2, immh, immb);
         if (ix == 3) {
            shift = (8 << szBlg2) - shift;
         }
         if (ok && szBlg2 < 4 && shift >= 0 && shift <= (8 << szBlg2)
             && !(szBlg2 == 3 && !isQ)) {
            IROp op = Iop_INVALID;
            const HChar* nm = NULL;
            switch (ix) {
               case 1: op = opsSHRN[szBlg2]; nm = isInsert ? "sri" : "ushr"; break;
               case 2: op = opsSARN[szBlg2]; nm = "sshr"; break;
               case 3: op = opsSHLN[szBlg2]; nm = isInsert ? "sli" : "shl";  break;
               default: vassert(0);
            }
            IRTemp mask = newTemp(Ity_V128);
            IRTemp res;
            IRTemp candidate  = newTemp(Ity_V128);

            assign(candidate, binop(op, getQReg128(nn), mkU8(shift)));

            if (isInsert) {
              assign(mask, binop(op,
                                 binop(Iop_64HLtoV128,
                                       mkU64(0xFFFFFFFFFFFFFFFFULL),
                                       mkU64(0xFFFFFFFFFFFFFFFFULL)),
                                 mkU8(shift)));
              res = newTemp(Ity_V128);

              assign(res, binop(Iop_OrV128,
                                binop(Iop_AndV128,
                                      unop(Iop_NotV128, mkexpr(mask)),
                                      getQReg128(dd)),
                                mkexpr(candidate)));
            } else {
               res = candidate;
            }

            putQReg128(dd, isQ ? mkexpr(res) : unop(Iop_ZeroHI64ofV128, mkexpr(res)));
            HChar laneCh = "bhsd"[szBlg2];
            UInt  nLanes = (isQ ? 128 : 64) / (8 << szBlg2);
            DIP("%s %s.%u%c, %s.%u%c, #%u\n", nm,
                nameQReg128(dd), nLanes, laneCh,
                nameQReg128(nn), nLanes, laneCh, shift);
            return True;
         }
         
      }
   }

   

   if (INSN(31,31) == 0 && INSN(28,23) == BITS6(0,1,1,1,1,0)
       && INSN(15,10) == BITS6(1,0,0,0,0,1)) {
      Bool isQ = INSN(30,30) == 1;
      UInt immh  = INSN(22,19);
      UInt immb  = INSN(18,16);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      IRTemp  src  = newTemp(Ity_V128);
      IRTemp  zero = newTemp(Ity_V128);
      IRExpr* res  = NULL;
      const HChar* ta = "??";
      const HChar* tb = "??";

      UInt szBlg2 = 0;
      UInt shift  = 0;
      Bool ok     = getLaneInfo_IMMH_IMMB(&shift, &szBlg2, immh, immb);

      if (ok && shift >= 0 && szBlg2 < 3 && shift <= (8 << szBlg2)) {
         const IROp opsSHR[3] = { Iop_ShrN16x8, Iop_ShrN32x4, Iop_ShrN64x2 };
         const HChar* tas[3] = { "8h", "4s", "2d" };
         const HChar* tbs_q0[3] = { "8b", "4h", "2s" };
         const HChar* tbs_q1[3] = { "16b", "8h", "4s" };
         assign(src, binop(opsSHR[szBlg2], getQReg128(nn), mkU8(shift)));
         assign(zero, mkV128(0x0000));
         switch(szBlg2) {
            case 0:
               res = mk_CatEvenLanes8x16(zero, src);
               break;
            case 1:
               res = mk_CatEvenLanes16x8(zero, src);
               break;
            case 2:
               res = mk_CatEvenLanes32x4(zero, src);
               break;
            default:
               break;
         }

         if (res != NULL) {
            if (isQ) {
               putQRegHI64(dd, unop(Iop_V128to64, res));
            } else {
               putQReg128(dd, res);
            }
            DIP("shrn%s %s.%s, %s.%s, #%d\n",
                isQ ? "2" : "", nameQReg128(dd), isQ ? tbs_q1[szBlg2] : tbs_q0[szBlg2],
                nameQReg128(nn), tas[szBlg2], shift);
            return True;
         }
      }
   }

   
   if (INSN(31,31) == 0 && INSN(28,23) == BITS6(0,1,1,1,1,0)
       && INSN(15,10) == BITS6(1,0,1,0,0,1)) {
      Bool isQ   = INSN(30,30) == 1;
      Bool isU   = INSN(29,29) == 1;
      UInt immh  = INSN(22,19);
      UInt immb  = INSN(18,16);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      UInt immhb = (immh << 3) | immb;
      IRTemp  src  = newTemp(Ity_V128);
      IRTemp  zero = newTemp(Ity_V128);
      IRExpr* res  = NULL;
      UInt    sh   = 0;
      const HChar* ta = "??";
      const HChar* tb = "??";
      assign(src, getQReg128(nn));
      assign(zero, mkV128(0x0000));
      if (immh & 8) {
         
      }
      else if (immh & 4) {
         sh = immhb - 32;
         vassert(sh < 32); 
         ta = "2d";
         tb = isQ ? "4s" : "2s";
         IRExpr* tmp = isQ ? mk_InterleaveHI32x4(src, zero) 
                           : mk_InterleaveLO32x4(src, zero);
         res = binop(isU ? Iop_ShrN64x2 : Iop_SarN64x2, tmp, mkU8(32-sh));
      }
      else if (immh & 2) {
         sh = immhb - 16;
         vassert(sh < 16); 
         ta = "4s";
         tb = isQ ? "8h" : "4h";
         IRExpr* tmp = isQ ? mk_InterleaveHI16x8(src, zero) 
                           : mk_InterleaveLO16x8(src, zero);
         res = binop(isU ? Iop_ShrN32x4 : Iop_SarN32x4, tmp, mkU8(16-sh));
      }
      else if (immh & 1) {
         sh = immhb - 8;
         vassert(sh < 8); 
         ta = "8h";
         tb = isQ ? "16b" : "8b";
         IRExpr* tmp = isQ ? mk_InterleaveHI8x16(src, zero) 
                           : mk_InterleaveLO8x16(src, zero);
         res = binop(isU ? Iop_ShrN16x8 : Iop_SarN16x8, tmp, mkU8(8-sh));
      } else {
         vassert(immh == 0);
         
      }
      
      if (res) {
         putQReg128(dd, res);
         DIP("%cshll%s %s.%s, %s.%s, #%d\n",
             isU ? 'u' : 's', isQ ? "2" : "",
             nameQReg128(dd), ta, nameQReg128(nn), tb, sh);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(29,24) == BITS6(0,0,1,1,1,0)
       && INSN(21,16) == BITS6(1,0,0,0,0,1)
       && INSN(15,10) == BITS6(0,0,1,0,1,0)) {
      Bool isQ  = INSN(30,30) == 1;
      UInt size = INSN(23,22);
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);
      IROp op   = Iop_INVALID;
      const HChar* tb = NULL;
      const HChar* ta = NULL;
      switch ((size << 1) | (isQ ? 1 : 0)) {
         case 0: tb = "8b";  ta = "8h"; op = Iop_NarrowUn16to8x8;  break;
         case 1: tb = "16b"; ta = "8h"; op = Iop_NarrowUn16to8x8;  break;
         case 2: tb = "4h";  ta = "4s"; op = Iop_NarrowUn32to16x4; break;
         case 3: tb = "8h";  ta = "4s"; op = Iop_NarrowUn32to16x4; break;
         case 4: tb = "2s";  ta = "2d"; op = Iop_NarrowUn64to32x2; break;
         case 5: tb = "4s";  ta = "2d"; op = Iop_NarrowUn64to32x2; break;
         case 6: break;
         case 7: break;
         default: vassert(0);
      }
      if (op != Iop_INVALID) {
         if (!isQ) {
            putQRegLane(dd, 1, mkU64(0));
         }
         putQRegLane(dd, isQ ? 1 : 0, unop(op, getQReg128(nn)));
         DIP("xtn%s %s.%s, %s.%s\n", isQ ? "2" : "",
             nameQReg128(dd), tb, nameQReg128(nn), ta);
         return True;
      }
      
   }

   

  if (INSN(31,31) == 0 && INSN(29,24) == BITS6(0,0,1,1,1,0)
      && INSN(23,22) == BITS2(0,0)
      && INSN(21,10) == BITS12(1,0,0,0,0,0,0,1,0,1,1,0) ) {
     Bool isQ = INSN(30,30) == 1;
     UInt nn  = INSN(9,5);
     UInt dd  = INSN(4,0);
     const HChar* name = isQ ? "16b" : "8b";

     IRExpr* res = unop(Iop_Cnt8x16, getQReg128(nn));
     putQReg128(dd, isQ ? res : unop(Iop_ZeroHI64ofV128, res));

     DIP("cnt %s.%s, %s.%s\n", nameQReg128(dd), name, nameQReg128(nn), name);
     return True;
  }


   
   if (INSN(31,31) == 0 && INSN(29,21) == BITS9(0,0,1,1,1,0,0,0,0)
       && INSN(15,10) == BITS6(0,0,0,0,0,1)) {
      Bool   isQ  = INSN(30,30) == 1;
      UInt   imm5 = INSN(20,16);
      UInt   nn   = INSN(9,5);
      UInt   dd   = INSN(4,0);
      IRTemp w0   = newTemp(Ity_I64);
      const HChar* arT  = "??";
      const HChar* arTs = "??";
      IRType laneTy = Ity_INVALID;
      UInt   laneNo = 16; 
      if (imm5 & 1) {
         arT    = isQ ? "16b" : "8b";
         arTs   = "b";
         laneNo = (imm5 >> 1) & 15;
         laneTy = Ity_I8;
         assign(w0, unop(Iop_8Uto64, getQRegLane(nn, laneNo, laneTy)));
      }
      else if (imm5 & 2) {
         arT    = isQ ? "8h" : "4h";
         arTs   = "h";
         laneNo = (imm5 >> 2) & 7;
         laneTy = Ity_I16;
         assign(w0, unop(Iop_16Uto64, getQRegLane(nn, laneNo, laneTy)));
      }
      else if (imm5 & 4) {
         arT    = isQ ? "4s" : "2s";
         arTs   = "s";
         laneNo = (imm5 >> 3) & 3;
         laneTy = Ity_I32;
         assign(w0, unop(Iop_32Uto64, getQRegLane(nn, laneNo, laneTy)));
      }
      else if ((imm5 & 8) && isQ) {
         arT  = "2d";
         arTs = "d";
         laneNo = (imm5 >> 4) & 1;
         laneTy = Ity_I64;
         assign(w0, getQRegLane(nn, laneNo, laneTy));
      }
      else {
         
      }
      
      if (laneTy != Ity_INVALID) {
         vassert(laneNo < 16);
         IRTemp w1 = math_DUP_TO_64(w0, laneTy);
         putQReg128(dd, binop(Iop_64HLtoV128,
                              isQ ? mkexpr(w1) : mkU64(0), mkexpr(w1)));
         DIP("dup %s.%s, %s.%s[%u]\n",
             nameQReg128(dd), arT, nameQReg128(nn), arTs, laneNo);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(29,21) == BITS9(0,0,1,1,1,0,0,0,0)
       && INSN(15,10) == BITS6(0,0,0,0,1,1)) {
      Bool   isQ  = INSN(30,30) == 1;
      UInt   imm5 = INSN(20,16);
      UInt   nn   = INSN(9,5);
      UInt   dd   = INSN(4,0);
      IRTemp w0   = newTemp(Ity_I64);
      const HChar* arT = "??";
      IRType laneTy = Ity_INVALID;
      if (imm5 & 1) {
         arT    = isQ ? "16b" : "8b";
         laneTy = Ity_I8;
         assign(w0, unop(Iop_8Uto64, unop(Iop_64to8, getIReg64orZR(nn))));
      }
      else if (imm5 & 2) {
         arT    = isQ ? "8h" : "4h";
         laneTy = Ity_I16;
         assign(w0, unop(Iop_16Uto64, unop(Iop_64to16, getIReg64orZR(nn))));
      }
      else if (imm5 & 4) {
         arT    = isQ ? "4s" : "2s";
         laneTy = Ity_I32;
         assign(w0, unop(Iop_32Uto64, unop(Iop_64to32, getIReg64orZR(nn))));
      }
      else if ((imm5 & 8) && isQ) {
         arT    = "2d";
         laneTy = Ity_I64;
         assign(w0, getIReg64orZR(nn));
      }
      else {
         
      }
      
      if (laneTy != Ity_INVALID) {
         IRTemp w1 = math_DUP_TO_64(w0, laneTy);
         putQReg128(dd, binop(Iop_64HLtoV128,
                              isQ ? mkexpr(w1) : mkU64(0), mkexpr(w1)));
         DIP("dup %s.%s, %s\n",
             nameQReg128(dd), arT, nameIRegOrZR(laneTy == Ity_I64, nn));
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(28, 24) == BITS5(0,1,1,1,0)
       && INSN(21, 10) == BITS12(1,1,0,0,0,0,0,0,1,1,1,0)) {
      UInt bitQ = INSN(30,30);
      UInt bitU = INSN(29,29);
      UInt sz   = INSN(23,22);
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);

      Bool valid = !((sz == BITS2(1,1)) || (bitQ == 0 && sz == BITS2(1,0)));
      if (valid) {
        const IRType ddTypes[3] = { Ity_I16, Ity_I32, Ity_I64 };
        const HChar* suffixesQ[3] = { "16b", "8h", "4s" };
        const HChar* suffixesq[3] = { "8b", "4h", "invalid" };

        IRTemp src = newTemp(Ity_V128);
        IRExpr* half = mkU64(0xFFFFFFFFFFFFFFFFULL);
        IRExpr* zero = mkU64(0x0);

        IRExpr* mask = binop(Iop_64HLtoV128, zero, half);
        assign(src, bitQ ? getQReg128(nn) : binop(Iop_AndV128, getQReg128(nn), mask));

        IROp op;
        switch (sz) {
        case BITS2(0,0): op = bitU ? Iop_AddLV8Ux16 : Iop_AddLV8Sx16; break;
        case BITS2(0,1): op = bitU ? Iop_AddLV16Ux8 : Iop_AddLV16Sx8; break;
        case BITS2(1,0): op = bitU ? Iop_AddLV32Ux4 : Iop_AddLV32Sx4; break;
        default: vassert(0);
        }

        putQReg128(dd, unop(op, mkexpr(src)));

        DIP("%saddlv %s,%s.%s\n", bitU ? "u" : "s", nameQRegLO(dd, ddTypes[sz]),
            nameQReg128(nn), bitQ ? suffixesQ[sz] : suffixesq[sz]);

        return True;
      }
      
   }
   
   if (INSN(31,31) == 0 && INSN(29,21) == BITS9(0,0,1,1,1,0,0,0,0)
       && (INSN(15,10) & BITS6(1,1,1,0,1,1)) == BITS6(0,0,1,0,1,1)) {
      UInt bitQ = INSN(30,30) == 1;
      UInt imm5 = INSN(20,16);
      UInt nn   = INSN(9,5);
      UInt dd   = INSN(4,0);
      Bool isU  = INSN(12,12) == 1;
      const HChar* arTs = "??";
      UInt    laneNo = 16; 
      
      IRExpr* res    = NULL;
      if (!bitQ && (imm5 & 1)) { 
         laneNo = (imm5 >> 1) & 15;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I8);
         res = isU ? unop(Iop_8Uto64, lane)
                   : unop(Iop_32Uto64, unop(Iop_8Sto32, lane));
         arTs = "b";
      }
      else if (bitQ && (imm5 & 1)) { 
         laneNo = (imm5 >> 1) & 15;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I8);
         res = isU ? NULL
                   : unop(Iop_8Sto64, lane);
         arTs = "b";
      }
      else if (!bitQ && (imm5 & 2)) { 
         laneNo = (imm5 >> 2) & 7;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I16);
         res = isU ? unop(Iop_16Uto64, lane)
                   : unop(Iop_32Uto64, unop(Iop_16Sto32, lane));
         arTs = "h";
      }
      else if (bitQ && (imm5 & 2)) { 
         laneNo = (imm5 >> 2) & 7;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I16);
         res = isU ? NULL
                   : unop(Iop_16Sto64, lane);
         arTs = "h";
      }
      else if (!bitQ && (imm5 & 4)) { 
         laneNo = (imm5 >> 3) & 3;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I32);
         res = isU ? unop(Iop_32Uto64, lane)
                   : NULL;
         arTs = "s";
      }
      else if (bitQ && (imm5 & 4)) { 
         laneNo = (imm5 >> 3) & 3;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I32);
         res = isU ? NULL
                   : unop(Iop_32Sto64, lane);
         arTs = "s";
      }
      else if (bitQ && (imm5 & 8)) { 
         laneNo = (imm5 >> 4) & 1;
         IRExpr* lane = getQRegLane(nn, laneNo, Ity_I64);
         res = isU ? lane
                   : NULL;
         arTs = "d";
      }
      
      if (res) {
         vassert(laneNo < 16);
         putIReg64orZR(dd, res);
         DIP("%cmov %s, %s.%s[%u]\n", isU ? 'u' : 's',
             nameIRegOrZR(bitQ == 1, dd),
             nameQReg128(nn), arTs, laneNo);
         return True;
      }
      
   }

   
   if (INSN(31,21) == BITS11(0,1,0,0,1,1,1,0,0,0,0)
       && INSN(15,10) == BITS6(0,0,0,1,1,1)) {
      UInt    imm5   = INSN(20,16);
      UInt    nn     = INSN(9,5);
      UInt    dd     = INSN(4,0);
      HChar   ts     = '?';
      UInt    laneNo = 16;
      IRExpr* src    = NULL;
      if (imm5 & 1) {
         src    = unop(Iop_64to8, getIReg64orZR(nn));
         laneNo = (imm5 >> 1) & 15;
         ts     = 'b';
      }
      else if (imm5 & 2) {
         src    = unop(Iop_64to16, getIReg64orZR(nn));
         laneNo = (imm5 >> 2) & 7;
         ts     = 'h';
      }
      else if (imm5 & 4) {
         src    = unop(Iop_64to32, getIReg64orZR(nn));
         laneNo = (imm5 >> 3) & 3;
         ts     = 's';
      }
      else if (imm5 & 8) {
         src    = getIReg64orZR(nn);
         laneNo = (imm5 >> 4) & 1;
         ts     = 'd';
      }
      
      if (src) {
         vassert(laneNo < 16);
         putQRegLane(dd, laneNo, src);
         DIP("ins %s.%c[%u], %s\n",
             nameQReg128(dd), ts, laneNo, nameIReg64orZR(nn));
         return True;
      }
      
   }

   
   if (INSN(31,21) == BITS11(0,1,1,0,1,1,1,0,0,0,0)
       && INSN(15,15) == 0 && INSN(10,10) == 1 ) {
      UInt   imm5      = INSN(20,16);
      UInt   imm4      = INSN(14,11);
      UInt   nn        = INSN(9,5);
      UInt   dd        = INSN(4,0);
      HChar  ts        = '?';
      IRType ty        = Ity_INVALID;
      UInt   srcLaneNo = 16;
      UInt   dstLaneNo = 16;

      if (imm5 & 1) {
         srcLaneNo = imm4;
         dstLaneNo = imm5 >> 1;
         ty = Ity_I8;
         ts = 'b';
      } else if (imm5 & 2) {
         srcLaneNo = imm4 >> 1;
         dstLaneNo = imm5 >> 2;
         ty = Ity_I16;
         ts = 'h';
      } else if (imm5 & 4) {
         srcLaneNo = imm4 >> 2;
         dstLaneNo = imm5 >> 3;
         ty = Ity_I32;
         ts = 's';
      } else if (imm5 & 8) {
         srcLaneNo = imm4 >> 3;
         dstLaneNo = imm5 >> 4;
         ty = Ity_I64;
         ts = 'd';
      }

      if (ty != Ity_INVALID) {
         vassert(srcLaneNo < 16);
         vassert(dstLaneNo < 16);
         putQRegLane(dd, dstLaneNo, getQRegLane(nn, srcLaneNo, ty));
         DIP("ins %s.%c[%u], %s.%c[%u]\n", 
             nameQReg128(dd), ts, dstLaneNo, nameQReg128(nn), ts, dstLaneNo);
         return True;
      }

   }

   
   if (INSN(31,31) == 0 && INSN(29,24) == BITS6(1,0,1,1,1,0)
       && INSN(21,10) == BITS12(1,0,0,0,0,0,1,0,1,1,1,0)) {
      Bool isQ    = INSN(30,30) == 1;
      UInt szBlg2 = INSN(23,22);
      UInt nn     = INSN(9,5);
      UInt dd     = INSN(4,0);
      Bool zeroHI = False;
      const HChar* arrSpec = "";
      Bool ok = getLaneInfo_SIMPLE(&zeroHI, &arrSpec, isQ, szBlg2 );
      if (ok) {
         const IROp opSUB[4]
            = { Iop_Sub8x16, Iop_Sub16x8, Iop_Sub32x4, Iop_Sub64x2 };
         IRTemp res = newTemp(Ity_V128);
         vassert(szBlg2 < 4);
         assign(res, binop(opSUB[szBlg2], mkV128(0x0000), getQReg128(nn)));
         putQReg128(dd, zeroHI ? unop(Iop_ZeroHI64ofV128, mkexpr(res))
                               : mkexpr(res));
         DIP("neg %s.%s, %s.%s\n",
             nameQReg128(dd), arrSpec, nameQReg128(nn), arrSpec);
         return True;
      }
      
   }

   
   if (INSN(31,31) == 0 && INSN(29,21) == BITS9(0,0,1,1,1,0,0,0,0)
       && INSN(15,15) == 0 && INSN(11,10) == BITS2(0,0)) {
      Bool isQ   = INSN(30,30) == 1;
      Bool isTBX = INSN(12,12) == 1;
      UInt mm    = INSN(20,16);
      UInt len   = INSN(14,13);
      UInt nn    = INSN(9,5);
      UInt dd    = INSN(4,0);
      
      IRTemp oor_values = newTemp(Ity_V128);
      assign(oor_values, isTBX ? getQReg128(dd) : mkV128(0));
      
      IRTemp src = newTemp(Ity_V128);
      assign(src, getQReg128(mm));
      
      IRTemp tab[4];
      UInt   i;
      for (i = 0; i <= len; i++) {
         vassert(i < 4);
         tab[i] = newTemp(Ity_V128);
         assign(tab[i], getQReg128((nn + i) % 32));
      }
      IRTemp res = math_TBL_TBX(tab, len, src, oor_values);
      putQReg128(dd, isQ ? mkexpr(res)
                         : unop(Iop_ZeroHI64ofV128, mkexpr(res)) );
      const HChar* Ta = isQ ? "16b" : "8b";
      const HChar* nm = isTBX ? "tbx" : "tbl";
      DIP("%s %s.%s, {v%d.16b .. v%d.16b}, %s.%s\n",
          nm, nameQReg128(dd), Ta, nn, (nn + len) % 32, nameQReg128(mm), Ta);
      return True;
   }
   

   
   
   if ((insn & 0xFFFFFFE0) == 0x4F000400) {
      UInt vD = INSN(4,0);
      putQReg128(vD, mkV128(0x0000));
      DIP("movi v%u.4s, #0x0\n", vD);
      return True;
   }

   
   if (INSN(31,24) == BITS8(0,1,0,0,1,1,1,0)
       && INSN(23,21) == BITS3(1,0,1) && INSN(15,10) == BITS6(0,0,0,1,1,1)) {
      UInt mm = INSN(20,16);
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      if (mm == nn) {
         putQReg128(dd, getQReg128(nn));
         DIP("mov v%u.16b, v%u.16b\n", dd, nn);
         return True;
      }
      
   }

   
   if ((INSN(31,0) & 0xFFFFFC00) == 0x5EE09800) {
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      putQReg128(dd, unop(Iop_ZeroHI64ofV128,
                          binop(Iop_CmpEQ64x2, getQReg128(nn),
                                mkV128(0x0000))));
      DIP("cmeq d%u, d%u, #0\n", dd, nn);
      return True;
   }

   
   if (INSN(31,22) == BITS10(0,1,0,1,1,1,1,1,0,1)
       && INSN(15,10) == BITS6(0,1,0,1,0,1)) {
      UInt nn = INSN(9,5);
      UInt dd = INSN(4,0);
      UInt sh = INSN(21,16);
      vassert(sh < 64);
      putQReg128(dd, unop(Iop_ZeroHI64ofV128,
                          binop(Iop_ShlN64x2, getQReg128(nn), mkU8(sh))));
      DIP("shl d%u, d%u, #%u\n", dd, nn, sh);
      return True;
   }
   vex_printf("ARM64 front end: simd_and_fp\n");
   return False;
#  undef INSN
}




static
Bool disInstr_ARM64_WRK (
        DisResult* dres,
        Bool         (*resteerOkFn) ( void*, Addr64 ),
        Bool         resteerCisOk,
        void*        callback_opaque,
        UChar*       guest_instr,
        VexArchInfo* archinfo,
        VexAbiInfo*  abiinfo
     )
{
   
#  define INSN(_bMax,_bMin)  SLICE_UInt(insn, (_bMax), (_bMin))


   
   dres->whatNext    = Dis_Continue;
   dres->len         = 4;
   dres->continueAt  = 0;
   dres->jk_StopHere = Ijk_INVALID;

   UInt insn = getUIntLittleEndianly( guest_instr );

   if (0) vex_printf("insn: 0x%x\n", insn);

   DIP("\t(arm64) 0x%llx:  ", (ULong)guest_PC_curr_instr);

   vassert(0 == (guest_PC_curr_instr & 3ULL));

   

   
   {
      UChar* code = (UChar*)guest_instr;
      UInt word1 = 0x93CC0D8C;
      UInt word2 = 0x93CC358C;
      UInt word3 = 0x93CCCD8C;
      UInt word4 = 0x93CCF58C;
      if (getUIntLittleEndianly(code+ 0) == word1 &&
          getUIntLittleEndianly(code+ 4) == word2 &&
          getUIntLittleEndianly(code+ 8) == word3 &&
          getUIntLittleEndianly(code+12) == word4) {
         
         if (getUIntLittleEndianly(code+16) == 0xAA0A014A
                                               ) {
            
            DIP("x3 = client_request ( x4 )\n");
            putPC(mkU64( guest_PC_curr_instr + 20 ));
            dres->jk_StopHere = Ijk_ClientReq;
            dres->whatNext    = Dis_StopHere;
            return True;
         }
         else
         if (getUIntLittleEndianly(code+16) == 0xAA0B016B
                                               ) {
            
            DIP("x3 = guest_NRADDR\n");
            dres->len = 20;
            putIReg64orZR(3, IRExpr_Get( OFFB_NRADDR, Ity_I64 ));
            return True;
         }
         else
         if (getUIntLittleEndianly(code+16) == 0xAA0C018C
                                               ) {
            
            DIP("branch-and-link-to-noredir x8\n");
            putIReg64orZR(30, mkU64(guest_PC_curr_instr + 20));
            putPC(getIReg64orZR(8));
            dres->jk_StopHere = Ijk_NoRedir;
            dres->whatNext    = Dis_StopHere;
            return True;
         }
         else
         if (getUIntLittleEndianly(code+16) == 0xAA090129
                                               ) {
            
            DIP("IR injection\n");
            vex_inject_ir(irsb, Iend_LE);
            
            
            
            
            stmt(IRStmt_Put(OFFB_CMSTART, mkU64(guest_PC_curr_instr)));
            stmt(IRStmt_Put(OFFB_CMLEN,   mkU64(20)));
            putPC(mkU64( guest_PC_curr_instr + 20 ));
            dres->whatNext    = Dis_StopHere;
            dres->jk_StopHere = Ijk_InvalICache;
            return True;
         }
         
         return False;
         
      }
   }

   

   

   Bool ok = False;

   switch (INSN(28,25)) {
      case BITS4(1,0,0,0): case BITS4(1,0,0,1):
         
         ok = dis_ARM64_data_processing_immediate(dres, insn);
         break;
      case BITS4(1,0,1,0): case BITS4(1,0,1,1):
         
         ok = dis_ARM64_branch_etc(dres, insn, archinfo);
         break;
      case BITS4(0,1,0,0): case BITS4(0,1,1,0):
      case BITS4(1,1,0,0): case BITS4(1,1,1,0):
         
         ok = dis_ARM64_load_store(dres, insn);
         break;
      case BITS4(0,1,0,1): case BITS4(1,1,0,1):
         
         ok = dis_ARM64_data_processing_register(dres, insn);
         break;
      case BITS4(0,1,1,1): case BITS4(1,1,1,1): 
         
         ok = dis_ARM64_simd_and_fp(dres, insn);
         break;
      case BITS4(0,0,0,0): case BITS4(0,0,0,1):
      case BITS4(0,0,1,0): case BITS4(0,0,1,1):
         
         break;
      default:
         vassert(0); 
   }

   if (!ok) {
      vassert(dres->whatNext    == Dis_Continue);
      vassert(dres->len         == 4);
      vassert(dres->continueAt  == 0);
      vassert(dres->jk_StopHere == Ijk_INVALID);
   }

   return ok;

#  undef INSN
}




DisResult disInstr_ARM64 ( IRSB*        irsb_IN,
                           Bool         (*resteerOkFn) ( void*, Addr64 ),
                           Bool         resteerCisOk,
                           void*        callback_opaque,
                           UChar*       guest_code_IN,
                           Long         delta_IN,
                           Addr64       guest_IP,
                           VexArch      guest_arch,
                           VexArchInfo* archinfo,
                           VexAbiInfo*  abiinfo,
                           Bool         host_bigendian_IN,
                           Bool         sigill_diag_IN )
{
   DisResult dres;
   vex_bzero(&dres, sizeof(dres));

   
   vassert(guest_arch == VexArchARM64);

   irsb                = irsb_IN;
   host_is_bigendian   = host_bigendian_IN;
   guest_PC_curr_instr = (Addr64)guest_IP;

   
   
   vassert((archinfo->arm64_dMinLine_lg2_szB - 2) <= 15);
   vassert((archinfo->arm64_iMinLine_lg2_szB - 2) <= 15);

   
   Bool ok = disInstr_ARM64_WRK( &dres,
                                 resteerOkFn, resteerCisOk, callback_opaque,
                                 (UChar*)&guest_code_IN[delta_IN],
                                 archinfo, abiinfo );
   if (ok) {
      
      vassert(dres.len == 4 || dres.len == 20);
      switch (dres.whatNext) {
         case Dis_Continue:
            putPC( mkU64(dres.len + guest_PC_curr_instr) );
            break;
         case Dis_ResteerU:
         case Dis_ResteerC:
            putPC(mkU64(dres.continueAt));
            break;
         case Dis_StopHere:
            break;
         default:
            vassert(0);
      }
      DIP("\n");
   } else {
      
      if (sigill_diag_IN) {
         Int   i, j;
         UChar buf[64];
         UInt  insn
                  = getUIntLittleEndianly( (UChar*)&guest_code_IN[delta_IN] );
         vex_bzero(buf, sizeof(buf));
         for (i = j = 0; i < 32; i++) {
            if (i > 0) {
              if ((i & 7) == 0) buf[j++] = ' ';
              else if ((i & 3) == 0) buf[j++] = '\'';
            }
            buf[j++] = (insn & (1<<(31-i))) ? '1' : '0';
         }
         vex_printf("disInstr(arm64): unhandled instruction 0x%08x\n", insn);
         vex_printf("disInstr(arm64): %s\n", buf);
      }

      putPC( mkU64(guest_PC_curr_instr) );
      dres.whatNext    = Dis_StopHere;
      dres.len         = 0;
      dres.continueAt  = 0;
      dres.jk_StopHere = Ijk_NoDecode;
   }
   return dres;
}



static IRExpr* mk_CatEvenLanes64x2 ( IRTemp a10, IRTemp b10 )
{
  
  return binop(Iop_64HLtoV128, unop(Iop_V128to64, mkexpr(a10)),
                               unop(Iop_V128to64, mkexpr(b10)));
}

static IRExpr* mk_CatOddLanes64x2 ( IRTemp a10, IRTemp b10 )
{
  
  return binop(Iop_64HLtoV128, unop(Iop_V128HIto64, mkexpr(a10)),
                               unop(Iop_V128HIto64, mkexpr(b10)));
}



static void breakV128to32s ( IRTemp* out3, IRTemp* out2, IRTemp* out1,
                             IRTemp* out0, IRTemp v128 )
{
  if (out3) *out3 = newTemp(Ity_I64);
  if (out2) *out2 = newTemp(Ity_I64);
  if (out1) *out1 = newTemp(Ity_I64);
  if (out0) *out0 = newTemp(Ity_I64);
  IRTemp hi64 = newTemp(Ity_I64);
  IRTemp lo64 = newTemp(Ity_I64);
  assign(hi64, unop(Iop_V128HIto64, mkexpr(v128)) );
  assign(lo64, unop(Iop_V128to64,   mkexpr(v128)) );
  if (out3) assign(*out3, binop(Iop_Shr64, mkexpr(hi64), mkU8(32)));
  if (out2) assign(*out2, binop(Iop_And64, mkexpr(hi64), mkU64(0xFFFFFFFF)));
  if (out1) assign(*out1, binop(Iop_Shr64, mkexpr(lo64), mkU8(32)));
  if (out0) assign(*out0, binop(Iop_And64, mkexpr(lo64), mkU64(0xFFFFFFFF)));
}

static IRTemp mkV128from32s ( IRTemp in3, IRTemp in2, IRTemp in1, IRTemp in0 )
{
  IRTemp hi64 = newTemp(Ity_I64);
  IRTemp lo64 = newTemp(Ity_I64);
  assign(hi64,
         binop(Iop_Or64,
               binop(Iop_Shl64, mkexpr(in3), mkU8(32)),
               binop(Iop_And64, mkexpr(in2), mkU64(0xFFFFFFFF))));
  assign(lo64,
         binop(Iop_Or64,
               binop(Iop_Shl64, mkexpr(in1), mkU8(32)),
               binop(Iop_And64, mkexpr(in0), mkU64(0xFFFFFFFF))));
  IRTemp res = newTemp(Ity_V128);
  assign(res, binop(Iop_64HLtoV128, mkexpr(hi64), mkexpr(lo64)));
  return res;
}

static IRExpr* mk_CatEvenLanes32x4 ( IRTemp a3210, IRTemp b3210 )
{
  
  IRTemp a2, a0, b2, b0;
  breakV128to32s(NULL, &a2, NULL, &a0, a3210);
  breakV128to32s(NULL, &b2, NULL, &b0, b3210);
  return mkexpr(mkV128from32s(a2, a0, b2, b0));
}

static IRExpr* mk_CatOddLanes32x4 ( IRTemp a3210, IRTemp b3210 )
{
  
  IRTemp a3, a1, b3, b1;
  breakV128to32s(&a3, NULL, &a1, NULL, a3210);
  breakV128to32s(&b3, NULL, &b1, NULL, b3210);
  return mkexpr(mkV128from32s(a3, a1, b3, b1));
}

static IRExpr* mk_InterleaveLO32x4 ( IRTemp a3210, IRTemp b3210 )
{
  
  IRTemp a1, a0, b1, b0;
  breakV128to32s(NULL, NULL, &a1, &a0, a3210);
  breakV128to32s(NULL, NULL, &b1, &b0, b3210);
  return mkexpr(mkV128from32s(a1, b1, a0, b0));
}

static IRExpr* mk_InterleaveHI32x4 ( IRTemp a3210, IRTemp b3210 )
{
  
  IRTemp a3, a2, b3, b2;
  breakV128to32s(&a3, &a2, NULL, NULL, a3210);
  breakV128to32s(&b3, &b2, NULL, NULL, b3210);
  return mkexpr(mkV128from32s(a3, b3, a2, b2));
}


static void breakV128to16s ( IRTemp* out7, IRTemp* out6, IRTemp* out5,
                             IRTemp* out4, IRTemp* out3, IRTemp* out2,
                             IRTemp* out1,IRTemp* out0, IRTemp v128 )
{
  if (out7) *out7 = newTemp(Ity_I64);
  if (out6) *out6 = newTemp(Ity_I64);
  if (out5) *out5 = newTemp(Ity_I64);
  if (out4) *out4 = newTemp(Ity_I64);
  if (out3) *out3 = newTemp(Ity_I64);
  if (out2) *out2 = newTemp(Ity_I64);
  if (out1) *out1 = newTemp(Ity_I64);
  if (out0) *out0 = newTemp(Ity_I64);
  IRTemp hi64 = newTemp(Ity_I64);
  IRTemp lo64 = newTemp(Ity_I64);
  assign(hi64, unop(Iop_V128HIto64, mkexpr(v128)) );
  assign(lo64, unop(Iop_V128to64,   mkexpr(v128)) );
  if (out7)
    assign(*out7, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(48)),
                        mkU64(0xFFFF)));
  if (out6)
    assign(*out6, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(32)),
                        mkU64(0xFFFF)));
  if (out5)
    assign(*out5, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(16)),
                        mkU64(0xFFFF)));
  if (out4)
    assign(*out4, binop(Iop_And64, mkexpr(hi64), mkU64(0xFFFF)));
  if (out3)
    assign(*out3, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(48)),
                        mkU64(0xFFFF)));
  if (out2)
    assign(*out2, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(32)),
                        mkU64(0xFFFF)));
  if (out1)
    assign(*out1, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(16)),
                        mkU64(0xFFFF)));
  if (out0)
    assign(*out0, binop(Iop_And64, mkexpr(lo64), mkU64(0xFFFF)));
}

static IRTemp mkV128from16s ( IRTemp in7, IRTemp in6, IRTemp in5, IRTemp in4,
                              IRTemp in3, IRTemp in2, IRTemp in1, IRTemp in0 )
{
  IRTemp hi64 = newTemp(Ity_I64);
  IRTemp lo64 = newTemp(Ity_I64);
  assign(hi64,
         binop(Iop_Or64,
               binop(Iop_Or64,
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in7), mkU64(0xFFFF)),
                           mkU8(48)),
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in6), mkU64(0xFFFF)),
                           mkU8(32))),
               binop(Iop_Or64,
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in5), mkU64(0xFFFF)),
                           mkU8(16)),
                     binop(Iop_And64,
                           mkexpr(in4), mkU64(0xFFFF)))));
  assign(lo64,
         binop(Iop_Or64,
               binop(Iop_Or64,
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in3), mkU64(0xFFFF)),
                           mkU8(48)),
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in2), mkU64(0xFFFF)),
                           mkU8(32))),
               binop(Iop_Or64,
                     binop(Iop_Shl64,
                           binop(Iop_And64, mkexpr(in1), mkU64(0xFFFF)),
                           mkU8(16)),
                     binop(Iop_And64,
                           mkexpr(in0), mkU64(0xFFFF)))));
  IRTemp res = newTemp(Ity_V128);
  assign(res, binop(Iop_64HLtoV128, mkexpr(hi64), mkexpr(lo64)));
  return res;
}

static IRExpr* mk_CatEvenLanes16x8 ( IRTemp a76543210, IRTemp b76543210 )
{
  
  IRTemp a6, a4, a2, a0, b6, b4, b2, b0;
  breakV128to16s(NULL, &a6, NULL, &a4, NULL, &a2, NULL, &a0, a76543210);
  breakV128to16s(NULL, &b6, NULL, &b4, NULL, &b2, NULL, &b0, b76543210);
  return mkexpr(mkV128from16s(a6, a4, a2, a0, b6, b4, b2, b0));
}

static IRExpr* mk_CatOddLanes16x8 ( IRTemp a76543210, IRTemp b76543210 )
{
  
  IRTemp a7, a5, a3, a1, b7, b5, b3, b1;
  breakV128to16s(&a7, NULL, &a5, NULL, &a3, NULL, &a1, NULL, a76543210);
  breakV128to16s(&b7, NULL, &b5, NULL, &b3, NULL, &b1, NULL, b76543210);
  return mkexpr(mkV128from16s(a7, a5, a3, a1, b7, b5, b3, b1));
}

static IRExpr* mk_InterleaveLO16x8 ( IRTemp a76543210, IRTemp b76543210 )
{
  
  IRTemp a3, b3, a2, b2, a1, a0, b1, b0;
  breakV128to16s(NULL, NULL, NULL, NULL, &a3, &a2, &a1, &a0, a76543210);
  breakV128to16s(NULL, NULL, NULL, NULL, &b3, &b2, &b1, &b0, b76543210);
  return mkexpr(mkV128from16s(a3, b3, a2, b2, a1, b1, a0, b0));
}

static IRExpr* mk_InterleaveHI16x8 ( IRTemp a76543210, IRTemp b76543210 )
{
  
  IRTemp a7, b7, a6, b6, a5, b5, a4, b4;
  breakV128to16s(&a7, &a6, &a5, &a4, NULL, NULL, NULL, NULL, a76543210);
  breakV128to16s(&b7, &b6, &b5, &b4, NULL, NULL, NULL, NULL, b76543210);
  return mkexpr(mkV128from16s(a7, b7, a6, b6, a5, b5, a4, b4));
}


static void breakV128to8s ( IRTemp* outF, IRTemp* outE, IRTemp* outD, 
                            IRTemp* outC, IRTemp* outB, IRTemp* outA, 
                            IRTemp* out9, IRTemp* out8, 
                            IRTemp* out7, IRTemp* out6, IRTemp* out5,
                            IRTemp* out4, IRTemp* out3, IRTemp* out2,
                            IRTemp* out1,IRTemp* out0, IRTemp v128 )
{
  if (outF) *outF = newTemp(Ity_I64);
  if (outE) *outE = newTemp(Ity_I64);
  if (outD) *outD = newTemp(Ity_I64);
  if (outC) *outC = newTemp(Ity_I64);
  if (outB) *outB = newTemp(Ity_I64);
  if (outA) *outA = newTemp(Ity_I64);
  if (out9) *out9 = newTemp(Ity_I64);
  if (out8) *out8 = newTemp(Ity_I64);
  if (out7) *out7 = newTemp(Ity_I64);
  if (out6) *out6 = newTemp(Ity_I64);
  if (out5) *out5 = newTemp(Ity_I64);
  if (out4) *out4 = newTemp(Ity_I64);
  if (out3) *out3 = newTemp(Ity_I64);
  if (out2) *out2 = newTemp(Ity_I64);
  if (out1) *out1 = newTemp(Ity_I64);
  if (out0) *out0 = newTemp(Ity_I64);
  IRTemp hi64 = newTemp(Ity_I64);
  IRTemp lo64 = newTemp(Ity_I64);
  assign(hi64, unop(Iop_V128HIto64, mkexpr(v128)) );
  assign(lo64, unop(Iop_V128to64,   mkexpr(v128)) );
  if (outF)
    assign(*outF, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(56)),
                        mkU64(0xFF)));
  if (outE)
    assign(*outE, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(48)),
                        mkU64(0xFF)));
  if (outD)
    assign(*outD, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(40)),
                        mkU64(0xFF)));
  if (outC)
    assign(*outC, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(32)),
                        mkU64(0xFF)));
  if (outB)
    assign(*outB, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(24)),
                        mkU64(0xFF)));
  if (outA)
    assign(*outA, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(16)),
                        mkU64(0xFF)));
  if (out9)
    assign(*out9, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(8)),
                        mkU64(0xFF)));
  if (out8)
    assign(*out8, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(hi64), mkU8(0)),
                        mkU64(0xFF)));
  if (out7)
    assign(*out7, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(56)),
                        mkU64(0xFF)));
  if (out6)
    assign(*out6, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(48)),
                        mkU64(0xFF)));
  if (out5)
    assign(*out5, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(40)),
                        mkU64(0xFF)));
  if (out4)
    assign(*out4, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(32)),
                        mkU64(0xFF)));
  if (out3)
    assign(*out3, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(24)),
                        mkU64(0xFF)));
  if (out2)
    assign(*out2, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(16)),
                        mkU64(0xFF)));
  if (out1)
    assign(*out1, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(8)),
                        mkU64(0xFF)));
  if (out0)
    assign(*out0, binop(Iop_And64,
                        binop(Iop_Shr64, mkexpr(lo64), mkU8(0)),
                        mkU64(0xFF)));
}

static IRTemp mkV128from8s ( IRTemp inF, IRTemp inE, IRTemp inD, IRTemp inC,
                             IRTemp inB, IRTemp inA, IRTemp in9, IRTemp in8,
                             IRTemp in7, IRTemp in6, IRTemp in5, IRTemp in4,
                             IRTemp in3, IRTemp in2, IRTemp in1, IRTemp in0 )
{
  IRTemp vFE = newTemp(Ity_I64);
  IRTemp vDC = newTemp(Ity_I64);
  IRTemp vBA = newTemp(Ity_I64);
  IRTemp v98 = newTemp(Ity_I64);
  IRTemp v76 = newTemp(Ity_I64);
  IRTemp v54 = newTemp(Ity_I64);
  IRTemp v32 = newTemp(Ity_I64);
  IRTemp v10 = newTemp(Ity_I64);
  assign(vFE, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(inF), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(inE), mkU64(0xFF))));
  assign(vDC, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(inD), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(inC), mkU64(0xFF))));
  assign(vBA, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(inB), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(inA), mkU64(0xFF))));
  assign(v98, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(in9), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(in8), mkU64(0xFF))));
  assign(v76, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(in7), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(in6), mkU64(0xFF))));
  assign(v54, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(in5), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(in4), mkU64(0xFF))));
  assign(v32, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(in3), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(in2), mkU64(0xFF))));
  assign(v10, binop(Iop_Or64,
                    binop(Iop_Shl64,
                          binop(Iop_And64, mkexpr(in1), mkU64(0xFF)), mkU8(8)),
                    binop(Iop_And64, mkexpr(in0), mkU64(0xFF))));
  return mkV128from16s(vFE, vDC, vBA, v98, v76, v54, v32, v10);
}

static IRExpr* mk_CatEvenLanes8x16 ( IRTemp aFEDCBA9876543210,
                                     IRTemp bFEDCBA9876543210 )
{
  
  IRTemp aE, aC, aA, a8, a6, a4, a2, a0, bE, bC, bA, b8, b6, b4, b2, b0;
  breakV128to8s(NULL, &aE, NULL, &aC, NULL, &aA, NULL, &a8, 
                NULL, &a6, NULL, &a4, NULL, &a2, NULL, &a0,
                aFEDCBA9876543210);
  breakV128to8s(NULL, &bE, NULL, &bC, NULL, &bA, NULL, &b8, 
                NULL, &b6, NULL, &b4, NULL, &b2, NULL, &b0,
                bFEDCBA9876543210);
  return mkexpr(mkV128from8s(aE, aC, aA, a8, a6, a4, a2, a0,
                             bE, bC, bA, b8, b6, b4, b2, b0));
}

static IRExpr* mk_CatOddLanes8x16 ( IRTemp aFEDCBA9876543210,
                                    IRTemp bFEDCBA9876543210 )
{
  
  IRTemp aF, aD, aB, a9, a7, a5, a3, a1, bF, bD, bB, b9, b7, b5, b3, b1;
  breakV128to8s(&aF, NULL, &aD, NULL, &aB, NULL, &a9, NULL,
                &a7, NULL, &a5, NULL, &a3, NULL, &a1, NULL,
                aFEDCBA9876543210);

  breakV128to8s(&bF, NULL, &bD, NULL, &bB, NULL, &b9, NULL,
                &b7, NULL, &b5, NULL, &b3, NULL, &b1, NULL,
                aFEDCBA9876543210);

  return mkexpr(mkV128from8s(aF, aD, aB, a9, a7, a5, a3, a1,
                             bF, bD, bB, b9, b7, b5, b3, b1));
}

static IRExpr* mk_InterleaveLO8x16 ( IRTemp aFEDCBA9876543210,
                                     IRTemp bFEDCBA9876543210 )
{
  
  IRTemp a7, b7, a6, b6, a5, b5, a4, b4, a3, b3, a2, b2, a1, b1, a0, b0;
  breakV128to8s(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                &a7,  &a6,  &a5,  &a4,  &a3,  &a2,  &a1,  &a0,
                aFEDCBA9876543210);
  breakV128to8s(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                &b7,  &b6,  &b5,  &b4,  &b3,  &b2,  &b1,  &b0,
                bFEDCBA9876543210);
  return mkexpr(mkV128from8s(a7, b7, a6, b6, a5, b5, a4, b4,
                             a3, b3, a2, b2, a1, b1, a0, b0));
}

static IRExpr* mk_InterleaveHI8x16 ( IRTemp aFEDCBA9876543210,
                                     IRTemp bFEDCBA9876543210 )
{
  
  IRTemp aF, bF, aE, bE, aD, bD, aC, bC, aB, bB, aA, bA, a9, b9, a8, b8;
  breakV128to8s(&aF,  &aE,  &aD,  &aC,  &aB,  &aA,  &a9,  &a8,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                aFEDCBA9876543210);
  breakV128to8s(&bF,  &bE,  &bD,  &bC,  &bB,  &bA,  &b9,  &b8,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                bFEDCBA9876543210);
  return mkexpr(mkV128from8s(aF, bF, aE, bE, aD, bD, aC, bC,
                             aB, bB, aA, bA, a9, b9, a8, b8));
}

