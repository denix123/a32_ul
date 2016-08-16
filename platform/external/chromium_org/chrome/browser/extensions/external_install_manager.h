// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTERNAL_INSTALL_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTERNAL_INSTALL_MANAGER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class BrowserContext;
class NotificationDetails;
class NotificationSource;
}

namespace extensions {
class Extension;
class ExtensionRegistry;
class ExtensionPrefs;
class ExternalInstallError;

class ExternalInstallManager : public ExtensionRegistryObserver,
                               public content::NotificationObserver {
 public:
  ExternalInstallManager(content::BrowserContext* browser_context,
                         bool is_first_run);
  virtual ~ExternalInstallManager();

  
  void RemoveExternalInstallError();

  
  bool HasExternalInstallError() const;

  
  void UpdateExternalExtensionAlert();

  
  
  void AcknowledgeExternalExtension(const std::string& extension_id);

  
  
  bool HasExternalInstallBubbleForTesting() const;

  
  const ExternalInstallError* error() { return error_.get(); }

  
  ExternalInstallError* error_for_testing() { return error_.get(); }

 private:
  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionInstalled(content::BrowserContext* browser_context,
                                    const Extension* extension,
                                    bool is_update) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  
  void AddExternalInstallError(const Extension* extension, bool is_new_profile);

  
  
  bool IsUnacknowledgedExternalExtension(const Extension* extension) const;

  
  content::BrowserContext* browser_context_;

  
  bool is_first_run_;

  
  ExtensionPrefs* extension_prefs_;

  
  scoped_ptr<ExternalInstallError> error_;

  content::NotificationRegistrar registrar_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(ExternalInstallManager);
};

}  

#endif  
