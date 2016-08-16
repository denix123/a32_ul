// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_ACCESSIBILITY_AUTOMATION_MANAGER_ASH_H_
#define CHROME_BROWSER_UI_ASH_ACCESSIBILITY_AUTOMATION_MANAGER_ASH_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

#include "chrome/browser/extensions/api/automation_internal/automation_action_adapter.h"
#include "chrome/browser/ui/ash/accessibility/ax_tree_source_ash.h"
#include "ui/accessibility/ax_tree_serializer.h"

template <typename T> struct DefaultSingletonTraits;

namespace content {
class BrowserContext;
}  

namespace views {
class AXAuraObjWrapper;
class View;
}  

class AutomationManagerAsh : public extensions::AutomationActionAdapter {
 public:
  
  static AutomationManagerAsh* GetInstance();

  
  void Enable(content::BrowserContext* context);

  
  void Disable();

  
  void HandleEvent(content::BrowserContext* context,
                   views::View* view,
                   ui::AXEvent event_type);

  
  virtual void DoDefault(int32 id) OVERRIDE;
  virtual void Focus(int32 id) OVERRIDE;
  virtual void MakeVisible(int32 id) OVERRIDE;
  virtual void SetSelection(int32 id, int32 start, int32 end) OVERRIDE;

 protected:
  virtual ~AutomationManagerAsh();

 private:
  friend struct DefaultSingletonTraits<AutomationManagerAsh>;

  AutomationManagerAsh();

    
  void Reset();

  void SendEvent(content::BrowserContext* context,
                 views::AXAuraObjWrapper* aura_obj,
                 ui::AXEvent event_type);

  
  bool enabled_;

  
  
  
  scoped_ptr <AXTreeSourceAsh> current_tree_;

  
  
  scoped_ptr<ui::AXTreeSerializer<views::AXAuraObjWrapper*> >
      current_tree_serializer_;

  DISALLOW_COPY_AND_ASSIGN(AutomationManagerAsh);
};

#endif  
