// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MAC_SCOPED_OBJC_CLASS_SWIZZLER_H_
#define BASE_MAC_SCOPED_OBJC_CLASS_SWIZZLER_H_

#import <objc/runtime.h>

#include "base/base_export.h"
#include "base/macros.h"

namespace base {
namespace mac {

class BASE_EXPORT ScopedObjCClassSwizzler {
 public:
  
  
  ScopedObjCClassSwizzler(Class target, Class source, SEL selector);

  
  
  
  ScopedObjCClassSwizzler(Class target, SEL original, SEL alternate);

  ~ScopedObjCClassSwizzler();

  
  
  
  IMP GetOriginalImplementation();

 private:
  
  void Init(Class target, Class source, SEL original, SEL alternate);

  Method old_selector_impl_;
  Method new_selector_impl_;

  DISALLOW_COPY_AND_ASSIGN(ScopedObjCClassSwizzler);
};

}  
}  

#endif  
