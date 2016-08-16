/* Function return value location for Linux/PPC64 ABI.
   Copyright (C) 2005-2010 Red Hat, Inc.
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <assert.h>
#include <dwarf.h>

#define BACKEND ppc64_
#include "libebl_CPU.h"


static const Dwarf_Op loc_intreg[] =
  {
    { .atom = DW_OP_reg3 }
  };
#define nloc_intreg	1

static const Dwarf_Op loc_fpreg[] =
  {
    { .atom = DW_OP_regx, .number = 33 }, { .atom = DW_OP_piece, .number = 8 },
    { .atom = DW_OP_regx, .number = 34 }, { .atom = DW_OP_piece, .number = 8 },
    { .atom = DW_OP_regx, .number = 35 }, { .atom = DW_OP_piece, .number = 8 },
    { .atom = DW_OP_regx, .number = 36 }, { .atom = DW_OP_piece, .number = 8 },
  };
#define nloc_fpreg	1
#define nloc_fp2regs	4
#define nloc_fp4regs	8

static const Dwarf_Op loc_vmxreg[] =
  {
    { .atom = DW_OP_regx, .number = 1124 + 2 }
  };
#define nloc_vmxreg	1

static const Dwarf_Op loc_aggregate[] =
  {
    { .atom = DW_OP_breg3, .number = 0 }
  };
#define nloc_aggregate 1

int
ppc64_return_value_location (Dwarf_Die *functypedie, const Dwarf_Op **locp)
{

  Dwarf_Attribute attr_mem;
  Dwarf_Attribute *attr = dwarf_attr_integrate (functypedie, DW_AT_type,
						&attr_mem);
  if (attr == NULL)
    
    return 0;

  Dwarf_Die die_mem;
  Dwarf_Die *typedie = dwarf_formref_die (attr, &die_mem);
  int tag = dwarf_tag (typedie);

  
  while (tag == DW_TAG_typedef
	 || tag == DW_TAG_const_type || tag == DW_TAG_volatile_type
	 || tag == DW_TAG_restrict_type || tag == DW_TAG_mutable_type)
    {
      attr = dwarf_attr_integrate (typedie, DW_AT_type, &attr_mem);
      typedie = dwarf_formref_die (attr, &die_mem);
      tag = dwarf_tag (typedie);
    }

  Dwarf_Word size;
  switch (tag)
    {
    case -1:
      return -1;

    case DW_TAG_subrange_type:
      if (! dwarf_hasattr_integrate (typedie, DW_AT_byte_size))
	{
	  attr = dwarf_attr_integrate (typedie, DW_AT_type, &attr_mem);
	  typedie = dwarf_formref_die (attr, &die_mem);
	  tag = dwarf_tag (typedie);
	}
      

    case DW_TAG_base_type:
    case DW_TAG_enumeration_type:
    case DW_TAG_pointer_type:
    case DW_TAG_ptr_to_member_type:
      if (dwarf_formudata (dwarf_attr_integrate (typedie, DW_AT_byte_size,
						 &attr_mem), &size) != 0)
	{
	  if (tag == DW_TAG_pointer_type || tag == DW_TAG_ptr_to_member_type)
	    size = 8;
	  else
	    return -1;
	}
      if (tag == DW_TAG_base_type)
	{
	  Dwarf_Word encoding;
	  if (dwarf_formudata (dwarf_attr_integrate (typedie, DW_AT_encoding,
						     &attr_mem),
			       &encoding) != 0)
	    return -1;

	  if (encoding == DW_ATE_float || encoding == DW_ATE_complex_float)
	    {
	      *locp = loc_fpreg;
	      if (size <= 8)
		return nloc_fpreg;
	      if (size <= 16)
		return nloc_fp2regs;
	      if (size <= 32)
		return nloc_fp4regs;
	    }
	}
      if (size <= 8)
	{
	intreg:
	  *locp = loc_intreg;
	  return nloc_intreg;
	}

      
    case DW_TAG_structure_type:
    case DW_TAG_class_type:
    case DW_TAG_union_type:
    aggregate:
      *locp = loc_aggregate;
      return nloc_aggregate;

    case DW_TAG_array_type:
      {
	bool is_vector;
	if (dwarf_formflag (dwarf_attr_integrate (typedie, DW_AT_GNU_vector,
						  &attr_mem), &is_vector) == 0
	    && is_vector)
	  {
	    *locp = loc_vmxreg;
	    return nloc_vmxreg;
	  }
      }
      

    case DW_TAG_string_type:
      if (dwarf_aggregate_size (typedie, &size) == 0 && size <= 8)
	{
	  if (tag == DW_TAG_array_type)
	    {
	      
	      attr = dwarf_attr_integrate (typedie, DW_AT_type, &attr_mem);
	      typedie = dwarf_formref_die (attr, &die_mem);
	      tag = dwarf_tag (typedie);
	      if (tag != DW_TAG_base_type)
		goto aggregate;
	      if (dwarf_formudata (dwarf_attr_integrate (typedie,
							 DW_AT_byte_size,
							 &attr_mem),
				   &size) != 0)
		return -1;
	      if (size != 1)
		goto aggregate;
	    }
	  goto intreg;
	}
      goto aggregate;
    }

  return -2;
}