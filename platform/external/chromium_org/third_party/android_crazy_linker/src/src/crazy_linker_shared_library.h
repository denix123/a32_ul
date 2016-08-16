// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_SHARED_LIBRARY_H
#define CRAZY_LINKER_SHARED_LIBRARY_H

#include <link.h>

#include "crazy_linker_elf_relro.h"
#include "crazy_linker_elf_symbols.h"
#include "crazy_linker_elf_view.h"
#include "crazy_linker_error.h"
#include "crazy_linker_rdebug.h"
#include "crazy_linker_util.h"
#include "elf_traits.h"

namespace crazy {

class LibraryList;
class LibraryView;



class SharedLibrary {
 public:
  SharedLibrary();
  ~SharedLibrary();

  size_t load_address() const { return view_.load_address(); }
  size_t load_size() const { return view_.load_size(); }
  size_t load_bias() const { return view_.load_bias(); }
  const ELF::Phdr* phdr() const { return view_.phdr(); }
  size_t phdr_count() const { return view_.phdr_count(); }
  const char* base_name() const { return base_name_; }

  
  
  
  
  
  
  
  
  
  
  bool Load(const char* full_path,
            size_t load_address,
            size_t file_offset,
            Error* error);

  
  
  
  bool Relocate(LibraryList* lib_list,
                Vector<LibraryView*>* dependencies,
                Error* error);

  void GetInfo(size_t* load_address,
               size_t* load_size,
               size_t* relro_start,
               size_t* relro_size) {
    *load_address = view_.load_address();
    *load_size = view_.load_size();
    *relro_start = relro_start_;
    *relro_size = relro_size_;
  }

  
  
  bool ContainsAddress(void* address) const {
    size_t addr = reinterpret_cast<size_t>(address);
    return load_address() <= addr && addr <= load_address() + load_size();
  }

  
  void CallConstructors();

  
  void CallDestructors();

  
  
  const ELF::Sym* LookupSymbolEntry(const char* symbol_name);

  
  
  
  bool FindNearestSymbolForAddress(void* address,
                                   const char** sym_name,
                                   void** sym_addr,
                                   size_t* sym_size) {
    return symbols_.LookupNearestByAddress(
        address, load_bias(), sym_name, sym_addr, sym_size);
  }

  
  
  void* FindAddressForSymbol(const char* symbol_name);

  
  
  
  
  
  
  bool CreateSharedRelro(size_t load_address,
                         size_t* relro_start,
                         size_t* relro_size,
                         int* relro_fd,
                         Error* error);

  
  
  
  bool UseSharedRelro(size_t relro_start,
                      size_t relro_size,
                      int relro_fd,
                      Error* error);

  
  
  
  
  
  bool SetJavaVM(void* java_vm, int minimum_jni_version, Error* error);

  
  
  
  void CallJniOnUnload();

  
  
  
  
  
  
  
  class DependencyIterator {
   public:
    DependencyIterator(SharedLibrary* lib)
        : iter_(&lib->view_), symbols_(&lib->symbols_), dep_name_(NULL) {}

    bool GetNext();

    const char* GetName() const { return dep_name_; }

   private:
    DependencyIterator();
    DependencyIterator(const DependencyIterator&);
    DependencyIterator& operator=(const DependencyIterator&);

    ElfView::DynamicIterator iter_;
    const ElfSymbols* symbols_;
    const char* dep_name_;
  };

  typedef void (*linker_function_t)();

 private:
  friend class LibraryList;

  ElfView view_;
  ElfSymbols symbols_;

  ELF::Addr relro_start_;
  ELF::Addr relro_size_;
  bool relro_used_;

  SharedLibrary* list_next_;
  SharedLibrary* list_prev_;
  unsigned flags_;

  linker_function_t* preinit_array_;
  size_t preinit_array_count_;
  linker_function_t* init_array_;
  size_t init_array_count_;
  linker_function_t* fini_array_;
  size_t fini_array_count_;
  linker_function_t init_func_;
  linker_function_t fini_func_;

#ifdef __arm__
  
  unsigned* arm_exidx_;
  size_t arm_exidx_count_;
#endif

#if defined(__arm__) || defined(__aarch64__)
  
  uint8_t* packed_relocations_;
#endif

  link_map_t link_map_;

  bool has_DT_SYMBOLIC_;

  void* java_vm_;

  const char* base_name_;
  char full_path_[512];
};

}  

#endif  
