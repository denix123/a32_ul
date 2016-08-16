/* Internal definitions for libasm.
   Copyright (C) 2002, 2004, 2005 Red Hat, Inc.
   This file is part of Red Hat elfutils.

   Red Hat elfutils is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 2 of the License.

   Red Hat elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with Red Hat elfutils; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301 USA.

   Red Hat elfutils is an included package of the Open Invention Network.
   An included package of the Open Invention Network is a package for which
   Open Invention Network licensees cross-license their patents.  No patent
   license is granted, either expressly or impliedly, by designation as an
   included package.  Should you wish to participate in the Open Invention
   Network licensing program, please visit www.openinventionnetwork.com
   <http://www.openinventionnetwork.com>.  */

#ifndef _LIBASMP_H
#define _LIBASMP_H 1

#include <stdio.h>

#include <libasm.h>

#define _(Str) dgettext ("elfutils", Str)


enum
  {
    ASM_E_NOERROR,
    ASM_E_NOMEM,		
    ASM_E_CANNOT_CREATE,	
    ASM_E_INVALID,		
    ASM_E_CANNOT_CHMOD,		
    ASM_E_CANNOT_RENAME,	
    ASM_E_DUPLSYM,		
    ASM_E_LIBELF,		
    ASM_E_TYPE,			
    ASM_E_IOERROR,		
    ASM_E_ENOSUP,		
    ASM_E_NUM			
  };


#define ASM_ABS_SCN ((Elf_Scn *) 1)
#define ASM_COM_SCN ((Elf_Scn *) 2)


#include <symbolhash.h>


struct AsmScn
{
  
  AsmCtx_t *ctx;

  
  unsigned int subsection_id;

  
  GElf_Word type;

  union
  {
    
    struct
    {
      
      Elf_Scn *scn;

      
      struct Ebl_Strent *strent;

      
      struct AsmScn *next_in_group;
    } main;

    
    AsmScn_t *up;
  } data;

  
  GElf_Off offset;
  
  GElf_Word max_align;

  
  struct AsmData
  {
    
    size_t len;

    
    size_t maxlen;

    
    struct AsmData *next;

    
    char data[flexarr_size];
  } *content;

  
  struct FillPattern
  {
    size_t len;
    char bytes[flexarr_size];
  } *pattern;

  
  AsmScn_t *subnext;

  
  AsmScn_t *allnext;

  
  char name[flexarr_size];
};


struct AsmCtx
{
  
  int fd;

  
  bool textp;

  
  union
  {
    
    Elf *elf;
    
    FILE *file;
  } out;


  
  AsmScn_t *section_list;
  
  struct Ebl_Strtab *section_strtab;

  
  asm_symbol_tab symbol_tab;
  
  unsigned int nsymbol_tab;
  
  struct Ebl_Strtab *symbol_strtab;

  
  struct AsmScnGrp *groups;
  
  size_t ngroups;

  
  GElf_Word common_align;

  
  rwlock_define (,lock);

  
  unsigned int tempsym_count;

  
  char *fname;
  
  char tmp_fname[flexarr_size];
};


struct AsmSym
{
  
  AsmScn_t *scn;

  
  int8_t type;
  
  int8_t binding;

  
  GElf_Xword size;

  
  GElf_Off offset;

  
  size_t symidx;

  
  struct Ebl_Strent *strent;
};


struct AsmScnGrp
{
  
  struct Ebl_Strent *strent;

  
  Elf_Scn *scn;

  
  struct AsmSym *signature;

  
  struct AsmScn *members;
  
  size_t nmembers;

  
  Elf32_Word flags;

  
  struct AsmScnGrp *next;

  
  char name[flexarr_size];
};


struct DisasmCtx
{
  
  Ebl *ebl;

  Elf *elf;

  
  DisasmGetSymCB_t symcb;
};


extern const struct FillPattern *__libasm_default_pattern
     attribute_hidden;


extern int __libasm_ensure_section_space (AsmScn_t *asmscn, size_t len)
     internal_function;

extern void __libasm_finictx (AsmCtx_t *ctx) internal_function;

extern void __libasm_seterrno (int err) internal_function;

extern AsmScn_t *__asm_newscn_internal (AsmCtx_t *ctx, const char *scnname,
					GElf_Word type, GElf_Xword flags)
     attribute_hidden;


extern int __asm_addint8_internal (AsmScn_t *asmscn, int8_t num)
     attribute_hidden;
extern int __asm_addint16_internal (AsmScn_t *asmscn, int16_t num)
     attribute_hidden;
extern int __asm_addint32_internal (AsmScn_t *asmscn, int32_t num)
     attribute_hidden;
extern int __asm_addint64_internal (AsmScn_t *asmscn, int64_t num)
     attribute_hidden;


extern int __disasm_cb_internal (DisasmCtx_t *ctx, const uint8_t **startp,
				 const uint8_t *end, GElf_Addr addr,
				 const char *fmt, DisasmOutputCB_t outcb,
				 void *outcbarp, void *symcbarg)
     attribute_hidden;


#define asm_emit_symbol_p(name) (strncmp (name, ".L", 2) != 0)

#endif	
