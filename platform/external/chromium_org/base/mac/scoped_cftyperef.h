// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MAC_SCOPED_CFTYPEREF_H_
#define BASE_MAC_SCOPED_CFTYPEREF_H_

#include <CoreFoundation/CoreFoundation.h>

#include "base/mac/scoped_typeref.h"

namespace base {


namespace internal {

struct ScopedCFTypeRefTraits {
  static void Retain(CFTypeRef object) {
    CFRetain(object);
  }
  static void Release(CFTypeRef object) {
    CFRelease(object);
  }
};

}  

template<typename CFT>
class ScopedCFTypeRef
    : public ScopedTypeRef<CFT, internal::ScopedCFTypeRefTraits> {
 public:
  typedef CFT element_type;

  explicit ScopedCFTypeRef(
      CFT object = NULL,
      base::scoped_policy::OwnershipPolicy policy = base::scoped_policy::ASSUME)
      : ScopedTypeRef<CFT,
                      internal::ScopedCFTypeRefTraits>(object, policy) {}

  ScopedCFTypeRef(const ScopedCFTypeRef<CFT>& that)
      : ScopedTypeRef<CFT, internal::ScopedCFTypeRefTraits>(that) {}
};

}  

#endif  
