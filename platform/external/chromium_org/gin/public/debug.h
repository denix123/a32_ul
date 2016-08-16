// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PUBLIC_DEBUG_H_
#define GIN_PUBLIC_DEBUG_H_

#include "gin/gin_export.h"
#include "v8/include/v8.h"

namespace gin {

class GIN_EXPORT Debug {
 public:
  static void SetFunctionEntryHook(v8::FunctionEntryHook entry_hook);

  static void SetJitCodeEventHandler(v8::JitCodeEventHandler event_handler);
};

}  

#endif  
