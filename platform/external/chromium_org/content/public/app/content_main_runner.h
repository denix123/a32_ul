// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_APP_CONTENT_MAIN_RUNNER_H_
#define CONTENT_PUBLIC_APP_CONTENT_MAIN_RUNNER_H_

#include "build/build_config.h"
#include "content/common/content_export.h"

namespace content {
struct ContentMainParams;

class CONTENT_EXPORT ContentMainRunner {
 public:
  virtual ~ContentMainRunner() {}

  
  static ContentMainRunner* Create();

  
  virtual int Initialize(const ContentMainParams& params) = 0;

  
  virtual int Run() = 0;

  
  virtual void Shutdown() = 0;
};

}  

#endif  
