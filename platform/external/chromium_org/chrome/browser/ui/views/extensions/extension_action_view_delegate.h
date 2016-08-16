// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_ACTION_VIEW_DELEGATE_H_
#define CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_ACTION_VIEW_DELEGATE_H_

namespace content {
class WebContents;
}

namespace views {
class FocusManager;
class MenuButton;
class View;
class Widget;
}

class ExtensionActionViewController;

class ExtensionActionViewDelegate {
 public:
  
  
  virtual views::View* GetAsView() = 0;

  
  virtual bool IsShownInMenu() = 0;

  
  virtual views::FocusManager* GetFocusManagerForAccelerator() = 0;

  
  virtual views::Widget* GetParentForContextMenu() = 0;

  
  
  
  virtual ExtensionActionViewController* GetPreferredPopupViewController() = 0;

  
  virtual views::View* GetReferenceViewForPopup() = 0;

  
  
  virtual views::MenuButton* GetContextMenuButton() = 0;

  
  virtual content::WebContents* GetCurrentWebContents() = 0;

  
  virtual void HideActivePopup() = 0;

  
  virtual void OnIconUpdated() = 0;

  
  
  virtual void OnPopupShown(bool grant_tab_permissions) {}

  
  virtual void CleanupPopup() {}

 protected:
  virtual ~ExtensionActionViewDelegate() {}
};

#endif  
