// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_PUBLIC_TRANSIENT_WINDOW_CLIENT_H_
#define UI_WM_PUBLIC_TRANSIENT_WINDOW_CLIENT_H_

#include "base/basictypes.h"
#include "ui/aura/aura_export.h"

namespace aura {

class Window;

namespace client {

class AURA_EXPORT TransientWindowClient {
 public:
  virtual void AddTransientChild(Window* parent, Window* child) = 0;
  virtual void RemoveTransientChild(Window* parent, Window* child) = 0;
  virtual Window* GetTransientParent(Window* window) = 0;
  virtual const Window* GetTransientParent(const Window* window) = 0;

 protected:
  virtual ~TransientWindowClient() {}
};

AURA_EXPORT void SetTransientWindowClient(TransientWindowClient* client);
AURA_EXPORT TransientWindowClient* GetTransientWindowClient();

}  
}  

#endif  
