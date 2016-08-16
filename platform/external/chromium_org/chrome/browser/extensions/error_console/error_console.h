// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ERROR_CONSOLE_ERROR_CONSOLE_H_
#define CHROME_BROWSER_EXTENSIONS_ERROR_CONSOLE_ERROR_CONSOLE_H_

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "base/threading/thread_checker.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/error_map.h"
#include "extensions/browser/extension_error.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class NotificationDetails;
class NotificationSource;
class RenderViewHost;
}

class Profile;

namespace extensions {
class Extension;
class ExtensionPrefs;
class ExtensionRegistry;

class ErrorConsole : public content::NotificationObserver,
                     public ExtensionRegistryObserver {
 public:
  class Observer {
   public:
    
    virtual void OnErrorAdded(const ExtensionError* error) = 0;

    
    
    virtual void OnErrorConsoleDestroyed();
  };

  explicit ErrorConsole(Profile* profile);
  virtual ~ErrorConsole();

  
  static ErrorConsole* Get(Profile* profile);

  
  
  
  void SetReportingForExtension(const std::string& extension_id,
                                ExtensionError::Type type,
                                bool enabled);

  
  
  void SetReportingAllForExtension(const std::string& extension_id,
                                           bool enabled);

  
  
  bool IsReportingEnabledForExtension(const std::string& extension_id) const;

  
  void UseDefaultReportingForExtension(const std::string& extension_id);

  
  void ReportError(scoped_ptr<ExtensionError> error);

  
  
  const ErrorList& GetErrorsForExtension(const std::string& extension_id) const;

  
  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  
  
  
  bool IsEnabledForChromeExtensionsPage() const;
  bool IsEnabledForAppsDeveloperTools() const;

  
  bool enabled() const { return enabled_; }

  
  size_t get_num_entries_for_test() const { return errors_.size(); }

  
  void set_default_reporting_for_test(ExtensionError::Type type, bool enabled) {
    default_mask_ =
        enabled ? default_mask_ | (1 << type) : default_mask_ & ~(1 << type);
  }

 private:
  
  
  void CheckEnabled();

  
  
  void Enable();

  
  
  void Disable();

  
  
  
  void OnPrefChanged();

  
  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionInstalled(content::BrowserContext* browser_context,
                                    const Extension* extension,
                                    bool is_update) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  void AddManifestErrorsForExtension(const Extension* extension);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  int GetMaskForExtension(const std::string& extension_id) const;

  
  
  
  
  
  bool enabled_;

  
  base::ThreadChecker thread_checker_;

  
  ObserverList<Observer> observers_;

  
  ErrorMap errors_;

  
  int32 default_mask_;

  
  
  
  Profile* profile_;

  
  
  
  ExtensionPrefs* prefs_;

  content::NotificationRegistrar notification_registrar_;
  PrefChangeRegistrar pref_registrar_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(ErrorConsole);
};

}  

#endif  
