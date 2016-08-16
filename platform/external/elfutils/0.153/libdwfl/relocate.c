/* Relocate debug information.
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

#include "libdwflP.h"

typedef uint8_t GElf_Byte;


Dwfl_Error
internal_function
__libdwfl_relocate_value (Dwfl_Module *mod, Elf *elf, size_t *shstrndx,
			  Elf32_Word shndx, GElf_Addr *value)
{
  assert (mod->e_type == ET_REL);

  Elf_Scn *refscn = elf_getscn (elf, shndx);
  GElf_Shdr refshdr_mem, *refshdr = gelf_getshdr (refscn, &refshdr_mem);
  if (refshdr == NULL)
    return DWFL_E_LIBELF;

  if (refshdr->sh_addr == 0 && (refshdr->sh_flags & SHF_ALLOC))
    {

      if (*shstrndx == SHN_UNDEF
	  && unlikely (elf_getshdrstrndx (elf, shstrndx) < 0))
	return DWFL_E_LIBELF;

      const char *name = elf_strptr (elf, *shstrndx, refshdr->sh_name);
      if (unlikely (name == NULL))
	return DWFL_E_LIBELF;

      if ((*mod->dwfl->callbacks->section_address) (MODCB_ARGS (mod),
						    name, shndx, refshdr,
						    &refshdr->sh_addr))
	return CBFAIL;

      if (refshdr->sh_addr == (Dwarf_Addr) -1l)
	refshdr->sh_addr = 0;	

      if (likely (refshdr->sh_addr != 0)
	  && unlikely (! gelf_update_shdr (refscn, refshdr)))
	return DWFL_E_LIBELF;
    }

  if (refshdr->sh_flags & SHF_ALLOC)
    
    *value += dwfl_adjusted_address (mod, refshdr->sh_addr);

  return DWFL_E_NOERROR;
}


struct reloc_symtab_cache
{
  Elf *symelf;
  Elf_Data *symdata;
  Elf_Data *symxndxdata;
  Elf_Data *symstrdata;
  size_t symshstrndx;
  size_t strtabndx;
};
#define RELOC_SYMTAB_CACHE(cache)	\
  struct reloc_symtab_cache cache =	\
    { NULL, NULL, NULL, NULL, SHN_UNDEF, SHN_UNDEF }

static Dwfl_Error
relocate_getsym (Dwfl_Module *mod,
		 Elf *relocated, struct reloc_symtab_cache *cache,
		 int symndx, GElf_Sym *sym, GElf_Word *shndx)
{
  if (cache->symdata == NULL)
    {
      if (mod->symfile == NULL || mod->symfile->elf != relocated)
	{
	  Elf_Scn *scn = NULL;
	  while ((scn = elf_nextscn (relocated, scn)) != NULL)
	    {
	      GElf_Shdr shdr_mem, *shdr = gelf_getshdr (scn, &shdr_mem);
	      if (shdr != NULL)
		switch (shdr->sh_type)
		  {
		  default:
		    continue;
		  case SHT_SYMTAB:
		    cache->symelf = relocated;
		    cache->symdata = elf_getdata (scn, NULL);
		    cache->strtabndx = shdr->sh_link;
		    if (unlikely (cache->symdata == NULL))
		      return DWFL_E_LIBELF;
		    break;
		  case SHT_SYMTAB_SHNDX:
		    cache->symxndxdata = elf_getdata (scn, NULL);
		    if (unlikely (cache->symxndxdata == NULL))
		      return DWFL_E_LIBELF;
		    break;
		  }
	      if (cache->symdata != NULL && cache->symxndxdata != NULL)
		break;
	    }
	}
      if (cache->symdata == NULL)
	{
	  if (unlikely (mod->symfile == NULL)
	      && unlikely (INTUSE(dwfl_module_getsymtab) (mod) < 0))
	    return dwfl_errno ();

	  cache->symelf = mod->symfile->elf;
	  cache->symdata = mod->symdata;
	  cache->symxndxdata = mod->symxndxdata;
	  cache->symstrdata = mod->symstrdata;
	}
    }

  if (unlikely (gelf_getsymshndx (cache->symdata, cache->symxndxdata,
				  symndx, sym, shndx) == NULL))
    return DWFL_E_LIBELF;

  if (sym->st_shndx != SHN_XINDEX)
    *shndx = sym->st_shndx;

  switch (sym->st_shndx)
    {
    case SHN_ABS:
    case SHN_UNDEF:
      return DWFL_E_NOERROR;

    case SHN_COMMON:
      sym->st_value = 0;	
      return DWFL_E_NOERROR;
    }

  return __libdwfl_relocate_value (mod, cache->symelf, &cache->symshstrndx,
				   *shndx, &sym->st_value);
}

static Dwfl_Error
resolve_symbol (Dwfl_Module *referer, struct reloc_symtab_cache *symtab,
		GElf_Sym *sym, GElf_Word shndx)
{
  
  if (sym->st_name != 0)
    {
      if (symtab->symstrdata == NULL)
	{
	  
	  assert (referer->symfile == NULL
		  || referer->symfile->elf != symtab->symelf);
	  symtab->symstrdata = elf_getdata (elf_getscn (symtab->symelf,
							symtab->strtabndx),
					    NULL);
	  if (unlikely (symtab->symstrdata == NULL))
	    return DWFL_E_LIBELF;
	}
      if (unlikely (sym->st_name >= symtab->symstrdata->d_size))
	return DWFL_E_BADSTROFF;

      const char *name = symtab->symstrdata->d_buf;
      name += sym->st_name;

      for (Dwfl_Module *m = referer->dwfl->modulelist; m != NULL; m = m->next)
	if (m != referer)
	  {
	    if (m->symdata == NULL
		&& m->symerr == DWFL_E_NOERROR
		&& INTUSE(dwfl_module_getsymtab) (m) < 0
		&& m->symerr != DWFL_E_NO_SYMTAB)
	      return m->symerr;

	    for (size_t ndx = 1; ndx < m->syments; ++ndx)
	      {
		sym = gelf_getsymshndx (m->symdata, m->symxndxdata,
					ndx, sym, &shndx);
		if (unlikely (sym == NULL))
		  return DWFL_E_LIBELF;
		if (sym->st_shndx != SHN_XINDEX)
		  shndx = sym->st_shndx;

		
		if (shndx == SHN_UNDEF || shndx == SHN_COMMON
		    || GELF_ST_BIND (sym->st_info) == STB_LOCAL
		    || sym->st_name == 0)
		  continue;

		
		if (unlikely (sym->st_name >= m->symstrdata->d_size))
		  return DWFL_E_BADSTROFF;
		const char *n = m->symstrdata->d_buf;
		n += sym->st_name;

		
		if (strcmp (name, n))
		  continue;

		
		if (shndx == SHN_ABS) 
		  return DWFL_E_NOERROR;

		if (m->e_type != ET_REL)
		  {
		    sym->st_value = dwfl_adjusted_st_value (m, sym->st_value);
		    return DWFL_E_NOERROR;
		  }

		size_t symshstrndx = SHN_UNDEF;
		return __libdwfl_relocate_value (m, m->symfile->elf,
						 &symshstrndx,
						 shndx, &sym->st_value);
	      }
	  }
    }

  return DWFL_E_RELUNDEF;
}

static Dwfl_Error
relocate_section (Dwfl_Module *mod, Elf *relocated, const GElf_Ehdr *ehdr,
		  size_t shstrndx, struct reloc_symtab_cache *reloc_symtab,
		  Elf_Scn *scn, GElf_Shdr *shdr,
		  Elf_Scn *tscn, bool debugscn, bool partial)
{
  
  GElf_Shdr tshdr_mem;
  GElf_Shdr *tshdr = gelf_getshdr (tscn, &tshdr_mem);
  const char *tname = elf_strptr (relocated, shstrndx, tshdr->sh_name);
  if (tname == NULL)
    return DWFL_E_LIBELF;

  if (unlikely (tshdr->sh_type == SHT_NOBITS) || unlikely (tshdr->sh_size == 0))
    
    return DWFL_E_NOERROR;

  if (debugscn && ! ebl_debugscn_p (mod->ebl, tname))
    return DWFL_E_NOERROR;

  
  Elf_Data *tdata = elf_rawdata (tscn, NULL);
  if (tdata == NULL)
    return DWFL_E_LIBELF;

  
  Dwfl_Error relocate (GElf_Addr offset, const GElf_Sxword *addend,
		       int rtype, int symndx)
  {

    if (unlikely (rtype == 0))
      return DWFL_E_NOERROR;

    Elf_Type type = ebl_reloc_simple_type (mod->ebl, rtype);
    if (unlikely (type == ELF_T_NUM))
      return DWFL_E_BADRELTYPE;

    
    GElf_Addr value;

    if (symndx == STN_UNDEF)
      value = 0;
    else
      {
	GElf_Sym sym;
	GElf_Word shndx;
	Dwfl_Error error = relocate_getsym (mod, relocated, reloc_symtab,
					    symndx, &sym, &shndx);
	if (unlikely (error != DWFL_E_NOERROR))
	  return error;

	if (shndx == SHN_UNDEF || shndx == SHN_COMMON)
	  {
	    
	    error = resolve_symbol (mod, reloc_symtab, &sym, shndx);
	    if (error != DWFL_E_NOERROR
		&& !(error == DWFL_E_RELUNDEF && shndx == SHN_COMMON))
	      return error;
	  }

	value = sym.st_value;
      }

    
#define TYPES		DO_TYPE (BYTE, Byte); DO_TYPE (HALF, Half);	\
    DO_TYPE (WORD, Word); DO_TYPE (SWORD, Sword);			\
    DO_TYPE (XWORD, Xword); DO_TYPE (SXWORD, Sxword)
    size_t size;
    switch (type)
      {
#define DO_TYPE(NAME, Name)			\
	case ELF_T_##NAME:			\
	  size = sizeof (GElf_##Name);		\
	break
	TYPES;
#undef DO_TYPE
      default:
	return DWFL_E_BADRELTYPE;
      }

    if (offset + size > tdata->d_size)
      return DWFL_E_BADRELOFF;

#define DO_TYPE(NAME, Name) GElf_##Name Name;
    union { TYPES; } tmpbuf;
#undef DO_TYPE
    Elf_Data tmpdata =
      {
	.d_type = type,
	.d_buf = &tmpbuf,
	.d_size = size,
	.d_version = EV_CURRENT,
      };
    Elf_Data rdata =
      {
	.d_type = type,
	.d_buf = tdata->d_buf + offset,
	.d_size = size,
	.d_version = EV_CURRENT,
      };

    
    if (addend)
      {
	
	value += *addend;
	switch (type)
	  {
#define DO_TYPE(NAME, Name)			\
	    case ELF_T_##NAME:			\
	      tmpbuf.Name = value;		\
	    break
	    TYPES;
#undef DO_TYPE
	  default:
	    abort ();
	  }
      }
    else
      {
	
	Elf_Data *d = gelf_xlatetom (relocated, &tmpdata, &rdata,
				     ehdr->e_ident[EI_DATA]);
	if (d == NULL)
	  return DWFL_E_LIBELF;
	assert (d == &tmpdata);
	switch (type)
	  {
#define DO_TYPE(NAME, Name)				\
	    case ELF_T_##NAME:				\
	      tmpbuf.Name += (GElf_##Name) value;	\
	    break
	    TYPES;
#undef DO_TYPE
	  default:
	    abort ();
	  }
      }

    Elf_Data *s = gelf_xlatetof (relocated, &rdata, &tmpdata,
				 ehdr->e_ident[EI_DATA]);
    if (s == NULL)
      return DWFL_E_LIBELF;
    assert (s == &rdata);

    
    return DWFL_E_NOERROR;
  }

  
  Elf_Data *reldata = elf_getdata (scn, NULL);
  if (reldata == NULL)
    return DWFL_E_LIBELF;

  Dwfl_Error result = DWFL_E_NOERROR;
  bool first_badreltype = true;
  inline void check_badreltype (void)
  {
    if (first_badreltype)
      {
	first_badreltype = false;
	if (ebl_get_elfmachine (mod->ebl) == EM_NONE)
	  result = DWFL_E_UNKNOWN_MACHINE;
      }
  }

  size_t nrels = shdr->sh_size / shdr->sh_entsize;
  size_t complete = 0;
  if (shdr->sh_type == SHT_REL)
    for (size_t relidx = 0; !result && relidx < nrels; ++relidx)
      {
	GElf_Rel rel_mem, *r = gelf_getrel (reldata, relidx, &rel_mem);
	if (r == NULL)
	  return DWFL_E_LIBELF;
	result = relocate (r->r_offset, NULL,
			   GELF_R_TYPE (r->r_info),
			   GELF_R_SYM (r->r_info));
	check_badreltype ();
	if (partial)
	  switch (result)
	    {
	    case DWFL_E_NOERROR:
	      
	      memset (&rel_mem, 0, sizeof rel_mem);
	      gelf_update_rel (reldata, relidx, &rel_mem);
	      ++complete;
	      break;
	    case DWFL_E_BADRELTYPE:
	    case DWFL_E_RELUNDEF:
	      
	      result = DWFL_E_NOERROR;
	      break;
	    default:
	      break;
	    }
      }
  else
    for (size_t relidx = 0; !result && relidx < nrels; ++relidx)
      {
	GElf_Rela rela_mem, *r = gelf_getrela (reldata, relidx,
					       &rela_mem);
	if (r == NULL)
	  return DWFL_E_LIBELF;
	result = relocate (r->r_offset, &r->r_addend,
			   GELF_R_TYPE (r->r_info),
			   GELF_R_SYM (r->r_info));
	check_badreltype ();
	if (partial)
	  switch (result)
	    {
	    case DWFL_E_NOERROR:
	      
	      memset (&rela_mem, 0, sizeof rela_mem);
	      gelf_update_rela (reldata, relidx, &rela_mem);
	      ++complete;
	      break;
	    case DWFL_E_BADRELTYPE:
	    case DWFL_E_RELUNDEF:
	      
	      result = DWFL_E_NOERROR;
	      break;
	    default:
	      break;
	    }
      }

  if (likely (result == DWFL_E_NOERROR))
    {
      if (!partial || complete == nrels)
	nrels = 0;
      else if (complete != 0)
	{

	  size_t next = 0;
	  if (shdr->sh_type == SHT_REL)
	    for (size_t relidx = 0; relidx < nrels; ++relidx)
	      {
		GElf_Rel rel_mem;
		GElf_Rel *r = gelf_getrel (reldata, relidx, &rel_mem);
		if (r->r_info != 0 || r->r_offset != 0)
		  {
		    if (next != relidx)
		      gelf_update_rel (reldata, next, r);
		    ++next;
		  }
	      }
	  else
	    for (size_t relidx = 0; relidx < nrels; ++relidx)
	      {
		GElf_Rela rela_mem;
		GElf_Rela *r = gelf_getrela (reldata, relidx, &rela_mem);
		if (r->r_info != 0 || r->r_offset != 0 || r->r_addend != 0)
		  {
		    if (next != relidx)
		      gelf_update_rela (reldata, next, r);
		    ++next;
		  }
	      }
	  nrels = next;
	}

      shdr->sh_size = reldata->d_size = nrels * shdr->sh_entsize;
      gelf_update_shdr (scn, shdr);
    }

  return result;
}

Dwfl_Error
internal_function
__libdwfl_relocate (Dwfl_Module *mod, Elf *debugfile, bool debug)
{
  assert (mod->e_type == ET_REL);

  GElf_Ehdr ehdr_mem;
  const GElf_Ehdr *ehdr = gelf_getehdr (debugfile, &ehdr_mem);
  if (ehdr == NULL)
    return DWFL_E_LIBELF;

  size_t d_shstrndx;
  if (elf_getshdrstrndx (debugfile, &d_shstrndx) < 0)
    return DWFL_E_LIBELF;

  RELOC_SYMTAB_CACHE (reloc_symtab);

  Dwfl_Error result = DWFL_E_NOERROR;
  Elf_Scn *scn = NULL;
  while (result == DWFL_E_NOERROR
	 && (scn = elf_nextscn (debugfile, scn)) != NULL)
    {
      GElf_Shdr shdr_mem;
      GElf_Shdr *shdr = gelf_getshdr (scn, &shdr_mem);

      if ((shdr->sh_type == SHT_REL || shdr->sh_type == SHT_RELA)
	  && shdr->sh_size != 0)
	{
	  

	  Elf_Scn *tscn = elf_getscn (debugfile, shdr->sh_info);
	  if (unlikely (tscn == NULL))
	    result = DWFL_E_LIBELF;
	  else
	    result = relocate_section (mod, debugfile, ehdr, d_shstrndx,
				       &reloc_symtab, scn, shdr, tscn,
				       debug, !debug);
	}
    }

  return result;
}

Dwfl_Error
internal_function
__libdwfl_relocate_section (Dwfl_Module *mod, Elf *relocated,
			    Elf_Scn *relocscn, Elf_Scn *tscn, bool partial)
{
  GElf_Ehdr ehdr_mem;
  GElf_Shdr shdr_mem;

  RELOC_SYMTAB_CACHE (reloc_symtab);

  size_t shstrndx;
  if (elf_getshdrstrndx (relocated, &shstrndx) < 0)
    return DWFL_E_LIBELF;

  return (__libdwfl_module_getebl (mod)
	  ?: relocate_section (mod, relocated,
			       gelf_getehdr (relocated, &ehdr_mem), shstrndx,
			       &reloc_symtab,
			       relocscn, gelf_getshdr (relocscn, &shdr_mem),
			       tscn, false, partial));
}
