// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ELF_RELOCATIONS_H
#define CRAZY_LINKER_ELF_RELOCATIONS_H

#include <string.h>
#include <unistd.h>

#include "elf_traits.h"

namespace crazy {

class ElfSymbols;
class ElfView;
class Error;

class ElfRelocations {
 public:
  ElfRelocations() { ::memset(this, 0, sizeof(*this)); }
  ~ElfRelocations() {}

  bool Init(const ElfView* view, Error* error);

  
  
  
  class SymbolResolver {
   public:
    SymbolResolver() {}
    ~SymbolResolver() {}
    virtual void* Lookup(const char* symbol_name) = 0;
  };

  
  
  
  
  
  bool ApplyAll(const ElfSymbols* symbols,
                SymbolResolver* resolver,
                Error* error);

#if defined(__arm__) || defined(__aarch64__)
  
  
  void RegisterPackedRelocations(uint8_t* packed_relocations);
#endif

  
  
  
  
  
  
  
  void CopyAndRelocate(size_t src_addr,
                       size_t dst_addr,
                       size_t map_addr,
                       size_t size);

 private:
  bool ResolveSymbol(unsigned rel_type,
                     unsigned rel_symbol,
                     const ElfSymbols* symbols,
                     SymbolResolver* resolver,
                     ELF::Addr reloc,
                     ELF::Addr* sym_addr,
                     Error* error);
  bool ApplyRelaReloc(const ELF::Rela* rela,
                      ELF::Addr sym_addr,
                      bool resolved,
                      Error* error);
  bool ApplyRelReloc(const ELF::Rel* rel,
                     ELF::Addr sym_addr,
                     bool resolved,
                     Error* error);
  bool ApplyRelaRelocs(const ELF::Rela* relocs,
                       size_t relocs_count,
                       const ElfSymbols* symbols,
                       SymbolResolver* resolver,
                       Error* error);
  bool ApplyRelRelocs(const ELF::Rel* relocs,
                      size_t relocs_count,
                      const ElfSymbols* symbols,
                      SymbolResolver* resolver,
                      Error* error);
  void AdjustRelocation(ELF::Word rel_type,
                        ELF::Addr src_reloc,
                        size_t dst_delta,
                        size_t map_delta);
  void RelocateRela(size_t src_addr,
                    size_t dst_addr,
                    size_t map_addr,
                    size_t size);
  void RelocateRel(size_t src_addr,
                   size_t dst_addr,
                   size_t map_addr,
                   size_t size);

#if defined(__arm__) || defined(__aarch64__)
  
  bool ApplyPackedRel(const uint8_t* packed_relocations, Error* error);
  bool ApplyPackedRela(const uint8_t* packed_relocations, Error* error);

  
  
  
  bool ApplyPackedRelocations(Error* error);
#endif

#if defined(__mips__)
  bool RelocateMipsGot(const ElfSymbols* symbols,
                       SymbolResolver* resolver,
                       Error* error);
#endif

  const ELF::Phdr* phdr_;
  size_t phdr_count_;
  size_t load_bias_;

  ELF::Addr relocations_type_;
  ELF::Addr plt_relocations_;
  size_t plt_relocations_size_;
  ELF::Addr* plt_got_;

  ELF::Addr relocations_;
  size_t relocations_size_;

#if defined(__mips__)
  
  ELF::Word mips_symtab_count_;
  ELF::Word mips_local_got_count_;
  ELF::Word mips_gotsym_;
#endif

#if defined(__arm__) || defined(__aarch64__)
  uint8_t* packed_relocations_;
#endif

  bool has_text_relocations_;
  bool has_symbolic_;
};

}  

#endif  
