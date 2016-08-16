// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TOOLBAR_EXTENSION_TOOLBAR_MENU_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_TOOLBAR_EXTENSION_TOOLBAR_MENU_VIEW_H_

#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/ui/views/toolbar/browser_actions_container_observer.h"
#include "ui/views/view.h"

class Browser;
class BrowserActionsContainer;
class WrenchMenu;

class ExtensionToolbarMenuView : public views::View,
                                 public BrowserActionsContainerObserver {
 public:
  ExtensionToolbarMenuView(Browser* browser, WrenchMenu* wrench_menu);
  virtual ~ExtensionToolbarMenuView();

  
  
  
  bool ShouldShow();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual int GetHeightForWidth(int width) const OVERRIDE;
  virtual void Layout() OVERRIDE;

 private:
  
  virtual void OnBrowserActionDragDone() OVERRIDE;

  
  void CloseWrenchMenu();

  
  Browser* browser_;

  
  WrenchMenu* wrench_menu_;

  
  BrowserActionsContainer* container_;

  ScopedObserver<BrowserActionsContainer, BrowserActionsContainerObserver>
      browser_actions_container_observer_;

  base::WeakPtrFactory<ExtensionToolbarMenuView> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionToolbarMenuView);
};

#endif  
