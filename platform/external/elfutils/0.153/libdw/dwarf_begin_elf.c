/* Create descriptor from ELF descriptor for processing file.
   Copyright (C) 2002-2011 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2002.

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

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "libdwP.h"

#if USE_ZLIB
# include <endian.h>
# define crc32		loser_crc32
# include <zlib.h>
# undef crc32
#endif


static const char dwarf_scnnames[IDX_last][17] =
{
  [IDX_debug_info] = ".debug_info",
  [IDX_debug_types] = ".debug_types",
  [IDX_debug_abbrev] = ".debug_abbrev",
  [IDX_debug_aranges] = ".debug_aranges",
  [IDX_debug_line] = ".debug_line",
  [IDX_debug_frame] = ".debug_frame",
  [IDX_debug_loc] = ".debug_loc",
  [IDX_debug_pubnames] = ".debug_pubnames",
  [IDX_debug_str] = ".debug_str",
  [IDX_debug_macinfo] = ".debug_macinfo",
  [IDX_debug_ranges] = ".debug_ranges"
};
#define ndwarf_scnnames (sizeof (dwarf_scnnames) / sizeof (dwarf_scnnames[0]))


static Dwarf *
check_section (Dwarf *result, GElf_Ehdr *ehdr, Elf_Scn *scn, bool inscngrp)
{
  GElf_Shdr shdr_mem;
  GElf_Shdr *shdr;

  
  shdr = gelf_getshdr (scn, &shdr_mem);
  if (shdr == NULL)
    abort ();

  if (unlikely (shdr->sh_type == SHT_NOBITS))
    return result;

  if (! inscngrp && (shdr->sh_flags & SHF_GROUP) != 0)
    
    return result;


  const char *scnname = elf_strptr (result->elf, ehdr->e_shstrndx,
				    shdr->sh_name);
  if (scnname == NULL)
    {
      __libdw_free_zdata (result);
      __libdw_seterrno (DWARF_E_INVALID_ELF);
      free (result);
      return NULL;
    }


  
  size_t cnt;
  for (cnt = 0; cnt < ndwarf_scnnames; ++cnt)
    if (strcmp (scnname, dwarf_scnnames[cnt]) == 0)
      {
	
	if (unlikely (result->sectiondata[cnt] != NULL))
	  
	  break;

	
	Elf_Data *data = elf_getdata (scn, NULL);
	if (data != NULL && data->d_size != 0)
	  
	  result->sectiondata[cnt] = data;

	break;
      }
#if USE_ZLIB
    else if (scnname[0] == '.' && scnname[1] == 'z'
	     && strcmp (&scnname[2], &dwarf_scnnames[cnt][1]) == 0)
      {
	

	if (unlikely (result->sectiondata[cnt] != NULL))
	  
	  break;

	
	Elf_Data *data = elf_getdata (scn, NULL);
	if (data != NULL && data->d_size != 0)
	  {

	    if (unlikely (data->d_size < 4 + 8)
		|| unlikely (memcmp (data->d_buf, "ZLIB", 4) != 0))
	      break;

	    uint64_t size;
	    memcpy (&size, data->d_buf + 4, sizeof size);
	    size = be64toh (size);

	    Elf_Data *zdata = malloc (sizeof (Elf_Data) + size);
	    if (unlikely (zdata == NULL))
	      break;

	    zdata->d_buf = &zdata[1];
	    zdata->d_type = ELF_T_BYTE;
	    zdata->d_version = EV_CURRENT;
	    zdata->d_size = size;
	    zdata->d_off = 0;
	    zdata->d_align = 1;

	    z_stream z =
	      {
		.next_in = data->d_buf + 4 + 8,
		.avail_in = data->d_size - 4 - 8,
		.next_out = zdata->d_buf,
		.avail_out = zdata->d_size
	      };
	    int zrc = inflateInit (&z);
	    while (z.avail_in > 0 && likely (zrc == Z_OK))
	      {
		z.next_out = zdata->d_buf + (zdata->d_size - z.avail_out);
		zrc = inflate (&z, Z_FINISH);
		if (unlikely (zrc != Z_STREAM_END))
		  {
		    zrc = Z_DATA_ERROR;
		    break;
		  }
		zrc = inflateReset (&z);
	      }
	    if (likely (zrc == Z_OK))
	      zrc = inflateEnd (&z);

	    if (unlikely (zrc != Z_OK) || unlikely (z.avail_out != 0))
	      free (zdata);
	    else
	      {
		result->sectiondata[cnt] = zdata;
		result->sectiondata_gzip_mask |= 1U << cnt;
	      }
	  }

	break;
      }
#endif

  return result;
}


static Dwarf *
valid_p (Dwarf *result)
{
  if (likely (result != NULL)
      && unlikely (result->sectiondata[IDX_debug_info] == NULL))
    {
      __libdw_free_zdata (result);
      __libdw_seterrno (DWARF_E_NO_DWARF);
      free (result);
      result = NULL;
    }

  return result;
}


static Dwarf *
global_read (Dwarf *result, Elf *elf, GElf_Ehdr *ehdr)
{
  Elf_Scn *scn = NULL;

  while (result != NULL && (scn = elf_nextscn (elf, scn)) != NULL)
    result = check_section (result, ehdr, scn, false);

  return valid_p (result);
}


static Dwarf *
scngrp_read (Dwarf *result, Elf *elf, GElf_Ehdr *ehdr, Elf_Scn *scngrp)
{
  Elf_Data *data = elf_getdata (scngrp, NULL);
  if (data == NULL)
    {
      
      __libdw_free_zdata (result);
      free (result);
      return NULL;
    }

  Elf32_Word *scnidx = (Elf32_Word *) data->d_buf;
  size_t cnt;
  for (cnt = 1; cnt * sizeof (Elf32_Word) <= data->d_size; ++cnt)
    {
      Elf_Scn *scn = elf_getscn (elf, scnidx[cnt]);
      if (scn == NULL)
	{
	  __libdw_free_zdata (result);
	  __libdw_seterrno (DWARF_E_INVALID_ELF);
	  free (result);
	  return NULL;
	}

      result = check_section (result, ehdr, scn, true);
      if (result == NULL)
	break;
    }

  return valid_p (result);
}


Dwarf *
dwarf_begin_elf (elf, cmd, scngrp)
     Elf *elf;
     Dwarf_Cmd cmd;
     Elf_Scn *scngrp;
{
  GElf_Ehdr *ehdr;
  GElf_Ehdr ehdr_mem;

  ehdr = gelf_getehdr (elf, &ehdr_mem);
  if (ehdr == NULL)
    {
      if (elf_kind (elf) != ELF_K_ELF)
	__libdw_seterrno (DWARF_E_NOELF);
      else
	__libdw_seterrno (DWARF_E_GETEHDR_ERROR);

      return NULL;
    }


  
  size_t mem_default_size = sysconf (_SC_PAGESIZE) - 4 * sizeof (void *);

  
  Dwarf *result = (Dwarf *) calloc (1, sizeof (Dwarf) + mem_default_size);
  if (unlikely (result == NULL)
      || unlikely (Dwarf_Sig8_Hash_init (&result->sig8_hash, 11) < 0))
    {
      free (result);
      __libdw_seterrno (DWARF_E_NOMEM);
      return NULL;
    }

  
  if ((BYTE_ORDER == LITTLE_ENDIAN && ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
      || (BYTE_ORDER == BIG_ENDIAN && ehdr->e_ident[EI_DATA] == ELFDATA2LSB))
    result->other_byte_order = true;

  result->elf = elf;

  
  result->mem_default_size = mem_default_size;
  result->oom_handler = __libdw_oom;
  result->mem_tail = (struct libdw_memblock *) (result + 1);
  result->mem_tail->size = (result->mem_default_size
			    - offsetof (struct libdw_memblock, mem));
  result->mem_tail->remaining = result->mem_tail->size;
  result->mem_tail->prev = NULL;

  if (cmd == DWARF_C_READ || cmd == DWARF_C_RDWR)
    {
      if (scngrp == NULL)
	return global_read (result, elf, ehdr);
      else
	return scngrp_read (result, elf, ehdr, scngrp);
    }
  else if (cmd == DWARF_C_WRITE)
    {
      __libdw_seterrno (DWARF_E_UNIMPL);
      free (result);
      return NULL;
    }

  __libdw_seterrno (DWARF_E_INVALID_CMD);
  free (result);
  return NULL;
}
INTDEF(dwarf_begin_elf)
