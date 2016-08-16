/* Interface for libebl.
   Copyright (C) 2000-2010 Red Hat, Inc.
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

#ifndef _LIBEBL_H
#define _LIBEBL_H 1

#include <gelf.h>
#include "libdw.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "elf-knowledge.h"


typedef struct ebl Ebl;


#ifdef __cplusplus
extern "C" {
#endif

extern Ebl *ebl_openbackend (Elf *elf);
extern Ebl *ebl_openbackend_machine (GElf_Half machine);
extern Ebl *ebl_openbackend_emulation (const char *emulation);

extern void ebl_closebackend (Ebl *bh);



extern int ebl_get_elfmachine (Ebl *ebl) __attribute__ ((__pure__));

extern int ebl_get_elfclass (Ebl *ebl) __attribute__ ((__pure__));

extern int ebl_get_elfdata (Ebl *ebl) __attribute__ ((__pure__));



extern const char *ebl_backend_name (Ebl *ebl);

extern const char *ebl_object_type_name (Ebl *ebl, int object,
					 char *buf, size_t len);

extern const char *ebl_reloc_type_name (Ebl *ebl, int reloc,
					char *buf, size_t len);

extern bool ebl_reloc_type_check (Ebl *ebl, int reloc);

extern bool ebl_reloc_valid_use (Ebl *ebl, int reloc);

extern Elf_Type ebl_reloc_simple_type (Ebl *ebl, int reloc);

extern bool ebl_gotpc_reloc_check (Ebl *ebl, int reloc);

extern const char *ebl_segment_type_name (Ebl *ebl, int segment,
					  char *buf, size_t len);

extern const char *ebl_section_type_name (Ebl *ebl, int section,
					  char *buf, size_t len);

extern const char *ebl_section_name (Ebl *ebl, int section, int xsection,
				     char *buf, size_t len,
				     const char *scnnames[], size_t shnum);

extern const char *ebl_machine_flag_name (Ebl *ebl, GElf_Word flags,
					  char *buf, size_t len);

extern bool ebl_machine_flag_check (Ebl *ebl, GElf_Word flags);

extern bool ebl_machine_section_flag_check (Ebl *ebl, GElf_Xword flags);

extern bool ebl_check_special_section (Ebl *ebl, int ndx,
				       const GElf_Shdr *shdr, const char *name);

extern const char *ebl_symbol_type_name (Ebl *ebl, int symbol,
					 char *buf, size_t len);

extern const char *ebl_symbol_binding_name (Ebl *ebl, int binding,
					    char *buf, size_t len);

extern const char *ebl_dynamic_tag_name (Ebl *ebl, int64_t tag,
					 char *buf, size_t len);

extern bool ebl_dynamic_tag_check (Ebl *ebl, int64_t tag);

extern bool ebl_check_special_symbol (Ebl *ebl, GElf_Ehdr *ehdr,
				      const GElf_Sym *sym, const char *name,
				      const GElf_Shdr *destshdr);

extern bool ebl_check_st_other_bits (Ebl *ebl, unsigned char st_other);

extern GElf_Word ebl_sh_flags_combine (Ebl *ebl, GElf_Word flags1,
				       GElf_Word flags2);

extern const char *ebl_osabi_name (Ebl *ebl, int osabi, char *buf, size_t len);


extern const char *ebl_core_note_type_name (Ebl *ebl, uint32_t type, char *buf,
					    size_t len);

extern const char *ebl_object_note_type_name (Ebl *ebl, const char *name,
					      uint32_t type, char *buf,
					      size_t len);

extern void ebl_object_note (Ebl *ebl, const char *name, uint32_t type,
			     uint32_t descsz, const char *desc);

extern bool ebl_check_object_attribute (Ebl *ebl, const char *vendor,
					int tag, uint64_t value,
					const char **tag_name,
					const char **value_name);


extern bool ebl_debugscn_p (Ebl *ebl, const char *name);

extern bool ebl_copy_reloc_p (Ebl *ebl, int reloc);

extern bool ebl_none_reloc_p (Ebl *ebl, int reloc);

extern bool ebl_relative_reloc_p (Ebl *ebl, int reloc);

extern bool ebl_section_strip_p (Ebl *ebl, const GElf_Ehdr *ehdr,
				 const GElf_Shdr *shdr, const char *name,
				 bool remove_comment, bool only_remove_debug);

extern bool ebl_bss_plt_p (Ebl *ebl, GElf_Ehdr *ehdr);

extern int ebl_sysvhash_entrysize (Ebl *ebl);

extern int ebl_return_value_location (Ebl *ebl,
				      Dwarf_Die *functypedie,
				      const Dwarf_Op **locops);

/* Fill in register information given DWARF register numbers.
   If NAME is null, return the maximum REGNO + 1 that has a name.
   Otherwise, store in NAME the name for DWARF register number REGNO
   and return the number of bytes written (including '\0' terminator).
   Return -1 if NAMELEN is too short or REGNO is negative or too large.
   Return 0 if REGNO is unused (a gap in the DWARF number assignment).
   On success, set *SETNAME to a description like "integer" or "FPU"
   fit for "%s registers" title display, and *PREFIX to the string
   that precedes NAME in canonical assembler syntax (e.g. "%" or "$").
   The NAME string contains identifier characters only (maybe just digits).  */
extern ssize_t ebl_register_info (Ebl *ebl,
				  int regno, char *name, size_t namelen,
				  const char **prefix, const char **setname,
				  int *bits, int *type);

extern int ebl_syscall_abi (Ebl *ebl, int *sp, int *pc,
			    int *callno, int args[6]);

extern int ebl_abi_cfi (Ebl *ebl, Dwarf_CIE *abi_info)
  __nonnull_attribute__ (2);

struct Ebl_Strtab;
struct Ebl_Strent;

extern struct Ebl_Strtab *ebl_strtabinit (bool nullstr);

extern void ebl_strtabfree (struct Ebl_Strtab *st);

extern struct Ebl_Strent *ebl_strtabadd (struct Ebl_Strtab *st,
					 const char *str, size_t len);

extern void ebl_strtabfinalize (struct Ebl_Strtab *st, Elf_Data *data);

extern size_t ebl_strtaboffset (struct Ebl_Strent *se);

extern const char *ebl_string (struct Ebl_Strent *se);


struct Ebl_WStrtab;
struct Ebl_WStrent;

extern struct Ebl_WStrtab *ebl_wstrtabinit (bool nullstr);

extern void ebl_wstrtabfree (struct Ebl_WStrtab *st);

extern struct Ebl_WStrent *ebl_wstrtabadd (struct Ebl_WStrtab *st,
					   const wchar_t *str, size_t len);

extern void ebl_wstrtabfinalize (struct Ebl_WStrtab *st, Elf_Data *data);

extern size_t ebl_wstrtaboffset (struct Ebl_WStrent *se);


struct Ebl_GStrtab;
struct Ebl_GStrent;

extern struct Ebl_GStrtab *ebl_gstrtabinit (unsigned int width, bool nullstr);

extern void ebl_gstrtabfree (struct Ebl_GStrtab *st);

extern struct Ebl_GStrent *ebl_gstrtabadd (struct Ebl_GStrtab *st,
					   const char *str, size_t len);

extern void ebl_gstrtabfinalize (struct Ebl_GStrtab *st, Elf_Data *data);

extern size_t ebl_gstrtaboffset (struct Ebl_GStrent *se);


typedef struct
{
  Dwarf_Half offset;		
  Dwarf_Half regno;		
  uint8_t bits;			
  uint8_t pad;			
  Dwarf_Half count;		
} Ebl_Register_Location;

typedef struct
{
  const char *name;		
  const char *group;		
  Dwarf_Half offset;		
  Dwarf_Half count;
  Elf_Type type;
  char format;
  bool thread_identifier;
} Ebl_Core_Item;

extern int ebl_core_note (Ebl *ebl, const GElf_Nhdr *nhdr, const char *name,
			  GElf_Word *regs_offset, size_t *nregloc,
			  const Ebl_Register_Location **reglocs,
			  size_t *nitems, const Ebl_Core_Item **items)
  __nonnull_attribute__ (1, 2, 3, 4, 5, 6, 7, 8);

extern int ebl_auxv_info (Ebl *ebl, GElf_Xword a_type,
			  const char **name, const char **format)
  __nonnull_attribute__ (1, 3, 4);


#ifdef __cplusplus
}
#endif

#endif	
