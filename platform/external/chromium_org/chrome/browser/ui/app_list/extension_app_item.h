// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_EXTENSION_APP_ITEM_H_
#define CHROME_BROWSER_UI_APP_LIST_EXTENSION_APP_ITEM_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/app_list/app_context_menu_delegate.h"
#include "chrome/browser/ui/app_list/app_list_syncable_service.h"
#include "chrome/browser/ui/extensions/extension_enable_flow_delegate.h"
#include "extensions/browser/extension_icon_image.h"
#include "ui/app_list/app_list_item.h"
#include "ui/gfx/image/image_skia.h"

class AppListControllerDelegate;
class ExtensionEnableFlow;
class Profile;

namespace app_list {
class AppContextMenu;
}

namespace extensions {
class ContextMenuMatcher;
class Extension;
}

class ExtensionAppItem : public app_list::AppListItem,
                         public extensions::IconImage::Observer,
                         public ExtensionEnableFlowDelegate,
                         public app_list::AppContextMenuDelegate {
 public:
  static const char kItemType[];

  ExtensionAppItem(Profile* profile,
                   const app_list::AppListSyncableService::SyncItem* sync_item,
                   const std::string& extension_id,
                   const std::string& extension_name,
                   const gfx::ImageSkia& installing_icon,
                   bool is_platform_app);
  virtual ~ExtensionAppItem();

  
  void Reload();

  
  
  void UpdateIcon();

  
  
  
  void Move(const ExtensionAppItem* prev, const ExtensionAppItem* next);

  const std::string& extension_id() const { return extension_id_; }
  const std::string& extension_name() const { return extension_name_; }

 private:
  
  
  const extensions::Extension* GetExtension() const;

  
  void LoadImage(const extensions::Extension* extension);

  
  
  
  bool RunExtensionEnableFlow();

  
  void Launch(int event_flags);

  
  bool NeedsOverlay() const;

  
  virtual void OnExtensionIconImageChanged(
      extensions::IconImage* image) OVERRIDE;

  
  virtual void ExtensionEnableFlowFinished() OVERRIDE;
  virtual void ExtensionEnableFlowAborted(bool user_initiated) OVERRIDE;

  
  virtual void Activate(int event_flags) OVERRIDE;
  virtual ui::MenuModel* GetContextMenuModel() OVERRIDE;
  
  virtual void OnExtensionPreferenceChanged() OVERRIDE;
  virtual const char* GetItemType() const OVERRIDE;

  
  virtual void ExecuteLaunchCommand(int event_flags) OVERRIDE;

  
  void UpdatePositionFromExtensionOrdering();

  
  AppListControllerDelegate* GetController();

  Profile* profile_;
  const std::string extension_id_;

  scoped_ptr<extensions::IconImage> icon_;
  scoped_ptr<app_list::AppContextMenu> context_menu_;
  scoped_ptr<ExtensionEnableFlow> extension_enable_flow_;
  AppListControllerDelegate* extension_enable_flow_controller_;

  
  std::string extension_name_;

  
  gfx::ImageSkia installing_icon_;

  
  bool is_platform_app_;

  
  bool has_overlay_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionAppItem);
};

#endif  
