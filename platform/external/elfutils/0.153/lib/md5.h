/* Declaration of functions and data types used for MD5 sum computing
   library functions.
   Copyright (C) 1995,1996,1997,1999-2001,2004,2005,2008 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 1995.

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

#ifndef _MD5_H
#define _MD5_H 1

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define MD5_DIGEST_SIZE 16
#define MD5_BLOCK_SIZE 64

typedef uint32_t md5_uint32;
typedef uintptr_t md5_uintptr;

struct md5_ctx
{
  md5_uint32 A;
  md5_uint32 B;
  md5_uint32 C;
  md5_uint32 D;

  md5_uint32 total[2];
  md5_uint32 buflen;
  char buffer[128] __attribute__ ((__aligned__ (__alignof__ (md5_uint32))));
};


extern void md5_init_ctx (struct md5_ctx *ctx);

extern void md5_process_block (const void *buffer, size_t len,
			       struct md5_ctx *ctx);

extern void md5_process_bytes (const void *buffer, size_t len,
			       struct md5_ctx *ctx);

extern void *md5_finish_ctx (struct md5_ctx *ctx, void *resbuf);


extern void *md5_read_ctx (const struct md5_ctx *ctx, void *resbuf);


/* Compute MD5 message digest for bytes read from STREAM.  The
   resulting message digest number will be written into the 16 bytes
   beginning at RESBLOCK.  */
extern int md5_stream (FILE *stream, void *resblock);

extern void *md5_buffer (const char *buffer, size_t len, void *resblock);

#endif 