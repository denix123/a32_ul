// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_WINDOW_OBSERVER_H_
#define UI_AURA_WINDOW_OBSERVER_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "ui/aura/aura_export.h"

namespace gfx {
class Rect;
}  

namespace aura {

class Window;

class AURA_EXPORT WindowObserver {
 public:
  struct HierarchyChangeParams {
    enum HierarchyChangePhase {
      HIERARCHY_CHANGING,
      HIERARCHY_CHANGED
    };

    Window* target;     
    Window* new_parent;
    Window* old_parent;
    HierarchyChangePhase phase;
    Window* receiver;   
  };

  WindowObserver();

  
  
  
  
  
  
  
  
  
  
  virtual void OnWindowHierarchyChanging(const HierarchyChangeParams& params) {}
  virtual void OnWindowHierarchyChanged(const HierarchyChangeParams& params) {}

  
  virtual void OnWindowAdded(Window* new_window) {}

  
  virtual void OnWillRemoveWindow(Window* window) {}

  
  virtual void OnWindowParentChanged(Window* window, Window* parent) {}

  
  
  
  
  
  
  virtual void OnWindowPropertyChanged(Window* window,
                                       const void* key,
                                       intptr_t old) {}

  
  
  
  virtual void OnWindowVisibilityChanging(Window* window, bool visible) {}
  virtual void OnWindowVisibilityChanged(Window* window, bool visible) {}

  
  
  virtual void OnWindowBoundsChanged(Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) {}

  
  virtual void OnWindowTransforming(Window* window) {}
  virtual void OnWindowTransformed(Window* window) {}

  
  
  virtual void OnAncestorWindowTransformed(Window* source, Window* window) {}

  
  
  virtual void OnWindowStackingChanged(Window* window) {}

  
  virtual void OnDelegatedFrameDamage(Window* window,
                                      const gfx::Rect& damage_rect_in_dip) {}

  
  
  virtual void OnWindowDestroying(Window* window) {}

  
  
  
  
  
  
  
  
  virtual void OnWindowDestroyed(Window* window) {}

  
  virtual void OnWindowAddedToRootWindow(Window* window) {}

  
  
  
  virtual void OnWindowRemovingFromRootWindow(Window* window,
                                              Window* new_root) {}

  
  virtual void OnWindowTitleChanged(Window* window) {}

 protected:
  virtual ~WindowObserver();

 private:
  friend class Window;

  
  void OnObservingWindow(Window* window);

  
  void OnUnobservingWindow(Window* window);

  
  
  int observing_;

  DISALLOW_COPY_AND_ASSIGN(WindowObserver);
};

}  

#endif  
