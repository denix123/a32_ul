// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_WM_PUBLIC_WINDOW_LIST_PROVIDER_H_
#define ATHENA_WM_PUBLIC_WINDOW_LIST_PROVIDER_H_

#include "athena/athena_export.h"
#include "ui/aura/window.h"

namespace athena {

class WindowListProviderObserver;

class ATHENA_EXPORT WindowListProvider {
 public:
  virtual ~WindowListProvider() {}

  
  virtual void AddObserver(WindowListProviderObserver* observer) = 0;
  virtual void RemoveObserver(WindowListProviderObserver* observer) = 0;

  
  virtual const aura::Window::Windows& GetWindowList() const = 0;

  
  virtual bool IsWindowInList(aura::Window* window) const = 0;

  
  
  virtual bool IsValidWindow(aura::Window* window) const = 0;

  
  
  virtual void StackWindowFrontOf(aura::Window* window,
                                  aura::Window* reference_window) = 0;

  
  
  virtual void StackWindowBehindTo(aura::Window* window,
                                   aura::Window* reference_window) = 0;
};

}  

#endif  
