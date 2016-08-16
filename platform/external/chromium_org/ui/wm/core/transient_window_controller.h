// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_TRANSIENT_WINDOW_CONTROLLER_H_
#define UI_WM_CORE_TRANSIENT_WINDOW_CONTROLLER_H_

#include "ui/wm/public/transient_window_client.h"
#include "ui/wm/wm_export.h"

namespace wm {

class WM_EXPORT TransientWindowController
    : public aura::client::TransientWindowClient {
 public:
  TransientWindowController();
  virtual ~TransientWindowController();

  
  virtual void AddTransientChild(aura::Window* parent,
                                 aura::Window* child) OVERRIDE;
  virtual void RemoveTransientChild(aura::Window* parent,
                                    aura::Window* child) OVERRIDE;
  virtual aura::Window* GetTransientParent(aura::Window* window) OVERRIDE;
  virtual const aura::Window* GetTransientParent(
      const aura::Window* window) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(TransientWindowController);
};

}  

#endif  
