// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MAC_SCOPED_MACH_VM_H_
#define BASE_MAC_SCOPED_MACH_VM_H_

#include <mach/mach.h>

#include <algorithm>

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/logging.h"


namespace base {
namespace mac {

class BASE_EXPORT ScopedMachVM {
 public:
  explicit ScopedMachVM(vm_address_t address = 0, vm_size_t size = 0)
      : address_(address),
        size_(size) {
    DCHECK(address % PAGE_SIZE == 0);
    DCHECK(size % PAGE_SIZE == 0);
  }

  ~ScopedMachVM() {
    if (size_) {
      vm_deallocate(mach_task_self(), address_, size_);
    }
  }

  void reset(vm_address_t address = 0, vm_size_t size = 0);

  vm_address_t address() const {
    return address_;
  }

  vm_size_t size() const {
    return size_;
  }

  void swap(ScopedMachVM& that) {
    std::swap(address_, that.address_);
    std::swap(size_, that.size_);
  }

  void release() {
    address_ = 0;
    size_ = 0;
  }

 private:
  vm_address_t address_;
  vm_size_t size_;

  DISALLOW_COPY_AND_ASSIGN(ScopedMachVM);
};

}  
}  

#endif  
