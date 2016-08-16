/* Internal definitions for libdwfl.
   Copyright (C) 2005-2011 Red Hat, Inc.
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

   In addition, as a special exception, Red Hat, Inc. gives You the
   additional right to link the code of Red Hat elfutils with code licensed
   under any Open Source Initiative certified open source license
   (http://www.opensource.org/licenses/index.php) which requires the
   distribution of source code with any binary distribution and to
   distribute linked combinations of the two.  Non-GPL Code permitted under
   this exception must only link to the code of Red Hat elfutils through
   those well defined interfaces identified in the file named EXCEPTION
   found in the source code files (the "Approved Interfaces").  The files
   of Non-GPL Code may instantiate templates or use macros or inline
   functions from the Approved Interfaces without causing the resulting
   work to be covered by the GNU General Public License.  Only Red Hat,
   Inc. may make changes or additions to the list of Approved Interfaces.
   Red Hat's grant of this exception is conditioned upon your not adding
   any new exceptions.  If you wish to add a new Approved Interface or
   exception, please contact Red Hat.  You must obey the GNU General Public
   License in all respects for all of the Red Hat elfutils code and other
   code used in conjunction with Red Hat elfutils except the Non-GPL Code
   covered by this exception.  If you modify this file, you may extend this
   exception to your version of the file, but you are not obligated to do
   so.  If you do not wish to provide this exception without modification,
   you must delete this exception statement from your version and license
   this file solely under the GPL without exception.

   Red Hat elfutils is an included package of the Open Invention Network.
   An included package of the Open Invention Network is a package for which
   Open Invention Network licensees cross-license their patents.  No patent
   license is granted, either expressly or impliedly, by designation as an
   included package.  Should you wish to participate in the Open Invention
   Network licensing program, please visit www.openinventionnetwork.com
   <http://www.openinventionnetwork.com>.  */

#ifndef _LIBDWFLP_H
#define _LIBDWFLP_H	1

#ifndef PACKAGE_NAME
# include <config.h>
#endif
#include <libdwfl.h>
#include <libebl.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../libdw/libdwP.h"	

#define _(Str) dgettext ("elfutils", Str)

#define DWFL_ERRORS							      \
  DWFL_ERROR (NOERROR, N_("no error"))					      \
  DWFL_ERROR (UNKNOWN_ERROR, N_("unknown error"))			      \
  DWFL_ERROR (NOMEM, N_("out of memory"))				      \
  DWFL_ERROR (ERRNO, N_("See errno"))					      \
  DWFL_ERROR (LIBELF, N_("See elf_errno"))				      \
  DWFL_ERROR (LIBDW, N_("See dwarf_errno"))				      \
  DWFL_ERROR (LIBEBL, N_("See ebl_errno (XXX missing)"))		      \
  DWFL_ERROR (ZLIB, N_("gzip decompression failed"))			      \
  DWFL_ERROR (BZLIB, N_("bzip2 decompression failed"))			      \
  DWFL_ERROR (LZMA, N_("LZMA decompression failed"))			      \
  DWFL_ERROR (UNKNOWN_MACHINE, N_("no support library found for machine"))    \
  DWFL_ERROR (NOREL, N_("Callbacks missing for ET_REL file"))		      \
  DWFL_ERROR (BADRELTYPE, N_("Unsupported relocation type"))		      \
  DWFL_ERROR (BADRELOFF, N_("r_offset is bogus"))			      \
  DWFL_ERROR (BADSTROFF, N_("offset out of range"))			      \
  DWFL_ERROR (RELUNDEF, N_("relocation refers to undefined symbol"))	      \
  DWFL_ERROR (CB, N_("Callback returned failure"))			      \
  DWFL_ERROR (NO_DWARF, N_("No DWARF information found"))		      \
  DWFL_ERROR (NO_SYMTAB, N_("No symbol table found"))			      \
  DWFL_ERROR (NO_PHDR, N_("No ELF program headers"))			      \
  DWFL_ERROR (OVERLAP, N_("address range overlaps an existing module"))	      \
  DWFL_ERROR (ADDR_OUTOFRANGE, N_("address out of range"))		      \
  DWFL_ERROR (NO_MATCH, N_("no matching address range"))		      \
  DWFL_ERROR (TRUNCATED, N_("image truncated"))				      \
  DWFL_ERROR (ALREADY_ELF, N_("ELF file opened"))			      \
  DWFL_ERROR (BADELF, N_("not a valid ELF file"))			      \
  DWFL_ERROR (WEIRD_TYPE, N_("cannot handle DWARF type description"))	      \
  DWFL_ERROR (WRONG_ID_ELF, N_("ELF file does not match build ID"))	      \
  DWFL_ERROR (BAD_PRELINK, N_("corrupt .gnu.prelink_undo section data"))

#define DWFL_ERROR(name, text) DWFL_E_##name,
typedef enum { DWFL_ERRORS DWFL_E_NUM } Dwfl_Error;
#undef	DWFL_ERROR

#define OTHER_ERROR(name)	((unsigned int) DWFL_E_##name << 16)
#define DWFL_E(name, errno)	(OTHER_ERROR (name) | (errno))

extern int __libdwfl_canon_error (Dwfl_Error) internal_function;
extern void __libdwfl_seterrno (Dwfl_Error) internal_function;

struct Dwfl
{
  const Dwfl_Callbacks *callbacks;

  Dwfl_Module *modulelist;    

  GElf_Addr offline_next_address;

  GElf_Addr segment_align;	

  
  size_t lookup_elts;		
  size_t lookup_alloc;		
  GElf_Addr *lookup_addr;	
  Dwfl_Module **lookup_module;	
  int *lookup_segndx;		

  
  const void *lookup_tail_ident;
  GElf_Off lookup_tail_vaddr;
  GElf_Off lookup_tail_offset;
  int lookup_tail_ndx;
};

#define OFFLINE_REDZONE		0x10000

struct dwfl_file
{
  char *name;
  int fd;
  bool valid;			
  bool relocated;		

  Elf *elf;

  GElf_Addr vaddr;

  GElf_Addr address_sync;
};

struct Dwfl_Module
{
  Dwfl *dwfl;
  struct Dwfl_Module *next;	

  void *userdata;

  char *name;			
  GElf_Addr low_addr, high_addr;

  struct dwfl_file main, debug;
  GElf_Addr main_bias;
  Ebl *ebl;
  GElf_Half e_type;		
  Dwfl_Error elferr;		

  struct dwfl_relocation *reloc_info; 

  struct dwfl_file *symfile;	
  Elf_Data *symdata;		
  size_t syments;		
  int first_global;		
  Elf_Data *symstrdata;		
  Elf_Data *symxndxdata;	

  Dwarf *dw;			

  Dwfl_Error symerr;		
  Dwfl_Error dwerr;		

  
  struct dwfl_cu *first_cu, **cu;

  void *lazy_cu_root;		

  struct dwfl_arange *aranges;	

  void *build_id_bits;		
  GElf_Addr build_id_vaddr;	
  int build_id_len;		

  unsigned int ncu;
  unsigned int lazycu;		
  unsigned int naranges;

  Dwarf_CFI *dwarf_cfi;		
  Dwarf_CFI *eh_cfi;		

  int segment;			
  bool gc;			
};



struct dwfl_cu
{
  Dwarf_Die die;

  Dwfl_Module *mod;		

  struct dwfl_cu *next;		

  struct Dwfl_Lines *lines;
};

struct Dwfl_Lines
{
  struct dwfl_cu *cu;

  struct Dwfl_Line
  {
    unsigned int idx;		
  } idx[0];
};

static inline struct dwfl_cu *
dwfl_linecu_inline (const Dwfl_Line *line)
{
  const struct Dwfl_Lines *lines = ((const void *) line
				    - offsetof (struct Dwfl_Lines,
						idx[line->idx]));
  return lines->cu;
}
#define dwfl_linecu dwfl_linecu_inline

static inline GElf_Addr
dwfl_adjusted_address (Dwfl_Module *mod, GElf_Addr addr)
{
  return addr + mod->main_bias;
}

static inline GElf_Addr
dwfl_deadjust_address (Dwfl_Module *mod, GElf_Addr addr)
{
  return addr - mod->main_bias;
}

static inline Dwarf_Addr
dwfl_adjusted_dwarf_addr (Dwfl_Module *mod, Dwarf_Addr addr)
{
  return dwfl_adjusted_address (mod, (addr
				      - mod->debug.address_sync
				      + mod->main.address_sync));
}

static inline Dwarf_Addr
dwfl_deadjust_dwarf_addr (Dwfl_Module *mod, Dwarf_Addr addr)
{
  return (dwfl_deadjust_address (mod, addr)
	  - mod->main.address_sync
	  + mod->debug.address_sync);
}

static inline GElf_Addr
dwfl_adjusted_st_value (Dwfl_Module *mod, GElf_Addr addr)
{
  if (mod->symfile == &mod->main)
    return dwfl_adjusted_address (mod, addr);
  return dwfl_adjusted_dwarf_addr (mod, addr);
}

static inline GElf_Addr
dwfl_deadjust_st_value (Dwfl_Module *mod, GElf_Addr addr)
{
  if (mod->symfile == &mod->main)
    return dwfl_deadjust_address (mod, addr);
  return dwfl_deadjust_dwarf_addr (mod, addr);
}

struct dwfl_arange
{
  struct dwfl_cu *cu;
  size_t arange;		
};



extern void __libdwfl_module_free (Dwfl_Module *mod) internal_function;

extern void __libdwfl_getelf (Dwfl_Module *mod) internal_function;

extern Dwfl_Error __libdwfl_relocate (Dwfl_Module *mod, Elf *file, bool debug)
  internal_function;

extern Dwfl_Error __libdwfl_relocate_section (Dwfl_Module *mod, Elf *relocated,
					      Elf_Scn *relocscn, Elf_Scn *tscn,
					      bool partial)
  internal_function;

extern Dwfl_Error __libdwfl_relocate_value (Dwfl_Module *mod, Elf *elf,
					    size_t *shstrndx_cache,
					    Elf32_Word shndx,
					    GElf_Addr *value)
     internal_function;


extern Dwfl_Error __libdwfl_module_getebl (Dwfl_Module *mod) internal_function;

extern Dwarf_CFI *__libdwfl_set_cfi (Dwfl_Module *mod, Dwarf_CFI **slot,
				     Dwarf_CFI *cfi)
  internal_function;

extern Dwfl_Error __libdwfl_nextcu (Dwfl_Module *mod, struct dwfl_cu *lastcu,
				    struct dwfl_cu **cu) internal_function;

extern Dwfl_Error __libdwfl_addrcu (Dwfl_Module *mod, Dwarf_Addr addr,
				    struct dwfl_cu **cu) internal_function;

extern Dwfl_Error __libdwfl_cu_getsrclines (struct dwfl_cu *cu)
  internal_function;

extern int __libdwfl_find_build_id (Dwfl_Module *mod, bool set, Elf *elf)
  internal_function;

extern int __libdwfl_open_by_build_id (Dwfl_Module *mod, bool debug,
				       char **file_name) internal_function;

extern uint32_t __libdwfl_crc32 (uint32_t crc, unsigned char *buf, size_t len)
  attribute_hidden;
extern int __libdwfl_crc32_file (int fd, uint32_t *resp) attribute_hidden;


extern Dwfl_Module *__libdwfl_report_elf (Dwfl *dwfl, const char *name,
					  const char *file_name, int fd,
					  Elf *elf, GElf_Addr base, bool sanity)
  internal_function;

extern Dwfl_Module *__libdwfl_report_offline (Dwfl *dwfl, const char *name,
					      const char *file_name,
					      int fd, bool closefd,
					      int (*predicate) (const char *,
								const char *))
  internal_function;

extern Dwfl_Error __libdw_gunzip  (int fd, off64_t start_offset,
				   void *mapped, size_t mapped_size,
				   void **whole, size_t *whole_size)
  internal_function;
extern Dwfl_Error __libdw_bunzip2 (int fd, off64_t start_offset,
				   void *mapped, size_t mapped_size,
				   void **whole, size_t *whole_size)
  internal_function;
extern Dwfl_Error __libdw_unlzma (int fd, off64_t start_offset,
				  void *mapped, size_t mapped_size,
				  void **whole, size_t *whole_size)
  internal_function;

extern Dwfl_Error __libdw_image_header (int fd, off64_t *start_offset,
					void *mapped, size_t mapped_size)
  internal_function;

extern Dwfl_Error __libdw_open_file (int *fdp, Elf **elfp,
				     bool close_on_fail, bool archive_ok)
  internal_function;


typedef bool Dwfl_Memory_Callback (Dwfl *dwfl, int segndx,
				   void **buffer, size_t *buffer_available,
				   GElf_Addr vaddr, size_t minread, void *arg);

typedef bool Dwfl_Module_Callback (Dwfl_Module *mod, void **userdata,
				   const char *name, Dwarf_Addr base,
				   void **buffer, size_t *buffer_available,
				   GElf_Off cost, GElf_Off worthwhile,
				   GElf_Off whole, GElf_Off contiguous,
				   void *arg, Elf **elfp);

extern int dwfl_segment_report_module (Dwfl *dwfl, int ndx, const char *name,
				       Dwfl_Memory_Callback *memory_callback,
				       void *memory_callback_arg,
				       Dwfl_Module_Callback *read_eagerly,
				       void *read_eagerly_arg);

extern int dwfl_link_map_report (Dwfl *dwfl, const void *auxv, size_t auxv_size,
				 Dwfl_Memory_Callback *memory_callback,
				 void *memory_callback_arg);


INTDECL (dwfl_begin)
INTDECL (dwfl_errmsg)
INTDECL (dwfl_errno)
INTDECL (dwfl_addrmodule)
INTDECL (dwfl_addrsegment)
INTDECL (dwfl_addrdwarf)
INTDECL (dwfl_addrdie)
INTDECL (dwfl_core_file_report)
INTDECL (dwfl_getmodules)
INTDECL (dwfl_module_addrdie)
INTDECL (dwfl_module_address_section)
INTDECL (dwfl_module_addrsym)
INTDECL (dwfl_module_build_id)
INTDECL (dwfl_module_getdwarf)
INTDECL (dwfl_module_getelf)
INTDECL (dwfl_module_getsym)
INTDECL (dwfl_module_getsymtab)
INTDECL (dwfl_module_getsrc)
INTDECL (dwfl_module_report_build_id)
INTDECL (dwfl_report_elf)
INTDECL (dwfl_report_begin)
INTDECL (dwfl_report_begin_add)
INTDECL (dwfl_report_module)
INTDECL (dwfl_report_segment)
INTDECL (dwfl_report_offline)
INTDECL (dwfl_report_end)
INTDECL (dwfl_build_id_find_elf)
INTDECL (dwfl_build_id_find_debuginfo)
INTDECL (dwfl_standard_find_debuginfo)
INTDECL (dwfl_link_map_report)
INTDECL (dwfl_linux_kernel_find_elf)
INTDECL (dwfl_linux_kernel_module_section_address)
INTDECL (dwfl_linux_proc_report)
INTDECL (dwfl_linux_proc_maps_report)
INTDECL (dwfl_linux_proc_find_elf)
INTDECL (dwfl_linux_kernel_report_kernel)
INTDECL (dwfl_linux_kernel_report_modules)
INTDECL (dwfl_linux_kernel_report_offline)
INTDECL (dwfl_offline_section_address)
INTDECL (dwfl_module_relocate_address)
INTDECL (dwfl_module_dwarf_cfi)
INTDECL (dwfl_module_eh_cfi)

#define MODCB_ARGS(mod)	(mod), &(mod)->userdata, (mod)->name, (mod)->low_addr
#define CBFAIL		(errno ? DWFL_E (ERRNO, errno) : DWFL_E_CB);


#define DEFAULT_DEBUGINFO_PATH ":.debug:/usr/lib/debug"


#endif	
