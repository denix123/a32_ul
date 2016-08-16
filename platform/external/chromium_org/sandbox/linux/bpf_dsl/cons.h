// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_BPF_DSL_CONS_H_
#define SANDBOX_LINUX_BPF_DSL_CONS_H_

#include "base/memory/ref_counted.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

template <typename T>
class Cons : public base::RefCounted<Cons<T> > {
 public:
  
  
  typedef scoped_refptr<const Cons<T> > List;

  
  const T& head() const { return head_; }

  
  List tail() const { return tail_; }

  
  static List Make(const T& head, List tail) {
    return make_scoped_refptr(new const Cons<T>(head, tail));
  }

 private:
  Cons(const T& head, List tail) : head_(head), tail_(tail) {}
  virtual ~Cons() {}

  T head_;
  List tail_;

  friend class base::RefCounted<Cons<T> >;
  DISALLOW_COPY_AND_ASSIGN(Cons);
};

}  

#endif  
