/* Get ELF program header table.
   Copyright (C) 1998-2010 Red Hat, Inc.
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
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <system.h>
#include "libelfP.h"
#include "common.h"

#ifndef LIBELFBITS
# define LIBELFBITS 32
#endif

ElfW2(LIBELFBITS,Phdr) *
__elfw2(LIBELFBITS,getphdr_wrlock) (elf)
     Elf *elf;
{
  ElfW2(LIBELFBITS,Phdr) *result;

  result = elf->state.ELFW(elf,LIBELFBITS).phdr;
  if (likely (result != NULL))
    return result;

  if (elf->class == 0)
    elf->class = ELFW(ELFCLASS,LIBELFBITS);
  else if (elf->class != ELFW(ELFCLASS,LIBELFBITS))
    {
      __libelf_seterrno (ELF_E_INVALID_CLASS);
      result = NULL;
      goto out;
    }

  if (likely (result == NULL))
    {
      
      ElfW2(LIBELFBITS,Ehdr) *ehdr = elf->state.ELFW(elf,LIBELFBITS).ehdr;

      
      size_t phnum;
      if (__elf_getphdrnum_rdlock (elf, &phnum) != 0)
	goto out;
      if (phnum == 0)
	{
	  __libelf_seterrno (ELF_E_NO_PHDR);
	  goto out;
	}

      size_t size = phnum * sizeof (ElfW2(LIBELFBITS,Phdr));

      if (ehdr->e_phoff > elf->maximum_size
	  || elf->maximum_size - ehdr->e_phoff < size)
	{
	  __libelf_seterrno (ELF_E_INVALID_DATA);
	  goto out;
	}

      if (elf->map_address != NULL)
	{
	  
	  void *file_phdr = ((char *) elf->map_address
			     + elf->start_offset + ehdr->e_phoff);
	  if (ehdr->e_ident[EI_DATA] == MY_ELFDATA
	      && (ALLOW_UNALIGNED
		  || ((uintptr_t) file_phdr
		      & (__alignof__ (ElfW2(LIBELFBITS,Phdr)) - 1)) == 0))
	    
	    elf->state.ELFW(elf,LIBELFBITS).phdr = file_phdr;
	  else
	    {
	      ElfW2(LIBELFBITS,Phdr) *notcvt;
	      ElfW2(LIBELFBITS,Phdr) *phdr;

	      phdr = elf->state.ELFW(elf,LIBELFBITS).phdr =
		(ElfW2(LIBELFBITS,Phdr) *) malloc (size);
	      if (elf->state.ELFW(elf,LIBELFBITS).phdr == NULL)
		{
		  __libelf_seterrno (ELF_E_NOMEM);
		  goto out;
		}
	      elf->state.ELFW(elf,LIBELFBITS).phdr_flags |=
		ELF_F_MALLOCED | ELF_F_DIRTY;


	      if (ehdr->e_ident[EI_DATA] == MY_ELFDATA)
		{
		  assert (! ALLOW_UNALIGNED);
		  memcpy (phdr, file_phdr, size);
		}
	      else
		{
		  if (ALLOW_UNALIGNED
		      || ((uintptr_t) file_phdr
			  & (__alignof__ (ElfW2(LIBELFBITS,Phdr)) - 1)) == 0)
		    notcvt = file_phdr;
		  else
		    {
		      notcvt = (ElfW2(LIBELFBITS,Phdr) *) alloca (size);
		      memcpy (notcvt, file_phdr, size);
		    }

		  for (size_t cnt = 0; cnt < phnum; ++cnt)
		    {
		      CONVERT_TO (phdr[cnt].p_type, notcvt[cnt].p_type);
		      CONVERT_TO (phdr[cnt].p_offset, notcvt[cnt].p_offset);
		      CONVERT_TO (phdr[cnt].p_vaddr, notcvt[cnt].p_vaddr);
		      CONVERT_TO (phdr[cnt].p_paddr, notcvt[cnt].p_paddr);
		      CONVERT_TO (phdr[cnt].p_filesz, notcvt[cnt].p_filesz);
		      CONVERT_TO (phdr[cnt].p_memsz, notcvt[cnt].p_memsz);
		      CONVERT_TO (phdr[cnt].p_flags, notcvt[cnt].p_flags);
		      CONVERT_TO (phdr[cnt].p_align, notcvt[cnt].p_align);
		    }
		}
	    }
	}
      else if (likely (elf->fildes != -1))
	{
	  elf->state.ELFW(elf,LIBELFBITS).phdr =
	    (ElfW2(LIBELFBITS,Phdr) *) malloc (size);
	  if (elf->state.ELFW(elf,LIBELFBITS).phdr == NULL)
	    {
	      __libelf_seterrno (ELF_E_NOMEM);
	      goto out;
	    }
	  elf->state.ELFW(elf,LIBELFBITS).phdr_flags |= ELF_F_MALLOCED;

	  
	  ssize_t n = pread_retry (elf->fildes,
				   elf->state.ELFW(elf,LIBELFBITS).phdr, size,
				   elf->start_offset + ehdr->e_phoff);
	  if (unlikely ((size_t) n != size))
	    {
	      
	      __libelf_seterrno (ELF_E_READ_ERROR);
	      free (elf->state.ELFW(elf,LIBELFBITS).phdr);
	      elf->state.ELFW(elf,LIBELFBITS).phdr = NULL;
	      goto out;
	    }

	  if (ehdr->e_ident[EI_DATA] != MY_ELFDATA)
	    {
	      ElfW2(LIBELFBITS,Phdr) *phdr
		= elf->state.ELFW(elf,LIBELFBITS).phdr;

	      for (size_t cnt = 0; cnt < phnum; ++cnt)
		{
		  CONVERT (phdr[cnt].p_type);
		  CONVERT (phdr[cnt].p_offset);
		  CONVERT (phdr[cnt].p_vaddr);
		  CONVERT (phdr[cnt].p_paddr);
		  CONVERT (phdr[cnt].p_filesz);
		  CONVERT (phdr[cnt].p_memsz);
		  CONVERT (phdr[cnt].p_flags);
		  CONVERT (phdr[cnt].p_align);
		}
	    }
	}
      else
	{
	  __libelf_seterrno (ELF_E_FD_DISABLED);
	  goto out;
	}

      result = elf->state.ELFW(elf,LIBELFBITS).phdr;
    }

 out:
  return result;
}

ElfW2(LIBELFBITS,Phdr) *
elfw2(LIBELFBITS,getphdr) (elf)
     Elf *elf;
{
  ElfW2(LIBELFBITS,Phdr) *result;

  if (elf == NULL)
    return NULL;

  if (unlikely (elf->kind != ELF_K_ELF))
    {
      __libelf_seterrno (ELF_E_INVALID_HANDLE);
      return NULL;
    }

  result = elf->state.ELFW(elf,LIBELFBITS).phdr;
  if (likely (result != NULL))
    return result;

  rwlock_wrlock (elf->lock);
  result = __elfw2(LIBELFBITS,getphdr_wrlock) (elf);
  rwlock_unlock (elf->lock);

  return result;
}
INTDEF(elfw2(LIBELFBITS,getphdr))
