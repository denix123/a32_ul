

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2004-2013 OpenWorks LLP
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

   Neither the names of the U.S. Department of Energy nor the
   University of California nor the names of its contributors may be
   used to endorse or promote products derived from this software
   without prior written permission.
*/

#ifndef __VEX_HOST_GENERIC_REGS_H
#define __VEX_HOST_GENERIC_REGS_H

#include "libvex_basictypes.h"




typedef
   struct {
      UInt reg;
   }
   HReg;

typedef
   enum { 
      HRcINVALID=1,   
      HRcInt32=3,     
      HRcInt64=4,     
      HRcFlt32=5,     
      HRcFlt64=6,     
      HRcVec64=7,     
      HRcVec128=8     
   }
   HRegClass;

extern void ppHRegClass ( HRegClass );


extern void ppHReg ( HReg );

static inline HReg mkHReg ( UInt regno, HRegClass rc, Bool virtual ) {
   UInt r24 = regno & 0x00FFFFFF;
   if (r24 != regno)
      vpanic("mkHReg: regno exceeds 2^24");
   HReg r;
   r.reg = regno | (((UInt)rc) << 28) | (virtual ? (1<<24) : 0);
   return r;
}

static inline HRegClass hregClass ( HReg r ) {
   UInt rc = r.reg;
   rc = (rc >> 28) & 0x0F;
   vassert(rc >= HRcInt32 && rc <= HRcVec128);
   return (HRegClass)rc;
}

static inline UInt hregNumber ( HReg r ) {
   return r.reg & 0x00FFFFFF;
}

static inline Bool hregIsVirtual ( HReg r ) {
   return toBool(r.reg & (1<<24));
}

static inline Bool sameHReg ( HReg r1, HReg r2 )
{
   return toBool(r1.reg == r2.reg);
}

static const HReg INVALID_HREG = { 0xFFFFFFFF };

static inline Bool hregIsInvalid ( HReg r )
{
   return sameHReg(r, INVALID_HREG);
}


typedef
   enum { HRmRead, HRmWrite, HRmModify }
   HRegMode;


#define N_HREG_USAGE 25

typedef
   struct {
      HReg     hreg[N_HREG_USAGE];
      HRegMode mode[N_HREG_USAGE];
      Int      n_used;
   }
   HRegUsage;

extern void ppHRegUsage ( HRegUsage* );

static inline void initHRegUsage ( HRegUsage* tab ) {
   tab->n_used = 0;
}

extern void addHRegUse ( HRegUsage*, HRegMode, HReg );





#define N_HREG_REMAP 6

typedef
   struct {
      HReg orig       [N_HREG_REMAP];
      HReg replacement[N_HREG_REMAP];
      Int  n_used;
   }
   HRegRemap;

extern void ppHRegRemap     ( HRegRemap* );
extern void initHRegRemap   ( HRegRemap* );
extern void addToHRegRemap  ( HRegRemap*, HReg, HReg );
extern HReg lookupHRegRemap ( HRegRemap*, HReg );




typedef  void  HInstr;


typedef
   struct {
      HInstr** arr;
      Int      arr_size;
      Int      arr_used;
      Int      n_vregs;
   }
   HInstrArray;

extern HInstrArray* newHInstrArray ( void );
extern void         addHInstr ( HInstrArray*, HInstr* );




typedef
   enum {
      RLPri_INVALID,   
      RLPri_None,      
      RLPri_Int,       
      RLPri_2Int,      
      RLPri_V128SpRel, 
      RLPri_V256SpRel  
   }
   RetLocPrimary;

typedef
   struct {
      
      RetLocPrimary pri;
      Int spOff;
   }
   RetLoc;

extern void ppRetLoc ( RetLoc rloc );

static inline RetLoc mk_RetLoc_simple ( RetLocPrimary pri ) {
   vassert(pri >= RLPri_INVALID && pri <= RLPri_2Int);
   return (RetLoc){pri, 0};
}

static inline RetLoc mk_RetLoc_spRel ( RetLocPrimary pri, Int off ) {
   vassert(pri >= RLPri_V128SpRel && pri <= RLPri_V256SpRel);
   return (RetLoc){pri, off};
}

static inline Bool is_sane_RetLoc ( RetLoc rloc ) {
   switch (rloc.pri) {
      case RLPri_None: case RLPri_Int: case RLPri_2Int:
         return rloc.spOff == 0;
      case RLPri_V128SpRel: case RLPri_V256SpRel:
         return True;
      default:
         return False;
   }
}

static inline RetLoc mk_RetLoc_INVALID ( void ) {
   return (RetLoc){RLPri_INVALID, 0};
}

static inline Bool is_RetLoc_INVALID ( RetLoc rl ) {
   return rl.pri == RLPri_INVALID && rl.spOff == 0;
}



extern
HInstrArray* doRegisterAllocation (

    
   HInstrArray* instrs_in,

   HReg* available_real_regs,
   Int   n_available_real_regs,

   Bool (*isMove) (HInstr*, HReg*, HReg*),

   
   void (*getRegUsage) (HRegUsage*, HInstr*, Bool),

   
   void (*mapRegs) (HRegRemap*, HInstr*, Bool),

   void    (*genSpill) (  HInstr**, HInstr**, HReg, Int, Bool ),
   void    (*genReload) ( HInstr**, HInstr**, HReg, Int, Bool ),
   HInstr* (*directReload) ( HInstr*, HReg, Short ),
   Int     guest_sizeB,

   
   void (*ppInstr) ( HInstr*, Bool ),
   void (*ppReg) ( HReg ),

   
   Bool mode64
);


#endif 

