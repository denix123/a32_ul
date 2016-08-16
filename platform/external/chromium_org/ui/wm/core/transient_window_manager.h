// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_TRANSIENT_WINDOW_MANAGER_H_
#define UI_WM_CORE_TRANSIENT_WINDOW_MANAGER_H_

#include <vector>

#include "base/observer_list.h"
#include "ui/aura/window_observer.h"
#include "ui/wm/wm_export.h"

namespace wm {

class TransientWindowObserver;

class WM_EXPORT TransientWindowManager : public aura::WindowObserver {
 public:
  typedef std::vector<aura::Window*> Windows;

  virtual ~TransientWindowManager();

  
  static TransientWindowManager* Get(aura::Window* window);

  
  
  static const TransientWindowManager* Get(const aura::Window* window);

  void AddObserver(TransientWindowObserver* observer);
  void RemoveObserver(TransientWindowObserver* observer);

  
  void AddTransientChild(aura::Window* child);
  void RemoveTransientChild(aura::Window* child);

  const Windows& transient_children() const { return transient_children_; }

  aura::Window* transient_parent() { return transient_parent_; }
  const aura::Window* transient_parent() const { return transient_parent_; }

  
  
  
  
  
  bool IsStackingTransient(const aura::Window* target) const;

 private:
  explicit TransientWindowManager(aura::Window* window);

  
  
  void RestackTransientDescendants();

  
  virtual void OnWindowParentChanged(aura::Window* window,
                                     aura::Window* parent) OVERRIDE;
  virtual void OnWindowVisibilityChanging(aura::Window* window,
                                          bool visible) OVERRIDE;
  virtual void OnWindowStackingChanged(aura::Window* window) OVERRIDE;
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  aura::Window* window_;
  aura::Window* transient_parent_;
  Windows transient_children_;

  
  
  aura::Window* stacking_target_;

  ObserverList<TransientWindowObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(TransientWindowManager);
};

}  

#endif  
