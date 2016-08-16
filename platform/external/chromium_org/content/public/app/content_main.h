// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_APP_CONTENT_MAIN_H_
#define CONTENT_PUBLIC_APP_CONTENT_MAIN_H_

#include <stddef.h>

#include "base/callback_forward.h"
#include "build/build_config.h"
#include "content/common/content_export.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace sandbox {
struct SandboxInterfaceInfo;
}

namespace content {
class ContentMainDelegate;

struct ContentMainParams {
  explicit ContentMainParams(ContentMainDelegate* delegate)
      : delegate(delegate),
#if defined(OS_WIN)
        instance(NULL),
        sandbox_info(NULL),
#elif !defined(OS_ANDROID)
        argc(0),
        argv(NULL),
#endif
        ui_task(NULL) {
  }

  ContentMainDelegate* delegate;

#if defined(OS_WIN)
  HINSTANCE instance;

  
  
  sandbox::SandboxInterfaceInfo* sandbox_info;
#elif !defined(OS_ANDROID)
  int argc;
  const char** argv;
#endif

  
  
  base::Closure* ui_task;
};

#if defined(OS_ANDROID)
CONTENT_EXPORT void SetContentMainDelegate(ContentMainDelegate* delegate);
#else
CONTENT_EXPORT int ContentMain(const ContentMainParams& params);
#endif

}  

#endif  
