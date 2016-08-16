// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_CRITICAL_CLOSURE_H_
#define BASE_CRITICAL_CLOSURE_H_

#include "base/callback.h"

#if defined(OS_IOS)
#include "base/bind.h"
#include "base/ios/scoped_critical_action.h"
#endif

namespace base {

namespace internal {

#if defined(OS_IOS)
bool IsMultiTaskingSupported();

template <typename R>
class CriticalClosure {
 public:
  explicit CriticalClosure(const Callback<R(void)>& closure)
      : closure_(closure) {}

  ~CriticalClosure() {}

  R Run() {
    return closure_.Run();
  }

 private:
  ios::ScopedCriticalAction critical_action_;
  Callback<R(void)> closure_;

  DISALLOW_COPY_AND_ASSIGN(CriticalClosure);
};
#endif  

}  

#if defined(OS_IOS)
template <typename R>
Callback<R(void)> MakeCriticalClosure(const Callback<R(void)>& closure) {
  DCHECK(internal::IsMultiTaskingSupported());
  return base::Bind(&internal::CriticalClosure<R>::Run,
                    Owned(new internal::CriticalClosure<R>(closure)));
}
#else  
template <typename R>
inline Callback<R(void)> MakeCriticalClosure(const Callback<R(void)>& closure) {
  
  
  return closure;
}
#endif  

}  

#endif  
