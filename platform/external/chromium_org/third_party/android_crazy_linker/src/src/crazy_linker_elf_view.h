// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ELF_VIEW_H
#define CRAZY_LINKER_ELF_VIEW_H

#include <string.h>

#include "crazy_linker_error.h"
#include "elf_traits.h"

namespace crazy {

class Error;

class ElfView {
 public:
  ElfView() { ::memset(this, 0, sizeof(*this)); }

  ~ElfView() {}

  
  
  
  
  
  
  
  
  
  
  
  
  bool InitUnmapped(ELF::Addr load_address,
                    const ELF::Phdr* phdr,
                    size_t phdr_count,
                    Error* error);

  const ELF::Phdr* phdr() const { return phdr_; }
  size_t phdr_count() const { return phdr_count_; }
  const ELF::Dyn* dynamic() const { return dynamic_; }
  size_t dynamic_count() const { return dynamic_count_; }
  size_t dynamic_flags() const { return dynamic_flags_; }
  size_t load_address() const { return load_address_; }
  size_t load_size() const { return load_size_; }
  size_t load_bias() const { return load_bias_; }

  
  
  
  
  
  
  
  
  
  class DynamicIterator {
   public:
    DynamicIterator(const ElfView* view) {
      dyn_ = view->dynamic();
      dyn_limit_ = dyn_ + view->dynamic_count();
    }

    ~DynamicIterator() {}

    bool HasNext() const { return dyn_ < dyn_limit_; }
    void GetNext() { dyn_ += 1; }

    ELF::Addr GetTag() const { return dyn_->d_tag; }

    ELF::Addr GetValue() const { return dyn_->d_un.d_val; }

    ELF::Addr* GetValuePointer() const {
      return const_cast<ELF::Addr*>(&dyn_->d_un.d_ptr);
    }

    uintptr_t GetOffset() const { return dyn_->d_un.d_ptr; }

    uintptr_t GetAddress(size_t load_bias) const {
      return load_bias + dyn_->d_un.d_ptr;
    }

   private:
    const ELF::Dyn* dyn_;
    const ELF::Dyn* dyn_limit_;
  };

  
  
  bool ProtectRelroSection(Error* error);

 protected:
  const ELF::Phdr* phdr_;
  size_t phdr_count_;
  const ELF::Dyn* dynamic_;
  size_t dynamic_count_;
  ELF::Word dynamic_flags_;
  ELF::Addr load_address_;
  size_t load_size_;
  size_t load_bias_;
};

}  

#endif  
