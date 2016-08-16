// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_APP_WINDOW_REGISTRY_UTIL_H_
#define CHROME_BROWSER_APPS_APP_WINDOW_REGISTRY_UTIL_H_

#include "ui/gfx/native_widget_types.h"

namespace extensions {
class AppWindow;
}

class AppWindowRegistryUtil {
 public:
  
  static extensions::AppWindow* GetAppWindowForNativeWindowAnyProfile(
      gfx::NativeWindow window);

  
  
  
  static bool IsAppWindowRegisteredInAnyProfile(int window_type_mask);

  
  static void CloseAllAppWindows();
};

#endif  
