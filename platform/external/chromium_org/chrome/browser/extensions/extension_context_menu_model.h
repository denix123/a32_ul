// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_CONTEXT_MENU_MODEL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_CONTEXT_MENU_MODEL_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/extension_uninstall_dialog.h"
#include "ui/base/models/simple_menu_model.h"

class Browser;
class ExtensionAction;
class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
class ContextMenuMatcher;
class ExtensionContextMenuModelTest;
}

class ExtensionContextMenuModel
    : public base::RefCounted<ExtensionContextMenuModel>,
      public ui::SimpleMenuModel,
      public ui::SimpleMenuModel::Delegate,
      public extensions::ExtensionUninstallDialog::Delegate {
 public:
  enum MenuEntries {
    NAME = 0,
    CONFIGURE,
    TOGGLE_VISIBILITY,
    UNINSTALL,
    MANAGE,
    INSPECT_POPUP,
    ALWAYS_RUN
  };

  
  enum ActionType { NO_ACTION = 0, BROWSER_ACTION, PAGE_ACTION };

  
  class PopupDelegate {
   public:
    
    
    
    virtual void InspectPopup() = 0;

   protected:
    virtual ~PopupDelegate() {}
  };

  
  
  
  
  ExtensionContextMenuModel(const extensions::Extension* extension,
                            Browser* browser,
                            PopupDelegate* delegate);

  
  
  ExtensionContextMenuModel(const extensions::Extension* extension,
                            Browser* browser);

  
  virtual bool IsCommandIdChecked(int command_id) const OVERRIDE;
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;

  
  virtual void ExtensionUninstallAccepted() OVERRIDE;
  virtual void ExtensionUninstallCanceled() OVERRIDE;

 private:
  friend class base::RefCounted<ExtensionContextMenuModel>;
  friend class extensions::ExtensionContextMenuModelTest;

  virtual ~ExtensionContextMenuModel();

  void InitMenu(const extensions::Extension* extension);

  
  
  const extensions::Extension* GetExtension() const;

  
  content::WebContents* GetActiveWebContents() const;

  
  void AppendExtensionItems();

  
  std::string extension_id_;

  
  
  ExtensionAction* extension_action_;

  Browser* browser_;

  Profile* profile_;

  
  PopupDelegate* delegate_;

  
  ActionType action_type_;

  
  scoped_ptr<extensions::ExtensionUninstallDialog> extension_uninstall_dialog_;

  
  scoped_ptr<extensions::ContextMenuMatcher> extension_items_;

  
  int extension_items_count_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionContextMenuModel);
};

#endif  
