// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_DEFAULT_ACTIVATION_CLIENT_H_
#define UI_WM_CORE_DEFAULT_ACTIVATION_CLIENT_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/observer_list.h"
#include "ui/aura/window_observer.h"
#include "ui/wm/public/activation_client.h"
#include "ui/wm/wm_export.h"

namespace aura {
namespace client {
class ActivationChangeObserver;
}
}

namespace wm {

class WM_EXPORT DefaultActivationClient : public aura::client::ActivationClient,
                                          public aura::WindowObserver {
 public:
  explicit DefaultActivationClient(aura::Window* root_window);

  
  virtual void AddObserver(
      aura::client::ActivationChangeObserver* observer) OVERRIDE;
  virtual void RemoveObserver(
      aura::client::ActivationChangeObserver* observer) OVERRIDE;
  virtual void ActivateWindow(aura::Window* window) OVERRIDE;
  virtual void DeactivateWindow(aura::Window* window) OVERRIDE;
  virtual aura::Window* GetActiveWindow() OVERRIDE;
  virtual aura::Window* GetActivatableWindow(aura::Window* window) OVERRIDE;
  virtual aura::Window* GetToplevelWindow(aura::Window* window) OVERRIDE;
  virtual bool CanActivateWindow(aura::Window* window) const OVERRIDE;

  
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;

 private:
  class Deleter;

  virtual ~DefaultActivationClient();
  void RemoveActiveWindow(aura::Window* window);

  
  
  
  
  std::vector<aura::Window*> active_windows_;

  
  aura::Window* last_active_;

  ObserverList<aura::client::ActivationChangeObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(DefaultActivationClient);
};

}  

#endif  
