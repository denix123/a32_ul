// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_CAPTURE_CONTROLLER_H_
#define UI_WM_CORE_CAPTURE_CONTROLLER_H_

#include <set>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/aura/client/capture_client.h"
#include "ui/aura/window_observer.h"
#include "ui/wm/wm_export.h"

namespace wm {

class WM_EXPORT CaptureController : public aura::client::CaptureClient {
 public:
  
  void Attach(aura::Window* root);

  
  void Detach(aura::Window* root);

  
  
  bool is_active() const { return !root_windows_.empty(); }

  
  virtual void SetCapture(aura::Window* window) OVERRIDE;
  virtual void ReleaseCapture(aura::Window* window) OVERRIDE;
  virtual aura::Window* GetCaptureWindow() OVERRIDE;
  virtual aura::Window* GetGlobalCaptureWindow() OVERRIDE;

 private:
  friend class ScopedCaptureClient;
  typedef std::set<aura::Window*> RootWindows;

  CaptureController();
  virtual ~CaptureController();

  
  aura::Window* capture_window_;

  
  RootWindows root_windows_;

  DISALLOW_COPY_AND_ASSIGN(CaptureController);
};

class WM_EXPORT ScopedCaptureClient : public aura::WindowObserver {
 public:
  explicit ScopedCaptureClient(aura::Window* root);
  virtual ~ScopedCaptureClient();

  
  static bool IsActive();

  aura::client::CaptureClient* capture_client() {
    return capture_controller_;
  }

  
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;

 private:
  
  void Shutdown();

  
  static CaptureController* capture_controller_;

  
  aura::Window* root_window_;

  DISALLOW_COPY_AND_ASSIGN(ScopedCaptureClient);
};

}  

#endif  
