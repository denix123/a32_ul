/* Create new subsection section in given section.
   Copyright (C) 2002 Red Hat, Inc.
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

#include <stdlib.h>

#include <libasmP.h>
#include <system.h>


AsmScn_t *
asm_newsubscn (asmscn, nr)
     AsmScn_t *asmscn;
     unsigned int nr;
{
  AsmScn_t *runp;
  AsmScn_t *newp;

  if (asmscn == NULL)
    return NULL;

  
  runp = asmscn->subsection_id == 0 ? asmscn : asmscn->data.up;
  while (1)
    {
      if (runp->subsection_id == nr)
	
	return runp;

      if (runp->subnext == NULL || runp->subnext->subsection_id > nr)
	break;

      runp = runp->subnext;
    }

  newp = (AsmScn_t *) malloc (sizeof (AsmScn_t));
  if (newp == NULL)
    return NULL;

  
  newp->ctx = runp->ctx;

  
  newp->subsection_id = nr;

  
  newp->type = runp->type;

  
  newp->data.up = runp->subsection_id == 0 ? runp : runp->data.up;

  
  newp->offset = 0;
  
  newp->max_align = 1;

  
  newp->content = NULL;

  
  newp->pattern = asmscn->pattern;

  
  newp->subnext = runp->subnext;
  runp->subnext = newp;

  return newp;
}
