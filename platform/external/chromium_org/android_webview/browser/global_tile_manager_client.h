// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_GLOBAL_TILE_MANAGER_CLIENT_H_
#define ANDROID_WEBVIEW_BROWSER_GLOBAL_TILE_MANAGER_CLIENT_H_

#include "content/public/browser/android/synchronous_compositor.h"

namespace android_webview {
class GlobalTileManagerClient {
 public:
  
  virtual content::SynchronousCompositorMemoryPolicy GetMemoryPolicy()
      const = 0;

  
  
  virtual void SetMemoryPolicy(
      content::SynchronousCompositorMemoryPolicy new_policy,
      bool effective_immediately) = 0;

 protected:
  virtual ~GlobalTileManagerClient() {}
};

}  

#endif  
