/* Copyright (C) 2007-2012 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2007.

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

#ifndef _ARLIB_H
#define _ARLIB_H	1

#include <ar.h>
#include <argp.h>
#include <byteswap.h>
#include <endian.h>
#include <libelf.h>
#include <obstack.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


extern bool arlib_deterministic_output;

extern const struct argp_child arlib_argp_children[];


#define MAX_AR_NAME_LEN (sizeof (((struct ar_hdr *) NULL)->ar_name) - 1)


#define AR_HDR_WORDS (sizeof (struct ar_hdr) / sizeof (uint32_t))


#if __BYTE_ORDER == __LITTLE_ENDIAN
# define le_bswap_32(val) bswap_32 (val)
#else
# define le_bswap_32(val) (val)
#endif


struct arlib_symtab
{
  
  struct obstack symsoffob;
  struct obstack symsnameob;
  size_t symsofflen;
  uint32_t *symsoff;
  size_t symsnamelen;
  char *symsname;

  
  struct obstack longnamesob;
  size_t longnameslen;
  char *longnames;
};


extern struct arlib_symtab symtab;


extern void arlib_init (void);

extern void arlib_finalize (void);

extern void arlib_fini (void);

extern void arlib_add_symbols (Elf *elf, const char *arfname,
			       const char *membername, off_t off);

extern void arlib_add_symref (const char *symname, off_t symoff);

extern long int arlib_add_long_name (const char *filename, size_t filenamelen);

#endif	
