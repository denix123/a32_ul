// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_STORAGE_MONITOR_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_STORAGE_MONITOR_H_

#include <set>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/extension_uninstall_dialog.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class BrowserContext;
}

namespace gfx {
class Image;
}

namespace extensions {

class Extension;
class ExtensionPrefs;
class ExtensionRegistry;
class StorageEventObserver;

class ExtensionStorageMonitor : public KeyedService,
                                public content::NotificationObserver,
                                public ExtensionRegistryObserver,
                                public ExtensionUninstallDialog::Delegate {
 public:
  static ExtensionStorageMonitor* Get(content::BrowserContext* context);

  
  enum ButtonIndex {
    BUTTON_DISABLE_NOTIFICATION = 0,
    BUTTON_UNINSTALL
  };

  explicit ExtensionStorageMonitor(content::BrowserContext* context);
  virtual ~ExtensionStorageMonitor();

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionWillBeInstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      bool is_update,
      bool from_ephemeral,
      const std::string& old_name) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void ExtensionUninstallAccepted() OVERRIDE;
  virtual void ExtensionUninstallCanceled() OVERRIDE;

  std::string GetNotificationId(const std::string& extension_id);

  void OnStorageThresholdExceeded(const std::string& extension_id,
                                  int64 next_threshold,
                                  int64 current_usage);
  void OnImageLoaded(const std::string& extension_id,
                     int64 current_usage,
                     const gfx::Image& image);
  void OnNotificationButtonClick(const std::string& extension_id,
                                 int button_index);

  void DisableStorageMonitoring(const std::string& extension_id);
  void StartMonitoringStorage(const Extension* extension);
  void StopMonitoringStorage(const std::string& extension_id);
  void StopMonitoringAll();

  void RemoveNotificationForExtension(const std::string& extension_id);
  void RemoveAllNotifications();

  
  void ShowUninstallPrompt(const std::string& extension_id);

  
  
  int64 GetNextStorageThreshold(const std::string& extension_id) const;
  void SetNextStorageThreshold(const std::string& extension_id,
                               int64 next_threshold);

  
  
  int64 GetNextStorageThresholdFromPrefs(const std::string& extension_id) const;

  
  
  bool IsStorageNotificationEnabled(const std::string& extension_id) const;
  void SetStorageNotificationEnabled(const std::string& extension_id,
                                     bool enable_notifications);

  
  
  bool enable_for_all_extensions_;

  
  
  
  int64 initial_extension_threshold_;
  int64 initial_ephemeral_threshold_;

  
  
  int observer_rate_;

  
  std::set<std::string> notified_extension_ids_;

  content::BrowserContext* context_;
  extensions::ExtensionPrefs* extension_prefs_;

  content::NotificationRegistrar registrar_;
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;

  
  scoped_refptr<StorageEventObserver> storage_observer_;

  
  scoped_ptr<ExtensionUninstallDialog> uninstall_dialog_;

  
  
  std::string uninstall_extension_id_;

  base::WeakPtrFactory<ExtensionStorageMonitor> weak_ptr_factory_;

  friend class StorageEventObserver;
  friend class ExtensionStorageMonitorTest;

  DISALLOW_COPY_AND_ASSIGN(ExtensionStorageMonitor);
};

}  

#endif  
