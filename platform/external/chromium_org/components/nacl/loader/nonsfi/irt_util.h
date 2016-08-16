// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_LOADER_NONSFI_IRT_UTIL_H_
#define COMPONENTS_NACL_LOADER_NONSFI_IRT_UTIL_H_

#include <errno.h>

namespace nacl {
namespace nonsfi {

inline int CheckError(int result) {
  return result < 0 ? errno : 0;
}

template<typename T1, typename T2>
int CheckErrorWithResult(const T1& result, T2* out) {
  if (result < 0)
    return errno;

  *out = result;
  return 0;
}

}  
}  

#endif  
