// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_PUBLIC_CPP_VIEW_MANAGER_VIEW_MANAGER_H_
#define MOJO_SERVICES_PUBLIC_CPP_VIEW_MANAGER_VIEW_MANAGER_H_

#include <string>
#include <vector>

#include "mojo/services/public/cpp/view_manager/types.h"
#include "mojo/services/public/interfaces/input_events/input_events.mojom.h"

namespace mojo {
class View;
class ViewManagerDelegate;
class WindowManagerDelegate;

class ViewManager {
 public:
  
  
  virtual void SetWindowManagerDelegate(
      WindowManagerDelegate* window_manager_delegate) = 0;

  
  
  virtual void DispatchEvent(View* target, EventPtr event) = 0;

  
  virtual const std::string& GetEmbedderURL() const = 0;

  
  virtual const std::vector<View*>& GetRoots() const = 0;

  
  virtual View* GetViewById(Id id) = 0;

 protected:
  virtual ~ViewManager() {}
};

}  

#endif  
