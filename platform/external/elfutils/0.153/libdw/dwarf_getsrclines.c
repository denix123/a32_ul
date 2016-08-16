/* Return line number information of CU.
   Copyright (C) 2004-2010 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2004.

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
#include <stdlib.h>
#include <string.h>
#include "dwarf.h"
#include "libdwP.h"


struct filelist
{
  Dwarf_Fileinfo info;
  struct filelist *next;
};

struct linelist
{
  Dwarf_Line line;
  struct linelist *next;
};


static int
compare_lines (const void *a, const void *b)
{
  Dwarf_Line *const *p1 = a;
  Dwarf_Line *const *p2 = b;

  if ((*p1)->addr == (*p2)->addr)
    
    return (*p2)->end_sequence - (*p1)->end_sequence;

  return (*p1)->addr - (*p2)->addr;
}

int
dwarf_getsrclines (Dwarf_Die *cudie, Dwarf_Lines **lines, size_t *nlines)
{
  if (unlikely (cudie == NULL
		|| INTUSE(dwarf_tag) (cudie) != DW_TAG_compile_unit))
    return -1;

  int res = -1;

  
  struct Dwarf_CU *const cu = cudie->cu;
  if (cu->lines == NULL)
    {
      
      cu->lines = (void *) -1l;
      cu->files = (void *) -1l;

      
      Dwarf_Attribute stmt_list_mem;
      Dwarf_Attribute *stmt_list = INTUSE(dwarf_attr) (cudie, DW_AT_stmt_list,
						       &stmt_list_mem);

      const unsigned char *lineendp;
      const unsigned char *linep
	= __libdw_formptr (stmt_list, IDX_debug_line, DWARF_E_NO_DEBUG_LINE,
			   (unsigned char **) &lineendp, NULL);
      if (linep == NULL)
	goto out;

      
      Dwarf_Attribute compdir_attr_mem;
      Dwarf_Attribute *compdir_attr = INTUSE(dwarf_attr) (cudie,
							  DW_AT_comp_dir,
							  &compdir_attr_mem);
      const char *comp_dir = INTUSE(dwarf_formstring) (compdir_attr);

      if (unlikely (linep + 4 > lineendp))
	{
	invalid_data:
	  __libdw_seterrno (DWARF_E_INVALID_DEBUG_LINE);
	  goto out;
	}

      Dwarf *dbg = cu->dbg;
      Dwarf_Word unit_length = read_4ubyte_unaligned_inc (dbg, linep);
      unsigned int length = 4;
      if (unlikely (unit_length == DWARF3_LENGTH_64_BIT))
	{
	  if (unlikely (linep + 8 > lineendp))
	    goto invalid_data;
	  unit_length = read_8ubyte_unaligned_inc (dbg, linep);
	  length = 8;
	}

      
      if (unit_length < 2 + length + 5 * 1
	  || unlikely (linep + unit_length > lineendp))
	goto invalid_data;
      lineendp = linep + unit_length;

      
      uint_fast16_t version = read_2ubyte_unaligned_inc (dbg, linep);
      if (unlikely (version < 2) || unlikely (version > 4))
	{
	  __libdw_seterrno (DWARF_E_VERSION);
	  goto out;
	}

      
      Dwarf_Word header_length;
      if (length == 4)
	header_length = read_4ubyte_unaligned_inc (dbg, linep);
      else
	header_length = read_8ubyte_unaligned_inc (dbg, linep);
      const unsigned char *header_start = linep;

      
      uint_fast8_t minimum_instr_len = *linep++;

      
      uint_fast8_t max_ops_per_instr = 1;
      if (version >= 4)
	{
	  if (unlikely (lineendp - linep < 5))
	    goto invalid_data;
	  max_ops_per_instr = *linep++;
	  if (unlikely (max_ops_per_instr == 0))
	    goto invalid_data;
	}

      uint_fast8_t default_is_stmt = *linep++;

      
      int_fast8_t line_base = (int8_t) *linep++;

      
      uint_fast8_t line_range = *linep++;

      
      uint_fast8_t opcode_base = *linep++;

      const uint8_t *standard_opcode_lengths = linep - 1;
      if (unlikely (lineendp - linep < opcode_base - 1))
	goto invalid_data;
      linep += opcode_base - 1;

      struct dirlist
      {
	const char *dir;
	size_t len;
	struct dirlist *next;
      } comp_dir_elem =
	{
	  .dir = comp_dir,
	  .len = comp_dir ? strlen (comp_dir) : 0,
	  .next = NULL
	};
      struct dirlist *dirlist = &comp_dir_elem;
      unsigned int ndirlist = 1;

      
      while (*linep != 0)
	{
	  struct dirlist *new_dir =
	    (struct dirlist *) alloca (sizeof (*new_dir));

	  new_dir->dir = (char *) linep;
	  uint8_t *endp = memchr (linep, '\0', lineendp - linep);
	  if (endp == NULL)
	    goto invalid_data;
	  new_dir->len = endp - linep;
	  new_dir->next = dirlist;
	  dirlist = new_dir;
	  ++ndirlist;
	  linep = endp + 1;
	}
      
      ++linep;

      
      struct dirlist **dirarray
	= (struct dirlist **) alloca (ndirlist * sizeof (*dirarray));
      for (unsigned int n = ndirlist; n-- > 0; dirlist = dirlist->next)
	dirarray[n] = dirlist;

      
      struct filelist null_file =
	{
	  .info =
	  {
	    .name = "???",
	    .mtime = 0,
	    .length = 0
	  },
	  .next = NULL
	};
      struct filelist *filelist = &null_file;
      unsigned int nfilelist = 1;

      if (unlikely (linep >= lineendp))
	goto invalid_data;
      while (*linep != 0)
	{
	  struct filelist *new_file =
	    (struct filelist *) alloca (sizeof (*new_file));

	  
	  char *fname = (char *) linep;
	  uint8_t *endp = memchr (fname, '\0', lineendp - linep);
	  if (endp == NULL)
	    goto invalid_data;
	  size_t fnamelen = endp - (uint8_t *) fname;
	  linep = endp + 1;

	  
	  Dwarf_Word diridx;
	  get_uleb128 (diridx, linep);
	  if (unlikely (diridx >= ndirlist))
	    {
	      __libdw_seterrno (DWARF_E_INVALID_DIR_IDX);
	      goto out;
	    }

	  if (*fname == '/')
	    
	    new_file->info.name = fname;
	  else
	    {
	      new_file->info.name = libdw_alloc (dbg, char, 1,
						 dirarray[diridx]->len + 1
						 + fnamelen + 1);
              char *cp = new_file->info.name;

              if (dirarray[diridx]->dir != NULL)
		{
		  cp = stpcpy (cp, dirarray[diridx]->dir);
		}
              *cp++ = '/';
              strcpy (cp, fname);
	      assert (strlen (new_file->info.name)
		      < dirarray[diridx]->len + 1 + fnamelen + 1);
            }

	  
	  get_uleb128 (new_file->info.mtime, linep);

	  
	  get_uleb128 (new_file->info.length, linep);

	  new_file->next = filelist;
	  filelist = new_file;
	  ++nfilelist;
	}
      
      ++linep;

      
      if (unlikely (linep != header_start + header_length))
	{
	  __libdw_seterrno (DWARF_E_INVALID_DWARF);
	  goto out;
	}

      Dwarf_Word addr = 0;
      unsigned int op_index = 0;
      unsigned int file = 1;
      int line = 1;
      unsigned int column = 0;
      uint_fast8_t is_stmt = default_is_stmt;
      bool basic_block = false;
      bool prologue_end = false;
      bool epilogue_begin = false;
      unsigned int isa = 0;
      unsigned int discriminator = 0;

      inline void advance_pc (unsigned int op_advance)
      {
	addr += minimum_instr_len * ((op_index + op_advance)
				     / max_ops_per_instr);
	op_index = (op_index + op_advance) % max_ops_per_instr;
      }

      
      struct linelist *linelist = NULL;
      unsigned int nlinelist = 0;

#define NEW_LINE(end_seq)						\
      do {								\
	if (unlikely (add_new_line (alloca (sizeof (struct linelist)),	\
				    end_seq)))				\
	  goto invalid_data;						\
      } while (0)

      inline bool add_new_line (struct linelist *new_line, bool end_sequence)
      {
#define SET(field)							      \
	do {								      \
	  new_line->line.field = field;					      \
	  if (unlikely (new_line->line.field != field))			      \
	    return true;						      \
        } while (0)

	SET (addr);
	SET (op_index);
	SET (file);
	SET (line);
	SET (column);
	SET (is_stmt);
	SET (basic_block);
	SET (end_sequence);
	SET (prologue_end);
	SET (epilogue_begin);
	SET (isa);
	SET (discriminator);

#undef SET

	new_line->next = linelist;
	linelist = new_line;
	++nlinelist;

	return false;
      }

      while (linep < lineendp)
	{
	  unsigned int opcode;
	  unsigned int u128;
	  int s128;

	  
	  opcode = *linep++;

	  
	  if (likely (opcode >= opcode_base))
	    {
	      int line_increment = (line_base
				    + (opcode - opcode_base) % line_range);

	      
	      line += line_increment;
	      advance_pc ((opcode - opcode_base) / line_range);

	      
	      NEW_LINE (0);

	      
	      basic_block = false;
	      prologue_end = false;
	      epilogue_begin = false;
	      discriminator = 0;
	    }
	  else if (opcode == 0)
	    {
	      
	      if (unlikely (lineendp - linep < 2))
		goto invalid_data;

	      
	      uint_fast8_t len = *linep++;

	      if (unlikely ((size_t) (lineendp - linep) < len))
		goto invalid_data;

	      
	      opcode = *linep++;

	      switch (opcode)
		{
		case DW_LNE_end_sequence:
		  NEW_LINE (1);

		  
		  addr = 0;
		  op_index = 0;
		  file = 1;
		  line = 1;
		  column = 0;
		  is_stmt = default_is_stmt;
		  basic_block = false;
		  prologue_end = false;
		  epilogue_begin = false;
		  isa = 0;
		  discriminator = 0;
		  break;

		case DW_LNE_set_address:
		  op_index = 0;
		  if (unlikely (lineendp - linep < cu->address_size))
		    goto invalid_data;
		  if (__libdw_read_address_inc (dbg, IDX_debug_line, &linep,
						cu->address_size, &addr))
		    goto out;
		  break;

		case DW_LNE_define_file:
		  {
		    char *fname = (char *) linep;
		    uint8_t *endp = memchr (linep, '\0', lineendp - linep);
		    if (endp == NULL)
		      goto invalid_data;
		    size_t fnamelen = endp - linep;
		    linep = endp + 1;

		    unsigned int diridx;
		    get_uleb128 (diridx, linep);
		    Dwarf_Word mtime;
		    get_uleb128 (mtime, linep);
		    Dwarf_Word filelength;
		    get_uleb128 (filelength, linep);

		    struct filelist *new_file =
		      (struct filelist *) alloca (sizeof (*new_file));
		    if (fname[0] == '/')
		      new_file->info.name = fname;
		    else
		      {
			new_file->info.name =
			  libdw_alloc (dbg, char, 1, (dirarray[diridx]->len + 1
						      + fnamelen + 1));
			char *cp = new_file->info.name;

			if (dirarray[diridx]->dir != NULL)
			  cp = stpcpy (cp, dirarray[diridx]->dir);
			*cp++ = '/';
			strcpy (cp, fname);
		      }

		    new_file->info.mtime = mtime;
		    new_file->info.length = filelength;
		    new_file->next = filelist;
		    filelist = new_file;
		    ++nfilelist;
		  }
		  break;

		case DW_LNE_set_discriminator:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_uleb128 (discriminator, linep);
		  break;

		default:
		  
		  if (unlikely ((size_t) (lineendp - (linep - 1)) < len))
		    goto invalid_data;
		  linep += len - 1;
		  break;
		}
	    }
	  else if (opcode <= DW_LNS_set_isa)
	    {
	      
	      switch (opcode)
		{
		case DW_LNS_copy:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  
		  NEW_LINE (0);

		  
		  basic_block = false;
		  prologue_end = false;
		  epilogue_begin = false;
		  discriminator = 0;
		  break;

		case DW_LNS_advance_pc:
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_uleb128 (u128, linep);
		  advance_pc (u128);
		  break;

		case DW_LNS_advance_line:
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_sleb128 (s128, linep);
		  line += s128;
		  break;

		case DW_LNS_set_file:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_uleb128 (u128, linep);
		  file = u128;
		  break;

		case DW_LNS_set_column:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_uleb128 (u128, linep);
		  column = u128;
		  break;

		case DW_LNS_negate_stmt:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  is_stmt = 1 - is_stmt;
		  break;

		case DW_LNS_set_basic_block:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  basic_block = true;
		  break;

		case DW_LNS_const_add_pc:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  advance_pc ((255 - opcode_base) / line_range);
		  break;

		case DW_LNS_fixed_advance_pc:
		  if (unlikely (standard_opcode_lengths[opcode] != 1)
		      || unlikely (lineendp - linep < 2))
		    goto invalid_data;

		  addr += read_2ubyte_unaligned_inc (dbg, linep);
		  op_index = 0;
		  break;

		case DW_LNS_set_prologue_end:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  prologue_end = true;
		  break;

		case DW_LNS_set_epilogue_begin:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 0))
		    goto invalid_data;

		  epilogue_begin = true;
		  break;

		case DW_LNS_set_isa:
		  
		  if (unlikely (standard_opcode_lengths[opcode] != 1))
		    goto invalid_data;

		  get_uleb128 (isa, linep);
		  break;
		}
	    }
	  else
	    {
	      for (int n = standard_opcode_lengths[opcode]; n > 0; --n)
		get_uleb128 (u128, linep);

	      
	      continue;
	    }
	}

      
      Dwarf_Files *files = libdw_alloc (dbg, Dwarf_Files,
					sizeof (Dwarf_Files)
					+ nfilelist * sizeof (Dwarf_Fileinfo)
					+ (ndirlist + 1) * sizeof (char *),
					1);
      const char **dirs = (void *) &files->info[nfilelist];

      files->nfiles = nfilelist;
      while (nfilelist-- > 0)
	{
	  files->info[nfilelist] = filelist->info;
	  filelist = filelist->next;
	}
      assert (filelist == NULL);

      
      files->ndirs = ndirlist;
      for (unsigned int i = 0; i < ndirlist; ++i)
	dirs[i] = dirarray[i]->dir;
      dirs[ndirlist] = NULL;

      
      files->cu = cu;

      
      cu->files = files;

      void *buf = libdw_alloc (dbg, Dwarf_Lines, (sizeof (Dwarf_Lines)
						  + (sizeof (Dwarf_Line)
						     * nlinelist)), 1);

      assert (sizeof (Dwarf_Line) >= sizeof (Dwarf_Line *));
      Dwarf_Line **sortlines = (buf + sizeof (Dwarf_Lines)
				+ ((sizeof (Dwarf_Line)
				    - sizeof (Dwarf_Line *)) * nlinelist));

      unsigned int i = nlinelist;
      while (i-- > 0)
	{
	  sortlines[i] = &linelist->line;
	  linelist = linelist->next;
	}
      assert (linelist == NULL);

      
      qsort (sortlines, nlinelist, sizeof sortlines[0], &compare_lines);

      cu->lines = buf;
      cu->lines->nlines = nlinelist;
      for (i = 0; i < nlinelist; ++i)
	{
	  cu->lines->info[i] = *sortlines[i];
	  cu->lines->info[i].files = files;
	}

      
      res = 0;
    }
  else if (cu->lines != (void *) -1l)
    
    res = 0;

  if (likely (res == 0))
    {
      *lines = cu->lines;
      *nlines = cu->lines->nlines;
    }
 out:

  

  return res;
}
INTDEF(dwarf_getsrclines)
