// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_MANAGER_WIN_H_
#define CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_MANAGER_WIN_H_

#include <oleacc.h>

#include "base/memory/scoped_ptr.h"
#include "base/win/scoped_comptr.h"
#include "content/browser/accessibility/browser_accessibility_manager.h"

namespace content {
class BrowserAccessibilityWin;

class CONTENT_EXPORT BrowserAccessibilityManagerWin
    : public BrowserAccessibilityManager {
 public:
  BrowserAccessibilityManagerWin(
      const ui::AXTreeUpdate& initial_tree,
      BrowserAccessibilityDelegate* delegate,
      BrowserAccessibilityFactory* factory = new BrowserAccessibilityFactory());

  virtual ~BrowserAccessibilityManagerWin();

  static ui::AXTreeUpdate GetEmptyDocument();

  
  HWND GetParentHWND();

  
  IAccessible* GetParentIAccessible();

  
  void MaybeCallNotifyWinEvent(DWORD event, LONG child_id);

  
  virtual void OnNodeWillBeDeleted(ui::AXNode* node) OVERRIDE;
  virtual void OnNodeCreated(ui::AXNode* node) OVERRIDE;

  
  virtual void OnWindowFocused() OVERRIDE;
  virtual void NotifyAccessibilityEvent(
      ui::AXEvent event_type, BrowserAccessibility* node) OVERRIDE;

  
  
  
  void TrackScrollingObject(BrowserAccessibilityWin* node);

  
  
  BrowserAccessibilityWin* GetFromUniqueIdWin(LONG unique_id_win);

  
  void OnAccessibleHwndDeleted();

 protected:
  
  virtual void OnRootChanged(ui::AXNode* new_root) OVERRIDE;

 private:
  
  friend class BrowserAccessibilityManager;

  
  
  
  BrowserAccessibilityWin* tracked_scroll_object_;

  
  
  base::hash_map<long, int32> unique_id_to_ax_id_map_;

  
  
  bool focus_event_on_root_needed_;

  DISALLOW_COPY_AND_ASSIGN(BrowserAccessibilityManagerWin);
};

}  

#endif  
