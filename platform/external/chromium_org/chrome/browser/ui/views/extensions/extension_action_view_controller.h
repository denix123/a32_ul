// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_ACTION_VIEW_CONTROLLER_H_
#define CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_ACTION_VIEW_CONTROLLER_H_

#include "chrome/browser/extensions/extension_action_icon_factory.h"
#include "chrome/browser/extensions/extension_context_menu_model.h"
#include "chrome/browser/ui/views/extensions/extension_popup.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/gfx/image/image.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/widget/widget_observer.h"

class Browser;
class ExtensionAction;
class ExtensionActionViewDelegate;

namespace content {
class WebContents;
}

namespace extensions {
class Command;
class Extension;
}

namespace ui {
class Accelerator;
}

namespace views {
class MenuRunner;
class View;
class Widget;
}

class ExtensionActionViewController
    : public ExtensionActionIconFactory::Observer,
      public ExtensionContextMenuModel::PopupDelegate,
      public ui::AcceleratorTarget,
      public views::ContextMenuController,
      public views::WidgetObserver {
 public:
  ExtensionActionViewController(const extensions::Extension* extension,
                                Browser* browser,
                                ExtensionAction* extension_action,
                                ExtensionActionViewDelegate* delegate);
  virtual ~ExtensionActionViewController();

  
  virtual void InspectPopup() OVERRIDE;

  
  
  
  void ExecuteActionByUser();

  
  
  
  
  bool ExecuteAction(ExtensionPopup::ShowAction show_action,
                     bool grant_tab_permissions);

  
  void HidePopup();

  
  gfx::Image GetIcon(int tab_id);

  
  int GetCurrentTabId() const;

  
  
  void RegisterCommand();

  
  
  
  void UnregisterCommand(bool only_if_removed);

  const extensions::Extension* extension() const { return extension_; }
  Browser* browser() { return browser_; }
  ExtensionAction* extension_action() { return extension_action_; }
  const ExtensionAction* extension_action() const { return extension_action_; }
  ExtensionPopup* popup() { return popup_; }
  bool is_menu_running() const { return menu_runner_.get() != NULL; }

 private:
  
  virtual void OnIconUpdated() OVERRIDE;

  
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;
  virtual bool CanHandleAccelerators() const OVERRIDE;

  
  virtual void OnWidgetDestroying(views::Widget* widget) OVERRIDE;

  
  virtual void ShowContextMenuForView(views::View* source,
                                      const gfx::Point& point,
                                      ui::MenuSourceType source_type) OVERRIDE;

  
  void DoShowContextMenu(ui::MenuSourceType source_type);

  
  
  
  
  
  bool ShowPopupWithUrl(ExtensionPopup::ShowAction show_action,
                        const GURL& popup_url,
                        bool grant_tab_permissions);

  
  
  bool GetExtensionCommand(extensions::Command* command);

  
  
  
  
  bool CloseActiveMenuIfNeeded();

  
  
  
  void CleanupPopup(bool close_widget);

  
  const extensions::Extension* extension_;

  
  Browser* browser_;

  
  
  ExtensionAction* extension_action_;

  
  ExtensionActionViewDelegate* delegate_;

  
  
  
  
  ExtensionActionIconFactory icon_factory_;

  
  scoped_ptr<views::MenuRunner> menu_runner_;

  
  ExtensionPopup* popup_;

  
  
  scoped_ptr<ui::Accelerator> action_keybinding_;

  
  
  base::Closure followup_context_menu_task_;

  base::WeakPtrFactory<ExtensionActionViewController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionActionViewController);
};

#endif  
