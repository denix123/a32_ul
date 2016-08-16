// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_LIBRARY_VIEW_H
#define CRAZY_LINKER_LIBRARY_VIEW_H

#include "crazy_linker_error.h"
#include "crazy_linker_util.h"

namespace crazy {

class SharedLibrary;

class LibraryView {
 public:
  enum {
    TYPE_NONE = 0xbaadbaad,
    TYPE_SYSTEM = 0x2387cef,
    TYPE_CRAZY = 0xcdef2387,
  };

  LibraryView()
      : type_(TYPE_NONE), crazy_(NULL), system_(NULL), name_(), ref_count_(1) {}

  ~LibraryView();

  bool IsSystem() const { return type_ == TYPE_SYSTEM; }

  bool IsCrazy() const { return type_ == TYPE_CRAZY; }

  void SetSystem(void* system_lib, const char* name) {
    type_ = TYPE_SYSTEM;
    system_ = system_lib;
    name_ = name;
  }

  void SetCrazy(SharedLibrary* crazy_lib, const char* name) {
    type_ = TYPE_CRAZY;
    crazy_ = crazy_lib;
    name_ = name;
  }

  const char* GetName() { return name_.c_str(); }

  SharedLibrary* GetCrazy() { return IsCrazy() ? crazy_ : NULL; }

  void* GetSystem() { return IsSystem() ? system_ : NULL; }

  void AddRef() { ref_count_++; }

  
  
  bool SafeDecrementRef() { return (--ref_count_ == 0); }

  
  
  
  void* LookupSymbol(const char* symbol_name);

  
  bool GetInfo(size_t* load_address,
               size_t* load_size,
               size_t* relro_start,
               size_t* relro_size,
               Error* error);

  
  int ref_count() const { return ref_count_; }

 private:
  uint32_t type_;
  SharedLibrary* crazy_;
  void* system_;
  String name_;
  int ref_count_;
};

}  

#endif  
