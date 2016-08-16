// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_EXTENSION_APP_MODEL_BUILDER_H_
#define CHROME_BROWSER_UI_APP_LIST_EXTENSION_APP_MODEL_BUILDER_H_

#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/install_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "ui/app_list/app_list_model.h"
#include "ui/base/models/list_model_observer.h"

class AppListControllerDelegate;
class ExtensionAppItem;
class Profile;

namespace app_list {
class AppListSyncableService;
}

namespace extensions {
class Extension;
class ExtensionRegistry;
class ExtensionSet;
class InstallTracker;
}

namespace gfx {
class ImageSkia;
}

class ExtensionAppModelBuilder : public extensions::InstallObserver,
                                 public extensions::ExtensionRegistryObserver,
                                 public app_list::AppListItemListObserver {
 public:
  explicit ExtensionAppModelBuilder(AppListControllerDelegate* controller);
  virtual ~ExtensionAppModelBuilder();

  
  void InitializeWithService(app_list::AppListSyncableService* service);

  
  
  void InitializeWithProfile(Profile* profile, app_list::AppListModel* model);

 private:
  typedef std::vector<ExtensionAppItem*> ExtensionAppList;

  
  void BuildModel();

  
  virtual void OnBeginExtensionInstall(
      const ExtensionInstallParams& params) OVERRIDE;
  virtual void OnDownloadProgress(const std::string& extension_id,
                                  int percent_downloaded) OVERRIDE;
  virtual void OnInstallFailure(const std::string& extension_id) OVERRIDE;
  virtual void OnDisabledExtensionUpdated(
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnAppInstalledToAppList(
      const std::string& extension_id) OVERRIDE;
  virtual void OnShutdown() OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;
  virtual void OnShutdown(extensions::ExtensionRegistry* registry) OVERRIDE;

  
  virtual void OnListItemMoved(size_t from_index,
                               size_t to_index,
                               app_list::AppListItem* item) OVERRIDE;

  scoped_ptr<ExtensionAppItem> CreateAppItem(
      const std::string& extension_id,
      const std::string& extension_name,
      const gfx::ImageSkia& installing_icon,
      bool is_platform_app);

  
  void PopulateApps();

  
  void InsertApp(scoped_ptr<ExtensionAppItem> app);

  
  
  void SetHighlightedApp(const std::string& extension_id);

  
  
  
  
  void UpdateHighlight();

  
  ExtensionAppItem* GetExtensionAppItem(const std::string& extension_id);

  
  
  
  
  void InitializePrefChangeRegistrars();

  
  void OnProfilePreferenceChanged();

  
  void OnExtensionPreferenceChanged();

  
  app_list::AppListSyncableService* service_;
  Profile* profile_;

  
  PrefChangeRegistrar profile_pref_change_registrar_;

  
  PrefChangeRegistrar extension_pref_change_registrar_;

  
  AppListControllerDelegate* controller_;

  
  app_list::AppListModel* model_;

  std::string highlight_app_id_;

  
  
  bool highlighted_app_pending_;

  
  extensions::InstallTracker* tracker_;

  
  extensions::ExtensionRegistry* extension_registry_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionAppModelBuilder);
};

#endif  
