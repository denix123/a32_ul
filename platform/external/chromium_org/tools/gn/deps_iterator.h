// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_DEPS_ITERATOR_H_
#define TOOLS_GN_DEPS_ITERATOR_H_

#include "base/basictypes.h"
#include "tools/gn/label_ptr.h"

class Target;

class DepsIterator {
 public:
  enum LinkedOnly {
    LINKED_ONLY,
  };

  
  explicit DepsIterator(const Target* t);

  
  DepsIterator(const Target* t, LinkedOnly);

  
  bool done() const {
    return !vect_stack_[0];
  }

  
  
  
  
  
  void Advance();

  
  const LabelTargetPair& pair() const {
    DCHECK_LT(current_index_, vect_stack_[0]->size());
    return (*vect_stack_[0])[current_index_];
  }

  
  const Target* target() const { return pair().ptr; }

  
  const Label& label() const { return pair().label; }

 private:
  const LabelTargetVector* vect_stack_[3];

  size_t current_index_;

  DISALLOW_COPY_AND_ASSIGN(DepsIterator);
};

#endif  
