/* Core file handling.
   Copyright (C) 2008-2010 Red Hat, Inc.
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

#include <config.h>
#include "../libelf/libelfP.h"	
#undef	_
#include "libdwflP.h"
#include <gelf.h>

#include <sys/param.h>
#include <unistd.h>
#include <endian.h>
#include <byteswap.h>
#include "system.h"


static Elf *
elf_begin_rand (Elf *parent, loff_t offset, loff_t size, loff_t *next)
{
  if (parent == NULL)
    return NULL;

  
  inline Elf *fail (int error)
  {
    if (next != NULL)
      *next = offset;
    
    __libdwfl_seterrno (DWFL_E (LIBELF, error));
    return NULL;
  }

  loff_t min = (parent->kind == ELF_K_ELF ?
		(parent->class == ELFCLASS32
		 ? sizeof (Elf32_Ehdr) : sizeof (Elf64_Ehdr))
		: parent->kind == ELF_K_AR ? SARMAG
		: 0);

  if (unlikely (offset < min)
      || unlikely (offset >= (loff_t) parent->maximum_size))
    return fail (ELF_E_RANGE);

  if (parent->kind == ELF_K_AR)
    {
      struct ar_hdr h = { .ar_size = "" };

      if (unlikely (parent->maximum_size - offset < sizeof h))
	return fail (ELF_E_RANGE);

      if (parent->map_address != NULL)
	memcpy (h.ar_size, parent->map_address + parent->start_offset + offset,
		sizeof h.ar_size);
      else if (unlikely (pread_retry (parent->fildes,
				      h.ar_size, sizeof (h.ar_size),
				      parent->start_offset + offset
				      + offsetof (struct ar_hdr, ar_size))
			 != sizeof (h.ar_size)))
	return fail (ELF_E_READ_ERROR);

      offset += sizeof h;

      char *endp;
      size = strtoll (h.ar_size, &endp, 10);
      if (unlikely (endp == h.ar_size)
	  || unlikely ((loff_t) parent->maximum_size - offset < size))
	return fail (ELF_E_INVALID_ARCHIVE);
    }

  if (unlikely ((loff_t) parent->maximum_size - offset < size))
    return fail (ELF_E_RANGE);

  
  if (next != NULL)
    *next = offset + size;

  if (unlikely (offset == 0)
      && unlikely (size == (loff_t) parent->maximum_size))
    return elf_clone (parent, parent->cmd);

  Elf_Data *data = elf_getdata_rawchunk (parent, offset, size, ELF_T_BYTE);
  if (data == NULL)
    return NULL;
  assert ((loff_t) data->d_size == size);
  return elf_memory (data->d_buf, size);
}


int
dwfl_report_core_segments (Dwfl *dwfl, Elf *elf, size_t phnum, GElf_Phdr *notes)
{
  if (unlikely (dwfl == NULL))
    return -1;

  int result = 0;

  if (notes != NULL)
    notes->p_type = PT_NULL;

  for (size_t ndx = 0; result >= 0 && ndx < phnum; ++ndx)
    {
      GElf_Phdr phdr_mem;
      GElf_Phdr *phdr = gelf_getphdr (elf, ndx, &phdr_mem);
      if (unlikely (phdr == NULL))
	{
	  __libdwfl_seterrno (DWFL_E_LIBELF);
	  return -1;
	}
      switch (phdr->p_type)
	{
	case PT_LOAD:
	  result = dwfl_report_segment (dwfl, ndx, phdr, 0, NULL);
	  break;

	case PT_NOTE:
	  if (notes != NULL)
	    {
	      *notes = *phdr;
	      notes = NULL;
	    }
	  break;
	}
    }

  return result;
}

#define MAX_EAGER_COST	8192

static bool
core_file_read_eagerly (Dwfl_Module *mod,
			void **userdata __attribute__ ((unused)),
			const char *name __attribute__ ((unused)),
			Dwarf_Addr start __attribute__ ((unused)),
			void **buffer, size_t *buffer_available,
			GElf_Off cost, GElf_Off worthwhile,
			GElf_Off whole,
			GElf_Off contiguous __attribute__ ((unused)),
			void *arg, Elf **elfp)
{
  Elf *core = arg;

  if (whole <= *buffer_available)
    {
      

      if (core->map_address == NULL)
	{
	  
	  *elfp = elf_memory (*buffer, whole);
	  if (unlikely (*elfp == NULL))
	    return false;

	  (*elfp)->flags |= ELF_F_MALLOCED;
	  *buffer = NULL;
	  *buffer_available = 0;
	  return true;
	}

      
      *elfp = elf_begin_rand (core, *buffer - core->map_address, whole, NULL);
      *buffer = NULL;
      *buffer_available = 0;
      return *elfp != NULL;
    }


  if (worthwhile == 0)
    
    return false;


  if (mod->build_id_len > 0)
    return false;

  if (core->map_address != NULL)
    
    return true;

  
  return cost <= MAX_EAGER_COST;
}

bool
dwfl_elf_phdr_memory_callback (Dwfl *dwfl, int ndx,
			       void **buffer, size_t *buffer_available,
			       GElf_Addr vaddr,
			       size_t minread,
			       void *arg)
{
  Elf *elf = arg;

  if (ndx == -1)
    {
      
      if (elf->map_address == NULL)
	free (*buffer);
      *buffer = NULL;
      *buffer_available = 0;
      return false;
    }

  const GElf_Off align = dwfl->segment_align ?: 1;
  GElf_Phdr phdr;

  do
    if (unlikely (gelf_getphdr (elf, ndx++, &phdr) == NULL))
      return false;
  while (phdr.p_type != PT_LOAD
	 || ((phdr.p_vaddr + phdr.p_memsz + align - 1) & -align) <= vaddr);

  GElf_Off start = vaddr - phdr.p_vaddr + phdr.p_offset;
  GElf_Off end;
  GElf_Addr end_vaddr;

  inline void update_end ()
  {
    end = (phdr.p_offset + phdr.p_filesz + align - 1) & -align;
    end_vaddr = (phdr.p_vaddr + phdr.p_memsz + align - 1) & -align;
  }

  update_end ();

  
  inline bool more (size_t size)
  {
    while (end <= start || end - start < size)
      {
	if (phdr.p_filesz < phdr.p_memsz)
	  
	  return false;

	if (unlikely (gelf_getphdr (elf, ndx++, &phdr) == NULL))
	  return false;

	if (phdr.p_type == PT_LOAD)
	  {
	    if (phdr.p_offset > end
		|| phdr.p_vaddr > end_vaddr)
	      
	      return false;

	    update_end ();
	  }
      }
    return true;
  }

  
  if (! more (minread))
    return false;

  
  (void) more (*buffer_available);

  
  if (elf->map_address != NULL)
    (void) more (elf->maximum_size - start);

  if (unlikely (end > elf->maximum_size))
    end = elf->maximum_size;

  
  if (unlikely (start >= end))
    return false;

  if (elf->map_address != NULL)
    {
      void *contents = elf->map_address + elf->start_offset + start;
      size_t size = end - start;

      if (minread == 0)		
	{
	  const void *eos = memchr (contents, '\0', size);
	  if (unlikely (eos == NULL) || unlikely (eos == contents))
	    return false;
	  size = eos + 1 - contents;
	}

      if (*buffer == NULL)
	{
	  *buffer = contents;
	  *buffer_available = size;
	}
      else
	{
	  *buffer_available = MIN (size, *buffer_available);
	  memcpy (*buffer, contents, *buffer_available);
	}
    }
  else
    {
      void *into = *buffer;
      if (*buffer == NULL)
	{
	  *buffer_available = MIN (minread ?: 512,
				   MAX (4096, MIN (end - start,
						   *buffer_available)));
	  into = malloc (*buffer_available);
	  if (unlikely (into == NULL))
	    {
	      __libdwfl_seterrno (DWFL_E_NOMEM);
	      return false;
	    }
	}

      ssize_t nread = pread_retry (elf->fildes, into, *buffer_available, start);
      if (nread < (ssize_t) minread)
	{
	  if (into != *buffer)
	    free (into);
	  if (nread < 0)
	    __libdwfl_seterrno (DWFL_E_ERRNO);
	  return false;
	}

      if (minread == 0)		
	{
	  const void *eos = memchr (into, '\0', nread);
	  if (unlikely (eos == NULL) || unlikely (eos == into))
	    {
	      if (*buffer == NULL)
		free (into);
	      return false;
	    }
	  nread = eos + 1 - into;
	}

      if (*buffer == NULL)
	*buffer = into;
      *buffer_available = nread;
    }

  return true;
}

int
dwfl_core_file_report (Dwfl *dwfl, Elf *elf)
{
  size_t phnum;
  if (unlikely (elf_getphdrnum (elf, &phnum) != 0))
    {
      __libdwfl_seterrno (DWFL_E_LIBELF);
      return -1;
    }

  
  GElf_Phdr notes_phdr;
  int ndx = dwfl_report_core_segments (dwfl, elf, phnum, &notes_phdr);
  if (unlikely (ndx <= 0))
    return ndx;

  
  int sniffed = 0;
  ndx = 0;
  do
    {
      int seg = dwfl_segment_report_module (dwfl, ndx, NULL,
					    &dwfl_elf_phdr_memory_callback, elf,
					    core_file_read_eagerly, elf);
      if (unlikely (seg < 0))
	return seg;
      if (seg > ndx)
	{
	  ndx = seg;
	  ++sniffed;
	}
      else
	++ndx;
    }
  while (ndx < (int) phnum);

  

  const void *auxv = NULL;
  size_t auxv_size = 0;
  if (likely (notes_phdr.p_type == PT_NOTE))
    {
      

      Elf_Data *notes = elf_getdata_rawchunk (elf,
					      notes_phdr.p_offset,
					      notes_phdr.p_filesz,
					      ELF_T_NHDR);
      if (likely (notes != NULL))
	{
	  size_t pos = 0;
	  GElf_Nhdr nhdr;
	  size_t name_pos;
	  size_t desc_pos;
	  while ((pos = gelf_getnote (notes, pos, &nhdr,
				      &name_pos, &desc_pos)) > 0)
	    if (nhdr.n_type == NT_AUXV
		&& nhdr.n_namesz == sizeof "CORE"
		&& !memcmp (notes->d_buf + name_pos, "CORE", sizeof "CORE"))
	      {
		auxv = notes->d_buf + desc_pos;
		auxv_size = nhdr.n_descsz;
		break;
	      }
	}
    }


  int listed = dwfl_link_map_report (dwfl, auxv, auxv_size,
				     dwfl_elf_phdr_memory_callback, elf);

  return sniffed == 0 || listed > sniffed ? listed : sniffed;
}
INTDEF (dwfl_core_file_report)
