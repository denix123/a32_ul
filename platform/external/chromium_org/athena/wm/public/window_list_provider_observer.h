// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_WM_PUBLIC_WINDOW_LIST_PROVIDER_OBSERVER_H_
#define ATHENA_WM_PUBLIC_WINDOW_LIST_PROVIDER_OBSERVER_H_

#include "athena/athena_export.h"

namespace aura {
class Window;
}

namespace athena {

class ATHENA_EXPORT WindowListProviderObserver {
 public:
  virtual ~WindowListProviderObserver() {}

  
  virtual void OnWindowStackingChanged() = 0;

  
  
  virtual void OnWindowRemoved(aura::Window* removed_window,
                               int index) = 0;
};

}  

#endif  
