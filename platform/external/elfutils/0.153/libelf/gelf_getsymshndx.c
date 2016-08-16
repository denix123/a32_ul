/* Get symbol information and separate section index from symbol table
   at the given index.
   Copyright (C) 2000, 2001, 2002 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2000.

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

#include <assert.h>
#include <gelf.h>
#include <string.h>

#include "libelfP.h"


GElf_Sym *
gelf_getsymshndx (symdata, shndxdata, ndx, dst, dstshndx)
     Elf_Data *symdata;
     Elf_Data *shndxdata;
     int ndx;
     GElf_Sym *dst;
     Elf32_Word *dstshndx;
{
  Elf_Data_Scn *symdata_scn = (Elf_Data_Scn *) symdata;
  Elf_Data_Scn *shndxdata_scn = (Elf_Data_Scn *) shndxdata;
  GElf_Sym *result = NULL;
  Elf32_Word shndx = 0;

  if (symdata == NULL)
    return NULL;

  if (unlikely (symdata->d_type != ELF_T_SYM)
      || (likely (shndxdata_scn != NULL)
	  && unlikely (shndxdata->d_type != ELF_T_WORD)))
    {
      __libelf_seterrno (ELF_E_INVALID_HANDLE);
      return NULL;
    }

  rwlock_rdlock (symdata_scn->s->elf->lock);

  if (likely (shndxdata_scn != NULL))
    {
      if (unlikely ((ndx + 1) * sizeof (Elf32_Word) > shndxdata_scn->d.d_size))
	{
	  __libelf_seterrno (ELF_E_INVALID_INDEX);
	  goto out;
	}

      shndx = ((Elf32_Word *) shndxdata_scn->d.d_buf)[ndx];
    }

  if (symdata_scn->s->elf->class == ELFCLASS32)
    {
      Elf32_Sym *src;

      if (unlikely ((ndx + 1) * sizeof (Elf32_Sym) > symdata->d_size))
	{
	  __libelf_seterrno (ELF_E_INVALID_INDEX);
	  goto out;
	}

      src = &((Elf32_Sym *) symdata->d_buf)[ndx];

#define COPY(name) \
      dst->name = src->name
      COPY (st_name);
      COPY (st_info);
      COPY (st_other);
      COPY (st_shndx);
      COPY (st_value);
      COPY (st_size);
    }
  else
    {
      
      assert (sizeof (GElf_Sym) == sizeof (Elf64_Sym));

      if (unlikely ((ndx + 1) * sizeof (GElf_Sym) > symdata->d_size))
	{
	  __libelf_seterrno (ELF_E_INVALID_INDEX);
	  goto out;
	}

      *dst = ((GElf_Sym *) symdata->d_buf)[ndx];
    }

  
  if (dstshndx != NULL)
    *dstshndx = shndx;

  result = dst;

 out:
  rwlock_unlock (symdata_scn->s->elf->lock);

  return result;
}