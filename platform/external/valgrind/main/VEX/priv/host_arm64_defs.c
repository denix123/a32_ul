

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
#include "libvex.h"
#include "libvex_trc_values.h"

#include "main_util.h"
#include "host_generic_regs.h"
#include "host_arm64_defs.h"





void ppHRegARM64 ( HReg reg )  {
   Int r;
   
   if (hregIsVirtual(reg)) {
      ppHReg(reg);
      return;
   }
   
   switch (hregClass(reg)) {
      case HRcInt64:
         r = hregNumber(reg);
         vassert(r >= 0 && r < 31);
         vex_printf("x%d", r);
         return;
      case HRcFlt64:
         r = hregNumber(reg);
         vassert(r >= 0 && r < 32);
         vex_printf("d%d", r);
         return;
      case HRcVec128:
         r = hregNumber(reg);
         vassert(r >= 0 && r < 32);
         vex_printf("q%d", r);
         return;
      default:
         vpanic("ppHRegARM64");
   }
}

static void ppHRegARM64asSreg ( HReg reg ) {
   ppHRegARM64(reg);
   vex_printf("(S-reg)");
}

HReg hregARM64_X0  ( void ) { return mkHReg(0,  HRcInt64, False); }
HReg hregARM64_X1  ( void ) { return mkHReg(1,  HRcInt64, False); }
HReg hregARM64_X2  ( void ) { return mkHReg(2,  HRcInt64, False); }
HReg hregARM64_X3  ( void ) { return mkHReg(3,  HRcInt64, False); }
HReg hregARM64_X4  ( void ) { return mkHReg(4,  HRcInt64, False); }
HReg hregARM64_X5  ( void ) { return mkHReg(5,  HRcInt64, False); }
HReg hregARM64_X6  ( void ) { return mkHReg(6,  HRcInt64, False); }
HReg hregARM64_X7  ( void ) { return mkHReg(7,  HRcInt64, False); }
HReg hregARM64_X9  ( void ) { return mkHReg(9,  HRcInt64, False); }
HReg hregARM64_X10 ( void ) { return mkHReg(10, HRcInt64, False); }
HReg hregARM64_X11 ( void ) { return mkHReg(11, HRcInt64, False); }
HReg hregARM64_X12 ( void ) { return mkHReg(12, HRcInt64, False); }
HReg hregARM64_X13 ( void ) { return mkHReg(13, HRcInt64, False); }
HReg hregARM64_X14 ( void ) { return mkHReg(14, HRcInt64, False); }
HReg hregARM64_X15 ( void ) { return mkHReg(15, HRcInt64, False); }
HReg hregARM64_X21 ( void ) { return mkHReg(21, HRcInt64, False); }
HReg hregARM64_X22 ( void ) { return mkHReg(22, HRcInt64, False); }
HReg hregARM64_X23 ( void ) { return mkHReg(23, HRcInt64, False); }
HReg hregARM64_X24 ( void ) { return mkHReg(24, HRcInt64, False); }
HReg hregARM64_X25 ( void ) { return mkHReg(25, HRcInt64, False); }
HReg hregARM64_X26 ( void ) { return mkHReg(26, HRcInt64, False); }
HReg hregARM64_X27 ( void ) { return mkHReg(27, HRcInt64, False); }
HReg hregARM64_X28 ( void ) { return mkHReg(28, HRcInt64, False); }

HReg hregARM64_D8  ( void ) { return mkHReg(8,  HRcFlt64, False); }
HReg hregARM64_D9  ( void ) { return mkHReg(9,  HRcFlt64, False); }
HReg hregARM64_D10 ( void ) { return mkHReg(10, HRcFlt64, False); }
HReg hregARM64_D11 ( void ) { return mkHReg(11, HRcFlt64, False); }
HReg hregARM64_D12 ( void ) { return mkHReg(12, HRcFlt64, False); }
HReg hregARM64_D13 ( void ) { return mkHReg(13, HRcFlt64, False); }
HReg hregARM64_Q16 ( void ) { return mkHReg(16, HRcVec128, False); }
HReg hregARM64_Q17 ( void ) { return mkHReg(17, HRcVec128, False); }
HReg hregARM64_Q18 ( void ) { return mkHReg(18, HRcVec128, False); }

void getAllocableRegs_ARM64 ( Int* nregs, HReg** arr )
{
   Int i = 0;
   *nregs = 24;
   *arr = LibVEX_Alloc(*nregs * sizeof(HReg));

   
   
   (*arr)[i++] = hregARM64_X22();
   (*arr)[i++] = hregARM64_X23();
   (*arr)[i++] = hregARM64_X24();
   (*arr)[i++] = hregARM64_X25();
   (*arr)[i++] = hregARM64_X26();
   (*arr)[i++] = hregARM64_X27();
   (*arr)[i++] = hregARM64_X28();

   (*arr)[i++] = hregARM64_X0();
   (*arr)[i++] = hregARM64_X1();
   (*arr)[i++] = hregARM64_X2();
   (*arr)[i++] = hregARM64_X3();
   (*arr)[i++] = hregARM64_X4();
   (*arr)[i++] = hregARM64_X5();
   (*arr)[i++] = hregARM64_X6();
   (*arr)[i++] = hregARM64_X7();
   
   

   
   
   
   
   
   
   
   

   
   (*arr)[i++] = hregARM64_Q16();
   (*arr)[i++] = hregARM64_Q17();
   (*arr)[i++] = hregARM64_Q18();

   
   (*arr)[i++] = hregARM64_D8();
   (*arr)[i++] = hregARM64_D9();
   (*arr)[i++] = hregARM64_D10();
   (*arr)[i++] = hregARM64_D11();
   (*arr)[i++] = hregARM64_D12();
   (*arr)[i++] = hregARM64_D13();

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   vassert(i == *nregs);
}



static const HChar* showARM64CondCode ( ARM64CondCode cond ) {
   switch (cond) {
       case ARM64cc_EQ:  return "eq";
       case ARM64cc_NE:  return "ne";
       case ARM64cc_CS:  return "cs";
       case ARM64cc_CC:  return "cc";
       case ARM64cc_MI:  return "mi";
       case ARM64cc_PL:  return "pl";
       case ARM64cc_VS:  return "vs";
       case ARM64cc_VC:  return "vc";
       case ARM64cc_HI:  return "hi";
       case ARM64cc_LS:  return "ls";
       case ARM64cc_GE:  return "ge";
       case ARM64cc_LT:  return "lt";
       case ARM64cc_GT:  return "gt";
       case ARM64cc_LE:  return "le";
       case ARM64cc_AL:  return "al"; 
       case ARM64cc_NV:  return "nv";
       default: vpanic("showARM64CondCode");
   }
}



ARM64AMode* ARM64AMode_RI9  ( HReg reg, Int simm9 ) {
   ARM64AMode* am        = LibVEX_Alloc(sizeof(ARM64AMode));
   am->tag               = ARM64am_RI9;
   am->ARM64am.RI9.reg   = reg;
   am->ARM64am.RI9.simm9 = simm9;
   vassert(-256 <= simm9 && simm9 <= 255);
   return am;
}

ARM64AMode* ARM64AMode_RI12 ( HReg reg, Int uimm12, UChar szB ) {
   ARM64AMode* am          = LibVEX_Alloc(sizeof(ARM64AMode));
   am->tag                 = ARM64am_RI12;
   am->ARM64am.RI12.reg    = reg;
   am->ARM64am.RI12.uimm12 = uimm12;
   am->ARM64am.RI12.szB    = szB;
   vassert(uimm12 >= 0 && uimm12 <= 4095);
   switch (szB) {
      case 1: case 2: case 4: case 8: break;
      default: vassert(0);
   }
   return am;
}

ARM64AMode* ARM64AMode_RR ( HReg base, HReg index ) {
   ARM64AMode* am       = LibVEX_Alloc(sizeof(ARM64AMode));
   am->tag              = ARM64am_RR;
   am->ARM64am.RR.base  = base;
   am->ARM64am.RR.index = index;
   return am;
}

static void ppARM64AMode ( ARM64AMode* am ) {
   switch (am->tag) {
      case ARM64am_RI9:
         vex_printf("%d(", am->ARM64am.RI9.simm9);
         ppHRegARM64(am->ARM64am.RI9.reg);
         vex_printf(")");
         break;
      case ARM64am_RI12:
         vex_printf("%u(", (UInt)am->ARM64am.RI12.szB
                           * (UInt)am->ARM64am.RI12.uimm12);
         ppHRegARM64(am->ARM64am.RI12.reg);
         vex_printf(")");
         break;
      case ARM64am_RR:
         vex_printf("(");
         ppHRegARM64(am->ARM64am.RR.base);
         vex_printf(",");
         ppHRegARM64(am->ARM64am.RR.index);
         vex_printf(")");
         break;
      default:
         vassert(0);
   }
}

static void addRegUsage_ARM64AMode ( HRegUsage* u, ARM64AMode* am ) {
   switch (am->tag) {
      case ARM64am_RI9:
         addHRegUse(u, HRmRead, am->ARM64am.RI9.reg);
         return;
      case ARM64am_RI12:
         addHRegUse(u, HRmRead, am->ARM64am.RI12.reg);
         return;
      case ARM64am_RR:
         addHRegUse(u, HRmRead, am->ARM64am.RR.base);
         addHRegUse(u, HRmRead, am->ARM64am.RR.index);
         return;
      default:
         vpanic("addRegUsage_ARM64Amode");
   }
}

static void mapRegs_ARM64AMode ( HRegRemap* m, ARM64AMode* am ) {
   switch (am->tag) {
      case ARM64am_RI9:
         am->ARM64am.RI9.reg = lookupHRegRemap(m, am->ARM64am.RI9.reg);
         return;
      case ARM64am_RI12:
         am->ARM64am.RI12.reg = lookupHRegRemap(m, am->ARM64am.RI12.reg);
         return;
      case ARM64am_RR:
         am->ARM64am.RR.base  = lookupHRegRemap(m, am->ARM64am.RR.base);
         am->ARM64am.RR.index = lookupHRegRemap(m, am->ARM64am.RR.index);
         return;
      default:
         vpanic("mapRegs_ARM64Amode");
   }
}





ARM64RIA* ARM64RIA_I12 ( UShort imm12, UChar shift ) {
   ARM64RIA* riA           = LibVEX_Alloc(sizeof(ARM64RIA));
   riA->tag                = ARM64riA_I12;
   riA->ARM64riA.I12.imm12 = imm12;
   riA->ARM64riA.I12.shift = shift;
   vassert(imm12 < 4096);
   vassert(shift == 0 || shift == 12);
   return riA;
}
ARM64RIA* ARM64RIA_R ( HReg reg ) {
   ARM64RIA* riA       = LibVEX_Alloc(sizeof(ARM64RIA));
   riA->tag            = ARM64riA_R;
   riA->ARM64riA.R.reg = reg;
   return riA;
}

static void ppARM64RIA ( ARM64RIA* riA ) {
   switch (riA->tag) {
      case ARM64riA_I12:
         vex_printf("#%u",(UInt)(riA->ARM64riA.I12.imm12
                                 << riA->ARM64riA.I12.shift));
         break;
      case ARM64riA_R:
         ppHRegARM64(riA->ARM64riA.R.reg);
         break;
      default:
         vassert(0);
   }
}

static void addRegUsage_ARM64RIA ( HRegUsage* u, ARM64RIA* riA ) {
   switch (riA->tag) {
      case ARM64riA_I12:
         return;
      case ARM64riA_R:
         addHRegUse(u, HRmRead, riA->ARM64riA.R.reg);
         return;
      default:
         vpanic("addRegUsage_ARM64RIA");
   }
}

static void mapRegs_ARM64RIA ( HRegRemap* m, ARM64RIA* riA ) {
   switch (riA->tag) {
      case ARM64riA_I12:
         return;
      case ARM64riA_R:
         riA->ARM64riA.R.reg = lookupHRegRemap(m, riA->ARM64riA.R.reg);
         return;
      default:
         vpanic("mapRegs_ARM64RIA");
   }
}



ARM64RIL* ARM64RIL_I13 ( UChar bitN, UChar immR, UChar immS ) {
   ARM64RIL* riL          = LibVEX_Alloc(sizeof(ARM64RIL));
   riL->tag               = ARM64riL_I13;
   riL->ARM64riL.I13.bitN = bitN;
   riL->ARM64riL.I13.immR = immR;
   riL->ARM64riL.I13.immS = immS;
   vassert(bitN < 2);
   vassert(immR < 64);
   vassert(immS < 64);
   return riL;
}
ARM64RIL* ARM64RIL_R ( HReg reg ) {
   ARM64RIL* riL       = LibVEX_Alloc(sizeof(ARM64RIL));
   riL->tag            = ARM64riL_R;
   riL->ARM64riL.R.reg = reg;
   return riL;
}

static void ppARM64RIL ( ARM64RIL* riL ) {
   switch (riL->tag) {
      case ARM64riL_I13:
         vex_printf("#nrs(%u,%u,%u)",
                     (UInt)riL->ARM64riL.I13.bitN,
                     (UInt)riL->ARM64riL.I13.immR,
                     (UInt)riL->ARM64riL.I13.immS);
         break;
      case ARM64riL_R:
         ppHRegARM64(riL->ARM64riL.R.reg);
         break;
      default:
         vassert(0);
   }
}

static void addRegUsage_ARM64RIL ( HRegUsage* u, ARM64RIL* riL ) {
   switch (riL->tag) {
      case ARM64riL_I13:
         return;
      case ARM64riL_R:
         addHRegUse(u, HRmRead, riL->ARM64riL.R.reg);
         return;
      default:
         vpanic("addRegUsage_ARM64RIL");
   }
}

static void mapRegs_ARM64RIL ( HRegRemap* m, ARM64RIL* riL ) {
   switch (riL->tag) {
      case ARM64riL_I13:
         return;
      case ARM64riL_R:
         riL->ARM64riL.R.reg = lookupHRegRemap(m, riL->ARM64riL.R.reg);
         return;
      default:
         vpanic("mapRegs_ARM64RIL");
   }
}



ARM64RI6* ARM64RI6_I6 ( UInt imm6 ) {
   ARM64RI6* ri6         = LibVEX_Alloc(sizeof(ARM64RI6));
   ri6->tag              = ARM64ri6_I6;
   ri6->ARM64ri6.I6.imm6 = imm6;
   vassert(imm6 > 0 && imm6 < 64);
   return ri6;
}
ARM64RI6* ARM64RI6_R ( HReg reg ) {
   ARM64RI6* ri6       = LibVEX_Alloc(sizeof(ARM64RI6));
   ri6->tag            = ARM64ri6_R;
   ri6->ARM64ri6.R.reg = reg;
   return ri6;
}

static void ppARM64RI6 ( ARM64RI6* ri6 ) {
   switch (ri6->tag) {
      case ARM64ri6_I6:
         vex_printf("#%u", ri6->ARM64ri6.I6.imm6);
         break;
      case ARM64ri6_R:
         ppHRegARM64(ri6->ARM64ri6.R.reg);
         break;
      default:
         vassert(0);
   }
}

static void addRegUsage_ARM64RI6 ( HRegUsage* u, ARM64RI6* ri6 ) {
   switch (ri6->tag) {
      case ARM64ri6_I6:
         return;
      case ARM64ri6_R:
         addHRegUse(u, HRmRead, ri6->ARM64ri6.R.reg);
         return;
      default:
         vpanic("addRegUsage_ARM64RI6");
   }
}

static void mapRegs_ARM64RI6 ( HRegRemap* m, ARM64RI6* ri6 ) {
   switch (ri6->tag) {
      case ARM64ri6_I6:
         return;
      case ARM64ri6_R:
         ri6->ARM64ri6.R.reg = lookupHRegRemap(m, ri6->ARM64ri6.R.reg);
         return;
      default:
         vpanic("mapRegs_ARM64RI6");
   }
}




static const HChar* showARM64LogicOp ( ARM64LogicOp op ) {
   switch (op) {
      case ARM64lo_AND: return "and";
      case ARM64lo_OR:  return "orr";
      case ARM64lo_XOR: return "eor";
      default: vpanic("showARM64LogicOp");
   }
}

static const HChar* showARM64ShiftOp ( ARM64ShiftOp op ) {
   switch (op) {
      case ARM64sh_SHL: return "lsl";
      case ARM64sh_SHR: return "lsr";
      case ARM64sh_SAR: return "asr";
      default: vpanic("showARM64ShiftOp");
   }
}

static const HChar* showARM64UnaryOp ( ARM64UnaryOp op ) {
   switch (op) {
      case ARM64un_NEG: return "neg";
      case ARM64un_NOT: return "not";
      case ARM64un_CLZ: return "clz";
      default: vpanic("showARM64UnaryOp");
   }
}

static const HChar* showARM64MulOp ( ARM64MulOp op ) {
   switch (op) {
      case ARM64mul_PLAIN: return "mul  ";
      case ARM64mul_ZX:    return "umulh";
      case ARM64mul_SX:    return "smulh";
      default: vpanic("showARM64MulOp");
   }
}

static void characteriseARM64CvtOp ( HChar* syn,
                                     UInt* fszB, UInt* iszB, 
                                     ARM64CvtOp op ) {
   switch (op) {
      case ARM64cvt_F32_I32S:
         *syn = 's'; *fszB = 4; *iszB = 4; break;
      case ARM64cvt_F64_I32S:
         *syn = 's'; *fszB = 8; *iszB = 4; break;
      case ARM64cvt_F32_I64S:
         *syn = 's'; *fszB = 4; *iszB = 8; break;
      case ARM64cvt_F64_I64S:
         *syn = 's'; *fszB = 8; *iszB = 8; break;
      case ARM64cvt_F32_I32U:
         *syn = 'u'; *fszB = 4; *iszB = 4; break;
      case ARM64cvt_F64_I32U:
         *syn = 'u'; *fszB = 8; *iszB = 4; break;
      case ARM64cvt_F32_I64U:
         *syn = 'u'; *fszB = 4; *iszB = 8; break;
      case ARM64cvt_F64_I64U:
         *syn = 'u'; *fszB = 8; *iszB = 8; break;
      default:
         vpanic("characteriseARM64CvtOp");
  }
}

static const HChar* showARM64FpBinOp ( ARM64FpBinOp op ) {
   switch (op) {
      case ARM64fpb_ADD: return "add";
      case ARM64fpb_SUB: return "sub";
      case ARM64fpb_MUL: return "mul";
      case ARM64fpb_DIV: return "div";
      default: vpanic("showARM64FpBinOp");
   }
}

static const HChar* showARM64FpUnaryOp ( ARM64FpUnaryOp op ) {
   switch (op) {
      case ARM64fpu_NEG:  return "neg  ";
      case ARM64fpu_ABS:  return "abs  ";
      case ARM64fpu_SQRT: return "sqrt ";
      case ARM64fpu_RINT: return "rinti";
      default: vpanic("showARM64FpUnaryOp");
   }
}

static void showARM64VecBinOp(const HChar** nm,
                              const HChar** ar, ARM64VecBinOp op ) {
   switch (op) {
      case ARM64vecb_ADD64x2:   *nm = "add ";  *ar = "2d";  return;
      case ARM64vecb_ADD32x4:   *nm = "add ";  *ar = "4s";  return;
      case ARM64vecb_ADD16x8:   *nm = "add ";  *ar = "8h";  return;
      case ARM64vecb_ADD8x16:   *nm = "add ";  *ar = "16b"; return;
      case ARM64vecb_SUB64x2:   *nm = "sub ";  *ar = "2d";  return;
      case ARM64vecb_SUB32x4:   *nm = "sub ";  *ar = "4s";  return;
      case ARM64vecb_SUB16x8:   *nm = "sub ";  *ar = "8h";  return;
      case ARM64vecb_SUB8x16:   *nm = "sub ";  *ar = "16b"; return;
      case ARM64vecb_MUL32x4:   *nm = "mul ";  *ar = "4s";  return;
      case ARM64vecb_MUL16x8:   *nm = "mul ";  *ar = "8h";  return;
      case ARM64vecb_MUL8x16:   *nm = "mul ";  *ar = "16b"; return;
      case ARM64vecb_FADD64x2:  *nm = "fadd";  *ar = "2d";  return;
      case ARM64vecb_FSUB64x2:  *nm = "fsub";  *ar = "2d";  return;
      case ARM64vecb_FMUL64x2:  *nm = "fmul";  *ar = "2d";  return;
      case ARM64vecb_FDIV64x2:  *nm = "fdiv";  *ar = "2d";  return;
      case ARM64vecb_FADD32x4:  *nm = "fadd";  *ar = "4s";  return;
      case ARM64vecb_FSUB32x4:  *nm = "fsub";  *ar = "4s";  return;
      case ARM64vecb_FMUL32x4:  *nm = "fmul";  *ar = "4s";  return;
      case ARM64vecb_FDIV32x4:  *nm = "fdiv";  *ar = "4s";  return;
      case ARM64vecb_UMAX32x4:  *nm = "umax";  *ar = "4s";  return;
      case ARM64vecb_UMAX16x8:  *nm = "umax";  *ar = "8h";  return;
      case ARM64vecb_UMAX8x16:  *nm = "umax";  *ar = "16b"; return;
      case ARM64vecb_UMIN32x4:  *nm = "umin";  *ar = "4s";  return;
      case ARM64vecb_UMIN16x8:  *nm = "umin";  *ar = "8h";  return;
      case ARM64vecb_UMIN8x16:  *nm = "umin";  *ar = "16b"; return;
      case ARM64vecb_UMULL32x2: *nm = "umull"; *ar = "2d"; return;
      case ARM64vecb_UMULL16x4: *nm = "umull"; *ar = "4s"; return;
      case ARM64vecb_UMULL8x8:  *nm = "umull"; *ar = "8b"; return;
      case ARM64vecb_SMAX32x4:  *nm = "smax";  *ar = "4s";  return;
      case ARM64vecb_SMAX16x8:  *nm = "smax";  *ar = "8h";  return;
      case ARM64vecb_SMAX8x16:  *nm = "smax";  *ar = "16b"; return;
      case ARM64vecb_SMIN32x4:  *nm = "smin";  *ar = "4s";  return;
      case ARM64vecb_SMIN16x8:  *nm = "smin";  *ar = "8h";  return;
      case ARM64vecb_SMIN8x16:  *nm = "smin";  *ar = "16b"; return;
      case ARM64vecb_AND:       *nm = "and ";  *ar = "all"; return;
      case ARM64vecb_ORR:       *nm = "orr ";  *ar = "all"; return;
      case ARM64vecb_XOR:       *nm = "eor ";  *ar = "all"; return;
      case ARM64vecb_CMEQ64x2:  *nm = "cmeq";  *ar = "2d";  return;
      case ARM64vecb_CMEQ32x4:  *nm = "cmeq";  *ar = "4s";  return;
      case ARM64vecb_CMEQ16x8:  *nm = "cmeq";  *ar = "8h";  return;
      case ARM64vecb_CMEQ8x16:  *nm = "cmeq";  *ar = "16b"; return;
      case ARM64vecb_CMHI64x2:  *nm = "cmhi";  *ar = "2d";  return;
      case ARM64vecb_CMHI32x4:  *nm = "cmhi";  *ar = "4s";  return;
      case ARM64vecb_CMHI16x8:  *nm = "cmhi";  *ar = "8h";  return;
      case ARM64vecb_CMHI8x16:  *nm = "cmhi";  *ar = "16b"; return;
      case ARM64vecb_CMGT64x2:  *nm = "cmgt";  *ar = "2d";  return;
      case ARM64vecb_CMGT32x4:  *nm = "cmgt";  *ar = "4s";  return;
      case ARM64vecb_CMGT16x8:  *nm = "cmgt";  *ar = "8h";  return;
      case ARM64vecb_CMGT8x16:  *nm = "cmgt";  *ar = "16b"; return;
      case ARM64vecb_FCMEQ64x2: *nm = "fcmeq"; *ar = "2d"; return;
      case ARM64vecb_FCMEQ32x4: *nm = "fcmeq"; *ar = "4s"; return;
      case ARM64vecb_FCMGE64x2: *nm = "fcmge"; *ar = "2d"; return;
      case ARM64vecb_FCMGE32x4: *nm = "fcmge"; *ar = "4s"; return;
      case ARM64vecb_FCMGT64x2: *nm = "fcmgt"; *ar = "2d"; return;
      case ARM64vecb_FCMGT32x4: *nm = "fcmgt"; *ar = "4s"; return;
      case ARM64vecb_TBL1:      *nm = "tbl ";  *ar = "16b"; return;
      default: vpanic("showARM64VecBinOp");
   }
}

static void showARM64VecUnaryOp(const HChar** nm,
                                const HChar** ar, ARM64VecUnaryOp op )
{
   switch (op) {
      case ARM64vecu_FNEG64x2:   *nm = "fneg   "; *ar = "2d";  return;
      case ARM64vecu_FNEG32x4:   *nm = "fneg   "; *ar = "4s";  return;
      case ARM64vecu_FABS64x2:   *nm = "fabs   "; *ar = "2d";  return;
      case ARM64vecu_FABS32x4:   *nm = "fabs   "; *ar = "4s";  return;
      case ARM64vecu_VMOVL8U:    *nm = "vmovl.u8"; *ar = "all"; return;
      case ARM64vecu_VMOVL16U:   *nm = "vmovl.u16"; *ar = "all"; return;
      case ARM64vecu_VMOVL32U:   *nm = "vmovl.u32"; *ar = "all"; return;
      case ARM64vecu_VMOVL8S:    *nm = "vmovl.s8"; *ar = "all"; return;
      case ARM64vecu_VMOVL16S:   *nm = "vmovl.s16"; *ar = "all"; return;
      case ARM64vecu_VMOVL32S:   *nm = "vmovl.s32"; *ar = "all"; return;
      case ARM64vecu_NOT:        *nm = "not    "; *ar = "all"; return;
      case ARM64vecu_CNT:        *nm = "cnt    "; *ar = "16b"; return;
      case ARM64vecu_UADDLV8x16: *nm = "uaddlv "; *ar = "16b"; return;
      case ARM64vecu_UADDLV16x8: *nm = "uaddlv "; *ar = "8h"; return;
      case ARM64vecu_UADDLV32x4: *nm = "uaddlv "; *ar = "4s"; return;
      case ARM64vecu_SADDLV8x16: *nm = "saddlv "; *ar = "16b"; return;
      case ARM64vecu_SADDLV16x8: *nm = "saddlv "; *ar = "8h"; return;
      case ARM64vecu_SADDLV32x4: *nm = "saddlv "; *ar = "4s"; return;
      default: vpanic("showARM64VecUnaryOp");
   }
}

static void showARM64VecShiftOp(const HChar** nm,
                                const HChar** ar,
                                ARM64VecShiftOp op )
{
   switch (op) {
      case ARM64vecsh_USHR64x2: *nm = "ushr  "; *ar = "2d";  return;
      case ARM64vecsh_USHR32x4: *nm = "ushr  "; *ar = "4s";  return;
      case ARM64vecsh_USHR16x8: *nm = "ushr  "; *ar = "8h";  return;
      case ARM64vecsh_USHR8x16: *nm = "ushr  "; *ar = "16b"; return;
      case ARM64vecsh_SSHR64x2: *nm = "sshr  "; *ar = "2d";  return;
      case ARM64vecsh_SSHR32x4: *nm = "sshr  "; *ar = "4s";  return;
      case ARM64vecsh_SSHR16x8: *nm = "sshr  "; *ar = "8h";  return;
      case ARM64vecsh_SSHR8x16: *nm = "sshr  "; *ar = "16b"; return;
      case ARM64vecsh_SHL64x2:  *nm = "shl   "; *ar = "2d";  return;
      case ARM64vecsh_SHL32x4:  *nm = "shl   "; *ar = "4s";  return;
      case ARM64vecsh_SHL16x8:  *nm = "shl   "; *ar = "8h";  return;
      case ARM64vecsh_SHL8x16:  *nm = "shl   "; *ar = "16b"; return;
      default: vpanic("showARM64VecShiftImmOp");
   }
}


ARM64Instr* ARM64Instr_Arith ( HReg dst,
                               HReg argL, ARM64RIA* argR, Bool isAdd ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_Arith;
   i->ARM64in.Arith.dst   = dst;
   i->ARM64in.Arith.argL  = argL;
   i->ARM64in.Arith.argR  = argR;
   i->ARM64in.Arith.isAdd = isAdd;
   return i;
}
ARM64Instr* ARM64Instr_Cmp ( HReg argL, ARM64RIA* argR, Bool is64 ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag              = ARM64in_Cmp;
   i->ARM64in.Cmp.argL = argL;
   i->ARM64in.Cmp.argR = argR;
   i->ARM64in.Cmp.is64 = is64;
   return i;
}
ARM64Instr* ARM64Instr_Logic ( HReg dst,
                               HReg argL, ARM64RIL* argR, ARM64LogicOp op ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_Logic;
   i->ARM64in.Logic.dst   = dst;
   i->ARM64in.Logic.argL  = argL;
   i->ARM64in.Logic.argR  = argR;
   i->ARM64in.Logic.op    = op;
   return i;
}
ARM64Instr* ARM64Instr_Test ( HReg argL, ARM64RIL* argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_Test;
   i->ARM64in.Test.argL = argL;
   i->ARM64in.Test.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_Shift ( HReg dst,
                               HReg argL, ARM64RI6* argR, ARM64ShiftOp op ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_Shift;
   i->ARM64in.Shift.dst  = dst;
   i->ARM64in.Shift.argL = argL;
   i->ARM64in.Shift.argR = argR;
   i->ARM64in.Shift.op   = op;
   return i;
}
ARM64Instr* ARM64Instr_Unary ( HReg dst, HReg src, ARM64UnaryOp op ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_Unary;
   i->ARM64in.Unary.dst = dst;
   i->ARM64in.Unary.src = src;
   i->ARM64in.Unary.op  = op;
   return i;
}
ARM64Instr* ARM64Instr_MovI ( HReg dst, HReg src ) {
   ARM64Instr* i      = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag             = ARM64in_MovI;
   i->ARM64in.MovI.dst = dst;
   i->ARM64in.MovI.src = src;
   vassert(hregClass(src) == HRcInt64);
   vassert(hregClass(dst) == HRcInt64);
   return i;
}
ARM64Instr* ARM64Instr_Imm64 ( HReg dst, ULong imm64 ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_Imm64;
   i->ARM64in.Imm64.dst   = dst;
   i->ARM64in.Imm64.imm64 = imm64;
   return i;
}
ARM64Instr* ARM64Instr_LdSt64 ( Bool isLoad, HReg rD, ARM64AMode* amode ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_LdSt64;
   i->ARM64in.LdSt64.isLoad = isLoad;
   i->ARM64in.LdSt64.rD     = rD;
   i->ARM64in.LdSt64.amode  = amode;
   return i;
}
ARM64Instr* ARM64Instr_LdSt32 ( Bool isLoad, HReg rD, ARM64AMode* amode ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_LdSt32;
   i->ARM64in.LdSt32.isLoad = isLoad;
   i->ARM64in.LdSt32.rD     = rD;
   i->ARM64in.LdSt32.amode  = amode;
   return i;
}
ARM64Instr* ARM64Instr_LdSt16 ( Bool isLoad, HReg rD, ARM64AMode* amode ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_LdSt16;
   i->ARM64in.LdSt16.isLoad = isLoad;
   i->ARM64in.LdSt16.rD     = rD;
   i->ARM64in.LdSt16.amode  = amode;
   return i;
}
ARM64Instr* ARM64Instr_LdSt8 ( Bool isLoad, HReg rD, ARM64AMode* amode ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                  = ARM64in_LdSt8;
   i->ARM64in.LdSt8.isLoad = isLoad;
   i->ARM64in.LdSt8.rD     = rD;
   i->ARM64in.LdSt8.amode  = amode;
   return i;
}
ARM64Instr* ARM64Instr_XDirect ( Addr64 dstGA, ARM64AMode* amPC,
                                 ARM64CondCode cond, Bool toFastEP ) {
   ARM64Instr* i               = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                      = ARM64in_XDirect;
   i->ARM64in.XDirect.dstGA    = dstGA;
   i->ARM64in.XDirect.amPC     = amPC;
   i->ARM64in.XDirect.cond     = cond;
   i->ARM64in.XDirect.toFastEP = toFastEP;
   return i;
}
ARM64Instr* ARM64Instr_XIndir ( HReg dstGA, ARM64AMode* amPC,
                                ARM64CondCode cond ) {
   ARM64Instr* i           = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                  = ARM64in_XIndir;
   i->ARM64in.XIndir.dstGA = dstGA;
   i->ARM64in.XIndir.amPC  = amPC;
   i->ARM64in.XIndir.cond  = cond;
   return i;
}
ARM64Instr* ARM64Instr_XAssisted ( HReg dstGA, ARM64AMode* amPC,
                                   ARM64CondCode cond, IRJumpKind jk ) {
   ARM64Instr* i              = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                     = ARM64in_XAssisted;
   i->ARM64in.XAssisted.dstGA = dstGA;
   i->ARM64in.XAssisted.amPC  = amPC;
   i->ARM64in.XAssisted.cond  = cond;
   i->ARM64in.XAssisted.jk    = jk;
   return i;
}
ARM64Instr* ARM64Instr_CSel ( HReg dst, HReg argL, HReg argR,
                              ARM64CondCode cond ) {
   ARM64Instr* i        = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_CSel;
   i->ARM64in.CSel.dst  = dst;
   i->ARM64in.CSel.argL = argL;
   i->ARM64in.CSel.argR = argR;
   i->ARM64in.CSel.cond = cond;
   return i;
}
ARM64Instr* ARM64Instr_Call ( ARM64CondCode cond, HWord target, Int nArgRegs,
                              RetLoc rloc ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_Call;
   i->ARM64in.Call.cond     = cond;
   i->ARM64in.Call.target   = target;
   i->ARM64in.Call.nArgRegs = nArgRegs;
   i->ARM64in.Call.rloc     = rloc;
   vassert(is_sane_RetLoc(rloc));
   return i;
}
extern ARM64Instr* ARM64Instr_AddToSP ( Int simm ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                  = ARM64in_AddToSP;
   i->ARM64in.AddToSP.simm = simm;
   vassert(-4096 < simm && simm < 4096);
   vassert(0 == (simm & 0xF));
   return i;
}
extern ARM64Instr* ARM64Instr_FromSP  ( HReg dst ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_FromSP;
   i->ARM64in.FromSP.dst = dst;
   return i;
}
ARM64Instr* ARM64Instr_Mul ( HReg dst, HReg argL, HReg argR,
                             ARM64MulOp op ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag              = ARM64in_Mul;
   i->ARM64in.Mul.dst  = dst;
   i->ARM64in.Mul.argL = argL;
   i->ARM64in.Mul.argR = argR;
   i->ARM64in.Mul.op   = op;
   return i;
}
ARM64Instr* ARM64Instr_LdrEX ( Int szB ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_LdrEX;
   i->ARM64in.LdrEX.szB = szB;
   vassert(szB == 8 || szB == 4 || szB == 2 || szB == 1);
   return i;
}
ARM64Instr* ARM64Instr_StrEX ( Int szB ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_StrEX;
   i->ARM64in.StrEX.szB = szB;
   vassert(szB == 8 || szB == 4 || szB == 2 || szB == 1);
   return i;
}
ARM64Instr* ARM64Instr_MFence ( void ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag        = ARM64in_MFence;
   return i;
}
ARM64Instr* ARM64Instr_VLdStS ( Bool isLoad, HReg sD, HReg rN, UInt uimm12 ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                  = ARM64in_VLdStS;
   i->ARM64in.VLdStS.isLoad = isLoad;
   i->ARM64in.VLdStS.sD     = sD;
   i->ARM64in.VLdStS.rN     = rN;
   i->ARM64in.VLdStS.uimm12 = uimm12;
   vassert(uimm12 < 16384 && 0 == (uimm12 & 3));
   return i;
}
ARM64Instr* ARM64Instr_VLdStD ( Bool isLoad, HReg dD, HReg rN, UInt uimm12 ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                  = ARM64in_VLdStD;
   i->ARM64in.VLdStD.isLoad = isLoad;
   i->ARM64in.VLdStD.dD     = dD;
   i->ARM64in.VLdStD.rN     = rN;
   i->ARM64in.VLdStD.uimm12 = uimm12;
   vassert(uimm12 < 32768 && 0 == (uimm12 & 7));
   return i;
}
ARM64Instr* ARM64Instr_VLdStQ ( Bool isLoad, HReg rQ, HReg rN ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_VLdStQ;
   i->ARM64in.VLdStQ.isLoad = isLoad;
   i->ARM64in.VLdStQ.rQ     = rQ;
   i->ARM64in.VLdStQ.rN     = rN;
   return i;
}
ARM64Instr* ARM64Instr_VCvtI2F ( ARM64CvtOp how, HReg rD, HReg rS ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_VCvtI2F;
   i->ARM64in.VCvtI2F.how = how;
   i->ARM64in.VCvtI2F.rD  = rD;
   i->ARM64in.VCvtI2F.rS  = rS;
   return i;
}
ARM64Instr* ARM64Instr_VCvtF2I ( ARM64CvtOp how, HReg rD, HReg rS,
                                 UChar armRM ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_VCvtF2I;
   i->ARM64in.VCvtF2I.how   = how;
   i->ARM64in.VCvtF2I.rD    = rD;
   i->ARM64in.VCvtF2I.rS    = rS;
   i->ARM64in.VCvtF2I.armRM = armRM;
   vassert(armRM <= 3);
   return i;
}
ARM64Instr* ARM64Instr_VCvtSD ( Bool sToD, HReg dst, HReg src ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_VCvtSD;
   i->ARM64in.VCvtSD.sToD = sToD;
   i->ARM64in.VCvtSD.dst  = dst;
   i->ARM64in.VCvtSD.src  = src;
   return i;
}
ARM64Instr* ARM64Instr_VUnaryD ( ARM64FpUnaryOp op, HReg dst, HReg src ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_VUnaryD;
   i->ARM64in.VUnaryD.op  = op;
   i->ARM64in.VUnaryD.dst = dst;
   i->ARM64in.VUnaryD.src = src;
   return i;
}
ARM64Instr* ARM64Instr_VUnaryS ( ARM64FpUnaryOp op, HReg dst, HReg src ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_VUnaryS;
   i->ARM64in.VUnaryS.op  = op;
   i->ARM64in.VUnaryS.dst = dst;
   i->ARM64in.VUnaryS.src = src;
   return i;
}
ARM64Instr* ARM64Instr_VBinD ( ARM64FpBinOp op,
                               HReg dst, HReg argL, HReg argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VBinD;
   i->ARM64in.VBinD.op   = op;
   i->ARM64in.VBinD.dst  = dst;
   i->ARM64in.VBinD.argL = argL;
   i->ARM64in.VBinD.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_VBinS ( ARM64FpBinOp op,
                               HReg dst, HReg argL, HReg argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VBinS;
   i->ARM64in.VBinS.op   = op;
   i->ARM64in.VBinS.dst  = dst;
   i->ARM64in.VBinS.argL = argL;
   i->ARM64in.VBinS.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_VCmpD ( HReg argL, HReg argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VCmpD;
   i->ARM64in.VCmpD.argL = argL;
   i->ARM64in.VCmpD.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_VCmpS ( HReg argL, HReg argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VCmpS;
   i->ARM64in.VCmpS.argL = argL;
   i->ARM64in.VCmpS.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_FPCR ( Bool toFPCR, HReg iReg ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_FPCR;
   i->ARM64in.FPCR.toFPCR = toFPCR;
   i->ARM64in.FPCR.iReg   = iReg;
   return i;
}
ARM64Instr* ARM64Instr_VBinV ( ARM64VecBinOp op,
                               HReg dst, HReg argL, HReg argR ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VBinV;
   i->ARM64in.VBinV.op   = op;
   i->ARM64in.VBinV.dst  = dst;
   i->ARM64in.VBinV.argL = argL;
   i->ARM64in.VBinV.argR = argR;
   return i;
}
ARM64Instr* ARM64Instr_VUnaryV ( ARM64VecUnaryOp op, HReg dst, HReg arg ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                 = ARM64in_VUnaryV;
   i->ARM64in.VUnaryV.op  = op;
   i->ARM64in.VUnaryV.dst = dst;
   i->ARM64in.VUnaryV.arg = arg;
   return i;
}
ARM64Instr* ARM64Instr_VNarrowV ( UInt dszBlg2, HReg dst, HReg src ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                      = ARM64in_VNarrowV;
   i->ARM64in.VNarrowV.dszBlg2 = dszBlg2;
   i->ARM64in.VNarrowV.dst     = dst;
   i->ARM64in.VNarrowV.src     = src;
   vassert(dszBlg2 == 0 || dszBlg2 == 1 || dszBlg2 == 2);
   return i;
}
ARM64Instr* ARM64Instr_VShiftImmV ( ARM64VecShiftOp op,
                                    HReg dst, HReg src, UInt amt ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                    = ARM64in_VShiftImmV;
   i->ARM64in.VShiftImmV.op  = op;
   i->ARM64in.VShiftImmV.dst = dst;
   i->ARM64in.VShiftImmV.src = src;
   i->ARM64in.VShiftImmV.amt = amt;
   UInt maxSh = 0;
   switch (op) {
      case ARM64vecsh_USHR64x2: case ARM64vecsh_SSHR64x2:
      case ARM64vecsh_SHL64x2:
         maxSh = 63; break;
      case ARM64vecsh_USHR32x4: case ARM64vecsh_SSHR32x4:
      case ARM64vecsh_SHL32x4:
         maxSh = 31; break;
      case ARM64vecsh_USHR16x8: case ARM64vecsh_SSHR16x8:
      case ARM64vecsh_SHL16x8:
         maxSh = 15; break;
      case ARM64vecsh_USHR8x16: case ARM64vecsh_SSHR8x16:
      case ARM64vecsh_SHL8x16:
         maxSh = 7; break;
      default:
         vassert(0);
   }
   vassert(maxSh > 0);
   vassert(amt > 0 && amt <= maxSh);
   return i;
}

ARM64Instr* ARM64Instr_VImmQ (HReg rQ, UShort imm) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag               = ARM64in_VImmQ;
   i->ARM64in.VImmQ.rQ  = rQ;
   i->ARM64in.VImmQ.imm = imm;
   return i;
}
ARM64Instr* ARM64Instr_VDfromX ( HReg rD, HReg rX ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                = ARM64in_VDfromX;
   i->ARM64in.VDfromX.rD = rD;
   i->ARM64in.VDfromX.rX = rX;
   return i;
}
ARM64Instr* ARM64Instr_VQfromXX ( HReg rQ, HReg rXhi, HReg rXlo ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                   = ARM64in_VQfromXX;
   i->ARM64in.VQfromXX.rQ   = rQ;
   i->ARM64in.VQfromXX.rXhi = rXhi;
   i->ARM64in.VQfromXX.rXlo = rXlo;
   return i;
}
ARM64Instr* ARM64Instr_VXfromQ ( HReg rX, HReg rQ, UInt laneNo ) {
   ARM64Instr* i = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                    = ARM64in_VXfromQ;
   i->ARM64in.VXfromQ.rX     = rX;
   i->ARM64in.VXfromQ.rQ     = rQ;
   i->ARM64in.VXfromQ.laneNo = laneNo;
   vassert(laneNo <= 1);
   return i;
}
ARM64Instr* ARM64Instr_VMov ( UInt szB, HReg dst, HReg src ) {
   ARM64Instr* i       = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag              = ARM64in_VMov;
   i->ARM64in.VMov.szB = szB;
   i->ARM64in.VMov.dst = dst;
   i->ARM64in.VMov.src = src;
   switch (szB) {
      case 16:
        vassert(hregClass(src) == HRcVec128);
        vassert(hregClass(dst) == HRcVec128);
        break;
      case 8:
        vassert(hregClass(src) == HRcFlt64);
        vassert(hregClass(dst) == HRcFlt64);
        break;
      default:
        vpanic("ARM64Instr_VMov");
   }
   return i;
}


ARM64Instr* ARM64Instr_EvCheck ( ARM64AMode* amCounter,
                                 ARM64AMode* amFailAddr ) {
   ARM64Instr* i                 = LibVEX_Alloc(sizeof(ARM64Instr));
   i->tag                        = ARM64in_EvCheck;
   i->ARM64in.EvCheck.amCounter  = amCounter;
   i->ARM64in.EvCheck.amFailAddr = amFailAddr;
   return i;
}



void ppARM64Instr ( ARM64Instr* i ) {
   switch (i->tag) {
      case ARM64in_Arith:
         vex_printf("%s    ", i->ARM64in.Arith.isAdd ? "add" : "sub");
         ppHRegARM64(i->ARM64in.Arith.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Arith.argL);
         vex_printf(", ");
         ppARM64RIA(i->ARM64in.Arith.argR);
         return;
      case ARM64in_Cmp:
         vex_printf("cmp%s ", i->ARM64in.Cmp.is64 ? "   " : "(w)" );
         ppHRegARM64(i->ARM64in.Cmp.argL);
         vex_printf(", ");
         ppARM64RIA(i->ARM64in.Cmp.argR);
         return;
      case ARM64in_Logic:
         vex_printf("%s    ", showARM64LogicOp(i->ARM64in.Logic.op));
         ppHRegARM64(i->ARM64in.Logic.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Logic.argL);
         vex_printf(", ");
         ppARM64RIL(i->ARM64in.Logic.argR);
         return;
      case ARM64in_Test:
         vex_printf("tst    ");
         ppHRegARM64(i->ARM64in.Test.argL);
         vex_printf(", ");
         ppARM64RIL(i->ARM64in.Test.argR);
         return;
      case ARM64in_Shift:
         vex_printf("%s    ", showARM64ShiftOp(i->ARM64in.Shift.op));
         ppHRegARM64(i->ARM64in.Shift.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Shift.argL);
         vex_printf(", ");
         ppARM64RI6(i->ARM64in.Shift.argR);
         return;
      case ARM64in_Unary:
         vex_printf("%s    ", showARM64UnaryOp(i->ARM64in.Unary.op));
         ppHRegARM64(i->ARM64in.Unary.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Unary.src);
         return;
      case ARM64in_MovI:
         vex_printf("mov    ");
         ppHRegARM64(i->ARM64in.MovI.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.MovI.src);
         return;
      case ARM64in_Imm64:
         vex_printf("imm64  ");
         ppHRegARM64(i->ARM64in.Imm64.dst);
         vex_printf(", 0x%llx", i->ARM64in.Imm64.imm64);
         return;
      case ARM64in_LdSt64:
         if (i->ARM64in.LdSt64.isLoad) {
            vex_printf("ldr    ");
            ppHRegARM64(i->ARM64in.LdSt64.rD);
            vex_printf(", ");
            ppARM64AMode(i->ARM64in.LdSt64.amode);
         } else {
            vex_printf("str    ");
            ppARM64AMode(i->ARM64in.LdSt64.amode);
            vex_printf(", ");
            ppHRegARM64(i->ARM64in.LdSt64.rD);
         }
         return;
      case ARM64in_LdSt32:
         if (i->ARM64in.LdSt32.isLoad) {
            vex_printf("ldruw  ");
            ppHRegARM64(i->ARM64in.LdSt32.rD);
            vex_printf(", ");
            ppARM64AMode(i->ARM64in.LdSt32.amode);
         } else {
            vex_printf("strw   ");
            ppARM64AMode(i->ARM64in.LdSt32.amode);
            vex_printf(", ");
            ppHRegARM64(i->ARM64in.LdSt32.rD);
         }
         return;
      case ARM64in_LdSt16:
         if (i->ARM64in.LdSt16.isLoad) {
            vex_printf("ldruh  ");
            ppHRegARM64(i->ARM64in.LdSt16.rD);
            vex_printf(", ");
            ppARM64AMode(i->ARM64in.LdSt16.amode);
         } else {
            vex_printf("strh   ");
            ppARM64AMode(i->ARM64in.LdSt16.amode);
            vex_printf(", ");
            ppHRegARM64(i->ARM64in.LdSt16.rD);
         }
         return;
      case ARM64in_LdSt8:
         if (i->ARM64in.LdSt8.isLoad) {
            vex_printf("ldrub  ");
            ppHRegARM64(i->ARM64in.LdSt8.rD);
            vex_printf(", ");
            ppARM64AMode(i->ARM64in.LdSt8.amode);
         } else {
            vex_printf("strb   ");
            ppARM64AMode(i->ARM64in.LdSt8.amode);
            vex_printf(", ");
            ppHRegARM64(i->ARM64in.LdSt8.rD);
         }
         return;
      case ARM64in_XDirect:
         vex_printf("(xDirect) ");
         vex_printf("if (%%pstate.%s) { ",
                    showARM64CondCode(i->ARM64in.XDirect.cond));
         vex_printf("imm64 x9,0x%llx; ", i->ARM64in.XDirect.dstGA);
         vex_printf("str x9,");
         ppARM64AMode(i->ARM64in.XDirect.amPC);
         vex_printf("; imm64-exactly4 x9,$disp_cp_chain_me_to_%sEP; ",
                    i->ARM64in.XDirect.toFastEP ? "fast" : "slow");
         vex_printf("blr x9 }");
         return;
      case ARM64in_XIndir:
         vex_printf("(xIndir) ");
         vex_printf("if (%%pstate.%s) { ",
                    showARM64CondCode(i->ARM64in.XIndir.cond));
         vex_printf("str ");
         ppHRegARM64(i->ARM64in.XIndir.dstGA);
         vex_printf(",");
         ppARM64AMode(i->ARM64in.XIndir.amPC);
         vex_printf("; imm64 x9,$disp_cp_xindir; ");
         vex_printf("br x9 }");
         return;
      case ARM64in_XAssisted:
         vex_printf("(xAssisted) ");
         vex_printf("if (%%pstate.%s) { ",
                    showARM64CondCode(i->ARM64in.XAssisted.cond));
         vex_printf("str ");
         ppHRegARM64(i->ARM64in.XAssisted.dstGA);
         vex_printf(",");
         ppARM64AMode(i->ARM64in.XAssisted.amPC);
         vex_printf("; movw x21,$IRJumpKind_to_TRCVAL(%d); ",
                    (Int)i->ARM64in.XAssisted.jk);
         vex_printf("imm64 x9,$disp_cp_xassisted; ");
         vex_printf("br x9 }");
         return;
      case ARM64in_CSel:
         vex_printf("csel   ");
         ppHRegARM64(i->ARM64in.CSel.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.CSel.argL);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.CSel.argR);
         vex_printf(", %s", showARM64CondCode(i->ARM64in.CSel.cond));
         return;
      case ARM64in_Call:
         vex_printf("call%s ",
                    i->ARM64in.Call.cond==ARM64cc_AL
                       ? "  " : showARM64CondCode(i->ARM64in.Call.cond));
         vex_printf("0x%lx [nArgRegs=%d, ",
                    i->ARM64in.Call.target, i->ARM64in.Call.nArgRegs);
         ppRetLoc(i->ARM64in.Call.rloc);
         vex_printf("]");
         return;
      case ARM64in_AddToSP: {
         Int simm = i->ARM64in.AddToSP.simm;
         vex_printf("%s    xsp, xsp, #%d", simm < 0 ? "sub" : "add", 
                                           simm < 0 ? -simm : simm);
         return;
      }
      case ARM64in_FromSP:
         vex_printf("mov    ");
         ppHRegARM64(i->ARM64in.FromSP.dst);
         vex_printf(", xsp");
         return;
      case ARM64in_Mul:
         vex_printf("%s  ", showARM64MulOp(i->ARM64in.Mul.op));
         ppHRegARM64(i->ARM64in.Mul.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Mul.argL);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.Mul.argR);
         return;

      case ARM64in_LdrEX: {
         const HChar* sz = " ";
         switch (i->ARM64in.LdrEX.szB) {
            case 1: sz = "b"; break;
            case 2: sz = "h"; break;
            case 4: case 8: break;
            default: vassert(0);
         }
         vex_printf("ldxr%s  %c2, [x4]",
                    sz, i->ARM64in.LdrEX.szB == 8 ? 'x' : 'w');
         return;
      }
      case ARM64in_StrEX: {
         const HChar* sz = " ";
         switch (i->ARM64in.StrEX.szB) {
            case 1: sz = "b"; break;
            case 2: sz = "h"; break;
            case 4: case 8: break;
            default: vassert(0);
         }
         vex_printf("stxr%s  w0, %c2, [x4]",
                    sz, i->ARM64in.StrEX.szB == 8 ? 'x' : 'w');
         return;
      }
      case ARM64in_MFence:
         vex_printf("(mfence) dsb sy; dmb sy; isb");
         return;
      case ARM64in_VLdStS:
         if (i->ARM64in.VLdStS.isLoad) {
            vex_printf("ldr    ");
            ppHRegARM64asSreg(i->ARM64in.VLdStS.sD);
            vex_printf(", %u(", i->ARM64in.VLdStS.uimm12);
            ppHRegARM64(i->ARM64in.VLdStS.rN);
            vex_printf(")");
         } else {
            vex_printf("str    ");
            vex_printf("%u(", i->ARM64in.VLdStS.uimm12);
            ppHRegARM64(i->ARM64in.VLdStS.rN);
            vex_printf("), ");
            ppHRegARM64asSreg(i->ARM64in.VLdStS.sD);
         }
         return;
      case ARM64in_VLdStD:
         if (i->ARM64in.VLdStD.isLoad) {
            vex_printf("ldr    ");
            ppHRegARM64(i->ARM64in.VLdStD.dD);
            vex_printf(", %u(", i->ARM64in.VLdStD.uimm12);
            ppHRegARM64(i->ARM64in.VLdStD.rN);
            vex_printf(")");
         } else {
            vex_printf("str    ");
            vex_printf("%u(", i->ARM64in.VLdStD.uimm12);
            ppHRegARM64(i->ARM64in.VLdStD.rN);
            vex_printf("), ");
            ppHRegARM64(i->ARM64in.VLdStD.dD);
         }
         return;
      case ARM64in_VLdStQ:
         if (i->ARM64in.VLdStQ.isLoad)
            vex_printf("ld1.2d {");
         else
            vex_printf("st1.2d {");
         ppHRegARM64(i->ARM64in.VLdStQ.rQ);
         vex_printf("}, [");
         ppHRegARM64(i->ARM64in.VLdStQ.rN);
         vex_printf("]");
         return;
      case ARM64in_VCvtI2F: {
         HChar syn  = '?';
         UInt  fszB = 0;
         UInt  iszB = 0;
         characteriseARM64CvtOp(&syn, &fszB, &iszB, i->ARM64in.VCvtI2F.how);
         vex_printf("%ccvtf  ", syn);
         ppHRegARM64(i->ARM64in.VCvtI2F.rD);
         vex_printf("(%c-reg), ", fszB == 4 ? 'S' : 'D');
         ppHRegARM64(i->ARM64in.VCvtI2F.rS);
         vex_printf("(%c-reg)", iszB == 4 ? 'W' : 'X');
         return;
      }
      case ARM64in_VCvtF2I: {
         HChar syn  = '?';
         UInt  fszB = 0;
         UInt  iszB = 0;
         HChar rmo  = '?';
         characteriseARM64CvtOp(&syn, &fszB, &iszB, i->ARM64in.VCvtF2I.how);
         UChar armRM = i->ARM64in.VCvtF2I.armRM;
         if (armRM < 4) rmo = "npmz"[armRM];
         vex_printf("fcvt%c%c ", rmo, syn);
         ppHRegARM64(i->ARM64in.VCvtF2I.rD);
         vex_printf("(%c-reg), ", iszB == 4 ? 'W' : 'X');
         ppHRegARM64(i->ARM64in.VCvtF2I.rS);
         vex_printf("(%c-reg)", fszB == 4 ? 'S' : 'D');
         return;
      }
      case ARM64in_VCvtSD:
         vex_printf("fcvt%s ", i->ARM64in.VCvtSD.sToD ? "s2d" : "d2s");
         if (i->ARM64in.VCvtSD.sToD) {
            ppHRegARM64(i->ARM64in.VCvtSD.dst);
            vex_printf(", ");
            ppHRegARM64asSreg(i->ARM64in.VCvtSD.src);
         } else {
            ppHRegARM64asSreg(i->ARM64in.VCvtSD.dst);
            vex_printf(", ");
            ppHRegARM64(i->ARM64in.VCvtSD.src);
         }
         return;
      case ARM64in_VUnaryD:
         vex_printf("f%s ", showARM64FpUnaryOp(i->ARM64in.VUnaryD.op));
         ppHRegARM64(i->ARM64in.VUnaryD.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VUnaryD.src);
         return;
      case ARM64in_VUnaryS:
         vex_printf("f%s ", showARM64FpUnaryOp(i->ARM64in.VUnaryS.op));
         ppHRegARM64asSreg(i->ARM64in.VUnaryS.dst);
         vex_printf(", ");
         ppHRegARM64asSreg(i->ARM64in.VUnaryS.src);
         return;
      case ARM64in_VBinD:
         vex_printf("f%s   ", showARM64FpBinOp(i->ARM64in.VBinD.op));
         ppHRegARM64(i->ARM64in.VBinD.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VBinD.argL);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VBinD.argR);
         return;
      case ARM64in_VBinS:
         vex_printf("f%s   ", showARM64FpBinOp(i->ARM64in.VBinS.op));
         ppHRegARM64asSreg(i->ARM64in.VBinS.dst);
         vex_printf(", ");
         ppHRegARM64asSreg(i->ARM64in.VBinS.argL);
         vex_printf(", ");
         ppHRegARM64asSreg(i->ARM64in.VBinS.argR);
         return;
      case ARM64in_VCmpD:
         vex_printf("fcmp   ");
         ppHRegARM64(i->ARM64in.VCmpD.argL);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VCmpD.argR);
         return;
      case ARM64in_VCmpS:
         vex_printf("fcmp   ");
         ppHRegARM64asSreg(i->ARM64in.VCmpS.argL);
         vex_printf(", ");
         ppHRegARM64asSreg(i->ARM64in.VCmpS.argR);
         return;
      case ARM64in_FPCR:
         if (i->ARM64in.FPCR.toFPCR) {
            vex_printf("msr    fpcr, ");
            ppHRegARM64(i->ARM64in.FPCR.iReg);
         } else {
            vex_printf("mrs    ");
            ppHRegARM64(i->ARM64in.FPCR.iReg);
            vex_printf(", fpcr");
         }
         return;
      case ARM64in_VBinV: {
         const HChar* nm = "??";
         const HChar* ar = "??";
         showARM64VecBinOp(&nm, &ar, i->ARM64in.VBinV.op);
         vex_printf("%s   ", nm);
         ppHRegARM64(i->ARM64in.VBinV.dst);
         vex_printf(".%s, ", ar);
         ppHRegARM64(i->ARM64in.VBinV.argL);
         vex_printf(".%s, ", ar);
         ppHRegARM64(i->ARM64in.VBinV.argR);
         vex_printf(".%s", ar);
         return;
      }
      case ARM64in_VUnaryV: {
         const HChar* nm = "??";
         const HChar* ar = "??";
         showARM64VecUnaryOp(&nm, &ar, i->ARM64in.VUnaryV.op);
         vex_printf("%s  ", nm);
         ppHRegARM64(i->ARM64in.VUnaryV.dst);
         vex_printf(".%s, ", ar);
         ppHRegARM64(i->ARM64in.VUnaryV.arg);
         vex_printf(".%s", ar);
         return;
      }
      case ARM64in_VNarrowV: {
         UInt dszBlg2 = i->ARM64in.VNarrowV.dszBlg2;
         const HChar* darr[3] = { "8b", "4h", "2s" };
         const HChar* sarr[3] = { "8h", "4s", "2d" };
         vex_printf("xtn    ");
         ppHRegARM64(i->ARM64in.VNarrowV.dst);
         vex_printf(".%s, ", dszBlg2 < 3 ? darr[dszBlg2] : "??");
         ppHRegARM64(i->ARM64in.VNarrowV.src);
         vex_printf(".%s", dszBlg2 < 3 ? sarr[dszBlg2] : "??");
         return;
      }
      case ARM64in_VShiftImmV: {
         const HChar* nm = "??";
         const HChar* ar = "??";
         showARM64VecShiftOp(&nm, &ar, i->ARM64in.VShiftImmV.op);
         vex_printf("%s ", nm);
         ppHRegARM64(i->ARM64in.VShiftImmV.dst);
         vex_printf(".%s, ", ar);
         ppHRegARM64(i->ARM64in.VShiftImmV.src);
         vex_printf(".%s, #%u", ar, i->ARM64in.VShiftImmV.amt);
         return;
      }
      case ARM64in_VImmQ:
         vex_printf("qimm   ");
         ppHRegARM64(i->ARM64in.VImmQ.rQ);
         vex_printf(", Bits16toBytes16(0x%x)", (UInt)i->ARM64in.VImmQ.imm);
         return;
      case ARM64in_VDfromX:
         vex_printf("fmov   ");
         ppHRegARM64(i->ARM64in.VDfromX.rD);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VDfromX.rX);
         return;
      case ARM64in_VQfromXX:
         vex_printf("qFromXX ");
         ppHRegARM64(i->ARM64in.VQfromXX.rQ);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VQfromXX.rXhi);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VQfromXX.rXlo);
         return;
      case ARM64in_VXfromQ:
         vex_printf("mov    ");
         ppHRegARM64(i->ARM64in.VXfromQ.rX);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VXfromQ.rQ);
         vex_printf(".d[%u]", i->ARM64in.VXfromQ.laneNo);
         return;
      case ARM64in_VMov: {
         UChar aux = '?';
         switch (i->ARM64in.VMov.szB) {
            case 16: aux = 'q'; break;
            case 8:  aux = 'd'; break;
            case 4:  aux = 's'; break;
            default: break;
         }
         vex_printf("mov(%c) ", aux);
         ppHRegARM64(i->ARM64in.VMov.dst);
         vex_printf(", ");
         ppHRegARM64(i->ARM64in.VMov.src);
         return;
   }
      case ARM64in_EvCheck:
         vex_printf("(evCheck) ldr w9,");
         ppARM64AMode(i->ARM64in.EvCheck.amCounter);
         vex_printf("; subs w9,w9,$1; str w9,");
         ppARM64AMode(i->ARM64in.EvCheck.amCounter);
         vex_printf("; bpl nofail; ldr x9,");
         ppARM64AMode(i->ARM64in.EvCheck.amFailAddr);
         vex_printf("; br x9; nofail:");
         return;
      default:
         vex_printf("ppARM64Instr: unhandled case (tag %d)", (Int)i->tag);
         vpanic("ppARM64Instr(1)");
         return;
   }
}



void getRegUsage_ARM64Instr ( HRegUsage* u, ARM64Instr* i, Bool mode64 )
{
   vassert(mode64 == True);
   initHRegUsage(u);
   switch (i->tag) {
      case ARM64in_Arith:
         addHRegUse(u, HRmWrite, i->ARM64in.Arith.dst);
         addHRegUse(u, HRmRead, i->ARM64in.Arith.argL);
         addRegUsage_ARM64RIA(u, i->ARM64in.Arith.argR);
         return;
      case ARM64in_Cmp:
         addHRegUse(u, HRmRead, i->ARM64in.Cmp.argL);
         addRegUsage_ARM64RIA(u, i->ARM64in.Cmp.argR);
         return;
      case ARM64in_Logic:
         addHRegUse(u, HRmWrite, i->ARM64in.Logic.dst);
         addHRegUse(u, HRmRead, i->ARM64in.Logic.argL);
         addRegUsage_ARM64RIL(u, i->ARM64in.Logic.argR);
         return;
      case ARM64in_Test:
         addHRegUse(u, HRmRead, i->ARM64in.Test.argL);
         addRegUsage_ARM64RIL(u, i->ARM64in.Test.argR);
         return;
      case ARM64in_Shift:
         addHRegUse(u, HRmWrite, i->ARM64in.Shift.dst);
         addHRegUse(u, HRmRead, i->ARM64in.Shift.argL);
         addRegUsage_ARM64RI6(u, i->ARM64in.Shift.argR);
         return;
      case ARM64in_Unary:
         addHRegUse(u, HRmWrite, i->ARM64in.Unary.dst);
         addHRegUse(u, HRmRead, i->ARM64in.Unary.src);
         return;
      case ARM64in_MovI:
         addHRegUse(u, HRmWrite, i->ARM64in.MovI.dst);
         addHRegUse(u, HRmRead,  i->ARM64in.MovI.src);
         return;
      case ARM64in_Imm64:
         addHRegUse(u, HRmWrite, i->ARM64in.Imm64.dst);
         return;
      case ARM64in_LdSt64:
         addRegUsage_ARM64AMode(u, i->ARM64in.LdSt64.amode);
         if (i->ARM64in.LdSt64.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.LdSt64.rD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.LdSt64.rD);
         }
         return;
      case ARM64in_LdSt32:
         addRegUsage_ARM64AMode(u, i->ARM64in.LdSt32.amode);
         if (i->ARM64in.LdSt32.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.LdSt32.rD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.LdSt32.rD);
         }
         return;
      case ARM64in_LdSt16:
         addRegUsage_ARM64AMode(u, i->ARM64in.LdSt16.amode);
         if (i->ARM64in.LdSt16.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.LdSt16.rD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.LdSt16.rD);
         }
         return;
      case ARM64in_LdSt8:
         addRegUsage_ARM64AMode(u, i->ARM64in.LdSt8.amode);
         if (i->ARM64in.LdSt8.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.LdSt8.rD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.LdSt8.rD);
         }
         return;
      case ARM64in_XDirect:
         addRegUsage_ARM64AMode(u, i->ARM64in.XDirect.amPC);
         return;
      case ARM64in_XIndir:
         addHRegUse(u, HRmRead, i->ARM64in.XIndir.dstGA);
         addRegUsage_ARM64AMode(u, i->ARM64in.XIndir.amPC);
         return;
      case ARM64in_XAssisted:
         addHRegUse(u, HRmRead, i->ARM64in.XAssisted.dstGA);
         addRegUsage_ARM64AMode(u, i->ARM64in.XAssisted.amPC);
         return;
      case ARM64in_CSel:
         addHRegUse(u, HRmWrite, i->ARM64in.CSel.dst);
         addHRegUse(u, HRmRead,  i->ARM64in.CSel.argL);
         addHRegUse(u, HRmRead,  i->ARM64in.CSel.argR);
         return;
      case ARM64in_Call:
         
         
         addHRegUse(u, HRmWrite, hregARM64_X0());
         addHRegUse(u, HRmWrite, hregARM64_X1());
         addHRegUse(u, HRmWrite, hregARM64_X2());
         addHRegUse(u, HRmWrite, hregARM64_X3());
         addHRegUse(u, HRmWrite, hregARM64_X4());
         addHRegUse(u, HRmWrite, hregARM64_X5());
         addHRegUse(u, HRmWrite, hregARM64_X6());
         addHRegUse(u, HRmWrite, hregARM64_X7());
         addHRegUse(u, HRmWrite, hregARM64_Q16());
         addHRegUse(u, HRmWrite, hregARM64_Q17());
         addHRegUse(u, HRmWrite, hregARM64_Q18());
            switch (i->ARM64in.Call.nArgRegs) {
            case 8: addHRegUse(u, HRmRead, hregARM64_X7()); 
            case 7: addHRegUse(u, HRmRead, hregARM64_X6()); 
            case 6: addHRegUse(u, HRmRead, hregARM64_X5()); 
            case 5: addHRegUse(u, HRmRead, hregARM64_X4()); 
            case 4: addHRegUse(u, HRmRead, hregARM64_X3()); 
            case 3: addHRegUse(u, HRmRead, hregARM64_X2()); 
            case 2: addHRegUse(u, HRmRead, hregARM64_X1()); 
            case 1: addHRegUse(u, HRmRead, hregARM64_X0()); break;
            case 0: break;
            default: vpanic("getRegUsage_ARM64:Call:regparms");
         }
         addHRegUse(u, HRmWrite, hregARM64_X9());
         return;
      case ARM64in_AddToSP:
         return;
      case ARM64in_FromSP:
         addHRegUse(u, HRmWrite, i->ARM64in.FromSP.dst);
         return;
      case ARM64in_Mul:
         addHRegUse(u, HRmWrite, i->ARM64in.Mul.dst);
         addHRegUse(u, HRmRead,  i->ARM64in.Mul.argL);
         addHRegUse(u, HRmRead,  i->ARM64in.Mul.argR);
         return;
      case ARM64in_LdrEX:
         addHRegUse(u, HRmRead, hregARM64_X4());
         addHRegUse(u, HRmWrite, hregARM64_X2());
         return;
      case ARM64in_StrEX:
         addHRegUse(u, HRmRead, hregARM64_X4());
         addHRegUse(u, HRmWrite, hregARM64_X0());
         addHRegUse(u, HRmRead, hregARM64_X2());
         return;
      case ARM64in_MFence:
         return;
      case ARM64in_VLdStS:
         addHRegUse(u, HRmRead, i->ARM64in.VLdStS.rN);
         if (i->ARM64in.VLdStS.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.VLdStS.sD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.VLdStS.sD);
         }
         return;
      case ARM64in_VLdStD:
         addHRegUse(u, HRmRead, i->ARM64in.VLdStD.rN);
         if (i->ARM64in.VLdStD.isLoad) {
            addHRegUse(u, HRmWrite, i->ARM64in.VLdStD.dD);
         } else {
            addHRegUse(u, HRmRead, i->ARM64in.VLdStD.dD);
         }
         return;
      case ARM64in_VLdStQ:
         addHRegUse(u, HRmRead, i->ARM64in.VLdStQ.rN);
         if (i->ARM64in.VLdStQ.isLoad)
            addHRegUse(u, HRmWrite, i->ARM64in.VLdStQ.rQ);
         else
            addHRegUse(u, HRmRead, i->ARM64in.VLdStQ.rQ);
         return;
      case ARM64in_VCvtI2F:
         addHRegUse(u, HRmRead, i->ARM64in.VCvtI2F.rS);
         addHRegUse(u, HRmWrite, i->ARM64in.VCvtI2F.rD);
         return;
      case ARM64in_VCvtF2I:
         addHRegUse(u, HRmRead, i->ARM64in.VCvtF2I.rS);
         addHRegUse(u, HRmWrite, i->ARM64in.VCvtF2I.rD);
         return;
      case ARM64in_VCvtSD:
         addHRegUse(u, HRmWrite, i->ARM64in.VCvtSD.dst);
         addHRegUse(u, HRmRead,  i->ARM64in.VCvtSD.src);
         return;
      case ARM64in_VUnaryD:
         addHRegUse(u, HRmWrite, i->ARM64in.VUnaryD.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VUnaryD.src);
         return;
      case ARM64in_VUnaryS:
         addHRegUse(u, HRmWrite, i->ARM64in.VUnaryS.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VUnaryS.src);
         return;
      case ARM64in_VBinD:
         addHRegUse(u, HRmWrite, i->ARM64in.VBinD.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VBinD.argL);
         addHRegUse(u, HRmRead, i->ARM64in.VBinD.argR);
         return;
      case ARM64in_VBinS:
         addHRegUse(u, HRmWrite, i->ARM64in.VBinS.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VBinS.argL);
         addHRegUse(u, HRmRead, i->ARM64in.VBinS.argR);
         return;
      case ARM64in_VCmpD:
         addHRegUse(u, HRmRead, i->ARM64in.VCmpD.argL);
         addHRegUse(u, HRmRead, i->ARM64in.VCmpD.argR);
         return;
      case ARM64in_VCmpS:
         addHRegUse(u, HRmRead, i->ARM64in.VCmpS.argL);
         addHRegUse(u, HRmRead, i->ARM64in.VCmpS.argR);
         return;
      case ARM64in_FPCR:
         if (i->ARM64in.FPCR.toFPCR)
            addHRegUse(u, HRmRead, i->ARM64in.FPCR.iReg);
         else
            addHRegUse(u, HRmWrite, i->ARM64in.FPCR.iReg);
         return;
      case ARM64in_VBinV:
         addHRegUse(u, HRmWrite, i->ARM64in.VBinV.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VBinV.argL);
         addHRegUse(u, HRmRead, i->ARM64in.VBinV.argR);
         return;
      case ARM64in_VUnaryV:
         addHRegUse(u, HRmWrite, i->ARM64in.VUnaryV.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VUnaryV.arg);
         return;
      case ARM64in_VNarrowV:
         addHRegUse(u, HRmWrite, i->ARM64in.VNarrowV.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VNarrowV.src);
         return;
      case ARM64in_VShiftImmV:
         addHRegUse(u, HRmWrite, i->ARM64in.VShiftImmV.dst);
         addHRegUse(u, HRmRead, i->ARM64in.VShiftImmV.src);
         return;
      case ARM64in_VImmQ:
         addHRegUse(u, HRmWrite, i->ARM64in.VImmQ.rQ);
         return;
      case ARM64in_VDfromX:
         addHRegUse(u, HRmWrite, i->ARM64in.VDfromX.rD);
         addHRegUse(u, HRmRead,  i->ARM64in.VDfromX.rX);
         return;
      case ARM64in_VQfromXX:
         addHRegUse(u, HRmWrite, i->ARM64in.VQfromXX.rQ);
         addHRegUse(u, HRmRead,  i->ARM64in.VQfromXX.rXhi);
         addHRegUse(u, HRmRead,  i->ARM64in.VQfromXX.rXlo);
         return;
      case ARM64in_VXfromQ:
         addHRegUse(u, HRmWrite, i->ARM64in.VXfromQ.rX);
         addHRegUse(u, HRmRead,  i->ARM64in.VXfromQ.rQ);
         return;
      case ARM64in_VMov:
         addHRegUse(u, HRmWrite, i->ARM64in.VMov.dst);
         addHRegUse(u, HRmRead,  i->ARM64in.VMov.src);
         return;
      case ARM64in_EvCheck:
         addRegUsage_ARM64AMode(u, i->ARM64in.EvCheck.amCounter);
         addRegUsage_ARM64AMode(u, i->ARM64in.EvCheck.amFailAddr);
         addHRegUse(u, HRmWrite, hregARM64_X9()); 
         return;
      default:
         ppARM64Instr(i);
         vpanic("getRegUsage_ARM64Instr");
   }
}


void mapRegs_ARM64Instr ( HRegRemap* m, ARM64Instr* i, Bool mode64 )
{
   vassert(mode64 == True);
   switch (i->tag) {
      case ARM64in_Arith:
         i->ARM64in.Arith.dst = lookupHRegRemap(m, i->ARM64in.Arith.dst);
         i->ARM64in.Arith.argL = lookupHRegRemap(m, i->ARM64in.Arith.argL);
         mapRegs_ARM64RIA(m, i->ARM64in.Arith.argR);
         return;
      case ARM64in_Cmp:
         i->ARM64in.Cmp.argL = lookupHRegRemap(m, i->ARM64in.Cmp.argL);
         mapRegs_ARM64RIA(m, i->ARM64in.Cmp.argR);
         return;
      case ARM64in_Logic:
         i->ARM64in.Logic.dst = lookupHRegRemap(m, i->ARM64in.Logic.dst);
         i->ARM64in.Logic.argL = lookupHRegRemap(m, i->ARM64in.Logic.argL);
         mapRegs_ARM64RIL(m, i->ARM64in.Logic.argR);
         return;
      case ARM64in_Test:
         i->ARM64in.Test.argL = lookupHRegRemap(m, i->ARM64in.Test.argL);
         mapRegs_ARM64RIL(m, i->ARM64in.Logic.argR);
         return;
      case ARM64in_Shift:
         i->ARM64in.Shift.dst = lookupHRegRemap(m, i->ARM64in.Shift.dst);
         i->ARM64in.Shift.argL = lookupHRegRemap(m, i->ARM64in.Shift.argL);
         mapRegs_ARM64RI6(m, i->ARM64in.Shift.argR);
         return;
      case ARM64in_Unary:
         i->ARM64in.Unary.dst = lookupHRegRemap(m, i->ARM64in.Unary.dst);
         i->ARM64in.Unary.src = lookupHRegRemap(m, i->ARM64in.Unary.src);
         return;
      case ARM64in_MovI:
         i->ARM64in.MovI.dst = lookupHRegRemap(m, i->ARM64in.MovI.dst);
         i->ARM64in.MovI.src = lookupHRegRemap(m, i->ARM64in.MovI.src);
         return;
      case ARM64in_Imm64:
         i->ARM64in.Imm64.dst = lookupHRegRemap(m, i->ARM64in.Imm64.dst);
         return;
      case ARM64in_LdSt64:
         i->ARM64in.LdSt64.rD = lookupHRegRemap(m, i->ARM64in.LdSt64.rD);
         mapRegs_ARM64AMode(m, i->ARM64in.LdSt64.amode);
         return;
      case ARM64in_LdSt32:
         i->ARM64in.LdSt32.rD = lookupHRegRemap(m, i->ARM64in.LdSt32.rD);
         mapRegs_ARM64AMode(m, i->ARM64in.LdSt32.amode);
         return;
      case ARM64in_LdSt16:
         i->ARM64in.LdSt16.rD = lookupHRegRemap(m, i->ARM64in.LdSt16.rD);
         mapRegs_ARM64AMode(m, i->ARM64in.LdSt16.amode);
         return;
      case ARM64in_LdSt8:
         i->ARM64in.LdSt8.rD = lookupHRegRemap(m, i->ARM64in.LdSt8.rD);
         mapRegs_ARM64AMode(m, i->ARM64in.LdSt8.amode);
         return;
      case ARM64in_XDirect:
         mapRegs_ARM64AMode(m, i->ARM64in.XDirect.amPC);
         return;
      case ARM64in_XIndir:
         i->ARM64in.XIndir.dstGA
            = lookupHRegRemap(m, i->ARM64in.XIndir.dstGA);
         mapRegs_ARM64AMode(m, i->ARM64in.XIndir.amPC);
         return;
      case ARM64in_XAssisted:
         i->ARM64in.XAssisted.dstGA
            = lookupHRegRemap(m, i->ARM64in.XAssisted.dstGA);
         mapRegs_ARM64AMode(m, i->ARM64in.XAssisted.amPC);
         return;
      case ARM64in_CSel:
         i->ARM64in.CSel.dst  = lookupHRegRemap(m, i->ARM64in.CSel.dst);
         i->ARM64in.CSel.argL = lookupHRegRemap(m, i->ARM64in.CSel.argL);
         i->ARM64in.CSel.argR = lookupHRegRemap(m, i->ARM64in.CSel.argR);
         return;
      case ARM64in_Call:
         return;
      case ARM64in_AddToSP:
         return;
      case ARM64in_FromSP:
         i->ARM64in.FromSP.dst = lookupHRegRemap(m, i->ARM64in.FromSP.dst);
         return;
      case ARM64in_Mul:
         i->ARM64in.Mul.dst  = lookupHRegRemap(m, i->ARM64in.Mul.dst);
         i->ARM64in.Mul.argL = lookupHRegRemap(m, i->ARM64in.Mul.argL);
         i->ARM64in.Mul.argR = lookupHRegRemap(m, i->ARM64in.Mul.argR);
         break;
      case ARM64in_LdrEX:
         return;
      case ARM64in_StrEX:
         return;
      case ARM64in_MFence:
         return;
      case ARM64in_VLdStS:
         i->ARM64in.VLdStS.sD = lookupHRegRemap(m, i->ARM64in.VLdStS.sD);
         i->ARM64in.VLdStS.rN = lookupHRegRemap(m, i->ARM64in.VLdStS.rN);
         return;
      case ARM64in_VLdStD:
         i->ARM64in.VLdStD.dD = lookupHRegRemap(m, i->ARM64in.VLdStD.dD);
         i->ARM64in.VLdStD.rN = lookupHRegRemap(m, i->ARM64in.VLdStD.rN);
         return;
      case ARM64in_VLdStQ:
         i->ARM64in.VLdStQ.rQ = lookupHRegRemap(m, i->ARM64in.VLdStQ.rQ);
         i->ARM64in.VLdStQ.rN = lookupHRegRemap(m, i->ARM64in.VLdStQ.rN);
         return;
      case ARM64in_VCvtI2F:
         i->ARM64in.VCvtI2F.rS = lookupHRegRemap(m, i->ARM64in.VCvtI2F.rS);
         i->ARM64in.VCvtI2F.rD = lookupHRegRemap(m, i->ARM64in.VCvtI2F.rD);
         return;
      case ARM64in_VCvtF2I:
         i->ARM64in.VCvtF2I.rS = lookupHRegRemap(m, i->ARM64in.VCvtF2I.rS);
         i->ARM64in.VCvtF2I.rD = lookupHRegRemap(m, i->ARM64in.VCvtF2I.rD);
         return;
      case ARM64in_VCvtSD:
         i->ARM64in.VCvtSD.dst = lookupHRegRemap(m, i->ARM64in.VCvtSD.dst);
         i->ARM64in.VCvtSD.src = lookupHRegRemap(m, i->ARM64in.VCvtSD.src);
         return;
      case ARM64in_VUnaryD:
         i->ARM64in.VUnaryD.dst = lookupHRegRemap(m, i->ARM64in.VUnaryD.dst);
         i->ARM64in.VUnaryD.src = lookupHRegRemap(m, i->ARM64in.VUnaryD.src);
         return;
      case ARM64in_VUnaryS:
         i->ARM64in.VUnaryS.dst = lookupHRegRemap(m, i->ARM64in.VUnaryS.dst);
         i->ARM64in.VUnaryS.src = lookupHRegRemap(m, i->ARM64in.VUnaryS.src);
         return;
      case ARM64in_VBinD:
         i->ARM64in.VBinD.dst  = lookupHRegRemap(m, i->ARM64in.VBinD.dst);
         i->ARM64in.VBinD.argL = lookupHRegRemap(m, i->ARM64in.VBinD.argL);
         i->ARM64in.VBinD.argR = lookupHRegRemap(m, i->ARM64in.VBinD.argR);
         return;
      case ARM64in_VBinS:
         i->ARM64in.VBinS.dst  = lookupHRegRemap(m, i->ARM64in.VBinS.dst);
         i->ARM64in.VBinS.argL = lookupHRegRemap(m, i->ARM64in.VBinS.argL);
         i->ARM64in.VBinS.argR = lookupHRegRemap(m, i->ARM64in.VBinS.argR);
         return;
      case ARM64in_VCmpD:
         i->ARM64in.VCmpD.argL = lookupHRegRemap(m, i->ARM64in.VCmpD.argL);
         i->ARM64in.VCmpD.argR = lookupHRegRemap(m, i->ARM64in.VCmpD.argR);
         return;
      case ARM64in_VCmpS:
         i->ARM64in.VCmpS.argL = lookupHRegRemap(m, i->ARM64in.VCmpS.argL);
         i->ARM64in.VCmpS.argR = lookupHRegRemap(m, i->ARM64in.VCmpS.argR);
         return;
      case ARM64in_FPCR:
         i->ARM64in.FPCR.iReg = lookupHRegRemap(m, i->ARM64in.FPCR.iReg);
         return;
      case ARM64in_VBinV:
         i->ARM64in.VBinV.dst  = lookupHRegRemap(m, i->ARM64in.VBinV.dst);
         i->ARM64in.VBinV.argL = lookupHRegRemap(m, i->ARM64in.VBinV.argL);
         i->ARM64in.VBinV.argR = lookupHRegRemap(m, i->ARM64in.VBinV.argR);
         return;
      case ARM64in_VUnaryV:
         i->ARM64in.VUnaryV.dst = lookupHRegRemap(m, i->ARM64in.VUnaryV.dst);
         i->ARM64in.VUnaryV.arg = lookupHRegRemap(m, i->ARM64in.VUnaryV.arg);
         return;
      case ARM64in_VNarrowV:
         i->ARM64in.VNarrowV.dst = lookupHRegRemap(m, i->ARM64in.VNarrowV.dst);
         i->ARM64in.VNarrowV.src = lookupHRegRemap(m, i->ARM64in.VNarrowV.src);
         return;
      case ARM64in_VShiftImmV:
         i->ARM64in.VShiftImmV.dst
            = lookupHRegRemap(m, i->ARM64in.VShiftImmV.dst);
         i->ARM64in.VShiftImmV.src
            = lookupHRegRemap(m, i->ARM64in.VShiftImmV.src);
         return;
      case ARM64in_VImmQ:
         i->ARM64in.VImmQ.rQ = lookupHRegRemap(m, i->ARM64in.VImmQ.rQ);
         return;
      case ARM64in_VDfromX:
         i->ARM64in.VDfromX.rD
            = lookupHRegRemap(m, i->ARM64in.VDfromX.rD);
         i->ARM64in.VDfromX.rX
            = lookupHRegRemap(m, i->ARM64in.VDfromX.rX);
         return;
      case ARM64in_VQfromXX:
         i->ARM64in.VQfromXX.rQ
            = lookupHRegRemap(m, i->ARM64in.VQfromXX.rQ);
         i->ARM64in.VQfromXX.rXhi
            = lookupHRegRemap(m, i->ARM64in.VQfromXX.rXhi);
         i->ARM64in.VQfromXX.rXlo
            = lookupHRegRemap(m, i->ARM64in.VQfromXX.rXlo);
         return;
      case ARM64in_VXfromQ:
         i->ARM64in.VXfromQ.rX
            = lookupHRegRemap(m, i->ARM64in.VXfromQ.rX);
         i->ARM64in.VXfromQ.rQ
            = lookupHRegRemap(m, i->ARM64in.VXfromQ.rQ);
         return;
      case ARM64in_VMov:
         i->ARM64in.VMov.dst = lookupHRegRemap(m, i->ARM64in.VMov.dst);
         i->ARM64in.VMov.src = lookupHRegRemap(m, i->ARM64in.VMov.src);
         return;

      case ARM64in_EvCheck:
         mapRegs_ARM64AMode(m, i->ARM64in.EvCheck.amCounter);
         mapRegs_ARM64AMode(m, i->ARM64in.EvCheck.amFailAddr);
         return;
      default:
         ppARM64Instr(i);
         vpanic("mapRegs_ARM64Instr");
   }
}

Bool isMove_ARM64Instr ( ARM64Instr* i, HReg* src, HReg* dst )
{
   switch (i->tag) {
      case ARM64in_MovI:
         *src = i->ARM64in.MovI.src;
         *dst = i->ARM64in.MovI.dst;
         return True;
      case ARM64in_VMov:
         *src = i->ARM64in.VMov.src;
         *dst = i->ARM64in.VMov.dst;
         return True;
      default:
         break;
   }

   return False;
}



void genSpill_ARM64 ( HInstr** i1, HInstr** i2,
                      HReg rreg, Int offsetB, Bool mode64 )
{
   HRegClass rclass;
   vassert(offsetB >= 0);
   vassert(!hregIsVirtual(rreg));
   vassert(mode64 == True);
   *i1 = *i2 = NULL;
   rclass = hregClass(rreg);
   switch (rclass) {
      case HRcInt64:
         vassert(0 == (offsetB & 7));
         offsetB >>= 3;
         vassert(offsetB < 4096);
         *i1 = ARM64Instr_LdSt64(
                  False, 
                  rreg, 
                  ARM64AMode_RI12(hregARM64_X21(), offsetB, 8)
               );
         return;
      case HRcFlt64:
         vassert(0 == (offsetB & 7));
         vassert(offsetB >= 0 && offsetB < 32768);
         *i1 = ARM64Instr_VLdStD(False,
                                 rreg, hregARM64_X21(), offsetB);
         return;
      case HRcVec128: {
         HReg x21  = hregARM64_X21();  
         HReg x9   = hregARM64_X9();   
         vassert(0 == (offsetB & 15)); 
         vassert(offsetB < 4096);
         *i1 = ARM64Instr_Arith(x9, x21, ARM64RIA_I12(offsetB, 0), True);
         *i2 = ARM64Instr_VLdStQ(False, rreg, x9);
         return;
      }
      default:
         ppHRegClass(rclass);
         vpanic("genSpill_ARM: unimplemented regclass");
   }
}

void genReload_ARM64 ( HInstr** i1, HInstr** i2,
                       HReg rreg, Int offsetB, Bool mode64 )
{
   HRegClass rclass;
   vassert(offsetB >= 0);
   vassert(!hregIsVirtual(rreg));
   vassert(mode64 == True);
   *i1 = *i2 = NULL;
   rclass = hregClass(rreg);
   switch (rclass) {
      case HRcInt64:
         vassert(0 == (offsetB & 7));
         offsetB >>= 3;
         vassert(offsetB < 4096);
         *i1 = ARM64Instr_LdSt64(
                  True, 
                  rreg, 
                  ARM64AMode_RI12(hregARM64_X21(), offsetB, 8)
               );
         return;
      case HRcFlt64:
         vassert(0 == (offsetB & 7));
         vassert(offsetB >= 0 && offsetB < 32768);
         *i1 = ARM64Instr_VLdStD(True,
                                 rreg, hregARM64_X21(), offsetB);
         return;
      case HRcVec128: {
         HReg x21  = hregARM64_X21();  
         HReg x9   = hregARM64_X9();   
         vassert(0 == (offsetB & 15)); 
         vassert(offsetB < 4096);
         *i1 = ARM64Instr_Arith(x9, x21, ARM64RIA_I12(offsetB, 0), True);
         *i2 = ARM64Instr_VLdStQ(True, rreg, x9);
         return;
      }
      default:
         ppHRegClass(rclass);
         vpanic("genReload_ARM: unimplemented regclass");
   }
}



static inline UChar iregNo ( HReg r )
{
   UInt n;
   vassert(hregClass(r) == HRcInt64);
   vassert(!hregIsVirtual(r));
   n = hregNumber(r);
   vassert(n <= 30);
   return toUChar(n);
}

static inline UChar dregNo ( HReg r )
{
   UInt n;
   vassert(hregClass(r) == HRcFlt64 || hregClass(r) == HRcInt64);
   vassert(!hregIsVirtual(r));
   n = hregNumber(r);
   vassert(n <= 31);
   return toUChar(n);
}

static inline UChar qregNo ( HReg r )
{
   UInt n;
   vassert(hregClass(r) == HRcVec128);
   vassert(!hregIsVirtual(r));
   n = hregNumber(r);
   vassert(n <= 31);
   return toUChar(n);
}

#define BITS4(zzb3,zzb2,zzb1,zzb0) \
   (((zzb3) << 3) | ((zzb2) << 2) | ((zzb1) << 1) | (zzb0))

#define X00  BITS4(0,0, 0,0)
#define X01  BITS4(0,0, 0,1)
#define X10  BITS4(0,0, 1,0)
#define X11  BITS4(0,0, 1,1)

#define X000 BITS4(0, 0,0,0)
#define X001 BITS4(0, 0,0,1)
#define X010 BITS4(0, 0,1,0)
#define X011 BITS4(0, 0,1,1)
#define X100 BITS4(0, 1,0,0)
#define X101 BITS4(0, 1,0,1)
#define X110 BITS4(0, 1,1,0)
#define X111 BITS4(0, 1,1,1)

#define X0000 BITS4(0,0,0,0)
#define X0001 BITS4(0,0,0,1)
#define X0010 BITS4(0,0,1,0)
#define X0011 BITS4(0,0,1,1)

#define BITS8(zzb7,zzb6,zzb5,zzb4,zzb3,zzb2,zzb1,zzb0) \
  ((BITS4(zzb7,zzb6,zzb5,zzb4) << 4) | BITS4(zzb3,zzb2,zzb1,zzb0))

#define X00000   BITS8(0,0,0, 0,0,0,0,0)
#define X00001   BITS8(0,0,0, 0,0,0,0,1)
#define X00111   BITS8(0,0,0, 0,0,1,1,1)
#define X01000   BITS8(0,0,0, 0,1,0,0,0)
#define X10000   BITS8(0,0,0, 1,0,0,0,0)
#define X11000   BITS8(0,0,0, 1,1,0,0,0)
#define X11110   BITS8(0,0,0, 1,1,1,1,0)
#define X11111   BITS8(0,0,0, 1,1,1,1,1)

#define X000000  BITS8(0,0, 0,0,0,0,0,0)
#define X000001  BITS8(0,0, 0,0,0,0,0,1)
#define X000100  BITS8(0,0, 0,0,0,1,0,0)
#define X000111  BITS8(0,0, 0,0,0,1,1,1)
#define X001000  BITS8(0,0, 0,0,1,0,0,0)
#define X001001  BITS8(0,0, 0,0,1,0,0,1)
#define X001010  BITS8(0,0, 0,0,1,0,1,0)
#define X001101  BITS8(0,0, 0,0,1,1,0,1)
#define X001110  BITS8(0,0, 0,0,1,1,1,0)
#define X001111  BITS8(0,0, 0,0,1,1,1,1)
#define X010000  BITS8(0,0, 0,1,0,0,0,0)
#define X010001  BITS8(0,0, 0,1,0,0,0,1)
#define X010101  BITS8(0,0, 0,1,0,1,0,1)
#define X010110  BITS8(0,0, 0,1,0,1,1,0)
#define X011001  BITS8(0,0, 0,1,1,0,0,1)
#define X011010  BITS8(0,0, 0,1,1,0,1,0)
#define X011011  BITS8(0,0, 0,1,1,0,1,1)
#define X011110  BITS8(0,0, 0,1,1,1,1,0)
#define X011111  BITS8(0,0, 0,1,1,1,1,1)
#define X100000  BITS8(0,0, 1,0,0,0,0,0)
#define X100001  BITS8(0,0, 1,0,0,0,0,1)
#define X100011  BITS8(0,0, 1,0,0,0,1,1)
#define X100100  BITS8(0,0, 1,0,0,1,0,0)
#define X100101  BITS8(0,0, 1,0,0,1,0,1)
#define X100110  BITS8(0,0, 1,0,0,1,1,0)
#define X100111  BITS8(0,0, 1,0,0,1,1,1)
#define X101000  BITS8(0,0, 1,0,1,0,0,0)
#define X110000  BITS8(0,0, 1,1,0,0,0,0)
#define X110001  BITS8(0,0, 1,1,0,0,0,1)
#define X110101  BITS8(0,0, 1,1,0,1,0,1)
#define X110111  BITS8(0,0, 1,1,0,1,1,1)
#define X111000  BITS8(0,0, 1,1,1,0,0,0)
#define X111001  BITS8(0,0, 1,1,1,0,0,1)
#define X111101  BITS8(0,0, 1,1,1,1,0,1)
#define X111110  BITS8(0,0, 1,1,1,1,1,0)
#define X111111  BITS8(0,0, 1,1,1,1,1,1)

#define X0001000  BITS8(0, 0,0,0,1,0,0,0)
#define X0010000  BITS8(0, 0,0,1,0,0,0,0)
#define X0100000  BITS8(0, 0,1,0,0,0,0,0)
#define X1000000  BITS8(0, 1,0,0,0,0,0,0)

#define X00100000  BITS8(0,0,1,0,0,0,0,0)
#define X00100001  BITS8(0,0,1,0,0,0,0,1)
#define X00100010  BITS8(0,0,1,0,0,0,1,0)
#define X00100011  BITS8(0,0,1,0,0,0,1,1)
#define X01010000  BITS8(0,1,0,1,0,0,0,0)
#define X01010001  BITS8(0,1,0,1,0,0,0,1)
#define X01010100  BITS8(0,1,0,1,0,1,0,0)
#define X01011000  BITS8(0,1,0,1,1,0,0,0)
#define X01100000  BITS8(0,1,1,0,0,0,0,0)
#define X01100001  BITS8(0,1,1,0,0,0,0,1)
#define X01100010  BITS8(0,1,1,0,0,0,1,0)
#define X01100011  BITS8(0,1,1,0,0,0,1,1)
#define X01110000  BITS8(0,1,1,1,0,0,0,0)
#define X01110001  BITS8(0,1,1,1,0,0,0,1)
#define X01110011  BITS8(0,1,1,1,0,0,1,1)
#define X01110101  BITS8(0,1,1,1,0,1,0,1)
#define X01110111  BITS8(0,1,1,1,0,1,1,1)
#define X11000001  BITS8(1,1,0,0,0,0,0,1)
#define X11000011  BITS8(1,1,0,0,0,0,1,1)
#define X11010100  BITS8(1,1,0,1,0,1,0,0)
#define X11010110  BITS8(1,1,0,1,0,1,1,0)
#define X11011000  BITS8(1,1,0,1,1,0,0,0)
#define X11011010  BITS8(1,1,0,1,1,0,1,0)
#define X11011110  BITS8(1,1,0,1,1,1,1,0)
#define X11110001  BITS8(1,1,1,1,0,0,0,1)
#define X11110011  BITS8(1,1,1,1,0,0,1,1)

#define BITS9(zzb8,zzb7,zzb6,zzb5,zzb4,zzb3,zzb2,zzb1,zzb0) \
  ((BITS8(zzb8,zzb7,zzb6,zzb5,zzb4,zzb3,zzb2,zzb1) << 1) | zzb0)

#define X111100111 BITS9(1,1,1,1,0,0,1,1,1)
#define X111100101 BITS9(1,1,1,1,0,0,1,0,1)



static inline UInt X_8_19_1_4 ( UInt f1, UInt f2, UInt f3, UInt f4 ) {
   vassert(8+19+1+4 == 32);
   vassert(f1 < (1<<8));
   vassert(f2 < (1<<19));
   vassert(f3 < (1<<1));
   vassert(f4 < (1<<4));
   UInt w = 0;
   w = (w <<  8) | f1;
   w = (w << 19) | f2;
   w = (w <<  1) | f3;
   w = (w <<  4) | f4;
   return w;
}


static inline UInt X_3_6_2_16_5 ( UInt f1, UInt f2,
                                  UInt f3, UInt f4, UInt f5 ) {
   vassert(3+6+2+16+5 == 32);
   vassert(f1 < (1<<3));
   vassert(f2 < (1<<6));
   vassert(f3 < (1<<2));
   vassert(f4 < (1<<16));
   vassert(f5 < (1<<5));
   UInt w = 0;
   w = (w <<  3) | f1;
   w = (w <<  6) | f2;
   w = (w <<  2) | f3;
   w = (w << 16) | f4;
   w = (w <<  5) | f5;
   return w;
}


static inline UInt X_2_6_2_12_5_5 ( UInt f1, UInt f2, UInt f3,
                                    UInt f4, UInt f5, UInt f6 ) {
   vassert(2+6+2+12+5+5 == 32);
   vassert(f1 < (1<<2));
   vassert(f2 < (1<<6));
   vassert(f3 < (1<<2));
   vassert(f4 < (1<<12));
   vassert(f5 < (1<<5));
   vassert(f6 < (1<<5));
   UInt w = 0;
   w = (w <<  2) | f1;
   w = (w <<  6) | f2;
   w = (w <<  2) | f3;
   w = (w << 12) | f4;
   w = (w <<  5) | f5;
   w = (w <<  5) | f6;
   return w;
}

static inline UInt X_3_8_5_6_5_5 ( UInt f1, UInt f2, UInt f3,
                                   UInt f4, UInt f5, UInt f6 ) {
   vassert(3+8+5+6+5+5 == 32);
   vassert(f1 < (1<<3));
   vassert(f2 < (1<<8));
   vassert(f3 < (1<<5));
   vassert(f4 < (1<<6));
   vassert(f5 < (1<<5));
   vassert(f6 < (1<<5));
   UInt w = 0;
   w = (w <<  3) | f1;
   w = (w <<  8) | f2;
   w = (w <<  5) | f3;
   w = (w <<  6) | f4;
   w = (w <<  5) | f5;
   w = (w <<  5) | f6;
   return w;
}

static inline UInt X_3_5_8_6_5_5 ( UInt f1, UInt f2, UInt f3,
                                   UInt f4, UInt f5, UInt f6 ) {
   vassert(3+8+5+6+5+5 == 32);
   vassert(f1 < (1<<3));
   vassert(f2 < (1<<5));
   vassert(f3 < (1<<8));
   vassert(f4 < (1<<6));
   vassert(f5 < (1<<5));
   vassert(f6 < (1<<5));
   UInt w = 0;
   w = (w <<  3) | f1;
   w = (w <<  5) | f2;
   w = (w <<  8) | f3;
   w = (w <<  6) | f4;
   w = (w <<  5) | f5;
   w = (w <<  5) | f6;
   return w;
}

static inline UInt X_3_6_7_6_5_5 ( UInt f1, UInt f2, UInt f3,
                                   UInt f4, UInt f5, UInt f6 ) {
   vassert(3+6+7+6+5+5 == 32);
   vassert(f1 < (1<<3));
   vassert(f2 < (1<<6));
   vassert(f3 < (1<<7));
   vassert(f4 < (1<<6));
   vassert(f5 < (1<<5));
   vassert(f6 < (1<<5));
   UInt w = 0;
   w = (w <<  3) | f1;
   w = (w <<  6) | f2;
   w = (w <<  7) | f3;
   w = (w <<  6) | f4;
   w = (w <<  5) | f5;
   w = (w <<  5) | f6;
   return w;
}


static inline UInt X_2_6_3_9_2_5_5 ( UInt f1, UInt f2, UInt f3,
                                     UInt f4, UInt f5, UInt f6, UInt f7 ) {
   vassert(2+6+3+9+2+5+5 == 32);
   vassert(f1 < (1<<2));
   vassert(f2 < (1<<6));
   vassert(f3 < (1<<3));
   vassert(f4 < (1<<9));
   vassert(f5 < (1<<2));
   vassert(f6 < (1<<5));
   vassert(f7 < (1<<5));
   UInt w = 0;
   w = (w << 2) | f1;
   w = (w << 6) | f2;
   w = (w << 3) | f3;
   w = (w << 9) | f4;
   w = (w << 2) | f5;
   w = (w << 5) | f6;
   w = (w << 5) | f7;
   return w;
}

static inline UInt X_3_6_1_6_6_5_5 ( UInt f1, UInt f2, UInt f3,
                                     UInt f4, UInt f5, UInt f6, UInt f7 ) {
   vassert(3+6+1+6+6+5+5 == 32);
   vassert(f1 < (1<<3));
   vassert(f2 < (1<<6));
   vassert(f3 < (1<<1));
   vassert(f4 < (1<<6));
   vassert(f5 < (1<<6));
   vassert(f6 < (1<<5));
   vassert(f7 < (1<<5));
   UInt w = 0;
   w = (w << 3) | f1;
   w = (w << 6) | f2;
   w = (w << 1) | f3;
   w = (w << 6) | f4;
   w = (w << 6) | f5;
   w = (w << 5) | f6;
   w = (w << 5) | f7;
   return w;
}

static inline UInt X_9_1_6_4_6_1_1_4( UInt f1, UInt f2, UInt f3, UInt f4,
                                        UInt f5, UInt f6, UInt f7, UInt f8) {
   vassert(9+1+6+4+6+1+1+4 == 32);
   vassert(f1 < (1<<9));
   vassert(f2 < (1<<1));
   vassert(f3 < (1<<6));
   vassert(f4 < (1<<4));
   vassert(f5 < (1<<6));
   vassert(f6 < (1<<1));
   vassert(f7 < (1<<1));
   vassert(f8 < (1<<9));
   UInt w = 0;
   w = (w << 9) | f1;
   w = (w << 1) | f2;
   w = (w << 6) | f3;
   w = (w << 4) | f4;
   w = (w << 6) | f5;
   w = (w << 1) | f6;
   w = (w << 1) | f7;
   w = (w << 4) | f8;
   return w;
}




static UInt* imm64_to_iregNo ( UInt* p, Int xD, ULong imm64 )
{
   if (imm64 == 0) {
      
      
      
      *p++ = X_3_6_2_16_5(X110, X100101, X00, 0, xD);
      return p;
   }

   
   
   
   UShort h[4];
   h[3] = (UShort)((imm64 >> 48) & 0xFFFF);
   h[2] = (UShort)((imm64 >> 32) & 0xFFFF);
   h[1] = (UShort)((imm64 >> 16) & 0xFFFF);
   h[0] = (UShort)((imm64 >>  0) & 0xFFFF);

   UInt i;
   for (i = 0; i < 4; i++) {
      if (h[i] != 0)
         break;
   }
   vassert(i < 4);

   
   *p++ = X_3_6_2_16_5(X110, X100101, i, h[i], xD);

   
   
   i++;
   for (; i < 4; i++) {
      if (h[i] == 0)
         continue;
      
      *p++ = X_3_6_2_16_5(X111, X100101, i, h[i], xD);
   }

   return p;
}

static UInt* imm64_to_iregNo_EXACTLY4 ( UInt* p, Int xD, ULong imm64 )
{
   UShort h[4];
   h[3] = (UShort)((imm64 >> 48) & 0xFFFF);
   h[2] = (UShort)((imm64 >> 32) & 0xFFFF);
   h[1] = (UShort)((imm64 >> 16) & 0xFFFF);
   h[0] = (UShort)((imm64 >>  0) & 0xFFFF);
   
   
   UInt i;
   for (i = 0; i < 4; i++) {
      if (i == 0) {
         
         *p++ = X_3_6_2_16_5(X110, X100101, i, h[i], xD);
      } else {
         
         *p++ = X_3_6_2_16_5(X111, X100101, i, h[i], xD);
      }
   }
   return p;
}

static Bool is_imm64_to_iregNo_EXACTLY4 ( UInt* p, Int xD, ULong imm64 )
{
   UShort h[4];
   h[3] = (UShort)((imm64 >> 48) & 0xFFFF);
   h[2] = (UShort)((imm64 >> 32) & 0xFFFF);
   h[1] = (UShort)((imm64 >> 16) & 0xFFFF);
   h[0] = (UShort)((imm64 >>  0) & 0xFFFF);
   
   
   UInt i;
   for (i = 0; i < 4; i++) {
      UInt expected;
      if (i == 0) {
         
         expected = X_3_6_2_16_5(X110, X100101, i, h[i], xD);
      } else {
         
         expected = X_3_6_2_16_5(X111, X100101, i, h[i], xD);
      }
      if (p[i] != expected)
         return False;
   }
   return True;
}


static UInt* do_load_or_store8 ( UInt* p,
                                 Bool isLoad, UInt wD, ARM64AMode* am )
{
   vassert(wD <= 30);
   if (am->tag == ARM64am_RI9) {
      Int simm9 = am->ARM64am.RI9.simm9;
      vassert(-256 <= simm9 && simm9 <= 255);
      UInt instr = X_2_6_3_9_2_5_5(X00, X111000, isLoad ? X010 : X000,
                                   simm9 & 0x1FF, X00,
                                   iregNo(am->ARM64am.RI9.reg), wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RI12) {
      UInt uimm12 = am->ARM64am.RI12.uimm12;
      UInt scale  = am->ARM64am.RI12.szB;
      vassert(scale == 1); 
      UInt xN    = iregNo(am->ARM64am.RI12.reg);
      vassert(xN <= 30);
      UInt instr = X_2_6_2_12_5_5(X00, X111001, isLoad ? X01 : X00,
                                  uimm12, xN, wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RR) {
      UInt xN = iregNo(am->ARM64am.RR.base);
      UInt xM = iregNo(am->ARM64am.RR.index);
      vassert(xN <= 30);
      UInt instr = X_3_8_5_6_5_5(X001, isLoad ? X11000011 : X11000001, 
                                 xM, X011010, xN, wD);
      *p++ = instr;
      return p;
   }
   vpanic("do_load_or_store8");
   vassert(0);
}


static UInt* do_load_or_store16 ( UInt* p,
                                  Bool isLoad, UInt wD, ARM64AMode* am )
{
   vassert(wD <= 30);
   if (am->tag == ARM64am_RI9) {
      Int simm9 = am->ARM64am.RI9.simm9;
      vassert(-256 <= simm9 && simm9 <= 255);
      UInt instr = X_2_6_3_9_2_5_5(X01, X111000, isLoad ? X010 : X000,
                                   simm9 & 0x1FF, X00,
                                   iregNo(am->ARM64am.RI9.reg), wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RI12) {
      UInt uimm12 = am->ARM64am.RI12.uimm12;
      UInt scale  = am->ARM64am.RI12.szB;
      vassert(scale == 2); 
      UInt xN    = iregNo(am->ARM64am.RI12.reg);
      vassert(xN <= 30);
      UInt instr = X_2_6_2_12_5_5(X01, X111001, isLoad ? X01 : X00,
                                  uimm12, xN, wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RR) {
      UInt xN = iregNo(am->ARM64am.RR.base);
      UInt xM = iregNo(am->ARM64am.RR.index);
      vassert(xN <= 30);
      UInt instr = X_3_8_5_6_5_5(X011, isLoad ? X11000011 : X11000001, 
                                 xM, X011010, xN, wD);
      *p++ = instr;
      return p;
   }
   vpanic("do_load_or_store16");
   vassert(0);
}


static UInt* do_load_or_store32 ( UInt* p,
                                  Bool isLoad, UInt wD, ARM64AMode* am )
{
   vassert(wD <= 30);
   if (am->tag == ARM64am_RI9) {
      Int simm9 = am->ARM64am.RI9.simm9;
      vassert(-256 <= simm9 && simm9 <= 255);
      UInt instr = X_2_6_3_9_2_5_5(X10, X111000, isLoad ? X010 : X000,
                                   simm9 & 0x1FF, X00,
                                   iregNo(am->ARM64am.RI9.reg), wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RI12) {
      UInt uimm12 = am->ARM64am.RI12.uimm12;
      UInt scale  = am->ARM64am.RI12.szB;
      vassert(scale == 4); 
      UInt xN    = iregNo(am->ARM64am.RI12.reg);
      vassert(xN <= 30);
      UInt instr = X_2_6_2_12_5_5(X10, X111001, isLoad ? X01 : X00,
                                  uimm12, xN, wD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RR) {
      UInt xN = iregNo(am->ARM64am.RR.base);
      UInt xM = iregNo(am->ARM64am.RR.index);
      vassert(xN <= 30);
      UInt instr = X_3_8_5_6_5_5(X101, isLoad ? X11000011 : X11000001, 
                                 xM, X011010, xN, wD);
      *p++ = instr;
      return p;
   }
   vpanic("do_load_or_store32");
   vassert(0);
}


static UInt* do_load_or_store64 ( UInt* p,
                                  Bool isLoad, UInt xD, ARM64AMode* am )
{
   
   vassert(xD <= 30);
   if (am->tag == ARM64am_RI9) {
      Int simm9 = am->ARM64am.RI9.simm9;
      vassert(-256 <= simm9 && simm9 <= 255);
      UInt xN = iregNo(am->ARM64am.RI9.reg);
      vassert(xN <= 30);
      UInt instr = X_2_6_3_9_2_5_5(X11, X111000, isLoad ? X010 : X000,
                                   simm9 & 0x1FF, X00, xN, xD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RI12) {
      UInt uimm12 = am->ARM64am.RI12.uimm12;
      UInt scale  = am->ARM64am.RI12.szB;
      vassert(scale == 8); 
      UInt xN    = iregNo(am->ARM64am.RI12.reg);
      vassert(xN <= 30);
      UInt instr = X_2_6_2_12_5_5(X11, X111001, isLoad ? X01 : X00,
                                  uimm12, xN, xD);
      *p++ = instr;
      return p;
   }
   if (am->tag == ARM64am_RR) {
      UInt xN = iregNo(am->ARM64am.RR.base);
      UInt xM = iregNo(am->ARM64am.RR.index);
      vassert(xN <= 30);
      UInt instr = X_3_8_5_6_5_5(X111, isLoad ? X11000011 : X11000001, 
                                 xM, X011010, xN, xD);
      *p++ = instr;
      return p;
   }
   vpanic("do_load_or_store64");
   vassert(0);
}



Int emit_ARM64Instr ( Bool* is_profInc,
                      UChar* buf, Int nbuf, ARM64Instr* i,
                      Bool mode64,
                      void* disp_cp_chain_me_to_slowEP,
                      void* disp_cp_chain_me_to_fastEP,
                      void* disp_cp_xindir,
                      void* disp_cp_xassisted )
{
   UInt* p = (UInt*)buf;
   vassert(nbuf >= 32);
   vassert(mode64 == True);
   vassert(0 == (((HWord)buf) & 3));

   switch (i->tag) {
      case ARM64in_Arith: {
         UInt      rD   = iregNo(i->ARM64in.Arith.dst);
         UInt      rN   = iregNo(i->ARM64in.Arith.argL);
         ARM64RIA* argR = i->ARM64in.Arith.argR;
         switch (argR->tag) {
            case ARM64riA_I12:
               *p++ = X_2_6_2_12_5_5(
                         i->ARM64in.Arith.isAdd ? X10 : X11,
                         X010001,
                         argR->ARM64riA.I12.shift == 12 ? X01 : X00,
                         argR->ARM64riA.I12.imm12, rN, rD
                      );
               break;
            case ARM64riA_R: {
               UInt rM = iregNo(i->ARM64in.Arith.argR->ARM64riA.R.reg);
               *p++ = X_3_8_5_6_5_5(
                         i->ARM64in.Arith.isAdd ? X100 : X110,
                         X01011000, rM, X000000, rN, rD
                      );
               break;
            }
            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_Cmp: {
         UInt      rD   = 31; 
         UInt      rN   = iregNo(i->ARM64in.Cmp.argL);
         ARM64RIA* argR = i->ARM64in.Cmp.argR;
         Bool      is64 = i->ARM64in.Cmp.is64;
         switch (argR->tag) {
            case ARM64riA_I12:
               
               
               *p++ = X_2_6_2_12_5_5(
                         is64 ? X11 : X01, X110001,
                         argR->ARM64riA.I12.shift == 12 ? X01 : X00,
                         argR->ARM64riA.I12.imm12, rN, rD);
               break;
            case ARM64riA_R: {
               
               
               UInt rM = iregNo(i->ARM64in.Cmp.argR->ARM64riA.R.reg);
               *p++ = X_3_8_5_6_5_5(is64 ? X111 : X011,
                                    X01011000, rM, X000000, rN, rD);
               break;
            }
            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_Logic: {
         UInt      rD   = iregNo(i->ARM64in.Logic.dst);
         UInt      rN   = iregNo(i->ARM64in.Logic.argL);
         ARM64RIL* argR = i->ARM64in.Logic.argR;
         UInt      opc  = 0; 
         vassert(rD < 31);
         vassert(rN < 31);
         switch (i->ARM64in.Logic.op) {
            case ARM64lo_OR:  opc = X101; break;
            case ARM64lo_AND: opc = X100; break;
            case ARM64lo_XOR: opc = X110; break;
            default: break;
         }
         vassert(opc != 0);
         switch (argR->tag) {
            case ARM64riL_I13: {
               
               
               
               *p++ = X_3_6_1_6_6_5_5(
                         opc, X100100, argR->ARM64riL.I13.bitN,
                         argR->ARM64riL.I13.immR, argR->ARM64riL.I13.immS,
                         rN, rD
                      );
               break;
            }
            case ARM64riL_R: {
               
               
               
               UInt rM = iregNo(argR->ARM64riL.R.reg);
               vassert(rM < 31);
               *p++ = X_3_8_5_6_5_5(opc, X01010000, rM, X000000, rN, rD);
               break;
            }
            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_Test: {
         UInt      rD   = 31; 
         UInt      rN   = iregNo(i->ARM64in.Test.argL);
         ARM64RIL* argR = i->ARM64in.Test.argR;
         switch (argR->tag) {
            case ARM64riL_I13: {
               
               *p++ = X_3_6_1_6_6_5_5(
                         X111, X100100, argR->ARM64riL.I13.bitN,
                         argR->ARM64riL.I13.immR, argR->ARM64riL.I13.immS,
                         rN, rD
                      );
               break;
            }
            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_Shift: {
         UInt      rD   = iregNo(i->ARM64in.Shift.dst);
         UInt      rN   = iregNo(i->ARM64in.Shift.argL);
         ARM64RI6* argR = i->ARM64in.Shift.argR;
         vassert(rD < 31);
         vassert(rN < 31);
         switch (argR->tag) {
            case ARM64ri6_I6: {
               
               
               
               UInt sh = argR->ARM64ri6.I6.imm6;
               vassert(sh > 0 && sh < 64);
               switch (i->ARM64in.Shift.op) {
                  case ARM64sh_SHL:
                     *p++ = X_3_6_1_6_6_5_5(X110, X100110,
                                            1, 64-sh, 63-sh, rN, rD);
                     break;
                  case ARM64sh_SHR:
                     *p++ = X_3_6_1_6_6_5_5(X110, X100110, 1, sh, 63, rN, rD);
                     break;
                  case ARM64sh_SAR:
                     *p++ = X_3_6_1_6_6_5_5(X100, X100110, 1, sh, 63, rN, rD);
                     break;
                  default:
                     vassert(0);
               }
               break;
            }
            case ARM64ri6_R: {
               
               
               
               UInt rM = iregNo(argR->ARM64ri6.R.reg);
               vassert(rM < 31);
               UInt subOpc = 0;
               switch (i->ARM64in.Shift.op) {
                  case ARM64sh_SHL: subOpc = X001000; break;
                  case ARM64sh_SHR: subOpc = X001001; break;
                  case ARM64sh_SAR: subOpc = X001010; break;
                  default: vassert(0);
               }
               *p++ = X_3_8_5_6_5_5(X100, X11010110, rM, subOpc, rN, rD);
               break;
            }
            default:
               vassert(0);
         }
         goto done;
      }
      case ARM64in_Unary: {
         UInt rDst = iregNo(i->ARM64in.Unary.dst);
         UInt rSrc = iregNo(i->ARM64in.Unary.src);
         switch (i->ARM64in.Unary.op) {
            case ARM64un_CLZ:
               
               
               *p++ = X_3_8_5_6_5_5(X110,
                                    X11010110, X00000, X000100, rSrc, rDst);
               goto done;
            case ARM64un_NEG:
               
               
               *p++ = X_3_8_5_6_5_5(X110,
                                    X01011000, rSrc, X000000, X11111, rDst);
               goto done;
            case ARM64un_NOT: {
               
               *p++ = X_3_8_5_6_5_5(X101,
                                    X01010001, rSrc, X000000, X11111, rDst);
               goto done;
            }
            default:
               break;
         }
         goto bad;
      }
      case ARM64in_MovI: {
         UInt instr = 0xAA0003E0;
         UInt d     = iregNo(i->ARM64in.MovI.dst);
         UInt m     = iregNo(i->ARM64in.MovI.src);
         *p++ = instr | ((m & 31) << 16) | ((d & 31) << 0);
         goto done;
      }
      case ARM64in_Imm64: {
         p = imm64_to_iregNo( p, iregNo(i->ARM64in.Imm64.dst),
                              i->ARM64in.Imm64.imm64 );
         goto done;
      }
      case ARM64in_LdSt64: {
         p = do_load_or_store64( p, i->ARM64in.LdSt64.isLoad,
                                 iregNo(i->ARM64in.LdSt64.rD),
                                 i->ARM64in.LdSt64.amode );
         goto done;
      }
      case ARM64in_LdSt32: {
         p = do_load_or_store32( p, i->ARM64in.LdSt32.isLoad,
                                 iregNo(i->ARM64in.LdSt32.rD),
                                 i->ARM64in.LdSt32.amode );
         goto done;
      }
      case ARM64in_LdSt16: {
         p = do_load_or_store16( p, i->ARM64in.LdSt16.isLoad,
                                 iregNo(i->ARM64in.LdSt16.rD),
                                 i->ARM64in.LdSt16.amode );
         goto done;
      }
      case ARM64in_LdSt8: {
         p = do_load_or_store8( p, i->ARM64in.LdSt8.isLoad,
                                iregNo(i->ARM64in.LdSt8.rD),
                                i->ARM64in.LdSt8.amode );
         goto done;
      }

      case ARM64in_XDirect: {
         vassert(disp_cp_chain_me_to_slowEP != NULL);
         vassert(disp_cp_chain_me_to_fastEP != NULL);

         
         UInt* ptmp = NULL;

         if (i->ARM64in.XDirect.cond != ARM64cc_AL) {
            vassert(i->ARM64in.XDirect.cond != ARM64cc_NV);
            ptmp = p;
            *p++ = 0;
         }

         
         
         
         p = imm64_to_iregNo(p, 9, i->ARM64in.XDirect.dstGA);
         p = do_load_or_store64(p, False,
                                9, i->ARM64in.XDirect.amPC);

         
         
         
         
         
         
         void* disp_cp_chain_me
                  = i->ARM64in.XDirect.toFastEP ? disp_cp_chain_me_to_fastEP 
                                                : disp_cp_chain_me_to_slowEP;
         p = imm64_to_iregNo_EXACTLY4(p, 9,
                                      Ptr_to_ULong(disp_cp_chain_me));
         *p++ = 0xD63F0120;
         

         
         if (i->ARM64in.XDirect.cond != ARM64cc_AL) {
            Int delta = (UChar*)p - (UChar*)ptmp; 
            vassert(delta > 0 && delta < 40);
            vassert((delta & 3) == 0);
            UInt notCond = 1 ^ (UInt)i->ARM64in.XDirect.cond;
            vassert(notCond <= 13); 
            vassert(ptmp != NULL);
            delta = delta >> 2;
            *ptmp = X_8_19_1_4(X01010100, delta & ((1<<19)-1), 0, notCond);
         }
         goto done;
      }

      case ARM64in_XIndir: {
         
         
         
         
         

         if (i->ARM64in.XIndir.cond != ARM64cc_AL) {
            vassert(0); 
         }

         
         
         p = do_load_or_store64(p, False,
                                iregNo(i->ARM64in.XIndir.dstGA),
                                i->ARM64in.XIndir.amPC);

         
         
         p = imm64_to_iregNo(p, 9, Ptr_to_ULong(disp_cp_xindir));
         *p++ = 0xD61F0120; 

         
         if (i->ARM64in.XIndir.cond != ARM64cc_AL) {
            vassert(0); 
         }
         goto done;
      }

      case ARM64in_XAssisted: {
         
         UInt* ptmp = NULL;

         if (i->ARM64in.XAssisted.cond != ARM64cc_AL) {
            vassert(i->ARM64in.XDirect.cond != ARM64cc_NV);
            ptmp = p;
            *p++ = 0;
         }

         
         
         p = do_load_or_store64(p, False,
                                iregNo(i->ARM64in.XAssisted.dstGA),
                                i->ARM64in.XAssisted.amPC);

         
         UInt trcval = 0;
         switch (i->ARM64in.XAssisted.jk) {
            case Ijk_ClientReq:   trcval = VEX_TRC_JMP_CLIENTREQ;   break;
            case Ijk_Sys_syscall: trcval = VEX_TRC_JMP_SYS_SYSCALL; break;
            
            
            
            
            case Ijk_NoDecode:    trcval = VEX_TRC_JMP_NODECODE;    break;
            case Ijk_InvalICache: trcval = VEX_TRC_JMP_INVALICACHE; break;
            case Ijk_FlushDCache: trcval = VEX_TRC_JMP_FLUSHDCACHE; break;
            case Ijk_NoRedir:     trcval = VEX_TRC_JMP_NOREDIR;     break;
            
            
            case Ijk_Boring:      trcval = VEX_TRC_JMP_BORING;      break;
            
            
            
            
            default: 
               ppIRJumpKind(i->ARM64in.XAssisted.jk);
               vpanic("emit_ARM64Instr.ARM64in_XAssisted: "
                      "unexpected jump kind");
         }
         vassert(trcval != 0);
         p = imm64_to_iregNo(p, 21, (ULong)trcval);

         
         
         p = imm64_to_iregNo(p, 9, Ptr_to_ULong(disp_cp_xassisted));
         *p++ = 0xD61F0120; 

         
         if (i->ARM64in.XAssisted.cond != ARM64cc_AL) {
            Int delta = (UChar*)p - (UChar*)ptmp; 
            vassert(delta > 0 && delta < 40);
            vassert((delta & 3) == 0);
            UInt notCond = 1 ^ (UInt)i->ARM64in.XDirect.cond;
            vassert(notCond <= 13); 
            vassert(ptmp != NULL);
            delta = delta >> 2;
            *ptmp = X_8_19_1_4(X01010100, delta & ((1<<19)-1), 0, notCond);
         }
         goto done;
      }

      case ARM64in_CSel: {
         
         UInt dd   = iregNo(i->ARM64in.CSel.dst);
         UInt nn   = iregNo(i->ARM64in.CSel.argL);
         UInt mm   = iregNo(i->ARM64in.CSel.argR);
         UInt cond = (UInt)i->ARM64in.CSel.cond;
         vassert(dd < 31 && nn < 31 && mm < 31 && cond < 16);
         *p++ = X_3_8_5_6_5_5(X100, X11010100, mm, cond << 2, nn, dd);
         goto done;
      }

      case ARM64in_Call: {
         if (i->ARM64in.Call.cond != ARM64cc_AL
             && i->ARM64in.Call.rloc.pri != RLPri_None) {
            goto bad;
         }

         UInt* ptmp = NULL;
         if (i->ARM64in.Call.cond != ARM64cc_AL) {
            ptmp = p;
            *p++ = 0;
         }

         
         p = imm64_to_iregNo( (UInt*)p,
                              9, (ULong)i->ARM64in.Call.target );
         
         *p++ = 0xD63F0120;

         
         if (i->ARM64in.Call.cond != ARM64cc_AL) {
            ULong dist = (ULong)(p - ptmp);
            vassert(dist >= 2 && dist <= 5);
            vassert(ptmp != NULL);
            
            *ptmp = X_8_19_1_4(X01010100, dist, 0,
                               1 ^ (UInt)i->ARM64in.Call.cond);
         } else {
            vassert(ptmp == NULL);
         }

         goto done;
      }

      case ARM64in_AddToSP: {
         Int simm12 = i->ARM64in.AddToSP.simm;
         vassert(-4096 < simm12 && simm12 < 4096);
         vassert(0 == (simm12 & 0xF));
         if (simm12 >= 0) {
            *p++ = X_2_6_2_12_5_5(X10, X010001, X00, simm12, X11111, X11111);
         } else {
            *p++ = X_2_6_2_12_5_5(X11, X010001, X00, -simm12, X11111, X11111);
         }
         goto done;
      }

      case ARM64in_FromSP: {
         
         UInt dd = iregNo(i->ARM64in.FromSP.dst);
         vassert(dd < 31);
         *p++ = X_2_6_2_12_5_5(X10, X010001, X00, 0, X11111, dd);
         goto done;
      }

      case ARM64in_Mul: {
         UInt dd = iregNo(i->ARM64in.Mul.dst);
         UInt nn = iregNo(i->ARM64in.Mul.argL);
         UInt mm = iregNo(i->ARM64in.Mul.argR);
         vassert(dd < 31 && nn < 31 && mm < 31);
         switch (i->ARM64in.Mul.op) {
            case ARM64mul_ZX:
               *p++ = X_3_8_5_6_5_5(X100, X11011110, mm, X011111, nn, dd);
               goto done;
            case ARM64mul_SX:
               *p++ = X_3_8_5_6_5_5(X100, X11011010, mm, X011111, nn, dd);
               goto done;
            case ARM64mul_PLAIN:
               *p++ = X_3_8_5_6_5_5(X100, X11011000, mm, X011111, nn, dd);
               goto done;
            default:
               vassert(0);
         }
         goto bad;
      }
      case ARM64in_LdrEX: {
         switch (i->ARM64in.LdrEX.szB) {
            case 1: *p++ = 0x085F7C82; goto done;
            case 2: *p++ = 0x485F7C82; goto done;
            case 4: *p++ = 0x885F7C82; goto done;
            case 8: *p++ = 0xC85F7C82; goto done;
            default: break;
         }
         goto bad;
      }
      case ARM64in_StrEX: {
         switch (i->ARM64in.StrEX.szB) {
            case 1: *p++ = 0x08007C82; goto done;
            case 2: *p++ = 0x48007C82; goto done;
            case 4: *p++ = 0x88007C82; goto done;
            case 8: *p++ = 0xC8007C82; goto done;
            default: break;
         }
         goto bad;
      }
      case ARM64in_MFence: {
         *p++ = 0xD5033F9F; 
         *p++ = 0xD5033FBF; 
         *p++ = 0xD5033FDF; 
         goto done;
      }
      
      
      
      
      
      
      case ARM64in_VLdStS: {
         UInt sD     = dregNo(i->ARM64in.VLdStS.sD);
         UInt rN     = iregNo(i->ARM64in.VLdStS.rN);
         UInt uimm12 = i->ARM64in.VLdStS.uimm12;
         Bool isLD   = i->ARM64in.VLdStS.isLoad;
         vassert(uimm12 < 16384 && 0 == (uimm12 & 3));
         uimm12 >>= 2;
         vassert(uimm12 < (1<<12));
         vassert(sD < 32);
         vassert(rN < 31);
         *p++ = X_2_6_2_12_5_5(X10, X111101, isLD ? X01 : X00,
                               uimm12, rN, sD);
         goto done;
      }
      case ARM64in_VLdStD: {
         UInt dD     = dregNo(i->ARM64in.VLdStD.dD);
         UInt rN     = iregNo(i->ARM64in.VLdStD.rN);
         UInt uimm12 = i->ARM64in.VLdStD.uimm12;
         Bool isLD   = i->ARM64in.VLdStD.isLoad;
         vassert(uimm12 < 32768 && 0 == (uimm12 & 7));
         uimm12 >>= 3;
         vassert(uimm12 < (1<<12));
         vassert(dD < 32);
         vassert(rN < 31);
         *p++ = X_2_6_2_12_5_5(X11, X111101, isLD ? X01 : X00,
                               uimm12, rN, dD);
         goto done;
      }
      case ARM64in_VLdStQ: {
         UInt rQ = qregNo(i->ARM64in.VLdStQ.rQ);
         UInt rN = iregNo(i->ARM64in.VLdStQ.rN);
         vassert(rQ < 32);
         vassert(rN < 31);
         if (i->ARM64in.VLdStQ.isLoad) {
            *p++ = 0x4C407C00 | (rN << 5) | rQ;
         } else {
            *p++ = 0x4C007C00 | (rN << 5) | rQ;
         }
         goto done;
      }
      case ARM64in_VCvtI2F: {
         UInt       rN = iregNo(i->ARM64in.VCvtI2F.rS);
         UInt       rD = dregNo(i->ARM64in.VCvtI2F.rD);
         ARM64CvtOp how = i->ARM64in.VCvtI2F.how;
         
         switch (how) {
            case ARM64cvt_F32_I32S: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X00100010, X000000, rN, rD);
               break;
            case ARM64cvt_F64_I32S: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X01100010, X000000, rN, rD);
               break;
            case ARM64cvt_F32_I64S: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X00100010, X000000, rN, rD);
               break;
            case ARM64cvt_F64_I64S: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X01100010, X000000, rN, rD);
               break;
            case ARM64cvt_F32_I32U: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X00100011, X000000, rN, rD);
               break;
            case ARM64cvt_F64_I32U: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X01100011, X000000, rN, rD);
               break;
            case ARM64cvt_F32_I64U: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X00100011, X000000, rN, rD);
               break;
            case ARM64cvt_F64_I64U: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X01100011, X000000, rN, rD);
               break;
            default:
               goto bad; 
         }
         goto done;
      }
      case ARM64in_VCvtF2I: {
         UInt       rD    = iregNo(i->ARM64in.VCvtF2I.rD);
         UInt       rN    = dregNo(i->ARM64in.VCvtF2I.rS);
         ARM64CvtOp how   = i->ARM64in.VCvtF2I.how;
         UChar      armRM = i->ARM64in.VCvtF2I.armRM;
         
         switch (how) {
            case ARM64cvt_F64_I32S: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X01100000 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F64_I32U: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X01100001 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F64_I64S: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X01100000 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F64_I64U: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X01100001 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F32_I32S: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X00100000 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F32_I32U: 
               *p++ = X_3_5_8_6_5_5(X000, X11110, X00100001 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F32_I64S: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X00100000 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            case ARM64cvt_F32_I64U: 
               *p++ = X_3_5_8_6_5_5(X100, X11110, X00100001 | (armRM << 3),
                                    X000000, rN, rD);
               break;
            default:
               goto bad; 
         }
         goto done;
      }
      case ARM64in_VCvtSD: {
         UInt dd = dregNo(i->ARM64in.VCvtSD.dst);
         UInt nn = dregNo(i->ARM64in.VCvtSD.src);
         if (i->ARM64in.VCvtSD.sToD) {
            *p++ = X_3_5_8_6_5_5(X000, X11110, X00100010, X110000, nn, dd);
         } else {
            *p++ = X_3_5_8_6_5_5(X000, X11110, X01100010, X010000, nn, dd);
         }
         goto done;
      }
      case ARM64in_VUnaryD: {
         UInt dD  = dregNo(i->ARM64in.VUnaryD.dst);
         UInt dN  = dregNo(i->ARM64in.VUnaryD.src);
         UInt b16 = 2; 
         UInt b15 = 2; 
         switch (i->ARM64in.VUnaryD.op) {
            case ARM64fpu_NEG:  b16 = 1; b15 = 0; break;
            case ARM64fpu_SQRT: b16 = 1; b15 = 1; break;
            case ARM64fpu_ABS:  b16 = 0; b15 = 1; break;
            default: break;
         }
         if (b16 < 2 && b15 < 2) {
            *p++ = X_3_8_5_6_5_5(X000, X11110011, (X0000 << 1) | b16,
                                 (b15 << 5) | X10000, dN, dD);
            goto done;
         }
         if (i->ARM64in.VUnaryD.op == ARM64fpu_RINT) {
           *p++ = X_3_8_5_6_5_5(X000, X11110011, X00111, X110000, dN, dD);
           goto done;
         }
         goto bad;
      }
      case ARM64in_VUnaryS: {
         UInt sD  = dregNo(i->ARM64in.VUnaryS.dst);
         UInt sN  = dregNo(i->ARM64in.VUnaryS.src);
         UInt b16 = 2; 
         UInt b15 = 2; 
         switch (i->ARM64in.VUnaryS.op) {
            case ARM64fpu_NEG:  b16 = 1; b15 = 0; break;
            case ARM64fpu_SQRT: b16 = 1; b15 = 1; break;
            case ARM64fpu_ABS:  b16 = 0; b15 = 1; break;
            default: break;
         }
         if (b16 < 2 && b15 < 2) {
            *p++ = X_3_8_5_6_5_5(X000, X11110001, (X0000 << 1) | b16,
                                 (b15 << 5) | X10000, sN, sD);
            goto done;
         }
         if (i->ARM64in.VUnaryS.op == ARM64fpu_RINT) {
           *p++ = X_3_8_5_6_5_5(X000, X11110001, X00111, X110000, sN, sD);
           goto done;
         }
         goto bad;
      }
      case ARM64in_VBinD: {
         UInt dD = dregNo(i->ARM64in.VBinD.dst);
         UInt dN = dregNo(i->ARM64in.VBinD.argL);
         UInt dM = dregNo(i->ARM64in.VBinD.argR);
         UInt b1512 = 16; 
         switch (i->ARM64in.VBinD.op) {
            case ARM64fpb_DIV: b1512 = X0001; break;
            case ARM64fpb_MUL: b1512 = X0000; break;
            case ARM64fpb_SUB: b1512 = X0011; break;
            case ARM64fpb_ADD: b1512 = X0010; break;
            default: goto bad;
         }
         vassert(b1512 < 16);
         *p++
            = X_3_8_5_6_5_5(X000, X11110011, dM, (b1512 << 2) | X10, dN, dD);
         goto done;
      }
      case ARM64in_VBinS: {
         UInt sD = dregNo(i->ARM64in.VBinS.dst);
         UInt sN = dregNo(i->ARM64in.VBinS.argL);
         UInt sM = dregNo(i->ARM64in.VBinS.argR);
         UInt b1512 = 16; 
         switch (i->ARM64in.VBinS.op) {
            case ARM64fpb_DIV: b1512 = X0001; break;
            case ARM64fpb_MUL: b1512 = X0000; break;
            case ARM64fpb_SUB: b1512 = X0011; break;
            case ARM64fpb_ADD: b1512 = X0010; break;
            default: goto bad;
         }
         vassert(b1512 < 16);
         *p++
            = X_3_8_5_6_5_5(X000, X11110001, sM, (b1512 << 2) | X10, sN, sD);
         goto done;
      }
      case ARM64in_VCmpD: {
         
         UInt dN = dregNo(i->ARM64in.VCmpD.argL);
         UInt dM = dregNo(i->ARM64in.VCmpD.argR);
         *p++ = X_3_8_5_6_5_5(X000, X11110011, dM, X001000, dN, X00000);
         goto done;
      }
      case ARM64in_VCmpS: {
         
         UInt sN = dregNo(i->ARM64in.VCmpS.argL);
         UInt sM = dregNo(i->ARM64in.VCmpS.argR);
         *p++ = X_3_8_5_6_5_5(X000, X11110001, sM, X001000, sN, X00000);
         goto done;
      }
      case ARM64in_FPCR: {
         Bool toFPCR = i->ARM64in.FPCR.toFPCR;
         UInt iReg   = iregNo(i->ARM64in.FPCR.iReg);
         if (toFPCR) {
            
            *p++ = 0xD51B4400 | (iReg & 0x1F);
            goto done;
         }
         goto bad; 
      }
      case ARM64in_VBinV: {
         UInt vD = qregNo(i->ARM64in.VBinV.dst);
         ARM64VecBinOp op = i->ARM64in.VBinV.op;
         Bool isV128 = (op != ARM64vecb_UMULL8x8
                        && op != ARM64vecb_UMULL16x4
                        && op != ARM64vecb_UMULL32x2);
         UInt vN = isV128 ? qregNo(i->ARM64in.VBinV.argL)
                          : dregNo(i->ARM64in.VBinV.argL);
         UInt vM = isV128 ? qregNo(i->ARM64in.VBinV.argR)
                          : dregNo(i->ARM64in.VBinV.argR);
         switch (i->ARM64in.VBinV.op) {
            case ARM64vecb_ADD64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110111, vM, X100001, vN, vD);
               break;
            case ARM64vecb_ADD32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X100001, vN, vD);
               break;
            case ARM64vecb_ADD16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X100001, vN, vD);
               break;
            case ARM64vecb_ADD8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X100001, vN, vD);
               break;
            case ARM64vecb_SUB64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110111, vM, X100001, vN, vD);
               break;
            case ARM64vecb_SUB32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM, X100001, vN, vD);
               break;
            case ARM64vecb_SUB16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X100001, vN, vD);
               break;
            case ARM64vecb_SUB8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X100001, vN, vD);
               break;
            case ARM64vecb_MUL32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X100111, vN, vD);
               break;
            case ARM64vecb_MUL16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X100111, vN, vD);
               break;
            case ARM64vecb_MUL8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X100111, vN, vD);
               break;
            case ARM64vecb_FADD64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X110101, vN, vD);
               break;
            case ARM64vecb_FADD32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X110101, vN, vD);
               break;
            case ARM64vecb_FSUB64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110111, vM, X110101, vN, vD);
               break;
            case ARM64vecb_FSUB32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X110101, vN, vD);
               break;
            case ARM64vecb_FMUL64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X110111, vN, vD);
               break;
            case ARM64vecb_FMUL32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X110111, vN, vD);
               break;
            case ARM64vecb_FDIV64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X111111, vN, vD);
               break;
            case ARM64vecb_FDIV32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X111111, vN, vD);
               break;

            case ARM64vecb_UMAX32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM, X011001, vN, vD);
               break;
            case ARM64vecb_UMAX16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X011001, vN, vD);
               break;
            case ARM64vecb_UMAX8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X011001, vN, vD);
               break;

            case ARM64vecb_UMIN32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM, X011011, vN, vD);
               break;
            case ARM64vecb_UMIN16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X011011, vN, vD);
               break;
            case ARM64vecb_UMIN8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X011011, vN, vD);
               break;

            case ARM64vecb_UMULL32x2:
               *p++ = X_3_8_5_6_5_5(X001, X01110101, vM, X110000, vN, vD);
               break;
            case ARM64vecb_UMULL16x4:
               *p++ = X_3_8_5_6_5_5(X001, X01110011, vM, X110000, vN, vD);
               break;
            case ARM64vecb_UMULL8x8:
               *p++ = X_3_8_5_6_5_5(X001, X01110001, vM, X110000, vN, vD);
               break;

            case ARM64vecb_SMAX32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X011001, vN, vD);
               break;
            case ARM64vecb_SMAX16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X011001, vN, vD);
               break;
            case ARM64vecb_SMAX8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X011001, vN, vD);
               break;

            case ARM64vecb_SMIN32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X011011, vN, vD);
               break;
            case ARM64vecb_SMIN16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X011011, vN, vD);
               break;
            case ARM64vecb_SMIN8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X011011, vN, vD);
               break;

            case ARM64vecb_AND:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X000111, vN, vD);
               break;
            case ARM64vecb_ORR:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM, X000111, vN, vD);
               break;
            case ARM64vecb_XOR:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X000111, vN, vD);
               break;

            case ARM64vecb_CMEQ64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110111, vM, X100011, vN, vD);
               break;
            case ARM64vecb_CMEQ32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM, X100011, vN, vD);
               break;
            case ARM64vecb_CMEQ16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X100011, vN, vD);
               break;
            case ARM64vecb_CMEQ8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X100011, vN, vD);
               break;

            case ARM64vecb_CMHI64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110111, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMHI32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMHI16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMHI8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM,  X001101, vN, vD);
               break;

            case ARM64vecb_CMGT64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110111, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMGT32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMGT16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM,  X001101, vN, vD);
               break;
            case ARM64vecb_CMGT8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM,  X001101, vN, vD);
               break;

            case ARM64vecb_FCMEQ64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, vM, X111001, vN, vD);
               break;
            case ARM64vecb_FCMEQ32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, vM, X111001, vN, vD);
               break;

            case ARM64vecb_FCMGE64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, vM, X111001, vN, vD);
               break;
            case ARM64vecb_FCMGE32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, vM, X111001, vN, vD);
               break;

            case ARM64vecb_FCMGT64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110111, vM, X111001, vN, vD);
               break;
            case ARM64vecb_FCMGT32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, vM, X111001, vN, vD);
               break;

            case ARM64vecb_TBL1:
               *p++ = X_3_8_5_6_5_5(X010, X01110000, vM,  X000000, vN, vD);
               break;

            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_VUnaryV: {
         ARM64VecUnaryOp op = i->ARM64in.VUnaryV.op;
         UInt vD = qregNo(i->ARM64in.VUnaryV.dst);
         Bool isV128 = !(op >= ARM64vecu_VMOVL8U && op <= ARM64vecu_VMOVL32S);
         UInt vN = isV128 ? qregNo(i->ARM64in.VUnaryV.arg)
                          : dregNo(i->ARM64in.VUnaryV.arg);
         switch (i->ARM64in.VUnaryV.op) {
            case ARM64vecu_FABS64x2:
               *p++ = X_3_8_5_6_5_5(X010, X01110111, X00000, X111110, vN, vD);
               break;
            case ARM64vecu_FABS32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, X00000, X111110, vN, vD);
               break;
            case ARM64vecu_FNEG64x2:
               *p++ = X_3_8_5_6_5_5(X011, X01110111, X00000, X111110, vN, vD);
               break;
            case ARM64vecu_FNEG32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, X00000, X111110, vN, vD);
               break;
            case ARM64vecu_VMOVL8U:
               *p++ = X_9_1_6_4_6_1_1_4(X111100111, vD >> 4, X001000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_VMOVL16U:
               *p++ = X_9_1_6_4_6_1_1_4(X111100111, vD >> 4, X010000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_VMOVL32U:
               *p++ = X_9_1_6_4_6_1_1_4(X111100111, vD >> 4, X100000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_VMOVL8S:
               *p++ = X_9_1_6_4_6_1_1_4(X111100101, vD >> 4, X001000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_VMOVL16S:
               *p++ = X_9_1_6_4_6_1_1_4(X111100101, vD >> 4, X010000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_VMOVL32S:
               *p++ = X_9_1_6_4_6_1_1_4(X111100101, vD >> 4, X100000, vD & 0xFU, X101000, vN >> 4, 1, vN & 0xFU);
               break;
            case ARM64vecu_NOT:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, X00000, X010110, vN, vD);
               break;
            case ARM64vecu_CNT:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, X00000, X010110, vN, vD);
               break;
            case ARM64vecu_UADDLV8x16:
               *p++ = X_3_8_5_6_5_5(X011, X01110001, X10000, X001110, vN, vD);
               break;
            case ARM64vecu_UADDLV16x8:
               *p++ = X_3_8_5_6_5_5(X011, X01110011, X10000, X001110, vN, vD);
               break;
            case ARM64vecu_UADDLV32x4:
               *p++ = X_3_8_5_6_5_5(X011, X01110101, X10000, X001110, vN, vD);
               break;
            case ARM64vecu_SADDLV8x16:
               *p++ = X_3_8_5_6_5_5(X010, X01110001, X10000, X001110, vN, vD);
               break;
            case ARM64vecu_SADDLV16x8:
               *p++ = X_3_8_5_6_5_5(X010, X01110011, X10000, X001110, vN, vD);
               break;
            case ARM64vecu_SADDLV32x4:
               *p++ = X_3_8_5_6_5_5(X010, X01110101, X10000, X001110, vN, vD);
               break;
            default:
               goto bad;
         }
         goto done;
      }
      case ARM64in_VNarrowV: {
         UInt vD = qregNo(i->ARM64in.VNarrowV.dst);
         UInt vN = qregNo(i->ARM64in.VNarrowV.src);
         UInt dszBlg2 = i->ARM64in.VNarrowV.dszBlg2;
         vassert(dszBlg2 >= 0 && dszBlg2 <= 2);
         *p++ = X_3_8_5_6_5_5(X000, X01110001 | (dszBlg2 << 1),
                              X00001, X001010, vN, vD);
         goto done;
      }
      case ARM64in_VShiftImmV: {
         UInt vD = qregNo(i->ARM64in.VShiftImmV.dst);
         UInt vN = qregNo(i->ARM64in.VShiftImmV.src);
         UInt sh = i->ARM64in.VShiftImmV.amt;
         ARM64VecShiftOp op = i->ARM64in.VShiftImmV.op;
         Bool syned = False;
         switch (op) {
            
            case ARM64vecsh_SSHR64x2: syned = True;
            case ARM64vecsh_USHR64x2: 
               if (sh >= 1 && sh <= 63) {
                  UInt xxxxxx = 64-sh;
                  *p++ = X_3_6_7_6_5_5(syned ? X010 : X011, X011110,
                                       X1000000 | xxxxxx, X000001, vN, vD);
                  goto done;
               }
               break;
            case ARM64vecsh_SHL64x2:
               if (sh >= 1 && sh <= 63) {
                  UInt xxxxxx = sh;
                  *p++ = X_3_6_7_6_5_5(X010, X011110,
                                       X1000000 | xxxxxx, X010101, vN, vD);
                  goto done;
               }
               break;
            
            case ARM64vecsh_SSHR32x4: syned = True;
            case ARM64vecsh_USHR32x4: 
               if (sh >= 1 && sh <= 31) {
                  UInt xxxxx = 32-sh;
                  *p++ = X_3_6_7_6_5_5(syned ? X010 : X011, X011110,
                                       X0100000 | xxxxx, X000001, vN, vD);
                  goto done;
               }
               break;
            case ARM64vecsh_SHL32x4:
               if (sh >= 1 && sh <= 31) {
                  UInt xxxxx = sh;
                  *p++ = X_3_6_7_6_5_5(X010, X011110,
                                       X0100000 | xxxxx, X010101, vN, vD);
                  goto done;
               }
               break;
            
            case ARM64vecsh_SSHR16x8: syned = True;
            case ARM64vecsh_USHR16x8: 
               if (sh >= 1 && sh <= 15) {
                  UInt xxxx = 16-sh;
                  *p++ = X_3_6_7_6_5_5(syned ? X010 : X011, X011110,
                                       X0010000 | xxxx, X000001, vN, vD);
                  goto done;
               }
               break;
            case ARM64vecsh_SHL16x8:
               if (sh >= 1 && sh <= 15) {
                  UInt xxxx = sh;
                  *p++ = X_3_6_7_6_5_5(X010, X011110,
                                       X0010000 | xxxx, X010101, vN, vD);
                  goto done;
               }
               break;


            
            case ARM64vecsh_SSHR8x16: syned = True;
            case ARM64vecsh_USHR8x16: 
               if (sh >= 1 && sh <= 7) {
                  UInt xxx = 8-sh;
                  *p++ = X_3_6_7_6_5_5(syned ? X010 : X011, X011110,
                                       X0001000 | xxx, X000001, vN, vD);
                  goto done;
               }
               break;
            case ARM64vecsh_SHL8x16:
               if (sh >= 1 && sh <= 7) {
                  UInt xxx = sh;
                  *p++ = X_3_6_7_6_5_5(X010, X011110,
                                       X0001000 | xxx, X010101, vN, vD);
                  goto done;
               }
               break;

            default:
               break;
         }
         goto bad;
      }
      case ARM64in_VImmQ: {
         UInt   rQ  = qregNo(i->ARM64in.VImmQ.rQ);
         UShort imm = i->ARM64in.VImmQ.imm;
         if (imm == 0x0000) {
            
            vassert(rQ < 32);
            *p++ = 0x4F000400 | rQ;
            goto done;
         }
         if (imm == 0x0001) {
            
            vassert(rQ < 32);
            *p++ = 0x2F00E420 | rQ;
            goto done;
         }
         if (imm == 0x0003) {
            
            vassert(rQ < 32);
            *p++ = 0x2F00E460 | rQ;
            goto done;
         }
         if (imm == 0x000F) {
            
            vassert(rQ < 32);
            *p++ = 0x2F00E5E0 | rQ;
            goto done;
         }
         if (imm == 0x00FF) {
            
            vassert(rQ < 32);
            *p++ = 0x2F07E7E0 | rQ;
            goto done;
         }
         goto bad; 
      }

      case ARM64in_VDfromX: {
         UInt dd = dregNo(i->ARM64in.VDfromX.rD);
         UInt xx = iregNo(i->ARM64in.VDfromX.rX);
         vassert(xx < 31);
         *p++ = 0x4E081C00 | X_2_6_2_12_5_5(0,0,0,0,xx,dd);
         goto done;
      }

      case ARM64in_VQfromXX: {
         UInt qq  = qregNo(i->ARM64in.VQfromXX.rQ);
         UInt xhi = iregNo(i->ARM64in.VQfromXX.rXhi);
         UInt xlo = iregNo(i->ARM64in.VQfromXX.rXlo);
         vassert(xhi < 31 && xlo < 31);
         *p++ = 0x4E081C00 | X_2_6_2_12_5_5(0,0,0,0,xlo,qq);
         *p++ = 0x4E181C00 | X_2_6_2_12_5_5(0,0,0,0,xhi,qq);
         goto done;
      }

      case ARM64in_VXfromQ: {
         UInt dd     = iregNo(i->ARM64in.VXfromQ.rX);
         UInt nn     = qregNo(i->ARM64in.VXfromQ.rQ);
         UInt laneNo = i->ARM64in.VXfromQ.laneNo;
         vassert(dd < 31);
         vassert(laneNo < 2);
         *p++ = X_3_8_5_6_5_5(X010, X01110000,
                              laneNo == 1 ? X11000 : X01000, X001111, nn, dd);
         goto done;
      }

      case ARM64in_VMov: {
        HReg rD = i->ARM64in.VMov.dst;
        HReg rN = i->ARM64in.VMov.src;
        switch (i->ARM64in.VMov.szB) {
           case 8: {
              UInt dd = dregNo(rD);
              UInt nn = dregNo(rN);
              *p++ = X_3_8_5_6_5_5(X000, X11110011, X00000, X010000, nn, dd);
              goto done;
           }
           default: 
              break;
        }
        goto bad;
      }

      case ARM64in_EvCheck: {
         UInt* p0 = p;
         p = do_load_or_store32(p, True, 9,
                                i->ARM64in.EvCheck.amCounter);
         *p++ = 0x71000529; 
         p = do_load_or_store32(p, False, 9,
                                i->ARM64in.EvCheck.amCounter);
         *p++ = 0x54000065; 
         p = do_load_or_store64(p, True, 9,
                                i->ARM64in.EvCheck.amFailAddr);
         *p++ = 0xD61F0120; 
         

         
         vassert(evCheckSzB_ARM64() == (UChar*)p - (UChar*)p0);
         goto done;
      }


      
      default: 
         goto bad;
    }

  bad:
   ppARM64Instr(i);
   vpanic("emit_ARM64Instr");
   

  done:
   vassert(((UChar*)p) - &buf[0] <= 36);
   return ((UChar*)p) - &buf[0];
}


Int evCheckSzB_ARM64 ( void )
{
   return 24;
}


VexInvalRange chainXDirect_ARM64 ( void* place_to_chain,
                                   void* disp_cp_chain_me_EXPECTED,
                                   void* place_to_jump_to )
{
   UInt* p = (UInt*)place_to_chain;
   vassert(0 == (3 & (HWord)p));
   vassert(is_imm64_to_iregNo_EXACTLY4(
              p, 9, Ptr_to_ULong(disp_cp_chain_me_EXPECTED)));
   vassert(p[4] == 0xD63F0120);

   (void)imm64_to_iregNo_EXACTLY4(
            p, 9, Ptr_to_ULong(place_to_jump_to));
   p[4] = 0xD61F0120;

   VexInvalRange vir = {(HWord)p, 20};
   return vir;
}


VexInvalRange unchainXDirect_ARM64 ( void* place_to_unchain,
                                     void* place_to_jump_to_EXPECTED,
                                     void* disp_cp_chain_me )
{
   UInt* p = (UInt*)place_to_unchain;
   vassert(0 == (3 & (HWord)p));
   vassert(is_imm64_to_iregNo_EXACTLY4(
              p, 9, Ptr_to_ULong(place_to_jump_to_EXPECTED)));
   vassert(p[4] == 0xD61F0120);

   (void)imm64_to_iregNo_EXACTLY4(
            p, 9, Ptr_to_ULong(disp_cp_chain_me));
   p[4] = 0xD63F0120;

   VexInvalRange vir = {(HWord)p, 20};
   return vir;
}



