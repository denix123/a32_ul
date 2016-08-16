/* Return the next data element from the section after possibly converting it.
   Copyright (C) 1998-2005, 2006, 2007 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 1998.

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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "libelfP.h"
#include <system.h>
#include "common.h"
#include "elf-knowledge.h"


#define TYPEIDX(Sh_Type) \
  (Sh_Type >= SHT_NULL && Sh_Type < SHT_NUM				      \
   ? Sh_Type								      \
   : (Sh_Type >= SHT_GNU_HASH && Sh_Type <= SHT_HISUNW			      \
      ? SHT_NUM + Sh_Type - SHT_GNU_HASH				      \
      : 0))

static const Elf_Type shtype_map[EV_NUM - 1][TYPEIDX (SHT_HISUNW) + 1] =
  {
    [EV_CURRENT - 1] =
    {
      [SHT_SYMTAB] = ELF_T_SYM,
      [SHT_RELA] = ELF_T_RELA,
      [SHT_HASH] = ELF_T_WORD,
      [SHT_DYNAMIC] = ELF_T_DYN,
      [SHT_REL] = ELF_T_REL,
      [SHT_DYNSYM] = ELF_T_SYM,
      [SHT_INIT_ARRAY] = ELF_T_ADDR,
      [SHT_FINI_ARRAY] = ELF_T_ADDR,
      [SHT_PREINIT_ARRAY] = ELF_T_ADDR,
      [SHT_GROUP] = ELF_T_WORD,
      [SHT_SYMTAB_SHNDX] = ELF_T_WORD,
      [SHT_NOTE] = ELF_T_NHDR,
      [TYPEIDX (SHT_GNU_verdef)] = ELF_T_VDEF,
      [TYPEIDX (SHT_GNU_verneed)] = ELF_T_VNEED,
      [TYPEIDX (SHT_GNU_versym)] = ELF_T_HALF,
      [TYPEIDX (SHT_SUNW_syminfo)] = ELF_T_SYMINFO,
      [TYPEIDX (SHT_SUNW_move)] = ELF_T_MOVE,
      [TYPEIDX (SHT_GNU_LIBLIST)] = ELF_T_LIB,
      [TYPEIDX (SHT_GNU_HASH)] = ELF_T_GNUHASH,
    }
  };

#if !ALLOW_UNALIGNED
const uint_fast8_t __libelf_type_aligns[EV_NUM - 1][ELFCLASSNUM - 1][ELF_T_NUM] =
  {
# define TYPE_ALIGNS(Bits)						      \
    {									      \
      [ELF_T_ADDR] = __alignof__ (ElfW2(Bits,Addr)),			      \
      [ELF_T_HALF] = __alignof__ (ElfW2(Bits,Half)),			      \
      [ELF_T_WORD] = __alignof__ (ElfW2(Bits,Word)),			      \
      [ELF_T_SYM] = __alignof__ (ElfW2(Bits,Sym)),			      \
      [ELF_T_SYMINFO] = __alignof__ (ElfW2(Bits,Syminfo)),		      \
      [ELF_T_REL] = __alignof__ (ElfW2(Bits,Rel)),			      \
      [ELF_T_RELA] = __alignof__ (ElfW2(Bits,Rela)),			      \
      [ELF_T_DYN] = __alignof__ (ElfW2(Bits,Dyn)),			      \
      [ELF_T_VDEF] = __alignof__ (ElfW2(Bits,Verdef)),			      \
      [ELF_T_VDAUX] = __alignof__ (ElfW2(Bits,Verdaux)),		      \
      [ELF_T_VNEED] = __alignof__ (ElfW2(Bits,Verneed)),		      \
      [ELF_T_VNAUX] = __alignof__ (ElfW2(Bits,Vernaux)),		      \
      [ELF_T_MOVE] = __alignof__ (ElfW2(Bits,Move)),			      \
      [ELF_T_LIB] = __alignof__ (ElfW2(Bits,Lib)),			      \
      [ELF_T_NHDR] = __alignof__ (ElfW2(Bits,Nhdr)),			      \
    }
    [EV_CURRENT - 1] =
    {
      [ELFCLASS32 - 1] = TYPE_ALIGNS (32),
      [ELFCLASS64 - 1] = TYPE_ALIGNS (64),
    }
# undef TYPE_ALIGNS
  };
#endif


static void
convert_data (Elf_Scn *scn, int version __attribute__ ((unused)), int eclass,
	      int data, size_t size, Elf_Type type)
{
  const size_t align = __libelf_type_align (eclass, type);

  if (data == MY_ELFDATA)
    {
      if (((((size_t) (char *) scn->rawdata_base)) & (align - 1)) == 0)
	
	scn->data_base = scn->rawdata_base;
      else
	{
	  scn->data_base = (char *) malloc (size);
	  if (scn->data_base == NULL)
	    {
	      __libelf_seterrno (ELF_E_NOMEM);
	      return;
	    }

	  
	  memcpy (scn->data_base, scn->rawdata_base, size);
	}
    }
  else
    {
      xfct_t fp;

      scn->data_base = (char *) malloc (size);
      if (scn->data_base == NULL)
	{
	  __libelf_seterrno (ELF_E_NOMEM);
	  return;
	}

      
#if EV_NUM != 2
      fp = __elf_xfctstom[version - 1][__libelf_version - 1][eclass - 1][type];
#else
      fp = __elf_xfctstom[0][0][eclass - 1][type];
#endif

      fp (scn->data_base, scn->rawdata_base, size, 0);
    }

  scn->data_list.data.d.d_buf = scn->data_base;
  scn->data_list.data.d.d_size = size;
  scn->data_list.data.d.d_type = type;
  scn->data_list.data.d.d_off = scn->rawdata.d.d_off;
  scn->data_list.data.d.d_align = scn->rawdata.d.d_align;
  scn->data_list.data.d.d_version = scn->rawdata.d.d_version;

  scn->data_list.data.s = scn;
}


int
internal_function
__libelf_set_rawdata_wrlock (Elf_Scn *scn)
{
  size_t offset;
  size_t size;
  size_t align;
  int type;
  Elf *elf = scn->elf;

  if (elf->class == ELFCLASS32)
    {
      Elf32_Shdr *shdr
	= scn->shdr.e32 ?: __elf32_getshdr_wrlock (scn);

      if (shdr == NULL)
	
	return 1;

      offset = shdr->sh_offset;
      size = shdr->sh_size;
      type = shdr->sh_type;
      align = shdr->sh_addralign;
    }
  else
    {
      Elf64_Shdr *shdr
	= scn->shdr.e64 ?: __elf64_getshdr_wrlock (scn);

      if (shdr == NULL)
	
	return 1;

      offset = shdr->sh_offset;
      size = shdr->sh_size;
      type = shdr->sh_type;
      align = shdr->sh_addralign;
    }

  if (size != 0 && type != SHT_NOBITS)
    {
      
      size_t entsize;

      if (type == SHT_HASH)
	{
	  GElf_Ehdr ehdr_mem;
	  GElf_Ehdr *ehdr = __gelf_getehdr_rdlock (elf, &ehdr_mem);
	  entsize = SH_ENTSIZE_HASH (ehdr);
	}
      else
	{
	  Elf_Type t = shtype_map[LIBELF_EV_IDX][TYPEIDX (type)];
	  if (t == ELF_T_VDEF || t == ELF_T_NHDR
	      || (t == ELF_T_GNUHASH && elf->class == ELFCLASS64))
	    entsize = 1;
	  else
	    entsize = __libelf_type_sizes[LIBELF_EV_IDX][elf->class - 1][t];
	}

      if (entsize == 0)
	entsize = 1;

      if (unlikely (size % entsize != 0))
	{
	  __libelf_seterrno (ELF_E_INVALID_DATA);
	  return 1;
	}

      
      if (elf->map_address != NULL)
	{
	  if (unlikely (offset + size > elf->maximum_size))
	    {
	      
	      __libelf_seterrno (ELF_E_INVALID_SECTION_HEADER);
	      return 1;
	    }

	  scn->rawdata_base = scn->rawdata.d.d_buf
	    = (char *) elf->map_address + elf->start_offset + offset;
	}
      else if (likely (elf->fildes != -1))
	{
	  scn->rawdata_base = scn->rawdata.d.d_buf
	    = (char *) malloc (size);
	  if (scn->rawdata.d.d_buf == NULL)
	    {
	      __libelf_seterrno (ELF_E_NOMEM);
	      return 1;
	    }

	  ssize_t n = pread_retry (elf->fildes, scn->rawdata.d.d_buf, size,
				   elf->start_offset + offset);
	  if (unlikely ((size_t) n != size))
	    {
	      
	      free (scn->rawdata.d.d_buf);
	      scn->rawdata_base = scn->rawdata.d.d_buf = NULL;
	      __libelf_seterrno (ELF_E_READ_ERROR);
	      return 1;
	    }
	}
      else
	{
	  __libelf_seterrno (ELF_E_FD_DISABLED);
	  return 1;
	}
    }

  scn->rawdata.d.d_size = size;
  if (type == SHT_HASH && elf->class == ELFCLASS64)
    {
      GElf_Ehdr ehdr_mem;
      GElf_Ehdr *ehdr = __gelf_getehdr_rdlock (elf, &ehdr_mem);
      scn->rawdata.d.d_type
	= (SH_ENTSIZE_HASH (ehdr) == 4 ? ELF_T_WORD : ELF_T_XWORD);
    }
  else
    scn->rawdata.d.d_type = shtype_map[LIBELF_EV_IDX][TYPEIDX (type)];
  scn->rawdata.d.d_off = 0;
  scn->rawdata.d.d_align = align;
  if (elf->class == ELFCLASS32
      || (offsetof (struct Elf, state.elf32.ehdr)
	  == offsetof (struct Elf, state.elf64.ehdr)))
    scn->rawdata.d.d_version =
      elf->state.elf32.ehdr->e_ident[EI_VERSION];
  else
    scn->rawdata.d.d_version =
      elf->state.elf64.ehdr->e_ident[EI_VERSION];

  scn->rawdata.s = scn;

  scn->data_read = 1;

  
  scn->flags |= ELF_F_FILEDATA;

  return 0;
}

int
internal_function
__libelf_set_rawdata (Elf_Scn *scn)
{
  int result;

  if (scn == NULL)
    return 1;

  rwlock_wrlock (scn->elf->lock);
  result = __libelf_set_rawdata_wrlock (scn);
  rwlock_unlock (scn->elf->lock);

  return result;
}

Elf_Data *
internal_function
__elf_getdata_rdlock (scn, data)
     Elf_Scn *scn;
     Elf_Data *data;
{
  Elf_Data *result = NULL;
  Elf *elf;
  int locked = 0;

  if (scn == NULL)
    return NULL;

  if (unlikely (scn->elf->kind != ELF_K_ELF))
    {
      __libelf_seterrno (ELF_E_INVALID_HANDLE);
      return NULL;
    }

  
  elf = scn->elf;

  if (data != NULL)
    {
      Elf_Data_List *runp;

      if (scn->data_list_rear == NULL
	  || unlikely (((Elf_Data_Scn *) data)->s != scn))
	{
	  __libelf_seterrno (ELF_E_DATA_MISMATCH);
	  goto out;
	}

      
      runp = &scn->data_list;

      while (1)
	{
	  
	  if (runp == NULL)
	    {
	      __libelf_seterrno (ELF_E_DATA_MISMATCH);
	      goto out;
	    }

	  if (&runp->data.d == data)
	    
	    break;

	  runp = runp->next;
	}

      
      result = runp->next ? &runp->next->data.d : NULL;
      goto out;
    }

  
  if (scn->data_read == 0)
    {
      rwlock_unlock (elf->lock);
      rwlock_wrlock (elf->lock);
      locked = 1;

      if (scn->data_read == 0 && __libelf_set_rawdata_wrlock (scn) != 0)
	
	goto out;
    }

  if (scn->data_list_rear == NULL)
    {
      if (scn->rawdata.d.d_buf != NULL && scn->rawdata.d.d_size > 0)
	{
	  if (!locked)
	    {
	      rwlock_unlock (elf->lock);
	      rwlock_wrlock (elf->lock);
	      if (scn->data_list_rear != NULL)
		goto pass;
	    }

	  
	  convert_data (scn, __libelf_version, elf->class,
			(elf->class == ELFCLASS32
			 || (offsetof (struct Elf, state.elf32.ehdr)
			     == offsetof (struct Elf, state.elf64.ehdr))
			 ? elf->state.elf32.ehdr->e_ident[EI_DATA]
			 : elf->state.elf64.ehdr->e_ident[EI_DATA]),
			scn->rawdata.d.d_size, scn->rawdata.d.d_type);
	}
      else
	{
	  scn->data_list.data.d = scn->rawdata.d;
	  scn->data_list.data.s = scn;
	}

      scn->data_list_rear = &scn->data_list;
    }

  
  if (scn->data_list_rear != NULL)
  pass:
    
    result = &scn->data_list.data.d;

 out:
  return result;
}

Elf_Data *
elf_getdata (scn, data)
     Elf_Scn *scn;
     Elf_Data *data;
{
  Elf_Data *result;

  if (scn == NULL)
    return NULL;

  rwlock_rdlock (scn->elf->lock);
  result = __elf_getdata_rdlock (scn, data);
  rwlock_unlock (scn->elf->lock);

  return result;
}
INTDEF(elf_getdata)