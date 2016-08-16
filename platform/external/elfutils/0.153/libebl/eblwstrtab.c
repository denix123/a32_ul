/* ELF string table handling.
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
#include <inttypes.h>
#include <libelf.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <sys/param.h>

#include "libebl.h"
#include <system.h>

#ifndef MIN
# define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif


struct Ebl_WStrent
{
  const wchar_t *string;
  size_t len;
  struct Ebl_WStrent *next;
  struct Ebl_WStrent *left;
  struct Ebl_WStrent *right;
  size_t offset;
  wchar_t reverse[0];
};


struct memoryblock
{
  struct memoryblock *next;
  char memory[0];
};


struct Ebl_WStrtab
{
  struct Ebl_WStrent *root;
  struct memoryblock *memory;
  char *backp;
  size_t left;
  size_t total;
  bool nullstr;

  struct Ebl_WStrent null;
};


static size_t ps;


struct Ebl_WStrtab *
ebl_wstrtabinit (bool nullstr)
{
  struct Ebl_WStrtab *ret;

  if (ps == 0)
    {
      ps = sysconf (_SC_PAGESIZE) - 2 * sizeof (void *);
      assert (sizeof (struct memoryblock) < ps);
    }

  ret = (struct Ebl_WStrtab *) calloc (1, sizeof (struct Ebl_WStrtab));
  if (ret != NULL)
    {
      ret->nullstr = nullstr;
      if (nullstr)
	{
	  ret->null.len = 1;
	  ret->null.string = L"";
	}
    }
  return ret;
}


static int
morememory (struct Ebl_WStrtab *st, size_t len)
{
  struct memoryblock *newmem;

  if (len < ps)
    len = ps;
  newmem = (struct memoryblock *) malloc (len);
  if (newmem == NULL)
    return 1;

  newmem->next = st->memory;
  st->memory = newmem;
  st->backp = newmem->memory;
  st->left = len - offsetof (struct memoryblock, memory);

  return 0;
}


void
ebl_wstrtabfree (struct Ebl_WStrtab *st)
{
  struct memoryblock *mb = st->memory;

  while (mb != NULL)
    {
      void *old = mb;
      mb = mb->next;
      free (old);
    }

  free (st);
}


static struct Ebl_WStrent *
newstring (struct Ebl_WStrtab *st, const wchar_t *str, size_t len)
{
  struct Ebl_WStrent *newstr;
  size_t align;
  int i;

  
  align = ((__alignof__ (struct Ebl_WStrent)
	    - (((uintptr_t) st->backp)
	       & (__alignof__ (struct Ebl_WStrent) - 1)))
	   & (__alignof__ (struct Ebl_WStrent) - 1));

  
  if (st->left < align + sizeof (struct Ebl_WStrent) + len * sizeof (wchar_t))
    {
      if (morememory (st,
		      sizeof (struct Ebl_WStrent) + len * sizeof (wchar_t)))
	return NULL;

      align = 0;
    }

  
  newstr = (struct Ebl_WStrent *) (st->backp + align);
  newstr->string = str;
  newstr->len = len;
  newstr->next = NULL;
  newstr->left = NULL;
  newstr->right = NULL;
  newstr->offset = 0;
  for (i = len - 2; i >= 0; --i)
    newstr->reverse[i] = str[len - 2 - i];
  newstr->reverse[len - 1] = L'\0';
  st->backp += align + sizeof (struct Ebl_WStrent) + len * sizeof (wchar_t);
  st->left -= align + sizeof (struct Ebl_WStrent) + len * sizeof (wchar_t);

  return newstr;
}


/* XXX This function should definitely be rewritten to use a balancing
   tree algorith (AVL, red-black trees).  For now a simple, correct
   implementation is enough.  */
static struct Ebl_WStrent **
searchstring (struct Ebl_WStrent **sep, struct Ebl_WStrent *newstr)
{
  int cmpres;

  
  if (*sep == NULL)
    {
      *sep = newstr;
      return sep;
    }

  
  cmpres = wmemcmp ((*sep)->reverse, newstr->reverse,
		    MIN ((*sep)->len, newstr->len) - 1);
  if (cmpres == 0)
    
    return sep;
  else if (cmpres > 0)
    return searchstring (&(*sep)->left, newstr);
  else
    return searchstring (&(*sep)->right, newstr);
}


struct Ebl_WStrent *
ebl_wstrtabadd (struct Ebl_WStrtab *st, const wchar_t *str, size_t len)
{
  struct Ebl_WStrent *newstr;
  struct Ebl_WStrent **sep;

  
  if (len == 0)
    len = wcslen (str) + 1;

  if (len == 1 && st->null.string != NULL)
    return &st->null;

  
  newstr = newstring (st, str, len);
  if (newstr == NULL)
    return NULL;

  sep = searchstring (&st->root, newstr);
  if (*sep != newstr)
    {
      
      if ((*sep)->len > newstr->len)
	{
	  struct Ebl_WStrent *subs;

	  
	  for (subs = (*sep)->next; subs != NULL; subs = subs->next)
	    if (subs->len == newstr->len)
	      {
		st->left += st->backp - (char *) newstr;
		st->backp = (char *) newstr;

		return subs;
	      }

	  st->backp -= newstr->len;
	  st->left += newstr->len;

	  newstr->next = (*sep)->next;
	  (*sep)->next = newstr;
	}
      else if ((*sep)->len != newstr->len)
	{
	  st->total += newstr->len - (*sep)->len;
	  newstr->next = *sep;
	  newstr->left = (*sep)->left;
	  newstr->right = (*sep)->right;
	  *sep = newstr;
	}
      else
	{
	  
	  st->left += st->backp - (char *) newstr;
	  st->backp = (char *) newstr;

	  newstr = *sep;
	}
    }
  else
    st->total += newstr->len;

  return newstr;
}


static void
copystrings (struct Ebl_WStrent *nodep, wchar_t **freep, size_t *offsetp)
{
  struct Ebl_WStrent *subs;

  if (nodep->left != NULL)
    copystrings (nodep->left, freep, offsetp);

  
  nodep->offset = *offsetp;
  *freep = wmempcpy (*freep, nodep->string, nodep->len);
  *offsetp += nodep->len * sizeof (wchar_t);

  for (subs = nodep->next; subs != NULL; subs = subs->next)
    {
      assert (subs->len < nodep->len);
      subs->offset = nodep->offset + nodep->len - subs->len;
      assert (subs->offset != 0 || subs->string[0] == '\0');
    }

  if (nodep->right != NULL)
    copystrings (nodep->right, freep, offsetp);
}


void
ebl_wstrtabfinalize (struct Ebl_WStrtab *st, Elf_Data *data)
{
  size_t copylen;
  wchar_t *endp;
  size_t nulllen = st->nullstr ? 1 : 0;

  
  data->d_buf = malloc ((st->total + nulllen) * sizeof (wchar_t));
  if (data->d_buf == NULL)
    abort ();

  if (st->nullstr)
    *((wchar_t *) data->d_buf) = L'\0';

  data->d_type = ELF_T_BYTE;
  data->d_size = st->total + nulllen;
  data->d_off = 0;
  data->d_align = 1;
  data->d_version = EV_CURRENT;

  endp = (wchar_t *) data->d_buf + nulllen;
  copylen = sizeof (wchar_t) * nulllen;
  copystrings (st->root, &endp, &copylen);
  assert (copylen == (st->total + nulllen) * sizeof (wchar_t));
}


size_t
ebl_wstrtaboffset (struct Ebl_WStrent *se)
{
  return se->offset;
}
