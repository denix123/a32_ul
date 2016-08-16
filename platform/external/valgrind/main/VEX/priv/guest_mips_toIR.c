

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2010-2013 RT-RK
      mips-valgrind@rt-rk.com

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
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/


#include "libvex_basictypes.h"
#include "libvex_ir.h"
#include "libvex.h"
#include "libvex_guest_mips32.h"
#include "libvex_guest_mips64.h"

#include "main_util.h"
#include "main_globals.h"
#include "guest_generic_bb_to_IR.h"
#include "guest_mips_defs.h"



static Bool host_is_bigendian;

static UChar *guest_code;

#if defined(VGP_mips32_linux)
static Addr32 guest_PC_curr_instr;
#else
static Addr64 guest_PC_curr_instr;
#endif

static IRSB *irsb;

static Bool mode64 = False;

static Bool fp_mode64 = False;

#define ONE_SINGLE 0x3F800000
#define ONE_DOUBLE 0x3FF0000000000000ULL


#define DIP(format, args...)           \
   if (vex_traceflags & VEX_TRACE_FE)  \
      vex_printf(format, ## args)



static UInt integerGuestRegOffset(UInt iregNo)
{
   UInt ret;
   if (!mode64)
      switch (iregNo) {
         case 0:
            ret = offsetof(VexGuestMIPS32State, guest_r0); break;
         case 1:
            ret = offsetof(VexGuestMIPS32State, guest_r1); break;
         case 2:
            ret = offsetof(VexGuestMIPS32State, guest_r2); break;
         case 3:
            ret = offsetof(VexGuestMIPS32State, guest_r3); break;
         case 4:
            ret = offsetof(VexGuestMIPS32State, guest_r4); break;
         case 5:
            ret = offsetof(VexGuestMIPS32State, guest_r5); break;
         case 6:
            ret = offsetof(VexGuestMIPS32State, guest_r6); break;
         case 7:
            ret = offsetof(VexGuestMIPS32State, guest_r7); break;
         case 8:
            ret = offsetof(VexGuestMIPS32State, guest_r8); break;
         case 9:
            ret = offsetof(VexGuestMIPS32State, guest_r9); break;
         case 10:
            ret = offsetof(VexGuestMIPS32State, guest_r10); break;
         case 11:
            ret = offsetof(VexGuestMIPS32State, guest_r11); break;
         case 12:
            ret = offsetof(VexGuestMIPS32State, guest_r12); break;
         case 13:
            ret = offsetof(VexGuestMIPS32State, guest_r13); break;
         case 14:
            ret = offsetof(VexGuestMIPS32State, guest_r14); break;
         case 15:
            ret = offsetof(VexGuestMIPS32State, guest_r15); break;
         case 16:
            ret = offsetof(VexGuestMIPS32State, guest_r16); break;
         case 17:
            ret = offsetof(VexGuestMIPS32State, guest_r17); break;
         case 18:
            ret = offsetof(VexGuestMIPS32State, guest_r18); break;
         case 19:
            ret = offsetof(VexGuestMIPS32State, guest_r19); break;
         case 20:
            ret = offsetof(VexGuestMIPS32State, guest_r20); break;
         case 21:
            ret = offsetof(VexGuestMIPS32State, guest_r21); break;
         case 22:
            ret = offsetof(VexGuestMIPS32State, guest_r22); break;
         case 23:
            ret = offsetof(VexGuestMIPS32State, guest_r23); break;
         case 24:
            ret = offsetof(VexGuestMIPS32State, guest_r24); break;
         case 25:
            ret = offsetof(VexGuestMIPS32State, guest_r25); break;
         case 26:
            ret = offsetof(VexGuestMIPS32State, guest_r26); break;
         case 27:
            ret = offsetof(VexGuestMIPS32State, guest_r27); break;
         case 28:
            ret = offsetof(VexGuestMIPS32State, guest_r28); break;
         case 29:
            ret = offsetof(VexGuestMIPS32State, guest_r29); break;
         case 30:
            ret = offsetof(VexGuestMIPS32State, guest_r30); break;
         case 31:
            ret = offsetof(VexGuestMIPS32State, guest_r31); break;
         default:
            vassert(0);
            break;
      }
   else
      switch (iregNo) {
         case 0:
            ret = offsetof(VexGuestMIPS64State, guest_r0); break;
         case 1:
            ret = offsetof(VexGuestMIPS64State, guest_r1); break;
         case 2:
            ret = offsetof(VexGuestMIPS64State, guest_r2); break;
         case 3:
            ret = offsetof(VexGuestMIPS64State, guest_r3); break;
         case 4:
            ret = offsetof(VexGuestMIPS64State, guest_r4); break;
         case 5:
            ret = offsetof(VexGuestMIPS64State, guest_r5); break;
         case 6:
            ret = offsetof(VexGuestMIPS64State, guest_r6); break;
         case 7:
            ret = offsetof(VexGuestMIPS64State, guest_r7); break;
         case 8:
            ret = offsetof(VexGuestMIPS64State, guest_r8); break;
         case 9:
            ret = offsetof(VexGuestMIPS64State, guest_r9); break;
         case 10:
            ret = offsetof(VexGuestMIPS64State, guest_r10); break;
         case 11:
            ret = offsetof(VexGuestMIPS64State, guest_r11); break;
         case 12:
            ret = offsetof(VexGuestMIPS64State, guest_r12); break;
         case 13:
            ret = offsetof(VexGuestMIPS64State, guest_r13); break;
         case 14:
            ret = offsetof(VexGuestMIPS64State, guest_r14); break;
         case 15:
            ret = offsetof(VexGuestMIPS64State, guest_r15); break;
         case 16:
            ret = offsetof(VexGuestMIPS64State, guest_r16); break;
         case 17:
            ret = offsetof(VexGuestMIPS64State, guest_r17); break;
         case 18:
            ret = offsetof(VexGuestMIPS64State, guest_r18); break;
         case 19:
            ret = offsetof(VexGuestMIPS64State, guest_r19); break;
         case 20:
            ret = offsetof(VexGuestMIPS64State, guest_r20); break;
         case 21:
            ret = offsetof(VexGuestMIPS64State, guest_r21); break;
         case 22:
            ret = offsetof(VexGuestMIPS64State, guest_r22); break;
         case 23:
            ret = offsetof(VexGuestMIPS64State, guest_r23); break;
         case 24:
            ret = offsetof(VexGuestMIPS64State, guest_r24); break;
         case 25:
            ret = offsetof(VexGuestMIPS64State, guest_r25); break;
         case 26:
            ret = offsetof(VexGuestMIPS64State, guest_r26); break;
         case 27:
            ret = offsetof(VexGuestMIPS64State, guest_r27); break;
         case 28:
            ret = offsetof(VexGuestMIPS64State, guest_r28); break;
         case 29:
            ret = offsetof(VexGuestMIPS64State, guest_r29); break;
         case 30:
            ret = offsetof(VexGuestMIPS64State, guest_r30); break;
         case 31:
            ret = offsetof(VexGuestMIPS64State, guest_r31); break;
         default:
            vassert(0);
            break;
      }
   return ret;
}

#if defined(VGP_mips32_linux)
#define OFFB_PC     offsetof(VexGuestMIPS32State, guest_PC)
#else
#define OFFB_PC     offsetof(VexGuestMIPS64State, guest_PC)
#endif


static UInt floatGuestRegOffset(UInt fregNo)
{
   vassert(fregNo < 32);
   UInt ret;
   if (!mode64)
      switch (fregNo) {
         case 0:
            ret = offsetof(VexGuestMIPS32State, guest_f0); break;
         case 1:
            ret = offsetof(VexGuestMIPS32State, guest_f1); break;
         case 2:
            ret = offsetof(VexGuestMIPS32State, guest_f2); break;
         case 3:
            ret = offsetof(VexGuestMIPS32State, guest_f3); break;
         case 4:
            ret = offsetof(VexGuestMIPS32State, guest_f4); break;
         case 5:
            ret = offsetof(VexGuestMIPS32State, guest_f5); break;
         case 6:
            ret = offsetof(VexGuestMIPS32State, guest_f6); break;
         case 7:
            ret = offsetof(VexGuestMIPS32State, guest_f7); break;
         case 8:
            ret = offsetof(VexGuestMIPS32State, guest_f8); break;
         case 9:
            ret = offsetof(VexGuestMIPS32State, guest_f9); break;
         case 10:
            ret = offsetof(VexGuestMIPS32State, guest_f10); break;
         case 11:
            ret = offsetof(VexGuestMIPS32State, guest_f11); break;
         case 12:
            ret = offsetof(VexGuestMIPS32State, guest_f12); break;
         case 13:
            ret = offsetof(VexGuestMIPS32State, guest_f13); break;
         case 14:
            ret = offsetof(VexGuestMIPS32State, guest_f14); break;
         case 15:
            ret = offsetof(VexGuestMIPS32State, guest_f15); break;
         case 16:
            ret = offsetof(VexGuestMIPS32State, guest_f16); break;
         case 17:
            ret = offsetof(VexGuestMIPS32State, guest_f17); break;
         case 18:
            ret = offsetof(VexGuestMIPS32State, guest_f18); break;
         case 19:
            ret = offsetof(VexGuestMIPS32State, guest_f19); break;
         case 20:
            ret = offsetof(VexGuestMIPS32State, guest_f20); break;
         case 21:
            ret = offsetof(VexGuestMIPS32State, guest_f21); break;
         case 22:
            ret = offsetof(VexGuestMIPS32State, guest_f22); break;
         case 23:
            ret = offsetof(VexGuestMIPS32State, guest_f23); break;
         case 24:
            ret = offsetof(VexGuestMIPS32State, guest_f24); break;
         case 25:
            ret = offsetof(VexGuestMIPS32State, guest_f25); break;
         case 26:
            ret = offsetof(VexGuestMIPS32State, guest_f26); break;
         case 27:
            ret = offsetof(VexGuestMIPS32State, guest_f27); break;
         case 28:
            ret = offsetof(VexGuestMIPS32State, guest_f28); break;
         case 29:
            ret = offsetof(VexGuestMIPS32State, guest_f29); break;
         case 30:
            ret = offsetof(VexGuestMIPS32State, guest_f30); break;
         case 31:
            ret = offsetof(VexGuestMIPS32State, guest_f31); break;
         default:
            vassert(0);
            break;
      }
   else
      switch (fregNo) {
         case 0:
            ret = offsetof(VexGuestMIPS64State, guest_f0); break;
         case 1:
            ret = offsetof(VexGuestMIPS64State, guest_f1); break;
         case 2:
            ret = offsetof(VexGuestMIPS64State, guest_f2); break;
         case 3:
            ret = offsetof(VexGuestMIPS64State, guest_f3); break;
         case 4:
            ret = offsetof(VexGuestMIPS64State, guest_f4); break;
         case 5:
            ret = offsetof(VexGuestMIPS64State, guest_f5); break;
         case 6:
            ret = offsetof(VexGuestMIPS64State, guest_f6); break;
         case 7:
            ret = offsetof(VexGuestMIPS64State, guest_f7); break;
         case 8:
            ret = offsetof(VexGuestMIPS64State, guest_f8); break;
         case 9:
            ret = offsetof(VexGuestMIPS64State, guest_f9); break;
         case 10:
            ret = offsetof(VexGuestMIPS64State, guest_f10); break;
         case 11:
            ret = offsetof(VexGuestMIPS64State, guest_f11); break;
         case 12:
            ret = offsetof(VexGuestMIPS64State, guest_f12); break;
         case 13:
            ret = offsetof(VexGuestMIPS64State, guest_f13); break;
         case 14:
            ret = offsetof(VexGuestMIPS64State, guest_f14); break;
         case 15:
            ret = offsetof(VexGuestMIPS64State, guest_f15); break;
         case 16:
            ret = offsetof(VexGuestMIPS64State, guest_f16); break;
         case 17:
            ret = offsetof(VexGuestMIPS64State, guest_f17); break;
         case 18:
            ret = offsetof(VexGuestMIPS64State, guest_f18); break;
         case 19:
            ret = offsetof(VexGuestMIPS64State, guest_f19); break;
         case 20:
            ret = offsetof(VexGuestMIPS64State, guest_f20); break;
         case 21:
            ret = offsetof(VexGuestMIPS64State, guest_f21); break;
         case 22:
            ret = offsetof(VexGuestMIPS64State, guest_f22); break;
         case 23:
            ret = offsetof(VexGuestMIPS64State, guest_f23); break;
         case 24:
            ret = offsetof(VexGuestMIPS64State, guest_f24); break;
         case 25:
            ret = offsetof(VexGuestMIPS64State, guest_f25); break;
         case 26:
            ret = offsetof(VexGuestMIPS64State, guest_f26); break;
         case 27:
            ret = offsetof(VexGuestMIPS64State, guest_f27); break;
         case 28:
            ret = offsetof(VexGuestMIPS64State, guest_f28); break;
         case 29:
            ret = offsetof(VexGuestMIPS64State, guest_f29); break;
         case 30:
            ret = offsetof(VexGuestMIPS64State, guest_f30); break;
         case 31:
            ret = offsetof(VexGuestMIPS64State, guest_f31); break;
         default:
            vassert(0);
            break;
      }
   return ret;
}


static UInt accumulatorGuestRegOffset(UInt acNo)
{
   vassert(!mode64);
   vassert(acNo <= 3);
   UInt ret;
   switch (acNo) {
      case 0:
         ret = offsetof(VexGuestMIPS32State, guest_ac0); break;
      case 1:
         ret = offsetof(VexGuestMIPS32State, guest_ac1); break;
      case 2:
         ret = offsetof(VexGuestMIPS32State, guest_ac2); break;
      case 3:
         ret = offsetof(VexGuestMIPS32State, guest_ac3); break;
      default:
         vassert(0);
    break;
   }
   return ret;
}

static inline UInt getUInt(UChar * p)
{
   UInt w = 0;
#if defined (_MIPSEL)
   w = (w << 8) | p[3];
   w = (w << 8) | p[2];
   w = (w << 8) | p[1];
   w = (w << 8) | p[0];
#elif defined (_MIPSEB)
   w = (w << 8) | p[0];
   w = (w << 8) | p[1];
   w = (w << 8) | p[2];
   w = (w << 8) | p[3];
#endif
   return w;
}

#define BITS2(_b1,_b0) \
   (((_b1) << 1) | (_b0))

#define BITS3(_b2,_b1,_b0)                      \
  (((_b2) << 2) | ((_b1) << 1) | (_b0))

#define BITS4(_b3,_b2,_b1,_b0) \
   (((_b3) << 3) | ((_b2) << 2) | ((_b1) << 1) | (_b0))

#define BITS5(_b4,_b3,_b2,_b1,_b0)  \
   (((_b4) << 4) | BITS4((_b3),(_b2),(_b1),(_b0)))

#define BITS6(_b5,_b4,_b3,_b2,_b1,_b0)  \
   ((BITS2((_b5),(_b4)) << 4) \
    | BITS4((_b3),(_b2),(_b1),(_b0)))

#define BITS8(_b7,_b6,_b5,_b4,_b3,_b2,_b1,_b0)  \
   ((BITS4((_b7),(_b6),(_b5),(_b4)) << 4) \
    | BITS4((_b3),(_b2),(_b1),(_b0)))

#define LOAD_STORE_PATTERN \
   t1 = newTemp(mode64 ? Ity_I64 : Ity_I32); \
      if(!mode64) \
         assign(t1, binop(Iop_Add32, getIReg(rs), \
                                     mkU32(extend_s_16to32(imm)))); \
      else \
         assign(t1, binop(Iop_Add64, getIReg(rs), \
                                     mkU64(extend_s_16to64(imm)))); \

#define LOADX_STORE_PATTERN \
   t1 = newTemp(mode64 ? Ity_I64 : Ity_I32); \
      if(!mode64) \
         assign(t1, binop(Iop_Add32, getIReg(regRs), getIReg(regRt))); \
      else \
         assign(t1, binop(Iop_Add64, getIReg(regRs), getIReg(regRt)));

#define LWX_SWX_PATTERN64 \
   t2 = newTemp(Ity_I64); \
   assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFFCULL))); \
   t4 = newTemp(Ity_I32); \
   assign(t4, mkNarrowTo32( ty, binop(Iop_And64, \
                                      mkexpr(t1), mkU64(0x3))));

#define LWX_SWX_PATTERN64_1 \
   t2 = newTemp(Ity_I64); \
   assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFF8ULL))); \
   t4 = newTemp(Ity_I64); \
   assign(t4, binop(Iop_And64, mkexpr(t1), mkU64(0x7)));

#define LWX_SWX_PATTERN \
   t2 = newTemp(Ity_I32); \
   assign(t2, binop(Iop_And32, mkexpr(t1), mkU32(0xFFFFFFFC))); \
   t4 = newTemp(Ity_I32); \
   assign(t4, binop(Iop_And32, mkexpr(t1), mkU32(0x00000003)))

#define SXXV_PATTERN(op) \
   putIReg(rd, binop(op, \
         getIReg(rt), \
            unop(Iop_32to8, \
               binop(Iop_And32, \
                  getIReg(rs), \
                  mkU32(0x0000001F) \
               ) \
            ) \
         ) \
      )

#define SXXV_PATTERN64(op) \
   putIReg(rd, mkWidenFrom32(ty, binop(op, \
           mkNarrowTo32(ty, getIReg(rt)), \
             unop(Iop_32to8, \
                binop(Iop_And32, \
                   mkNarrowTo32(ty, getIReg(rs)), \
                   mkU32(0x0000001F) \
                ) \
             ) \
          ), True \
       ))

#define SXX_PATTERN(op) \
   putIReg(rd, binop(op, getIReg(rt), mkU8(sa)));

#define ALU_PATTERN(op) \
   putIReg(rd, binop(op, getIReg(rs), getIReg(rt)));

#define ALUI_PATTERN(op) \
   putIReg(rt, binop(op, getIReg(rs), mkU32(imm)));

#define ALUI_PATTERN64(op) \
   putIReg(rt, binop(op, getIReg(rs), mkU64(imm)));

#define ALU_PATTERN64(op) \
   putIReg(rd, mkWidenFrom32(ty, binop(op, \
                             mkNarrowTo32(ty, getIReg(rs)), \
                             mkNarrowTo32(ty, getIReg(rt))), True));

#define FP_CONDITIONAL_CODE \
   t3 = newTemp(Ity_I32);   \
   assign(t3, binop(Iop_And32, \
                 IRExpr_ITE( binop(Iop_CmpEQ32, mkU32(cc), mkU32(0)), \
                             binop(Iop_Shr32, getFCSR(), mkU8(23)), \
                             binop(Iop_Shr32, getFCSR(), mkU8(24+cc))), \
                 mkU32(0x1)));

#define ILLEGAL_INSTRUCTON \
   putPC(mkU32(guest_PC_curr_instr + 4)); \
   dres.jk_StopHere = Ijk_SigILL; \
   dres.whatNext    = Dis_StopHere;


static UInt get_opcode(UInt mipsins)
{
   return (0xFC000000 & mipsins) >> 26;
}

static UInt get_rs(UInt mipsins)
{
   return (0x03E00000 & mipsins) >> 21;
}

static UInt get_rt(UInt mipsins)
{
   return (0x001F0000 & mipsins) >> 16;
}

static UInt get_imm(UInt mipsins)
{
   return (0x0000FFFF & mipsins);
}

static UInt get_instr_index(UInt mipsins)
{
   return (0x03FFFFFF & mipsins);
}

static UInt get_rd(UInt mipsins)
{
   return (0x0000F800 & mipsins) >> 11;
}

static UInt get_sa(UInt mipsins)
{
   return (0x000007C0 & mipsins) >> 6;
}

static UInt get_function(UInt mipsins)
{
   return (0x0000003F & mipsins);
}

static UInt get_ft(UInt mipsins)
{
   return (0x001F0000 & mipsins) >> 16;
}

static UInt get_fs(UInt mipsins)
{
   return (0x0000F800 & mipsins) >> 11;
}

static UInt get_fd(UInt mipsins)
{
   return (0x000007C0 & mipsins) >> 6;
}

static UInt get_mov_cc(UInt mipsins)
{
   return (0x001C0000 & mipsins) >> 18;
}

static UInt get_bc1_cc(UInt mipsins)
{
   return (0x001C0000 & mipsins) >> 18;
}

static UInt get_fpc_cc(UInt mipsins)
{
   return (0x00000700 & mipsins) >> 8;
}

static UInt get_tf(UInt mipsins)
{
   return (0x00010000 & mipsins) >> 16;
}

static UInt get_nd(UInt mipsins)
{
   return (0x00020000 & mipsins) >> 17;
}

static UInt get_fmt(UInt mipsins)
{
   return (0x03E00000 & mipsins) >> 21;
}

static UInt get_FC(UInt mipsins)
{
   return (0x000000F0 & mipsins) >> 4;
}

static UInt get_cond(UInt mipsins)
{
   return (0x0000000F & mipsins);
}

static UInt get_code(UInt mipsins)
{
   return (0xFFC0 & mipsins) >> 6;
}

static UInt get_lsb(UInt mipsins)
{
   return (0x7C0 & mipsins) >> 6;
}

static UInt get_msb(UInt mipsins)
{
   return (0x0000F800 & mipsins) >> 11;
}

static UInt get_rot(UInt mipsins)
{
   return (0x00200000 & mipsins) >> 21;
}

static UInt get_rotv(UInt mipsins)
{
   return (0x00000040 & mipsins) >> 6;
}

static UInt get_sel(UInt mipsins)
{
   return (0x00000007 & mipsins);
}

static UInt get_acNo(UInt mipsins)
{
   return (0x00001800 & mipsins) >> 11;
}

static UInt get_acNo_mfhilo(UInt mipsins)
{
   return (0x00600000 & mipsins) >> 21;
}

static UInt get_wrdspMask(UInt mipsins)
{
   return (0x001ff800 & mipsins) >> 11;
}

static UInt get_rddspMask(UInt mipsins)
{
   return (0x03ff0000 & mipsins) >> 16;
}

static UInt get_shift(UInt mipsins)
{
   return (0x03f00000 & mipsins) >> 20;
}

static UInt get_dspImm(UInt mipsins)
{
   return (0x03ff0000 & mipsins) >> 16;
}

static Bool branch_or_jump(UChar * addr)
{
   UInt fmt;
   UInt cins = getUInt(addr);

   UInt opcode = get_opcode(cins);
   UInt rt = get_rt(cins);
   UInt function = get_function(cins);

   
   if (opcode == 0x07 || opcode == 0x06 || opcode == 0x05 || opcode == 0x04
       || opcode == 0x03 || opcode == 0x02) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x01) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x11) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x10) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x00) {
      return True;
   }

   
   if (opcode == 0x00 && function == 0x09) {
      return True;
   }

   
   if (opcode == 0x00 && function == 0x08) {
      return True;
   }

   if (opcode == 0x11) {
      
      fmt = get_fmt(cins);
      if (fmt == 0x08) {
         return True;
      }
   }

   
   if (opcode == 0x01 && rt == 0x1c) {
      return True;
   }

   return False;
}

static Bool is_Branch_or_Jump_and_Link(UChar * addr)
{
   UInt cins = getUInt(addr);

   UInt opcode = get_opcode(cins);
   UInt rt = get_rt(cins);
   UInt function = get_function(cins);

   
   if (opcode == 0x02) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x11) {
      return True;
   }

   
   if (opcode == 0x01 && rt == 0x10) {
      return True;
   }

   
   if (opcode == 0x00 && function == 0x09) {
      return True;
   }

   return False;
}

static Bool branch_or_link_likely(UChar * addr)
{
   UInt cins = getUInt(addr);
   UInt opcode = get_opcode(cins);
   UInt rt = get_rt(cins);

   
   if (opcode == 0x17 || opcode == 0x16 || opcode == 0x15 || opcode == 0x14)
      return True;

   
   if (opcode == 0x01 && rt == 0x03)
      return True;

   
   if (opcode == 0x01 && rt == 0x13)
      return True;

   
   if (opcode == 0x01 && rt == 0x12)
      return True;

   
   if (opcode == 0x01 && rt == 0x02)
      return True;

   return False;
}


static IRExpr *mkU8(UInt i)
{
   vassert(i < 256);
   return IRExpr_Const(IRConst_U8((UChar) i));
}

static IRExpr *mkU16(UInt i)
{
   return IRExpr_Const(IRConst_U16(i));
}

static IRExpr *mkU32(UInt i)
{
   return IRExpr_Const(IRConst_U32(i));
}

static IRExpr *mkU64(ULong i)
{
   return IRExpr_Const(IRConst_U64(i));
}

static IRExpr *mkexpr(IRTemp tmp)
{
   return IRExpr_RdTmp(tmp);
}

static IRExpr *unop(IROp op, IRExpr * a)
{
   return IRExpr_Unop(op, a);
}

static IRExpr *binop(IROp op, IRExpr * a1, IRExpr * a2)
{
   return IRExpr_Binop(op, a1, a2);
}

static IRExpr *triop(IROp op, IRExpr * a1, IRExpr * a2, IRExpr * a3)
{
   return IRExpr_Triop(op, a1, a2, a3);
}

static IRExpr *qop ( IROp op, IRExpr * a1, IRExpr * a2, IRExpr * a3,
                     IRExpr * a4 )
{
   return IRExpr_Qop(op, a1, a2, a3, a4);
}

static IRExpr *load(IRType ty, IRExpr * addr)
{
   IRExpr *load1 = NULL;
#if defined (_MIPSEL)
   load1 = IRExpr_Load(Iend_LE, ty, addr);
#elif defined (_MIPSEB)
   load1 = IRExpr_Load(Iend_BE, ty, addr);
#endif
   return load1;
}

static void stmt(IRStmt * st)
{
   addStmtToIRSB(irsb, st);
}

static void assign(IRTemp dst, IRExpr * e)
{
   stmt(IRStmt_WrTmp(dst, e));
}

static void store(IRExpr * addr, IRExpr * data)
{
#if defined (_MIPSEL)
   stmt(IRStmt_Store(Iend_LE, addr, data));
#elif defined (_MIPSEB)
   stmt(IRStmt_Store(Iend_BE, addr, data));
#endif
}

static IRTemp newTemp(IRType ty)
{
   vassert(isPlausibleIRType(ty));
   return newIRTemp(irsb->tyenv, ty);
}

static IRExpr *genROR32(IRExpr * src, Int rot)
{
   vassert(rot >= 0 && rot < 32);
   if (rot == 0)
      return src;
   return binop(Iop_Or32, binop(Iop_Shl32, src, mkU8(32 - rot)),
                          binop(Iop_Shr32, src, mkU8(rot)));
}

static IRExpr *genRORV32(IRExpr * src, IRExpr * rs)
{
   IRTemp t0 = newTemp(Ity_I8);
   IRTemp t1 = newTemp(Ity_I8);

   assign(t0, unop(Iop_32to8, binop(Iop_And32, rs, mkU32(0x0000001F))));
   assign(t1, binop(Iop_Sub8, mkU8(32), mkexpr(t0)));
   return binop(Iop_Or32, binop(Iop_Shl32, src, mkexpr(t1)),
                          binop(Iop_Shr32, src, mkexpr(t0)));
}

static UShort extend_s_10to16(UInt x)
{
   return (UShort) ((((Int) x) << 22) >> 22);
}

static ULong extend_s_10to32(UInt x)
{
   return (ULong)((((Long) x) << 22) >> 22);
}

static ULong extend_s_10to64(UInt x)
{
   return (ULong)((((Long) x) << 54) >> 54);
}

static UInt extend_s_16to32(UInt x)
{
   return (UInt) ((((Int) x) << 16) >> 16);
}

static UInt extend_s_18to32(UInt x)
{
   return (UInt) ((((Int) x) << 14) >> 14);
}

static ULong extend_s_16to64 ( UInt x )
{
   return (ULong) ((((Long) x) << 48) >> 48);
}

static ULong extend_s_18to64 ( UInt x )
{
   return (ULong) ((((Long) x) << 46) >> 46);
}

static ULong extend_s_32to64 ( UInt x )
{
   return (ULong) ((((Long) x) << 32) >> 32);
}

static void jmp_lit32 (  DisResult* dres, IRJumpKind kind, Addr32 d32 )
{
   vassert(dres->whatNext    == Dis_Continue);
   vassert(dres->len         == 0);
   vassert(dres->continueAt  == 0);
   vassert(dres->jk_StopHere == Ijk_INVALID);
   dres->whatNext    = Dis_StopHere;
   dres->jk_StopHere = kind;
   stmt( IRStmt_Put( OFFB_PC, mkU32(d32) ) );
}

static void jmp_lit64 (  DisResult* dres, IRJumpKind kind, Addr64 d64 )
{
   vassert(dres->whatNext    == Dis_Continue);
   vassert(dres->len         == 0);
   vassert(dres->continueAt  == 0);
   vassert(dres->jk_StopHere == Ijk_INVALID);
   dres->whatNext    = Dis_StopHere;
   dres->jk_StopHere = kind;
   stmt(IRStmt_Put(OFFB_PC, mkU64(d64)));
}

static IRExpr *getAcc(UInt acNo)
{
   vassert(!mode64);
   vassert(acNo <= 3);
   return IRExpr_Get(accumulatorGuestRegOffset(acNo), Ity_I64);
}

static IRExpr *getDSPControl(void)
{
   vassert(!mode64);
   return IRExpr_Get(offsetof(VexGuestMIPS32State, guest_DSPControl), Ity_I32);
}

/* Put value to DSPControl register. Expression e is written to DSPControl as
   is. If only certain bits of DSPControl need to be changed, it should be done
   before calling putDSPControl(). It could be done by reading DSPControl and
   ORing it with appropriate mask. */
static void putDSPControl(IRExpr * e)
{
   vassert(!mode64);
   stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_DSPControl), e));
}

static UChar getIByte(Int delta)
{
   return guest_code[delta];
}

static IRExpr *getIReg(UInt iregNo)
{
   if (0 == iregNo) {
      return mode64 ? mkU64(0x0) : mkU32(0x0);
   } else {
      IRType ty = mode64 ? Ity_I64 : Ity_I32;
      vassert(iregNo < 32);
      return IRExpr_Get(integerGuestRegOffset(iregNo), ty);
   }
}

static IRExpr *getHI(void)
{
   if (mode64)
      return IRExpr_Get(offsetof(VexGuestMIPS64State, guest_HI), Ity_I64);
   else
      return IRExpr_Get(offsetof(VexGuestMIPS32State, guest_HI), Ity_I32);
}

static IRExpr *getLO(void)
{
   if (mode64)
      return IRExpr_Get(offsetof(VexGuestMIPS64State, guest_LO), Ity_I64);
   else
      return IRExpr_Get(offsetof(VexGuestMIPS32State, guest_LO), Ity_I32);
}

static IRExpr *getFCSR(void)
{
   if (mode64)
      return IRExpr_Get(offsetof(VexGuestMIPS64State, guest_FCSR), Ity_I32);
   else
      return IRExpr_Get(offsetof(VexGuestMIPS32State, guest_FCSR), Ity_I32);
}

static IRExpr *getByteFromReg(UInt reg, UInt byte_pos)
{
  UInt pos = byte_pos * 8;
  if (mode64)
      return unop(Iop_64to8, binop(Iop_And64,
                                   binop(Iop_Shr64, getIReg(reg), mkU8(pos)),
                                   mkU64(0xFF)));
   else
      return unop(Iop_32to8, binop(Iop_And32,
                                   binop(Iop_Shr32, getIReg(reg), mkU8(pos)),
                                   mkU32(0xFF)));
}

static void putFCSR(IRExpr * e)
{
   if (mode64)
      stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_FCSR), e));
   else
      stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_FCSR), e));
}

static void calculateFCSR(UInt fs, UInt ft, UInt inst, Bool sz32, UInt opN)
{
   IRDirty *d;
   IRTemp fcsr = newTemp(Ity_I32);
   
   if (fp_mode64)
      d = unsafeIRDirty_1_N(fcsr, 0,
                            "mips_dirtyhelper_calculate_FCSR_fp64",
                            &mips_dirtyhelper_calculate_FCSR_fp64,
                            mkIRExprVec_4(IRExpr_BBPTR(),
                                          mkU32(fs),
                                          mkU32(ft),
                                          mkU32(inst)));
   else
      d = unsafeIRDirty_1_N(fcsr, 0,
                            "mips_dirtyhelper_calculate_FCSR_fp32",
                            &mips_dirtyhelper_calculate_FCSR_fp32,
                            mkIRExprVec_4(IRExpr_BBPTR(),
                                          mkU32(fs),
                                          mkU32(ft),
                                          mkU32(inst)));

   if (opN == 1) {  
      
      if (sz32 || fp_mode64)
         d->nFxState = 2;
      else
         d->nFxState = 3;
      vex_bzero(&d->fxState, sizeof(d->fxState));

      d->fxState[0].fx     = Ifx_Read;  
      if (mode64)
         d->fxState[0].offset = offsetof(VexGuestMIPS64State, guest_FCSR);
      else
         d->fxState[0].offset = offsetof(VexGuestMIPS32State, guest_FCSR);
      d->fxState[0].size   = sizeof(UInt);
      d->fxState[1].fx     = Ifx_Read;  
      d->fxState[1].offset = floatGuestRegOffset(fs);
      d->fxState[1].size   = sizeof(ULong);

      if (!(sz32 || fp_mode64)) {
         d->fxState[2].fx     = Ifx_Read;  
         d->fxState[2].offset = floatGuestRegOffset(fs+1);
         d->fxState[2].size   = sizeof(ULong);
      }
   } else if (opN == 2) {  
      
      if (sz32 || fp_mode64)
         d->nFxState = 3;
      else
         d->nFxState = 5;
      vex_bzero(&d->fxState, sizeof(d->fxState));

      d->fxState[0].fx     = Ifx_Read;  
      if (mode64)
         d->fxState[0].offset = offsetof(VexGuestMIPS64State, guest_FCSR);
      else
         d->fxState[0].offset = offsetof(VexGuestMIPS32State, guest_FCSR);
      d->fxState[0].size   = sizeof(UInt);
      d->fxState[1].fx     = Ifx_Read;  
      d->fxState[1].offset = floatGuestRegOffset(fs);
      d->fxState[1].size   = sizeof(ULong);
      d->fxState[2].fx     = Ifx_Read;  
      d->fxState[2].offset = floatGuestRegOffset(ft);
      d->fxState[2].size   = sizeof(ULong);

      if (!(sz32 || fp_mode64)) {
         d->fxState[3].fx     = Ifx_Read;  
         d->fxState[3].offset = floatGuestRegOffset(fs+1);
         d->fxState[3].size   = sizeof(ULong);
         d->fxState[4].fx     = Ifx_Read;  
         d->fxState[4].offset = floatGuestRegOffset(ft+1);
         d->fxState[4].size   = sizeof(ULong);
      }
   }

   stmt(IRStmt_Dirty(d));

   putFCSR(mkexpr(fcsr));
}

static IRExpr *getULR(void)
{
   if (mode64)
      return IRExpr_Get(offsetof(VexGuestMIPS64State, guest_ULR), Ity_I64);
   else
      return IRExpr_Get(offsetof(VexGuestMIPS32State, guest_ULR), Ity_I32);
}

static void putIReg(UInt archreg, IRExpr * e)
{
   IRType ty = mode64 ? Ity_I64 : Ity_I32;
   vassert(archreg < 32);
   vassert(typeOfIRExpr(irsb->tyenv, e) == ty);
   if (archreg != 0)
      stmt(IRStmt_Put(integerGuestRegOffset(archreg), e));
}

static IRExpr *mkNarrowTo32(IRType ty, IRExpr * src)
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   return ty == Ity_I64 ? unop(Iop_64to32, src) : src;
}

static void putLO(IRExpr * e)
{
   if (mode64) {
      stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_LO), e));
   } else {
      stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_LO), e));
      IRTemp t_lo = newTemp(Ity_I32);
      IRTemp t_hi = newTemp(Ity_I32);
      assign(t_lo, e);
      assign(t_hi, unop(Iop_64HIto32, getAcc(0)));
      stmt(IRStmt_Put(accumulatorGuestRegOffset(0),
           binop(Iop_32HLto64, mkexpr(t_hi), mkexpr(t_lo))));
   }
}

static void putHI(IRExpr * e)
{
   if (mode64) {
      stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_HI), e));
   } else {
      stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_HI), e));
      IRTemp t_lo = newTemp(Ity_I32);
      IRTemp t_hi = newTemp(Ity_I32);
      assign(t_hi, e);
      assign(t_lo, unop(Iop_64to32, getAcc(0)));
      stmt(IRStmt_Put(accumulatorGuestRegOffset(0),
           binop(Iop_32HLto64, mkexpr(t_hi), mkexpr(t_lo))));
   }
}

static void putAcc(UInt acNo, IRExpr * e)
{
   vassert(!mode64);
   vassert(acNo <= 3);
   vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_I64);
   stmt(IRStmt_Put(accumulatorGuestRegOffset(acNo), e));
   if (0 == acNo) {
     putLO(unop(Iop_64to32, e));
     putHI(unop(Iop_64HIto32, e));
   }
}

static IRExpr *mkNarrowTo8 ( IRType ty, IRExpr * src )
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   return ty == Ity_I64 ? unop(Iop_64to8, src) : unop(Iop_32to8, src);
}

static void putPC(IRExpr * e)
{
   stmt(IRStmt_Put(OFFB_PC, e));
}

static IRExpr *mkWidenFrom32(IRType ty, IRExpr * src, Bool sined)
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   if (ty == Ity_I32)
      return src;
   return (sined) ? unop(Iop_32Sto64, src) : unop(Iop_32Uto64, src);
}

static IRExpr *narrowTo(IRType dst_ty, IRExpr * e)
{
   IRType src_ty = typeOfIRExpr(irsb->tyenv, e);
   if (src_ty == dst_ty)
      return e;
   if (src_ty == Ity_I32 && dst_ty == Ity_I16)
      return unop(Iop_32to16, e);
   if (src_ty == Ity_I32 && dst_ty == Ity_I8)
      return unop(Iop_32to8, e);
   if (src_ty == Ity_I64 && dst_ty == Ity_I8) {
      vassert(mode64);
      return unop(Iop_64to8, e);
   }
   if (src_ty == Ity_I64 && dst_ty == Ity_I16) {
      vassert(mode64);
      return unop(Iop_64to16, e);
   }
   vpanic("narrowTo(mips)");
   return 0;
}

static IRExpr *getLoFromF64(IRType ty, IRExpr * src)
{
   vassert(ty == Ity_F32 || ty == Ity_F64);
   if (ty == Ity_F64) {
      IRTemp t0, t1;
      t0 = newTemp(Ity_I64);
      t1 = newTemp(Ity_I32);
      assign(t0, unop(Iop_ReinterpF64asI64, src));
      assign(t1, unop(Iop_64to32, mkexpr(t0)));
      return unop(Iop_ReinterpI32asF32, mkexpr(t1));
   } else
      return src;
}

static IRExpr *mkWidenFromF32(IRType ty, IRExpr * src)
{
   vassert(ty == Ity_F32 || ty == Ity_F64);
   if (ty == Ity_F64) {
      IRTemp t0 = newTemp(Ity_I32);
      IRTemp t1 = newTemp(Ity_I64);
      assign(t0, unop(Iop_ReinterpF32asI32, src));
      assign(t1, binop(Iop_32HLto64, mkU32(0x0), mkexpr(t0)));
      return unop(Iop_ReinterpI64asF64, mkexpr(t1));
   } else
      return src;
}

static IRExpr *dis_branch_likely(IRExpr * guard, UInt imm)
{
   ULong branch_offset;
   IRTemp t0;

   if (mode64)
      branch_offset = extend_s_18to64(imm << 2);
   else
      branch_offset = extend_s_18to32(imm << 2);

   t0 = newTemp(Ity_I1);
   assign(t0, guard);

   if (mode64)
      stmt(IRStmt_Exit(mkexpr(t0), Ijk_Boring,
                       IRConst_U64(guest_PC_curr_instr + 8), OFFB_PC));
   else
      stmt(IRStmt_Exit(mkexpr(t0), Ijk_Boring,
                       IRConst_U32(guest_PC_curr_instr + 8), OFFB_PC));

   irsb->jumpkind = Ijk_Boring;

   if (mode64)
      return mkU64(guest_PC_curr_instr + 4 + branch_offset);
   else
      return mkU32(guest_PC_curr_instr + 4 + branch_offset);
}

static void dis_branch(Bool link, IRExpr * guard, UInt imm, IRStmt ** set)
{
   ULong branch_offset;
   IRTemp t0;

   if (link) {  
      if (mode64)
         putIReg(31, mkU64(guest_PC_curr_instr + 8));
      else
         putIReg(31, mkU32(guest_PC_curr_instr + 8));
   }


   if (mode64)
      branch_offset = extend_s_18to64(imm << 2);
   else
      branch_offset = extend_s_18to32(imm << 2);

   t0 = newTemp(Ity_I1);
   assign(t0, guard);
   if (mode64)
      *set = IRStmt_Exit(mkexpr(t0), link ? Ijk_Call : Ijk_Boring,
                         IRConst_U64(guest_PC_curr_instr + 4 + branch_offset),
                         OFFB_PC);
   else
      *set = IRStmt_Exit(mkexpr(t0), link ? Ijk_Call : Ijk_Boring,
                         IRConst_U32(guest_PC_curr_instr + 4 +
                                     (UInt) branch_offset), OFFB_PC);
}

static IRExpr *getFReg(UInt fregNo)
{
   vassert(fregNo < 32);
   IRType ty = fp_mode64 ? Ity_F64 : Ity_F32;
   return IRExpr_Get(floatGuestRegOffset(fregNo), ty);
}

static IRExpr *getDReg(UInt dregNo)
{
   vassert(dregNo < 32);
   if (fp_mode64) {
      return IRExpr_Get(floatGuestRegOffset(dregNo), Ity_F64);
   } else {
      IRTemp t0 = newTemp(Ity_F32);
      IRTemp t1 = newTemp(Ity_F32);
      IRTemp t2 = newTemp(Ity_F64);
      IRTemp t3 = newTemp(Ity_I32);
      IRTemp t4 = newTemp(Ity_I32);
      IRTemp t5 = newTemp(Ity_I64);

      assign(t0, getFReg(dregNo));
      assign(t1, getFReg(dregNo + 1));

      assign(t3, unop(Iop_ReinterpF32asI32, mkexpr(t0)));
      assign(t4, unop(Iop_ReinterpF32asI32, mkexpr(t1)));
      assign(t5, binop(Iop_32HLto64, mkexpr(t4), mkexpr(t3)));
      assign(t2, unop(Iop_ReinterpI64asF64, mkexpr(t5)));

      return mkexpr(t2);
   }
}

static void putFReg(UInt dregNo, IRExpr * e)
{
   vassert(dregNo < 32);
   IRType ty = fp_mode64 ? Ity_F64 : Ity_F32;
   vassert(typeOfIRExpr(irsb->tyenv, e) == ty);
   stmt(IRStmt_Put(floatGuestRegOffset(dregNo), e));
}

static void putDReg(UInt dregNo, IRExpr * e)
{
   if (fp_mode64) {
      vassert(dregNo < 32);
      IRType ty = Ity_F64;
      vassert(typeOfIRExpr(irsb->tyenv, e) == ty);
      stmt(IRStmt_Put(floatGuestRegOffset(dregNo), e));
   } else {
      vassert(dregNo < 32);
      vassert(typeOfIRExpr(irsb->tyenv, e) == Ity_F64);
      IRTemp t1 = newTemp(Ity_F64);
      IRTemp t4 = newTemp(Ity_I32);
      IRTemp t5 = newTemp(Ity_I32);
      IRTemp t6 = newTemp(Ity_I64);
      assign(t1, e);
      assign(t6, unop(Iop_ReinterpF64asI64, mkexpr(t1)));
      assign(t4, unop(Iop_64HIto32, mkexpr(t6)));  
      assign(t5, unop(Iop_64to32, mkexpr(t6)));    
      putFReg(dregNo, unop(Iop_ReinterpI32asF32, mkexpr(t5)));
      putFReg(dregNo + 1, unop(Iop_ReinterpI32asF32, mkexpr(t4)));
   }
}

static void setFPUCondCode(IRExpr * e, UInt cc)
{
   if (cc == 0) {
      putFCSR(binop(Iop_And32, getFCSR(), mkU32(0xFF7FFFFF)));
      putFCSR(binop(Iop_Or32, getFCSR(), binop(Iop_Shl32, e, mkU8(23))));
   } else {
      putFCSR(binop(Iop_And32, getFCSR(), unop(Iop_Not32,
                               binop(Iop_Shl32, mkU32(0x01000000), mkU8(cc)))));
      putFCSR(binop(Iop_Or32, getFCSR(), binop(Iop_Shl32, e, mkU8(24 + cc))));
   }
}

static IRExpr* get_IR_roundingmode ( void )
{
   IRTemp rm_MIPS = newTemp(Ity_I32);
   

   if (mode64)
      assign(rm_MIPS, binop(Iop_And32, IRExpr_Get(offsetof(VexGuestMIPS64State,
                                       guest_FCSR), Ity_I32), mkU32(3)));
   else
      assign(rm_MIPS, binop(Iop_And32, IRExpr_Get(offsetof(VexGuestMIPS32State,
                                       guest_FCSR), Ity_I32), mkU32(3)));

   

   return binop(Iop_Xor32, mkexpr(rm_MIPS), binop(Iop_And32,
                binop(Iop_Shl32, mkexpr(rm_MIPS), mkU8(1)), mkU32(2)));
}

static IRExpr *mkSzImm ( IRType ty, ULong imm64 )
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   return ty == Ity_I64 ? mkU64(imm64) : mkU32((UInt) imm64);
}

static IRConst *mkSzConst ( IRType ty, ULong imm64 )
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   return (ty == Ity_I64 ? IRConst_U64(imm64) : IRConst_U32((UInt) imm64));
}

static Addr64 mkSzAddr ( IRType ty, Addr64 addr )
{
   vassert(ty == Ity_I32 || ty == Ity_I64);
   return (ty == Ity_I64 ? (Addr64) addr :
                           (Addr64) extend_s_32to64(toUInt(addr)));
}

static Bool dis_instr_shrt ( UInt theInstr )
{
   UInt opc2 = get_function(theInstr);
   UChar regRs = get_rs(theInstr);
   UChar regRt = get_rt(theInstr);
   UChar regRd = get_rd(theInstr);
   UChar uImmsa = get_sa(theInstr);
   Long sImmsa = extend_s_16to64(uImmsa);
   IRType ty = mode64 ? Ity_I64 : Ity_I32;
   IRTemp tmp = newTemp(ty);
   IRTemp tmpOr = newTemp(ty);
   IRTemp tmpRt = newTemp(ty);
   IRTemp tmpRs = newTemp(ty);
   IRTemp tmpRd = newTemp(ty);

   assign(tmpRs, getIReg(regRs));
   assign(tmpRt, getIReg(regRt));

   switch (opc2) {
      case 0x3A:
         if ((regRs & 0x01) == 0) {
            
            DIP("dsrl r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
            assign(tmpRd, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(uImmsa)));
            putIReg(regRd, mkexpr(tmpRd));
         } else if ((regRs & 0x01) == 1) {
            
            vassert(mode64);
            DIP("drotr r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
            IRTemp tmpL = newTemp(ty);
            IRTemp tmpR = newTemp(ty);
            assign(tmpR, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(uImmsa)));
            assign(tmp, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(63 - uImmsa)));
            assign(tmpL, binop(Iop_Shl64, mkexpr(tmp), mkU8(1)));
            assign(tmpRd, binop(Iop_Or64, mkexpr(tmpL), mkexpr(tmpR)));
            putIReg(regRd, mkexpr(tmpRd));
         } else
            return False;
         break;

      case 0x3E:
         if ((regRs & 0x01) == 0) {
            
            DIP("dsrl32 r%u, r%u, %d", regRd, regRt, (Int)(sImmsa + 32));
            assign(tmpRd, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(uImmsa + 32)));
            putIReg(regRd, mkexpr(tmpRd));
         } else if ((regRs & 0x01) == 1) {
            
            DIP("drotr32 r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
            vassert(mode64);
            IRTemp tmpL = newTemp(ty);
            IRTemp tmpR = newTemp(ty);
            
            assign(tmpR, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(uImmsa + 32)));
            assign(tmp, binop(Iop_Shl64, mkexpr(tmpRt),
                              mkU8(63 - (uImmsa + 32))));
            assign(tmpL, binop(Iop_Shl64, mkexpr(tmp), mkU8(1)));
            assign(tmpRd, binop(Iop_Or64, mkexpr(tmpL), mkexpr(tmpR)));
            putIReg(regRd, mkexpr(tmpRd));
         } else
            return False;
         break;

      case 0x16:
         if ((uImmsa & 0x01) == 0) {
            
            DIP("dsrlv r%u, r%u, r%u", regRd, regRt, regRs);
            IRTemp tmpRs8 = newTemp(Ity_I8);
            
            assign(tmp, binop(Iop_And64, mkexpr(tmpRs), mkU64(63)));
            assign(tmpRs8, mkNarrowTo8(ty, mkexpr(tmp)));
            assign(tmpRd, binop(Iop_Shr64, mkexpr(tmpRt), mkexpr(tmpRs8)));
            putIReg(regRd, mkexpr(tmpRd));
         } else if ((uImmsa & 0x01) == 1) {
            
            DIP("drotrv r%u, r%u, r%u", regRd, regRt, regRs);
            IRTemp tmpL = newTemp(ty);
            IRTemp tmpR = newTemp(ty);
            IRTemp tmpRs8 = newTemp(Ity_I8);
            IRTemp tmpLs8 = newTemp(Ity_I8);
            IRTemp tmp64 = newTemp(ty);

            assign(tmp64, binop(Iop_And64, mkexpr(tmpRs), mkSzImm(ty, 63)));
            assign(tmp, binop(Iop_Sub64, mkU64(63), mkexpr(tmp64)));

            assign(tmpLs8, mkNarrowTo8(ty, mkexpr(tmp)));
            assign(tmpRs8, mkNarrowTo8(ty, mkexpr(tmp64)));

            assign(tmpR, binop(Iop_Shr64, mkexpr(tmpRt), mkexpr(tmpRs8)));
            assign(tmpL, binop(Iop_Shl64, mkexpr(tmpRt), mkexpr(tmpLs8)));
            assign(tmpRd, binop(Iop_Shl64, mkexpr(tmpL), mkU8(1)));
            assign(tmpOr, binop(Iop_Or64, mkexpr(tmpRd), mkexpr(tmpR)));

            putIReg(regRd, mkexpr(tmpOr));
         } else
            return False;
         break;

      case 0x38:  
         DIP("dsll r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
         vassert(mode64);
         assign(tmpRd, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(uImmsa)));
         putIReg(regRd, mkexpr(tmpRd));
         break;

      case 0x3C:  
         DIP("dsll32 r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
         assign(tmpRd, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(uImmsa + 32)));
         putIReg(regRd, mkexpr(tmpRd));
         break;

      case 0x14: {  
         DIP("dsllv r%u, r%u, r%u", regRd, regRt, regRs);
         IRTemp tmpRs8 = newTemp(Ity_I8);

         assign(tmp, binop(Iop_And64, mkexpr(tmpRs), mkSzImm(ty, 63)));
         assign(tmpRs8, mkNarrowTo8(ty, mkexpr(tmp)));
         assign(tmpRd, binop(Iop_Shl64, mkexpr(tmpRt), mkexpr(tmpRs8)));
         putIReg(regRd, mkexpr(tmpRd));
         break;
      }

      case 0x3B:  
         DIP("dsra r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
         assign(tmpRd, binop(Iop_Sar64, mkexpr(tmpRt), mkU8(uImmsa)));
         putIReg(regRd, mkexpr(tmpRd));
         break;

      case 0x3F:  
         DIP("dsra32 r%u, r%u, %d", regRd, regRt, (Int)sImmsa);
         assign(tmpRd, binop(Iop_Sar64, mkexpr(tmpRt), mkU8(uImmsa + 32)));
         putIReg(regRd, mkexpr(tmpRd));
         break;

      case 0x17: {  
         DIP("dsrav r%u, r%u, r%u", regRd, regRt, regRs);
         IRTemp tmpRs8 = newTemp(Ity_I8);
         assign(tmp, binop(Iop_And64, mkexpr(tmpRs), mkSzImm(ty, 63)));
         assign(tmpRs8, mkNarrowTo8(ty, mkexpr(tmp)));
         assign(tmpRd, binop(Iop_Sar64, mkexpr(tmpRt), mkexpr(tmpRs8)));
         putIReg(regRd, mkexpr(tmpRd));
         break;

      }

      default:
         return False;

   }
   return True;
}

static IROp mkSzOp ( IRType ty, IROp op8 )
{
   Int adj;
   vassert(ty == Ity_I8 || ty == Ity_I16 || ty == Ity_I32 || ty == Ity_I64);
   vassert(op8 == Iop_Add8 || op8 == Iop_Sub8 || op8 == Iop_Mul8
           || op8 == Iop_Or8 || op8 == Iop_And8 || op8 == Iop_Xor8
           || op8 == Iop_Shl8 || op8 == Iop_Shr8 || op8 == Iop_Sar8
           || op8 == Iop_CmpEQ8 || op8 == Iop_CmpNE8 || op8 == Iop_Not8);
   adj = ty == Ity_I8 ? 0 : (ty == Ity_I16 ? 1 : (ty == Ity_I32 ? 2 : 3));
   return adj + op8;
}

static const HChar* showCondCode(UInt code) {
   const HChar* ret;
   switch (code) {
      case 0: ret = "f"; break;
      case 1: ret = "un"; break;
      case 2: ret = "eq"; break;
      case 3: ret = "ueq"; break;
      case 4: ret = "olt"; break;
      case 5: ret = "ult"; break;
      case 6: ret = "ole"; break;
      case 7: ret = "ule"; break;
      case 8: ret = "sf"; break;
      case 9: ret = "ngle"; break;
      case 10: ret = "seq"; break;
      case 11: ret = "ngl"; break;
      case 12: ret = "lt"; break;
      case 13: ret = "nge"; break;
      case 14: ret = "le"; break;
      case 15: ret = "ngt"; break;
      default: vpanic("showCondCode"); break;
   }
   return ret;
}

static Bool dis_instr_CCondFmt ( UInt cins )
{
   IRTemp t0, t1, t2, t3, tmp5, tmp6;
   IRTemp ccIR = newTemp(Ity_I32);
   IRTemp ccMIPS = newTemp(Ity_I32);
   UInt FC = get_FC(cins);
   UInt fmt = get_fmt(cins);
   UInt fs = get_fs(cins);
   UInt ft = get_ft(cins);
   UInt cond = get_cond(cins);

   if (FC == 0x3) {  
      UInt fpc_cc = get_fpc_cc(cins);
      switch (fmt) {
         case 0x10: {  
            DIP("c.%s.s %d, f%d, f%d", showCondCode(cond), fpc_cc, fs, ft);
            if (fp_mode64) {
               t0 = newTemp(Ity_I32);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I32);

               tmp5 = newTemp(Ity_F64);
               tmp6 = newTemp(Ity_F64);

               assign(tmp5, unop(Iop_F32toF64, getLoFromF64(Ity_F64,
                                 getFReg(fs))));
               assign(tmp6, unop(Iop_F32toF64, getLoFromF64(Ity_F64,
                                 getFReg(ft))));

               assign(ccIR, binop(Iop_CmpF64, mkexpr(tmp5), mkexpr(tmp6)));
               putHI(mkWidenFrom32(mode64 ? Ity_I64: Ity_I32,
                                   mkexpr(ccIR), True));

               
               assign(ccMIPS, binop(Iop_Shl32, mkU32(1), unop(Iop_32to8,
                              binop(Iop_Or32, binop(Iop_And32, unop(Iop_Not32,
                              binop(Iop_Shr32, mkexpr(ccIR),mkU8(5))),mkU32(2)),
                              binop(Iop_And32, binop(Iop_Xor32, mkexpr(ccIR),
                              binop(Iop_Shr32, mkexpr(ccIR), mkU8(6))),
                              mkU32(1))))));
               putLO(mkWidenFrom32(mode64 ? Ity_I64: Ity_I32,
                                   mkexpr(ccMIPS), True));

               
               assign(t0, binop(Iop_And32, mkexpr(ccMIPS), mkU32(0x1)));
               
               assign(t1, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                                                 mkU8(0x1)), mkU32(0x1)));
               
               assign(t2, binop(Iop_And32, unop(Iop_Not32, binop(Iop_Shr32,
                                 mkexpr(ccMIPS), mkU8(0x2))),mkU32(0x1)));
               
               assign(t3, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                                                 mkU8(0x3)), mkU32(0x1)));
               switch (cond) {
                  case 0x0:
                     setFPUCondCode(mkU32(0), fpc_cc);
                     break;
                  case 0x1:
                     setFPUCondCode(mkexpr(t0), fpc_cc);
                     break;
                  case 0x2:
                     setFPUCondCode(mkexpr(t1), fpc_cc);
                     break;
                  case 0x3:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0x4:
                     setFPUCondCode(mkexpr(t3), fpc_cc);
                     break;
                  case 0x5:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                          fpc_cc);
                     break;
                  case 0x6:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0x7:
                     setFPUCondCode(mkexpr(t2), fpc_cc);
                     break;
                  case 0x8:
                     setFPUCondCode(mkU32(0), fpc_cc);
                     break;
                  case 0x9:
                     setFPUCondCode(mkexpr(t0), fpc_cc);
                     break;
                  case 0xA:
                     setFPUCondCode(mkexpr(t1), fpc_cc);
                     break;
                  case 0xB:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0xC:
                     setFPUCondCode(mkexpr(t3), fpc_cc);
                     break;
                  case 0xD:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                          fpc_cc);
                     break;
                  case 0xE:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0xF:
                     setFPUCondCode(mkexpr(t2), fpc_cc);
                     break;

                  default:
                     return False;
               }

            } else {
               t0 = newTemp(Ity_I32);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I32);

               assign(ccIR, binop(Iop_CmpF64, unop(Iop_F32toF64, getFReg(fs)),
                                  unop(Iop_F32toF64, getFReg(ft))));

               
               assign(ccMIPS, binop(Iop_Shl32, mkU32(1), unop(Iop_32to8,
                              binop(Iop_Or32, binop(Iop_And32, unop(Iop_Not32,
                              binop(Iop_Shr32, mkexpr(ccIR), mkU8(5))),
                                    mkU32(2)), binop(Iop_And32,
                              binop(Iop_Xor32, mkexpr(ccIR),
                              binop(Iop_Shr32, mkexpr(ccIR), mkU8(6))),
                              mkU32(1))))));
               
               assign(t0, binop(Iop_And32, mkexpr(ccMIPS), mkU32(0x1)));
               
               assign(t1, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                      mkU8(0x1)), mkU32(0x1)));
               
               assign(t2, binop(Iop_And32, unop(Iop_Not32, binop(Iop_Shr32,
                      mkexpr(ccMIPS), mkU8(0x2))), mkU32(0x1)));
               
               assign(t3, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                      mkU8(0x3)), mkU32(0x1)));

               switch (cond) {
                  case 0x0:
                     setFPUCondCode(mkU32(0), fpc_cc);
                     break;
                  case 0x1:
                     setFPUCondCode(mkexpr(t0), fpc_cc);
                     break;
                  case 0x2:
                     setFPUCondCode(mkexpr(t1), fpc_cc);
                     break;
                  case 0x3:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0x4:
                     setFPUCondCode(mkexpr(t3), fpc_cc);
                     break;
                  case 0x5:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                          fpc_cc);
                     break;
                  case 0x6:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0x7:
                     setFPUCondCode(mkexpr(t2), fpc_cc);
                     break;
                  case 0x8:
                     setFPUCondCode(mkU32(0), fpc_cc);
                     break;
                  case 0x9:
                     setFPUCondCode(mkexpr(t0), fpc_cc);
                     break;
                  case 0xA:
                     setFPUCondCode(mkexpr(t1), fpc_cc);
                     break;
                  case 0xB:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0xC:
                     setFPUCondCode(mkexpr(t3), fpc_cc);
                     break;
                  case 0xD:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                          fpc_cc);
                     break;
                  case 0xE:
                     setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                          fpc_cc);
                     break;
                  case 0xF:
                     setFPUCondCode(mkexpr(t2), fpc_cc);
                     break;

                  default:
                     return False;
               }
            }
         }
            break;

         case 0x11: {  
            DIP("c.%s.d %d, f%d, f%d", showCondCode(cond), fpc_cc, fs, ft);
            t0 = newTemp(Ity_I32);
            t1 = newTemp(Ity_I32);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I32);
            assign(ccIR, binop(Iop_CmpF64, getDReg(fs), getDReg(ft)));

            
            assign(ccMIPS, binop(Iop_Shl32, mkU32(1), unop(Iop_32to8,
                           binop(Iop_Or32, binop(Iop_And32, unop(Iop_Not32,
                           binop(Iop_Shr32, mkexpr(ccIR), mkU8(5))), mkU32(2)),
                           binop(Iop_And32, binop(Iop_Xor32, mkexpr(ccIR),
                           binop(Iop_Shr32, mkexpr(ccIR), mkU8(6))),
                           mkU32(1))))));

            
            assign(t0, binop(Iop_And32, mkexpr(ccMIPS), mkU32(0x1)));
            
            assign(t1, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                   mkU8(0x1)), mkU32(0x1)));
            
            assign(t2, binop(Iop_And32, unop(Iop_Not32, binop(Iop_Shr32,
                   mkexpr(ccMIPS), mkU8(0x2))), mkU32(0x1)));
            
            assign(t3, binop(Iop_And32, binop(Iop_Shr32, mkexpr(ccMIPS),
                   mkU8(0x3)), mkU32(0x1)));

            switch (cond) {
               case 0x0:
                  setFPUCondCode(mkU32(0), fpc_cc);
                  break;
               case 0x1:
                  setFPUCondCode(mkexpr(t0), fpc_cc);
                  break;
               case 0x2:
                  setFPUCondCode(mkexpr(t1), fpc_cc);
                  break;
               case 0x3:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                       fpc_cc);
                  break;
               case 0x4:
                  setFPUCondCode(mkexpr(t3), fpc_cc);
                  break;
               case 0x5:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                       fpc_cc);
                  break;
               case 0x6:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                       fpc_cc);
                  break;
               case 0x7:
                  setFPUCondCode(mkexpr(t2), fpc_cc);
                  break;
               case 0x8:
                  setFPUCondCode(mkU32(0), fpc_cc);
                  break;
               case 0x9:
                  setFPUCondCode(mkexpr(t0), fpc_cc);
                  break;
               case 0xA:
                  setFPUCondCode(mkexpr(t1), fpc_cc);
                  break;
               case 0xB:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t1)),
                                       fpc_cc);
                  break;
               case 0xC:
                  setFPUCondCode(mkexpr(t3), fpc_cc);
                  break;
               case 0xD:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t0), mkexpr(t3)),
                                       fpc_cc);
                  break;
               case 0xE:
                  setFPUCondCode(binop(Iop_Or32, mkexpr(t3), mkexpr(t1)),
                                       fpc_cc);
                  break;
               case 0xF:
                  setFPUCondCode(mkexpr(t2), fpc_cc);
                  break;
               default:
                  return False;
            }
         }
         break;

         default:
            return False;
      }
   } else {
      return False;
   }

   return True;
}

static Bool dis_instr_branch ( UInt theInstr, DisResult * dres,
                               Bool(*resteerOkFn) (void *, Addr64),
                               void *callback_opaque, IRStmt ** set )
{
   UInt jmpKind = 0;
   UChar opc1 = get_opcode(theInstr);
   UChar regRs = get_rs(theInstr);
   UChar regRt = get_rt(theInstr);
   UInt offset = get_imm(theInstr);
   Long sOffset = extend_s_16to64(offset);
   IRType ty = mode64 ? Ity_I64 : Ity_I32;
   IROp opSlt = mode64 ? Iop_CmpLT64S : Iop_CmpLT32S;

   IRTemp tmp = newTemp(ty);
   IRTemp tmpRs = newTemp(ty);
   IRTemp tmpRt = newTemp(ty);
   IRTemp tmpLt = newTemp(ty);
   IRTemp tmpReg0 = newTemp(ty);

   UChar regLnk = 31;   
   Addr64 addrTgt = 0;
   Addr64 cia = guest_PC_curr_instr;

   IRExpr *eConst0 = mkSzImm(ty, (UInt) 0);
   IRExpr *eNia = mkSzImm(ty, cia + 8);
   IRExpr *eCond = NULL;

   assign(tmpRs, getIReg(regRs));
   assign(tmpRt, getIReg(regRt));
   assign(tmpReg0, getIReg(0));

   eCond = binop(mkSzOp(ty, Iop_CmpNE8), mkexpr(tmpReg0), mkexpr(tmpReg0));

   switch (opc1) {
      case 0x01:
         switch (regRt) {
            case 0x00: {  
               addrTgt = mkSzAddr(ty, cia + 4 + (sOffset << 2));
               IRTemp tmpLtRes = newTemp(Ity_I1);

               assign(tmp, eConst0);
               assign(tmpLtRes, binop(opSlt, mkexpr(tmpRs), mkexpr(tmp)));
               assign(tmpLt, mode64 ? unop(Iop_1Uto64, mkexpr(tmpLtRes)) :
                      unop(Iop_1Uto32, mkexpr(tmpLtRes)));

               eCond = binop(mkSzOp(ty, Iop_CmpNE8), mkexpr(tmpLt),
                             mkexpr(tmpReg0));

               jmpKind = Ijk_Call;
               break;
            }

            case 0x01: {  
               IRTemp tmpLtRes = newTemp(Ity_I1);
               addrTgt = mkSzAddr(ty, cia + 4 + (sOffset << 2));

               assign(tmp, eConst0);
               assign(tmpLtRes, binop(opSlt, mkexpr(tmpRs), mkexpr(tmp)));
               assign(tmpLt, mode64 ? unop(Iop_1Uto64, mkexpr(tmpLtRes)) :
                                      unop(Iop_1Uto32, mkexpr(tmpLtRes)));
               eCond = binop(mkSzOp(ty, Iop_CmpEQ8), mkexpr(tmpLt),
                                    mkexpr(tmpReg0));

               jmpKind = Ijk_Call;
               break;
            }

            case 0x11: {  
               addrTgt = mkSzAddr(ty, cia + 4 + (sOffset << 2));
               putIReg(regLnk, eNia);
               IRTemp tmpLtRes = newTemp(Ity_I1);

               assign(tmpLtRes, binop(opSlt, mkexpr(tmpRs), eConst0));
               assign(tmpLt, mode64 ? unop(Iop_1Uto64, mkexpr(tmpLtRes)) :
                                      unop(Iop_1Uto32, mkexpr(tmpLtRes)));

               eCond = binop(mkSzOp(ty, Iop_CmpEQ8), mkexpr(tmpLt),
                                    mkexpr(tmpReg0));

               jmpKind = Ijk_Call;
               break;
            }

            case 0x10: {  
               IRTemp tmpLtRes = newTemp(Ity_I1);
               IRTemp tmpRes = newTemp(ty);

               addrTgt = mkSzAddr(ty, cia + 4 + (sOffset << 2));
               putIReg(regLnk, eNia);

               assign(tmp, eConst0);
               assign(tmpLtRes, binop(opSlt, mkexpr(tmpRs), mkexpr(tmp)));
               assign(tmpRes, mode64 ? unop(Iop_1Uto64,
                      mkexpr(tmpLtRes)) : unop(Iop_1Uto32, mkexpr(tmpLtRes)));
               eCond = binop(mkSzOp(ty, Iop_CmpNE8), mkexpr(tmpRes),
                                                     mkexpr(tmpReg0));

               jmpKind = Ijk_Call;
               break;
            }

         }
         break;
      default:
         return False;
      }
   *set = IRStmt_Exit(eCond, jmpKind, mkSzConst(ty, addrTgt), OFFB_PC);
   return True;
}

static Bool dis_instr_CVM ( UInt theInstr )
{
   UChar  opc2     = get_function(theInstr);
   UChar  opc1     = get_opcode(theInstr);
   UChar  regRs    = get_rs(theInstr);
   UChar  regRt    = get_rt(theInstr);
   UChar  regRd    = get_rd(theInstr);
   UInt   imm 	   = get_imm(theInstr);
   UChar  lenM1    = get_msb(theInstr);
   UChar  p        = get_lsb(theInstr);
   IRType ty       = mode64? Ity_I64 : Ity_I32;
   IRTemp tmp      = newTemp(ty);
   IRTemp tmpRs    = newTemp(ty);
   IRTemp tmpRt    = newTemp(ty);
   IRTemp t1       = newTemp(ty);
   UInt size;
   assign(tmpRs, getIReg(regRs));

   switch(opc1){
      case 0x1C:  {
         switch(opc2) { 
            case 0x03: {  
               DIP("dmul r%d, r%d, r%d", regRd, regRs, regRt);
               IRType t0 = newTemp(Ity_I128);
               assign(t0, binop(Iop_MullU64, getIReg(regRs), getIReg(regRt)));
               putIReg(regRd, unop(Iop_128to64, mkexpr(t0)));
               break;
            }

            case 0x32:  
               DIP("cins r%u, r%u, %d, %d\n", regRt, regRs, p, lenM1); 
               assign ( tmp  , binop(Iop_Shl64, mkexpr(tmpRs),
                                     mkU8(64-( lenM1+1 ))));
               assign ( tmpRt, binop(Iop_Shr64, mkexpr( tmp ),
                                     mkU8(64-(p+lenM1+1))));
               putIReg( regRt, mkexpr(tmpRt));
               break;

            case 0x33:  
               DIP("cins32 r%u, r%u, %d, %d\n", regRt, regRs, p+32, lenM1);
               assign ( tmp  , binop(Iop_Shl64, mkexpr(tmpRs),
                                     mkU8(64-( lenM1+1 ))));
               assign ( tmpRt, binop(Iop_Shr64, mkexpr( tmp ),
                                     mkU8(32-(p+lenM1+1))));
               putIReg( regRt, mkexpr(tmpRt));
               break;

            case 0x3A:  
               DIP("exts r%u, r%u, %d, %d\n", regRt, regRs, p, lenM1); 
               size = lenM1 + 1;  
               UChar lsAmt = 64 - (p + size);  
               UChar rsAmt = 64 - size;  
               tmp = newTemp(Ity_I64);
               assign(tmp, binop(Iop_Shl64, mkexpr(tmpRs), mkU8(lsAmt)));
               putIReg(regRt, binop(Iop_Sar64, mkexpr(tmp), mkU8(rsAmt)));
               break;

            case 0x3B:  
               DIP("exts32 r%u, r%u, %d, %d\n", regRt, regRs, p, lenM1); 
               assign ( tmp  , binop(Iop_Shl64, mkexpr(tmpRs),
                                     mkU8(32-(p+lenM1+1))));
               assign ( tmpRt, binop(Iop_Sar64, mkexpr(tmp),
                                     mkU8(64-(lenM1+1))) );
               putIReg( regRt, mkexpr(tmpRt));
               break;

            case 0x2B:  
               DIP("sne r%d, r%d, r%d", regRd,regRs, regRt);
               if (mode64)
                  putIReg(regRd, unop(Iop_1Uto64, binop(Iop_CmpNE64,
                                                        getIReg(regRs),
                                                        getIReg(regRt))));
               else
                  putIReg(regRd,unop(Iop_1Uto32, binop(Iop_CmpNE32,
                                                       getIReg(regRs),
                                                       getIReg(regRt))));
               break;

            case 0x2A:  
               DIP("seq r%d, r%d, %d", regRd, regRs, regRt);
               if (mode64)
                  putIReg(regRd, unop(Iop_1Uto64,
                                      binop(Iop_CmpEQ64, getIReg(regRs),
                                            getIReg(regRt))));
               else
                  putIReg(regRd, unop(Iop_1Uto32,
                                      binop(Iop_CmpEQ32, getIReg(regRs),
                                            getIReg(regRt))));
               break;

            case 0x2E:  
               DIP("seqi r%d, r%d, %d", regRt, regRs, imm);
               if (mode64)
                  putIReg(regRt, unop(Iop_1Uto64,
                                      binop(Iop_CmpEQ64, getIReg(regRs),
                                            mkU64(extend_s_10to64(imm)))));
               else
                  putIReg(regRt, unop(Iop_1Uto32,
                                      binop(Iop_CmpEQ32, getIReg(regRs),
                                            mkU32(extend_s_10to32(imm)))));
               break;

            case 0x2F:  
               DIP("snei r%d, r%d, %d", regRt, regRs, imm);
               if (mode64)
                  putIReg(regRt, unop(Iop_1Uto64,
                                   binop(Iop_CmpNE64,
                                         getIReg(regRs),
                                         mkU64(extend_s_10to64(imm)))));
               else
                  putIReg(regRt, unop(Iop_1Uto32,
                                   binop(Iop_CmpNE32,
                                         getIReg(regRs),
                                         mkU32(extend_s_10to32(imm)))));
               break;

            default:
               return False;
         }
         break;
      } 
      case 0x1F:{
         switch(opc2) {
            case 0x0A: {  
               switch (get_sa(theInstr)) {
                  case 0x00: {  
                     DIP("lwx r%d, r%d(r%d)", regRd, regRt, regRs);
                     LOADX_STORE_PATTERN;
                     putIReg(regRd, mkWidenFrom32(ty, load(Ity_I32, mkexpr(t1)),
                                                  True));
                     break;
                  }
                  case 0x08: {  
                     DIP("ldx r%d, r%d(r%d)", regRd, regRt, regRs);
                     vassert(mode64); 
                     LOADX_STORE_PATTERN;
                     putIReg(regRd, load(Ity_I64, mkexpr(t1)));
                     break;
                  }
                  case 0x06: {  
                     DIP("lbux r%d, r%d(r%d)", regRd, regRt, regRs);
                     LOADX_STORE_PATTERN;
                     if (mode64)
                        putIReg(regRd, unop(Iop_8Uto64, load(Ity_I8,
                                                             mkexpr(t1))));
                     else
                        putIReg(regRd, unop(Iop_8Uto32, load(Ity_I8,
                                                             mkexpr(t1))));
                     break;
                  }
                  case 0x10: {  
                     DIP("lwux r%d, r%d(r%d)", regRd, regRt, regRs);
                     LOADX_STORE_PATTERN; 
                     putIReg(regRd, mkWidenFrom32(ty, load(Ity_I32, mkexpr(t1)),
                                                  False));
                     break;
                  }
                  case 0x14: {  
                     DIP("lhux r%d, r%d(r%d)", regRd, regRt, regRs);
                     LOADX_STORE_PATTERN;
                     if (mode64)
                        putIReg(regRd,
                                unop(Iop_16Uto64, load(Ity_I16, mkexpr(t1))));
                     else
                        putIReg(regRd,
                                unop(Iop_16Uto32, load(Ity_I16, mkexpr(t1))));
                     break;
                  }
                  case 0x16: {  
                     DIP("lbx r%d, r%d(r%d)", regRd, regRs, regRt);
                     LOADX_STORE_PATTERN;
                     if (mode64)
                        putIReg(regRd,
                                unop(Iop_8Sto64, load(Ity_I8, mkexpr(t1))));
                     else
                        putIReg(regRd,
                                unop(Iop_8Sto32, load(Ity_I8, mkexpr(t1))));
                     break;
                  }
                  default:
                     vex_printf("\nUnhandled LX instruction opc3 = %x\n",
                                get_sa(theInstr));
                     return False;
               }
               break;
            }
         } 
         break;
      } 
      default:
         return False; 
   } 
   return True;
}


static UInt disDSPInstr_MIPS_WRK ( UInt cins )
{
   IRTemp t0, t1 = 0, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14,
          t15, t16, t17;
   UInt opcode, rs, rt, rd, sa, function, ac, ac_mfhilo, rddsp_mask,
        wrdsp_mask, dsp_imm, shift;

   opcode = get_opcode(cins);
   rs = get_rs(cins);
   rt = get_rt(cins);
   rd = get_rd(cins);
   sa = get_sa(cins);
   function = get_function(cins);
   ac = get_acNo(cins);
   ac_mfhilo = get_acNo_mfhilo(cins);
   rddsp_mask = get_rddspMask(cins);
   wrdsp_mask = get_wrdspMask(cins);
   dsp_imm = get_dspImm(cins);
   shift = get_shift(cins);

   switch (opcode) {
      case 0x00: {  
         switch (function) {
            case 0x10: {  
               DIP("mfhi ac%d r%d", ac_mfhilo, rd);
               putIReg(rd, unop(Iop_64HIto32, getAcc(ac_mfhilo)));
               break;
            }

            case 0x11: {  
               DIP("mthi ac%d r%d", ac, rs);
               t1 = newTemp(Ity_I32);
               assign(t1, unop(Iop_64to32, getAcc(ac)));
               putAcc(ac, binop(Iop_32HLto64, getIReg(rs), mkexpr(t1)));
               break;
            }

            case 0x12: {  
               DIP("mflo ac%d r%d", ac_mfhilo, rd);
               putIReg(rd, unop(Iop_64to32, getAcc(ac_mfhilo)));
               break;
            }

            case 0x13: {  
               DIP("mtlo ac%d r%d", ac, rs);
               t1 = newTemp(Ity_I32);
               assign(t1, unop(Iop_64HIto32, getAcc(ac)));
               putAcc(ac, binop(Iop_32HLto64, mkexpr(t1), getIReg(rs)));
               break;
            }

            case 0x18: {  
               DIP("mult ac%d r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               assign(t1, binop(Iop_MullS32, mkNarrowTo32(Ity_I32, getIReg(rs)),
                                mkNarrowTo32(Ity_I32, getIReg(rt))));
               putAcc(ac, mkexpr(t1));
               break;
            }

            case 0x19: {  
               DIP("multu ac%d r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               assign(t1, binop(Iop_MullU32, mkNarrowTo32(Ity_I32, getIReg(rs)),
                                             mkNarrowTo32(Ity_I32,
                                                          getIReg(rt))));
               putAcc(ac, mkexpr(t1));
            break;
            }
         }
         break;
      }
      case 0x1C: {  
         switch (function) {
            case 0x00: {  
               DIP("madd ac%d, r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               t2 = newTemp(Ity_I64);
               t3 = newTemp(Ity_I64);

               assign(t1, getAcc(ac));
               assign(t2, binop(Iop_MullS32, getIReg(rs), getIReg(rt)));
               assign(t3, binop(Iop_Add64, mkexpr(t1), mkexpr(t2)));

               putAcc(ac, mkexpr(t3));
               break;
            }
            case 0x01: {  
               DIP("maddu ac%d r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               t2 = newTemp(Ity_I64);
               t3 = newTemp(Ity_I64);

               assign(t1, getAcc(ac));
               assign(t2, binop(Iop_MullU32, getIReg(rs), getIReg(rt)));
               assign(t3, binop(Iop_Add64, mkexpr(t2), mkexpr(t1)));

               putAcc(ac, mkexpr(t3));
               break;
            }
            case 0x04: {  
               DIP("msub ac%d r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               t2 = newTemp(Ity_I64);
               t3 = newTemp(Ity_I64);

               assign(t1, getAcc(ac));
               assign(t2, binop(Iop_MullS32, getIReg(rs), getIReg(rt)));
               assign(t3, binop(Iop_Sub64, mkexpr(t1), mkexpr(t2)));

               putAcc(ac, mkexpr(t3));
               break;
            }
            case 0x05: {  
               DIP("msubu ac%d r%d, r%d", ac, rs, rt);
               t1 = newTemp(Ity_I64);
               t2 = newTemp(Ity_I64);
               t3 = newTemp(Ity_I64);

               assign(t1, getAcc(ac));
               assign(t2, binop(Iop_MullU32, getIReg(rs), getIReg(rt)));
               assign(t3, binop(Iop_Sub64, mkexpr(t1), mkexpr(t2)));

               putAcc(ac, mkexpr(t3));
               break;
            }
         }
         break;
      }
      case 0x1F: {  
         switch (function) {
            case 0x12: {  
               switch (sa) {
                  case 0x1: {  
                     DIP("absq_s.qb r%d, r%d", rd, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I8);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I8);
                     t8 = newTemp(Ity_I8);
                     t9 = newTemp(Ity_I1);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I8);
                     t12 = newTemp(Ity_I8);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I1);
                     t15 = newTemp(Ity_I8);
                     t16 = newTemp(Ity_I32);
                     t17 = newTemp(Ity_I32);

                     
                     
                     assign(t0, unop(Iop_16to8, unop(Iop_32to16, getIReg(rt))));
                     
                     assign(t1, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32, mkexpr(t0)),
                                      mkU32(0x00000080)));
                     
                     assign(t2, unop(Iop_32to1,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 getIReg(rt),
                                                 mkU32(0x00000080)),
                                           mkU8(0x7))));
                     
                     assign(t3, IRExpr_ITE(mkexpr(t1),
                                           mkU8(0x7F),
                                           IRExpr_ITE(mkexpr(t2),
                                                      binop(Iop_Add8,
                                                            unop(Iop_Not8,
                                                                 mkexpr(t0)),
                                                            mkU8(0x1)),
                                                      mkexpr(t0))));

                     
                     
                     assign(t4,
                            unop(Iop_16HIto8, unop(Iop_32to16, getIReg(rt))));
                     
                     assign(t5, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32, mkexpr(t4)),
                                      mkU32(0x00000080)));
                     
                     assign(t6, unop(Iop_32to1,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 getIReg(rt),
                                                 mkU32(0x00008000)),
                                           mkU8(15))));
                     
                     assign(t7, IRExpr_ITE(mkexpr(t5),
                                           mkU8(0x7F),
                                           IRExpr_ITE(mkexpr(t6),
                                                      binop(Iop_Add8,
                                                            unop(Iop_Not8,
                                                                 mkexpr(t4)),
                                                            mkU8(0x1)),
                                                      mkexpr(t4))));

                     
                     
                     assign(t8,
                            unop(Iop_16to8, unop(Iop_32HIto16, getIReg(rt))));
                     
                     assign(t9, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32, mkexpr(t8)),
                                      mkU32(0x00000080)));
                     
                     assign(t10, unop(Iop_32to1,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0x00800000)),
                                            mkU8(23))));
                     
                     assign(t11, IRExpr_ITE(mkexpr(t9),
                                            mkU8(0x7F),
                                            IRExpr_ITE(mkexpr(t10),
                                                       binop(Iop_Add8,
                                                             unop(Iop_Not8,
                                                                  mkexpr(t8)),
                                                             mkU8(0x1)),
                                                       mkexpr(t8))));

                     
                     
                     assign(t12,
                            unop(Iop_16HIto8, unop(Iop_32HIto16, getIReg(rt))));
                     
                     assign(t13, binop(Iop_CmpEQ32,
                                       unop(Iop_8Uto32, mkexpr(t12)),
                                       mkU32(0x00000080)));
                     
                     assign(t14, unop(Iop_32to1,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0x80000000)),
                                            mkU8(31))));
                     
                     assign(t15, IRExpr_ITE(mkexpr(t13),
                                            mkU8(0x7F),
                                            IRExpr_ITE(mkexpr(t14),
                                                       binop(Iop_Add8,
                                                             unop(Iop_Not8,
                                                                  mkexpr(t12)),
                                                             mkU8(0x1)),
                                                       mkexpr(t12))));

                     assign(t16,
                            binop(Iop_Or32,
                                  binop(Iop_Or32,
                                        binop(Iop_Or32,
                                              unop(Iop_1Sto32, mkexpr(t13)),
                                              unop(Iop_1Sto32, mkexpr(t9))),
                                        unop(Iop_1Sto32, mkexpr(t5))),
                                  unop(Iop_1Sto32, mkexpr(t1))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    mkexpr(t16),
                                                    mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000))));

                     
                     assign(t17,
                            binop(Iop_16HLto32,
                                  binop(Iop_8HLto16, mkexpr(t15), mkexpr(t11)),
                                  binop(Iop_8HLto16, mkexpr(t7), mkexpr(t3))));

                     putIReg(rd, mkexpr(t17));
                     break;
                  }
                  case 0x2: {  
                     DIP("repl.qb r%d, %d", rd, dsp_imm);
                     vassert(!mode64);

                     putIReg(rd, mkU32((dsp_imm << 24) | (dsp_imm << 16) |
                                       (dsp_imm << 8) | (dsp_imm)));
                     break;
                  }
                  case 0x3: {  
                     DIP("replv.qb r%d, r%d", rd, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I8);

                     assign(t0, unop(Iop_32to8,
                                binop(Iop_And32, getIReg(rt), mkU32(0xff))));
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16, mkexpr(t0), mkexpr(t0)),
                                   binop(Iop_8HLto16, mkexpr(t0), mkexpr(t0))));
                     break;
                  }
                  case 0x4: {  
                     DIP("precequ.ph.qbl r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0xff000000)),
                                             mkU8(1)),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x00ff0000)),
                                             mkU8(9))));
                     break;
                  }
                  case 0x5: {  
                     DIP("precequ.ph.qbr r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shl32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x0000ff00)),
                                             mkU8(15)),
                                       binop(Iop_Shl32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x000000ff)),
                                             mkU8(7))));
                     break;
                  }
                  case 0x6: {  
                     DIP("precequ.ph.qbla r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0xff000000)),
                                             mkU8(1)),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x0000ff00)),
                                             mkU8(1))));
                     break;
                  }
                  case 0x7: {  
                     DIP("precequ.ph.qbra r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shl32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x00ff0000)),
                                             mkU8(7)),
                                       binop(Iop_Shl32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x000000ff)),
                                             mkU8(7))));
                     break;
                  }
                  case 0x9: {  
                     DIP("absq_s.ph r%d, r%d", rd, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I16);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I16);
                     t4 = newTemp(Ity_I16);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I16);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     
                     assign(t0, unop(Iop_32to16, getIReg(rt)));
                     
                     assign(t1, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32, mkexpr(t0)),
                                      mkU32(0x00008000)));
                     
                     assign(t2, unop(Iop_32to1,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 getIReg(rt),
                                                 mkU32(0x00008000)),
                                           mkU8(15))));
                     
                     assign(t3, IRExpr_ITE(mkexpr(t1),
                                           mkU16(0x7FFF),
                                           IRExpr_ITE(mkexpr(t2),
                                                      binop(Iop_Add16,
                                                            unop(Iop_Not16,
                                                                 mkexpr(t0)),
                                                            mkU16(0x1)),
                                                      mkexpr(t0))));

                     
                     assign(t4, unop(Iop_32HIto16, getIReg(rt)));
                     
                     assign(t5, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32, mkexpr(t4)),
                                      mkU32(0x00008000)));
                     
                     assign(t6, unop(Iop_32to1,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 getIReg(rt),
                                                 mkU32(0x80000000)),
                                           mkU8(31))));
                     
                     assign(t7, IRExpr_ITE(mkexpr(t5),
                                           mkU16(0x7FFF),
                                           IRExpr_ITE(mkexpr(t6),
                                                      binop(Iop_Add16,
                                                            unop(Iop_Not16,
                                                                 mkexpr(t4)),
                                                            mkU16(0x1)),
                                                      mkexpr(t4))));
                     assign(t8, binop(Iop_Or32,
                                      unop(Iop_1Sto32, mkexpr(t5)),
                                      unop(Iop_1Sto32, mkexpr(t1))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    mkexpr(t8),
                                                    mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000))));

                     
                     assign(t9, binop(Iop_16HLto32, mkexpr(t7), mkexpr(t3)));

                     putIReg(rd, mkexpr(t9));
                     break;
                  }
                  case 0xA: {  
                     DIP("repl.ph r%d, %d", rd, dsp_imm);
                     vassert(!mode64);
                     UShort immediate = extend_s_10to16(dsp_imm);

                     putIReg(rd, mkU32(immediate << 16 | immediate));
                     break;
                  }
                  case 0xB: {  
                     DIP("replv.ph r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, getIReg(rt)),
                                       unop(Iop_32to16, getIReg(rt))));
                     break;
                  }
                  case 0xC: {  
                     DIP("preceq.w.phl r%d, r%d", rd, rt);
                     vassert(!mode64);
                     putIReg(rd, binop(Iop_And32,
                                       getIReg(rt),
                                       mkU32(0xffff0000)));
                     break;
                  }
                  case 0xD: {  
                     DIP("preceq.w.phr r%d, r%d", rd, rt);
                     vassert(!mode64);
                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, getIReg(rt)),
                                       mkU16(0x0)));
                     break;
                  }
                  case 0x11: {  
                     DIP("absq_s.w r%d, r%d", rd, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I1);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);

                     assign(t0,
                            binop(Iop_CmpEQ32, getIReg(rt), mkU32(0x80000000)));

                     putDSPControl(IRExpr_ITE(mkexpr(t0),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     assign(t1, binop(Iop_CmpLT32S, getIReg(rt), mkU32(0x0)));

                     assign(t2, IRExpr_ITE(mkexpr(t0),
                                           mkU32(0x7FFFFFFF),
                                           IRExpr_ITE(mkexpr(t1),
                                                      binop(Iop_Add32,
                                                            unop(Iop_Not32,
                                                                 getIReg(rt)),
                                                            mkU32(0x1)),
                                                      getIReg(rt))));
                     putIReg(rd, mkexpr(t2));
                     break;
                  }
                  case 0x1B: {  
                     DIP("bitrev r%d, r%d", rd, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_Or32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0xaaaaaaaa)),
                                            mkU8(0x1)),
                                      binop(Iop_Shl32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0x55555555)),
                                            mkU8(0x1))));
                     assign(t2, binop(Iop_Or32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t1),
                                                  mkU32(0xcccccccc)),
                                            mkU8(0x2)),
                                      binop(Iop_Shl32,
                                            binop(Iop_And32,
                                                  mkexpr(t1),
                                                  mkU32(0x33333333)),
                                            mkU8(0x2))));
                     assign(t3, binop(Iop_Or32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0xf0f0f0f0)),
                                            mkU8(0x4)),
                                      binop(Iop_Shl32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0x0f0f0f0f)),
                                            mkU8(0x4))));
                     assign(t4, binop(Iop_Or32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t3),
                                                  mkU32(0xff00ff00)),
                                            mkU8(0x8)),
                                      binop(Iop_Shl32,
                                            binop(Iop_And32,
                                                  mkexpr(t3),
                                                  mkU32(0x00ff00ff)),
                                            mkU8(0x8))));
                     assign(t5, binop(Iop_Or32,
                                      binop(Iop_Shr32,
                                            mkexpr(t4),
                                            mkU8(0x10)),
                                      binop(Iop_Shl32,
                                            mkexpr(t4),
                                            mkU8(0x10))));
                     putIReg(rd, binop(Iop_Shr32,
                                       mkexpr(t5),
                                       mkU8(16)));
                     break;
                  }
                  case 0x1C: {  
                     DIP("preceu.ph.qbl r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0xff000000)),
                                             mkU8(8)),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x00ff0000)),
                                             mkU8(16))));
                     break;
                  }
                  case 0x1E: {  
                     DIP("preceu.ph.qbla r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0xff000000)),
                                             mkU8(8)),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x0000ff00)),
                                             mkU8(8))));
                     break;
                  }
                  case 0x1D: {  
                     DIP("preceu.ph.qbr r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Shl32,
                                             binop(Iop_And32,
                                                   getIReg(rt),
                                                   mkU32(0x0000ff00)),
                                             mkU8(8)),
                                       binop(Iop_And32,
                                             getIReg(rt),
                                             mkU32(0x000000ff))));
                     break;
                  }
                  case 0x1F: {  
                     DIP("preceu.ph.qbra r%d, r%d", rd, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_And32,
                                             getIReg(rt),
                                             mkU32(0x00ff0000)),
                                       binop(Iop_And32,
                                             getIReg(rt),
                                             mkU32(0x000000ff))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x38: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("extr.w r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     if (0 == rs) {
                        assign(t1, mkexpr(t0));
                     } else {
                        assign(t1, binop(Iop_Sar64, mkexpr(t0), mkU8(rs)));
                     }
                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     if (0 == rs) {
                        assign(t8, mkU64(0x0ULL));
                     } else {
                        assign(t8, binop(Iop_And64,
                                         binop(Iop_Shr64,
                                               mkexpr(t0),
                                               mkU8(rs-1)),
                                         mkU64(0x1ULL)));
                     }
                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     if (0 == rs) {
                        putIReg(rt, unop(Iop_64to32, mkexpr(t0)));
                     } else {
                        putIReg(rt, unop(Iop_64to32, mkexpr(t1)));
                     }
                     break;
                  }
                  case 0x1: {  
                     DIP("extrv.w r%d, ac%d, r%d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);
                     t15 = newTemp(Ity_I8);

                     assign(t15, unop(Iop_32to8,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0x1f))));
                     assign(t0, getAcc(ac));
                     assign(t1, binop(Iop_Sar64, mkexpr(t0), mkexpr(t15)));
                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        unop(Iop_8Uto32,
                                                             mkexpr(t15)),
                                                        mkU32(0)),
                                                  unop(Iop_64to32, mkexpr(t0)),
                                                  unop(Iop_64to32, mkexpr(t1))));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     assign(t8,
                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                             unop(Iop_8Uto32,
                                                  mkexpr(t15)),
                                             mkU32(0)),
                                       mkU64(0x0ULL),
                                       binop(Iop_And64,
                                             binop(Iop_Shr64,
                                                   mkexpr(t0),
                                                   unop(Iop_32to8,
                                                        binop(Iop_Sub32,
                                                              unop(Iop_8Uto32,
                                                                   mkexpr(t15)),
                                                                   mkU32(1)))),
                                             mkU64(0x1ULL))));

                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     break;
                  }
                  case 0x2: {  
                     DIP("extp r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     
                     assign(t1, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));

                     assign(t2, binop(Iop_CmpLT32U, mkexpr(t1), mkU32(rs)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    binop(Iop_And32,
                                                          getDSPControl(),
                                                          mkU32(0xffffbfff)),
                                                    mkU32(0x4000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xffffbfff))));

                     assign(t3, binop(Iop_CmpLE32U, mkexpr(t1), mkU32(31)));

                     assign(t4,
                           IRExpr_ITE(mkexpr(t3),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkexpr(t1), mkU32(rs))),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkU32(63), mkexpr(t1)))));

                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Shr64,
                                                 mkexpr(t0), mkexpr(t4)),
                                           binop(Iop_Shl64,
                                                 mkexpr(t0), mkexpr(t4))));

                     
                     assign(t6,
                            IRExpr_ITE(mkexpr(t3),
                                       unop(Iop_Not64,
                                            binop(Iop_Shl64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  mkU8(rs+1))),
                                       unop(Iop_Not64,
                                            binop(Iop_Shr64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  mkU8(rs+1)))));

                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           unop(Iop_64to32,
                                                binop(Iop_And64,
                                                      mkexpr(t5),
                                                      mkexpr(t6))),
                                           binop(Iop_Shr32,
                                                 unop(Iop_64HIto32,
                                                      binop(Iop_And64,
                                                            mkexpr(t5),
                                                            mkexpr(t6))),
                                                 mkU8(31-rs))));

                     putIReg(rt, mkexpr(t7));
                     break;
                  }
                  case 0x3: {  
                     DIP("extpv r%d, ac%d, r%d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t8, binop(Iop_And32, getIReg(rs), mkU32(0x1f)));
                     assign(t0, getAcc(ac));
                     
                     assign(t1, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));

                     assign(t2, binop(Iop_CmpLT32U, mkexpr(t1), mkexpr(t8)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    binop(Iop_And32,
                                                          getDSPControl(),
                                                          mkU32(0xffffbfff)),
                                                    mkU32(0x4000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xffffbfff))));

                     assign(t3, binop(Iop_CmpLE32U, mkexpr(t1), mkU32(31)));

                     assign(t4,
                           IRExpr_ITE(mkexpr(t3),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkexpr(t1), mkexpr(t8))),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkU32(63), mkexpr(t1)))));

                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Shr64,
                                                 mkexpr(t0), mkexpr(t4)),
                                           binop(Iop_Shl64,
                                                 mkexpr(t0), mkexpr(t4))));

                     
                     assign(t6,
                            IRExpr_ITE(mkexpr(t3),
                                       unop(Iop_Not64,
                                            binop(Iop_Shl64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  unop(Iop_32to8,
                                                       binop(Iop_Add32,
                                                             mkexpr(t8),
                                                             mkU32(1))))),
                                       unop(Iop_Not64,
                                            binop(Iop_Shr64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  unop(Iop_32to8,
                                                       binop(Iop_Add32,
                                                             mkexpr(t8),
                                                             mkU32(1)))))));

                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           unop(Iop_64to32,
                                                binop(Iop_And64,
                                                      mkexpr(t5),
                                                      mkexpr(t6))),
                                           binop(Iop_Shr32,
                                                 unop(Iop_64HIto32,
                                                      binop(Iop_And64,
                                                            mkexpr(t5),
                                                            mkexpr(t6))),
                                                 unop(Iop_32to8,
                                                      binop(Iop_Sub32,
                                                            mkU32(31),
                                                            mkexpr(t8))))));

                     putIReg(rt, mkexpr(t7));
                     break;
                  }
                  case 0x4: {  
                     DIP("extr_r.w r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);
                     t15 = newTemp(Ity_I64);
                     t16 = newTemp(Ity_I1);

                     assign(t0, getAcc(ac));
                     assign(t16, binop(Iop_CmpEQ32,
                                       mkU32(rs),
                                       mkU32(0)));
                     assign(t1, IRExpr_ITE(mkexpr(t16),
                                           mkexpr(t0),
                                           binop(Iop_Sar64,
                                                 mkexpr(t0),
                                                 mkU8(rs))));
                     assign(t15, binop(Iop_Shr64,
                                       mkexpr(t0),
                                       unop(Iop_32to8,
                                            binop(Iop_Sub32,
                                                  binop(Iop_And32,
                                                        mkU32(rs),
                                                        mkU32(0x1f)),
                                                  mkU32(1)))));

                     assign(t8,
                            IRExpr_ITE(mkexpr(t16),
                                       mkU64(0x0ULL),
                                       binop(Iop_And64,
                                             mkexpr(t15),
                                             mkU64(0x0000000000000001ULL))));
                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));
                     putIReg(rt, unop(Iop_64to32, mkexpr(t9)));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     break;
                  }
                  case 0x5: {  
                     DIP("extrv_r.w r%d, ac%d, r%d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);
                     t15 = newTemp(Ity_I8);

                     assign(t15, unop(Iop_32to8,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0x1f))));
                     assign(t0, getAcc(ac));
                     assign(t1, binop(Iop_Sar64, mkexpr(t0), mkexpr(t15)));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     assign(t8,
                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                             unop(Iop_8Uto32,
                                                  mkexpr(t15)),
                                             mkU32(0)),
                                       mkU64(0x0ULL),
                                       binop(Iop_And64,
                                             binop(Iop_Shr64,
                                                   mkexpr(t0),
                                                   unop(Iop_32to8,
                                                        binop(Iop_Sub32,
                                                              unop(Iop_8Uto32,
                                                                   mkexpr(t15)),
                                                                   mkU32(1)))),
                                             mkU64(0x1ULL))));

                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));
                     
                     putIReg(rt, unop(Iop_64to32, mkexpr(t9)));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     break;
                  }
                  case 0x6: {  
                     DIP("extr_rs.w r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);
                     t16 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     if (0 == rs) {
                        assign(t1, mkexpr(t0));
                     } else {
                        assign(t1, binop(Iop_Sar64, mkexpr(t0), mkU8(rs)));
                     }

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     if (0 == rs) {
                        assign(t8, mkU64(0x0ULL));
                     } else {
                        assign(t8, binop(Iop_And64,
                                         binop(Iop_Shr64,
                                               mkexpr(t0),
                                               mkU8(rs-1)),
                                         mkU64(0x1ULL)));
                     }

                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     assign(t16, binop(Iop_And32,
                                       unop(Iop_64HIto32,
                                            mkexpr(t9)),
                                       mkU32(0x80000000)));
                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t14),
                                                  mkU32(0)),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             mkexpr(t16),
                                                             mkU32(0)),
                                                       mkU32(0x7fffffff),
                                                       mkU32(0x80000000)),
                                            unop(Iop_64to32, mkexpr(t9))));
                     break;
                  }
                  case 0x7: {  
                     DIP("extrv_rs.w r%d, ac%d, r%d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I32);
                     t15 = newTemp(Ity_I32);
                     t16 = newTemp(Ity_I32);
                     t17 = newTemp(Ity_I1);

                     assign(t15, binop(Iop_And32,
                                       getIReg(rs),
                                       mkU32(0x1f)));
                     assign(t17, binop(Iop_CmpEQ32,
                                       mkexpr(t15),
                                       mkU32(0)));
                     assign(t0, getAcc(ac));
                     assign(t1, IRExpr_ITE(mkexpr(t17),
                                           mkexpr(t0),
                                           binop(Iop_Sar64,
                                                 mkexpr(t0),
                                                 unop(Iop_32to8,
                                                      mkexpr(t15)))));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t1)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t3)),
                                            unop(Iop_1Sto32, mkexpr(t4))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t5)),
                                            unop(Iop_1Sto32, mkexpr(t6)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t7),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     assign(t8,
                            IRExpr_ITE(mkexpr(t17),
                                       mkU64(0x0ULL),
                                       binop(Iop_And64,
                                             binop(Iop_Shr64,
                                                   mkexpr(t0),
                                                   unop(Iop_32to8,
                                                        binop(Iop_Sub32,
                                                              mkexpr(t15),
                                                              mkU32(1)))),
                                             mkU64(0x1ULL))));

                     assign(t9, binop(Iop_Add64, mkexpr(t1), mkexpr(t8)));

                     
                     assign(t10, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0)));
                     assign(t11, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0)));

                     assign(t12, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32,
                                           mkexpr(t9)),
                                      mkU32(0xffffffff)));
                     assign(t13, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32,
                                                 mkexpr(t9)),
                                            mkU32(0x80000000)),
                                      mkU32(0x80000000)));

                     assign(t14, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t10)),
                                            unop(Iop_1Sto32, mkexpr(t11))),
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32, mkexpr(t12)),
                                            unop(Iop_1Sto32, mkexpr(t13)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t14),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));

                     assign(t16, binop(Iop_And32,
                                       unop(Iop_64HIto32,
                                            mkexpr(t9)),
                                       mkU32(0x80000000)));
                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t14),
                                                  mkU32(0)),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             mkexpr(t16),
                                                             mkU32(0)),
                                                       mkU32(0x7fffffff),
                                                       mkU32(0x80000000)),
                                            unop(Iop_64to32, mkexpr(t9))));
                     break;
                  }
                  case 0xA: {  
                     DIP("extpdp r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     
                     assign(t1, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));

                     assign(t2, binop(Iop_CmpLT32U, mkexpr(t1), mkU32(rs)));

                     assign(t8, binop(Iop_Or32,
                                      binop(Iop_And32,
                                            getDSPControl(),
                                            mkU32(0xffffbfc0)),
                                      binop(Iop_And32,
                                            binop(Iop_Sub32,
                                                  binop(Iop_And32,
                                                        getDSPControl(),
                                                        mkU32(0x3f)),
                                                  mkU32(rs+1)),
                                            mkU32(0x3f))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                     binop(Iop_And32,
                                                           getDSPControl(),
                                                           mkU32(0xffffbfff)),
                                                     mkU32(0x4000)),
                                              mkexpr(t8)));

                     assign(t3, binop(Iop_CmpLE32U, mkexpr(t1), mkU32(31)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t3),
                                       unop(Iop_32to8,
                                            binop(Iop_Sub32,
                                                  mkexpr(t1), mkU32(rs))),
                                       unop(Iop_32to8,
                                            binop(Iop_Sub32,
                                                  mkU32(63), mkexpr(t1)))));

                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Shr64,
                                                 mkexpr(t0), mkexpr(t4)),
                                           binop(Iop_Shl64,
                                                 mkexpr(t0), mkexpr(t4))));

                     
                     assign(t6,
                            IRExpr_ITE(mkexpr(t3),
                                       unop(Iop_Not64,
                                            binop(Iop_Shl64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  mkU8(rs+1))),
                                       unop(Iop_Not64,
                                            binop(Iop_Shr64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  mkU8(rs+1)))));

                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           unop(Iop_64to32,
                                                binop(Iop_And64,
                                                      mkexpr(t5),
                                                      mkexpr(t6))),
                                           binop(Iop_Shr32,
                                                 unop(Iop_64HIto32,
                                                      binop(Iop_And64,
                                                            mkexpr(t5),
                                                            mkexpr(t6))),
                                                 mkU8(31-rs))));

                     putIReg(rt, mkexpr(t7));
                     break;
                  }
                  case 0xB: {  
                     DIP("extpdpv r%d, ac%d, r%d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     assign(t8, binop(Iop_And32, getIReg(rs), mkU32(0x1f)));
                     assign(t0, getAcc(ac));
                     
                     assign(t1, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));

                     assign(t2, binop(Iop_CmpLT32U, mkexpr(t1), mkexpr(t8)));

                     assign(t9, binop(Iop_Or32,
                                      binop(Iop_And32,
                                            getDSPControl(),
                                            mkU32(0xffffbfc0)),
                                      binop(Iop_And32,
                                            binop(Iop_Sub32,
                                                  binop(Iop_And32,
                                                        getDSPControl(),
                                                        mkU32(0x3f)),
                                                  binop(Iop_Add32,
                                                        mkexpr(t8),
                                                        mkU32(0x1))),
                                            mkU32(0x3f))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    binop(Iop_And32,
                                                          getDSPControl(),
                                                          mkU32(0xffffbfff)),
                                                    mkU32(0x4000)),
                                              mkexpr(t9)));

                     assign(t3, binop(Iop_CmpLE32U, mkexpr(t1), mkU32(31)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t3),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkexpr(t1), mkexpr(t8))),
                                      unop(Iop_32to8,
                                           binop(Iop_Sub32,
                                                 mkU32(63), mkexpr(t1)))));

                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Shr64,
                                                 mkexpr(t0), mkexpr(t4)),
                                           binop(Iop_Shl64,
                                                 mkexpr(t0), mkexpr(t4))));

                     
                     assign(t6,
                            IRExpr_ITE(mkexpr(t3),
                                       unop(Iop_Not64,
                                            binop(Iop_Shl64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  unop(Iop_32to8,
                                                       binop(Iop_Add32,
                                                             mkexpr(t8),
                                                             mkU32(1))))),
                                       unop(Iop_Not64,
                                            binop(Iop_Shr64,
                                                  mkU64(0xffffffffffffffffULL),
                                                  unop(Iop_32to8,
                                                       binop(Iop_Add32,
                                                             mkexpr(t8),
                                                             mkU32(1)))))));

                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           unop(Iop_64to32,
                                                binop(Iop_And64,
                                                      mkexpr(t5),
                                                      mkexpr(t6))),
                                           binop(Iop_Shr32,
                                                 unop(Iop_64HIto32,
                                                      binop(Iop_And64,
                                                            mkexpr(t5),
                                                            mkexpr(t6))),
                                                 unop(Iop_32to8,
                                                      binop(Iop_Sub32,
                                                            mkU32(31),
                                                            mkexpr(t8))))));

                     putIReg(rt, mkexpr(t7));
                     break;
                  }
                  case 0xE: {  
                     DIP("extr_s.h r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I64);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Sar64, mkexpr(t0), mkU8(rs)));

                     assign(t2, binop(Iop_Or32,
                                      getDSPControl(), mkU32(0x00800000)));

                     assign(t9, binop(Iop_And32,
                                      unop(Iop_64to32,
                                           mkexpr(t1)),
                                      mkU32(0x80000000)));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t9),
                                                    binop(Iop_And32,
                                                          unop(Iop_64HIto32,
                                                               mkexpr(t0)),
                                                          mkU32(0x80000000))),
                                              mkexpr(t2),
                                              getDSPControl()));

                     assign(t3, binop(Iop_Sub64,
                                      mkexpr(t1),
                                      mkU64(0x0000000000007fffULL)));
                     assign(t4, binop(Iop_And32,
                                       binop(Iop_Or32,
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       binop(Iop_And32,
                                                             unop(Iop_64HIto32,
                                                                  mkexpr(t3)),
                                                             mkU32(0x7fffffff)))),
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       unop(Iop_64to32,
                                                            mkexpr(t3))))),
                                       unop(Iop_1Sto32,
                                            binop(Iop_CmpEQ32,
                                                  binop(Iop_And32,
                                                        unop(Iop_64HIto32,
                                                                  mkexpr(t3)),
                                                             mkU32(0x80000000)),
                                                  mkU32(0)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t4)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     assign(t6, binop(Iop_Sub64,
                                       mkU64(0xffffffffffff8000ULL),
                                       mkexpr(t1)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       binop(Iop_And32,
                                                             unop(Iop_64HIto32,
                                                                  mkexpr(t6)),
                                                             mkU32(0x7fffffff)))),
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       unop(Iop_64to32,
                                                            mkexpr(t6))))),
                                      unop(Iop_1Sto32,
                                            binop(Iop_CmpEQ32,
                                                  binop(Iop_And32,
                                                        unop(Iop_64HIto32,
                                                                  mkexpr(t6)),
                                                             mkU32(0x80000000)),
                                                  mkU32(0)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t7)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t4)),
                                            mkU32(0x00007fff),
                                            IRExpr_ITE(binop(Iop_CmpNE32,
                                                             mkU32(0),
                                                             mkexpr(t7)),
                                                       mkU32(0xffff8000),
                                                       unop(Iop_64to32,
                                                            mkexpr(t1)))));
                     break;
                  }
                  case 0xF: {  
                     DIP("extrv_s.h r%d, ac%d, %d", rt, ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I64);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Sar64,
                                      mkexpr(t0),
                                      unop(Iop_32to8,
                                           binop(Iop_And32,
                                                 getIReg(rs),
                                                 mkU32(0x1f)))));

                     assign(t2, binop(Iop_Or32,
                                      getDSPControl(), mkU32(0x00800000)));

                     assign(t9, binop(Iop_And32,
                                      unop(Iop_64to32,
                                           mkexpr(t1)),
                                      mkU32(0x80000000)));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t9),
                                                    binop(Iop_And32,
                                                          unop(Iop_64HIto32,
                                                               mkexpr(t0)),
                                                          mkU32(0x80000000))),
                                              mkexpr(t2),
                                              getDSPControl()));

                     assign(t3, binop(Iop_Sub64,
                                      mkexpr(t1),
                                      mkU64(0x0000000000007fffULL)));
                     assign(t4, binop(Iop_And32,
                                       binop(Iop_Or32,
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       binop(Iop_And32,
                                                             unop(Iop_64HIto32,
                                                                  mkexpr(t3)),
                                                             mkU32(0x7fffffff)))),
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       unop(Iop_64to32,
                                                            mkexpr(t3))))),
                                       unop(Iop_1Sto32,
                                            binop(Iop_CmpEQ32,
                                                  binop(Iop_And32,
                                                        unop(Iop_64HIto32,
                                                                  mkexpr(t3)),
                                                             mkU32(0x80000000)),
                                                  mkU32(0)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t4)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     assign(t6, binop(Iop_Sub64,
                                       mkU64(0xffffffffffff8000ULL),
                                       mkexpr(t1)));
                     assign(t7, binop(Iop_And32,
                                      binop(Iop_Or32,
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       binop(Iop_And32,
                                                             unop(Iop_64HIto32,
                                                                  mkexpr(t6)),
                                                             mkU32(0x7fffffff)))),
                                            unop(Iop_1Sto32,
                                                 binop(Iop_CmpNE32,
                                                       mkU32(0),
                                                       unop(Iop_64to32,
                                                            mkexpr(t6))))),
                                      unop(Iop_1Sto32,
                                            binop(Iop_CmpEQ32,
                                                  binop(Iop_And32,
                                                        unop(Iop_64HIto32,
                                                                  mkexpr(t6)),
                                                             mkU32(0x80000000)),
                                                  mkU32(0)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t7)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00800000)),
                                              getDSPControl()));
                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkU32(0),
                                                    mkexpr(t4)),
                                            mkU32(0x00007fff),
                                            IRExpr_ITE(binop(Iop_CmpNE32,
                                                             mkU32(0),
                                                             mkexpr(t7)),
                                                       mkU32(0xffff8000),
                                                       unop(Iop_64to32,
                                                            mkexpr(t1)))));
                     break;
                  }
                  case 0x12: {  
                     DIP("rddsp r%d, mask 0x%x", rd, rddsp_mask);
                     vassert(!mode64);

                     putIReg(rd, mkU32(0x0));

                     if ((rddsp_mask & 0x1) == 0x1) {
                        
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0x0000003F))));
                     }

                     if ((rddsp_mask & 0x2) == 0x2) {
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0x00001F80))));
                     }

                     if ((rddsp_mask & 0x4) == 0x4) {
                        
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0x00002000))));
                     }

                     if ((rddsp_mask & 0x8) == 0x8) {
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0x00FF0000))));
                     }

                     if ((rddsp_mask & 0x10) == 0x10) {
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0xFF000000))));
                     }

                     if ((rddsp_mask & 0x20) == 0x20) {
                        
                        putIReg(rd, binop(Iop_Or32,
                                          getIReg(rd),
                                          binop(Iop_And32,
                                                getDSPControl(),
                                                mkU32(0x00004000))));
                     }

                     if ((rddsp_mask & 0x3f) == 0x3f) {
                        
                        putIReg(rd, getDSPControl());
                     }
                     break;
                  }
                  case 0x13: {  
                     DIP("wrdsp r%d, mask 0x%x", rs, wrdsp_mask);
                     vassert(!mode64);

                     if ((wrdsp_mask & 0x3f) == 0x3f) {
                        putDSPControl(mode64 ?
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0xffff7fbf)) :
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0x0fff7fbf)));
                     } else {
                        if ((wrdsp_mask & 0x1) == 0x1) {
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0xFFFF7F40)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mkU32(0x0000003F))));
                        }

                        if ((wrdsp_mask & 0x2) == 0x2) {
                           
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0xFFFFE03F)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mkU32(0x00001F80))));
                        }

                        if ((wrdsp_mask & 0x4) == 0x4) {
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0xFFFF5FBF)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mkU32(0x00002000))));
                        }

                        if ((wrdsp_mask & 0x8) == 0x8) {
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0xFF007FBF)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mkU32(0x00FF0000))));
                        }

                        if ((wrdsp_mask & 0x10) == 0x10) {
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0x00FF7FBF)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mode64 ? mkU32(0xFF000000)
                                                            : mkU32(0x0F000000))
                                               )
                                        );
                        }

                        if ((wrdsp_mask & 0x20) == 0x20) {
                           putDSPControl(binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     getDSPControl(),
                                                     mkU32(0xFFFF3FBF)),
                                               binop(Iop_And32,
                                                     getIReg(rs),
                                                     mkU32(0x00004000))));
                        }
                     }
                     break;
                  }
                  case 0x1A: {  
                     DIP("shilo ac%d, %d", ac, shift);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));

                     putAcc(ac, mkexpr(t0));

                     if (0x20 == (shift & 0x3f)) {
                        putAcc(ac, binop(Iop_32HLto64,
                                         unop(Iop_64to32, mkexpr(t0)),
                                         mkU32(0x0)));
                     } else if (0x20 == (shift & 0x20)) {
                        assign(t1, binop(Iop_Shl64,
                                         mkexpr(t0),
                                         unop(Iop_32to8,
                                              binop(Iop_Add32,
                                                    unop(Iop_Not32,
                                                         mkU32(shift)),
                                                    mkU32(0x1)))));

                        putAcc(ac, mkexpr(t1));
                     } else {
                        assign(t1, binop(Iop_Shr64, mkexpr(t0), mkU8(shift)));

                        putAcc(ac, mkexpr(t1));
                     }
                     break;
                  }
                  case 0x1B: {  
                     DIP("shilov ac%d, r%d", ac, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I64);
                     t4 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));
                     assign(t1, binop(Iop_And32, getIReg(rs), mkU32(0x3f)));
                     assign(t2, binop(Iop_CmpEQ32, mkexpr(t1), mkU32(0x20)));
                     assign(t3, binop(Iop_Shl64,
                                      mkexpr(t0),
                                      unop(Iop_32to8,
                                           binop(Iop_Add32,
                                                 unop(Iop_Not32,
                                                      mkexpr(t1)),
                                                 mkU32(0x1)))));
                     assign(t4, binop(Iop_Shr64,
                                      mkexpr(t0),
                                      unop(Iop_32to8,
                                           mkexpr(t1))));

                     putAcc(ac,
                            IRExpr_ITE(mkexpr(t2),
                                       binop(Iop_32HLto64,
                                             unop(Iop_64to32, mkexpr(t0)),
                                             mkU32(0x0)),
                                       IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        binop(Iop_And32,
                                                              mkexpr(t1),
                                                              mkU32(0x20)),
                                                        mkU32(0x20)),
                                                  mkexpr(t3),
                                                  mkexpr(t4))));
                     break;
                  }
                  case 0x1F: {  
                     DIP("mthlip r%d, ac%d", rs, ac);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);

                     assign(t0, getAcc(ac));
                     putAcc(ac, binop(Iop_32HLto64,
                                      unop(Iop_64to32, mkexpr(t0)),
                                      getIReg(rs)));
                     assign(t1, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpLE32U,
                                                    mkU32(32),
                                                    mkexpr(t1)),
                                              binop(Iop_Or32,
                                                    binop(Iop_Sub32,
                                                          mkexpr(t1),
                                                          mkU32(32)),
                                                   binop(Iop_And32,
                                                         getDSPControl(),
                                                         mkU32(0xffffffc0))),
                                              binop(Iop_Or32,
                                                    binop(Iop_Add32,
                                                          mkexpr(t1),
                                                          mkU32(32)),
                                                    binop(Iop_And32,
                                                          getDSPControl(),
                                                          mkU32(0xffffffc0)))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0xA: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("lwx r%d, r%d(r%d)", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Add32, getIReg(rt), getIReg(rs)));

                     putIReg(rd, load(Ity_I32, mkexpr(t0)));
                     break;
                  }
                  case 0x4: {  
                     DIP("lhx r%d, r%d(r%d)", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Add32, getIReg(rt), getIReg(rs)));

                     putIReg(rd, unop(Iop_16Sto32, load(Ity_I16, mkexpr(t0))));
                     break;
                  }
                  case 0x6: {  
                     DIP("lbux r%d, r%d(r%d)", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Add32, getIReg(rt), getIReg(rs)));

                     putIReg(rd, unop(Iop_8Uto32, load(Ity_I8, mkexpr(t0))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0xC: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("insv r%d, r%d", rt, rs);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));
                     
                     assign(t1, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            getDSPControl(),
                                            mkU32(0x1f80)),
                                      mkU8(7)));

                     assign(t2, unop(Iop_32to8,
                                     binop(Iop_Add32,
                                           mkexpr(t1),
                                           mkexpr(t0))));

                     
                     assign(t6, binop(Iop_Shl32,
                                      binop(Iop_Shr32,
                                            getIReg(rt),
                                            mkexpr(t2)),
                                      mkexpr(t2)));

                     assign(t3, unop(Iop_32to8,
                                     binop(Iop_Sub32,
                                           mkU32(32),
                                           mkexpr(t0))));
                     
                     assign(t7, binop(Iop_Shr32,
                                      binop(Iop_Shl32,
                                            getIReg(rt),
                                            mkexpr(t3)),
                                      mkexpr(t3)));

                     assign(t8, binop(Iop_Shl32,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            unop(Iop_Not32,
                                                 binop(Iop_Shl32,
                                                       mkU32(0xffffffff),
                                                       unop(Iop_32to8,
                                                            mkexpr(t1))))),
                                      unop(Iop_32to8,
                                           mkexpr(t0))));

                     putIReg(rt, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  mkexpr(t0),
                                                  mkU32(0)),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             mkexpr(t1),
                                                             mkU32(32)),
                                                       getIReg(rs),
                                                       binop(Iop_Or32,
                                                             mkexpr(t6),
                                                             mkexpr(t8))),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             unop(Iop_8Uto32,
                                                                  mkexpr(t2)),
                                                             mkU32(32)),
                                                       binop(Iop_Or32,
                                                             mkexpr(t7),
                                                             mkexpr(t8)),
                                                       binop(Iop_Or32,
                                                             binop(Iop_Or32,
                                                                   mkexpr(t6),
                                                                   mkexpr(t7)),
                                                             mkexpr(t8)))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x10: {  
               switch(sa) {
                  case 0x00: {  
                     DIP("addu.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I32);

                     
                     assign(t0,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t2,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t3, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t2),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t4,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t5, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t4),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t6,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t7, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t6),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     assign(t8,
                            binop(Iop_Or32,
                                  binop(Iop_Or32,
                                        binop(Iop_Or32,
                                              unop(Iop_1Sto32, mkexpr(t7)),
                                              unop(Iop_1Sto32,  mkexpr(t5))),
                                        unop(Iop_1Sto32, mkexpr(t3))),
                                  unop(Iop_1Sto32, mkexpr(t1))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    mkexpr(t8),
                                                    mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       binop(Iop_8HLto16,
                                             unop(Iop_32to8, mkexpr(t6)),
                                             unop(Iop_32to8, mkexpr(t4))),
                                       binop(Iop_8HLto16,
                                             unop(Iop_32to8, mkexpr(t2)),
                                             unop(Iop_32to8, mkexpr(t0)))));
                     break;
                  }
                  case 0x1: {  
                     DIP("subu.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I32);

                     
                     assign(t0,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t2,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t3, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t2),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t4,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t5, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t4),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     
                     assign(t6,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t7, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t6),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));

                     assign(t8, binop(Iop_Or32,
                                      binop(Iop_Or32,
                                            binop(Iop_Or32,
                                                  unop(Iop_1Sto32, mkexpr(t7)),
                                                  unop(Iop_1Sto32, mkexpr(t5))),
                                            unop(Iop_1Sto32, mkexpr(t3))),
                                      unop(Iop_1Sto32, mkexpr(t1))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                     mkexpr(t8),
                                                     mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       binop(Iop_8HLto16,
                                             unop(Iop_32to8, mkexpr(t6)),
                                             unop(Iop_32to8, mkexpr(t4))),
                                       binop(Iop_8HLto16,
                                             unop(Iop_32to8, mkexpr(t2)),
                                             unop(Iop_32to8, mkexpr(t0)))));
                     break;
                  }
                  case 0x04: {  
                     DIP("addu_s.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I8);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I8);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I8);
                     t12 = newTemp(Ity_I32);

                     
                     assign(t0,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           mkU8(0xff),
                                           unop(Iop_32to8, mkexpr(t0))));

                     
                     assign(t3,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t4, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t3),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     
                     assign(t5, IRExpr_ITE(mkexpr(t4),
                                           mkU8(0xff),
                                           unop(Iop_32to8, mkexpr(t3))));

                     
                     assign(t6,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t7, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t6),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     
                     assign(t8, IRExpr_ITE(mkexpr(t7),
                                           mkU8(0xff),
                                           unop(Iop_32to8, mkexpr(t6))));

                     
                     assign(t9,
                            binop(Iop_Add32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     
                     assign(t10, binop(Iop_CmpEQ32,
                                       binop(Iop_And32,
                                             mkexpr(t9),
                                             mkU32(0x00000100)),
                                       mkU32(0x00000100)));
                     
                     assign(t11, IRExpr_ITE(mkexpr(t10),
                                            mkU8(0xff),
                                            unop(Iop_32to8, mkexpr(t9))));

                     assign(t12,
                            binop(Iop_Or32,
                                  binop(Iop_Or32,
                                        binop(Iop_Or32,
                                              unop(Iop_1Sto32, mkexpr(t10)),
                                              unop(Iop_1Sto32, mkexpr(t7))),
                                        unop(Iop_1Sto32, mkexpr(t4))),
                                  unop(Iop_1Sto32, mkexpr(t1))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    mkexpr(t12),
                                                    mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000))));

                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16, mkexpr(t11), mkexpr(t8)),
                                   binop(Iop_8HLto16, mkexpr(t5), mkexpr(t2))));
                     break;
                  }
                  case 0x05: {  
                     DIP("subu_s.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_QSub8Ux4, getIReg(rs), getIReg(rt)));

                     
                     assign(t6,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t7,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t8,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t9,
                            binop(Iop_Sub32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t6),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     assign(t3, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t7),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     assign(t4, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t8),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     assign(t5, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            mkexpr(t9),
                                            mkU32(0x00000100)),
                                      mkU32(0x00000100)));
                     putDSPControl(IRExpr_ITE(mkexpr(t5),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     putIReg(rd, mkexpr(t1));
                     break;
                  }
                  case 0x6: {  
                     DIP("muleu_s.ph.qbl r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);

                     assign(t0,
                            unop(Iop_64to32,
                                 binop(Iop_MullU32,
                                       unop(Iop_8Uto32,
                                            unop(Iop_16HIto8,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs)))),
                                       unop(Iop_16Uto32,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t1,
                            unop(Iop_64to32,
                                 binop(Iop_MullU32,
                                       unop(Iop_8Uto32,
                                            unop(Iop_16to8,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs)))),
                                       unop(Iop_16Uto32,
                                            unop(Iop_32to16, getIReg(rt))))));

                     assign(t2, binop(Iop_CmpNE32,
                                      mkU32(0x0),
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x03ff0000))));
                     assign(t3, binop(Iop_CmpNE32,
                                      mkU32(0x0),
                                      binop(Iop_And32,
                                            mkexpr(t1),
                                            mkU32(0x03ff0000))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x200000)),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x200000)),
                                                         getDSPControl())));
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   IRExpr_ITE(mkexpr(t2),
                                              mkU16(0xffff),
                                              unop(Iop_32to16, mkexpr(t0))),
                                   IRExpr_ITE(mkexpr(t3),
                                              mkU16(0xffff),
                                              unop(Iop_32to16, mkexpr(t1)))));
                     break;
                  }
                  case 0x7: {  
                     DIP("muleu_s.ph.qbr r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);

                     assign(t0, unop(Iop_64to32,
                                     binop(Iop_MullU32,
                                           unop(Iop_8Uto32,
                                                unop(Iop_16HIto8,
                                                     unop(Iop_32to16,
                                                          getIReg(rs)))),
                                           unop(Iop_16Uto32,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t1, unop(Iop_64to32,
                                     binop(Iop_MullU32,
                                           unop(Iop_8Uto32,
                                                unop(Iop_16to8,
                                                     unop(Iop_32to16,
                                                          getIReg(rs)))),
                                           unop(Iop_16Uto32,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));

                     assign(t2, binop(Iop_CmpNE32,
                                      mkU32(0x0),
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x03ff0000))));
                     assign(t3, binop(Iop_CmpNE32,
                                      mkU32(0x0),
                                      binop(Iop_And32,
                                            mkexpr(t1),
                                            mkU32(0x03ff0000))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x200000)),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x200000)),
                                                         getDSPControl())));
                     putIReg(rd, binop(Iop_16HLto32,
                                       IRExpr_ITE(mkexpr(t2),
                                                  mkU16(0xffff),
                                                  unop(Iop_32to16,
                                                       mkexpr(t0))),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU16(0xffff),
                                                  unop(Iop_32to16,
                                                       mkexpr(t1)))));
                     break;
                  }
                  case 0x08: {  
                     DIP("addu.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);

                     
                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t1, binop(Iop_CmpLT32U,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, mkexpr(t0))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs)))));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t3, binop(Iop_CmpLT32U,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, mkexpr(t2))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16,
                                                getIReg(rs)))));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t2)),
                                       unop(Iop_32to16, mkexpr(t0))));
                     break;
                  }
                  case 0x9: {  
                     DIP("subu.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);

                     
                     assign(t0, binop(Iop_Sub32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            mkexpr(t0),
                                            mkU32(0x00010000)),
                                      mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Sub32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            mkexpr(t2),
                                            mkU32(0x00010000)),
                                      mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t2)),
                                       unop(Iop_32to16, mkexpr(t0))));
                     break;
                  }
                  case 0xA: {  
                     DIP("addq.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t6, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t0))),
                                      mkU32(0x1)));
                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t0),
                                                  mkU32(0x8000)),
                                            mkU8(15)),
                                      mkexpr(t6)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t7, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x1)));
                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0x00008000)),
                                            mkU8(15)),
                                      mkexpr(t7)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t2)),
                                       unop(Iop_32to16, mkexpr(t0))));
                     break;
                  }
                  case 0xB: {  
                     DIP("subq.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t6, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t0))),
                                      mkU32(0x1)));
                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t0),
                                                  mkU32(0x8000)),
                                            mkU8(15)),
                                      mkexpr(t6)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t7, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x1)));
                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0x00008000)),
                                            mkU8(15)),
                                      mkexpr(t7)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t2)),
                                       unop(Iop_32to16, mkexpr(t0))));
                     break;
                  }
                  case 0xC: {  
                     DIP("addu_s.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);

                     
                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t1, binop(Iop_CmpLT32U,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, mkexpr(t0))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs)))));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t3, binop(Iop_CmpLT32U,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, mkexpr(t2))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs)))));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, binop(Iop_16HLto32,
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU16(0xffff),
                                                  unop(Iop_32to16,
                                                       mkexpr(t2))),
                                       IRExpr_ITE(mkexpr(t1),
                                                  mkU16(0xffff),
                                                  unop(Iop_32to16,
                                                       mkexpr(t0)))));
                     break;
                  }
                  case 0xD: {  
                     DIP("subu_s.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);

                     
                     assign(t0, binop(Iop_Sub32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            mkexpr(t0), mkU32(0x00010000)),
                                      mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     
                     assign(t2, binop(Iop_Sub32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            mkexpr(t2), mkU32(0x00010000)),
                                      mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   IRExpr_ITE(mkexpr(t3),
                                              mkU16(0x0000),
                                              unop(Iop_32to16, mkexpr(t2))),
                                   IRExpr_ITE(mkexpr(t1),
                                              mkU16(0x0000),
                                              unop(Iop_32to16, mkexpr(t0)))));
                     break;
                  }
                  case 0xE: {  
                     DIP("addq_s.ph r%d r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I16);
                     t5 = newTemp(Ity_I16);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t6, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t0))),
                                      mkU32(0x1)));
                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t0),
                                                  mkU32(0x8000)),
                                            mkU8(15)),
                                      mkexpr(t6)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     
                     assign(t4, IRExpr_ITE(mkexpr(t1),
                                           IRExpr_ITE(binop(Iop_CmpEQ32,
                                                            mkexpr(t6),
                                                            mkU32(0x0)),
                                                      mkU16(0x7fff),
                                                      mkU16(0x8000)),
                                           unop(Iop_32to16, mkexpr(t0))));

                     
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t7, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x1)));
                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0x00008000)),
                                            mkU8(15)),
                                      mkexpr(t7)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     
                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           IRExpr_ITE(binop(Iop_CmpEQ32,
                                                            mkexpr(t7),
                                                            mkU32(0x0)),
                                                      mkU16(0x7fff),
                                                      mkU16(0x8000)),
                                           unop(Iop_32to16, mkexpr(t2))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t5), mkexpr(t4)));
                     break;
                  }
                  case 0xF: {  
                     DIP("subq_s.ph r%d r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I16);
                     t5 = newTemp(Ity_I16);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t6, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t0))),
                                      mkU32(0x1)));
                     
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t0),
                                                  mkU32(0x8000)),
                                            mkU8(15)),
                                      mkexpr(t6)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     
                     assign(t4, IRExpr_ITE(mkexpr(t1),
                                           IRExpr_ITE(binop(Iop_CmpEQ32,
                                                            mkexpr(t6),
                                                            mkU32(0x0)),
                                                      mkU16(0x7fff),
                                                      mkU16(0x8000)),
                                           unop(Iop_32to16, mkexpr(t0))));

                     
                     assign(t2, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t7, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x1)));
                     
                     assign(t3, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  mkexpr(t2),
                                                  mkU32(0x00008000)),
                                            mkU8(15)),
                                      mkexpr(t7)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     
                     assign(t5, IRExpr_ITE(mkexpr(t3),
                                           IRExpr_ITE(binop(Iop_CmpEQ32,
                                                            mkexpr(t7),
                                                            mkU32(0x0)),
                                                      mkU16(0x7fff),
                                                      mkU16(0x8000)),
                                           unop(Iop_32to16, mkexpr(t2))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t5), mkexpr(t4)));
                     break;
                  }
                  case 0x10: {  
                     DIP("addsc r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);

                     /* The carry bit result out of the addition operation is
                        written to bit 13(the c field) of the DSPControl reg. */
                     assign(t0, binop(Iop_Add64,
                                      unop(Iop_32Uto64, getIReg(rs)),
                                      unop(Iop_32Uto64, getIReg(rt))));

                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t0)),
                                            mkU32(0x1)),
                                      mkU32(0x1)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x2000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xffffdfff))));

                     putIReg(rd, unop(Iop_64to32, mkexpr(t0)));
                     break;
                  }
                  case 0x11: {  
                     DIP("addwc r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I1);

                     
                     assign(t0, binop(Iop_Shr32,
                                       binop(Iop_And32,
                                             getDSPControl(),
                                             mkU32(0x2000)),
                                       mkU8(0xd)));
                     assign(t1, binop(Iop_Add64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64,
                                           binop(Iop_Add32,
                                                 getIReg(rt),
                                                 mkexpr(t0)))));

                     
                     assign(t2, binop(Iop_And32,
                                      unop(Iop_64HIto32, mkexpr(t1)),
                                      mkU32(0x1)));
                     assign(t3, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            unop(Iop_64to32, mkexpr(t1)),
                                            mkU32(0x80000000)),
                                      mkU8(31)));
                     assign(t4, binop(Iop_CmpNE32, mkexpr(t2), mkexpr(t3)));

                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));
                     putIReg(rd, unop(Iop_64to32, mkexpr(t1)));
                     break;
                  }
                  case 0x12: {  
                     DIP("modsub r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);

                     
                     assign(t0,
                            unop(Iop_8Uto32,
                                 unop(Iop_16to8,
                                      unop(Iop_32to16, getIReg(rt)))));

                     
                     assign(t1,
                            unop(Iop_16Uto32,
                                 binop(Iop_8HLto16,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))),
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     
                     assign(t2,
                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                             getIReg(rs),
                                             mkU32(0x00000000)),
                                       mkexpr(t1),
                                       binop(Iop_Sub32,
                                             getIReg(rs), mkexpr(t0))));
                     putIReg(rd, mkexpr(t2));
                     break;
                  }
                  case 0x14: {  
                     DIP("raddu.w.qb r%d, r%d", rd, rs);
                     vassert(!mode64);
                     putIReg(rd, binop(Iop_Add32,
                                       binop(Iop_Add32,
                                             unop(Iop_8Uto32,
                                                  unop(Iop_16to8,
                                                       unop(Iop_32to16,
                                                            getIReg(rs)))),
                                             unop(Iop_8Uto32,
                                                  unop(Iop_16HIto8,
                                                       unop(Iop_32to16,
                                                            getIReg(rs))))),
                                       binop(Iop_Add32,
                                             unop(Iop_8Uto32,
                                                  unop(Iop_16to8,
                                                       unop(Iop_32HIto16,
                                                            getIReg(rs)))),
                                             unop(Iop_8Uto32,
                                                  unop(Iop_16HIto8,
                                                       unop(Iop_32HIto16,
                                                            getIReg(rs)))))));
                     break;
                  }
                  case 0x16: {  
                     DIP("addq_s.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Add64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));

                     assign(t3, binop(Iop_And32,
                                      unop(Iop_64HIto32, mkexpr(t0)),
                                      mkU32(0x1)));
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t0)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      mkexpr(t3)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             mkexpr(t3),
                                                             mkU32(0x0)),
                                                       mkU32(0x7fffffff),
                                                       mkU32(0x80000000)),
                                            unop(Iop_64to32, mkexpr(t0))));
                     break;
                  }
                  case 0x17: {  
                     DIP("subq_s.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Sub64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));

                     assign(t3, binop(Iop_And32,
                                      unop(Iop_64HIto32, mkexpr(t0)),
                                      mkU32(0x1)));
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t0)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      mkexpr(t3)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00100000)),
                                              getDSPControl()));

                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                                             mkexpr(t3),
                                                             mkU32(0x0)),
                                                       mkU32(0x7fffffff),
                                                       mkU32(0x80000000)),
                                            unop(Iop_64to32, mkexpr(t0))));
                     break;
                  }
                  case 0x1C: {  
                     DIP("muleq_s.w.phl r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I32);

                     assign(t0,
                            binop(Iop_Shl32,
                                  binop(Iop_Mul32,
                                        unop(Iop_16Sto32,
                                             unop(Iop_32HIto16, getIReg(rt))),
                                        unop(Iop_16Sto32,
                                             unop(Iop_32HIto16, getIReg(rs)))),
                                  mkU8(0x1)));
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0xffff0000)),
                                      mkU32(0x80000000)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0xffff0000)),
                                      mkU32(0x80000000)));
                     assign(t3, IRExpr_ITE(mkexpr(t1),
                                           IRExpr_ITE(mkexpr(t2),
                                                      binop(Iop_Or32,
                                                            getDSPControl(),
                                                            mkU32(0x00200000)),
                                                      getDSPControl()),
                                           getDSPControl()));
                     putDSPControl(mkexpr(t3));

                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(mkexpr(t2),
                                                       mkU32(0x7fffffff),
                                                       mkexpr(t0)),
                                            mkexpr(t0)));
                     break;
                  }
                  case 0x1D: {  
                     DIP("muleq_s.w.phr r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t0,
                            binop(Iop_Shl32,
                                  binop(Iop_Mul32,
                                        unop(Iop_16Sto32,
                                             unop(Iop_32to16, getIReg(rt))),
                                        unop(Iop_16Sto32,
                                             unop(Iop_32to16, getIReg(rs)))),
                                  mkU8(0x1)));
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0xffff)),
                                      mkU32(0x8000)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0xffff)),
                                      mkU32(0x8000)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              IRExpr_ITE(mkexpr(t2),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(mkexpr(t2),
                                                       mkU32(0x7fffffff),
                                                       mkexpr(t0)),
                                            mkexpr(t0)));
                     break;
                  }
                  case 0x1E: {  
                     DIP("mulq_s.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I16);
                     t3 = newTemp(Ity_I16);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t5,
                            unop(Iop_16Sto32, unop(Iop_32to16, getIReg(rs))));
                     assign(t6,
                            unop(Iop_16Sto32, unop(Iop_32to16, getIReg(rt))));

                     assign(t7,
                            unop(Iop_16Sto32, unop(Iop_32HIto16, getIReg(rs))));
                     assign(t8,
                            unop(Iop_16Sto32, unop(Iop_32HIto16, getIReg(rt))));

                     assign(t0, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t5),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000))),
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t6),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000)))));
                     assign(t1, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t7),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000))),
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t8),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000)))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    binop(Iop_Or32,
                                                          mkexpr(t0),
                                                          mkexpr(t1)),
                                                    mkU32(0x0)),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x200000))));

                     assign(t2, unop(Iop_32HIto16,
                                     binop(Iop_Shl32,
                                           unop(Iop_64to32,
                                                binop(Iop_MullS32,
                                                      mkexpr(t7),
                                                      mkexpr(t8))),
                                           mkU8(0x1))));
                     assign(t3, unop(Iop_32HIto16,
                                     binop(Iop_Shl32,
                                           unop(Iop_64to32,
                                                binop(Iop_MullS32,
                                                      mkexpr(t5),
                                                      mkexpr(t6))),
                                           mkU8(0x1))));
                     putIReg(rd, binop(Iop_16HLto32,
                                       IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        mkexpr(t1),
                                                        mkU32(0x0)),
                                                  mkexpr(t2),
                                                  mkU16(0x7fff)),
                                       IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        mkexpr(t0),
                                                        mkU32(0x0)),
                                                  mkexpr(t3),
                                                  mkU16(0x7fff))));
                     break;
                  }
                  case 0x1F: {  
                     DIP("mulq_rs.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I16);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I16);

                     
                     assign(t0, binop(Iop_Add32,
                                      binop(Iop_Shl32,
                                            binop(Iop_Mul32,
                                                  unop(Iop_16Sto32,
                                                       unop(Iop_32to16,
                                                            getIReg(rt))),
                                                  unop(Iop_16Sto32,
                                                       unop(Iop_32to16,
                                                            getIReg(rs)))),
                                            mkU8(0x1)),
                                      mkU32(0x00008000)));
                     assign(t1, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rt), mkU32(0xffff)),
                                      mkU32(0x8000)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rs), mkU32(0xffff)),
                                      mkU32(0x8000)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              IRExpr_ITE(mkexpr(t2),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     assign(t3, IRExpr_ITE(mkexpr(t1),
                                           IRExpr_ITE(mkexpr(t2),
                                                      mkU16(0x7fff),
                                                      unop(Iop_32HIto16,
                                                           mkexpr(t0))),
                                           unop(Iop_32HIto16, mkexpr(t0))));

                     
                     assign(t4, binop(Iop_Add32,
                                      binop(Iop_Shl32,
                                            binop(Iop_Mul32,
                                                  unop(Iop_16Sto32,
                                                       unop(Iop_32HIto16,
                                                            getIReg(rt))),
                                                  unop(Iop_16Sto32,
                                                       unop(Iop_32HIto16,
                                                            getIReg(rs)))),
                                            mkU8(0x1)),
                                      mkU32(0x00008000)));
                     assign(t5, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0xffff0000)),
                                      mkU32(0x80000000)));
                     assign(t6, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0xffff0000)),
                                      mkU32(0x80000000)));
                     putDSPControl(IRExpr_ITE(mkexpr(t5),
                                             IRExpr_ITE(mkexpr(t6),
                                                        binop(Iop_Or32,
                                                             getDSPControl(),
                                                             mkU32(0x00200000)),
                                                        getDSPControl()),
                                             getDSPControl()));
                     assign(t7, IRExpr_ITE(mkexpr(t5),
                                           IRExpr_ITE(mkexpr(t6),
                                                      mkU16(0x7fff),
                                                      unop(Iop_32HIto16,
                                                           mkexpr(t4))),
                                           unop(Iop_32HIto16, mkexpr(t4))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t7), mkexpr(t3)));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x11: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("cmpu.eq.qb r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);

                     assign(t1,
                            binop(Iop_CmpEQ32,
                                  binop(Iop_And32, getIReg(rs), mkU32(0xff)),
                                  binop(Iop_And32, getIReg(rt), mkU32(0xff))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));
                     break;
                  }
                  case 0x1: {  
                     DIP("cmpu.lt.qb r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);

                     assign(t1, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));
                     break;
                  }
                  case 0x2: {  
                     DIP("cmpu.le.qb r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);

                     assign(t1, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));
                     break;
                  }
                  case 0x3: {  
                     DIP("pick.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I8);

                     assign(t0, getDSPControl());
                     assign(t1, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x01000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_16to8,
                                                 unop(Iop_32to16,
                                                      getIReg(rs))),
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt)))));
                     assign(t2, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x02000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs))),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt)))));
                     assign(t3, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x04000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs))),
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt)))));
                     assign(t4, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x08000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs))),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt)))));
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16, mkexpr(t4), mkexpr(t3)),
                                   binop(Iop_8HLto16, mkexpr(t2), mkexpr(t1))));
                     break;
                  }
                  case 0x4: {  
                     DIP("cmpgu.eq.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001), mkU32(0)));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));

                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));

                     assign(t4, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  case 0x5: {  
                     DIP("cmpgu.lt.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001), mkU32(0)));

                     assign(t2, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));

                     assign(t3, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));

                     assign(t4, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));
                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  case 0x6: {  
                     DIP("cmpgu.le.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001), mkU32(0)));

                     assign(t2, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));

                     assign(t3, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));

                     assign(t4, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));
                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  case 0x8: {  
                     DIP("cmp.eq.ph r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t1, binop(Iop_CmpEQ16,
                                      unop(Iop_32to16, getIReg(rs)),
                                      unop(Iop_32to16, getIReg(rt))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));
                     assign(t2, binop(Iop_CmpEQ16,
                                      unop(Iop_32HIto16, getIReg(rs)),
                                      unop(Iop_32HIto16, getIReg(rt))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));
                     break;
                  }
                  case 0x9: {  
                     DIP("cmp.lt.ph r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t1, binop(Iop_CmpLT32S,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLT32S,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));
                     break;
                  }
                  case 0xA: {  
                     DIP("cmp.le.ph r%d, r%d", rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t1, binop(Iop_CmpLE32S,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLE32S,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));
                     break;
                  }
                  case 0xB: {  
                     DIP("pick.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I16);
                     t2 = newTemp(Ity_I16);

                     assign(t0, getDSPControl());

                     assign(t1, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x01000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_32to16, getIReg(rs)),
                                           unop(Iop_32to16, getIReg(rt))));

                     assign(t2, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0x02000000)),
                                                 mkU32(0x0)),
                                           unop(Iop_32HIto16, getIReg(rs)),
                                           unop(Iop_32HIto16, getIReg(rt))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t2), mkexpr(t1)));
                     break;
                  }
                  case 0xC: {  
                     DIP("precrq.qb.ph r%d, r%d, %d", rd, rs, rt);
                     vassert(!mode64);
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16,
                                         unop(Iop_16HIto8,
                                              unop(Iop_32HIto16, getIReg(rs))),
                                         unop(Iop_16HIto8,
                                              unop(Iop_32to16, getIReg(rs)))),
                                   binop(Iop_8HLto16,
                                         unop(Iop_16HIto8,
                                              unop(Iop_32HIto16, getIReg(rt))),
                                         unop(Iop_16HIto8,
                                              unop(Iop_32to16, getIReg(rt))))));
                     break;
                  }
                  case 0xD: {  
                     DIP("precr.qb.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);

                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16,
                                         unop(Iop_16to8,
                                              unop(Iop_32HIto16, getIReg(rs))),
                                         unop(Iop_16to8,
                                              unop(Iop_32to16, getIReg(rs)))),
                                   binop(Iop_8HLto16,
                                         unop(Iop_16to8,
                                              unop(Iop_32HIto16, getIReg(rt))),
                                         unop(Iop_16to8,
                                              unop(Iop_32to16, getIReg(rt))))));
                     break;
                  }
                  case 0xF: {  
                     DIP("precrqu_s.qb.ph r%d, r%d, %d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I8);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I8);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I8);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I8);
                     t11 = newTemp(Ity_I1);
                     t12 = newTemp(Ity_I32);
                     t13 = newTemp(Ity_I8);
                     t14 = newTemp(Ity_I1);
                     t15 = newTemp(Ity_I32);

                     assign(t4, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                 mkU32(0x7f80),
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32to16,
                                                            getIReg(rs))),
                                                       mkU32(0x7fff))),
                                           mkU8(0xff),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     binop(Iop_Shl32,
                                                           getIReg(rs),
                                                           mkU8(1))))));
                     assign(t0, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32to16,
                                                                 getIReg(rs))),
                                                       mkU32(0x00008000)),
                                                 mkU32(0x0)),
                                           mkexpr(t4),
                                           mkU8(0x0)));
                     assign(t5, binop(Iop_And32,
                                      unop(Iop_16Uto32,
                                            unop(Iop_32to16,
                                                 getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t6, binop(Iop_CmpLT32U,
                                      mkU32(0x7f80),
                                      binop(Iop_And32,
                                            unop(Iop_16Uto32,
                                                 unop(Iop_32to16,
                                                 getIReg(rs))),
                                            mkU32(0x7fff))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    mkexpr(t5),
                                                    mkU32(0x0)),
                                              IRExpr_ITE(mkexpr(t6),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00400000)
                                                              ),
                                                         getDSPControl()),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00400000))));

                     assign(t7, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                 mkU32(0x7f80),
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32HIto16,
                                                                 getIReg(rs))),
                                                       mkU32(0x7fff))),
                                           mkU8(0xff),
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     binop(Iop_Shl32,
                                                           getIReg(rs),
                                                           mkU8(1))))));
                     assign(t1, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32HIto16,
                                                                 getIReg(rs))),
                                                       mkU32(0x00008000)),
                                                 mkU32(0x0)),
                                           mkexpr(t7),
                                           mkU8(0x0)));
                     assign(t8, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            unop(Iop_16Uto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs))),
                                            mkU32(0x00008000)),
                                      mkU32(0x0)));
                     assign(t9, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                 mkU32(0x7f80),
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32HIto16,
                                                                 getIReg(rs))),
                                                       mkU32(0x7fff))),
                                           binop(Iop_Or32,
                                                 getDSPControl(),
                                                 mkU32(0x00400000)),
                                           getDSPControl()));
                     putDSPControl(IRExpr_ITE(mkexpr(t8),
                                              mkexpr(t9),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00400000))));

                     assign(t10, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                  mkU32(0x7f80),
                                                  binop(Iop_And32,
                                                        unop(Iop_16Uto32,
                                                             unop(Iop_32to16,
                                                             getIReg(rt))),
                                                        mkU32(0x7fff))),
                                            mkU8(0xff),
                                            unop(Iop_16HIto8,
                                                 unop(Iop_32to16,
                                                      binop(Iop_Shl32,
                                                            getIReg(rt),
                                                            mkU8(1))))));
                     assign(t2, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32to16,
                                                                 getIReg(rt))),
                                                       mkU32(0x00008000)),
                                                 mkU32(0x0)),
                                           mkexpr(t10),
                                           mkU8(0x0)));
                     assign(t11, binop(Iop_CmpEQ32,
                                       binop(Iop_And32,
                                             unop(Iop_16Uto32,
                                                  unop(Iop_32to16,
                                                       getIReg(rt))),
                                             mkU32(0x00008000)),
                                       mkU32(0x0)));
                     assign(t12, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                  mkU32(0x7f80),
                                                  binop(Iop_And32,
                                                        unop(Iop_16Uto32,
                                                             unop(Iop_32to16,
                                                             getIReg(rt))),
                                                        mkU32(0x7fff))),
                                            binop(Iop_Or32,
                                                  getDSPControl(),
                                                  mkU32(0x00400000)),
                                            getDSPControl()));
                     putDSPControl(IRExpr_ITE(mkexpr(t11),
                                              mkexpr(t12),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00400000))));

                     assign(t13, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                  mkU32(0x7f80),
                                                  binop(Iop_And32,
                                                        unop(Iop_16Uto32,
                                                             unop(Iop_32HIto16,
                                                                  getIReg(rt))),
                                                        mkU32(0x7fff))),
                                            mkU8(0xff),
                                            unop(Iop_16HIto8,
                                                 unop(Iop_32HIto16,
                                                      binop(Iop_Shl32,
                                                            getIReg(rt),
                                                            mkU8(1))))));
                     assign(t3, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       unop(Iop_16Uto32,
                                                            unop(Iop_32HIto16,
                                                                 getIReg(rt))),
                                                       mkU32(0x00008000)),
                                                 mkU32(0x0)),
                                           mkexpr(t13),
                                           mkU8(0x0)));
                     assign(t14, binop(Iop_CmpEQ32,
                                       binop(Iop_And32,
                                             unop(Iop_16Uto32,
                                                  unop(Iop_32HIto16,
                                                       getIReg(rt))),
                                             mkU32(0x00008000)),
                                       mkU32(0x0)));
                     assign(t15, IRExpr_ITE(binop(Iop_CmpLT32U,
                                                  mkU32(0x7f80),
                                                  binop(Iop_And32,
                                                        unop(Iop_16Uto32,
                                                             unop(Iop_32HIto16,
                                                                  getIReg(rt))),
                                                        mkU32(0x7fff))),
                                            binop(Iop_Or32,
                                                  getDSPControl(),
                                                  mkU32(0x00400000)),
                                            getDSPControl()));
                     putDSPControl(IRExpr_ITE(mkexpr(t14),
                                              mkexpr(t15),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00400000))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       binop(Iop_8HLto16,
                                             mkexpr(t1), mkexpr(t0)),
                                       binop(Iop_8HLto16,
                                             mkexpr(t3), mkexpr(t2))));
                     break;
                  }
                  case 0x14: {  
                     DIP("precrq.ph.w r%d, r%d, %d", rd, rs, rt);
                     vassert(!mode64);
                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32HIto16, getIReg(rs)),
                                       unop(Iop_32HIto16, getIReg(rt))));
                     break;
                  }
                  case 0x15: {  
                     DIP("precrq_rs.ph.w r%d, r%d, %d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I64);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_Add64,
                                      binop(Iop_32HLto64,
                                            binop(Iop_Shr32,
                                                  binop(Iop_And32,
                                                        getIReg(rs),
                                                        mkU32(0x80000000)),
                                                  mkU8(31)),
                                            getIReg(rs)),
                                      mkU64(0x0000000000008000ULL)));
                     assign(t1, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t0)),
                                            mkU32(0x1)),
                                      binop(Iop_And32,
                                            binop(Iop_Shr32,
                                                  unop(Iop_64to32, mkexpr(t0)),
                                                  mkU8(31)),
                                            mkU32(0x1))));
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x7fffffff),
                                           unop(Iop_64to32, mkexpr(t0))));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              getDSPControl()));
                     assign(t3, binop(Iop_Add64,
                                      binop(Iop_32HLto64,
                                            binop(Iop_Shr32,
                                                  binop(Iop_And32,
                                                        getIReg(rt),
                                                        mkU32(0x80000000)),
                                                  mkU8(31)),
                                            getIReg(rt)),
                                      mkU64(0x0000000000008000ULL)));
                     assign(t4, binop(Iop_CmpNE32,
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t3)),
                                            mkU32(0x1)),
                                      binop(Iop_And32,
                                            binop(Iop_Shr32,
                                                  unop(Iop_64to32, mkexpr(t3)),
                                                  mkU8(31)),
                                            mkU32(0x1))));
                     assign(t5, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x7fffffff),
                                           unop(Iop_64to32, mkexpr(t3))));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              getDSPControl()));
                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32HIto16, mkexpr(t2)),
                                       unop(Iop_32HIto16, mkexpr(t5))));
                     break;
                  }
                  case 0x1E: {  
                     DIP("precr_sra.ph.w r%d, r%d, %d", rt, rs, rd);
                     vassert(!mode64);

                     if (0 == rd) {
                        putIReg(rt, binop(Iop_16HLto32,
                                          unop(Iop_32to16, getIReg(rt)),
                                          unop(Iop_32to16, getIReg(rs))));
                     } else {
                        putIReg(rt, binop(Iop_16HLto32,
                                          unop(Iop_32to16, binop(Iop_Sar32,
                                                                 getIReg(rt),
                                                                 mkU8(rd))),
                                          unop(Iop_32to16, binop(Iop_Sar32,
                                                                 getIReg(rs),
                                                                 mkU8(rd)))));
                     }
                     break;
                  }
                  case 0x1F: {  
                     DIP("precr_sra_r.ph.w r%d, r%d, %d", rt, rs, rd);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);

                     if (0 == rd) {
                        putIReg(rt, binop(Iop_16HLto32,
                                          unop(Iop_32to16, getIReg(rt)),
                                          unop(Iop_32to16, getIReg(rs))));
                     } else {
                        assign(t0, binop(Iop_Shr32,
                                         binop(Iop_Add32,
                                               binop(Iop_Sar32,
                                                     getIReg(rt),
                                                     mkU8(rd-1)),
                                               mkU32(0x1)),
                                         mkU8(0x1)));
                        assign(t1, binop(Iop_Shr32,
                                         binop(Iop_Add32,
                                               binop(Iop_Sar32,
                                                     getIReg(rs),
                                                     mkU8(rd-1)),
                                               mkU32(0x1)),
                                         mkU8(0x1)));
                        putIReg(rt, binop(Iop_16HLto32,
                                          unop(Iop_32to16, mkexpr(t0)),
                                          unop(Iop_32to16, mkexpr(t1))));
                     };
                     break;
                  }
                  case 0xE: {  
                     DIP("packrl.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, getIReg(rs)),
                                       unop(Iop_32HIto16, getIReg(rt))));
                     break;
                  }
                  case 0x18: {  
                     DIP("cmpgdu.eq.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1,
                            binop(Iop_CmpEQ32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpEQ32,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  case 0x19: {  
                     DIP("cmpgdu.lt.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpLT32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  case 0x1A: {  
                     DIP("cmpgdu.le.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           mkU32(0x00000001),
                                           mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x01000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfeffffff))));

                     assign(t2, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16, getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32to16,
                                                     getIReg(rt))))));
                     assign(t6, IRExpr_ITE(mkexpr(t2),
                                           mkU32(0x00000002), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x02000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfdffffff))));

                     assign(t3, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16to8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t7, IRExpr_ITE(mkexpr(t3),
                                           mkU32(0x00000004), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x04000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xfbffffff))));

                     assign(t4, binop(Iop_CmpLE32U,
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rs)))),
                                      unop(Iop_8Uto32,
                                           unop(Iop_16HIto8,
                                                unop(Iop_32HIto16,
                                                     getIReg(rt))))));
                     assign(t8, IRExpr_ITE(mkexpr(t4),
                                           mkU32(0x00000008), mkU32(0)));
                     putDSPControl(IRExpr_ITE(mkexpr(t4),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x08000000)),
                                              binop(Iop_And32,
                                                    getDSPControl(),
                                                    mkU32(0xf7ffffff))));

                     putIReg(rd, binop(Iop_Or32,
                                       binop(Iop_Or32,
                                             binop(Iop_Or32,
                                                   mkexpr(t5), mkexpr(t6)),
                                             mkexpr(t7)),
                                       mkexpr(t8)));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x13: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("shll.qb r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I1);
                     t10 = newTemp(Ity_I1);

                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        
                        assign(t0, binop(Iop_Shl32,
                                         binop(Iop_And32,
                                               getIReg(rt),
                                               mkU32(0x00ff00ff)),
                                         mkU8(rs)));
                        assign(t1, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t0),
                                              mkU32(0xff000000)),
                                        mkU32(0x00000000)));
                        assign(t2, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t0),
                                              mkU32(0xff000000)),
                                        mkU32(0xff000000)));
                        assign(t7, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t0),
                                              mkU32(0x0000ff00)),
                                        mkU32(0x00000000)));
                        assign(t8, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t0),
                                              mkU32(0x0000ff00)),
                                        mkU32(0x000ff00)));
                        
                        assign(t3, binop(Iop_Shl32,
                                         binop(Iop_Shr32,
                                               binop(Iop_And32,
                                                     getIReg(rt),
                                                     mkU32(0xff00ff00)),
                                               mkU8(8)),
                                         mkU8(rs)));
                        assign(t4, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t3),
                                              mkU32(0xff000000)),
                                        mkU32(0x00000000)));
                        assign(t5, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t3),
                                              mkU32(0xff000000)),
                                        mkU32(0xff000000)));
                        assign(t9, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t3),
                                              mkU32(0x0000ff00)),
                                        mkU32(0x00000000)));
                        assign(t10, binop(Iop_CmpNE32,
                                        binop(Iop_And32,
                                              mkexpr(t3),
                                              mkU32(0x0000ff00)),
                                        mkU32(0x0000ff00)));

                        assign(t6, binop(Iop_Or32,
                                         binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t1)),
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t2))),
                                               binop(Iop_And32,
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t7)),
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t8)))),
                                         binop(Iop_Or32,
                                               binop(Iop_And32,
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t4)),
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t5))),
                                               binop(Iop_And32,
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t9)),
                                                     unop(Iop_1Uto32,
                                                          mkexpr(t10))))));

                        putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                       mkexpr(t6),
                                                       mkU32(0x0)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putIReg(rd, binop(Iop_Or32,
                                          binop(Iop_Shl32,
                                                binop(Iop_And32,
                                                      mkexpr(t3),
                                                      mkU32(0x00ff00ff)),
                                                mkU8(8)),
                                          binop(Iop_And32,
                                                mkexpr(t0),
                                                mkU32(0x00ff00ff))));
                     }
                     break;
                  }
                  case 0x3: {  
                     DIP("shrl.qb r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I8);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I8);
                     t9 = newTemp(Ity_I32);

                     assign(t9, binop(Iop_And32, getIReg(rs), mkU32(0x7)));
                     assign(t0, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t1, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           mkexpr(t0),
                                           unop(Iop_32to8, mkexpr(t9)))));

                     assign(t2, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t3, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           mkexpr(t2),
                                           unop(Iop_32to8, mkexpr(t9)))));

                     assign(t4, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t5, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           mkexpr(t4),
                                           unop(Iop_32to8, mkexpr(t9)))));

                     assign(t6, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t7, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           mkexpr(t6),
                                           unop(Iop_32to8, mkexpr(t9)))));
                     putIReg(rd, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  mkexpr(t9),
                                                  mkU32(0x0)),
                                            getIReg(rt),
                                            binop(Iop_16HLto32,
                                                  binop(Iop_8HLto16,
                                                        mkexpr(t7),
                                                        mkexpr(t5)),
                                                  binop(Iop_8HLto16,
                                                        mkexpr(t3),
                                                        mkexpr(t1)))));
                     break;
                  }
                  case 0x2: {  
                     DIP("shllv.qb r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I1);
                     t10 = newTemp(Ity_I1);
                     t11 = newTemp(Ity_I8);

                     assign(t11, unop(Iop_32to8,
                                      binop(Iop_And32,
                                            getIReg(rs),
                                            mkU32(0x7))));
                     
                     assign(t0, binop(Iop_Shl32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0x00ff00ff)),
                                      mkexpr(t11)));
                     assign(t1, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t0),
                                           mkU32(0xff000000)),
                                     mkU32(0x00000000)));
                     assign(t2, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t0),
                                           mkU32(0xff000000)),
                                     mkU32(0xff000000)));
                     assign(t7, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t0),
                                           mkU32(0x0000ff00)),
                                     mkU32(0x00000000)));
                     assign(t8, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t0),
                                           mkU32(0x0000ff00)),
                                     mkU32(0x000ff00)));
                     
                     assign(t3, binop(Iop_Shl32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0xff00ff00)),
                                            mkU8(8)),
                                      mkexpr(t11)));
                     assign(t4, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t3),
                                           mkU32(0xff000000)),
                                     mkU32(0x00000000)));
                     assign(t5, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t3),
                                           mkU32(0xff000000)),
                                     mkU32(0xff000000)));
                     assign(t9, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t3),
                                           mkU32(0x0000ff00)),
                                     mkU32(0x00000000)));
                     assign(t10, binop(Iop_CmpNE32,
                                     binop(Iop_And32,
                                           mkexpr(t3),
                                           mkU32(0x0000ff00)),
                                     mkU32(0x0000ff00)));

                     assign(t6, binop(Iop_Or32,
                                      binop(Iop_Or32,
                                            binop(Iop_And32,
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t1)),
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t2))),
                                            binop(Iop_And32,
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t7)),
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t8)))),
                                      binop(Iop_Or32,
                                            binop(Iop_And32,
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t4)),
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t5))),
                                            binop(Iop_And32,
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t9)),
                                                  unop(Iop_1Uto32,
                                                       mkexpr(t10))))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t6),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              getDSPControl()));
                     putIReg(rd, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  unop(Iop_8Uto32, mkexpr(t11)),
                                                  mkU32(0)),
                                            getIReg(rt),
                                            binop(Iop_Or32,
                                                  binop(Iop_Shl32,
                                                        binop(Iop_And32,
                                                              mkexpr(t3),
                                                              mkU32(0xff00ff)),
                                                        mkU8(8)),
                                                  binop(Iop_And32,
                                                        mkexpr(t0),
                                                        mkU32(0x00ff00ff)))));
                     break;
                  }
                  case 0x1: {  
                     DIP("shrlv.qb r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I8);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I8);

                     assign(t0, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           unop(Iop_8Uto32,
                                                unop(Iop_32to8, getIReg(rt))),
                                           mkU8(rs))));
                     assign(t1, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           unop(Iop_8Uto32,
                                                unop(Iop_16HIto8,
                                                     unop(Iop_32to16,
                                                          getIReg(rt)))),
                                           mkU8(rs))));
                     assign(t2, unop(Iop_32to8,
                                      binop(Iop_Shr32,
                                            unop(Iop_8Uto32,
                                                 unop(Iop_16to8,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rt)))),
                                            mkU8(rs))));
                     assign(t3, unop(Iop_32to8,
                                     binop(Iop_Shr32,
                                           unop(Iop_8Uto32,
                                                unop(Iop_16HIto8,
                                                     unop(Iop_32HIto16,
                                                          getIReg(rt)))),
                                           mkU8(rs))));
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16, mkexpr(t3), mkexpr(t2)),
                                   binop(Iop_8HLto16, mkexpr(t1), mkexpr(t0))));
                     break;
                  }
                  case 0x4: {  
                     DIP("shra.qb r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I32);

                     
                     assign(t1,
                            unop(Iop_8Uto32,
                                 unop(Iop_16HIto8,
                                      unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t2,
                            binop(Iop_Shr32, mkexpr(t1), mkU8(rs)));
                     
                     assign(t0,
                            binop(Iop_Or32,
                                  mkexpr(t2),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t1),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8, mkU8(0x8), mkU8(rs)))));

                     
                     assign(t4,
                            unop(Iop_8Uto32,
                                 unop(Iop_16to8,
                                      unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t5, binop(Iop_Shr32, mkexpr(t4), mkU8(rs)));
                     
                     assign(t3,
                            binop(Iop_Or32,
                                  mkexpr(t5),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t4),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8, mkU8(0x8), mkU8(rs)))));

                     
                     assign(t7,
                            unop(Iop_8Uto32,
                                 unop(Iop_16HIto8,
                                      unop(Iop_32to16, getIReg(rt)))));
                     assign(t8, binop(Iop_Shr32, mkexpr(t7), mkU8(rs)));
                     
                     assign(t6,
                            binop(Iop_Or32,
                                  mkexpr(t8),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t7),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8, mkU8(0x8), mkU8(rs)))));

                     
                     assign(t10,
                            unop(Iop_8Uto32,
                                 unop(Iop_16to8,
                                      unop(Iop_32to16, getIReg(rt)))));
                     assign(t11, binop(Iop_Shr32, mkexpr(t10), mkU8(rs)));
                     
                     assign(t9,
                            binop(Iop_Or32,
                                  mkexpr(t11),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t10),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8, mkU8(0x8), mkU8(rs)))));

                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16,
                                         unop(Iop_32to8, mkexpr(t0)),
                                         unop(Iop_32to8, mkexpr(t3))),
                                   binop(Iop_8HLto16,
                                         unop(Iop_32to8, mkexpr(t6)),
                                         unop(Iop_32to8, mkexpr(t9)))));
                     break;
                  }
                  case 0x5: {  
                     DIP("shra_r.qb r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I8);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I8);

                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        assign(t0, unop(Iop_8Sto32,
                                        unop(Iop_16to8,
                                             unop(Iop_32to16, getIReg(rt)))));
                        assign(t1, unop(Iop_32to8,
                                        binop(Iop_Sar32,
                                              binop(Iop_Add32,
                                                    mkexpr(t0),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(rs-1))),
                                              mkU8(rs))));

                        assign(t2, unop(Iop_8Sto32,
                                        unop(Iop_16HIto8,
                                             unop(Iop_32to16, getIReg(rt)))));
                        assign(t3, unop(Iop_32to8,
                                        binop(Iop_Sar32,
                                              binop(Iop_Add32,
                                                    mkexpr(t2),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(rs-1))),
                                              mkU8(rs))));

                        assign(t4, unop(Iop_8Sto32,
                                        unop(Iop_16to8,
                                             unop(Iop_32HIto16, getIReg(rt)))));
                        assign(t5, unop(Iop_32to8,
                                        binop(Iop_Sar32,
                                              binop(Iop_Add32,
                                                    mkexpr(t4),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(rs-1))),
                                              mkU8(rs))));

                        assign(t6, unop(Iop_8Sto32,
                                        unop(Iop_16HIto8,
                                             unop(Iop_32HIto16, getIReg(rt)))));
                        assign(t7, unop(Iop_32to8,
                                        binop(Iop_Sar32,
                                              binop(Iop_Add32,
                                                    mkexpr(t6),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(rs-1))),
                                              mkU8(rs))));
                        putIReg(rd, binop(Iop_16HLto32,
                                         binop(Iop_8HLto16,
                                               mkexpr(t7), mkexpr(t5)),
                                         binop(Iop_8HLto16,
                                               mkexpr(t3), mkexpr(t1))));
                     }
                     break;
                  }
                  case 0x6: {  
                     DIP("shrav.qb r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);

                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);

                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);

                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I32);

                     
                     assign(t1,
                            unop(Iop_8Uto32,
                                 unop(Iop_16HIto8,
                                      unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t2,
                            binop(Iop_Shr32,
                                  mkexpr(t1),
                                  unop(Iop_32to8, binop(Iop_And32,
                                                        getIReg(rs),
                                                        mkU32(0x7)))));
                     
                     assign(t0,
                            binop(Iop_Or32,
                                  mkexpr(t2),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t1),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8,
                                              mkU8(0x8),
                                              unop(Iop_32to8, binop(Iop_And32,
                                                                    getIReg(rs),
                                                                    mkU32(0x7)))
                                              ))));

                     
                     assign(t4,
                            unop(Iop_8Uto32,
                                 unop(Iop_16to8,
                                      unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t5,
                            binop(Iop_Shr32,
                                  mkexpr(t4),
                                  unop(Iop_32to8, binop(Iop_And32,
                                                        getIReg(rs),
                                                        mkU32(0x7)))));
                     
                     assign(t3,
                            binop(Iop_Or32,
                                  mkexpr(t5),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t4),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8,
                                              mkU8(0x8),
                                              unop(Iop_32to8, binop(Iop_And32,
                                                                    getIReg(rs),
                                                                    mkU32(0x7)))
                                              ))));

                     
                     assign(t7,
                            unop(Iop_8Uto32,
                                 unop(Iop_16HIto8,
                                      unop(Iop_32to16, getIReg(rt)))));
                     assign(t8,
                            binop(Iop_Shr32,
                                  mkexpr(t7),
                                  unop(Iop_32to8, binop(Iop_And32,
                                                        getIReg(rs),
                                                        mkU32(0x7)))));
                     
                     assign(t6,
                            binop(Iop_Or32,
                                  mkexpr(t8),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t7),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8,
                                              mkU8(0x8),
                                              unop(Iop_32to8, binop(Iop_And32,
                                                                    getIReg(rs),
                                                                    mkU32(0x7)))
                                              ))));

                     
                     assign(t10,
                            unop(Iop_8Uto32,
                                 unop(Iop_16to8,
                                      unop(Iop_32to16, getIReg(rt)))));
                     assign(t11,
                            binop(Iop_Shr32,
                                  mkexpr(t10),
                                  unop(Iop_32to8, binop(Iop_And32,
                                                        getIReg(rs),
                                                        mkU32(0x7)))));
                     
                     assign(t9,
                            binop(Iop_Or32,
                                  mkexpr(t11),
                                  binop(Iop_Shl32,
                                        IRExpr_ITE(binop(Iop_CmpEQ32,
                                                         binop(Iop_And32,
                                                               mkexpr(t10),
                                                               mkU32(0x00000080)
                                                              ),
                                                         mkU32(0x00000080)),
                                                   mkU32(0xFFFFFFFF),
                                                   mkU32(0x00000000)),
                                        binop(Iop_Sub8,
                                              mkU8(0x8),
                                              unop(Iop_32to8, binop(Iop_And32,
                                                                    getIReg(rs),
                                                                    mkU32(0x7)))
                                              ))));

                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   binop(Iop_8HLto16,
                                         unop(Iop_32to8,
                                              IRExpr_ITE(binop(Iop_CmpEQ32,
                                                               binop(Iop_And32,
                                                                     mkU32(rs),
                                                                     mkU32(0x7)
                                                                    ),
                                                               mkU32(0x0)),
                                                         mkexpr(t1),
                                                         mkexpr(t0))),
                                         unop(Iop_32to8,
                                              IRExpr_ITE(binop(Iop_CmpEQ32,
                                                               binop(Iop_And32,
                                                                     mkU32(rs),
                                                                     mkU32(0x7)
                                                                    ),
                                                               mkU32(0x0)),
                                                         mkexpr(t2),
                                                         mkexpr(t3)))),
                                   binop(Iop_8HLto16,
                                         unop(Iop_32to8,
                                              IRExpr_ITE(binop(Iop_CmpEQ32,
                                                               binop(Iop_And32,
                                                                     mkU32(rs),
                                                                     mkU32(0x7)
                                                                    ),
                                                               mkU32(0x0)),
                                                         mkexpr(t5),
                                                         mkexpr(t6))),
                                         unop(Iop_32to8,
                                              IRExpr_ITE(binop(Iop_CmpEQ32,
                                                               binop(Iop_And32,
                                                                     mkU32(rs),
                                                                     mkU32(0x7)
                                                                    ),
                                                               mkU32(0x0)),
                                                         mkexpr(t8),
                                                         mkexpr(t9))))));
                     break;
                  }
                  case 0x7: {  
                     DIP("shrav_r.qb r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I8);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I8);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I8);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I8);
                     t8 = newTemp(Ity_I8);
                     t9 = newTemp(Ity_I32);

                     assign(t9, binop(Iop_And32, getIReg(rs), mkU32(0x7)));
                     assign(t8, unop(Iop_32to8,
                                     binop(Iop_Sub32, mkexpr(t9), mkU32(0x1))));
                     assign(t0, unop(Iop_8Sto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t1, unop(Iop_32to8,
                                     binop(Iop_Sar32,
                                           binop(Iop_Add32,
                                                 mkexpr(t0),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkexpr(t8))),
                                           unop(Iop_32to8,
                                                mkexpr(t9)))));

                     assign(t2, unop(Iop_8Sto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t3, unop(Iop_32to8,
                                     binop(Iop_Sar32,
                                           binop(Iop_Add32,
                                                 mkexpr(t2),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkexpr(t8))),
                                           unop(Iop_32to8, mkexpr(t9)))));

                     assign(t4, unop(Iop_8Sto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t5, unop(Iop_32to8,
                                     binop(Iop_Sar32,
                                           binop(Iop_Add32,
                                                 mkexpr(t4),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkexpr(t8))),
                                           unop(Iop_32to8, mkexpr(t9)))));

                     assign(t6, unop(Iop_8Sto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t7, unop(Iop_32to8,
                                     binop(Iop_Sar32,
                                           binop(Iop_Add32,
                                                 mkexpr(t6),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkexpr(t8))),
                                           unop(Iop_32to8, mkexpr(t9)))));
                     putIReg(rd, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  mkexpr(t9),
                                                  mkU32(0x0)),
                                            getIReg(rt),
                                            binop(Iop_16HLto32,
                                                  binop(Iop_8HLto16,
                                                        mkexpr(t7),
                                                        mkexpr(t5)),
                                                  binop(Iop_8HLto16,
                                                        mkexpr(t3),
                                                        mkexpr(t1)))));
                     break;
                  }
                  case 0x8: {  
                     DIP("shll.ph r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);

                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        
                        assign(t0, binop(Iop_Shl32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32to16, getIReg(rt))),
                                         mkU8(rs)));

                        assign(t1, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                               binop(Iop_Sar32,
                                                     mkexpr(t0),
                                                     mkU8(16)),
                                               mkU32(0))));
                        assign(t2, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                              binop(Iop_Sar32,
                                                    mkexpr(t0),
                                                    mkU8(16)),
                                              mkU32(0xffffffff))));
                        assign(t3, binop(Iop_And32,
                                         mkexpr(t1),
                                         mkexpr(t2)));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t3),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       binop(Iop_And32,
                                                             getIReg(rt),
                                                             mkU32(0x00008000)),
                                                       binop(Iop_And32,
                                                             mkexpr(t0),
                                                             mkU32(0x00008000))
                                                      ),
                                                 getDSPControl(),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000))));
                        
                        assign(t4, binop(Iop_Shl32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32HIto16, getIReg(rt))),
                                         mkU8(rs)));

                        assign(t5, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                               binop(Iop_Sar32,
                                                     mkexpr(t4),
                                                     mkU8(16)),
                                               mkU32(0))));
                        assign(t6, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                              binop(Iop_Sar32,
                                                    mkexpr(t4),
                                                    mkU8(16)),
                                              mkU32(0xffffffff))));
                        assign(t7, binop(Iop_And32,
                                         mkexpr(t5),
                                         mkexpr(t6)));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t7),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t7),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       binop(Iop_And32,
                                                             getIReg(rt),
                                                             mkU32(0x80000000)),
                                                       binop(Iop_Shl32,
                                                             binop(Iop_And32,
                                                                   mkexpr(t4),
                                                                   mkU32(0x00008000)),
                                                             mkU8(16))
                                                      ),
                                                 getDSPControl(),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000))));
                        putIReg(rd, binop(Iop_16HLto32,
                                          unop(Iop_32to16, mkexpr(t4)),
                                          unop(Iop_32to16, mkexpr(t0))));
                     }
                     break;
                  }
                  case 0x9: {  
                     DIP("shra.ph r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        assign(t0, binop(Iop_Sar32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32to16, getIReg(rt))),
                                         mkU8(rs)));
                        assign(t1, binop(Iop_Sar32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32HIto16, getIReg(rt))),
                                         mkU8(rs)));
                        putIReg(rd, binop(Iop_16HLto32,
                                          unop(Iop_32to16, mkexpr(t1)),
                                          unop(Iop_32to16, mkexpr(t0))));
                     }
                     break;
                  }
                  case 0xA: {  
                     DIP("shllv.ph r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I32);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x0f)));

                     
                     assign(t2, binop(Iop_Shl32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x00000000)));
                     assign(t4, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0xffffffff)));
                     assign(t10, binop(Iop_And32,
                                       unop(Iop_1Sto32, mkexpr(t3)),
                                       unop(Iop_1Sto32, mkexpr(t4))));
                     assign(t5, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0x00008000)),
                                      mkU8(15)));
                     assign(t12, binop(Iop_CmpEQ32,
                                       mkexpr(t5),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   mkexpr(t2),
                                                   mkU32(0x00008000)),
                                             mkU8(15))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t10),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              IRExpr_ITE(mkexpr(t12),
                                                         getDSPControl(),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x400000)))
                                             ));
                     
                     assign(t6, binop(Iop_Shl32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     assign(t7, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t6))),
                                      mkU32(0x00000000)));
                     assign(t8, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t6))),
                                      mkU32(0xffffffff)));
                     assign(t11, binop(Iop_And32,
                                       unop(Iop_1Sto32, mkexpr(t7)),
                                       unop(Iop_1Sto32, mkexpr(t8))));

                     assign(t9, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0x80000000)),
                                      mkU8(31)));
                     assign(t13, binop(Iop_CmpEQ32,
                                       mkexpr(t9),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   mkexpr(t6),
                                                   mkU32(0x00008000)),
                                             mkU8(15))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t11),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              IRExpr_ITE(mkexpr(t13),
                                                         getDSPControl(),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x400000)))
                                             ));

                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t6)),
                                       unop(Iop_32to16, mkexpr(t2))));
                     break;
                  }
                  case 0xB: {  
                     DIP("shrav.ph r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x0f)));
                     assign(t1, binop(Iop_CmpEQ32, mkexpr(t0), mkU32(0x0)));
                     assign(t2, binop(Iop_Sar32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));
                     assign(t3, binop(Iop_Sar32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));
                     putIReg(rd,
                             binop(Iop_16HLto32,
                                   IRExpr_ITE(mkexpr(t1),
                                              unop(Iop_32HIto16, getIReg(rt)),
                                              unop(Iop_32to16, mkexpr(t3))),
                                   IRExpr_ITE(mkexpr(t1),
                                              unop(Iop_32to16, getIReg(rt)),
                                              unop(Iop_32to16, mkexpr(t2)))));
                     break;
                  }
                  case 0xC: {  
                     DIP("shll_s.ph r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I32);
                     t12 = newTemp(Ity_I32);
                     t13 = newTemp(Ity_I32);
                     t14 = newTemp(Ity_I32);

                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        
                        assign(t0, binop(Iop_Shl32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32to16, getIReg(rt))),
                                         mkU8(rs)));

                        assign(t1, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                               binop(Iop_Sar32,
                                                     mkexpr(t0),
                                                     mkU8(16)),
                                               mkU32(0))));
                        assign(t2, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                              binop(Iop_Sar32,
                                                    mkexpr(t0),
                                                    mkU8(16)),
                                              mkU32(0xffffffff))));
                        assign(t3, binop(Iop_And32,
                                         mkexpr(t1),
                                         mkexpr(t2)));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t3),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       binop(Iop_And32,
                                                             getIReg(rt),
                                                             mkU32(0x00008000)),
                                                       binop(Iop_And32,
                                                             mkexpr(t0),
                                                             mkU32(0x00008000))
                                                      ),
                                                 getDSPControl(),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000))));
                        assign(t8,
                               IRExpr_ITE(binop(Iop_CmpEQ32,
                                                mkexpr(t3),
                                                mkU32(0x1)),
                                          IRExpr_ITE(binop(Iop_CmpEQ32,
                                                           binop(Iop_And32,
                                                                 getIReg(rt),
                                                                 mkU32(0x8000)),
                                                           mkU32(0)),
                                                     mkU32(0x00007fff),
                                                     mkU32(0x00008000)),
                                          binop(Iop_And32,
                                                mkexpr(t0),
                                                mkU32(0x0000ffff))));
                        assign(t10,
                               IRExpr_ITE(binop(Iop_CmpEQ32,
                                                binop(Iop_And32,
                                                      getIReg(rt),
                                                      mkU32(0x00008000)),
                                                binop(Iop_And32,
                                                      mkexpr(t0),
                                                      mkU32(0x00008000))),
                                          mkexpr(t8),
                                          IRExpr_ITE(binop(Iop_CmpEQ32,
                                                           binop(Iop_And32,
                                                                 getIReg(rt),
                                                                 mkU32(0x8000)),
                                                           mkU32(0)),
                                                     mkU32(0x00007fff),
                                                     mkU32(0x00008000))));
                        
                        assign(t4, binop(Iop_Shl32,
                                         unop(Iop_16Sto32,
                                              unop(Iop_32HIto16, getIReg(rt))),
                                         mkU8(rs)));

                        assign(t5, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                               binop(Iop_Sar32,
                                                     mkexpr(t4),
                                                     mkU8(16)),
                                               mkU32(0))));
                        assign(t6, unop(Iop_1Uto32,
                                        binop(Iop_CmpNE32,
                                              binop(Iop_Sar32,
                                                    mkexpr(t4),
                                                    mkU8(16)),
                                              mkU32(0xffffffff))));
                        assign(t7, binop(Iop_And32,
                                         mkexpr(t5),
                                         mkexpr(t6)));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t7),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       mkexpr(t7),
                                                       mkU32(0x1)),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000)),
                                                 getDSPControl()));
                        assign(t12, binop(Iop_Shl32,
                                          binop(Iop_And32,
                                                mkexpr(t4),
                                                mkU32(0x8000)),
                                          mkU8(16)));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       binop(Iop_And32,
                                                             getIReg(rt),
                                                             mkU32(0x80000000)),
                                                       mkexpr(t12)),
                                                 getDSPControl(),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000))));
                        assign(t13, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                     binop(Iop_And32,
                                                           getIReg(rt),
                                                           mkU32(0x80000000)),
                                                     mkU32(0)),
                                               mkU32(0x7fff0000),
                                               mkU32(0x80000000)));
                        assign(t9,
                               IRExpr_ITE(binop(Iop_CmpEQ32,
                                                mkexpr(t7),
                                                mkU32(0x1)),
                                          mkexpr(t13),
                                          binop(Iop_Shl32,
                                                binop(Iop_And32,
                                                      mkexpr(t4),
                                                      mkU32(0x0000ffff)),
                                                mkU8(16))));
                        assign(t14, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                     binop(Iop_And32,
                                                           getIReg(rt),
                                                           mkU32(0x80000000)),
                                                     mkU32(0)),
                                               mkU32(0x7fff0000),
                                               mkU32(0x80000000)));
                        assign(t11,
                               IRExpr_ITE(binop(Iop_CmpEQ32,
                                                binop(Iop_And32,
                                                      getIReg(rt),
                                                      mkU32(0x80000000)),
                                                binop(Iop_Shl32,
                                                      binop(Iop_And32,
                                                            mkexpr(t4),
                                                            mkU32(0x00008000)),
                                                      mkU8(16))),
                                          mkexpr(t9),
                                          mkexpr(t14)));
                        putIReg(rd, binop(Iop_Or32,
                                          mkexpr(t10),
                                          mkexpr(t11)));
                     }
                     break;
                  }
                  case 0xD: {  
                     DIP("shra.ph r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        assign(t0, binop(Iop_Sar32,
                                         binop(Iop_Add32,
                                               unop(Iop_16Sto32,
                                                    unop(Iop_32to16,
                                                         getIReg(rt))),
                                               binop(Iop_Shl32,
                                                     mkU32(0x1),
                                                     mkU8(rs-1))),
                                         mkU8(rs)));
                        assign(t1, binop(Iop_Sar32,
                                         binop(Iop_Add32,
                                               unop(Iop_16Sto32,
                                                    unop(Iop_32HIto16,
                                                         getIReg(rt))),
                                               binop(Iop_Shl32,
                                                     mkU32(0x1),
                                                     mkU8(rs-1))),
                                         mkU8(rs)));
                        putIReg(rd, binop(Iop_16HLto32,
                                          unop(Iop_32to16, mkexpr(t1)),
                                          unop(Iop_32to16, mkexpr(t0))));
                     }
                     break;
                  }
                  case 0xE: {  
                     DIP("shllv_s.ph r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I32);
                     t12 = newTemp(Ity_I1);
                     t13 = newTemp(Ity_I1);
                     t14 = newTemp(Ity_I16);
                     t15 = newTemp(Ity_I16);
                     t16 = newTemp(Ity_I16);
                     t17 = newTemp(Ity_I16);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x0f)));

                     
                     assign(t2, binop(Iop_Shl32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     assign(t3, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0x00000000)));
                     assign(t4, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t2))),
                                      mkU32(0xffffffff)));
                     assign(t10, binop(Iop_And32,
                                       unop(Iop_1Sto32, mkexpr(t3)),
                                       unop(Iop_1Sto32, mkexpr(t4))));
                     assign(t5, binop(Iop_Shr32,
                                       binop(Iop_And32,
                                             getIReg(rt),
                                             mkU32(0x00008000)),
                                       mkU8(15)));
                     assign(t12, binop(Iop_CmpEQ32,
                                       mkexpr(t5),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   mkexpr(t2),
                                                   mkU32(0x00008000)),
                                             mkU8(15))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t10),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              IRExpr_ITE(mkexpr(t12),
                                                         getDSPControl(),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x400000)))
                                             ));
                     assign(t14, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t5),
                                                  mkU32(0x0)),
                                            mkU16(0x8000),
                                            mkU16(0x7fff)));
                     assign(t15, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t10),
                                                  mkU32(0x0)),
                                            mkexpr(t14),
                                            IRExpr_ITE(mkexpr(t12),
                                                       unop(Iop_32to16,
                                                            mkexpr(t2)),
                                                       mkexpr(t14))));
                     
                     assign(t6, binop(Iop_Shl32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     assign(t7, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t6))),
                                      mkU32(0x00000000)));
                     assign(t8, binop(Iop_CmpNE32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, mkexpr(t6))),
                                      mkU32(0xffffffff)));
                     assign(t11, binop(Iop_And32,
                                       unop(Iop_1Sto32, mkexpr(t7)),
                                       unop(Iop_1Sto32, mkexpr(t8))));

                     assign(t9, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0x80000000)),
                                      mkU8(31)));
                     assign(t13, binop(Iop_CmpEQ32,
                                       mkexpr(t9),
                                       binop(Iop_Shr32,
                                             binop(Iop_And32,
                                                   mkexpr(t6),
                                                   mkU32(0x00008000)),
                                             mkU8(15))));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t11),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              IRExpr_ITE(mkexpr(t13),
                                                         getDSPControl(),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x400000)))
                                             ));

                     assign(t16, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t9),
                                                  mkU32(0x0)),
                                            mkU16(0x8000),
                                            mkU16(0x7fff)));
                     assign(t17, IRExpr_ITE(binop(Iop_CmpNE32,
                                                  mkexpr(t11),
                                                  mkU32(0x0)),
                                            mkexpr(t16),
                                            IRExpr_ITE(mkexpr(t13),
                                                       unop(Iop_32to16,
                                                            mkexpr(t6)),
                                                       mkexpr(t16))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t17), mkexpr(t15)));
                     break;
                  }
                  case 0xF: {  
                     DIP("shrav_r.ph r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x0f)));
                     assign(t1, binop(Iop_CmpEQ32, mkexpr(t0), mkU32(0x0)));
                     assign(t2, unop(Iop_32to8,
                                     binop(Iop_Sub32, mkexpr(t0), mkU32(1))));

                     assign(t3, binop(Iop_Sar32,
                                      binop(Iop_Add32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16, getIReg(rt))),
                                            binop(Iop_Shl32,
                                                  mkU32(0x1),
                                                  mkexpr(t2))),
                                      unop(Iop_32to8, mkexpr(t0))));
                     assign(t4, binop(Iop_Sar32,
                                      binop(Iop_Add32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rt))),
                                            binop(Iop_Shl32,
                                                  mkU32(0x1),
                                                  mkexpr(t2))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       IRExpr_ITE(mkexpr(t1),
                                                  unop(Iop_32HIto16,
                                                       getIReg(rt)),
                                                  unop(Iop_32to16,
                                                       mkexpr(t4))),
                                       IRExpr_ITE(mkexpr(t1),
                                                  unop(Iop_32to16, getIReg(rt)),
                                                  unop(Iop_32to16,
                                                       mkexpr(t3)))));
                     break;
                  }
                  case 0x14: {  
                     DIP("shll_s.w r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);

                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        assign(t0, binop(Iop_Sar32,
                                         binop(Iop_And32,
                                               getIReg(rt),
                                               binop(Iop_Sar32,
                                                     mkU32(0x80000000),
                                                     mkU8(rs-1))),
                                         mkU8(32-rs)));

                        assign(t1, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    binop(Iop_And32,
                                                          getIReg(rt),
                                                          mkU32(0x80000000)),
                                                    mkU32(0x0)),
                                              mkU32(0x7fffffff),
                                              mkU32(0x80000000)));

                        assign(t2, binop(Iop_Shl32, getIReg(rt), mkU8(rs)));
                        assign(t3, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    binop(Iop_And32,
                                                          getIReg(rt),
                                                          mkU32(0x80000000)),
                                                    binop(Iop_And32,
                                                          mkexpr(t2),
                                                          mkU32(0x80000000))),
                                              mkexpr(t2),
                                              mkexpr(t1)));

                        assign(t4, IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t0),
                                                    mkU32(0x0)),
                                              IRExpr_ITE(binop(Iop_CmpNE32,
                                                               mkexpr(t0),
                                                               mkU32(0xffffffff)
                                                              ),
                                                         mkexpr(t1),
                                                         mkexpr(t3)),
                                              mkexpr(t3)));
                        assign(t5, IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t0),
                                                    mkU32(0xffffffff)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x400000)),
                                              getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                       mkexpr(t0),
                                                       mkU32(0x0)),
                                                 mkexpr(t5),
                                                 getDSPControl()));
                        putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                       binop(Iop_And32,
                                                             getIReg(rt),
                                                             mkU32(0x80000000)),
                                                       binop(Iop_And32,
                                                             mkexpr(t2),
                                                             mkU32(0x80000000))
                                                            ),
                                                 getDSPControl(),
                                                 binop(Iop_Or32,
                                                       getDSPControl(),
                                                       mkU32(0x400000))));
                        putIReg(rd, mkexpr(t4));
                     }
                     break;
                  }
                  case 0x15: {  
                     DIP("shra_r.w r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     if (0 == rs) {
                        putIReg(rd, getIReg(rt));
                     } else {
                        putIReg(rd, binop(Iop_Add32,
                                          binop(Iop_Sar32,
                                                getIReg(rt), mkU8(rs)),
                                          binop(Iop_Shr32,
                                                binop(Iop_And32,
                                                      getIReg(rt),
                                                      binop(Iop_Shl32,
                                                            mkU32(0x1),
                                                            mkU8(rs-1))),
                                                mkU8(rs-1))));
                     }
                     break;
                  }
                  case 0x16: {  
                     DIP("shllv_s.w r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I64);
                     t4 = newTemp(Ity_I1);
                     t5 = newTemp(Ity_I1);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I32);

                     
                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x1f)));
                     assign(t1, binop(Iop_CmpEQ32, mkexpr(t0), mkU32(0x0)));

                     
                     assign(t2, binop(Iop_Shr32,
                                      binop(Iop_And32,
                                            getIReg(rt),
                                            mkU32(0x80000000)),
                                      mkU8(31)));
                     
                     assign(t3, binop(Iop_Shl64,
                                      unop(Iop_32Sto64, getIReg(rt)),
                                      unop(Iop_32to8, mkexpr(t0))));
                     assign(t4, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32, mkexpr(t3)),
                                      mkU32(0x00000000)));
                     assign(t5, binop(Iop_CmpNE32,
                                      unop(Iop_64HIto32, mkexpr(t3)),
                                      mkU32(0xffffffff)));
                     assign(t6, binop(Iop_And32,
                                      unop(Iop_1Uto32, mkexpr(t4)),
                                      unop(Iop_1Uto32, mkexpr(t5))));
                     assign(t7, binop(Iop_CmpEQ32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  getIReg(rt),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t3)),
                                                  mkU32(0x80000000)),
                                            mkU8(31))));

                     putDSPControl(IRExpr_ITE(unop(Iop_32to1, mkexpr(t6)),
                                                   binop(Iop_Or32,
                                                         getDSPControl(),
                                                         mkU32(0x400000)),
                                              IRExpr_ITE(mkexpr(t7),
                                                         getDSPControl(),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x400000)))
                                             ));

                     assign(t8, IRExpr_ITE(unop(Iop_32to1,
                                                mkexpr(t2)),
                                           mkU32(0x80000000),
                                           mkU32(0x7fffffff)));
                     putIReg(rd, IRExpr_ITE(unop(Iop_32to1, mkexpr(t6)),
                                            IRExpr_ITE(unop(Iop_32to1,
                                                            mkexpr(t2)),
                                                       mkU32(0x80000000),
                                                       mkU32(0x7fffffff)),
                                            IRExpr_ITE(mkexpr(t7),
                                                       unop(Iop_64to32,
                                                            mkexpr(t3)),
                                                       mkexpr(t8))));
                     break;
                  }
                  case 0x17: {  
                     DIP("shrav_r.w r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x1f)));
                     assign(t1, binop(Iop_CmpEQ32, mkexpr(t0), mkU32(0x0)));
                     assign(t2, unop(Iop_32to8,
                                     binop(Iop_Sub32, mkexpr(t0), mkU32(1))));

                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            getIReg(rt),
                                            binop(Iop_Sar32,
                                                  binop(Iop_Add32,
                                                        binop(Iop_Sar32,
                                                              getIReg(rt),
                                                              mkexpr(t2)),
                                                        mkU32(0x1)),
                                                  mkU8(1))));
                     break;
                  }
                  case 0x19: {  
                     DIP("shrl.ph r%d, r%d, %d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     assign(t0, binop(Iop_Shr32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU8(rs)));
                     assign(t1, binop(Iop_Shr32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU8(rs)));
                     putIReg(rd, binop(Iop_16HLto32,
                                       unop(Iop_32to16, mkexpr(t1)),
                                       unop(Iop_32to16, mkexpr(t0))));
                     break;
                  }
                  case 0x1B: {  
                     DIP("shrlv.ph r%d, r%d, r%d", rd, rt, rs);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I16);
                     t5 = newTemp(Ity_I16);

                     assign(t0, binop(Iop_And32, getIReg(rs), mkU32(0x0f)));
                     assign(t1, binop(Iop_CmpEQ32, mkexpr(t0), mkU32(0x0)));

                     assign(t2, binop(Iop_Shr32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));
                     assign(t3, binop(Iop_Shr32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      unop(Iop_32to8, mkexpr(t0))));

                     assign(t4, IRExpr_ITE(mkexpr(t1),
                                           unop(Iop_32HIto16, getIReg(rt)),
                                           unop(Iop_32to16, mkexpr(t3))));
                     assign(t5, IRExpr_ITE(mkexpr(t1),
                                           unop(Iop_32to16, getIReg(rt)),
                                           unop(Iop_32to16, mkexpr(t2))));
                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t4), mkexpr(t5)));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x18: {  
               switch(sa) {
                  case 0x00: {  
                     DIP("adduh.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_HAdd8Ux4, getIReg(rs), getIReg(rt)));

                     putIReg(rd, mkexpr(t0));
                     break;
                  }
                  case 0x1: {  
                     DIP("subuh.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);

                     assign(t0, binop(Iop_HSub8Ux4, getIReg(rs), getIReg(rt)));

                     putIReg(rd, mkexpr(t0));
                     break;
                  }
                  case 0x02: {  
                     DIP("adduh_r.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I8);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I8);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I8);
                     t9 = newTemp(Ity_I32);
                     t10 = newTemp(Ity_I32);
                     t11 = newTemp(Ity_I8);

                     assign(t0, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rs)))));
                     assign(t1, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t2, unop(Iop_16to8,
                                     unop(Iop_32to16,
                                          binop(Iop_Shr32,
                                                binop(Iop_Add32,
                                                      binop(Iop_Add32,
                                                            mkexpr(t0),
                                                            mkexpr(t1)),
                                                      mkU32(0x00000001)),
                                                mkU8(0x01)))));

                     assign(t3, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rs)))));
                     assign(t4, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t5, unop(Iop_16to8,
                                     unop(Iop_32to16,
                                          binop(Iop_Shr32,
                                                binop(Iop_Add32,
                                                      binop(Iop_Add32,
                                                            mkexpr(t3),
                                                            mkexpr(t4)),
                                                      mkU32(0x00000001)),
                                                mkU8(0x01)))));

                     assign(t6, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rs)))));
                     assign(t7, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t8, unop(Iop_16to8,
                                     unop(Iop_32to16,
                                          binop(Iop_Shr32,
                                                binop(Iop_Add32,
                                                      binop(Iop_Add32,
                                                            mkexpr(t7),
                                                            mkexpr(t6)),
                                                      mkU32(0x00000001)),
                                                mkU8(0x01)))));

                     assign(t9, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32HIto16, getIReg(rs)))));
                     assign(t10, unop(Iop_8Uto32,
                                      unop(Iop_16HIto8,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t11, unop(Iop_16to8,
                                      unop(Iop_32to16,
                                           binop(Iop_Shr32,
                                                 binop(Iop_Add32,
                                                       binop(Iop_Add32,
                                                             mkexpr(t9),
                                                             mkexpr(t10)),
                                                       mkU32(0x00000001)),
                                                 mkU8(0x01)))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       binop(Iop_8HLto16,
                                             mkexpr(t11), mkexpr(t8)),
                                       binop(Iop_8HLto16,
                                             mkexpr(t5), mkexpr(t2))));
                     break;
                  }
                  case 0x3: {  
                     DIP("subuh_r.qb r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I32);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I8);
                     t10 = newTemp(Ity_I8);
                     t11 = newTemp(Ity_I8);
                     t12 = newTemp(Ity_I8);

                     
                     assign(t1, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rs)))));
                     assign(t2, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rs)))));
                     assign(t3, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rs)))));
                     assign(t4, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32HIto16, getIReg(rs)))));

                     assign(t5, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t6, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32to16, getIReg(rt)))));
                     assign(t7, unop(Iop_8Uto32,
                                     unop(Iop_16to8,
                                          unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t8, unop(Iop_8Uto32,
                                     unop(Iop_16HIto8,
                                          unop(Iop_32HIto16, getIReg(rt)))));

                     
                     assign(t9, unop(Iop_16to8,
                                     unop(Iop_32to16,
                                          binop(Iop_Shr32,
                                                binop(Iop_Add32,
                                                      binop(Iop_Sub32,
                                                            mkexpr(t1),
                                                            mkexpr(t5)),
                                                      mkU32(0x00000001)),
                                                mkU8(0x01)))));
                     assign(t10, unop(Iop_16to8,
                                      unop(Iop_32to16,
                                           binop(Iop_Shr32,
                                                 binop(Iop_Add32,
                                                       binop(Iop_Sub32,
                                                             mkexpr(t2),
                                                             mkexpr(t6)),
                                                       mkU32(0x00000001)),
                                                 mkU8(0x01)))));
                     assign(t11, unop(Iop_16to8,
                                      unop(Iop_32to16,
                                            binop(Iop_Shr32,
                                                  binop(Iop_Add32,
                                                        binop(Iop_Sub32,
                                                              mkexpr(t3),
                                                              mkexpr(t7)),
                                                        mkU32(0x00000001)),
                                                  mkU8(0x01)))));
                     assign(t12, unop(Iop_16to8,
                                      unop(Iop_32to16,
                                           binop(Iop_Shr32,
                                                 binop(Iop_Add32,
                                                       binop(Iop_Sub32,
                                                             mkexpr(t4),
                                                             mkexpr(t8)),
                                                       mkU32(0x00000001)),
                                                 mkU8(0x01)))));

                     putIReg(rd, binop(Iop_16HLto32,
                                       binop(Iop_8HLto16,
                                             mkexpr(t12), mkexpr(t11)),
                                       binop(Iop_8HLto16,
                                             mkexpr(t10), mkexpr(t9))));
                     break;
                  }
                  case 0x8: {  
                     DIP("addqh.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I16);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I16);

                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));
                     assign(t1, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 mkexpr(t0),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t3, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 mkexpr(t2),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));
                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t3), mkexpr(t1)));
                     break;
                  }
                  case 0x9: {  
                     DIP("subqh.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);

                     putIReg(rd, binop(Iop_HSub16Sx2,
                                       getIReg(rs), getIReg(rt)));
                     break;
                  }
                  case 0xA: {
                     DIP("addqh_r.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I16);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I16);

                     assign(t0, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));
                     assign(t1, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 binop(Iop_Add32,
                                                       mkexpr(t0),
                                                       mkU32(0x1)),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));
                     assign(t2, binop(Iop_Add32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t3, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 binop(Iop_Add32,
                                                       mkexpr(t2),
                                                       mkU32(0x1)),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t3), mkexpr(t1)));
                     break;
                  }
                  case 0xB: {  
                     DIP("subqh_r.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I16);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I16);

                     assign(t0, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));
                     assign(t1, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 binop(Iop_Add32,
                                                       mkexpr(t0),
                                                       mkU32(0x1)),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));
                     assign(t2, binop(Iop_Sub32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt)))));
                     assign(t3, unop(Iop_32to16,
                                     binop(Iop_Shr32,
                                           binop(Iop_And32,
                                                 binop(Iop_Add32,
                                                       mkexpr(t2),
                                                       mkU32(0x1)),
                                                 mkU32(0x0001fffe)),
                                           mkU8(0x1))));

                     putIReg(rd, binop(Iop_16HLto32, mkexpr(t3), mkexpr(t1)));
                     break;
                  }
                  case 0xC: {  
                     DIP("mul.ph r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);

                     assign(t0,
                            binop(Iop_Mul32,
                                  unop(Iop_16Sto32,
                                       unop(Iop_32HIto16, getIReg(rs))),
                                  unop(Iop_16Sto32,
                                       unop(Iop_32HIto16, getIReg(rt)))));
                     
                     putDSPControl(IRExpr_ITE(unop(Iop_Not1,
                                                   binop(Iop_CmpLE32S,
                                                         mkexpr(t0),
                                                         mkU32(0x7FFF))),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00200000)),
                                              IRExpr_ITE(binop(Iop_CmpLT32S,
                                                               mkexpr(t0),
                                                               mkU32(0xFFFF8000)
                                                             ),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl())));

                     assign(t1,
                            binop(Iop_Mul32,
                                  unop(Iop_16Sto32,
                                       unop(Iop_32to16, getIReg(rs))),
                                  unop(Iop_16Sto32,
                                       unop(Iop_32to16, getIReg(rt)))));
                     
                     putDSPControl(IRExpr_ITE(unop(Iop_Not1,
                                                   binop(Iop_CmpLE32S,
                                                         mkexpr(t1),
                                                         mkU32(0x7FFF))),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00200000)),
                                              IRExpr_ITE(binop(Iop_CmpLT32S,
                                                               mkexpr(t1),
                                                               mkU32(0xFFFF8000)
                                                              ),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl())));

                     assign(t2, binop(Iop_16HLto32,
                                      unop(Iop_32to16, mkexpr(t0)),
                                      unop(Iop_32to16, mkexpr(t1))));
                     putIReg(rd, mkexpr(t2));
                     break;
                  }
                  case 0xE: {  
                     DIP("mul_s.ph r%d r%d, r%d", rd, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);

                     
                     assign(t0,
                           binop(Iop_Mul32,
                                 unop(Iop_16Sto32,
                                      unop(Iop_32HIto16, getIReg(rs))),
                                 unop(Iop_16Sto32,
                                      unop(Iop_32HIto16, getIReg(rt)))));

                     assign(t1,
                            IRExpr_ITE(unop(Iop_Not1,
                                            binop(Iop_CmpLE32S,
                                                  mkexpr(t0),
                                                  mkU32(0x7FFF))),
                                       mkU32(0x00007FFF),
                                       IRExpr_ITE(binop(Iop_CmpLT32S,
                                                        mkexpr(t0),
                                                        mkU32(0xFFFF8000)),
                                                  mkU32(0xFFFF8000),
                                                  mkexpr(t0))));

                     
                     putDSPControl(IRExpr_ITE(unop(Iop_Not1,
                                                   binop(Iop_CmpLE32S,
                                                         mkexpr(t0),
                                                         mkU32(0x7FFF))),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00200000)),
                                              IRExpr_ITE(binop(Iop_CmpLT32S,
                                                               mkexpr(t0),
                                                               mkU32(0xFFFF8000)
                                                              ),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl())));

                     
                     assign(t2, binop(Iop_Mul32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt)))));

                     assign(t3, IRExpr_ITE(unop(Iop_Not1,
                                                binop(Iop_CmpLE32S,
                                                      mkexpr(t2),
                                                      mkU32(0x7FFF))),
                                           mkU32(0x00007FFF),
                                           IRExpr_ITE(binop(Iop_CmpLT32S,
                                                            mkexpr(t2),
                                                            mkU32(0xFFFF8000)),
                                                      mkU32(0xFFFF8000),
                                                      mkexpr(t2))));

                     
                     putDSPControl(IRExpr_ITE(unop(Iop_Not1,
                                                   binop(Iop_CmpLE32S,
                                                         mkexpr(t2),
                                                         mkU32(0x7FFF))),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    mkU32(0x00200000)),
                                              IRExpr_ITE(binop(Iop_CmpLT32S,
                                                               mkexpr(t2),
                                                               mkU32(0xFFFF8000)
                                                              ),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl())));

                     assign(t4, binop(Iop_16HLto32,
                                      unop(Iop_32to16, mkexpr(t1)),
                                      unop(Iop_32to16, mkexpr(t3))));
                     putIReg(rd, mkexpr(t4));
                     break;
                  }
                  case 0x10: {  
                     DIP("addqh.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);

                     assign(t0, binop(Iop_Add64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));
                     assign(t1, binop(Iop_And64,
                                      mkexpr(t0),
                                      mkU64(0x00000001fffffffeULL)));
                     putIReg(rd, unop(Iop_64to32,
                                      binop(Iop_Shr64, mkexpr(t1), mkU8(0x1))));
                     break;
                  }
                  case 0x11: {  
                     DIP("subqh.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);

                     assign(t0, binop(Iop_Sub64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));
                     assign(t1, binop(Iop_And64,
                                      mkexpr(t0),
                                      mkU64(0x00000001fffffffeULL)));
                     putIReg(rd, unop(Iop_64to32,
                                      binop(Iop_Shr64, mkexpr(t1), mkU8(0x1))));
                     break;
                  }
                  case 0x12: {  
                     DIP("addqh_r.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0, binop(Iop_Add64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));
                     assign(t1, binop(Iop_Add64,
                                      mkexpr(t0),
                                      mkU64(0x0000000000000001ULL)));
                     assign(t2, binop(Iop_And64,
                                      mkexpr(t1),
                                      mkU64(0x00000001fffffffeULL)));
                     putIReg(rd, unop(Iop_64to32,
                                      binop(Iop_Shr64, mkexpr(t2), mkU8(0x1))));
                     break;
                  }
                  case 0x13: {  
                     DIP("subqh_r.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0, binop(Iop_Sub64,
                                      unop(Iop_32Sto64, getIReg(rs)),
                                      unop(Iop_32Sto64, getIReg(rt))));
                     assign(t1, binop(Iop_Add64,
                                      mkexpr(t0),
                                      mkU64(0x0000000000000001ULL)));
                     assign(t2, binop(Iop_And64,
                                      mkexpr(t1),
                                      mkU64(0x00000001fffffffeULL)));
                     putIReg(rd, unop(Iop_64to32,
                                      binop(Iop_Shr64, mkexpr(t2), mkU8(0x1))));
                     break;
                  }
                  case 0x16: {  
                     DIP("mulq_s.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t0, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            getIReg(rt), getIReg(rs)),
                                      mkU8(0x1)));
                     assign(t1, binop(Iop_CmpEQ32,
                                      getIReg(rt), mkU32(0x80000000)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      getIReg(rs), mkU32(0x80000000)));

                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              IRExpr_ITE(mkexpr(t2),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(mkexpr(t2),
                                                       mkU32(0x7fffffff),
                                                       unop(Iop_64HIto32,
                                                            mkexpr(t0))),
                                            unop(Iop_64HIto32, mkexpr(t0))));
                     break;
                  }
                  case 0x17: {  
                     DIP("mulq_rs.w r%d, r%d, r%d", rd, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I1);

                     assign(t0, binop(Iop_Add64,
                                      binop(Iop_Shl64,
                                            binop(Iop_MullS32,
                                                  getIReg(rt),
                                                  getIReg(rs)),
                                            mkU8(0x1)),
                                      mkU64(0x0000000080000000ULL)));
                     assign(t1,
                            binop(Iop_CmpEQ32, getIReg(rt), mkU32(0x80000000)));
                     assign(t2,
                            binop(Iop_CmpEQ32, getIReg(rs), mkU32(0x80000000)));
                     putDSPControl(IRExpr_ITE(mkexpr(t1),
                                              IRExpr_ITE(mkexpr(t2),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               mkU32(0x00200000)
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                            IRExpr_ITE(mkexpr(t2),
                                                       mkU32(0x7fffffff),
                                                       unop(Iop_64HIto32,
                                                            mkexpr(t0))),
                                            unop(Iop_64HIto32, mkexpr(t0))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x30: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("dpa.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t1,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t2,
                            binop(Iop_Add64,
                                  getAcc(ac),
                                  binop(Iop_Add64, mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, mkexpr(t2));
                     break;
                  }
                  case 0x1: {  
                     DIP("dps.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t1,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t2,
                            binop(Iop_Sub64,
                                  getAcc(ac),
                                  binop(Iop_Add64, mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, mkexpr(t2));
                     break;
                  }
                  case 0x2: {  
                     DIP("mulsa.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);

                     assign(t4, getAcc(ac));
                     assign(t0, binop(Iop_Mul32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32to16, getIReg(rs)))));
                     assign(t1, binop(Iop_Mul32,
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      unop(Iop_16Sto32,
                                           unop(Iop_32HIto16, getIReg(rs)))));
                     assign(t2, binop(Iop_Sub32, mkexpr(t1), mkexpr(t0)));
                     putAcc(ac, binop(Iop_Add64,
                                      mkexpr(t4),
                                      unop(Iop_32Sto64, mkexpr(t2))));
                     break;
                  }
                  case 0x3: {  
                     DIP("dpau.h.qbl ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I64);
                     t3 = newTemp(Ity_I64);

                     assign(t0,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t1,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t2,
                            unop(Iop_32Uto64,
                                 binop(Iop_Add32,
                                       mkexpr(t0),
                                       mkexpr(t1))));
                     assign(t3,
                            binop(Iop_Add64, getAcc(ac), mkexpr(t2)));
                     putAcc(ac, mkexpr(t3));
                     break;
                  }
                  case 0x4: {  
                     DIP("dpaq_s.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16, getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16, getIReg(rt)))
                                           ),
                                      mkU8(0x1)));
                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t8,
                            IRExpr_ITE(mkexpr(t6),
                                       IRExpr_ITE(mkexpr(t7),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t5)),
                                       mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              IRExpr_ITE(mkexpr(t7),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t9, binop(Iop_Add64,
                                      binop(Iop_Add64, mkexpr(t4), mkexpr(t8)),
                                      mkexpr(t0)));
                     putAcc(ac, mkexpr(t9));
                     break;
                  }
                  case 0x5: {  
                     DIP("dpsq_s.w.ph ac%d r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5,
                            binop(Iop_Shl64,
                                  binop(Iop_MullS32,
                                        unop(Iop_16Sto32,
                                             unop(Iop_32to16, getIReg(rs))),
                                        unop(Iop_16Sto32,
                                             unop(Iop_32to16, getIReg(rt)))),
                                  mkU8(0x1)));
                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t8,
                            IRExpr_ITE(mkexpr(t6),
                                       IRExpr_ITE(mkexpr(t7),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t5)),
                                       mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              IRExpr_ITE(mkexpr(t7),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t9,
                            binop(Iop_Sub64,
                                  mkexpr(t0),
                                  binop(Iop_Add64, mkexpr(t4), mkexpr(t8))));
                     putAcc(ac, mkexpr(t9));
                     break;
                  }
                  case 0x6: {  
                     DIP("mulsaq_s.w.ph ac%d r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I32);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I64);
                     t8 = newTemp(Ity_I32);
                     t9 = newTemp(Ity_I32);

                     assign(t0, unop(Iop_16Sto32,
                                     unop(Iop_32HIto16, getIReg(rs))));
                     assign(t1, unop(Iop_16Sto32,
                                     unop(Iop_32HIto16, getIReg(rt))));

                     assign(t8, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 unop(Iop_16Uto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rs))),
                                                 mkU32(0x8000))),
                                    unop(Iop_1Sto32,
                                         binop(Iop_CmpEQ32,
                                               unop(Iop_16Uto32,
                                                    unop(Iop_32HIto16,
                                                         getIReg(rt))),
                                               mkU32(0x8000)))));
                     
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t8),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x00010000),
                                                          mkU8(ac))),
                                              getDSPControl()));

                     
                     assign(t2,
                            IRExpr_ITE(binop(Iop_CmpNE32,
                                             mkexpr(t8), mkU32(0x0)),
                                       mkU32(0x7FFFFFFF),
                                       binop(Iop_Shl32,
                                             binop(Iop_Mul32,
                                                   mkexpr(t0), mkexpr(t1)),
                                             mkU8(1))));

                     assign(t3, unop(Iop_16Sto32,
                                     unop(Iop_32to16, getIReg(rs))));
                     assign(t4, unop(Iop_16Sto32,
                                     unop(Iop_32to16, getIReg(rt))));

                     assign(t9, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 unop(Iop_16Uto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rs))),
                                                 mkU32(0x8000))),
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 unop(Iop_16Uto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rt))),
                                                 mkU32(0x8000)))));
                     
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    mkexpr(t9),
                                                    mkU32(0x0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x00010000),
                                                          mkU8(ac))),
                                              getDSPControl()));
                     
                     assign(t5,
                            IRExpr_ITE(binop(Iop_CmpNE32,
                                             mkexpr(t9),
                                             mkU32(0x0)),
                                       mkU32(0x7FFFFFFF),
                                       binop(Iop_Shl32,
                                             binop(Iop_Mul32,
                                                   mkexpr(t3),
                                                   mkexpr(t4)),
                                             mkU8(1))));
                     
                     assign(t6,
                            binop(Iop_Sub64,
                                  unop(Iop_32Sto64, mkexpr(t2)),
                                  unop(Iop_32Sto64, mkexpr(t5))));
                     
                     assign(t7, binop(Iop_Add64, getAcc(ac), mkexpr(t6)));

                     putAcc(ac, mkexpr(t7));
                     break;
                  }
                  case 0x7: {  
                     DIP("dpau.h.qbr ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I64);
                     t3 = newTemp(Ity_I64);

                     assign(t0,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t1,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t2, unop(Iop_32Uto64,
                                     binop(Iop_Add32, mkexpr(t0), mkexpr(t1))));
                     assign(t3, binop(Iop_Add64, getAcc(ac), mkexpr(t2)));
                     putAcc(ac, mkexpr(t3));
                     break;
                  }
                  case 0x8: {  
                     DIP("dpax.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t1,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t2,
                            binop(Iop_Add64,
                                  getAcc(ac),
                                  binop(Iop_Add64, mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, mkexpr(t2));
                     break;
                  }
                  case 0x9: {  
                     DIP("dpsx.w.ph ac%d r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I64);

                     assign(t0,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t1,
                            unop(Iop_32Sto64,
                                 binop(Iop_Mul32,
                                       unop(Iop_16Sto32,
                                            unop(Iop_32to16, getIReg(rs))),
                                       unop(Iop_16Sto32,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t2,
                            binop(Iop_Sub64,
                                  getAcc(ac),
                                  binop(Iop_Add64, mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, mkexpr(t2));
                     break;
                  }
                  case 0xB: {  
                     DIP("dpsu.h.qbl ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I64);
                     t3 = newTemp(Ity_I64);

                     assign(t0,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t1,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32HIto16, getIReg(rt))))));
                     assign(t2,
                            unop(Iop_32Uto64,
                                 binop(Iop_Add32, mkexpr(t0), mkexpr(t1))));
                     assign(t3,
                            binop(Iop_Sub64, getAcc(ac), mkexpr(t2)));
                     putAcc(ac, mkexpr(t3));
                     break;
                  }
                  case 0xC: {  
                     DIP("dpaq_sa.l.w ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I64);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I1);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            getIReg(rs), getIReg(rt)),
                                      mkU8(0x1)));

                     assign(t2, binop(Iop_CmpEQ32,
                                      getIReg(rs),
                                      mkU32(0x80000000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      getIReg(rt),
                                      mkU32(0x80000000)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x7fffffffffffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5, binop(Iop_Add64,
                                      unop(Iop_32Uto64,
                                           unop(Iop_64to32, mkexpr(t0))),
                                      unop(Iop_32Uto64,
                                           unop(Iop_64to32, mkexpr(t4)))));
                     assign(t6,
                            binop(Iop_Add64,
                                  binop(Iop_Add64,
                                        unop(Iop_32Sto64,
                                             unop(Iop_64HIto32, mkexpr(t0))),
                                        unop(Iop_32Sto64,
                                             unop(Iop_64HIto32, mkexpr(t4)))),
                                  unop(Iop_32Uto64,
                                       binop(Iop_And32,
                                             unop(Iop_64HIto32, mkexpr(t5)),
                                             mkU32(0x1)))));
                     assign(t7, binop(Iop_32HLto64,
                                      unop(Iop_64to32, mkexpr(t6)),
                                      unop(Iop_64to32, mkexpr(t5))));
                     assign(t8, binop(Iop_CmpEQ32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t6)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t6)),
                                            mkU32(0x00000001))));
                     assign(t9, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32,
                                                 mkexpr(t6)),
                                            mkU32(0x00000001)),
                                      mkU32(0x1)));
                     putDSPControl(IRExpr_ITE(mkexpr(t8),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     putAcc(ac,
                            IRExpr_ITE(mkexpr(t8),
                                       mkexpr(t7),
                                       IRExpr_ITE(mkexpr(t9),
                                                  mkU64(0x8000000000000000ULL),
                                                  mkU64(0x7fffffffffffffffULL)))
                           );
                     break;
                  }
                  case 0xD: {  
                     DIP("dpsq_sa.l.w ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I64);
                     t7 = newTemp(Ity_I64);
                     t8 = newTemp(Ity_I1);
                     t9 = newTemp(Ity_I1);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            getIReg(rs), getIReg(rt)),
                                      mkU8(0x1)));

                     assign(t2, binop(Iop_CmpEQ32,
                                      getIReg(rs),
                                      mkU32(0x80000000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      getIReg(rt),
                                      mkU32(0x80000000)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x7fffffffffffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5, binop(Iop_Sub64,
                                      unop(Iop_32Uto64,
                                           unop(Iop_64to32, mkexpr(t0))),
                                      unop(Iop_32Uto64,
                                           unop(Iop_64to32, mkexpr(t4)))));
                     assign(t6, binop(Iop_Sub64,
                                      binop(Iop_Add64,
                                            unop(Iop_32Sto64,
                                                 unop(Iop_64HIto32, mkexpr(t0))
                                                ),
                                            unop(Iop_32Sto64,
                                                 unop(Iop_1Sto32,
                                                      binop(Iop_CmpLT32U,
                                                            unop(Iop_64to32,
                                                                 mkexpr(t0)),
                                                            unop(Iop_64to32,
                                                                mkexpr(t4)))))),
                                      unop(Iop_32Sto64,
                                           unop(Iop_64HIto32, mkexpr(t4)))));
                     assign(t7, binop(Iop_32HLto64,
                                      unop(Iop_64to32, mkexpr(t6)),
                                      unop(Iop_64to32, mkexpr(t5))));
                     assign(t8, binop(Iop_CmpEQ32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t6)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t6)),
                                            mkU32(0x00000001))));
                     assign(t9, binop(Iop_CmpEQ32,
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t6)),
                                            mkU32(0x00000001)),
                                      mkU32(0x1)));
                     putDSPControl(IRExpr_ITE(mkexpr(t8),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     putAcc(ac,
                            IRExpr_ITE(mkexpr(t8),
                                       mkexpr(t7),
                                       IRExpr_ITE(mkexpr(t9),
                                                  mkU64(0x8000000000000000ULL),
                                                  mkU64(0x7fffffffffffffffULL)))
                           );
                     break;
                  }
                  case 0xF: {  
                     DIP("dpsu.h.qbr ac%d r%d, r%d", ac, rs, rt);
                     vassert(!mode64);

                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I64);
                     t3 = newTemp(Ity_I64);

                     assign(t0,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16HIto8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t1,
                            binop(Iop_Mul32,
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rs)))),
                                  unop(Iop_8Uto32,
                                       unop(Iop_16to8,
                                            unop(Iop_32to16, getIReg(rt))))));
                     assign(t2, unop(Iop_32Uto64,
                                     binop(Iop_Add32, mkexpr(t0), mkexpr(t1))));
                     assign(t3, binop(Iop_Sub64, getAcc(ac), mkexpr(t2)));
                     putAcc(ac, mkexpr(t3));

                     break;
                  }
                  case 0x10: {  
                     DIP("maq_sa.w.phl ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));
                     assign(t1, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     assign(t5, binop(Iop_Add64, mkexpr(t0), mkexpr(t4)));

                     
                     assign(t6, binop(Iop_CmpEQ32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t5)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t5)),
                                            mkU32(1))));
                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     assign(t7,
                            IRExpr_ITE(mkexpr(t6),
                                       mkexpr(t5),
                                       IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        binop(Iop_And32,
                                                              unop(Iop_64HIto32,
                                                                   mkexpr(t5)),
                                                              mkU32(1)),
                                                        mkU32(0x0)),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkU64(0xffffffff80000000ULL)))
                           );
                     putAcc(ac, mkexpr(t7));
                     break;
                  }
                  case 0x12: {  
                     DIP("maq_sa.w.phr ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));
                     assign(t1, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));
                     assign(t5, binop(Iop_Add64, mkexpr(t0), mkexpr(t4)));

                     
                     assign(t6, binop(Iop_CmpEQ32,
                                      binop(Iop_Shr32,
                                            binop(Iop_And32,
                                                  unop(Iop_64to32, mkexpr(t5)),
                                                  mkU32(0x80000000)),
                                            mkU8(31)),
                                      binop(Iop_And32,
                                            unop(Iop_64HIto32, mkexpr(t5)),
                                            mkU32(1))));
                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     assign(t7,
                            IRExpr_ITE(mkexpr(t6),
                                       mkexpr(t5),
                                       IRExpr_ITE(binop(Iop_CmpEQ32,
                                                        binop(Iop_And32,
                                                              unop(Iop_64HIto32,
                                                                   mkexpr(t5)),
                                                              mkU32(1)),
                                                        mkU32(0x0)),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkU64(0xffffffff80000000ULL)))
                           );
                     putAcc(ac, mkexpr(t7));
                     break;
                  }
                  case 0x14: {  
                     DIP("maq_s.w.phl ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I64);

                     assign(t5, getAcc(ac));

                     assign(t0, unop(Iop_16Sto32,
                                     unop(Iop_32HIto16, getIReg(rs))));
                     assign(t1, unop(Iop_16Sto32,
                                     unop(Iop_32HIto16, getIReg(rt))));

                     assign(t2, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000))),
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t1),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000)))));

                     assign(t3, binop(Iop_CmpEQ32, mkexpr(t2), mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));

                     assign(t4, unop(Iop_64to32,
                                     binop(Iop_MullS32,
                                           mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Add64,
                                                 unop(Iop_32Sto64,
                                                      binop(Iop_Shl32,
                                                            mkexpr(t4),
                                                            mkU8(0x1))),
                                                 mkexpr(t5)),
                                           binop(Iop_Add64,
                                                 mkexpr(t5),
                                                 unop(Iop_32Sto64,
                                                      mkU32(0x7fffffff)))));
                     break;
                  }
                  case 0x16: {  
                     DIP("maq_s.w.phr ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I64);

                     assign(t5, getAcc(ac));

                     assign(t0, unop(Iop_16Sto32,
                                     unop(Iop_32to16, getIReg(rs))));
                     assign(t1, unop(Iop_16Sto32,
                                     unop(Iop_32to16, getIReg(rt))));

                     assign(t2, binop(Iop_And32,
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t0),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000))),
                                      unop(Iop_1Sto32,
                                           binop(Iop_CmpEQ32,
                                                 binop(Iop_And32,
                                                       mkexpr(t1),
                                                       mkU32(0xffff)),
                                                 mkU32(0x8000)))));

                     assign(t3, binop(Iop_CmpEQ32, mkexpr(t2), mkU32(0x0)));

                     putDSPControl(IRExpr_ITE(mkexpr(t3),
                                              getDSPControl(),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));

                     assign(t4, unop(Iop_64to32,
                                     binop(Iop_MullS32,
                                           mkexpr(t0), mkexpr(t1))));
                     putAcc(ac, IRExpr_ITE(mkexpr(t3),
                                           binop(Iop_Add64,
                                                 unop(Iop_32Sto64,
                                                      binop(Iop_Shl32,
                                                            mkexpr(t4),
                                                            mkU8(0x1))),
                                                 mkexpr(t5)),
                                           binop(Iop_Add64,
                                                 mkexpr(t5),
                                                 unop(Iop_32Sto64,
                                                      mkU32(0x7fffffff)))));
                     break;
                  }
                  case 0x18: {  
                     DIP("dpaqx_s.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                  mkU32(0x1),
                                                                  mkU8(ac+16))),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t8,
                            IRExpr_ITE(mkexpr(t6),
                                       IRExpr_ITE(mkexpr(t7),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t5)),
                                       mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              IRExpr_ITE(mkexpr(t7),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t9, binop(Iop_Add64,
                                      binop(Iop_Add64, mkexpr(t4), mkexpr(t8)),
                                      mkexpr(t0)));
                     putAcc(ac, mkexpr(t9));
                     break;
                  }
                  case 0x19: {  
                     DIP("dpsqx_s.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);

                     assign(t0, getAcc(ac));

                     assign(t1, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t4,
                            IRExpr_ITE(mkexpr(t2),
                                       IRExpr_ITE(mkexpr(t3),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t1)),
                                       mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(mkexpr(t2),
                                              IRExpr_ITE(mkexpr(t3),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t5, binop(Iop_Shl64,
                                      binop(Iop_MullS32,
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32to16,
                                                      getIReg(rs))),
                                            unop(Iop_16Sto32,
                                                 unop(Iop_32HIto16,
                                                      getIReg(rt)))),
                                      mkU8(0x1)));
                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));
                     assign(t8,
                            IRExpr_ITE(mkexpr(t6),
                                       IRExpr_ITE(mkexpr(t7),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t5)),
                                       mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(mkexpr(t6),
                                              IRExpr_ITE(mkexpr(t7),
                                                         binop(Iop_Or32,
                                                               getDSPControl(),
                                                               binop(Iop_Shl32,
                                                                     mkU32(0x1),
                                                                     mkU8(ac+16)
                                                                    )
                                                              ),
                                                         getDSPControl()),
                                              getDSPControl()));

                     assign(t9, binop(Iop_Sub64,
                                     mkexpr(t0),
                                     binop(Iop_Add64, mkexpr(t4), mkexpr(t8))));
                     putAcc(ac, mkexpr(t9));
                     break;
                  }
                  case 0x1A: {  
                     DIP("dpaqx_sa.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     assign(t1, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t4, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t2)),
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t3))),
                                                 mkU32(0)),
                                           mkU64(0x000000007fffffffULL),
                                           mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    binop(Iop_And32,
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t2)),
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t3))),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16))),
                                              getDSPControl()));
                     assign(t5, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t8, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t6)),
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t7))),
                                                 mkU32(0)),
                                           mkU64(0x000000007fffffffULL),
                                           mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    binop(Iop_And32,
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t6)),
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t7))),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16))),
                                              getDSPControl()));
                     assign(t9,
                            binop(Iop_Add64,
                                  mkexpr(t0),
                                  binop(Iop_Add64, mkexpr(t8), mkexpr(t4))));

                     putAcc(ac,
                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                             binop(Iop_And32,
                                                   unop(Iop_64HIto32,
                                                        mkexpr(t9)),
                                                   mkU32(0x80000000)),
                                             mkU32(0x0)),
                                       IRExpr_ITE(binop(Iop_CmpNE32,
                                                        unop(Iop_64HIto32,
                                                             binop(Iop_Shl64,
                                                                   mkexpr(t9),
                                                                   mkU8(1))),
                                                        mkU32(0x0)),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t9)),
                                       IRExpr_ITE(binop(Iop_CmpNE32,
                                                        unop(Iop_64HIto32,
                                                             binop(Iop_Shl64,
                                                                   mkexpr(t9),
                                                                   mkU8(1))),
                                                        mkU32(0xffffffff)),
                                                  mkU64(0xffffffff80000000ULL),
                                                  mkexpr(t9))));
                     assign(t10, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  unop(Iop_64to32,
                                                       mkexpr(t9)),
                                                  unop(Iop_64to32,
                                                       getAcc(ac))),
                                           getDSPControl(),
                                           binop(Iop_Or32,
                                                 getDSPControl(),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkU8(ac+16)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    unop(Iop_64HIto32,
                                                         mkexpr(t9)),
                                                    unop(Iop_64HIto32,
                                                         getAcc(ac))),
                                              mkexpr(t10),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     break;
                  }
                  case 0x1B: {  
                     DIP("dpsqx_sa.w.ph ac%d, r%d, r%d", ac, rs, rt);
                     vassert(!mode64);
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I64);
                     t2 = newTemp(Ity_I1);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_I64);
                     t5 = newTemp(Ity_I64);
                     t6 = newTemp(Ity_I1);
                     t7 = newTemp(Ity_I1);
                     t8 = newTemp(Ity_I64);
                     t9 = newTemp(Ity_I64);
                     t10 = newTemp(Ity_I32);

                     assign(t0, getAcc(ac));
                     assign(t1, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t2, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t3, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t4, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t2)),
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t3))),
                                                 mkU32(0)),
                                           mkU64(0x000000007fffffffULL),
                                           mkexpr(t1)));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    binop(Iop_And32,
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t2)),
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t3))),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16))),
                                              getDSPControl()));
                     assign(t5, unop(Iop_32Sto64,
                                     binop(Iop_Shl32,
                                           binop(Iop_Mul32,
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32to16,
                                                           getIReg(rs))),
                                                 unop(Iop_16Sto32,
                                                      unop(Iop_32HIto16,
                                                           getIReg(rt)))),
                                           mkU8(0x1))));

                     assign(t6, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32to16, getIReg(rs))),
                                      mkU32(0x00008000)));
                     assign(t7, binop(Iop_CmpEQ32,
                                      unop(Iop_16Uto32,
                                           unop(Iop_32HIto16, getIReg(rt))),
                                      mkU32(0x00008000)));

                     assign(t8, IRExpr_ITE(binop(Iop_CmpNE32,
                                                 binop(Iop_And32,
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t6)),
                                                       unop(Iop_1Sto32,
                                                            mkexpr(t7))),
                                                 mkU32(0)),
                                           mkU64(0x000000007fffffffULL),
                                           mkexpr(t5)));

                     putDSPControl(IRExpr_ITE(binop(Iop_CmpNE32,
                                                    binop(Iop_And32,
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t6)),
                                                          unop(Iop_1Sto32,
                                                               mkexpr(t7))),
                                                    mkU32(0)),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16))),
                                              getDSPControl()));
                     assign(t9,
                            binop(Iop_Sub64,
                                  mkexpr(t0),
                                  binop(Iop_Add64, mkexpr(t8), mkexpr(t4))));

                     putAcc(ac,
                            IRExpr_ITE(binop(Iop_CmpEQ32,
                                             binop(Iop_And32,
                                                   unop(Iop_64HIto32,
                                                        mkexpr(t9)),
                                                   mkU32(0x80000000)),
                                             mkU32(0x0)),
                                       IRExpr_ITE(binop(Iop_CmpNE32,
                                                        unop(Iop_64HIto32,
                                                             binop(Iop_Shl64,
                                                                   mkexpr(t9),
                                                                   mkU8(1))),
                                                        mkU32(0x0)),
                                                  mkU64(0x000000007fffffffULL),
                                                  mkexpr(t9)),
                                       IRExpr_ITE(binop(Iop_CmpNE32,
                                                        unop(Iop_64HIto32,
                                                             binop(Iop_Shl64,
                                                                   mkexpr(t9),
                                                                   mkU8(1))),
                                                        mkU32(0xffffffff)),
                                                  mkU64(0xffffffff80000000ULL),
                                                  mkexpr(t9))));
                     assign(t10, IRExpr_ITE(binop(Iop_CmpEQ32,
                                                  unop(Iop_64to32,
                                                       mkexpr(t9)),
                                                  unop(Iop_64to32,
                                                       getAcc(ac))),
                                           getDSPControl(),
                                           binop(Iop_Or32,
                                                 getDSPControl(),
                                                 binop(Iop_Shl32,
                                                       mkU32(0x1),
                                                       mkU8(ac+16)))));
                     putDSPControl(IRExpr_ITE(binop(Iop_CmpEQ32,
                                                    unop(Iop_64HIto32,
                                                         mkexpr(t9)),
                                                    unop(Iop_64HIto32,
                                                         getAcc(ac))),
                                              mkexpr(t10),
                                              binop(Iop_Or32,
                                                    getDSPControl(),
                                                    binop(Iop_Shl32,
                                                          mkU32(0x1),
                                                          mkU8(ac+16)))));
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            case 0x31: {  
               switch(sa) {
                  case 0x0: {  
                     DIP("append r%d, r%d, %d", rt, rs, rd);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     assign(t1, binop(Iop_Shl32, getIReg(rt), mkU8(rd)));

                     if (31 == rd) {
                        putIReg(rt, binop(Iop_Or32,
                                          mkexpr(t1),
                                          binop(Iop_And32,
                                                getIReg(rs),
                                                mkU32(0x7fffffff))));
                     } else if (1 == rd) {
                        putIReg(rt,
                                binop(Iop_Or32,
                                      mkexpr(t1),
                                      binop(Iop_And32,
                                            getIReg(rs), mkU32(0x1))));
                     } else {
                        assign(t2,
                               unop(Iop_Not32,
                                    binop(Iop_Shl32,
                                          mkU32(0xffffffff), mkU8(rd))));

                        putIReg(rt, binop(Iop_Or32,
                                          mkexpr(t1),
                                          binop(Iop_And32,
                                                getIReg(rs), mkexpr(t2))));
                     }
                     break;
                  }
                  case 0x1: {  
                     DIP("prepend r%d, r%d, %d", rt, rs, rd);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     if (0 != rd) {
                        assign(t1, binop(Iop_Shr32, getIReg(rt), mkU8(rd)));

                        if (31 == rd) {
                           putIReg(rt, binop(Iop_Or32,
                                             mkexpr(t1),
                                             binop(Iop_Shl32,
                                                   binop(Iop_And32,
                                                         getIReg(rs),
                                                         mkU32(0x7fffffff)),
                                                   mkU8(1))));
                        } else if (1 == rd) {
                           putIReg(rt, binop(Iop_Or32,
                                             mkexpr(t1),
                                             binop(Iop_Shl32,
                                                   binop(Iop_And32,
                                                         getIReg(rs),
                                                         mkU32(0x1)),
                                                   mkU8(31))));
                        } else {
                           assign(t2, binop(Iop_Add32, mkU32(rd), mkU32(0x1)));

                           assign(t3, unop(Iop_Not32,
                                           binop(Iop_Shl32,
                                                 mkU32(0xffffffff),
                                                 unop(Iop_32to8, mkexpr(t2)))));

                           putIReg(rt, binop(Iop_Or32,
                                             mkexpr(t1),
                                             binop(Iop_Shl32,
                                                   binop(Iop_And32,
                                                         getIReg(rs),
                                                         mkexpr(t3)),
                                                   mkU8(32-rd))));
                        }
                     }
                     break;
                  }
                  case 0x10: {  
                     DIP("balign r%d, r%d, %d", rt, rs, rd);
                     vassert(!mode64);
                     t1 = newTemp(Ity_I32);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I32);

                     if ((2 != rd) && (0 != rd)) {
                        assign(t1, binop(Iop_Shl32,
                                         binop(Iop_And32,
                                               mkU32(rd), mkU32(0x3)),
                                         mkU8(0x3)));
                        assign(t2, binop(Iop_Shl32,
                                         getIReg(rt),
                                         unop(Iop_32to8, mkexpr(t1))));
                        assign(t3, binop(Iop_Shr32,
                                         getIReg(rs),
                                         unop(Iop_32to8,
                                              binop(Iop_Shl32,
                                                    binop(Iop_Sub32,
                                                          mkU32(0x4),
                                                          binop(Iop_And32,
                                                                mkU32(rd),
                                                                mkU32(0x3))),
                                                    mkU8(0x3)))));
                        putIReg(rt, binop(Iop_Or32, mkexpr(t2), mkexpr(t3)));
                     }
                     break;
                  }
                  default:
                     return -1;
               }
               break;  
            }
            default:
               return -1;
         }
         break;
      }
      default:
            return -1;
   }
   return 0;
}



static DisResult disInstr_MIPS_WRK ( Bool(*resteerOkFn) (void *,
                                                                    Addr64),
                                     Bool         resteerCisOk,
                                     void*        callback_opaque,
                                     Long         delta64,
                                     VexArchInfo* archinfo,
                                     VexAbiInfo*  abiinfo,
                                     Bool         sigill_diag )
{
   IRTemp t0, t1 = 0, t2, t3, t4, t5, t6, t7;

   UInt opcode, cins, rs, rt, rd, sa, ft, fs, fd, fmt, tf, nd, function,
        trap_code, imm, instr_index, p, msb, lsb, size, rot, sel;
   
   UInt ac;

   DisResult dres;

   static IRExpr *lastn = NULL;  
   static IRStmt *bstmt = NULL;  

   
   Int delta = (Int) delta64;

   Int delta_start = delta;

   
   Bool delay_slot_branch, likely_delay_slot, delay_slot_jump;

   
   dres.whatNext = Dis_Continue;
   dres.len = 0;
   dres.continueAt = 0;
   dres.jk_StopHere = Ijk_INVALID;

   delay_slot_branch = likely_delay_slot = delay_slot_jump = False;

   UChar *code = (UChar *) (guest_code + delta);
   cins = getUInt(code);
   DIP("\t0x%lx:\t0x%08x\t", (long)guest_PC_curr_instr, cins);

   if (delta != 0) {
      if (branch_or_jump(guest_code + delta - 4)) {
         if (lastn == NULL && bstmt == NULL) {
            vassert(0);
         } else {
            dres.whatNext = Dis_StopHere;
            if (lastn != NULL) {
               delay_slot_jump = True;
            } else if (bstmt != NULL) {
               delay_slot_branch = True;
            }
         }
      }

      if (branch_or_link_likely(guest_code + delta - 4)) {
         likely_delay_slot = True;
      }
   }

   
   {

      UInt word1 = mode64 ? 0xF8  : 0x342;
      UInt word2 = mode64 ? 0x378 : 0x742;
      UInt word3 = mode64 ? 0x778 : 0xC2;
      UInt word4 = mode64 ? 0x4F8 : 0x4C2;
      if (getUInt(code + 0) == word1 && getUInt(code + 4) == word2 &&
          getUInt(code + 8) == word3 && getUInt(code + 12) == word4) {
         
         if (getUInt(code + 16) == 0x01ad6825  ) {
            
            DIP("$11 = client_request ( $12 )");
            if (mode64)
               putPC(mkU64(guest_PC_curr_instr + 20));
            else
               putPC(mkU32(guest_PC_curr_instr + 20));
            dres.jk_StopHere = Ijk_ClientReq;
            dres.whatNext    = Dis_StopHere;

            goto decode_success;
         } else if (getUInt(code + 16) == 0x01ce7025  ) {
            
            DIP("$11 = guest_NRADDR");
            dres.len = 20;
            delta += 20;
            if (mode64)
               putIReg(11, IRExpr_Get(offsetof(VexGuestMIPS64State,
                                               guest_NRADDR), Ity_I64));
            else
               putIReg(11, IRExpr_Get(offsetof(VexGuestMIPS32State,
                                               guest_NRADDR), Ity_I32));
            goto decode_success;
         } else if (getUInt(code + 16) == 0x01ef7825  ) {
            
            DIP("branch-and-link-to-noredir $25");
            if (mode64)
               putIReg(31, mkU64(guest_PC_curr_instr + 20));
            else
               putIReg(31, mkU32(guest_PC_curr_instr + 20));
            putPC(getIReg(25));
            dres.jk_StopHere = Ijk_NoRedir;
            dres.whatNext    = Dis_StopHere;
            goto decode_success;
         } else if (getUInt(code + 16) == 0x016b5825  ) {
           
            DIP("IR injection");
#if defined (_MIPSEL)
            vex_inject_ir(irsb, Iend_LE);
#elif defined (_MIPSEB)
            vex_inject_ir(irsb, Iend_BE);
#endif
            if (mode64) {
               stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_CMSTART),
                               mkU64(guest_PC_curr_instr)));
               stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_CMLEN),
                               mkU64(20)));

               putPC(mkU64(guest_PC_curr_instr + 20));
            } else {
               stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_CMSTART),
                               mkU32(guest_PC_curr_instr)));
               stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_CMLEN),
                               mkU32(20)));

               putPC(mkU32(guest_PC_curr_instr + 20));
            }
            dres.whatNext    = Dis_StopHere;
            dres.jk_StopHere = Ijk_InvalICache;
            dres.len = 20;
            delta += 20;
            goto decode_success;
         }

         delta += 16;
         goto decode_failure;
       }
   }

   opcode = get_opcode(cins);
   imm = get_imm(cins);
   rs = get_rs(cins);
   rt = get_rt(cins);
   rd = get_rd(cins);
   sa = get_sa(cins);
   fs = get_fs(cins);
   fd = get_fd(cins);
   ft = get_ft(cins);
   tf = get_tf(cins);
   nd = get_nd(cins);
   sel = get_sel(cins);
   fmt = get_fmt(cins);
   instr_index = get_instr_index(cins);
   trap_code = get_code(cins);
   function = get_function(cins);
   IRType ty = mode64 ? Ity_I64 : Ity_I32;
   IRType tyF = fp_mode64 ? Ity_F64 : Ity_F32;

   ac = get_acNo(cins);

   switch (opcode) {

   case 0x03:     
      DIP("jal 0x%x", instr_index);
      if (mode64) {
         putIReg(31, mkU64(guest_PC_curr_instr + 8));
         t0 = newTemp(ty);
         assign(t0, mkU64((guest_PC_curr_instr & 0xFFFFFFFFF0000000ULL) |
                          (instr_index << 2)));
      } else {
         putIReg(31, mkU32(guest_PC_curr_instr + 8));
         t0 = newTemp(ty);
         assign(t0, mkU32((guest_PC_curr_instr & 0xF0000000) |
                          (instr_index << 2)));
      }
      lastn = mkexpr(t0);
      break;
   case 0x02:     
      DIP("j 0x%x", instr_index);
      t0 = newTemp(ty);
      if (mode64)
         assign(t0, mkU64((guest_PC_curr_instr & 0xFFFFFFFFF0000000ULL) |
                          (instr_index << 2)));
      else
         assign(t0, mkU32((guest_PC_curr_instr & 0xF0000000) |
                          (instr_index << 2)));
      lastn = mkexpr(t0);
      break;

   case 0x11: {  
      if (fmt == 0x3 && fd == 0 && function == 0) {  
         DIP("mfhc1 r%d, f%d", rt, fs);
         if (fp_mode64) {
            t0 = newTemp(Ity_I64);
            t1 = newTemp(Ity_I32);
            assign(t0, unop(Iop_ReinterpF64asI64, getDReg(fs)));
            assign(t1, unop(Iop_64HIto32, mkexpr(t0)));
            putIReg(rt, mkWidenFrom32(ty, mkexpr(t1), True));
         } else {
            ILLEGAL_INSTRUCTON;
         }
         break;
      } else if (fmt == 0x7 && fd == 0 && function == 0) {  
         DIP("mthc1 r%d, f%d", rt, fs);
         if (fp_mode64) {
            t0 = newTemp(Ity_I64);
            assign(t0, binop(Iop_32HLto64, getIReg(rt),
                             unop(Iop_ReinterpF32asI32,
                                  getLoFromF64(Ity_F64 ,
                                               getDReg(fs)))));
            putDReg(fs, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
         } else {
            ILLEGAL_INSTRUCTON;
         }
         break;
      } else if (fmt == 0x8) {  
         
         UInt bc1_cc = get_bc1_cc(cins);
         t1 = newTemp(Ity_I1);
         t2 = newTemp(Ity_I32);
         t3 = newTemp(Ity_I1);

         assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(bc1_cc)));
         assign(t2, IRExpr_ITE(mkexpr(t1),
                               binop(Iop_And32,
                                     binop(Iop_Shr32, getFCSR(), mkU8(23)),
                                     mkU32(0x1)),
                               binop(Iop_And32,
                                     binop(Iop_Shr32, getFCSR(),
                                           mkU8(24 + bc1_cc)),
                                     mkU32(0x1))));

         if (tf == 1 && nd == 0) {
            
            DIP("bc1t %d, %d", bc1_cc, imm);
            assign(t3, binop(Iop_CmpEQ32, mkU32(1), mkexpr(t2)));
            dis_branch(False, mkexpr(t3), imm, &bstmt);
            break;
         } else if (tf == 0 && nd == 0) {
            
            DIP("bc1f %d, %d", bc1_cc, imm);
            assign(t3, binop(Iop_CmpEQ32, mkU32(0), mkexpr(t2)));
            dis_branch(False, mkexpr(t3), imm, &bstmt);
            break;
         } else if (nd == 1 && tf == 0) {
            DIP("bc1fl %d, %d", bc1_cc, imm);
            lastn = dis_branch_likely(binop(Iop_CmpNE32, mkexpr(t2),
                                            mkU32(0x0)), imm);
            break;
         } else if (nd == 1 && tf == 1) {
            DIP("bc1tl %d, %d", bc1_cc, imm);
            lastn = dis_branch_likely(binop(Iop_CmpEQ32, mkexpr(t2),
                                            mkU32(0x0)), imm);
            break;
         } else
            goto decode_failure;
      } else {
         switch (function) {
            case 0x4: {  
               switch (fmt) {
                  case 0x10: {  
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, binop(Iop_SqrtF32, rm,
                                 getLoFromF64(tyF, getFReg(fs)))));
                     break;
                  }
                  case 0x11: {  
                     IRExpr *rm = get_IR_roundingmode();
                     putDReg(fd, binop(Iop_SqrtF64, rm, getDReg(fs)));
                     break;
                  }
                  default:
                     goto decode_failure;
                  }
               }
               break;
            case 0x5:  
               switch (fmt) {
                  case 0x10:  
                     DIP("abs.s f%d, f%d", fd, fs);
                     putFReg(fd, mkWidenFromF32(tyF, unop(Iop_AbsF32,
                                 getLoFromF64(tyF, getFReg(fs)))));
                     break;
                  case 0x11:  
                     DIP("abs.d f%d, f%d", fd, fs);
                     putDReg(fd, unop(Iop_AbsF64, getDReg(fs)));
                     break;
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x02:  
               switch (fmt) {
                  case 0x11: {  
                     DIP("mul.d f%d, f%d, f%d", fd, fs, ft);
                     IRExpr *rm = get_IR_roundingmode();
                     putDReg(fd, triop(Iop_MulF64, rm, getDReg(fs),
                                       getDReg(ft)));
                     break;
                  }
                  case 0x10: {  
                     DIP("mul.s f%d, f%d, f%d", fd, fs, ft);
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, triop(Iop_MulF32, rm,
                                 getLoFromF64(tyF, getFReg(fs)),
                                 getLoFromF64(tyF, getFReg(ft)))));
                     break;
                  }
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x03:  
               switch (fmt) {
                  case 0x11: {  
                     DIP("div.d f%d, f%d, f%d", fd, fs, ft);
                     IRExpr *rm = get_IR_roundingmode();
                     putDReg(fd, triop(Iop_DivF64, rm, getDReg(fs),
                                 getDReg(ft)));
                     break;
                  }
                  case 0x10: {  
                     DIP("div.s f%d, f%d, f%d", fd, fs, ft);
                     calculateFCSR(fs, ft, DIVS, False, 2);
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, triop(Iop_DivF32, rm,
                                 getLoFromF64(tyF, getFReg(fs)),
                                 getLoFromF64(tyF, getFReg(ft)))));
                     break;
                  }
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x01:  
               switch (fmt) {
                  case 0x11: {  
                     DIP("sub.d f%d, f%d, f%d", fd, fs, ft);
                     calculateFCSR(fs, ft, SUBD, False, 2);
                     IRExpr *rm = get_IR_roundingmode();
                     putDReg(fd, triop(Iop_SubF64, rm, getDReg(fs),
                                       getDReg(ft)));
                     break;
                  }
                  case 0x10: {  
                     DIP("sub.s f%d, f%d, f%d", fd, fs, ft);
                     calculateFCSR(fs, ft, SUBS, True, 2);
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, triop(Iop_SubF32, rm,
                                 getLoFromF64(tyF, getFReg(fs)),
                                 getLoFromF64(tyF, getFReg(ft)))));
                     break;
                  }
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x06:  
               switch (fmt) {
                  case 0x11:  
                     DIP("mov.d f%d, f%d", fd, fs);
                     if (fp_mode64) {
                        putDReg(fd, getDReg(fs));
                     } else {
                        putFReg(fd, getFReg(fs));
                        putFReg(fd + 1, getFReg(fs + 1));
                     }
                     break;
                  case 0x10:  
                     DIP("mov.s f%d, f%d", fd, fs);
                     putFReg(fd, getFReg(fs));
                     break;
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x7:  
               switch (fmt) {
                  case 0x10:  
                     DIP("neg.s f%d, f%d", fd, fs);
                     putFReg(fd, mkWidenFromF32(tyF, unop(Iop_NegF32,
                                 getLoFromF64(tyF, getFReg(fs)))));
                     break;
                  case 0x11:  
                     DIP("neg.d f%d, f%d", fd, fs);
                     putDReg(fd, unop(Iop_NegF64, getDReg(fs)));
                     break;
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x08:  
               switch (fmt) {
                  case 0x10:  
                     DIP("round.l.s f%d, f%d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, ROUNDLS, True, 1);
                        t0 = newTemp(Ity_I64);

                        assign(t0, binop(Iop_F32toI64S, mkU32(0x0),
                                         getLoFromF64(Ity_F64, getFReg(fs))));

                        putDReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  case 0x11:  
                     DIP("round.l.d f%d, f%d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, ROUNDLD, False, 1);
                        putDReg(fd, binop(Iop_RoundF64toInt, mkU32(0x0),
                                          getDReg(fs)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  default:
                    goto decode_failure;

               }
               break;  

            case 0x09:  
               switch (fmt) {
                  case 0x10:  
                     DIP("trunc.l.s f%d, f%d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, TRUNCLS, True, 1);
                        t0 = newTemp(Ity_I64);
                        assign(t0, binop(Iop_F32toI64S, mkU32(0x3),
                                         getLoFromF64(Ity_F64, getFReg(fs))));

                        putDReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  case 0x11:  
                     DIP("trunc.l.d f%d, f%d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, TRUNCLD, False, 1);
                        putDReg(fd, binop(Iop_RoundF64toInt, mkU32(0x3),
                                          getDReg(fs)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  default:
                     goto decode_failure;
                 }
              break;  

            case 0x15:  
               switch (fmt) {
                  case 0x10: {  
                     DIP("recip.s f%d, f%d", fd, fs);
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, triop(Iop_DivF32,
                                 rm, unop(Iop_ReinterpI32asF32,
                                 mkU32(ONE_SINGLE)), getLoFromF64(tyF,
                                 getFReg(fs)))));
                     break;
                  }
                  case 0x11: {  
                     DIP("recip.d f%d, f%d", fd, fs);
                     IRExpr *rm = get_IR_roundingmode();
                     
                     putDReg(fd, triop(Iop_DivF64, rm,
                                 unop(Iop_ReinterpI64asF64,
                                 mkU64(ONE_DOUBLE)), getDReg(fs)));
                     break;
                  }
               default:
                  goto decode_failure;

               }
               break;  

            case 0x13:  
               switch (fmt) {
               case 0x10:  
                  DIP("movn.s f%d, f%d, r%d", fd, fs, rt);
                  t1 = newTemp(Ity_F64);
                  t2 = newTemp(Ity_F64);
                  t3 = newTemp(Ity_I1);
                  t4 = newTemp(Ity_F64);
                  if (mode64) {
                     assign(t1, getFReg(fs));
                     assign(t2, getFReg(fd));
                     assign(t3, binop(Iop_CmpNE64, mkU64(0), getIReg(rt)));
                  } else {
                     if (fp_mode64) {
                        assign(t1, getFReg(fs));
                        assign(t2, getFReg(fd));
                        assign(t3, binop(Iop_CmpNE32, mkU32(0), getIReg(rt)));
                     } else {
                        assign(t1, unop(Iop_F32toF64, getFReg(fs)));
                        assign(t2, unop(Iop_F32toF64, getFReg(fd)));
                        assign(t3, binop(Iop_CmpNE32, mkU32(0), getIReg(rt)));
                     }
                  }

                  assign(t4, IRExpr_ITE(mkexpr(t3), mkexpr(t1), mkexpr(t2)));
                  if (fp_mode64) {
                     IRTemp f = newTemp(Ity_F64);
                     IRTemp fd_hi = newTemp(Ity_I32);
                     t5 = newTemp(Ity_I64);
                     assign(f, getFReg(fd));
                     assign(fd_hi, unop(Iop_64HIto32, unop(Iop_ReinterpF64asI64,
                                        mkexpr(f))));

                     assign(t5, mkWidenFrom32(Ity_I64, unop(Iop_64to32,
                                unop(Iop_ReinterpF64asI64, mkexpr(t4))), True));

                     putFReg(fd, unop (Iop_ReinterpI64asF64, mkexpr(t5)));
                  } else
                     putFReg(fd, binop(Iop_F64toF32, get_IR_roundingmode(),
                                       mkexpr(t4)));
                  break;
               case 0x11:  
                  DIP("movn.d f%d, f%d, r%d", fd, fs, rt);

                  t3 = newTemp(Ity_I1);
                  t4 = newTemp(Ity_F64);

                  if (mode64)
                     assign(t3, binop(Iop_CmpNE64, mkU64(0), getIReg(rt)));
                  else
                     assign(t3, binop(Iop_CmpNE32, mkU32(0), getIReg(rt)));

                  putDReg(fd, IRExpr_ITE(mkexpr(t3), getDReg(fs), getDReg(fd)));
                  break;
               default:
                  goto decode_failure;
               }
               break;  

            case 0x12:  
               switch (fmt) {
               case 0x10:  
                  DIP("movz.s f%d, f%d, r%d", fd, fs, rt);

                  t1 = newTemp(Ity_F64);
                  t2 = newTemp(Ity_F64);
                  t3 = newTemp(Ity_I1);
                  t4 = newTemp(Ity_F64);
                  if (fp_mode64) {
                     assign(t1, getFReg(fs));
                     assign(t2, getFReg(fd));
                     if (mode64)
                        assign(t3, binop(Iop_CmpEQ64, mkU64(0), getIReg(rt)));
                     else
                        assign(t3, binop(Iop_CmpEQ32, mkU32(0), getIReg(rt)));
                  } else {
                     assign(t1, unop(Iop_F32toF64, getFReg(fs)));
                     assign(t2, unop(Iop_F32toF64, getFReg(fd)));
                     assign(t3, binop(Iop_CmpEQ32, mkU32(0), getIReg(rt)));
                  }
                  assign(t4, IRExpr_ITE(mkexpr(t3), mkexpr(t1), mkexpr(t2)));

                 if (fp_mode64) {
                     IRTemp f = newTemp(Ity_F64);
                     IRTemp fd_hi = newTemp(Ity_I32);
                     t7 = newTemp(Ity_I64);
                     assign(f, getFReg(fd));
                     assign(fd_hi, unop(Iop_64HIto32,
                                   unop(Iop_ReinterpF64asI64, mkexpr(f))));
                     assign(t7, mkWidenFrom32(Ity_I64, unop(Iop_64to32,
                                unop(Iop_ReinterpF64asI64, mkexpr(t4))), True));

                     putFReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t7)));
                  } else
                     putFReg(fd, binop(Iop_F64toF32, get_IR_roundingmode(),
                                       mkexpr(t4)));

                  break;
               case 0x11:  
                  DIP("movz.d f%d, f%d, r%d", fd, fs, rt);
                  t3 = newTemp(Ity_I1);
                  t4 = newTemp(Ity_F64);
                  if (mode64)
                     assign(t3, binop(Iop_CmpEQ64, mkU64(0), getIReg(rt)));
                  else
                     assign(t3, binop(Iop_CmpEQ32, mkU32(0), getIReg(rt)));

                  putDReg(fd, IRExpr_ITE(mkexpr(t3), getDReg(fs), getDReg(fd)));
                  break;
               default:
                  goto decode_failure;
               }
               break;  

            case 0x11:  
               if (tf == 1) {
                  UInt mov_cc = get_mov_cc(cins);
                  switch (fmt) {  
                  case 0x11:  
                     DIP("movt.d f%d, f%d, %d", fd, fs, mov_cc);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_F64);

                     assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(23)),
                                                 mkU32(0x1)),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(24 + mov_cc)),
                                                 mkU32(0x1))
                                           ));

                     assign(t3, binop(Iop_CmpEQ32, mkU32(1), mkexpr(t2)));
                     assign(t4, IRExpr_ITE(mkexpr(t3),
                                           getDReg(fs), getDReg(fd)));
                     putDReg(fd, mkexpr(t4));
                     break;
                  case 0x10:  
                     DIP("movt.s f%d, f%d, %d", fd, fs, mov_cc);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_F64);
                     t5 = newTemp(Ity_F64);
                     t6 = newTemp(Ity_F64);
                     t7 = newTemp(Ity_I64);

                     if (fp_mode64) {
                        assign(t5, getFReg(fs));
                        assign(t6, getFReg(fd));
                     } else {
                        assign(t5, unop(Iop_F32toF64, getFReg(fs)));
                        assign(t6, unop(Iop_F32toF64, getFReg(fd)));
                     }

                     assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(23)),
                                                 mkU32(0x1)),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(24 + mov_cc)),
                                                 mkU32(0x1))
                                           ));

                     assign(t3, binop(Iop_CmpEQ32, mkU32(1), mkexpr(t2)));
                     assign(t4, IRExpr_ITE(mkexpr(t3),
                                           mkexpr(t5), mkexpr(t6)));

                     if (fp_mode64) {
                        IRTemp f = newTemp(Ity_F64);
                        IRTemp fd_hi = newTemp(Ity_I32);
                        assign(f, getFReg(fd));
                        assign(fd_hi, unop(Iop_64HIto32,
                                      unop(Iop_ReinterpF64asI64, mkexpr(f))));
                        assign(t7, mkWidenFrom32(Ity_I64, unop(Iop_64to32,
                                      unop(Iop_ReinterpF64asI64, mkexpr(t4))),
                                      True));

                        putFReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t7)));
                     } else
                        putFReg(fd, binop(Iop_F64toF32, get_IR_roundingmode(),
                                          mkexpr(t4)));
                     break;
                  default:
                     goto decode_failure;
                  }
               } else if (tf == 0)  
               {
                  UInt mov_cc = get_mov_cc(cins);
                  switch (fmt)  
                  {
                  case 0x11:  
                     DIP("movf.d f%d, f%d, %d", fd, fs, mov_cc);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_F64);

                     assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(23)),
                                                 mkU32(0x1)),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(24 + mov_cc)),
                                                 mkU32(0x1))
                                           ));

                     assign(t3, binop(Iop_CmpEQ32, mkU32(0), mkexpr(t2)));
                     assign(t4, IRExpr_ITE(mkexpr(t3),
                                           getDReg(fs), getDReg(fd)));
                     putDReg(fd, mkexpr(t4));
                     break;
                  case 0x10:  
                     DIP("movf.s f%d, f%d, %d", fd, fs, mov_cc);
                     t1 = newTemp(Ity_I1);
                     t2 = newTemp(Ity_I32);
                     t3 = newTemp(Ity_I1);
                     t4 = newTemp(Ity_F64);
                     t5 = newTemp(Ity_F64);
                     t6 = newTemp(Ity_F64);

                     if (fp_mode64) {
                        assign(t5, getFReg(fs));
                        assign(t6, getFReg(fd));
                     } else {
                        assign(t5, unop(Iop_F32toF64, getFReg(fs)));
                        assign(t6, unop(Iop_F32toF64, getFReg(fd)));
                     }

                     assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
                     assign(t2, IRExpr_ITE(mkexpr(t1),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(23)),
                                                 mkU32(0x1)),
                                           binop(Iop_And32,
                                                 binop(Iop_Shr32, getFCSR(),
                                                       mkU8(24 + mov_cc)),
                                                 mkU32(0x1))
                                           ));

                     assign(t3, binop(Iop_CmpEQ32, mkU32(0), mkexpr(t2)));
                     assign(t4, IRExpr_ITE(mkexpr(t3),
                                           mkexpr(t5), mkexpr(t6)));

                     if (fp_mode64) {
                        IRTemp f = newTemp(Ity_F64);
                        IRTemp fd_hi = newTemp(Ity_I32);
                        t7 = newTemp(Ity_I64);
                        assign(f, getFReg(fd));
                        assign(fd_hi, unop(Iop_64HIto32,
                                      unop(Iop_ReinterpF64asI64, mkexpr(f))));
                        assign(t7, mkWidenFrom32(Ity_I64, unop(Iop_64to32,
                                   unop(Iop_ReinterpF64asI64, mkexpr(t4))),
                                   True));

                        putFReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t7)));
                     } else
                        putFReg(fd, binop(Iop_F64toF32, get_IR_roundingmode(),
                                          mkexpr(t4)));
                     break;
                  default:
                     goto decode_failure;
                  }
               }

               break;  

            case 0x0:  
               switch (fmt) {
               case 0x10: {  
                  DIP("add.s f%d, f%d, f%d", fd, fs, ft);
                  calculateFCSR(fs, ft, ADDS, True, 2);
                  IRExpr *rm = get_IR_roundingmode();
                  putFReg(fd, mkWidenFromF32(tyF, triop(Iop_AddF32, rm,
                              getLoFromF64(tyF, getFReg(fs)),
                              getLoFromF64(tyF, getFReg(ft)))));
                  break;
               }
               case 0x11: {  
                  DIP("add.d f%d, f%d, f%d", fd, fs, ft);
                  calculateFCSR(fs, ft, ADDD, False, 2);
                  IRExpr *rm = get_IR_roundingmode();
                  putDReg(fd, triop(Iop_AddF64, rm, getDReg(fs), getDReg(ft)));
                  break;
               }

               case 0x4:  
                  DIP("mtc1 r%d, f%d", rt, fs);
                  if (fp_mode64) {
                     t0 = newTemp(Ity_I32);
                     t1 = newTemp(Ity_F32);
                     assign(t0, mkNarrowTo32(ty, getIReg(rt)));
                     assign(t1, unop(Iop_ReinterpI32asF32, mkexpr(t0)));

                     putFReg(fs, mkWidenFromF32(tyF, mkexpr(t1)));
                  } else
                     putFReg(fs, unop(Iop_ReinterpI32asF32, getIReg(rt)));
                  break;

               case 0x5:  
                  DIP("dmtc1 r%d, f%d", rt, fs);
                  vassert(mode64);
                  putFReg(fs, unop(Iop_ReinterpI64asF64, getIReg(rt)));
                  break;

               case 0x0:  
                  DIP("mfc1 r%d, f%d", rt, fs);
                  if (fp_mode64) {
                     t0 = newTemp(Ity_I64);
                     t1 = newTemp(Ity_I32);
                     assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));
                     assign(t1, unop(Iop_64to32, mkexpr(t0)));
                     putIReg(rt, mkWidenFrom32(ty, mkexpr(t1), True));
                  } else
                     putIReg(rt, unop(Iop_ReinterpF32asI32, getFReg(fs)));
                  break;

               case 0x1:  
                  DIP("dmfc1 r%d, f%d", rt, fs);
                  putIReg(rt, unop(Iop_ReinterpF64asI64, getFReg(fs)));
                  break;

               case 0x6:  
                  DIP("ctc1 r%d, f%d", rt, fs);
                  t0 = newTemp(Ity_I32);
                  t1 = newTemp(Ity_I32);
                  t2 = newTemp(Ity_I32);
                  t3 = newTemp(Ity_I32);
                  t4 = newTemp(Ity_I32);
                  t5 = newTemp(Ity_I32);
                  t6 = newTemp(Ity_I32);
                  assign(t0, mkNarrowTo32(ty, getIReg(rt)));
                  if (fs == 25) {  
                     assign(t1, binop(Iop_Shl32, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x000000FE)), mkU8(24)));
                     assign(t2, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x01000000)));
                     assign(t3, binop(Iop_Shl32, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x00000001)), mkU8(23)));
                     assign(t4, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x007FFFFF)));
                     putFCSR(binop(Iop_Or32, binop(Iop_Or32, mkexpr(t1),
                                   mkexpr(t2)), binop(Iop_Or32, mkexpr(t3),
                                   mkexpr(t4))));
                  } else if (fs == 26) {  
                     assign(t1, binop(Iop_And32, getFCSR(), mkU32(0xFFFC0000)));
                     assign(t2, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x0003F000)));
                     assign(t3, binop(Iop_And32, getFCSR(), mkU32(0x00000F80)));
                     assign(t4, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x0000007C)));
                     assign(t5, binop(Iop_And32, getFCSR(), mkU32(0x00000003)));
                     putFCSR(binop(Iop_Or32, binop(Iop_Or32, binop(Iop_Or32,
                                   mkexpr(t1), mkexpr(t2)), binop(Iop_Or32,
                                   mkexpr(t3), mkexpr(t4))), mkexpr(t5)));
                  } else if (fs == 28) {
                     assign(t1, binop(Iop_And32, getFCSR(), mkU32(0xFE000000)));
                     assign(t2, binop(Iop_Shl32, binop(Iop_And32, mkexpr(t0),
                                mkU32(0x00000002)), mkU8(22)));
                     assign(t3, binop(Iop_And32, getFCSR(), mkU32(0x00FFF000)));
                     assign(t4, binop(Iop_And32, mkexpr(t0),
                                mkU32(0x00000F80)));
                     assign(t5, binop(Iop_And32, getFCSR(), mkU32(0x0000007C)));
                     assign(t6, binop(Iop_And32, mkexpr(t0),
                                mkU32(0x00000003)));
                     putFCSR(binop(Iop_Or32, binop(Iop_Or32, binop(Iop_Or32,
                                   mkexpr(t1), mkexpr(t2)), binop(Iop_Or32,
                                   mkexpr(t3), mkexpr(t4))), binop(Iop_Or32,
                                   mkexpr(t5), mkexpr(t6))));
                  } else if (fs == 31) {
                     putFCSR(mkexpr(t0));
                  }
                  break;
               case 0x2:  
                  DIP("cfc1 r%d, f%d", rt, fs);
                  t0 = newTemp(Ity_I32);
                  t1 = newTemp(Ity_I32);
                  t2 = newTemp(Ity_I32);
                  t3 = newTemp(Ity_I32);
                  t4 = newTemp(Ity_I32);
                  t5 = newTemp(Ity_I32);
                  t6 = newTemp(Ity_I32);
                  assign(t0, getFCSR());
                  if (fs == 0) {
                     putIReg(rt, mkWidenFrom32(ty,
                             IRExpr_Get(offsetof(VexGuestMIPS32State,
                                                 guest_FIR),
                                       Ity_I32),
                             False));
                  } else if (fs == 25) {
                     assign(t1, mkU32(0x000000FF));
                     assign(t2, binop(Iop_Shr32, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0xFE000000)), mkU8(25)));
                     assign(t3, binop(Iop_Shr32, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x00800000)), mkU8(23)));
                     putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32,
                                 binop(Iop_Or32, mkexpr(t1), mkexpr(t2)),
                                 mkexpr(t3)), False));
                  } else if (fs == 26) {
                     assign(t1, mkU32(0xFFFFF07C));
                     assign(t2, binop(Iop_And32, mkexpr(t0),
                                mkU32(0x0003F000)));
                     assign(t3, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x0000007C)));
                     putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32,
                                 binop(Iop_Or32, mkexpr(t1), mkexpr(t2)),
                                 mkexpr(t3)), False));
                  } else if (fs == 28) {
                     assign(t1, mkU32(0x00000F87));
                     assign(t2, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x00000F83)));
                     assign(t3, binop(Iop_Shr32, binop(Iop_And32, mkexpr(t0),
                                      mkU32(0x01000000)), mkU8(22)));
                     putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32,
                                 binop(Iop_Or32, mkexpr(t1), mkexpr(t2)),
                                 mkexpr(t3)), False));
                  } else if (fs == 31) {
                     putIReg(rt, mkWidenFrom32(ty, getFCSR(), False));
                  }
                  break;
               default:
                  goto decode_failure;
               }
               break;

            case 0x21:  
               switch (fmt) {
                  case 0x10:  
                     DIP("cvt.d.s f%d, f%d", fd, fs);
                     calculateFCSR(fs, 0, CVTDS, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));

                        assign(t3, unop(Iop_ReinterpI32asF32, mkexpr(t1)));

                        putFReg(fd, unop(Iop_F32toF64, mkexpr(t3)));
                     } else
                        putDReg(fd, unop(Iop_F32toF64, getFReg(fs)));
                     break;

                  case 0x14:
                     DIP("cvt.d.w %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CVTDW, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));
                        putDReg(fd,unop(Iop_I32StoF64, mkexpr(t1)));
                        break;
                     } else {
                        t0 = newTemp(Ity_I32);
                        assign(t0, unop(Iop_ReinterpF32asI32, getFReg(fs)));
                        putDReg(fd, unop(Iop_I32StoF64, mkexpr(t0)));
                        break;
                     }

                  case 0x15: {  
                     if (fp_mode64) {
                        DIP("cvt.d.l %d, %d", fd, fs);
                        calculateFCSR(fs, 0, CVTDL, False, 1);
                        t0 = newTemp(Ity_I64);
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        putFReg(fd, binop(Iop_I64StoF64,
                                          get_IR_roundingmode(), mkexpr(t0)));
                        break;
                     } else
                        goto decode_failure;
                  }
                  default:
                     goto decode_failure;
               }
               break;  

            case 0x20:  
               switch (fmt) {
                  case 0x14:  
                     DIP("cvt.s.w %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CVTSW, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));
                        putFReg(fd, mkWidenFromF32(tyF, binop(Iop_I32StoF32,
                                    get_IR_roundingmode(), mkexpr(t1))));
                     } else {
                        t0 = newTemp(Ity_I32);
                        assign(t0, unop(Iop_ReinterpF32asI32, getFReg(fs)));
                        putFReg(fd, binop(Iop_I32StoF32, get_IR_roundingmode(),
                                    mkexpr(t0)));
                     }
                     break;

                  case 0x11:  
                     DIP("cvt.s.d %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CVTSD, False, 1);
                     t0 = newTemp(Ity_F32);
                     assign(t0, binop(Iop_F64toF32, get_IR_roundingmode(),
                                      getDReg(fs)));
                     putFReg(fd, mkWidenFromF32(tyF, mkexpr(t0)));
                     break;

                  case 0x15:  
                     DIP("cvt.s.l %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CVTSL, False, 1);
                     t0 = newTemp(Ity_I64);
                     assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                     putFReg(fd, mkWidenFromF32(tyF, binop(Iop_I64StoF32,
                                 get_IR_roundingmode(), mkexpr(t0))));
                     break;

                  default:
                     goto decode_failure;
               }
               break;  

            case 0x24:  
               switch (fmt) {
               case 0x10:  
                  DIP("cvt.w.s %d, %d", fd, fs);
                  calculateFCSR(fs, 0, CVTWS, True, 1);
                  putFReg(fd,
                          mkWidenFromF32(tyF,
                                         binop(Iop_RoundF32toInt,
                                               get_IR_roundingmode(),
                                               getLoFromF64(tyF, getFReg(fs))))
                         );
                  break;

               case 0x11:
                  DIP("cvt.w.d %d, %d", fd, fs);
                  calculateFCSR(fs, 0, CVTWD, False, 1);
                  t0 = newTemp(Ity_I32);
                  t1 = newTemp(Ity_F32);
                  assign(t0, binop(Iop_F64toI32S, get_IR_roundingmode(),
                                   getDReg(fs)));
                  assign(t1, unop(Iop_ReinterpI32asF32, mkexpr(t0)));
                  putFReg(fd, mkWidenFromF32(tyF, mkexpr(t1)));
                  break;

               default:
                  goto decode_failure;

               }
               break;

            case 0x25:  
               switch (fmt) {
                  case 0x10:  
                     DIP("cvt.l.s %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, CVTLS, True, 1);
                        t0 = newTemp(Ity_I64);

                        assign(t0, binop(Iop_F32toI64S, get_IR_roundingmode(),
                                         getLoFromF64(tyF, getFReg(fs))));

                        putDReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;

                  case 0x11: {  
                     DIP("cvt.l.d %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, CVTLD, False, 1);
                        putDReg(fd, binop(Iop_RoundF64toInt,
                                get_IR_roundingmode(), getDReg(fs)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  }

                  default:
                     goto decode_failure;
               }
               break;

            case 0x0B:  
               switch (fmt) {
                  case 0x10:  
                     DIP("floor.l.s %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, FLOORLS, True, 1);
                        t0 = newTemp(Ity_I64);

                        assign(t0, binop(Iop_F32toI64S, mkU32(0x1),
                                         getLoFromF64(tyF, getFReg(fs))));

                        putDReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;

                  case 0x11:  
                     DIP("floor.l.d %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, FLOORLD, False, 1);
                        putDReg(fd, binop(Iop_RoundF64toInt, mkU32(0x1),
                                          getDReg(fs)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;
                  default:
                     goto decode_failure;
               }
               break;

            case 0x0C:  
               switch (fmt) {
                  case 0x10:  
                     DIP("round.w.s f%d, f%d", fd, fs);
                     calculateFCSR(fs, 0, ROUNDWS, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));

                        assign(t3, unop(Iop_ReinterpI32asF32, mkexpr(t1)));

                        assign(t4, binop(Iop_RoundF32toInt, mkU32(0x0),
                                         mkexpr(t3)));

                        putFReg(fd, mkWidenFromF32(tyF, mkexpr(t4)));
                     } else
                        putFReg(fd, binop(Iop_RoundF32toInt, mkU32(0x0),
                                          getFReg(fs)));
                     break;

                  case 0x11:  
                     DIP("round.w.d f%d, f%d", fd, fs);
                     calculateFCSR(fs, 0, ROUNDWD, False, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I32);
                        assign(t0, binop(Iop_F64toI32S, mkU32(0x0),
                                         getDReg(fs)));
                        putFReg(fd, mkWidenFromF32(tyF,
                                    unop(Iop_ReinterpI32asF32, mkexpr(t0))));
                     } else {
                        t0 = newTemp(Ity_I32);

                        assign(t0, binop(Iop_F64toI32S, mkU32(0x0),
                                         getDReg(fs)));

                        putFReg(fd, unop(Iop_ReinterpI32asF32, mkexpr(t0)));
                     }
                     break;
                  default:
                     goto decode_failure;

                  }
                  break;  

            case 0x0F:  
               switch (fmt) {
                  case 0x10:  
                     DIP("floor.w.s f%d, f%d", fd, fs);
                     calculateFCSR(fs, 0, FLOORWS, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));

                        assign(t3, unop(Iop_ReinterpI32asF32, mkexpr(t1)));

                        assign(t4, binop(Iop_RoundF32toInt, mkU32(0x1),
                                         mkexpr(t3)));

                        putFReg(fd, mkWidenFromF32(tyF, mkexpr(t4)));
                     } else
                        putFReg(fd, binop(Iop_RoundF32toInt, mkU32(0x1),
                                         getFReg(fs)));
                     break;

                  case 0x11:  
                     DIP("floor.w.d f%d, f%d", fd, fs);
                     calculateFCSR(fs, 0, FLOORWD, False, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I32);
                        assign(t0, binop(Iop_F64toI32S, mkU32(0x1),
                                         getDReg(fs)));
                        putFReg(fd, mkWidenFromF32(tyF,
                                    unop(Iop_ReinterpI32asF32, mkexpr(t0))));
                        break;
                     } else {
                        t0 = newTemp(Ity_I32);

                        assign(t0, binop(Iop_F64toI32S, mkU32(0x1),
                                         getDReg(fs)));

                        putFReg(fd, unop(Iop_ReinterpI32asF32, mkexpr(t0)));
                        break;
                     }
                  default:
                     goto decode_failure;

               }
               break;  

            case 0x0D:  
               switch (fmt) {
                  case 0x10:  
                     DIP("trunc.w.s %d, %d", fd, fs);
                     calculateFCSR(fs, 0, TRUNCWS, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));

                        assign(t3, unop(Iop_ReinterpI32asF32, mkexpr(t1)));

                        assign(t4, binop(Iop_RoundF32toInt, mkU32(0x3),
                                         mkexpr(t3)));

                        putFReg(fd, mkWidenFromF32(tyF, mkexpr(t4)));
                     } else
                        putFReg(fd, binop(Iop_RoundF32toInt, mkU32(0x3),
                                       getFReg(fs)));
                     break;
                  case 0x11:  
                     DIP("trunc.w.d %d, %d", fd, fs);
                     calculateFCSR(fs, 0, TRUNCWD, False, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I32);

                        assign(t0, binop(Iop_F64toI32S, mkU32(0x3),
                                         getFReg(fs)));

                        putFReg(fd, mkWidenFromF32(tyF,
                                    unop(Iop_ReinterpI32asF32, mkexpr(t0))));
                     } else {
                        t0 = newTemp(Ity_I32);

                        assign(t0, binop(Iop_F64toI32S, mkU32(0x3),
                                         getDReg(fs)));

                        putFReg(fd, unop(Iop_ReinterpI32asF32, mkexpr(t0)));
                     }
                     break;
                  default:
                     goto decode_failure;

               }
               break;

            case 0x0E:  
               switch (fmt) {
                  case 0x10:  
                     DIP("ceil.w.s %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CEILWS, True, 1);
                     if (fp_mode64) {
                        t0 = newTemp(Ity_I64);
                        t1 = newTemp(Ity_I32);
                        t3 = newTemp(Ity_F32);
                        t4 = newTemp(Ity_F32);
                        
                        assign(t0, unop(Iop_ReinterpF64asI64, getFReg(fs)));

                        assign(t1, unop(Iop_64to32, mkexpr(t0)));

                        assign(t3, unop(Iop_ReinterpI32asF32, mkexpr(t1)));

                        assign(t4, binop(Iop_RoundF32toInt, mkU32(0x2),
                                         mkexpr(t3)));

                        putFReg(fd, mkWidenFromF32(tyF, mkexpr(t4)));
                     } else
                        putFReg(fd, binop(Iop_RoundF32toInt, mkU32(0x2),
                                          getFReg(fs)));
                     break;

                  case 0x11:  
                     DIP("ceil.w.d %d, %d", fd, fs);
                     calculateFCSR(fs, 0, CEILWD, False, 1);
                     if (!fp_mode64) {
                        t0 = newTemp(Ity_I32);
                        assign(t0, binop(Iop_F64toI32S, mkU32(0x2),
                                         getDReg(fs)));
                        putFReg(fd, unop(Iop_ReinterpI32asF32, mkexpr(t0)));
                     } else {
                        t0 = newTemp(Ity_I32);
                        assign(t0, binop(Iop_F64toI32S, mkU32(0x2),
                                         getDReg(fs)));
                        putFReg(fd, mkWidenFromF32(tyF,
                                    unop(Iop_ReinterpI32asF32, mkexpr(t0))));
                     }
                     break;
                  default:
                     goto decode_failure;

               }
               break;

            case 0x0A:  
               switch (fmt) {
                  case 0x10:  
                     DIP("ceil.l.s %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, CEILLS, True, 1);
                        t0 = newTemp(Ity_I64);

                        assign(t0, binop(Iop_F32toI64S, mkU32(0x2),
                                   getLoFromF64(tyF, getFReg(fs))));

                        putFReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t0)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;

                  case 0x11:  
                     DIP("ceil.l.d %d, %d", fd, fs);
                     if (fp_mode64) {
                        calculateFCSR(fs, 0, CEILLD, False, 1);
                        putFReg(fd, binop(Iop_RoundF64toInt, mkU32(0x2),
                                          getFReg(fs)));
                     } else {
                        ILLEGAL_INSTRUCTON;
                     }
                     break;

                  default:
                     goto decode_failure;

               }
               break;

            case 0x16:  
               switch (fmt) {
                  case 0x10: {  
                     DIP("rsqrt.s %d, %d", fd, fs);
                     IRExpr *rm = get_IR_roundingmode();
                     putFReg(fd, mkWidenFromF32(tyF, triop(Iop_DivF32, rm,
                                 unop(Iop_ReinterpI32asF32, mkU32(ONE_SINGLE)),
                                 binop(Iop_SqrtF32, rm, getLoFromF64(tyF,
                                 getFReg(fs))))));
                     break;
                  }
                  case 0x11: {  
                     DIP("rsqrt.d %d, %d", fd, fs);
                     IRExpr *rm = get_IR_roundingmode();
                     putDReg(fd, triop(Iop_DivF64, rm,
                                 unop(Iop_ReinterpI64asF64,
                                 mkU64(ONE_DOUBLE)),
                                 binop(Iop_SqrtF64, rm, getDReg(fs))));
                     break;
                  }
                  default:
                     goto decode_failure;

               }
               break;

            default:
               if (dis_instr_CCondFmt(cins))
                  break;
               goto decode_failure;

            }

         }
      }
      break;  
   case 0x10:  
      if (rs == 0) {  
         DIP("mfc0 r%d, r%d, %d", rt, rd, sel);
         IRTemp   val  = newTemp(Ity_I32);
         IRExpr** args = mkIRExprVec_3 (IRExpr_BBPTR(), mkU32(rd), mkU32(sel));
         IRDirty *d = unsafeIRDirty_1_N(val,
                                        0,
                                        "mips32_dirtyhelper_mfc0",
                                        &mips32_dirtyhelper_mfc0,
                                        args);
         stmt(IRStmt_Dirty(d));
         putIReg(rt, mkexpr(val));
      } else if (rs == 1) {
         
         DIP("dmfc0 r%d, r%d, %d", rt, rd, sel);
         IRTemp   val  = newTemp(Ity_I64);
         IRExpr** args = mkIRExprVec_3 (IRExpr_BBPTR(), mkU64(rd), mkU64(sel));
         IRDirty *d = unsafeIRDirty_1_N(val,
                                        0,
                                        "mips64_dirtyhelper_dmfc0",
                                        &mips64_dirtyhelper_dmfc0,
                                        args);
         stmt(IRStmt_Dirty(d));
         putDReg(rt, mkexpr(val));
      } else
         goto decode_failure;
      break;

   case 0x31:  
      
      DIP("lwc1 f%d, %d(r%d)", ft, imm, rs);
      if (fp_mode64) {
         t1 = newTemp(Ity_F32);
         t2 = newTemp(Ity_I64);
         if (mode64) {
            t0 = newTemp(Ity_I64);
            
            assign(t0, binop(Iop_Add64, getIReg(rs),
                             mkU64(extend_s_16to64(imm))));
         } else {
            t0 = newTemp(Ity_I32);
            
            assign(t0, binop(Iop_Add32, getIReg(rs),
                             mkU32(extend_s_16to32(imm))));
         }
         assign(t1, load(Ity_F32, mkexpr(t0)));
         assign(t2, mkWidenFrom32(Ity_I64, unop(Iop_ReinterpF32asI32,
                                                mkexpr(t1)), True));
         putDReg(ft, unop(Iop_ReinterpI64asF64, mkexpr(t2)));
      } else {
         t0 = newTemp(Ity_I32);
         assign(t0, binop(Iop_Add32, getIReg(rs),
                           mkU32(extend_s_16to32(imm))));
         putFReg(ft, load(Ity_F32, mkexpr(t0)));
      }
      break;

   case 0x39:  
      DIP("swc1 f%d, %d(r%d)", ft, imm, rs);
      if (fp_mode64) {
         t0 = newTemp(Ity_I64);
         t2 = newTemp(Ity_I32);
         LOAD_STORE_PATTERN;
         assign(t0, unop(Iop_ReinterpF64asI64, getFReg(ft)));
         assign(t2, unop(Iop_64to32, mkexpr(t0)));
         store(mkexpr(t1), unop(Iop_ReinterpI32asF32, mkexpr(t2)));
      } else {
         LOAD_STORE_PATTERN;
         store(mkexpr(t1), getFReg(ft));
      }
      break;

   case 0x33:  
      DIP("pref");
      break;

   case 0x35:
      
      DIP("ldc1 f%d, %d(%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      putDReg(ft, load(Ity_F64, mkexpr(t1)));
      break;

   case 0x3D:
      
      DIP("sdc1 f%d, %d(%d)", ft, imm, rs);
      LOAD_STORE_PATTERN;
      store(mkexpr(t1), getDReg(ft));
      break;

   case 0x23:  
      DIP("lw r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      putIReg(rt, mkWidenFrom32(ty, load(Ity_I32, mkexpr(t1)), True));
      break;

   case 0x20:  
      DIP("lb r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      if (mode64)
         putIReg(rt, unop(Iop_8Sto64, load(Ity_I8, mkexpr(t1))));
      else
         putIReg(rt, unop(Iop_8Sto32, load(Ity_I8, mkexpr(t1))));
      break;

   case 0x24:  
      DIP("lbu r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      if (mode64)
         putIReg(rt, unop(Iop_8Uto64, load(Ity_I8, mkexpr(t1))));
      else
         putIReg(rt, unop(Iop_8Uto32, load(Ity_I8, mkexpr(t1))));
      break;

   case 0x21:  
      DIP("lh r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      if (mode64)
         putIReg(rt, unop(Iop_16Sto64, load(Ity_I16, mkexpr(t1))));
      else
         putIReg(rt, unop(Iop_16Sto32, load(Ity_I16, mkexpr(t1))));
      break;

   case 0x25:  
      DIP("lhu r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      if (mode64)
         putIReg(rt, unop(Iop_16Uto64, load(Ity_I16, mkexpr(t1))));
      else
         putIReg(rt, unop(Iop_16Uto32, load(Ity_I16, mkexpr(t1))));
      break;

   case 0x0F:  
      p = (imm << 16);
      DIP("lui r%d, imm: 0x%x", rt, imm);
      if (mode64)
         putIReg(rt, mkU64(extend_s_32to64(p)));
      else
         putIReg(rt, mkU32(p));
      break;

   case 0x13:  
      switch (function) {
      case 0x0: {  
         
         DIP("lwxc1 f%d, r%d(r%d)", fd, rt, rs);
         if (fp_mode64) {
            t0 = newTemp(Ity_I64);
            t1 = newTemp(Ity_I32);
            t3 = newTemp(Ity_F32);
            t4 = newTemp(Ity_I64);

            t2 = newTemp(ty);
            
            assign(t2, binop(mode64 ? Iop_Add64 : Iop_Add32, getIReg(rs),
                             getIReg(rt)));
            assign(t3, load(Ity_F32, mkexpr(t2)));

            assign(t4, mkWidenFrom32(Ity_I64, unop(Iop_ReinterpF32asI32,
                                                   mkexpr(t3)), True));

            putFReg(fd, unop(Iop_ReinterpI64asF64, mkexpr(t4)));
         } else {
            t0 = newTemp(Ity_I32);
            assign(t0, binop(Iop_Add32, getIReg(rs), getIReg(rt)));
            putFReg(fd, load(Ity_F32, mkexpr(t0)));
         }
         break;
      }

      case 0x1: {  
         if (fp_mode64) {
            DIP("ldxc1 f%d, r%d(r%d)", fd, rt, rs);
            t0 = newTemp(ty);
            assign(t0, binop(mode64 ? Iop_Add64 : Iop_Add32, getIReg(rs),
                             getIReg(rt)));
            putFReg(fd, load(Ity_F64, mkexpr(t0)));
            break;
         } else {
            t0 = newTemp(Ity_I32);
            assign(t0, binop(Iop_Add32, getIReg(rs), getIReg(rt)));

            t1 = newTemp(Ity_I32);
            assign(t1, binop(Iop_Add32, mkexpr(t0), mkU32(4)));

#if defined (_MIPSEL)
            putFReg(fd, load(Ity_F32, mkexpr(t0)));
            putFReg(fd + 1, load(Ity_F32, mkexpr(t1)));
#elif defined (_MIPSEB)
            putFReg(fd + 1, load(Ity_F32, mkexpr(t0)));
            putFReg(fd, load(Ity_F32, mkexpr(t1)));
#endif
            break;
         }
      }

      case 0x5:  
         DIP("luxc1 f%d, r%d(r%d)", fd, rt, rs);
         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);
         assign(t0, binop(Iop_Add64, getIReg(rs), getIReg(rt)));
         assign(t1, binop(Iop_And64, mkexpr(t0),
                                     mkU64(0xfffffffffffffff8ULL)));
         putFReg(fd, load(Ity_F64, mkexpr(t1)));
         break;

      case 0x8: {  
         DIP("swxc1 f%d, r%d(r%d)", ft, rt, rs);
         if (fp_mode64) {
            t0 = newTemp(ty);
            assign(t0, binop(mode64 ? Iop_Add64 : Iop_Add32, getIReg(rs),
                             getIReg(rt)));
            store(mkexpr(t0), getLoFromF64(tyF, getFReg(fs)));

         } else {
            t0 = newTemp(Ity_I32);
            assign(t0, binop(Iop_Add32, getIReg(rs), getIReg(rt)));

            store(mkexpr(t0), getFReg(fs));
         }
         break;
      }
      case 0x9: {  
         DIP("sdc1 f%d, %d(%d)", ft, imm, rs);
         if (fp_mode64) {
            t0 = newTemp(ty);
            assign(t0, binop(mode64 ? Iop_Add64 : Iop_Add32, getIReg(rs),
                             getIReg(rt)));
            store(mkexpr(t0), getFReg(fs));
         } else {
            t0 = newTemp(Ity_I32);
            assign(t0, binop(Iop_Add32, getIReg(rs), getIReg(rt)));

            t1 = newTemp(Ity_I32);
            assign(t1, binop(Iop_Add32, mkexpr(t0), mkU32(4)));

#if defined (_MIPSEL)
            store(mkexpr(t0), getFReg(fs));
            store(mkexpr(t1), getFReg(fs + 1));
#elif defined (_MIPSEB)
            store(mkexpr(t0), getFReg(fs + 1));
            store(mkexpr(t1), getFReg(fs));
#endif
         }
         break;
      }
      case 0xD:  
         DIP("suxc1 f%d, r%d(r%d)", fd, rt, rs);
         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);
         assign(t0, binop(Iop_Add64, getIReg(rs), getIReg(rt)));
         assign(t1, binop(Iop_And64, mkexpr(t0), mkU64(0xfffffffffffffff8ULL)));
         store(mkexpr(t1), getFReg(fs));
         break;

      case 0x0F: {
         DIP("prefx");
         break;
      }
      case 0x20:  {  
         DIP("madd.s f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F32);
         assign(t1, qop(Iop_MAddF32, rm,
                        getLoFromF64(tyF, getFReg(fmt)),
                        getLoFromF64(tyF, getFReg(fs)),
                        getLoFromF64(tyF, getFReg(ft))));
         putFReg(fd, mkWidenFromF32(tyF, mkexpr(t1)));
         break;  
      }
      case 0x21: {  
         DIP("madd.d f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         putDReg(fd, qop(Iop_MAddF64, rm, getDReg(fmt), getDReg(fs),
                         getDReg(ft)));
         break;  
      }
      case 0x28: {  
         DIP("msub.s f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F32);
         assign(t1, qop(Iop_MSubF32, rm,
                        getLoFromF64(tyF, getFReg(fmt)),
                        getLoFromF64(tyF, getFReg(fs)),
                        getLoFromF64(tyF, getFReg(ft))));
         putFReg(fd, mkWidenFromF32(tyF, mkexpr(t1)));
         break;  
      }
      case 0x29: {  
         DIP("msub.d f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         putDReg(fd, qop(Iop_MSubF64, rm, getDReg(fmt), getDReg(fs),
                         getDReg(ft)));
         break;  
      }
      case 0x30: {  
         DIP("nmadd.s f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F32);
         assign(t1, qop(Iop_MAddF32, rm,
                        getLoFromF64(tyF, getFReg(fmt)),
                        getLoFromF64(tyF, getFReg(fs)),
                        getLoFromF64(tyF, getFReg(ft))));

         putFReg(fd, mkWidenFromF32(tyF, unop(Iop_NegF32, mkexpr(t1))));
         break;  
      }
      case 0x31: {  
         DIP("nmadd.d f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F64);
         assign(t1, qop(Iop_MAddF64, rm, getDReg(fmt), getDReg(fs),
                        getDReg(ft)));
         putDReg(fd, unop(Iop_NegF64, mkexpr(t1)));
         break;  
      }
      case 0x38: {  
         DIP("nmsub.s f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F32);
         assign(t1, qop(Iop_MSubF32, rm,
                        getLoFromF64(tyF, getFReg(fmt)),
                        getLoFromF64(tyF, getFReg(fs)),
                        getLoFromF64(tyF, getFReg(ft))));

         putFReg(fd, mkWidenFromF32(tyF, unop(Iop_NegF32, mkexpr(t1))));
         break;  
      }
      case 0x39: {  
         DIP("nmsub.d f%d, f%d, f%d, f%d", fd, fmt, fs, ft);
         IRExpr *rm = get_IR_roundingmode();
         t1 = newTemp(Ity_F64);
         assign(t1, qop(Iop_MSubF64, rm, getDReg(fmt), getDReg(fs),
                        getDReg(ft)));
         putDReg(fd, unop(Iop_NegF64, mkexpr(t1)));
         break;  
      }

      default:
         goto decode_failure;
      }
      break;

   case 0x22:  
      DIP("lwl r%d, %d(r%d)", rt, imm, rs);
      if (mode64) {
         
         t1 = newTemp(Ity_I64);
#if defined (_MIPSEL)
         assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));
         
         
         LWX_SWX_PATTERN64;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shl32, mkNarrowTo32(ty, load(Ity_I64,
                          mkexpr(t2))), narrowTo(Ity_I8, binop(Iop_Shl32,
                    binop(Iop_Sub32, mkU32(0x03), mkexpr(t4)), mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32,
                          mkNarrowTo32(ty, getIReg(rt)),
                          binop(Iop_Shr32,
                                mkU32(0x00FFFFFF),
                                      narrowTo(Ity_I8, binop(Iop_Mul32,
                                                             mkU32(0x08),
                                                             mkexpr(t4))))));

         putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t5),
                                             mkexpr(t3)), True));
#elif defined (_MIPSEB)
         assign(t1, binop(Iop_Xor64, mkU64(0x3),
                binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm)))));
         
         
         LWX_SWX_PATTERN64;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shl32, unop(Iop_64HIto32, load(Ity_I64,
                          mkexpr(t2))), narrowTo(Ity_I8, binop(Iop_Shl32,
                    binop(Iop_Sub32, mkU32(0x03), mkexpr(t4)), mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32,
                          mkNarrowTo32(ty, getIReg(rt)),
                          binop(Iop_Shr32,
                                mkU32(0x00FFFFFF),
                                      narrowTo(Ity_I8, binop(Iop_Mul32,
                                                             mkU32(0x08),
                                                             mkexpr(t4))))));

         putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t5),
                                             mkexpr(t3)), True));
#endif
      } else {
         
         t1 = newTemp(Ity_I32);
#if defined (_MIPSEL)
         assign(t1, binop(Iop_Add32, getIReg(rs), mkU32(extend_s_16to32(imm))));
#elif defined (_MIPSEB)
         assign(t1, binop(Iop_Xor32, mkU32(0x3), binop(Iop_Add32, getIReg(rs),
                                     mkU32(extend_s_16to32(imm)))));
#endif

         
         
         LWX_SWX_PATTERN;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shl32, load(Ity_I32, mkexpr(t2)), narrowTo(Ity_I8,
                    binop(Iop_Shl32, binop(Iop_Sub32, mkU32(0x03), mkexpr(t4)),
                    mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32,
                          getIReg(rt),
                          binop(Iop_Shr32,
                                mkU32(0x00FFFFFF),
                                      narrowTo(Ity_I8, binop(Iop_Mul32,
                                                             mkU32(0x08),
                                                             mkexpr(t4))))));

         putIReg(rt, binop(Iop_Or32, mkexpr(t5), mkexpr(t3)));
      }
      break;

   case 0x26:  
      DIP("lwr r%d, %d(r%d)", rt, imm, rs);
      if (mode64) {
         
         t1 = newTemp(Ity_I64);
#if defined (_MIPSEL)
         assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));
         
         
         LWX_SWX_PATTERN64;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shr32, mkNarrowTo32(ty, load(Ity_I64,mkexpr(t2))),
                    narrowTo(Ity_I8, binop(Iop_Shl32, mkexpr(t4), mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32, mkNarrowTo32(ty, getIReg(rt)),
                unop(Iop_Not32, binop(Iop_Shr32, mkU32(0xFFFFFFFF),
                narrowTo(Ity_I8, binop(Iop_Shl32, mkexpr(t4), mkU8(0x3)))))));

         putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t5),
                                       mkexpr(t3)), True));
#elif defined (_MIPSEB)
         assign(t1, binop(Iop_Xor64, mkU64(0x3), binop(Iop_Add64, getIReg(rs),
                          mkU64(extend_s_16to64(imm)))));
         
         
         LWX_SWX_PATTERN64;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shr32, unop(Iop_64HIto32, load(Ity_I64,mkexpr(t2))),
                    narrowTo(Ity_I8, binop(Iop_Shl32, mkexpr(t4), mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32, mkNarrowTo32(ty, getIReg(rt)),
                unop(Iop_Not32, binop(Iop_Shr32, mkU32(0xFFFFFFFF),
                narrowTo(Ity_I8, binop(Iop_Shl32, mkexpr(t4), mkU8(0x3)))))));

         putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t5),
                                       mkexpr(t3)), True));
#endif

      } else {
         
         t1 = newTemp(Ity_I32);
#if defined (_MIPSEL)
         assign(t1, binop(Iop_Add32, getIReg(rs), mkU32(extend_s_16to32(imm))));
#elif defined (_MIPSEB)
         assign(t1, binop(Iop_Xor32, mkU32(0x3), binop(Iop_Add32, getIReg(rs),
                                     mkU32(extend_s_16to32(imm)))));
#endif

         
         
         LWX_SWX_PATTERN;

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_Shr32, load(Ity_I32, mkexpr(t2)),
                    narrowTo(Ity_I8, binop(Iop_Shl32, mkexpr(t4),
                    mkU8(3)))));

         
         t5 = newTemp(Ity_I32);
         assign(t5, binop(Iop_And32, getIReg(rt), unop(Iop_Not32,
                    binop(Iop_Shr32, mkU32(0xFFFFFFFF), narrowTo(Ity_I8,
                          binop(Iop_Shl32, mkexpr(t4), mkU8(0x3)))))));

         putIReg(rt, binop(Iop_Or32, mkexpr(t5), mkexpr(t3)));
      }
      break;

   case 0x2B:  
      DIP("sw r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      store(mkexpr(t1), mkNarrowTo32(ty, getIReg(rt)));
      break;

   case 0x2C: {  
      DIP("sdl r%u, %d(r%u)", rt, (Int) imm, rs);
      vassert(mode64);
      IRTemp A_byte = newTemp(Ity_I8);
      IRTemp B_byte = newTemp(Ity_I8);
      IRTemp C_byte = newTemp(Ity_I8);
      IRTemp D_byte = newTemp(Ity_I8);
      IRTemp E_byte = newTemp(Ity_I8);
      IRTemp F_byte = newTemp(Ity_I8);
      IRTemp G_byte = newTemp(Ity_I8);
      IRTemp H_byte = newTemp(Ity_I8);
      IRTemp B_pos  = newTemp(Ity_I64);
      IRTemp C_pos  = newTemp(Ity_I64);
      IRTemp D_pos  = newTemp(Ity_I64);
      IRTemp E_pos  = newTemp(Ity_I64);
      IRTemp F_pos  = newTemp(Ity_I64);
      IRTemp G_pos  = newTemp(Ity_I64);

      
      assign(H_byte, getByteFromReg(rt, 0));
      
      assign(G_byte, getByteFromReg(rt, 1));
      
      assign(F_byte, getByteFromReg(rt, 2));
      
      assign(E_byte, getByteFromReg(rt, 3));
      
      assign(D_byte, getByteFromReg(rt, 4));
      
      assign(C_byte, getByteFromReg(rt, 5));
      
      assign(B_byte, getByteFromReg(rt, 6));
      
      assign(A_byte, getByteFromReg(rt, 7));

      
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));

      
      t2 = newTemp(Ity_I64);
      assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFF8ULL)));

      
      t3 = newTemp(Ity_I64);
      assign(t3, binop(Iop_And64, mkexpr(t1), mkU64(0x7)));

#if defined (_MIPSEL)
      
      assign(B_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x1)),
                               mkU64(0x0),
                               mkU64(0x1)));

      assign(C_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x2)),
                               mkU64(0x0),
                               mkU64(0x2)));

      assign(D_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x3)),
                               mkU64(0x0),
                               mkU64(0x3)));

      assign(E_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x4)),
                               mkU64(0x0),
                               mkU64(0x4)));

      assign(F_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x5)),
                               mkU64(0x0),
                               mkU64(0x5)));

      assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x7)),
                               mkU64(0x1),
                               mkU64(0x0)));

      
      store(mkexpr(t2), mkexpr(H_byte));
      store(binop(Iop_Add64, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(E_pos)), mkexpr(E_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(D_pos)), mkexpr(D_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(C_pos)), mkexpr(C_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(B_pos)), mkexpr(B_byte));
      store(mkexpr(t1), mkexpr(A_byte));

#else 
      
      assign(B_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x7)),
                               mkU64(0x0),
                               mkU64(0x1)));

      assign(C_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x6)),
                               mkU64(0x2),
                               mkU64(0x0)));

      assign(D_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x5)),
                               mkU64(0x3),
                               mkU64(0x0)));

      assign(E_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x4)),
                               mkU64(0x4),
                               mkU64(0x0)));

      assign(F_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkexpr(t3), mkU64(0x3)),
                               mkU64(0x5),
                               mkU64(0x0)));

      assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                               mkU64(0x6),
                               mkU64(0x7)));

      
      store(binop(Iop_Add64, mkexpr(t2), mkU64(0x7)), mkexpr(H_byte));
      store(binop(Iop_Add64, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(E_pos)), mkexpr(E_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(D_pos)), mkexpr(D_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(C_pos)), mkexpr(C_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(B_pos)), mkexpr(B_byte));
      store(mkexpr(t1), mkexpr(A_byte));
#endif

      break;
   }

   case 0x2D: {
      
      vassert(mode64);
      DIP("sdr r%u, %d(r%u)", rt, imm, rs);
      IRTemp A_byte = newTemp(Ity_I8);
      IRTemp B_byte = newTemp(Ity_I8);
      IRTemp C_byte = newTemp(Ity_I8);
      IRTemp D_byte = newTemp(Ity_I8);
      IRTemp E_byte = newTemp(Ity_I8);
      IRTemp F_byte = newTemp(Ity_I8);
      IRTemp G_byte = newTemp(Ity_I8);
      IRTemp H_byte = newTemp(Ity_I8);
      IRTemp B_pos  = newTemp(Ity_I64);
      IRTemp C_pos  = newTemp(Ity_I64);
      IRTemp D_pos  = newTemp(Ity_I64);
      IRTemp E_pos  = newTemp(Ity_I64);
      IRTemp F_pos  = newTemp(Ity_I64);
      IRTemp G_pos  = newTemp(Ity_I64);

      
      assign(H_byte, getByteFromReg(rt, 0));
      
      assign(G_byte, getByteFromReg(rt, 1));
      
      assign(F_byte, getByteFromReg(rt, 2));
      
      assign(E_byte, getByteFromReg(rt, 3));
      
      assign(D_byte, getByteFromReg(rt, 4));
      
      assign(C_byte, getByteFromReg(rt, 5));
      
      assign(B_byte, getByteFromReg(rt, 6));
      
      assign(A_byte, getByteFromReg(rt, 7));

      
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));

      
      t2 = newTemp(Ity_I64);
      assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFF8ULL)));

      
      t3 = newTemp(Ity_I64);
      assign(t3, binop(Iop_And64, mkexpr(t1), mkU64(0x7)));

#if defined (_MIPSEL)
      
      assign(B_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x1), mkexpr(t3)),
                               mkU64(0x0),
                               mkU64(0x6)));

      assign(C_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x2), mkexpr(t3)),
                               mkU64(0x0),
                               mkU64(0x5)));

      assign(D_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x3), mkexpr(t3)),
                               mkU64(0x0),
                               mkU64(0x4)));

      assign(E_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x4), mkexpr(t3)),
                               mkU64(0x0),
                               mkU64(0x3)));

      assign(F_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x5), mkexpr(t3)),
                               mkU64(0x0),
                               mkU64(0x2)));

      assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x7)),
                               mkU64(0x0),
                               mkU64(0x1)));

      
      store(binop(Iop_Add64, mkexpr(t2), mkU64(0x7)), mkexpr(A_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(B_pos)), mkexpr(B_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(C_pos)), mkexpr(C_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(D_pos)), mkexpr(D_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(E_pos)), mkexpr(E_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
      store(binop(Iop_Add64, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
      store(mkexpr(t1), mkexpr(H_byte));

#else 
      
      assign(B_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x5), mkexpr(t3)),
                               mkU64(0x6),
                               mkU64(0x0)));

      assign(C_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x4), mkexpr(t3)),
                               mkU64(0x5),
                               mkU64(0x0)));

      assign(D_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x3), mkexpr(t3)),
                               mkU64(0x4),
                               mkU64(0x0)));

      assign(E_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x2), mkexpr(t3)),
                               mkU64(0x3),
                               mkU64(0x0)));

      assign(F_pos, IRExpr_ITE(binop(Iop_CmpLT64U, mkU64(0x1), mkexpr(t3)),
                               mkU64(0x2),
                               mkU64(0x0)));

      assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                               mkU64(0x0),
                               mkU64(0x1)));

      
      store(mkexpr(t2), mkexpr(A_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(B_pos)), mkexpr(B_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(C_pos)), mkexpr(C_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(D_pos)), mkexpr(D_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(E_pos)), mkexpr(E_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
      store(binop(Iop_Sub64, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
      store(mkexpr(t1), mkexpr(H_byte));
#endif
      break;
   }

   case 0x28:  
      DIP("sb r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      store(mkexpr(t1), narrowTo(Ity_I8, getIReg(rt)));
      break;

   case 0x29:  
      DIP("sh r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      store(mkexpr(t1), narrowTo(Ity_I16, getIReg(rt)));
      break;

   case 0x2A:  
      DIP("swl r%d, %d(r%d)", rt, imm, rs);
      if (mode64) {
         IRTemp E_byte = newTemp(Ity_I8);
         IRTemp F_byte = newTemp(Ity_I8);
         IRTemp G_byte = newTemp(Ity_I8);
         IRTemp H_byte = newTemp(Ity_I8);
         IRTemp F_pos  = newTemp(Ity_I64);
         IRTemp G_pos  = newTemp(Ity_I64);

         
         assign(H_byte, getByteFromReg(rt, 0));
         
         assign(G_byte, getByteFromReg(rt, 1));
         
         assign(F_byte, getByteFromReg(rt, 2));
         
         assign(E_byte, getByteFromReg(rt, 3));

         
         t1 = newTemp(Ity_I64);
         assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));

         
         t2 = newTemp(Ity_I64);
         assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFFCULL)));

         
         t3 = newTemp(Ity_I64);
         assign(t3, binop(Iop_And64, mkexpr(t1), mkU64(0x3)));

#if defined (_MIPSEL)
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                                  mkU64(0x0),
                                  mkU64(0x1)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x3)),
                                  mkU64(0x1),
                                  mkU64(0x0)));

         
         store(mkexpr(t2), mkexpr(H_byte));
         store(binop(Iop_Add64, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
         store(binop(Iop_Sub64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
         store(mkexpr(t1), mkexpr(E_byte));

#else    
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x3)),
                                  mkU64(0x0),
                                  mkU64(0x1)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                                  mkU64(0x2),
                                  mkU64(0x3)));

         store(binop(Iop_Add64, mkexpr(t2), mkU64(3)), mkexpr(H_byte));
         store(binop(Iop_Add64, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
         store(binop(Iop_Add64, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
         store(mkexpr(t1), mkexpr(E_byte));

#endif
      } else {
         IRTemp E_byte = newTemp(Ity_I8);
         IRTemp F_byte = newTemp(Ity_I8);
         IRTemp G_byte = newTemp(Ity_I8);
         IRTemp H_byte = newTemp(Ity_I8);
         IRTemp F_pos  = newTemp(Ity_I32);
         IRTemp G_pos  = newTemp(Ity_I32);

         
         assign(H_byte, getByteFromReg(rt, 0));
         
         assign(G_byte, getByteFromReg(rt, 1));
         
         assign(F_byte, getByteFromReg(rt, 2));
         
         assign(E_byte, getByteFromReg(rt, 3));

         
         t1 = newTemp(Ity_I32);
         assign(t1, binop(Iop_Add32, getIReg(rs), mkU32(extend_s_16to32(imm))));

         
         t2 = newTemp(Ity_I32);
         assign(t2, binop(Iop_And32, mkexpr(t1), mkU32(0xFFFFFFFCULL)));

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_And32, mkexpr(t1), mkU32(0x3)));

#if defined (_MIPSEL)
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x0)),
                                  mkU32(0x0),
                                  mkU32(0x1)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x3)),
                                  mkU32(0x1),
                                  mkU32(0x0)));

         
         store(mkexpr(t2), mkexpr(H_byte));
         store(binop(Iop_Add32, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
         store(binop(Iop_Sub32, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
         store(mkexpr(t1), mkexpr(E_byte));

#else    
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x3)),
                                  mkU32(0x0),
                                  mkU32(0x1)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x0)),
                                  mkU32(0x2),
                                  mkU32(0x3)));

         store(binop(Iop_Add32, mkexpr(t2), mkU32(3)), mkexpr(H_byte));
         store(binop(Iop_Add32, mkexpr(t2), mkexpr(G_pos)), mkexpr(G_byte));
         store(binop(Iop_Add32, mkexpr(t1), mkexpr(F_pos)), mkexpr(F_byte));
         store(mkexpr(t1), mkexpr(E_byte));

#endif
      }
      break;

   case 0x2E:  
      DIP("swr r%d, %d(r%d)", rt, imm, rs);
      if (mode64) {
         IRTemp E_byte = newTemp(Ity_I8);
         IRTemp F_byte = newTemp(Ity_I8);
         IRTemp G_byte = newTemp(Ity_I8);
         IRTemp H_byte = newTemp(Ity_I8);
         IRTemp F_pos  = newTemp(Ity_I64);
         IRTemp G_pos  = newTemp(Ity_I64);

         
         assign(H_byte, getByteFromReg(rt, 0));
         
         assign(G_byte, getByteFromReg(rt, 1));
         
         assign(F_byte, getByteFromReg(rt, 2));
         
         assign(E_byte, getByteFromReg(rt, 3));

         
         t1 = newTemp(Ity_I64);
         assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));

         
         t2 = newTemp(Ity_I64);
         assign(t2, binop(Iop_And64, mkexpr(t1), mkU64(0xFFFFFFFFFFFFFFFCULL)));

         
         t3 = newTemp(Ity_I64);
         assign(t3, binop(Iop_And64, mkexpr(t1), mkU64(0x3)));

#if defined (_MIPSEL)
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                                  mkU64(0x2),
                                  mkU64(0x3)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x3)),
                                  mkU64(0x0),
                                  mkU64(0x1)));

         
         store(binop(Iop_Add64, mkexpr(t2), mkU64(0x3)), mkexpr(E_byte));
         store(binop(Iop_Add64, mkexpr(t2), mkexpr(F_pos)), mkexpr(F_byte));
         store(binop(Iop_Add64, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
         store(mkexpr(t1), mkexpr(H_byte));

#else    
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x3)),
                                  mkU64(0x1),
                                  mkU64(0x0)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ64, mkexpr(t3), mkU64(0x0)),
                                  mkU64(0x0),
                                  mkU64(0x1)));

         
         store(mkexpr(t2), mkexpr(E_byte));
         store(binop(Iop_Add64, mkexpr(t2), mkexpr(F_pos)), mkexpr(F_byte));
         store(binop(Iop_Sub64, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
         store(mkexpr(t1), mkexpr(H_byte));
#endif
      } else {
         IRTemp E_byte = newTemp(Ity_I8);
         IRTemp F_byte = newTemp(Ity_I8);
         IRTemp G_byte = newTemp(Ity_I8);
         IRTemp H_byte = newTemp(Ity_I8);
         IRTemp F_pos  = newTemp(Ity_I32);
         IRTemp G_pos  = newTemp(Ity_I32);

         
         assign(H_byte, getByteFromReg(rt, 0));
         
         assign(G_byte, getByteFromReg(rt, 1));
         
         assign(F_byte, getByteFromReg(rt, 2));
         
         assign(E_byte, getByteFromReg(rt, 3));

         
         t1 = newTemp(Ity_I32);
         assign(t1, binop(Iop_Add32, getIReg(rs), mkU32(extend_s_16to32(imm))));

         
         t2 = newTemp(Ity_I32);
         assign(t2, binop(Iop_And32, mkexpr(t1), mkU32(0xFFFFFFFCULL)));

         
         t3 = newTemp(Ity_I32);
         assign(t3, binop(Iop_And32, mkexpr(t1), mkU32(0x3)));

#if defined (_MIPSEL)
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x0)),
                                  mkU32(0x2),
                                  mkU32(0x3)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x3)),
                                  mkU32(0x0),
                                  mkU32(0x1)));

         
         store(binop(Iop_Add32, mkexpr(t2), mkU32(0x3)), mkexpr(E_byte));
         store(binop(Iop_Add32, mkexpr(t2), mkexpr(F_pos)), mkexpr(F_byte));
         store(binop(Iop_Add32, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
         store(mkexpr(t1), mkexpr(H_byte));

#else    
         
         assign(F_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x3)),
                                  mkU32(0x1),
                                  mkU32(0x0)));

         assign(G_pos, IRExpr_ITE(binop(Iop_CmpEQ32, mkexpr(t3), mkU32(0x0)),
                                  mkU32(0x0),
                                  mkU32(0x1)));

         
         store(mkexpr(t2), mkexpr(E_byte));
         store(binop(Iop_Add32, mkexpr(t2), mkexpr(F_pos)), mkexpr(F_byte));
         store(binop(Iop_Sub32, mkexpr(t1), mkexpr(G_pos)), mkexpr(G_byte));
         store(mkexpr(t1), mkexpr(H_byte));
#endif
      }
      break;

   case 0x1C:  
      switch (function) {
      
      case 0x03: case 0x32: case 0x33:  
      case 0x3A: case 0x3B: case 0x2B:  
      
      case 0x2A: case 0x2E: case 0x2F:  
         if (VEX_MIPS_COMP_ID(archinfo->hwcaps) == VEX_PRID_COMP_CAVIUM) {
            if (dis_instr_CVM(cins))
               break;
            goto decode_failure;
         } else {
            goto decode_failure;
         }
         break;
      case 0x02: {  
         DIP("mul r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            IRTemp tmpRs32 = newTemp(Ity_I32);
            IRTemp tmpRt32 = newTemp(Ity_I32);
            IRTemp tmpRes = newTemp(Ity_I32);

            assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));
            assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
            assign(tmpRes, binop(Iop_Mul32, mkexpr(tmpRs32), mkexpr(tmpRt32)));
            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpRes), True));
         } else
            putIReg(rd, binop(Iop_Mul32, getIReg(rs), getIReg(rt)));
         break;
      }

         case 0x00: {  
            if (mode64) {
               DIP("madd r%d, r%d", rs, rt);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I64);
               t4 = newTemp(Ity_I64);
               t5 = newTemp(Ity_I64);
               t6 = newTemp(Ity_I32);

               assign(t1, mkNarrowTo32(ty, getHI()));
               assign(t2, mkNarrowTo32(ty, getLO()));

               assign(t3, binop(Iop_MullS32, mkNarrowTo32(ty, getIReg(rs)),
                                             mkNarrowTo32(ty, getIReg(rt))));

               assign(t4, binop(Iop_32HLto64, mkexpr(t1), mkexpr(t2)));
               assign(t5, binop(Iop_Add64, mkexpr(t3), mkexpr(t4)));

               putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t5)), True));
               putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t5)), True));
            } else {
               if ( (1 <= ac) && ( 3 >= ac) ) {
                  if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                     
                     UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                     if (0 != retVal ) {
                        goto decode_failure_dsp;
                     }
                     break;
                  } else {
                     goto decode_failure_dsp;
                  }
               } else {
                  DIP("madd r%d, r%d", rs, rt);
                  t1 = newTemp(Ity_I32);
                  t2 = newTemp(Ity_I32);
                  t3 = newTemp(Ity_I64);
                  t4 = newTemp(Ity_I32);
                  t5 = newTemp(Ity_I32);
                  t6 = newTemp(Ity_I32);

                  assign(t1, getHI());
                  assign(t2, getLO());

                  assign(t3, binop(Iop_MullS32, getIReg(rs), getIReg(rt)));

                  assign(t4, binop(Iop_Add32, mkexpr(t2), unop(Iop_64to32,
                                                               mkexpr(t3))));

                  assign(t5, unop(Iop_1Uto32, binop(Iop_CmpLT32U, mkexpr(t4),
                                              unop(Iop_64to32, mkexpr(t3)))));
                  assign(t6, binop(Iop_Add32, mkexpr(t5), mkexpr(t1)));

                  putHI(binop(Iop_Add32, mkexpr(t6), unop(Iop_64HIto32,
                                                          mkexpr(t3))));
                  putLO(mkexpr(t4));
                  break;
               }
            }
            break;
         }

      case 0x01: {  
         if (mode64) {
            DIP("maddu r%d, r%d", rs, rt);
            t1 = newTemp(Ity_I32);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I64);
            t4 = newTemp(Ity_I64);
            t5 = newTemp(Ity_I64);
            t6 = newTemp(Ity_I32);

            assign(t1, mkNarrowTo32(ty, getHI()));
            assign(t2, mkNarrowTo32(ty, getLO()));

            assign(t3, binop(Iop_MullU32, mkNarrowTo32(ty, getIReg(rs)),
                                          mkNarrowTo32(ty, getIReg(rt))));

            assign(t4, binop(Iop_32HLto64, mkexpr(t1), mkexpr(t2)));
            assign(t5, binop(Iop_Add64, mkexpr(t3), mkexpr(t4)));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t5)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t5)), True));
         } else {
            if ( (1 <= ac) && ( 3 >= ac) ) {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
            } else {
               DIP("maddu r%d, r%d", rs, rt);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I64);
               t4 = newTemp(Ity_I32);
               t5 = newTemp(Ity_I32);
               t6 = newTemp(Ity_I32);

               assign(t1, getHI());
               assign(t2, getLO());

               assign(t3, binop(Iop_MullU32, getIReg(rs), getIReg(rt)));

               assign(t4, binop(Iop_Add32, mkexpr(t2), unop(Iop_64to32,
                                                            mkexpr(t3))));
               assign(t5, unop(Iop_1Uto32, binop(Iop_CmpLT32U, mkexpr(t4),
                                           unop(Iop_64to32, mkexpr(t3)))));
               assign(t6, binop(Iop_Add32, mkexpr(t5), mkexpr(t1)));

               putHI(binop(Iop_Add32, mkexpr(t6), unop(Iop_64HIto32,
                                                      mkexpr(t3))));
               putLO(mkexpr(t4));
               break;
            }
         }
         break;
      }

      case 0x04: {  
         if (mode64) {
            DIP("msub r%d, r%d", rs, rt);
            t1 = newTemp(Ity_I32);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I64);
            t4 = newTemp(Ity_I64);
            t5 = newTemp(Ity_I64);
            t6 = newTemp(Ity_I32);

            assign(t1, mkNarrowTo32(ty, getHI()));
            assign(t2, mkNarrowTo32(ty, getLO()));

            assign(t3, binop(Iop_MullS32, mkNarrowTo32(ty, getIReg(rs)),
                                          mkNarrowTo32(ty, getIReg(rt))));

            assign(t4, binop(Iop_32HLto64, mkexpr(t1), mkexpr(t2)));
            assign(t5, binop(Iop_Sub64, mkexpr(t4), mkexpr(t3)));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t5)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t5)), True));
         } else {
            if ( (1 <= ac) && ( 3 >= ac) ) {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
            } else {
               DIP("msub r%d, r%d", rs, rt);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I64);
               t4 = newTemp(Ity_I32);
               t5 = newTemp(Ity_I1);
               t6 = newTemp(Ity_I32);

               assign(t1, getHI());
               assign(t2, getLO());

               assign(t3, binop(Iop_MullS32, getIReg(rs), getIReg(rt)));
               assign(t4, unop(Iop_64to32, mkexpr(t3)));  

               
               assign(t5, binop(Iop_CmpLT32U,
                                 mkexpr(t2),
                                 mkexpr(t4)));

               assign(t6, IRExpr_ITE(mkexpr(t5),
                                       binop(Iop_Sub32, mkexpr(t1), mkU32(0x1)),
                                       mkexpr(t1)));

               putHI(binop(Iop_Sub32, mkexpr(t6), unop(Iop_64HIto32,
                                                      mkexpr(t3))));
               putLO(binop(Iop_Sub32, mkexpr(t2), mkexpr(t4)));
               break;
            }
         }
         break;
      }

      case 0x05: {  
         if (mode64) {
            DIP("msubu r%d, r%d", rs, rt);
            t1 = newTemp(Ity_I32);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I64);
            t4 = newTemp(Ity_I64);
            t5 = newTemp(Ity_I64);
            t6 = newTemp(Ity_I32);

            assign(t1, mkNarrowTo32(ty, getHI()));
            assign(t2, mkNarrowTo32(ty, getLO()));

            assign(t3, binop(Iop_MullU32, mkNarrowTo32(ty, getIReg(rs)),
                                          mkNarrowTo32(ty, getIReg(rt))));

            assign(t4, binop(Iop_32HLto64, mkexpr(t1), mkexpr(t2)));
            assign(t5, binop(Iop_Sub64, mkexpr(t4), mkexpr(t3)));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t5)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t5)), True));
         } else {
            if ( (1 <= ac) && ( 3 >= ac) ) {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
            } else {
               DIP("msubu r%d, r%d", rs, rt);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I64);
               t4 = newTemp(Ity_I32);
               t5 = newTemp(Ity_I1);
               t6 = newTemp(Ity_I32);

               assign(t1, getHI());
               assign(t2, getLO());

               assign(t3, binop(Iop_MullU32, getIReg(rs), getIReg(rt)));
               assign(t4, unop(Iop_64to32, mkexpr(t3)));  

               
               assign(t5, binop(Iop_CmpLT32U,
                                 mkexpr(t2),
                                 mkexpr(t4)));

               assign(t6, IRExpr_ITE(mkexpr(t5),
                                    binop(Iop_Sub32,
                                          mkexpr(t1),
                                          mkU32(0x1)),
                                    mkexpr(t1)));

               putHI(binop(Iop_Sub32, mkexpr(t6), unop(Iop_64HIto32,
                                                      mkexpr(t3))));
               putLO(binop(Iop_Sub32, mkexpr(t2), mkexpr(t4)));
               break;
            }
         }
         break;
      }

      case 0x6:  
         DIP("dmul r%u, r%u, r%u", rd, rs, rt);
         t0 = newTemp(Ity_I128);

         assign(t0, binop(Iop_MullU64, getIReg(rs), getIReg(rt)));

         putIReg(rd, unop(Iop_128to64, mkexpr(t0)));
         break;

      case 0x10:  
         DIP("ldaddw r%u, r%u", rt, rs);
         t0 = newTemp(Ity_I32);
         t1 = newTemp(Ity_I32);
         t2 = newTemp(Ity_I32);
         t3 = newTemp(Ity_I64);
         t4 = newTemp(Ity_I32);
         t5 = newTemp(Ity_I32);
         t6 = newTemp(Ity_I32);

         
         assign(t0, mkNarrowTo32(ty, getIReg(rt)));

         
         assign(t1, load(Ity_I32, getIReg(rs)));
         putIReg(rt, mkWidenFrom32(ty, mkexpr(t1), True));

         
         store(getIReg(rs), binop(Iop_Add32, mkexpr(t0), mkexpr(t1)));
         break;

      case 0x12:  
         DIP("ldaddw r%u, r%u", rt, rs);
         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);

         
         assign(t0, getIReg(rt));

         
         assign(t1, load(Ity_I64, getIReg(rs)));
         putIReg(rt, mkexpr(t1));

         
         store(getIReg(rs), binop(Iop_Add64, mkexpr(t0), mkexpr(t1)));
         break;

      case 0x14:  
         DIP("swapw r%u, r%u", rt, rs);
         t0 = newTemp(Ity_I32);
         t1 = newTemp(Ity_I32);
         assign(t0, mkNarrowTo32(ty, getIReg(rt)));
         assign(t1, load(Ity_I32, getIReg(rs)));
         putIReg(rt, mkWidenFrom32(ty, mkexpr(t1), True));
         store(getIReg(rs), mkexpr(t0));
         break;

      case 0x16:  
         DIP("swapw r%u, r%u", rt, rs);
         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);
         assign(t0, getIReg(rt));
         assign(t1, load(Ity_I64, getIReg(rs)));
         putIReg(rt, mkexpr(t1));
         store(getIReg(rs), mkexpr(t0));
         break;

      case 0x20: {  
         DIP("clz r%d, r%d", rd, rs);
         if (mode64) {
            IRTemp tmpClz32 = newTemp(Ity_I32);
            IRTemp tmpRs32 = newTemp(Ity_I32);

            assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));
            assign(tmpClz32, unop(Iop_Clz32, mkexpr(tmpRs32)));
            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpClz32), True));
         } else {
            t1 = newTemp(Ity_I1);
            assign(t1, binop(Iop_CmpEQ32, getIReg(rs), mkU32(0)));
            putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                   mkU32(0x00000020),
                                   unop(Iop_Clz32, getIReg(rs))));
         }
         break;
      }

      case 0x21: {  
         DIP("clo r%d, r%d", rd, rs);
         if (mode64) {
            IRTemp tmpClo32 = newTemp(Ity_I32);
            IRTemp tmpRs32 = newTemp(Ity_I32);
            assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));

            t1 = newTemp(Ity_I1);
            assign(t1, binop(Iop_CmpEQ32, mkexpr(tmpRs32), mkU32(0xffffffff)));
            assign(tmpClo32, IRExpr_ITE(mkexpr(t1),
                      mkU32(0x00000020),
                      unop(Iop_Clz32, unop(Iop_Not32, mkexpr(tmpRs32)))));

            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpClo32), True));
            break;
         } else {
            t1 = newTemp(Ity_I1);
            assign(t1, binop(Iop_CmpEQ32, getIReg(rs), mkU32(0xffffffff)));
            putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                   mkU32(0x00000020),
                                   unop(Iop_Clz32,
                                        unop(Iop_Not32, getIReg(rs)))));
            break;
         }
      }

      case 0x24:  
         DIP("dclz r%d, r%d", rd, rs);
         t1 = newTemp(Ity_I1);
         assign(t1, binop(Iop_CmpEQ64, getIReg(rs), mkU64(0)));
         putIReg(rd, IRExpr_ITE(mkexpr(t1),
                     mkU64(0x00000040),
                     unop(Iop_Clz64, getIReg(rs))));
         break;

      case 0x25:  
         DIP("dclo r%d, r%d", rd, rs);
         t1 = newTemp(Ity_I1);
         assign(t1, binop(Iop_CmpEQ64, getIReg(rs),
                                        mkU64(0xffffffffffffffffULL)));
         putIReg(rd, IRExpr_ITE(mkexpr(t1),
                                mkU64(0x40),
                                unop(Iop_Clz64, unop(Iop_Not64,
                                                     getIReg(rs)))));
         break;

      default:
         goto decode_failure;
      }
      break;

   case 0x1F:  
      switch (function) {
         case 0x01: {
            
            msb = get_msb(cins);
            lsb = get_lsb(cins);
            size = msb + 1;
            UInt srcPos = lsb;
            UInt dstSz = msb + 33;
            t1 = newTemp(Ity_I64);
            DIP("dextm r%u, r%u, %d, %d", rt, rs, lsb, msb + 1);

            UChar lsAmt = 64 - (srcPos + dstSz);  
            UChar rsAmt = 64 - dstSz;  

            assign(t1, binop(Iop_Shl64, getIReg(rs), mkU8(lsAmt)));
            putIReg(rt, binop(Iop_Shr64, mkexpr(t1), mkU8(rsAmt)));

            break;
         }
         case 0x02: {
            
            msb = get_msb(cins);
            lsb = get_lsb(cins);
            size = msb + 1;
            UInt srcPos = lsb + 32;
            UInt dstSz = msb + 1;
            DIP("dextu r%u, r%u, %d, %d", rt, rs, srcPos, dstSz);
            t1 = newTemp(Ity_I64);

            vassert(srcPos >= 32 && srcPos < 64);
            vassert(dstSz > 0 && dstSz <= 32);
            vassert((srcPos + dstSz) > 32 && (srcPos + dstSz) <= 64);

            UChar lsAmt = 64 - (srcPos + dstSz);  
            UChar rsAmt = 64 - dstSz;  

            assign(t1, binop(Iop_Shl64, getIReg(rs), mkU8(lsAmt)));
            putIReg(rt, binop(Iop_Shr64, mkexpr(t1), mkU8(rsAmt)));
            break;
         }
         case 0x05: {
            
            msb = get_msb(cins);
            lsb = get_lsb(cins);
            size = msb + 1;
            UInt dstPos = lsb;
            UInt srcSz = msb - lsb + 33;
            t1 = newTemp(ty);
            t2 = newTemp(ty);
            t3 = newTemp(ty);
            t4 = newTemp(ty);
            IRTemp tmpT1 = newTemp(ty);
            IRTemp tmpT2 = newTemp(ty);
            IRTemp tmpT3 = newTemp(ty);
            IRTemp tmpT4 = newTemp(ty);
            IRTemp tmpT5 = newTemp(ty);
            IRTemp tmpT6 = newTemp(ty);
            IRTemp tmpT7 = newTemp(ty);
            IRTemp tmpRs = newTemp(ty);
            IRTemp tmpRt = newTemp(ty);
            IRTemp tmpRd = newTemp(ty);

            assign(tmpRs, getIReg(rs));
            assign(tmpRt, getIReg(rt));
            DIP("dinsm r%u, r%u, %d, %d", rt, rs, lsb, msb);

            UChar lsAmt = dstPos + srcSz - 1;   
            UChar rsAmt = dstPos + srcSz - 1;   

            assign(t1, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(rsAmt)));
            assign(tmpT1, binop(Iop_Shr64, mkexpr(t1), mkU8(1)));
            assign(t2, binop(Iop_Shl64, mkexpr(tmpT1), mkU8(lsAmt)));
            assign(tmpT2, binop(Iop_Shl64, mkexpr(t2), mkU8(1)));

            lsAmt = 63 - dstPos; 
            rsAmt = 63 - dstPos; 

            assign(t3, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(lsAmt)));
            assign(tmpT3, binop(Iop_Shl64, mkexpr(t3), mkU8(1)));
            assign(t4, binop(Iop_Shr64, mkexpr(tmpT3), mkU8(rsAmt)));
            assign(tmpT4, binop(Iop_Shr64, mkexpr(t4), mkU8(1)));

            
            lsAmt = 64 - srcSz;  
            rsAmt = 64 - (lsb + srcSz);   

            assign(tmpT5, binop(Iop_Shl64, mkexpr(tmpRs), mkU8(lsAmt)));
            assign(tmpT6, binop(Iop_Shr64, mkexpr(tmpT5), mkU8(rsAmt)));

            assign(tmpT7, binop(Iop_Or64, mkexpr(tmpT2), mkexpr(tmpT4)));
            assign(tmpRd, binop(Iop_Or64, mkexpr(tmpT6), mkexpr(tmpT7)));
            putIReg(rt, mkexpr(tmpRd));
            break;
         }
         case 0x06: {
            
            msb = get_msb(cins);
            lsb = get_lsb(cins);
            size = msb + 1;
            UInt dstPos = lsb + 32;
            UInt srcSz = msb - lsb + 1;
            IRTemp tmpT1 = newTemp(ty);
            IRTemp tmpT2 = newTemp(ty);
            IRTemp tmpT3 = newTemp(ty);
            IRTemp tmpT4 = newTemp(ty);
            IRTemp tmpT5 = newTemp(ty);
            IRTemp tmpT6 = newTemp(ty);
            IRTemp tmpT7 = newTemp(ty);
            IRTemp tmpT8 = newTemp(ty);
            IRTemp tmpT9 = newTemp(ty);
            IRTemp tmpRs = newTemp(ty);
            IRTemp tmpRt = newTemp(ty);
            IRTemp tmpRd = newTemp(ty);

            assign(tmpRs, getIReg(rs));
            assign(tmpRt, getIReg(rt));
            DIP("dinsu r%u, r%u, %d, %d", rt, rs, lsb, msb);

            UChar lsAmt = 64 - srcSz;  
            UChar rsAmt = 64 - (dstPos + srcSz);  
            assign(tmpT1, binop(Iop_Shl64, mkexpr(tmpRs), mkU8(lsAmt)));
            assign(tmpT2, binop(Iop_Shr64, mkexpr(tmpT1), mkU8(rsAmt)));

            lsAmt = 64 - dstPos;  
            rsAmt = 64 - dstPos;  
            assign(tmpT3, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(lsAmt)));
            assign(tmpT4, binop(Iop_Shr64, mkexpr(tmpT3), mkU8(rsAmt)));

            lsAmt = dstPos;  
            rsAmt = srcSz;  
            assign(tmpT5, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(rsAmt)));
            assign(tmpT6, binop(Iop_Shr64, mkexpr(tmpT5), mkU8(lsAmt)));

            assign(tmpT7, binop(Iop_Shl64, mkexpr(tmpT6), mkU8(rsAmt)));
            assign(tmpT8, binop(Iop_Shl64, mkexpr(tmpT7), mkU8(lsAmt)));

            assign(tmpT9, binop(Iop_Or64, mkexpr(tmpT8), mkexpr(tmpT4)));
            assign(tmpRd, binop(Iop_Or64, mkexpr(tmpT2), mkexpr(tmpT9)));
            putIReg(rt, mkexpr(tmpRd));
            break;
         }
         case 0x07: {
            
            IRTemp tmp1 = newTemp(ty);
            IRTemp tmpT1 = newTemp(ty);
            IRTemp tmpT2 = newTemp(ty);
            IRTemp tmpT3 = newTemp(ty);
            IRTemp tmpT4 = newTemp(ty);
            IRTemp tmpT5 = newTemp(ty);
            IRTemp tmpT6 = newTemp(ty);
            IRTemp tmpT7 = newTemp(ty);
            IRTemp tmpT8 = newTemp(ty);
            IRTemp tmpT9 = newTemp(ty);
            IRTemp tmp = newTemp(ty);
            IRTemp tmpRs = newTemp(ty);
            IRTemp tmpRt = newTemp(ty);
            IRTemp tmpRd = newTemp(ty);

            assign(tmpRs, getIReg(rs));
            assign(tmpRt, getIReg(rt));

            msb = get_msb(cins);
            lsb = get_lsb(cins);
            size = msb + 1;
            DIP("dins r%u, r%u, %d, %d", rt, rs, lsb,
                msb - lsb + 1);
            UChar lsAmt = 63 - lsb;  
            UChar rsAmt = 63 - lsb;  
            assign(tmp, binop(Iop_Shl64, mkexpr(tmpRt), mkU8(lsAmt)));
            assign(tmpT1, binop(Iop_Shl64, mkexpr(tmp), mkU8(1)));
            assign(tmp1, binop(Iop_Shr64, mkexpr(tmpT1), mkU8(rsAmt)));
            assign(tmpT2, binop(Iop_Shr64, mkexpr(tmp1), mkU8(1)));

            lsAmt = msb;  
            rsAmt = 1;  
            assign(tmpT3, binop(Iop_Shr64, mkexpr(tmpRt), mkU8(rsAmt)));
            assign(tmpT4, binop(Iop_Shr64, mkexpr(tmpT3), mkU8(lsAmt)));
            assign(tmpT5, binop(Iop_Shl64, mkexpr(tmpT4), mkU8(rsAmt)));
            assign(tmpT6, binop(Iop_Shl64, mkexpr(tmpT5), mkU8(lsAmt)));

            lsAmt = 64 - (msb - lsb + 1);  
            rsAmt = 64 - (msb + 1);  
            assign(tmpT7, binop(Iop_Shl64, mkexpr(tmpRs), mkU8(lsAmt)));
            assign(tmpT8, binop(Iop_Shr64, mkexpr(tmpT7), mkU8(rsAmt)));

            assign(tmpT9, binop(Iop_Or64, mkexpr(tmpT2), mkexpr(tmpT8)));
            assign(tmpRd, binop(Iop_Or64, mkexpr(tmpT6), mkexpr(tmpT9)));
            putIReg(rt, mkexpr(tmpRd));
            break;
         }
      case 0x24:  
         lsb = get_lsb(cins);
         IRTemp tmpRs = newTemp(ty);
         IRTemp tmpRt = newTemp(ty);
         IRTemp tmpRd = newTemp(ty);
         assign(tmpRs, getIReg(rs));
         assign(tmpRt, getIReg(rt));
         switch (lsb) {
            case 0x02: {  
               DIP("dsbh r%u, r%u", rd, rt);
               IRTemp tmpT1 = newTemp(ty);
               IRTemp tmpT2 = newTemp(ty);
               IRTemp tmpT3 = newTemp(ty);
               IRTemp tmpT4 = newTemp(ty);
               IRTemp tmpT5 = newTemp(Ity_I64);
               IRTemp tmpT6 = newTemp(ty);
               assign(tmpT5, mkU64(0xFF00FF00FF00FF00ULL));
               assign(tmpT6, mkU64(0x00FF00FF00FF00FFULL));
               assign(tmpT1, binop(Iop_And64, mkexpr(tmpRt), mkexpr(tmpT5)));
               assign(tmpT2, binop(Iop_Shr64, mkexpr(tmpT1), mkU8(8)));
               assign(tmpT3, binop(Iop_And64, mkexpr(tmpRt), mkexpr(tmpT6)));
               assign(tmpT4, binop(Iop_Shl64, mkexpr(tmpT3), mkU8(8)));
               assign(tmpRd, binop(Iop_Or64, mkexpr(tmpT4), mkexpr(tmpT2)));
               putIReg(rd, mkexpr(tmpRd));
               break;
            }
            case 0x05: {  
               DIP("dshd r%u, r%u\n", rd, rt);
               IRTemp tmpT1 = newTemp(ty);
               IRTemp tmpT2 = newTemp(ty);
               IRTemp tmpT3 = newTemp(ty);
               IRTemp tmpT4 = newTemp(ty);
               IRTemp tmpT5 = newTemp(Ity_I64);
               IRTemp tmpT6 = newTemp(ty);
               IRTemp tmpT7 = newTemp(ty);
               IRTemp tmpT8 = newTemp(ty);
               IRTemp tmpT9 = newTemp(ty);
               assign(tmpT5, mkU64(0xFFFF0000FFFF0000ULL));
               assign(tmpT6, mkU64(0x0000FFFF0000FFFFULL));
               assign(tmpT1, binop(Iop_And64, mkexpr(tmpRt), mkexpr(tmpT5)));
               assign(tmpT2, binop(Iop_Shr64, mkexpr(tmpT1), mkU8(16)));
               assign(tmpT3, binop(Iop_And64, mkexpr(tmpRt), mkexpr(tmpT6)));
               assign(tmpT4, binop(Iop_Shl64, mkexpr(tmpT3), mkU8(16)));
               assign(tmpT7, binop(Iop_Or64, mkexpr(tmpT4), mkexpr(tmpT2)));
               assign(tmpT8, binop(Iop_Shl64, mkexpr(tmpT7), mkU8(32)));
               assign(tmpT9, binop(Iop_Shr64, mkexpr(tmpT7), mkU8(32)));
               assign(tmpRd, binop(Iop_Or64, mkexpr(tmpT8), mkexpr(tmpT9)));
               putIReg(rd, mkexpr(tmpRd));
               break;
            }
         default:
            vex_printf("\nop6o10 = %d", lsb);
            goto decode_failure;;
         }
         break;
      case 0x3B: {  
         DIP("rdhwr r%d, r%d", rt, rd);
            if (rd == 29) {
               putIReg(rt, getULR());
#if defined(__mips__) && ((defined(__mips_isa_rev) && __mips_isa_rev >= 2))
            } else if (rd == 1) {
               if (mode64) {
                  IRTemp   val  = newTemp(Ity_I64);
                  IRExpr** args = mkIRExprVec_2 (mkU64(rt), mkU64(rd));
                  IRDirty *d = unsafeIRDirty_1_N(val,
                                                 0,
                                                 "mips64_dirtyhelper_rdhwr",
                                                 &mips64_dirtyhelper_rdhwr,
                                                 args);
                  stmt(IRStmt_Dirty(d));
                  putIReg(rt, mkexpr(val));
               } else {
                  IRTemp   val  = newTemp(Ity_I32);
                  IRExpr** args = mkIRExprVec_2 (mkU32(rt), mkU32(rd));
                  IRDirty *d = unsafeIRDirty_1_N(val,
                                                 0,
                                                 "mips32_dirtyhelper_rdhwr",
                                                 &mips32_dirtyhelper_rdhwr,
                                                 args);
                  stmt(IRStmt_Dirty(d));
                  putIReg(rt, mkexpr(val));
               }
#endif
            } else
               goto decode_failure;
            break;
         }
      case 0x04:  
         msb = get_msb(cins);
         lsb = get_lsb(cins);
         size = msb - lsb + 1;
         DIP("ins size:%d msb:%d lsb:%d", size, msb, lsb);

         vassert(lsb + size <= 32);
         vassert(lsb + size > 0);

         
         t0 = newTemp(Ity_I32);
         t3 = newTemp(Ity_I32);
         assign(t0, binop(Iop_Shl32, mkNarrowTo32(ty, getIReg(rs)),
                          mkU8(32 - size)));
         
         t1 = newTemp(Ity_I32);
         assign(t1, binop(Iop_Shr32, mkexpr(t0), mkU8(32 - size - lsb)));

         if (lsb > 0) {
            t2 = newTemp(Ity_I32);
            
            assign(t2, binop(Iop_Shl32, mkNarrowTo32(ty, getIReg(rt)),
                             mkU8(32 - lsb)));
            assign(t3, binop(Iop_Shr32, mkexpr(t2), mkU8(32 - lsb)));
         } else
            assign(t3, mkU32(0));

         if (msb < 31) {
            t4 = newTemp(Ity_I32);
            
            assign(t4, binop(Iop_Shr32, mkNarrowTo32(ty, getIReg(rt)),
                             mkU8(msb + 1)));
            t5 = newTemp(Ity_I32);
            assign(t5, binop(Iop_Shl32, mkexpr(t4), mkU8(msb + 1)));

            
            if (lsb > 0) {
               t6 = newTemp(Ity_I32);
               assign(t6, binop(Iop_Or32, mkexpr(t5), mkexpr(t1)));
               putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t6),
                                                   mkexpr(t3)), True));
            } else {
               putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t1),
                                                   mkexpr(t5)), True));
            }
         } else {
            putIReg(rt, mkWidenFrom32(ty, binop(Iop_Or32, mkexpr(t1),
                                                mkexpr(t3)), True));
         }
         break;

      case 0x00:  
         msb = get_msb(cins);
         lsb = get_lsb(cins);
         size = msb + 1;
         DIP("ext size:%d msb:%d lsb:%d", size, msb, lsb);
         vassert(lsb + size <= 32);
         vassert(lsb + size > 0);
         
         if (lsb + size < 32) {
            t0 = newTemp(Ity_I32);
            assign(t0, binop(Iop_Shl32, mkNarrowTo32(ty, getIReg(rs)),
                             mkU8(32 - lsb - size)));

            putIReg(rt, mkWidenFrom32(ty, binop(Iop_Shr32, mkexpr(t0),
                                                mkU8(32 - size)), True));
         } else {
            putIReg(rt, mkWidenFrom32(ty, binop(Iop_Shr32,
                                                mkNarrowTo32(ty, getIReg(rs)),
                                                mkU8(32 - size)), True));
         }
         break;

      case 0x03:  
         msb = get_msb(cins);
         lsb = get_lsb(cins);
         size = msb + 1;
         DIP("dext r%u, r%u, %d, %d", rt, rs, lsb, msb + 1);
         t1 = newTemp(Ity_I64);
         vassert(lsb >= 0 && lsb < 32);
         vassert(size > 0 && size <= 32);
         vassert((lsb + size) > 0 && (lsb + size) <= 63);

         UChar lsAmt = 63 - (lsb + msb);  
         UChar rsAmt = 63 - msb;  

         assign(t1, binop(Iop_Shl64, getIReg(rs), mkU8(lsAmt)));
         putIReg(rt, binop(Iop_Shr64, mkexpr(t1), mkU8(rsAmt)));

         break;

      case 0x20:  
         switch (sa) {
            case 0x02:  
               DIP("wsbh r%d, r%d", rd, rt);
               t0 = newTemp(Ity_I32);
               t1 = newTemp(Ity_I32);
               t2 = newTemp(Ity_I32);
               t3 = newTemp(Ity_I32);
               assign(t0, binop(Iop_Shl32, binop(Iop_And32, mkNarrowTo32(ty,
                                           getIReg(rt)), mkU32(0x00FF0000)),
                                           mkU8(0x8)));
               assign(t1, binop(Iop_Shr32, binop(Iop_And32, mkNarrowTo32(ty,
                                getIReg(rt)), mkU32(0xFF000000)), mkU8(0x8)));
               assign(t2, binop(Iop_Shl32, binop(Iop_And32, mkNarrowTo32(ty,
                                getIReg(rt)), mkU32(0x000000FF)), mkU8(0x8)));
               assign(t3, binop(Iop_Shr32, binop(Iop_And32, mkNarrowTo32(ty,
                                getIReg(rt)), mkU32(0x0000FF00)), mkU8(0x8)));
               putIReg(rd, mkWidenFrom32(ty, binop(Iop_Or32, binop(Iop_Or32,
                                         mkexpr(t0), mkexpr(t1)),
                                         binop(Iop_Or32, mkexpr(t2),
                                         mkexpr(t3))), True));
               break;

            case 0x10:  
               DIP("seb r%d, r%d", rd, rt);
               if (mode64)
                  putIReg(rd, unop(Iop_8Sto64, unop(Iop_64to8, getIReg(rt))));
               else
                  putIReg(rd, unop(Iop_8Sto32, unop(Iop_32to8, getIReg(rt))));
               break;

            case 0x18:  
               DIP("seh r%d, r%d", rd, rt);
               if (mode64)
                  putIReg(rd, unop(Iop_16Sto64, unop(Iop_64to16, getIReg(rt))));
               else
                  putIReg(rd, unop(Iop_16Sto32, unop(Iop_32to16, getIReg(rt))));
               break;

            default:
               goto decode_failure;

         }
         break;  

      
      case 0xA:  
         if (VEX_MIPS_COMP_ID(archinfo->hwcaps) == VEX_PRID_COMP_CAVIUM) {
            if (dis_instr_CVM(cins))
               break;
            goto decode_failure;
         }
      case 0xC:  
      case 0x38: {  
         if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure_dsp;
            }
            break;
         } else {
            goto decode_failure_dsp;
         }
         break;
      }
      case 0x10: {  
         switch(sa) {
            case  0xC:  
            case  0xD:  
            case 0x1E: {  
               if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
            default: {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
         }
         break;
      }
      case 0x11: {  
         switch(sa) {
            case 0x18:  
            case 0x19:  
            case 0x1A:  
            case 0x0D:  
            case 0x1E:  
            case 0x1F: {  
               if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
            default: {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
         }
         break;
      }
      case 0x12: {  
         switch(sa){
            case 0x1: {  
               if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
            default: {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
         }
         break;
      }
      case 0x13: {  
         switch(sa) {
            case 0x04:  
            case 0x05:  
            case 0x06:  
            case 0x07:  
            case 0x19:  
            case 0x1B: {  
               if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
            default: {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
         }
         break;
      }
      case 0x30: {  
         switch(sa) {
            case  0x0:  
            case 0x18:  
            case 0x1A:  
            case  0x8:  
            case  0x1:  
            case 0x19:  
            case 0x1B:  
            case  0x9:  
            case  0x2: {  
               if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
            default: {
               if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
                  UInt retVal = disDSPInstr_MIPS_WRK ( cins );
                  if (0 != retVal ) {
                     goto decode_failure_dsp;
                  }
                  break;
               } else {
                  goto decode_failure_dsp;
               }
               break;
            }
         }
         break;
      }
      case 0x18:  
      case 0x31: {  
         if (VEX_MIPS_PROC_DSP2(archinfo->hwcaps)) {
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure_dsp;
            }
            break;
         } else {
            goto decode_failure_dsp;
         }
      }
      default:
         goto decode_failure;

   }
      break;  

   case 0x3B:
      if (0x3B == function &&
          (VEX_MIPS_COMP_ID(archinfo->hwcaps) == VEX_PRID_COMP_BROADCOM)) {
         
         DIP("rdhwr r%d, r%d", rt, rd);
         if (rd == 29) {
            putIReg(rt, getULR());
         } else
            goto decode_failure;
         break;
      } else {
         goto decode_failure;
      }

   case 0x00:  

      switch (function) {
      case 0x1: {
         UInt mov_cc = get_mov_cc(cins);
         if (tf == 0) {  
            DIP("movf r%d, r%d, %d", rd, rs, mov_cc);
            t1 = newTemp(Ity_I1);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I1);

            assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
            assign(t2, IRExpr_ITE(mkexpr(t1),
                                  binop(Iop_And32,
                                        binop(Iop_Shr32, getFCSR(),
                                              mkU8(23)),
                                        mkU32(0x1)),
                                  binop(Iop_And32,
                                        binop(Iop_Shr32, getFCSR(),
                                              mkU8(24 + mov_cc)),
                                        mkU32(0x1))
                                  ));
            assign(t3, binop(Iop_CmpEQ32, mkU32(0), mkexpr(t2)));
            putIReg(rd, IRExpr_ITE(mkexpr(t3), getIReg(rs), getIReg(rd)));
         } else if (tf == 1) {  
            DIP("movt r%d, r%d, %d", rd, rs, mov_cc);
            t1 = newTemp(Ity_I1);
            t2 = newTemp(Ity_I32);
            t3 = newTemp(Ity_I1);

            assign(t1, binop(Iop_CmpEQ32, mkU32(0), mkU32(mov_cc)));
            assign(t2, IRExpr_ITE(mkexpr(t1),
                                  binop(Iop_And32,
                                        binop(Iop_Shr32, getFCSR(),
                                              mkU8(23)),
                                        mkU32(0x1)),
                                  binop(Iop_And32,
                                        binop(Iop_Shr32, getFCSR(),
                                              mkU8(24 + mov_cc)),
                                        mkU32(0x1))
                                  ));
            assign(t3, binop(Iop_CmpEQ32, mkU32(1), mkexpr(t2)));
            putIReg(rd, IRExpr_ITE(mkexpr(t3), getIReg(rs), getIReg(rd)));
         }
         break;
      }
      case 0x0A: {  
         DIP("movz r%d, r%d, r%d", rd, rs, rt);
         t1 = newTemp(ty);
         t2 = newTemp(ty);
         if (mode64) {
            assign(t1, unop(Iop_32Sto64, unop(Iop_1Sto32, binop(Iop_CmpEQ64,
                            getIReg(rt), mkU64(0x0)))));
            assign(t2, unop(Iop_32Sto64, unop(Iop_1Sto32, binop(Iop_CmpNE64,
                            getIReg(rt), mkU64(0x0)))));
            putIReg(rd, binop(Iop_Add64, binop(Iop_And64, getIReg(rs),
                        mkexpr(t1)), binop(Iop_And64, getIReg(rd),mkexpr(t2))));
         } else {
            assign(t1, unop(Iop_1Sto32, binop(Iop_CmpEQ32, getIReg(rt),
                                              mkU32(0x0))));
            assign(t2, unop(Iop_1Sto32, binop(Iop_CmpNE32, getIReg(rt),
                                              mkU32(0x0))));
            putIReg(rd, binop(Iop_Add32, binop(Iop_And32, getIReg(rs),
                        mkexpr(t1)), binop(Iop_And32, getIReg(rd),
                        mkexpr(t2))));
         }
         break;
      }

      case 0x0B: {  
         DIP("movn r%d, r%d, r%d", rd, rs, rt);
         t1 = newTemp(ty);
         t2 = newTemp(ty);
         if (mode64) {
            assign(t1, unop(Iop_32Sto64, unop(Iop_1Sto32, binop(Iop_CmpEQ64,
                            getIReg(rt), mkU64(0x0)))));
            assign(t2, unop(Iop_32Sto64, unop(Iop_1Sto32, binop(Iop_CmpNE64,
                            getIReg(rt), mkU64(0x0)))));
            putIReg(rd, binop(Iop_Add64, binop(Iop_And64, getIReg(rs),
                        mkexpr(t2)), binop(Iop_And64, getIReg(rd),
                                           mkexpr(t1))));
         } else {
            assign(t1, unop(Iop_1Sto32, binop(Iop_CmpEQ32, getIReg(rt),
                                              mkU32(0x0))));
            assign(t2, unop(Iop_1Sto32, binop(Iop_CmpNE32, getIReg(rt),
                                              mkU32(0x0))));
            putIReg(rd, binop(Iop_Add32, binop(Iop_And32, getIReg(rs),
                        mkexpr(t2)), binop(Iop_And32, getIReg(rd),
                        mkexpr(t1))));
         }
         break;
      }

      case 0x18:  {  
         if ( (1 <= ac) && ( 3 >= ac) ) {
            if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
               
               UInt retVal = disDSPInstr_MIPS_WRK ( cins );
               if (0 != retVal ) {
                  goto decode_failure_dsp;
               }
               break;
            } else {
               goto decode_failure_dsp;
            }
         } else {
            DIP("mult r%d, r%d", rs, rt);
            t2 = newTemp(Ity_I64);

            assign(t2, binop(Iop_MullS32, mkNarrowTo32(ty, getIReg(rs)),
                                          mkNarrowTo32(ty, getIReg(rt))));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t2)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t2)), True));
            break;
         }
      }
      case 0x19:  {  
         if ( (1 <= ac) && ( 3 >= ac) ) {
            if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
               
               UInt retVal = disDSPInstr_MIPS_WRK ( cins );
               if (0 != retVal ) {
                  goto decode_failure_dsp;
               }
               break;
            } else {
               goto decode_failure_dsp;
            }
         } else {
            DIP("multu r%d, r%d", rs, rt);
            t2 = newTemp(Ity_I64);

            assign(t2, binop(Iop_MullU32, mkNarrowTo32(ty, getIReg(rs)),
                                          mkNarrowTo32(ty, getIReg(rt))));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t2)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t2)), True));
            break;
         }
      }
      case 0x20: {  
         DIP("add r%d, r%d, r%d", rd, rs, rt);
         IRTemp tmpRs32 = newTemp(Ity_I32);
         IRTemp tmpRt32 = newTemp(Ity_I32);

         assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));
         assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));

         t0 = newTemp(Ity_I32);
         t1 = newTemp(Ity_I32);
         t2 = newTemp(Ity_I32);
         t3 = newTemp(Ity_I32);
         t4 = newTemp(Ity_I32);

         assign(t0, binop(Iop_Add32, mkexpr(tmpRs32), mkexpr(tmpRt32)));
         assign(t1, binop(Iop_Xor32, mkexpr(tmpRs32), mkexpr(tmpRt32)));
         assign(t2, unop(Iop_1Uto32,
                         binop(Iop_CmpEQ32,
                               binop(Iop_And32, mkexpr(t1), mkU32(0x80000000)),
                               mkU32(0x80000000))));

         assign(t3, binop(Iop_Xor32, mkexpr(t0), mkexpr(tmpRs32)));
         assign(t4, unop(Iop_1Uto32,
                         binop(Iop_CmpNE32,
                               binop(Iop_And32, mkexpr(t3), mkU32(0x80000000)),
                               mkU32(0x80000000))));

         stmt(IRStmt_Exit(binop(Iop_CmpEQ32,
                                binop(Iop_Or32, mkexpr(t2), mkexpr(t4)),
                                mkU32(0)),
                          Ijk_SigFPE_IntOvf,
                          mode64 ? IRConst_U64(guest_PC_curr_instr + 4) :
                                   IRConst_U32(guest_PC_curr_instr + 4),
                          OFFB_PC));

         putIReg(rd,  mkWidenFrom32(ty, mkexpr(t0), True));
         break;
      }
      case 0x1A:  
         DIP("div r%d, r%d", rs, rt);
         if (mode64) {
            t2 = newTemp(Ity_I64);

            assign(t2, binop(Iop_DivModS64to32,
                             getIReg(rs), mkNarrowTo32(ty, getIReg(rt))));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t2)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t2)), True));
         } else {
            t1 = newTemp(Ity_I64);
            t2 = newTemp(Ity_I64);

            assign(t1, unop(Iop_32Sto64, getIReg(rs)));
            assign(t2, binop(Iop_DivModS64to32, mkexpr(t1), getIReg(rt)));

            putHI(unop(Iop_64HIto32, mkexpr(t2)));
            putLO(unop(Iop_64to32, mkexpr(t2)));
         }
         break;

      case 0x1B:  
         DIP("divu r%d, r%d", rs, rt);
         if (mode64) {
            t2 = newTemp(Ity_I64);

            assign(t2, binop(Iop_DivModU64to32,
                             getIReg(rs), mkNarrowTo32(ty, getIReg(rt))));

            putHI(mkWidenFrom32(ty, unop(Iop_64HIto32, mkexpr(t2)), True));
            putLO(mkWidenFrom32(ty, unop(Iop_64to32, mkexpr(t2)), True));
         } else {
            t1 = newTemp(Ity_I64);
            t2 = newTemp(Ity_I64);
            assign(t1, unop(Iop_32Uto64, getIReg(rs)));
            assign(t2, binop(Iop_DivModU64to32, mkexpr(t1), getIReg(rt)));
            putHI(unop(Iop_64HIto32, mkexpr(t2)));
            putLO(unop(Iop_64to32, mkexpr(t2)));
         }
         break;

      case 0x1C:  
         DIP("dmult r%u, r%u", rs, rt);
         t0 = newTemp(Ity_I128);

         assign(t0, binop(Iop_MullS64, getIReg(rs), getIReg(rt)));

         putHI(unop(Iop_128HIto64, mkexpr(t0)));
         putLO(unop(Iop_128to64, mkexpr(t0)));
         break;

      case 0x1D:  
         DIP("dmultu r%u, r%u", rs, rt);
         t0 = newTemp(Ity_I128);

         assign(t0, binop(Iop_MullU64, getIReg(rs), getIReg(rt)));

         putHI(unop(Iop_128HIto64, mkexpr(t0)));
         putLO(unop(Iop_128to64, mkexpr(t0)));
         break;

      case 0x1E:  
         DIP("ddiv r%u, r%u", rs, rt);
         t1 = newTemp(Ity_I128);

         assign(t1, binop(Iop_DivModS64to64, getIReg(rs), getIReg(rt)));

         putHI(unop(Iop_128HIto64, mkexpr(t1)));
         putLO(unop(Iop_128to64, mkexpr(t1)));
         break;

      case 0x1F:  
         DIP("ddivu r%u, r%u", rs, rt);
         t1 = newTemp(Ity_I128);
         t2 = newTemp(Ity_I128);

         assign(t1, binop(Iop_64HLto128, mkU64(0), getIReg(rs)));

         assign(t2, binop(Iop_DivModU128to64, mkexpr(t1), getIReg(rt)));

         putHI(unop(Iop_128HIto64, mkexpr(t2)));
         putLO(unop(Iop_128to64, mkexpr(t2)));
         break;

      case 0x10: {  
         if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
            
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure;
            }
            break;
         } else {
            DIP("mfhi r%d", rd);
            putIReg(rd, getHI());
            break;
         }
      }

      case 0x11:  {  
         if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
            
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure;
            }
            break;
         } else {
            DIP("mthi r%d", rs);
            putHI(getIReg(rs));
            break;
         }
      }

      case 0x12:  {  
         if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
            
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure;
            }
            break;
         } else {
            DIP("mflo r%d", rd);
            putIReg(rd, getLO());
            break;
         }
      }

      case 0x13:  {  
         if (VEX_MIPS_PROC_DSP(archinfo->hwcaps)) {
            
            UInt retVal = disDSPInstr_MIPS_WRK ( cins );
            if (0 != retVal ) {
               goto decode_failure;
            }
            break;
         } else {
            DIP("mtlo r%d", rs);
            putLO(getIReg(rs));
            break;
         }
      }

      case 0x21:  
         DIP("addu r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            ALU_PATTERN64(Iop_Add32);
         } else {
            ALU_PATTERN(Iop_Add32);
         }
         break;

      case 0x22: {  
         DIP("sub r%d, r%d, r%d", rd, rs, rt);
         IRTemp tmpRs32 = newTemp(Ity_I32);
         IRTemp tmpRt32 = newTemp(Ity_I32);

         assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));
         assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
         t0 = newTemp(Ity_I32);
         t1 = newTemp(Ity_I32);
         t2 = newTemp(Ity_I32);
         t3 = newTemp(Ity_I32);
         t4 = newTemp(Ity_I32);
         t5 = newTemp(Ity_I32);

         assign(t5, binop(Iop_Mul32, mkexpr(tmpRt32), mkU32(-1)));
         assign(t0, binop(Iop_Add32, mkexpr(tmpRs32), mkexpr(t5)));
         assign(t1, binop(Iop_Xor32, mkexpr(tmpRs32), mkexpr(t5)));
         assign(t2, unop(Iop_1Sto32, binop(Iop_CmpEQ32, binop(Iop_And32,
                         mkexpr(t1), mkU32(0x80000000)), mkU32(0x80000000))));

         assign(t3, binop(Iop_Xor32, mkexpr(t0), mkexpr(tmpRs32)));
         assign(t4, unop(Iop_1Sto32, binop(Iop_CmpNE32, binop(Iop_And32,
                         mkexpr(t3), mkU32(0x80000000)), mkU32(0x80000000))));

         stmt(IRStmt_Exit(binop(Iop_CmpEQ32, binop(Iop_Or32, mkexpr(t2),
                                mkexpr(t4)), mkU32(0)), Ijk_SigFPE_IntOvf,
                          mode64 ? IRConst_U64(guest_PC_curr_instr + 4) :
                                   IRConst_U32(guest_PC_curr_instr + 4),
                          OFFB_PC));

         putIReg(rd, mkWidenFrom32(ty, mkexpr(t0), True));
         break;
      }
      case 0x23:  
         DIP("subu r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            ALU_PATTERN64(Iop_Sub32);
         } else {
            ALU_PATTERN(Iop_Sub32);
         }
         break;

      case 0x24:  
         DIP("and r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            ALU_PATTERN(Iop_And64);
         } else {
            ALU_PATTERN(Iop_And32);
         }
         break;

      case 0x25:  
         DIP("or r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            ALU_PATTERN(Iop_Or64);
         } else {
            ALU_PATTERN(Iop_Or32);
         }
         break;

      case 0x26:  
         DIP("xor r%d, r%d, r%d", rd, rs, rt);
         if (mode64) {
            ALU_PATTERN(Iop_Xor64);
         } else {
            ALU_PATTERN(Iop_Xor32);
         }
         break;

      case 0x27:  
         DIP("nor r%d, r%d, r%d", rd, rs, rt);
         if (mode64)
            putIReg(rd, unop(Iop_Not64, binop(Iop_Or64, getIReg(rs),
                                              getIReg(rt))));
         else
            putIReg(rd, unop(Iop_Not32, binop(Iop_Or32, getIReg(rs),
                                              getIReg(rt))));
         break;

      case 0x08:  
         DIP("jr r%d", rs);
         t0 = newTemp(ty);
         assign(t0, getIReg(rs));
         lastn = mkexpr(t0);
         break;

      case 0x09:  
         DIP("jalr r%d r%d", rd, rs);
         if (mode64) {
            putIReg(rd, mkU64(guest_PC_curr_instr + 8));
            t0 = newTemp(Ity_I64);
            assign(t0, getIReg(rs));
            lastn = mkexpr(t0);
         } else {
            putIReg(rd, mkU32(guest_PC_curr_instr + 8));
            t0 = newTemp(Ity_I32);
            assign(t0, getIReg(rs));
            lastn = mkexpr(t0);
         }
         break;

      case 0x0C:  
         DIP("syscall");
         if (mode64)
            putPC(mkU64(guest_PC_curr_instr + 4));
         else
            putPC(mkU32(guest_PC_curr_instr + 4));
         dres.jk_StopHere = Ijk_Sys_syscall;
         dres.whatNext    = Dis_StopHere;
         break;

      case 0x2A:  
         DIP("slt r%d, r%d, r%d", rd, rs, rt);
         if (mode64)
            putIReg(rd, unop(Iop_1Uto64, binop(Iop_CmpLT64S, getIReg(rs),
                                               getIReg(rt))));
         else
            putIReg(rd, unop(Iop_1Uto32, binop(Iop_CmpLT32S, getIReg(rs),
                                               getIReg(rt))));
         break;

      case 0x2B:  
         DIP("sltu r%d, r%d, r%d", rd, rs, rt);
         if (mode64)
            putIReg(rd, unop(Iop_1Uto64, binop(Iop_CmpLT64U, getIReg(rs),
                                         getIReg(rt))));
         else
            putIReg(rd, unop(Iop_1Uto32, binop(Iop_CmpLT32U, getIReg(rs),
                                         getIReg(rt))));
         break;

      case 0x00: {  
         DIP("sll r%d, r%d, %d", rd, rt, sa);
         IRTemp tmpRt32 = newTemp(Ity_I32);
         IRTemp tmpSh32 = newTemp(Ity_I32);
         IRTemp tmpRd = newTemp(Ity_I64);
         if (mode64) {
            assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
            assign(tmpSh32, binop(Iop_Shl32, mkexpr(tmpRt32), mkU8(sa)));
            assign(tmpRd, mkWidenFrom32(ty, mkexpr(tmpSh32), True));
            putIReg(rd, mkexpr(tmpRd));
         } else
            SXX_PATTERN(Iop_Shl32);
         break;
      }

      case 0x04: {  
         DIP("sllv r%d, r%d, r%d", rd, rt, rs);
         if (mode64) {
            IRTemp tmpRs8 = newTemp(Ity_I8);
            IRTemp tmpRt32 = newTemp(Ity_I32);
            IRTemp tmpSh32 = newTemp(Ity_I32);
            IRTemp tmp = newTemp(ty);
            assign(tmp, binop(mkSzOp(ty, Iop_And8), getIReg(rs),
                              mkSzImm(ty, 31)));
            assign(tmpRs8, mkNarrowTo8(ty, mkexpr(tmp)));
            assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
            assign(tmpSh32, binop(Iop_Shl32, mkexpr(tmpRt32), mkexpr(tmpRs8)));
            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpSh32), True));
         } else {
            SXXV_PATTERN(Iop_Shl32);
         }
         break;
      }

      case 0x03:  
         DIP("sra r%d, r%d, %d", rd, rt, sa);
         if (mode64) {
            IRTemp tmpRt32 = newTemp(Ity_I32);
            IRTemp tmpSh32 = newTemp(Ity_I32);

            t1 = newTemp(Ity_I64);
            t2 = newTemp(Ity_I64);
            t3 = newTemp(Ity_I64);

            assign(t1, binop(Iop_And64, getIReg(rt),  
                             mkU64(0xFFFFFFFF00000000ULL)));

            assign(t2, binop(Iop_Sar64, mkexpr(t1), mkU8(sa)));

            assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
            assign(tmpSh32, binop(Iop_Sar32, mkexpr(tmpRt32), mkU8(sa)));

            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpSh32), True));
         } else {
            SXX_PATTERN(Iop_Sar32);
         }
         break;

      case 0x07:  
         DIP("srav r%d, r%d, r%d", rd, rt, rs);
         if (mode64) {
            IRTemp tmpRt32 = newTemp(Ity_I32);
            IRTemp tmpSh32 = newTemp(Ity_I32);

            t1 = newTemp(Ity_I64);
            t2 = newTemp(Ity_I64);
            t3 = newTemp(Ity_I64);
            t4 = newTemp(Ity_I8);

            assign(t4, unop(Iop_32to8, binop(Iop_And32,
                       mkNarrowTo32(ty, getIReg(rs)), mkU32(0x0000001F))));

            assign(t1, binop(Iop_And64, getIReg(rt),  
                   mkU64(0xFFFFFFFF00000000ULL)));

            assign(t2, binop(Iop_Sar64, mkexpr(t1), mkexpr(t4)));

            assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
            assign(tmpSh32, binop(Iop_Sar32, mkexpr(tmpRt32), mkexpr(t4)));

            putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpSh32), True));
         } else {
            SXXV_PATTERN(Iop_Sar32);
         }
         break;

      case 0x02: {  
         rot = get_rot(cins);
         if (rot) {
            DIP("rotr r%d, r%d, %d", rd, rt, sa);
            putIReg(rd, mkWidenFrom32(ty, genROR32(mkNarrowTo32(ty,
                        getIReg(rt)), sa), True));
         } else {
            DIP("srl r%d, r%d, %d", rd, rt, sa);
            if (mode64) {
               IRTemp tmpSh32 = newTemp(Ity_I32);
               IRTemp tmpRt32 = newTemp(Ity_I32);

               assign(tmpRt32, mkNarrowTo32(ty, getIReg(rt)));
               assign(tmpSh32, binop(Iop_Shr32, mkexpr(tmpRt32), mkU8(sa)));
               putIReg(rd, mkWidenFrom32(ty, mkexpr(tmpSh32), True));
            } else {
               SXX_PATTERN(Iop_Shr32);
            }
         }
      break;
      }

      case 0x06: {
         rot = get_rotv(cins);
         if (rot) {
            DIP("rotrv r%d, r%d, r%d", rd, rt, rs);
            putIReg(rd, mkWidenFrom32(ty, genRORV32(mkNarrowTo32(ty,
                        getIReg(rt)), mkNarrowTo32(ty, getIReg(rs))), True));
            break;
         } else {  
            DIP("srlv r%d, r%d, r%d", rd, rt, rs);
            if (mode64) {
               SXXV_PATTERN64(Iop_Shr32);
            } else {
               SXXV_PATTERN(Iop_Shr32);
            }
            break;
         }
      }

      case 0x0D:  
         DIP("break 0x%x", trap_code);
         if (mode64)
            jmp_lit64(&dres, Ijk_SigTRAP, (guest_PC_curr_instr + 4));
         else
            jmp_lit32(&dres, Ijk_SigTRAP, (guest_PC_curr_instr + 4));
         vassert(dres.whatNext == Dis_StopHere);
         break;

      case 0x30: {  
         DIP("tge r%d, r%d %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                Ijk_SigFPE_IntDiv,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                Ijk_SigFPE_IntOvf,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                Ijk_SigTRAP,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntDiv,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else if (trap_code == 6)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntOvf,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32S,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigTRAP,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
         }
         break;
      }
      case 0x31: {  
         DIP("tgeu r%d, r%d %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntDiv,
                                  IRConst_U64(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else if (trap_code == 6)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntOvf,
                                  IRConst_U64(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT64U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigTRAP,
                                  IRConst_U64(guest_PC_curr_instr + 4),
                                  OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntDiv,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else if (trap_code == 6)
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigFPE_IntOvf,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
            else
               stmt (IRStmt_Exit (unop (Iop_Not1,
                                        binop (Iop_CmpLT32U,
                                               getIReg (rs),
                                               getIReg (rt))),
                                  Ijk_SigTRAP,
                                  IRConst_U32(guest_PC_curr_instr + 4),
                                  OFFB_PC));
         }
         break;
      }
      case 0x32: {  
         DIP("tlt r%d, r%d %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpLT64S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpLT64S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpLT64S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpLT32S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpLT32S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpLT32S, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
         }
         break;
      }
      case 0x33: {  
         DIP("tltu r%d, r%d %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpLT64U, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpLT64U, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpLT64U, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpLT32U, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpLT32U, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpLT32U, getIReg(rs),
                                      getIReg (rt)), Ijk_SigTRAP,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
         }
         break;
      }
      case 0x34: {  
         DIP("teq r%d, r%d, %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpEQ64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpEQ64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpEQ64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpEQ32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpEQ32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpEQ32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
         }
         break;
      }
      case 0x36: {  
         DIP("tne r%d, r%d %d", rs, rt, trap_code);
         if (mode64) {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpNE64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpNE64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpNE64, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U64(guest_PC_curr_instr + 4),
                                OFFB_PC));
         } else {
            if (trap_code == 7)
               stmt(IRStmt_Exit(binop(Iop_CmpNE32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntDiv,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else if (trap_code == 6)
               stmt(IRStmt_Exit(binop(Iop_CmpNE32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigFPE_IntOvf,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
            else
               stmt(IRStmt_Exit(binop(Iop_CmpNE32, getIReg(rs),
                                      getIReg(rt)), Ijk_SigTRAP,
                                IRConst_U32(guest_PC_curr_instr + 4),
                                OFFB_PC));
         }
         break;
      }
      case 0x14:
      case 0x16:
      case 0x17:  
      case 0x38:
      case 0x3A:
      case 0x3B:  
      case 0x3C:
      case 0x3E:
      case 0x3F:  
         if (dis_instr_shrt(cins))
            break;
         goto decode_failure;

      case 0x0F:  
         DIP("sync 0x%x", sel);
         
         break;

      case 0x2C: {  
         DIP("dadd r%d, r%d, r%d", rd, rs, rt);
         IRTemp tmpRs64 = newTemp(Ity_I64);
         IRTemp tmpRt64 = newTemp(Ity_I64);

         assign(tmpRs64, getIReg(rs));
         assign(tmpRt64, getIReg(rt));

         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);
         t2 = newTemp(Ity_I64);
         t3 = newTemp(Ity_I64);
         t4 = newTemp(Ity_I64);

         assign(t0, binop(Iop_Add64, mkexpr(tmpRs64), mkexpr(tmpRt64)));
         assign(t1, binop(Iop_Xor64, mkexpr(tmpRs64), mkexpr(tmpRt64)));
         assign(t2, unop(Iop_1Uto64,
                         binop(Iop_CmpEQ64,
                               binop(Iop_And64, mkexpr(t1),
                                     mkU64(0x8000000000000000ULL)),
                               mkU64(0x8000000000000000ULL))));

         assign(t3, binop(Iop_Xor64, mkexpr(t0), mkexpr(tmpRs64)));
         assign(t4, unop(Iop_1Uto64,
                         binop(Iop_CmpNE64,
                               binop(Iop_And64, mkexpr(t3),
                                     mkU64(0x8000000000000000ULL)),
                               mkU64(0x8000000000000000ULL))));

         stmt(IRStmt_Exit(binop(Iop_CmpEQ64,
                                binop(Iop_Or64, mkexpr(t2), mkexpr(t4)),
                                mkU64(0)),
                          Ijk_SigFPE_IntOvf,
                          IRConst_U64(guest_PC_curr_instr + 4),
                          OFFB_PC));

         putIReg(rd,  mkexpr(t0));
         break;
      }

      case 0x2D:  
         DIP("daddu r%d, r%d, r%d", rd, rs, rt);
         ALU_PATTERN(Iop_Add64);
         break;

      case 0x2E: {  
         DIP("dsub r%u, r%u, r%u", rd, rs, rt);
         IRTemp tmpRs64 = newTemp(Ity_I64);
         IRTemp tmpRt64 = newTemp(Ity_I64);

         assign(tmpRs64, getIReg(rs));
         assign(tmpRt64, getIReg(rt));
         t0 = newTemp(Ity_I64);
         t1 = newTemp(Ity_I64);
         t2 = newTemp(Ity_I64);
         t3 = newTemp(Ity_I64);
         t4 = newTemp(Ity_I64);
         t5 = newTemp(Ity_I64);

         assign(t5, binop(Iop_Mul64,
                          mkexpr(tmpRt64),
                          mkU64(0xffffffffffffffffULL)));
         assign(t0, binop(Iop_Add64, mkexpr(tmpRs64), mkexpr(t5)));
         assign(t1, binop(Iop_Xor64, mkexpr(tmpRs64), mkexpr(t5)));
         assign(t2, unop(Iop_1Sto64,
                         binop(Iop_CmpEQ64,
                               binop(Iop_And64,
                                     mkexpr(t1),
                                     mkU64(0x8000000000000000ULL)),
                               mkU64(0x8000000000000000ULL))));

         assign(t3, binop(Iop_Xor64, mkexpr(t0), mkexpr(tmpRs64)));
         assign(t4, unop(Iop_1Sto64,
                         binop(Iop_CmpNE64,
                               binop(Iop_And64,
                                     mkexpr(t3),
                                     mkU64(0x8000000000000000ULL)),
                               mkU64(0x8000000000000000ULL))));

         stmt(IRStmt_Exit(binop(Iop_CmpEQ64, binop(Iop_Or64, mkexpr(t2),
                                mkexpr(t4)), mkU64(0)), Ijk_SigFPE_IntOvf,
                          IRConst_U64(guest_PC_curr_instr + 4),
                          OFFB_PC));

         putIReg(rd, binop(Iop_Sub64, getIReg(rs), getIReg(rt)));
         break;
      }

      case 0x2F:  
         DIP("dsub r%u, r%u,r%u", rd, rt, rt);
         ALU_PATTERN(Iop_Sub64);
         break;

      default:
         goto decode_failure;
      }
      break;

   case 0x01:  

      switch (rt) {
      case 0x00:  
         DIP("bltz r%d, %d", rs, imm);
         if (mode64) {
            if (!dis_instr_branch(cins, &dres, resteerOkFn,
                        callback_opaque, &bstmt))
               goto decode_failure;
         } else
            dis_branch(False, binop(Iop_CmpEQ32, binop(Iop_And32, getIReg(rs),
                       mkU32(0x80000000)), mkU32(0x80000000)), imm, &bstmt);
         break;

      case 0x01:  
         DIP("bgez r%d, %d", rs, imm);
         if (mode64) {
            if (!dis_instr_branch(cins, &dres, resteerOkFn,
                                  callback_opaque, &bstmt))
               goto decode_failure;
         } else
            dis_branch(False, binop(Iop_CmpEQ32, binop(Iop_And32, getIReg(rs),
                              mkU32(0x80000000)), mkU32(0x0)), imm, &bstmt);
         break;

      case 0x02:  
         DIP("bltzl r%d, %d", rs, imm);
         lastn = dis_branch_likely(binop(mode64 ? Iop_CmpNE64 : Iop_CmpNE32,
                     binop(mode64 ? Iop_And64 : Iop_And32, getIReg(rs),
                     mode64 ? mkU64(0x8000000000000000ULL) : mkU32(0x80000000)),
                     mode64 ? mkU64(0x8000000000000000ULL) : mkU32(0x80000000)),
                     imm);
         break;

      case 0x03:  
         DIP("bgezl r%d, %d", rs, imm);
         lastn = dis_branch_likely(binop(mode64 ? Iop_CmpNE64 : Iop_CmpNE32,
                     binop(mode64 ? Iop_And64 : Iop_And32, getIReg(rs),
                     mode64 ? mkU64(0x8000000000000000ULL) : mkU32(0x80000000)),
                     mode64 ? mkU64(0x0) : mkU32(0x0)), imm);
         break;

      case 0x10:  
         DIP("bltzal r%d, %d", rs, imm);
         if (mode64) {
            if (!dis_instr_branch(cins, &dres, resteerOkFn,
                        callback_opaque, &bstmt))
               goto decode_failure;
         } else
            dis_branch(True, binop(Iop_CmpEQ32, binop(Iop_And32, getIReg(rs),
                       mkU32(0x80000000)), mkU32(0x80000000)), imm, &bstmt);
         break;

      case 0x12:  
         DIP("bltzall r%d, %d", rs, imm);
         putIReg(31, mode64 ? mkU64(guest_PC_curr_instr + 8) :
                              mkU32(guest_PC_curr_instr + 8));
         lastn = dis_branch_likely(binop(mode64 ? Iop_CmpNE64 : Iop_CmpNE32,
                     binop(mode64 ? Iop_And64 : Iop_And32, getIReg(rs),
                     mode64 ? mkU64(0x8000000000000000ULL) : mkU32(0x80000000)),
                     mode64 ? mkU64(0x8000000000000000ULL) : mkU32(0x80000000)),
                     imm);
         break;

      case 0x11:  
         DIP("bgezal r%d, %d", rs, imm);
         if (mode64) {
            if (!dis_instr_branch(cins, &dres, resteerOkFn,
                        callback_opaque, &bstmt))
               goto decode_failure;
         } else
            dis_branch(True, binop(Iop_CmpEQ32, binop(Iop_And32, getIReg(rs),
                       mkU32(0x80000000)), mkU32(0x0)), imm, &bstmt);
         break;

      case 0x13:  
         DIP("bgezall r%d, %d", rs, imm);
         if (mode64) {
            putIReg(31, mkU64(guest_PC_curr_instr + 8));
            lastn = dis_branch_likely(binop(Iop_CmpNE64,
                                            binop(Iop_And64,
                                                  getIReg(rs),
                                                  mkU64(0x8000000000000000ULL)),
                                            mkU64(0x0)),
                                      imm);
         } else {
            putIReg(31, mkU32(guest_PC_curr_instr + 8));
            lastn = dis_branch_likely(binop(Iop_CmpNE32, binop(Iop_And32,
                                      getIReg(rs), mkU32(0x80000000)),
                                      mkU32(0x0)), imm);
         }
         break;

      case 0x08:  
         DIP("tgei r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (unop (Iop_Not1,
                                     binop (Iop_CmpLT64S,
                                            getIReg (rs),
                                            mkU64 (extend_s_16to64 (imm)))),
                             Ijk_SigTRAP,
                             IRConst_U64(guest_PC_curr_instr + 4),
                             OFFB_PC));
         } else {
            stmt (IRStmt_Exit (unop (Iop_Not1,
                                     binop (Iop_CmpLT32S,
                                     getIReg (rs),
                                     mkU32 (extend_s_16to32 (imm)))),
                             Ijk_SigTRAP,
                             IRConst_U32(guest_PC_curr_instr + 4),
                             OFFB_PC));
         }
         break;

      case 0x09: {  
         DIP("tgeiu r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (unop (Iop_Not1,
                                     binop (Iop_CmpLT64U,
                                            getIReg (rs),
                                            mkU64 (extend_s_16to64 (imm)))),
                             Ijk_SigTRAP,
                             IRConst_U64(guest_PC_curr_instr + 4),
                             OFFB_PC));
         } else {
            stmt (IRStmt_Exit (unop (Iop_Not1,
                                     binop (Iop_CmpLT32U,
                                            getIReg (rs),
                                            mkU32 (extend_s_16to32 (imm)))),
                               Ijk_SigTRAP,
                               IRConst_U32(guest_PC_curr_instr + 4),
                               OFFB_PC));
         }
         break;
      }
      case 0x0A: {  
         DIP("tlti r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (binop (Iop_CmpLT64S, getIReg (rs),
                                      mkU64 (extend_s_16to64 (imm))),
                             Ijk_SigTRAP,
                             IRConst_U64(guest_PC_curr_instr + 4),
                             OFFB_PC));
         } else {
            stmt (IRStmt_Exit (binop (Iop_CmpLT32S, getIReg (rs),
                                      mkU32 (extend_s_16to32 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U32(guest_PC_curr_instr + 4),
                               OFFB_PC));
         }
         break;
      }
      case 0x0B: {  
         DIP("tltiu r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (binop (Iop_CmpLT64U, getIReg (rs),
                                      mkU64 (extend_s_16to64 (imm))),
                             Ijk_SigTRAP,
                             IRConst_U64(guest_PC_curr_instr + 4),
                             OFFB_PC));
         } else {
            stmt (IRStmt_Exit (binop (Iop_CmpLT32U, getIReg (rs),
                                      mkU32 (extend_s_16to32 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U32(guest_PC_curr_instr + 4),
                               OFFB_PC));
         }
         break;
      }
      case 0x0C: {  
          DIP("teqi r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (binop (Iop_CmpEQ64, getIReg (rs),
                                      mkU64 (extend_s_16to64 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U64(guest_PC_curr_instr + 4),
                               OFFB_PC));
         } else {
            stmt (IRStmt_Exit (binop (Iop_CmpEQ32, getIReg (rs),
                                      mkU32 (extend_s_16to32 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U32(guest_PC_curr_instr + 4),
                               OFFB_PC));
         }
         break;
      }
      case 0x0E: {  
         DIP("tnei r%d, %d %d", rs, imm, trap_code);
         if (mode64) {
            stmt (IRStmt_Exit (binop (Iop_CmpNE64, getIReg (rs),
                                      mkU64 (extend_s_16to64 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U64(guest_PC_curr_instr + 4),
                               OFFB_PC));
         } else {
            stmt (IRStmt_Exit (binop (Iop_CmpNE32, getIReg (rs),
                                      mkU32 (extend_s_16to32 (imm))),
                               Ijk_SigTRAP,
                               IRConst_U32(guest_PC_curr_instr + 4),
                               OFFB_PC));
         }
         break;
      }
      case 0x1C: {  
         DIP("bposge32 %d", imm);
         vassert(!mode64);
         t0 = newTemp(Ity_I32);
         
         assign(t0, binop(Iop_And32, getDSPControl(), mkU32(0x3f)));
         dis_branch(False, unop(Iop_Not1, binop(Iop_CmpLT32U, mkexpr(t0),
                                mkU32(32))), imm, &bstmt);
      }
      case 0x1F:
         
         
         break;

      default:
         goto decode_failure;
      }
      break;

   case 0x04:
      DIP("beq r%d, r%d, %d", rs, rt, imm);
      if (mode64)
         dis_branch(False, binop(Iop_CmpEQ64, getIReg(rs), getIReg(rt)),
                                 imm, &bstmt);
      else
         dis_branch(False, binop(Iop_CmpEQ32, getIReg(rs), getIReg(rt)),
                                 imm, &bstmt);
      break;

   case 0x14:
      DIP("beql r%d, r%d, %d", rs, rt, imm);
      lastn = dis_branch_likely(binop(mode64 ? Iop_CmpNE64 : Iop_CmpNE32,
                                getIReg(rs), getIReg(rt)), imm);
      break;

   case 0x05:
      DIP("bne r%d, r%d, %d", rs, rt, imm);
      if (mode64)
         dis_branch(False, binop(Iop_CmpNE64, getIReg(rs), getIReg(rt)),
                                 imm, &bstmt);
      else
         dis_branch(False, binop(Iop_CmpNE32, getIReg(rs), getIReg(rt)),
                                 imm, &bstmt);
      break;

   case 0x15:
      DIP("bnel r%d, r%d, %d", rs, rt, imm);
      lastn = dis_branch_likely(binop(mode64 ? Iop_CmpEQ64 : Iop_CmpEQ32,
                                      getIReg(rs), getIReg(rt)), imm);
      break;

   case 0x07:  
      DIP("bgtz r%d, %d", rs, imm);
      if (mode64)
         dis_branch(False, unop(Iop_Not1, binop(Iop_CmpLE64S, getIReg(rs),
                                mkU64(0x00))), imm, &bstmt);
      else
         dis_branch(False, unop(Iop_Not1, binop(Iop_CmpLE32S, getIReg(rs),
                                mkU32(0x00))), imm, &bstmt);
      break;

   case 0x17:  
      DIP("bgtzl r%d, %d", rs, imm);
      if (mode64)
         lastn = dis_branch_likely(binop(Iop_CmpLE64S, getIReg(rs),
                                         mkU64(0x00)), imm);
      else
         lastn = dis_branch_likely(binop(Iop_CmpLE32S, getIReg(rs),
                                         mkU32(0x00)), imm);
      break;

   case 0x06:  
      DIP("blez r%d, %d", rs, imm);
      if (mode64)
         dis_branch(False, binop(Iop_CmpLE64S, getIReg(rs), mkU64(0x0)),
                                imm, &bstmt);
      else
         dis_branch(False,binop(Iop_CmpLE32S, getIReg(rs), mkU32(0x0)), imm,
                                &bstmt);
      break;

   case 0x16:  
      DIP("blezl r%d, %d", rs, imm);
      lastn = dis_branch_likely(unop(Iop_Not1, (binop(mode64 ? Iop_CmpLE64S :
                                     Iop_CmpLE32S, getIReg(rs), mode64 ?
                                     mkU64(0x0) : mkU32(0x0)))), imm);
      break;

   case 0x08: {  
      DIP("addi r%d, r%d, %d", rt, rs, imm);
      IRTemp tmpRs32 = newTemp(Ity_I32);
      assign(tmpRs32, mkNarrowTo32(ty, getIReg(rs)));

      t0 = newTemp(Ity_I32);
      t1 = newTemp(Ity_I32);
      t2 = newTemp(Ity_I32);
      t3 = newTemp(Ity_I32);
      t4 = newTemp(Ity_I32);

      assign(t0, binop(Iop_Add32, mkexpr(tmpRs32),
                       mkU32(extend_s_16to32(imm))));
      assign(t1, binop(Iop_Xor32, mkexpr(tmpRs32),
                       mkU32(extend_s_16to32(imm))));
      assign(t2, unop(Iop_1Sto32, binop(Iop_CmpEQ32, binop(Iop_And32,
                      mkexpr(t1), mkU32(0x80000000)), mkU32(0x80000000))));

      assign(t3, binop(Iop_Xor32, mkexpr(t0), mkexpr(tmpRs32)));
      assign(t4, unop(Iop_1Sto32, binop(Iop_CmpNE32, binop(Iop_And32,
                      mkexpr(t3), mkU32(0x80000000)), mkU32(0x80000000))));

      stmt(IRStmt_Exit(binop(Iop_CmpEQ32, binop(Iop_Or32, mkexpr(t2),
                             mkexpr(t4)), mkU32(0)), Ijk_SigFPE_IntOvf,
                       mode64 ? IRConst_U64(guest_PC_curr_instr + 4) :
                                IRConst_U32(guest_PC_curr_instr + 4),
                       OFFB_PC));

      putIReg(rt,  mkWidenFrom32(ty, mkexpr(t0), True));
      break;
   }
   case 0x09:  
      DIP("addiu r%d, r%d, %d", rt, rs, imm);
      if (mode64) {
         putIReg(rt, mkWidenFrom32(ty, binop(Iop_Add32,
                     mkNarrowTo32(ty, getIReg(rs)),mkU32(extend_s_16to32(imm))),
                     True));
      } else
         putIReg(rt, binop(Iop_Add32, getIReg(rs),mkU32(extend_s_16to32(imm))));
      break;

   case 0x0C:  
      DIP("andi r%d, r%d, %d", rt, rs, imm);
      if (mode64) {
         ALUI_PATTERN64(Iop_And64);
      } else {
         ALUI_PATTERN(Iop_And32);
      }
      break;

   case 0x0E:  
      DIP("xori r%d, r%d, %d", rt, rs, imm);
      if (mode64) {
         ALUI_PATTERN64(Iop_Xor64);
      } else {
         ALUI_PATTERN(Iop_Xor32);
      }
      break;

   case 0x0D:  
      DIP("ori r%d, r%d, %d", rt, rs, imm);
      if (mode64) {
         ALUI_PATTERN64(Iop_Or64);
      } else {
         ALUI_PATTERN(Iop_Or32);
      }
      break;

   case 0x0A:  
      DIP("slti r%d, r%d, %d", rt, rs, imm);
      if (mode64)
         putIReg(rt, unop(Iop_1Uto64, binop(Iop_CmpLT64S, getIReg(rs),
                                            mkU64(extend_s_16to64(imm)))));
      else
         putIReg(rt, unop(Iop_1Uto32, binop(Iop_CmpLT32S, getIReg(rs),
                                            mkU32(extend_s_16to32(imm)))));
      break;

   case 0x0B:  
      DIP("sltiu r%d, r%d, %d", rt, rs, imm);
      if (mode64)
         putIReg(rt, unop(Iop_1Uto64, binop(Iop_CmpLT64U, getIReg(rs),
                                            mkU64(extend_s_16to64(imm)))));
      else
         putIReg(rt, unop(Iop_1Uto32, binop(Iop_CmpLT32U, getIReg(rs),
                                            mkU32(extend_s_16to32(imm)))));
      break;

   case 0x18: {  
      DIP("daddi r%d, r%d, %d", rt, rs, imm);
      IRTemp tmpRs64 = newTemp(Ity_I64);
      assign(tmpRs64, getIReg(rs));

      t0 = newTemp(Ity_I64);
      t1 = newTemp(Ity_I64);
      t2 = newTemp(Ity_I64);
      t3 = newTemp(Ity_I64);
      t4 = newTemp(Ity_I64);

      assign(t0, binop(Iop_Add64, mkexpr(tmpRs64),
                       mkU64(extend_s_16to64(imm))));
      assign(t1, binop(Iop_Xor64, mkexpr(tmpRs64),
                       mkU64(extend_s_16to64(imm))));
      assign(t2, unop(Iop_1Sto64, binop(Iop_CmpEQ64, binop(Iop_And64,
                      mkexpr(t1), mkU64(0x8000000000000000ULL)),
                                        mkU64(0x8000000000000000ULL))));

      assign(t3, binop(Iop_Xor64, mkexpr(t0), mkexpr(tmpRs64)));
      assign(t4, unop(Iop_1Sto64, binop(Iop_CmpNE64, binop(Iop_And64,
                      mkexpr(t3), mkU64(0x8000000000000000ULL)),
                                        mkU64(0x8000000000000000ULL))));

      stmt(IRStmt_Exit(binop(Iop_CmpEQ64, binop(Iop_Or64, mkexpr(t2),
                             mkexpr(t4)), mkU64(0)), Ijk_SigFPE_IntOvf,
                       IRConst_U64(guest_PC_curr_instr + 4),
                       OFFB_PC));

      putIReg(rt,  mkexpr(t0));
      break;
   }

   case 0x19:  
      DIP("daddiu r%d, r%d, %d", rt, rs, imm);
      putIReg(rt, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));
      break;

   case 0x1A: {
      
      vassert(mode64);
      DIP("ldl r%u, %d(r%u)", rt, imm, rs);
      
#if defined (_MIPSEL)
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));
#elif defined (_MIPSEB)
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Xor64, mkU64(0x7), binop(Iop_Add64, getIReg(rs),
                                  mkU64(extend_s_16to64(imm)))));
#endif
      
      
      LWX_SWX_PATTERN64_1;

      
      t3 = newTemp(Ity_I64);
      assign(t3, binop(Iop_Shl64, load(Ity_I64, mkexpr(t2)),
                 narrowTo(Ity_I8, binop(Iop_Shl64, binop(Iop_Sub64, mkU64(0x07),
                 mkexpr(t4)), mkU8(3)))));

      
      t5 = newTemp(Ity_I64);
      t6 = newTemp(Ity_I64);
      t7 = newTemp(Ity_I64);

      assign(t5, binop(Iop_Mul64, mkexpr(t4), mkU64(0x8)));

      assign(t6, binop(Iop_Shr64, mkU64(0x00FFFFFFFFFFFFFFULL),
                       narrowTo(Ity_I8, mkexpr(t5))));

      assign(t7, binop(Iop_And64, getIReg(rt), mkexpr(t6)));

      putIReg(rt, binop(Iop_Or64, mkexpr(t7), mkexpr(t3)));
      break;
   }

   case 0x1B: {
      
      vassert(mode64);
      DIP("ldr r%u,%d(r%u)", rt, imm, rs);
      
#if defined (_MIPSEL)
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Add64, getIReg(rs), mkU64(extend_s_16to64(imm))));
#elif defined (_MIPSEB)
      t1 = newTemp(Ity_I64);
      assign(t1, binop(Iop_Xor64, mkU64(0x7), binop(Iop_Add64, getIReg(rs),
                                  mkU64(extend_s_16to64(imm)))));
#endif
      
      
      LWX_SWX_PATTERN64_1;

      
      t3 = newTemp(Ity_I64);
      assign(t3, binop(Iop_Shr64, load(Ity_I64, mkexpr(t2)),
                 narrowTo(Ity_I8, binop(Iop_Shl64, mkexpr(t4), mkU8(3)))));

      
      t5 = newTemp(Ity_I64);
      assign(t5, binop(Iop_And64, getIReg(rt), unop(Iop_Not64,
                 binop(Iop_Shr64, mkU64(0xFFFFFFFFFFFFFFFFULL),
                 narrowTo(Ity_I8, binop(Iop_Shl64, mkexpr(t4), mkU8(0x3)))))));

      putIReg(rt, binop(Iop_Or64, mkexpr(t5), mkexpr(t3)));
      break;
   }

   case 0x27:  
      DIP("lwu r%u,%d(r%u)", rt, imm, rs);
      LOAD_STORE_PATTERN;

      putIReg(rt, mkWidenFrom32(ty, load(Ity_I32, mkexpr(t1)), False));
      break;

   case 0x30:  
      DIP("ll r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;

      t2 = newTemp(Ity_I32);
#if defined (_MIPSEL)
      stmt(IRStmt_LLSC(Iend_LE, t2, mkexpr(t1), NULL  ));
#elif defined (_MIPSEB)
      stmt(IRStmt_LLSC(Iend_BE, t2, mkexpr(t1), NULL  ));
#endif
      if (mode64)
         putIReg(rt, unop(Iop_32Sto64, mkexpr(t2)));
      else
         putIReg(rt, mkexpr(t2));
      break;

   case 0x34:  
      DIP("lld r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;

      t2 = newTemp(Ity_I64);
#if defined (_MIPSEL)
      stmt(IRStmt_LLSC
           (Iend_LE, t2, mkexpr(t1), NULL  ));
#elif defined (_MIPSEB)
      stmt(IRStmt_LLSC
           (Iend_BE, t2, mkexpr(t1), NULL  ));
#endif

      putIReg(rt, mkexpr(t2));
      break;

   case 0x38:  
      DIP("sc r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;

      t2 = newTemp(Ity_I1);
#if defined (_MIPSEL)
      stmt(IRStmt_LLSC(Iend_LE, t2, mkexpr(t1), mkNarrowTo32(ty, getIReg(rt))));
#elif defined (_MIPSEB)
      stmt(IRStmt_LLSC(Iend_BE, t2, mkexpr(t1), mkNarrowTo32(ty, getIReg(rt))));
#endif

      putIReg(rt, unop(mode64 ? Iop_1Uto64 : Iop_1Uto32, mkexpr(t2)));
      break;

   case 0x3C:  
      DIP("sdc r%d, %d(r%d)", rt, imm, rs);
      LOAD_STORE_PATTERN;

      t2 = newTemp(Ity_I1);
#if defined (_MIPSEL)
      stmt(IRStmt_LLSC(Iend_LE, t2, mkexpr(t1), getIReg(rt)));
#elif defined (_MIPSEB)
      stmt(IRStmt_LLSC(Iend_BE, t2, mkexpr(t1), getIReg(rt)));
#endif

      putIReg(rt, unop(Iop_1Uto64, mkexpr(t2)));
      break;

   case 0x37:  
      DIP("ld r%u, %d(r%u)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      putIReg(rt, load(Ity_I64, mkexpr(t1)));
      break;

   case 0x3F:  
      DIP("sd r%u, %d(r%u)", rt, imm, rs);
      LOAD_STORE_PATTERN;
      store(mkexpr(t1), getIReg(rt));
      break;

   decode_failure_dsp:
      vex_printf("Error occured while trying to decode MIPS32 DSP "
                 "instruction.\nYour platform probably doesn't support "
                 "MIPS32 DSP ASE.\n");
   decode_failure:
      
      if (sigill_diag)
         vex_printf("vex mips->IR: unhandled instruction bytes: "
                    "0x%x 0x%x 0x%x 0x%x\n",
                    (Int) getIByte(delta_start + 0),
                    (Int) getIByte(delta_start + 1),
                    (Int) getIByte(delta_start + 2),
                    (Int) getIByte(delta_start + 3));

      if (mode64) {
         stmt(IRStmt_Put(offsetof(VexGuestMIPS64State, guest_PC),
              mkU64(guest_PC_curr_instr)));
         jmp_lit64(&dres, Ijk_NoDecode, guest_PC_curr_instr);
      } else {
         stmt(IRStmt_Put(offsetof(VexGuestMIPS32State, guest_PC),
              mkU32(guest_PC_curr_instr)));
         jmp_lit32(&dres, Ijk_NoDecode, guest_PC_curr_instr);
      }
      dres.whatNext = Dis_StopHere;
      dres.len = 0;
      return dres;
   }  

   

   if (delay_slot_branch) {
      delay_slot_branch = False;
      stmt(bstmt);
      bstmt = NULL;
      if (mode64)
         putPC(mkU64(guest_PC_curr_instr + 4));
      else
         putPC(mkU32(guest_PC_curr_instr + 4));
      dres.jk_StopHere = is_Branch_or_Jump_and_Link(guest_code + delta - 4) ?
                         Ijk_Call : Ijk_Boring;
   }

   if (likely_delay_slot) {
      dres.jk_StopHere = Ijk_Boring;
      dres.whatNext = Dis_StopHere;
      putPC(lastn);
      lastn = NULL;
   }
   if (delay_slot_jump) {
      putPC(lastn);
      lastn = NULL;
      dres.jk_StopHere = is_Branch_or_Jump_and_Link(guest_code + delta - 4) ?
                         Ijk_Call : Ijk_Boring;
   }

 decode_success:
   
   switch (dres.whatNext) {
      case Dis_Continue:
         if (mode64)
            putPC(mkU64(guest_PC_curr_instr + 4));
         else
            putPC(mkU32(guest_PC_curr_instr + 4));
         break;
      case Dis_ResteerU:
      case Dis_ResteerC:
         putPC(mkU32(dres.continueAt));
         break;
      case Dis_StopHere:
         break;
      default:
         vassert(0);
         break;
   }

   if (((vex_control.guest_max_insns - 1) == (delta + 4) / 4)
       &&  (dres.whatNext != Dis_StopHere))
      if (branch_or_jump(guest_code + delta + 4)) {
         dres.whatNext = Dis_StopHere;
         dres.jk_StopHere = Ijk_Boring;
         if (mode64)
            putPC(mkU64(guest_PC_curr_instr + 4));
         else
            putPC(mkU32(guest_PC_curr_instr + 4));
      }
   dres.len = 4;

   DIP("\n");

   return dres;

}


DisResult disInstr_MIPS( IRSB*        irsb_IN,
                         Bool         (*resteerOkFn) ( void *, Addr64 ),
                         Bool         resteerCisOk,
                         void*        callback_opaque,
                         UChar*       guest_code_IN,
                         Long         delta,
                         Addr64       guest_IP,
                         VexArch      guest_arch,
                         VexArchInfo* archinfo,
                         VexAbiInfo*  abiinfo,
                         Bool         host_bigendian_IN,
                         Bool         sigill_diag_IN )
{
   DisResult dres;
   
   vassert(guest_arch == VexArchMIPS32 || guest_arch == VexArchMIPS64);

   mode64 = guest_arch != VexArchMIPS32;
#if (__mips_fpr==64)
   fp_mode64 = ((VEX_MIPS_REV(archinfo->hwcaps) == VEX_PRID_CPU_32FPR)
                || guest_arch == VexArchMIPS64);
#endif

   guest_code = guest_code_IN;
   irsb = irsb_IN;
   host_is_bigendian = host_bigendian_IN;
#if defined(VGP_mips32_linux)
   guest_PC_curr_instr = (Addr32)guest_IP;
#elif defined(VGP_mips64_linux)
   guest_PC_curr_instr = (Addr64)guest_IP;
#endif

   dres = disInstr_MIPS_WRK(resteerOkFn, resteerCisOk, callback_opaque,
                            delta, archinfo, abiinfo, sigill_diag_IN);

   return dres;
}
