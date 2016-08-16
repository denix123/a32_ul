/* Find debugging and symbol information for a module in libdwfl.
   Copyright (C) 2005-2011 Red Hat, Inc.
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
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "../libdw/libdwP.h"	


static inline Dwfl_Error
open_elf (Dwfl_Module *mod, struct dwfl_file *file)
{
  if (file->elf == NULL)
    {
      errno = 0;

      if (file->fd < 0 && file->name != NULL)
	file->fd = TEMP_FAILURE_RETRY (open64 (file->name, O_RDONLY));

      if (file->fd < 0)
	return CBFAIL;

      Dwfl_Error error = __libdw_open_file (&file->fd, &file->elf, true, false);
      if (error != DWFL_E_NOERROR)
	return error;
    }
  else if (unlikely (elf_kind (file->elf) != ELF_K_ELF))
    {
      elf_end (file->elf);
      file->elf = NULL;
      close (file->fd);
      file->fd = -1;
      return DWFL_E_BADELF;
    }

  GElf_Ehdr ehdr_mem, *ehdr = gelf_getehdr (file->elf, &ehdr_mem);
  if (ehdr == NULL)
    {
    elf_error:
      elf_end (file->elf);
      file->elf = NULL;
      close (file->fd);
      file->fd = -1;
      return DWFL_E (LIBELF, elf_errno ());
    }

  if (mod->e_type != ET_REL)
    {

      size_t phnum;
      if (unlikely (elf_getphdrnum (file->elf, &phnum) != 0))
	goto elf_error;

      file->vaddr = file->address_sync = 0;
      for (size_t i = 0; i < phnum; ++i)
	{
	  GElf_Phdr ph_mem;
	  GElf_Phdr *ph = gelf_getphdr (file->elf, i, &ph_mem);
	  if (unlikely (ph == NULL))
	    goto elf_error;
	  if (ph->p_type == PT_LOAD)
	    {
	      file->vaddr = ph->p_vaddr & -ph->p_align;
	      file->address_sync = ph->p_vaddr + ph->p_memsz;
	      break;
	    }
	}
    }

  mod->e_type = ehdr->e_type;

  
  if (mod->e_type == ET_EXEC && file->vaddr != mod->low_addr)
    mod->e_type = ET_DYN;

  return DWFL_E_NOERROR;
}

void
internal_function
__libdwfl_getelf (Dwfl_Module *mod)
{
  if (mod->main.elf != NULL	
      || mod->elferr != DWFL_E_NOERROR)	
    return;

  mod->main.fd = (*mod->dwfl->callbacks->find_elf) (MODCB_ARGS (mod),
						    &mod->main.name,
						    &mod->main.elf);
  const bool fallback = mod->main.elf == NULL && mod->main.fd < 0;
  mod->elferr = open_elf (mod, &mod->main);
  if (mod->elferr != DWFL_E_NOERROR)
    return;

  if (!mod->main.valid)
    {
      free (mod->build_id_bits);
      mod->build_id_bits = NULL;
      mod->build_id_len = 0;
    }
  else if (fallback)
    {

      assert (mod->build_id_len > 0);

      switch (__builtin_expect (__libdwfl_find_build_id (mod, false,
							 mod->main.elf), 2))
	{
	case 2:
	  
	  return;

	case -1:			
	  mod->elferr = INTUSE(dwfl_errno) ();
	  break;

	case 0:			
	case 1:			
	  mod->elferr = DWFL_E_WRONG_ID_ELF;
	  break;

	default:
	  abort ();
	}

      
      elf_end (mod->main.elf);
      mod->main.elf = NULL;
      if (mod->main.fd >= 0)
	{
	  close (mod->main.fd);
	  mod->main.fd = -1;
	}
    }

  mod->main_bias = mod->e_type == ET_REL ? 0 : mod->low_addr - mod->main.vaddr;
}

static const char *
find_debuglink (Elf *elf, GElf_Word *crc)
{
  size_t shstrndx;
  if (elf_getshdrstrndx (elf, &shstrndx) < 0)
    return NULL;

  Elf_Scn *scn = NULL;
  while ((scn = elf_nextscn (elf, scn)) != NULL)
    {
      GElf_Shdr shdr_mem;
      GElf_Shdr *shdr = gelf_getshdr (scn, &shdr_mem);
      if (shdr == NULL)
	return NULL;

      const char *name = elf_strptr (elf, shstrndx, shdr->sh_name);
      if (name == NULL)
	return NULL;

      if (!strcmp (name, ".gnu_debuglink"))
	break;
    }

  if (scn == NULL)
    return NULL;

  
  Elf_Data *rawdata = elf_rawdata (scn, NULL);
  if (rawdata == NULL)
    return NULL;

  Elf_Data crcdata =
    {
      .d_type = ELF_T_WORD,
      .d_buf = crc,
      .d_size = sizeof *crc,
      .d_version = EV_CURRENT,
    };
  Elf_Data conv =
    {
      .d_type = ELF_T_WORD,
      .d_buf = rawdata->d_buf + rawdata->d_size - sizeof *crc,
      .d_size = sizeof *crc,
      .d_version = EV_CURRENT,
    };

  GElf_Ehdr ehdr_mem;
  GElf_Ehdr *ehdr = gelf_getehdr (elf, &ehdr_mem);
  if (ehdr == NULL)
    return NULL;

  Elf_Data *d = gelf_xlatetom (elf, &crcdata, &conv, ehdr->e_ident[EI_DATA]);
  if (d == NULL)
    return NULL;
  assert (d == &crcdata);

  return rawdata->d_buf;
}

static Dwfl_Error
find_prelink_address_sync (Dwfl_Module *mod)
{
  
  size_t shstrndx;
  if (elf_getshdrstrndx (mod->main.elf, &shstrndx) < 0)
    return DWFL_E_LIBELF;

  Elf_Scn *scn = NULL;
  while ((scn = elf_nextscn (mod->main.elf, scn)) != NULL)
    {
      GElf_Shdr shdr_mem;
      GElf_Shdr *shdr = gelf_getshdr (scn, &shdr_mem);
      if (unlikely (shdr == NULL))
	return DWFL_E_LIBELF;
      if (shdr->sh_type == SHT_PROGBITS
	  && !(shdr->sh_flags & SHF_ALLOC)
	  && shdr->sh_name != 0)
	{
	  const char *secname = elf_strptr (mod->main.elf, shstrndx,
					    shdr->sh_name);
	  if (unlikely (secname == NULL))
	    return DWFL_E_LIBELF;
	  if (!strcmp (secname, ".gnu.prelink_undo"))
	    break;
	}
    }

  if (scn == NULL)
    
    return DWFL_E_NOERROR;

  Elf_Data *undodata = elf_rawdata (scn, NULL);
  if (unlikely (undodata == NULL))
    return DWFL_E_LIBELF;


  union
  {
    Elf32_Ehdr e32;
    Elf64_Ehdr e64;
  } ehdr;
  Elf_Data dst =
    {
      .d_buf = &ehdr,
      .d_size = sizeof ehdr,
      .d_type = ELF_T_EHDR,
      .d_version = EV_CURRENT
    };
  Elf_Data src = *undodata;
  src.d_size = gelf_fsize (mod->main.elf, ELF_T_EHDR, 1, EV_CURRENT);
  src.d_type = ELF_T_EHDR;
  if (unlikely (gelf_xlatetom (mod->main.elf, &dst, &src,
			       elf_getident (mod->main.elf, NULL)[EI_DATA])
		== NULL))
    return DWFL_E_LIBELF;

  size_t shentsize = gelf_fsize (mod->main.elf, ELF_T_SHDR, 1, EV_CURRENT);
  size_t phentsize = gelf_fsize (mod->main.elf, ELF_T_PHDR, 1, EV_CURRENT);

  uint_fast16_t phnum;
  uint_fast16_t shnum;
  if (ehdr.e32.e_ident[EI_CLASS] == ELFCLASS32)
    {
      if (ehdr.e32.e_shentsize != shentsize
	  || ehdr.e32.e_phentsize != phentsize)
	return DWFL_E_BAD_PRELINK;
      phnum = ehdr.e32.e_phnum;
      shnum = ehdr.e32.e_shnum;
    }
  else
    {
      if (ehdr.e64.e_shentsize != shentsize
	  || ehdr.e64.e_phentsize != phentsize)
	return DWFL_E_BAD_PRELINK;
      phnum = ehdr.e64.e_phnum;
      shnum = ehdr.e64.e_shnum;
    }

  if (unlikely (shnum >= SHN_LORESERVE)
      || unlikely (undodata->d_size != (src.d_size
					+ phnum * phentsize
					+ (shnum - 1) * shentsize)))
    return DWFL_E_BAD_PRELINK;


  GElf_Addr main_interp = 0;
  {
    size_t main_phnum;
    if (unlikely (elf_getphdrnum (mod->main.elf, &main_phnum)))
      return DWFL_E_LIBELF;
    for (size_t i = 0; i < main_phnum; ++i)
      {
	GElf_Phdr phdr;
	if (unlikely (gelf_getphdr (mod->main.elf, i, &phdr) == NULL))
	  return DWFL_E_LIBELF;
	if (phdr.p_type == PT_INTERP)
	  {
	    main_interp = phdr.p_vaddr;
	    break;
	  }
      }
  }

  src.d_buf += src.d_size;
  src.d_type = ELF_T_PHDR;
  src.d_size = phnum * phentsize;

  GElf_Addr undo_interp = 0;
  {
    union
    {
      Elf32_Phdr p32[phnum];
      Elf64_Phdr p64[phnum];
    } phdr;
    dst.d_buf = &phdr;
    dst.d_size = sizeof phdr;
    if (unlikely (gelf_xlatetom (mod->main.elf, &dst, &src,
				 ehdr.e32.e_ident[EI_DATA]) == NULL))
      return DWFL_E_LIBELF;
    if (ehdr.e32.e_ident[EI_CLASS] == ELFCLASS32)
      {
	for (uint_fast16_t i = 0; i < phnum; ++i)
	  if (phdr.p32[i].p_type == PT_INTERP)
	    {
	      undo_interp = phdr.p32[i].p_vaddr;
	      break;
	    }
      }
    else
      {
	for (uint_fast16_t i = 0; i < phnum; ++i)
	  if (phdr.p64[i].p_type == PT_INTERP)
	    {
	      undo_interp = phdr.p64[i].p_vaddr;
	      break;
	    }
      }
  }

  if (unlikely ((main_interp == 0) != (undo_interp == 0)))
    return DWFL_E_BAD_PRELINK;

  src.d_buf += src.d_size;
  src.d_type = ELF_T_SHDR;
  src.d_size = gelf_fsize (mod->main.elf, ELF_T_SHDR, shnum - 1, EV_CURRENT);

  union
  {
    Elf32_Shdr s32[shnum - 1];
    Elf64_Shdr s64[shnum - 1];
  } shdr;
  dst.d_buf = &shdr;
  dst.d_size = sizeof shdr;
  if (unlikely (gelf_xlatetom (mod->main.elf, &dst, &src,
			       ehdr.e32.e_ident[EI_DATA]) == NULL))
    return DWFL_E_LIBELF;


  GElf_Addr highest;

  inline void consider_shdr (GElf_Addr interp,
			     GElf_Word sh_type,
			     GElf_Xword sh_flags,
			     GElf_Addr sh_addr,
			     GElf_Xword sh_size)
  {
    if ((sh_flags & SHF_ALLOC)
	&& ((sh_type == SHT_PROGBITS && sh_addr != interp)
	    || sh_type == SHT_NOBITS))
      {
	const GElf_Addr sh_end = sh_addr + sh_size;
	if (sh_end > highest)
	  highest = sh_end;
      }
  }

  highest = 0;
  scn = NULL;
  while ((scn = elf_nextscn (mod->main.elf, scn)) != NULL)
    {
      GElf_Shdr sh_mem;
      GElf_Shdr *sh = gelf_getshdr (scn, &sh_mem);
      if (unlikely (sh == NULL))
	return DWFL_E_LIBELF;
      consider_shdr (main_interp, sh->sh_type, sh->sh_flags,
		     sh->sh_addr, sh->sh_size);
    }
  if (highest > mod->main.vaddr)
    {
      mod->main.address_sync = highest;

      highest = 0;
      if (ehdr.e32.e_ident[EI_CLASS] == ELFCLASS32)
	for (size_t i = 0; i < shnum - 1; ++i)
	  consider_shdr (undo_interp, shdr.s32[i].sh_type, shdr.s32[i].sh_flags,
			 shdr.s32[i].sh_addr, shdr.s32[i].sh_size);
      else
	for (size_t i = 0; i < shnum - 1; ++i)
	  consider_shdr (undo_interp, shdr.s64[i].sh_type, shdr.s64[i].sh_flags,
			 shdr.s64[i].sh_addr, shdr.s64[i].sh_size);

      if (highest > mod->debug.vaddr)
	mod->debug.address_sync = highest;
      else
	return DWFL_E_BAD_PRELINK;
    }

  return DWFL_E_NOERROR;
}

static Dwfl_Error
find_debuginfo (Dwfl_Module *mod)
{
  if (mod->debug.elf != NULL)
    return DWFL_E_NOERROR;

  GElf_Word debuglink_crc = 0;
  const char *debuglink_file = find_debuglink (mod->main.elf, &debuglink_crc);

  mod->debug.fd = (*mod->dwfl->callbacks->find_debuginfo) (MODCB_ARGS (mod),
							   mod->main.name,
							   debuglink_file,
							   debuglink_crc,
							   &mod->debug.name);
  Dwfl_Error result = open_elf (mod, &mod->debug);
  if (result == DWFL_E_NOERROR && mod->debug.address_sync != 0)
    result = find_prelink_address_sync (mod);
  return result;
}


static Dwfl_Error
load_symtab (struct dwfl_file *file, struct dwfl_file **symfile,
	     Elf_Scn **symscn, Elf_Scn **xndxscn,
	     size_t *syments, int *first_global, GElf_Word *strshndx)
{
  bool symtab = false;
  Elf_Scn *scn = NULL;
  while ((scn = elf_nextscn (file->elf, scn)) != NULL)
    {
      GElf_Shdr shdr_mem, *shdr = gelf_getshdr (scn, &shdr_mem);
      if (shdr != NULL)
	switch (shdr->sh_type)
	  {
	  case SHT_SYMTAB:
	    symtab = true;
	    *symscn = scn;
	    *symfile = file;
	    *strshndx = shdr->sh_link;
	    *syments = shdr->sh_size / shdr->sh_entsize;
	    *first_global = shdr->sh_info;
	    if (*xndxscn != NULL)
	      return DWFL_E_NOERROR;
	    break;

	  case SHT_DYNSYM:
	    if (symtab)
	      break;
	    
	    *symscn = scn;
	    *symfile = file;
	    *strshndx = shdr->sh_link;
	    *syments = shdr->sh_size / shdr->sh_entsize;
	    break;

	  case SHT_SYMTAB_SHNDX:
	    *xndxscn = scn;
	    if (symtab)
	      return DWFL_E_NOERROR;
	    break;

	  default:
	    break;
	  }
    }

  if (symtab)
    
    return DWFL_E_NOERROR;

  *xndxscn = NULL;
  return DWFL_E_NO_SYMTAB;
}


static void
find_offsets (Elf *elf, size_t phnum, size_t n,
	      GElf_Addr addrs[n], GElf_Off offs[n])
{
  size_t unsolved = n;
  for (size_t i = 0; i < phnum; ++i)
    {
      GElf_Phdr phdr_mem;
      GElf_Phdr *phdr = gelf_getphdr (elf, i, &phdr_mem);
      if (phdr != NULL && phdr->p_type == PT_LOAD && phdr->p_memsz > 0)
	for (size_t j = 0; j < n; ++j)
	  if (offs[j] == 0
	      && addrs[j] >= phdr->p_vaddr
	      && addrs[j] - phdr->p_vaddr < phdr->p_filesz)
	    {
	      offs[j] = addrs[j] - phdr->p_vaddr + phdr->p_offset;
	      if (--unsolved == 0)
		break;
	    }
    }
}

static void
find_dynsym (Dwfl_Module *mod)
{
  GElf_Ehdr ehdr_mem;
  GElf_Ehdr *ehdr = gelf_getehdr (mod->main.elf, &ehdr_mem);

  size_t phnum;
  if (unlikely (elf_getphdrnum (mod->main.elf, &phnum) != 0))
    return;

  for (size_t i = 0; i < phnum; ++i)
    {
      GElf_Phdr phdr_mem;
      GElf_Phdr *phdr = gelf_getphdr (mod->main.elf, i, &phdr_mem);
      if (phdr == NULL)
	break;

      if (phdr->p_type == PT_DYNAMIC)
	{
	  

	  Elf_Data *data = elf_getdata_rawchunk (mod->main.elf,
						 phdr->p_offset, phdr->p_filesz,
						 ELF_T_DYN);
	  if (data == NULL)
	    continue;

	  enum
	    {
	      i_symtab,
	      i_strtab,
	      i_hash,
	      i_gnu_hash,
	      i_max
	    };
	  GElf_Addr addrs[i_max] = { 0, };
	  GElf_Xword strsz = 0;
	  size_t n = data->d_size / gelf_fsize (mod->main.elf,
						ELF_T_DYN, 1, EV_CURRENT);
	  for (size_t j = 0; j < n; ++j)
	    {
	      GElf_Dyn dyn_mem;
	      GElf_Dyn *dyn = gelf_getdyn (data, j, &dyn_mem);
	      if (dyn != NULL)
		switch (dyn->d_tag)
		  {
		  case DT_SYMTAB:
		    addrs[i_symtab] = dyn->d_un.d_ptr;
		    continue;

		  case DT_HASH:
		    addrs[i_hash] = dyn->d_un.d_ptr;
		    continue;

		  case DT_GNU_HASH:
		    addrs[i_gnu_hash] = dyn->d_un.d_ptr;
		    continue;

		  case DT_STRTAB:
		    addrs[i_strtab] = dyn->d_un.d_ptr;
		    continue;

		  case DT_STRSZ:
		    strsz = dyn->d_un.d_val;
		    continue;

		  default:
		    continue;

		  case DT_NULL:
		    break;
		  }
	      break;
	    }

	  
	  GElf_Off offs[i_max] = { 0, };
	  find_offsets (mod->main.elf, phnum, i_max, addrs, offs);

	  
	  if (offs[i_hash] != 0)
	    {
	      

	      size_t entsz = SH_ENTSIZE_HASH (ehdr);
	      data = elf_getdata_rawchunk (mod->main.elf,
					   offs[i_hash] + entsz, entsz,
					   entsz == 4 ? ELF_T_WORD
					   : ELF_T_XWORD);
	      if (data != NULL)
		mod->syments = (entsz == 4
				? *(const GElf_Word *) data->d_buf
				: *(const GElf_Xword *) data->d_buf);
	    }
	  if (offs[i_gnu_hash] != 0 && mod->syments == 0)
	    {
	      

	      const struct
	      {
		Elf32_Word nbuckets;
		Elf32_Word symndx;
		Elf32_Word maskwords;
		Elf32_Word shift2;
	      } *header;

	      data = elf_getdata_rawchunk (mod->main.elf, offs[i_gnu_hash],
					   sizeof *header, ELF_T_WORD);
	      if (data != NULL)
		{
		  header = data->d_buf;
		  Elf32_Word nbuckets = header->nbuckets;
		  Elf32_Word symndx = header->symndx;
		  GElf_Off buckets_at = (offs[i_gnu_hash] + sizeof *header
					 + (gelf_getclass (mod->main.elf)
					    * sizeof (Elf32_Word)
					    * header->maskwords));

		  data = elf_getdata_rawchunk (mod->main.elf, buckets_at,
					       nbuckets * sizeof (Elf32_Word),
					       ELF_T_WORD);
		  if (data != NULL && symndx < nbuckets)
		    {
		      const Elf32_Word *const buckets = data->d_buf;
		      Elf32_Word maxndx = symndx;
		      for (Elf32_Word bucket = 0; bucket < nbuckets; ++bucket)
			if (buckets[bucket] > maxndx)
			  maxndx = buckets[bucket];

		      GElf_Off hasharr_at = (buckets_at
					     + nbuckets * sizeof (Elf32_Word));
		      hasharr_at += (maxndx - symndx) * sizeof (Elf32_Word);
		      do
			{
			  data = elf_getdata_rawchunk (mod->main.elf,
						       hasharr_at,
						       sizeof (Elf32_Word),
						       ELF_T_WORD);
			  if (data != NULL
			      && (*(const Elf32_Word *) data->d_buf & 1u))
			    {
			      mod->syments = maxndx + 1;
			      break;
			    }
			  ++maxndx;
			  hasharr_at += sizeof (Elf32_Word);
			} while (data != NULL);
		    }
		}
	    }
	  if (offs[i_strtab] > offs[i_symtab] && mod->syments == 0)
	    mod->syments = ((offs[i_strtab] - offs[i_symtab])
			    / gelf_fsize (mod->main.elf,
					  ELF_T_SYM, 1, EV_CURRENT));

	  if (mod->syments > 0)
	    {
	      mod->symdata = elf_getdata_rawchunk (mod->main.elf,
						   offs[i_symtab],
						   gelf_fsize (mod->main.elf,
							       ELF_T_SYM,
							       mod->syments,
							       EV_CURRENT),
						   ELF_T_SYM);
	      if (mod->symdata != NULL)
		{
		  mod->symstrdata = elf_getdata_rawchunk (mod->main.elf,
							  offs[i_strtab],
							  strsz,
							  ELF_T_BYTE);
		  if (mod->symstrdata == NULL)
		    mod->symdata = NULL;
		}
	      if (mod->symdata == NULL)
		mod->symerr = DWFL_E (LIBELF, elf_errno ());
	      else
		{
		  mod->symfile = &mod->main;
		  mod->symerr = DWFL_E_NOERROR;
		}
	      return;
	    }
	}
    }
}

static void
find_symtab (Dwfl_Module *mod)
{
  if (mod->symdata != NULL	
      || mod->symerr != DWFL_E_NOERROR) 
    return;

  __libdwfl_getelf (mod);
  mod->symerr = mod->elferr;
  if (mod->symerr != DWFL_E_NOERROR)
    return;

  mod->first_global = -1; 

  
  Elf_Scn *symscn = NULL, *xndxscn = NULL;
  GElf_Word strshndx;
  mod->symerr = load_symtab (&mod->main, &mod->symfile, &symscn,
			     &xndxscn, &mod->syments, &mod->first_global,
			     &strshndx);
  switch (mod->symerr)
    {
    default:
      return;

    case DWFL_E_NOERROR:
      break;

    case DWFL_E_NO_SYMTAB:
      
      mod->symerr = find_debuginfo (mod);
      switch (mod->symerr)
	{
	default:
	  return;

	case DWFL_E_NOERROR:
	  mod->symerr = load_symtab (&mod->debug, &mod->symfile, &symscn,
				     &xndxscn, &mod->syments,
				     &mod->first_global, &strshndx);
	  break;

	case DWFL_E_CB:		
	  mod->symerr = DWFL_E_NO_SYMTAB;
	  break;
	}

      switch (mod->symerr)
	{
	default:
	  return;

	case DWFL_E_NOERROR:
	  break;

	case DWFL_E_NO_SYMTAB:
	  if (symscn != NULL)
	    {
	      
	      mod->symerr = DWFL_E_NOERROR;
	      break;
	    }

	  
	  find_dynsym (mod);
	  return;
	}
      break;
    }

  
  if (elf_strptr (mod->symfile->elf, strshndx, 0) == NULL)
    {
    elferr:
      mod->symerr = DWFL_E (LIBELF, elf_errno ());
      return;
    }

  

  mod->symstrdata = elf_getdata (elf_getscn (mod->symfile->elf, strshndx),
				 NULL);
  if (mod->symstrdata == NULL)
    goto elferr;

  if (xndxscn == NULL)
    mod->symxndxdata = NULL;
  else
    {
      mod->symxndxdata = elf_getdata (xndxscn, NULL);
      if (mod->symxndxdata == NULL)
	goto elferr;
    }

  mod->symdata = elf_getdata (symscn, NULL);
  if (mod->symdata == NULL)
    goto elferr;
}


Dwfl_Error
internal_function
__libdwfl_module_getebl (Dwfl_Module *mod)
{
  if (mod->ebl == NULL)
    {
      __libdwfl_getelf (mod);
      if (mod->elferr != DWFL_E_NOERROR)
	return mod->elferr;

      mod->ebl = ebl_openbackend (mod->main.elf);
      if (mod->ebl == NULL)
	return DWFL_E_LIBEBL;
    }
  return DWFL_E_NOERROR;
}

static Dwfl_Error
load_dw (Dwfl_Module *mod, struct dwfl_file *debugfile)
{
  if (mod->e_type == ET_REL && !debugfile->relocated)
    {
      const Dwfl_Callbacks *const cb = mod->dwfl->callbacks;

      
      if (cb->section_address == NULL)
	return DWFL_E_NOREL;

      Dwfl_Error error = __libdwfl_module_getebl (mod);
      if (error != DWFL_E_NOERROR)
	return error;

      find_symtab (mod);
      Dwfl_Error result = mod->symerr;
      if (result == DWFL_E_NOERROR)
	result = __libdwfl_relocate (mod, debugfile->elf, true);
      if (result != DWFL_E_NOERROR)
	return result;

      
      if (mod->main.fd != -1 && elf_cntl (mod->main.elf, ELF_C_FDREAD) == 0)
	{
	  close (mod->main.fd);
	  mod->main.fd = -1;
	}
      if (debugfile->fd != -1 && elf_cntl (debugfile->elf, ELF_C_FDREAD) == 0)
	{
	  close (debugfile->fd);
	  debugfile->fd = -1;
	}
    }

  mod->dw = INTUSE(dwarf_begin_elf) (debugfile->elf, DWARF_C_READ, NULL);
  if (mod->dw == NULL)
    {
      int err = INTUSE(dwarf_errno) ();
      return err == DWARF_E_NO_DWARF ? DWFL_E_NO_DWARF : DWFL_E (LIBDW, err);
    }

  
  mod->lazycu = 1;

  return DWFL_E_NOERROR;
}

static void
find_dw (Dwfl_Module *mod)
{
  if (mod->dw != NULL		
      || mod->dwerr != DWFL_E_NOERROR) 
    return;

  __libdwfl_getelf (mod);
  mod->dwerr = mod->elferr;
  if (mod->dwerr != DWFL_E_NOERROR)
    return;

  
  mod->dwerr = load_dw (mod, &mod->main);
  switch (mod->dwerr)
    {
    case DWFL_E_NOERROR:
      mod->debug.elf = mod->main.elf;
      mod->debug.address_sync = mod->main.address_sync;
      return;

    case DWFL_E_NO_DWARF:
      break;

    default:
      goto canonicalize;
    }

  
  mod->dwerr = find_debuginfo (mod);
  switch (mod->dwerr)
    {
    case DWFL_E_NOERROR:
      mod->dwerr = load_dw (mod, &mod->debug);
      break;

    case DWFL_E_CB:		
      mod->dwerr = DWFL_E_NO_DWARF;
      return;

    default:
      break;
    }

 canonicalize:
  mod->dwerr = __libdwfl_canon_error (mod->dwerr);
}

Dwarf *
dwfl_module_getdwarf (Dwfl_Module *mod, Dwarf_Addr *bias)
{
  if (mod == NULL)
    return NULL;

  find_dw (mod);
  if (mod->dwerr == DWFL_E_NOERROR)
    {
      if (mod->e_type == ET_REL
	  && mod->main.relocated && ! mod->debug.relocated)
	{
	  mod->debug.relocated = true;
	  if (mod->debug.elf != mod->main.elf)
	    (void) __libdwfl_relocate (mod, mod->debug.elf, false);
	}

      *bias = dwfl_adjusted_dwarf_addr (mod, 0);
      return mod->dw;
    }

  __libdwfl_seterrno (mod->dwerr);
  return NULL;
}
INTDEF (dwfl_module_getdwarf)

int
dwfl_module_getsymtab (Dwfl_Module *mod)
{
  if (mod == NULL)
    return -1;

  find_symtab (mod);
  if (mod->symerr == DWFL_E_NOERROR)
    return mod->syments;

  __libdwfl_seterrno (mod->symerr);
  return -1;
}
INTDEF (dwfl_module_getsymtab)
