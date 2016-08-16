// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_ACCESSIBILITY_AX_WINDOW_OBJ_WRAPPER_H_
#define UI_VIEWS_ACCESSIBILITY_AX_WINDOW_OBJ_WRAPPER_H_

#include "ui/aura/window_observer.h"
#include "ui/views/accessibility/ax_aura_obj_wrapper.h"

namespace aura {
class Window;
}  

namespace views {

class AXWindowObjWrapper : public AXAuraObjWrapper,
                           public aura::WindowObserver {
 public:
  explicit AXWindowObjWrapper(aura::Window* window);
  virtual ~AXWindowObjWrapper();

  
  virtual AXAuraObjWrapper* GetParent() OVERRIDE;
  virtual void GetChildren(
      std::vector<AXAuraObjWrapper*>* out_children) OVERRIDE;
  virtual void Serialize(ui::AXNodeData* out_node_data) OVERRIDE;
  virtual int32 GetID() OVERRIDE;

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

 private:
  aura::Window* window_;

  DISALLOW_COPY_AND_ASSIGN(AXWindowObjWrapper);
};

}  

#endif  
