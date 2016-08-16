// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_LIBRARY_LIST_H
#define CRAZY_LINKER_LIBRARY_LIST_H

#include <link.h>

#include "crazy_linker_error.h"
#include "crazy_linker_search_path_list.h"
#include "elf_traits.h"


namespace crazy {

class SharedLibrary;
class LibraryView;

class LibraryList {
 public:
  LibraryList();
  ~LibraryList();

  
  
  LibraryView* FindLibraryByName(const char* base_name);

  
  
  
  void* FindSymbolFrom(const char* symbol_name, LibraryView* from_lib);

  
  
  void* FindAddressForSymbol(const char* symbol_name);

  
  
  LibraryView* FindLibraryForAddress(void* address);

#ifdef __arm__
  
  
  
  
  _Unwind_Ptr FindArmExIdx(void* pc, int* count);
#else
  typedef int (*PhdrIterationCallback)(dl_phdr_info* info,
                                       size_t info_size,
                                       void* data);

  
  
  
  
  int IteratePhdr(PhdrIterationCallback callback, void* data);
#endif

  
  
  LibraryView* LoadLibrary(const char* path,
                           int dlopen_flags,
                           uintptr_t load_address,
                           off_t file_offset,
                           SearchPathList* search_path_list,
                           Error* error);

  
  
  LibraryView* LoadLibraryInZipFile(const char* zip_file_path,
                                    const char* lib_name,
                                    int dlopen_flags,
                                    uintptr_t load_address,
                                    SearchPathList* search_path_list,
                                    Error* error);

  
  
  
  
  void UnloadLibrary(LibraryView* lib);

  
  void AddLibrary(LibraryView* lib);

 private:
  LibraryList(const LibraryList&);
  LibraryList& operator=(const LibraryList&);

  void ClearError();

  
  Vector<LibraryView*> known_libraries_;

  LibraryView* FindKnownLibrary(const char* name);

  
  
  SharedLibrary* head_;

  size_t count_;
  bool has_error_;
  char error_buffer_[512];
};

}  

#endif  
