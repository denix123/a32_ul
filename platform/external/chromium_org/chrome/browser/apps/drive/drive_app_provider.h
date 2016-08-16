// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_DRIVE_DRIVE_APP_PROVIDER_H_
#define CHROME_BROWSER_APPS_DRIVE_DRIVE_APP_PROVIDER_H_

#include <set>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/drive/drive_app_registry_observer.h"
#include "extensions/browser/extension_registry_observer.h"

namespace drive {
struct DriveAppInfo;
}

class BrowserContextKeyedServiceFactory;
class DriveAppConverter;
class DriveAppMapping;
class DriveServiceBridge;
class ExtensionService;
class Profile;

class DriveAppProvider : public drive::DriveAppRegistryObserver,
                         public extensions::ExtensionRegistryObserver {
 public:
  explicit DriveAppProvider(Profile* profile);
  virtual ~DriveAppProvider();

  
  static void AppendDependsOnFactories(
      std::set<BrowserContextKeyedServiceFactory*>* factories);

  void SetDriveServiceBridgeForTest(scoped_ptr<DriveServiceBridge> test_bridge);

 private:
  friend class DriveAppProviderTest;

  typedef std::set<std::string> IdSet;
  typedef std::vector<drive::DriveAppInfo> DriveAppInfos;

  
  
  void UpdateMappingAndExtensionSystem(const std::string& drive_app_id,
                                       const extensions::Extension* new_app,
                                       bool is_new_app_generated);

  
  void ProcessDeferredOnExtensionInstalled(const std::string drive_app_id,
                                           const std::string chrome_app_id);

  void SchedulePendingConverters();
  void OnLocalAppConverted(const DriveAppConverter* converter, bool success);

  bool IsMappedUrlAppUpToDate(const drive::DriveAppInfo& drive_app) const;

  void AddOrUpdateDriveApp(const drive::DriveAppInfo& drive_app);
  void ProcessRemovedDriveApp(const std::string& drive_app_id);

  
  virtual void OnDriveAppRegistryUpdated() OVERRIDE;

  
  virtual void OnExtensionInstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      bool is_update) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  Profile* profile_;

  scoped_ptr<DriveServiceBridge> service_bridge_;
  scoped_ptr<DriveAppMapping> mapping_;
  DriveAppInfos drive_apps_;

  
  ScopedVector<DriveAppConverter> pending_converters_;

  base::WeakPtrFactory<DriveAppProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DriveAppProvider);
};

#endif  
