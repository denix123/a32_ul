// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_SHARED_PTR_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_SHARED_PTR_H_

#include "mojo/public/cpp/bindings/lib/shared_data.h"

namespace mojo {
namespace internal {

template <typename P>
class SharedPtr {
 public:
  SharedPtr() {}

  explicit SharedPtr(P* ptr) {
    impl_.mutable_value()->ptr = ptr;
  }

  

  P* get() {
    return impl_.value().ptr;
  }
  const P* get() const {
    return impl_.value().ptr;
  }

  P* operator->() { return get(); }
  const P* operator->() const { return get(); }

 private:
  class Impl {
   public:
    ~Impl() {
      if (ptr)
        delete ptr;
    }

    Impl() : ptr(NULL) {
    }

    Impl(P* ptr) : ptr(ptr) {
    }

    P* ptr;

   private:
    MOJO_DISALLOW_COPY_AND_ASSIGN(Impl);
  };

  SharedData<Impl> impl_;
};

}  
}  

#endif  
