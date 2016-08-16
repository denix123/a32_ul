/* Advance to next CU header.
   Copyright (C) 2002-2010 Red Hat, Inc.
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

#include <libdwP.h>
#include <dwarf.h>


int
dwarf_next_unit (dwarf, off, next_off, header_sizep, versionp, abbrev_offsetp,
		 address_sizep, offset_sizep, type_signaturep, type_offsetp)
     Dwarf *dwarf;
     Dwarf_Off off;
     Dwarf_Off *next_off;
     size_t *header_sizep;
     Dwarf_Half *versionp;
     Dwarf_Off *abbrev_offsetp;
     uint8_t *address_sizep;
     uint8_t *offset_sizep;
     uint64_t *type_signaturep;
     Dwarf_Off *type_offsetp;
{
  const bool debug_types = type_signaturep != NULL;
  const size_t sec_idx = debug_types ? IDX_debug_types : IDX_debug_info;

  
  if (dwarf == NULL)
    return -1;

  
  if (off == (Dwarf_Off) -1l
      || unlikely (dwarf->sectiondata[sec_idx] == NULL)
      || unlikely (off + 4 >= dwarf->sectiondata[sec_idx]->d_size))
    {
      *next_off = (Dwarf_Off) -1l;
      return 1;
    }

  const unsigned char *data = dwarf->sectiondata[sec_idx]->d_buf;
  const unsigned char *bytes = data + off;

  uint64_t length = read_4ubyte_unaligned_inc (dwarf, bytes);
  size_t offset_size = 4;
  if (length == DWARF3_LENGTH_64_BIT)
    offset_size = 8;
  else if (unlikely (length >= DWARF3_LENGTH_MIN_ESCAPE_CODE
		     && length <= DWARF3_LENGTH_MAX_ESCAPE_CODE))
    {
    invalid:
      __libdw_seterrno (DWARF_E_INVALID_DWARF);
      return -1;
    }

  
  if (unlikely (DIE_OFFSET_FROM_CU_OFFSET (off, offset_size, debug_types)
		>= dwarf->sectiondata[sec_idx]->d_size))
    {
      *next_off = -1;
      return 1;
    }

  if (length == DWARF3_LENGTH_64_BIT)
    
    length = read_8ubyte_unaligned_inc (dwarf, bytes);

  
  uint_fast16_t version = read_2ubyte_unaligned_inc (dwarf, bytes);

  uint64_t abbrev_offset;
  if (__libdw_read_offset_inc (dwarf, sec_idx, &bytes, offset_size,
			       &abbrev_offset, IDX_debug_abbrev, 0))
    return -1;

  
  uint8_t address_size = *bytes++;

  if (debug_types)
    {
      uint64_t type_sig8 = read_8ubyte_unaligned_inc (dwarf, bytes);

      Dwarf_Off type_offset;
      if (__libdw_read_offset_inc (dwarf, sec_idx, &bytes, offset_size,
				   &type_offset, sec_idx, 0))
	return -1;

      
      if (unlikely (type_offset < (size_t) (bytes - (data + off))))
	goto invalid;

      *type_signaturep = type_sig8;
      if (type_offsetp != NULL)
	*type_offsetp = type_offset;
    }

  
  if (header_sizep != NULL)
    *header_sizep = bytes - (data + off);

  if (versionp != NULL)
    *versionp = version;

  if (abbrev_offsetp != NULL)
    *abbrev_offsetp = abbrev_offset;

  if (address_sizep != NULL)
    *address_sizep = address_size;

  
  if (offset_sizep != NULL)
    *offset_sizep = offset_size;

  *next_off = off + 2 * offset_size - 4 + length;

  return 0;
}
INTDEF(dwarf_next_unit)

int
dwarf_nextcu (dwarf, off, next_off, header_sizep, abbrev_offsetp,
	      address_sizep, offset_sizep)
     Dwarf *dwarf;
     Dwarf_Off off;
     Dwarf_Off *next_off;
     size_t *header_sizep;
     Dwarf_Off *abbrev_offsetp;
     uint8_t *address_sizep;
     uint8_t *offset_sizep;
{
  return INTUSE(dwarf_next_unit) (dwarf, off, next_off, header_sizep, NULL,
				  abbrev_offsetp, address_sizep, offset_sizep,
				  NULL, NULL);
}
INTDEF(dwarf_nextcu)
