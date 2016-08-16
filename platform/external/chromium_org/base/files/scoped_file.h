// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_SCOPED_FILE_H_
#define BASE_FILES_SCOPED_FILE_H_

#include <stdio.h>

#include "base/base_export.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/scoped_generic.h"
#include "build/build_config.h"

namespace base {

namespace internal {

#if defined(OS_POSIX)
struct BASE_EXPORT ScopedFDCloseTraits {
  static int InvalidValue() {
    return -1;
  }
  static void Free(int fd);
};
#endif

struct ScopedFILECloser {
  inline void operator()(FILE* x) const {
    if (x)
      fclose(x);
  }
};

}  


#if defined(OS_POSIX)
typedef ScopedGeneric<int, internal::ScopedFDCloseTraits> ScopedFD;
#endif

typedef scoped_ptr<FILE, internal::ScopedFILECloser> ScopedFILE;

}  

#endif  
