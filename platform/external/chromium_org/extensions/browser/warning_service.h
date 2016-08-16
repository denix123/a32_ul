// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_WARNING_SERVICE_H_
#define EXTENSIONS_BROWSER_WARNING_SERVICE_H_

#include <set>
#include <string>
#include <vector>

#include "base/observer_list.h"
#include "base/scoped_observer.h"
#include "base/threading/non_thread_safe.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/warning_set.h"


namespace content {
class BrowserContext;
class NotificationDetails;
class NotificationSource;
}

namespace extensions {

class ExtensionRegistry;

class WarningService : public ExtensionRegistryObserver,
                       public base::NonThreadSafe {
 public:
  class Observer {
   public:
    virtual void ExtensionWarningsChanged() = 0;
  };

  
  
  explicit WarningService(content::BrowserContext* browser_context);
  virtual ~WarningService();

  
  
  void ClearWarnings(const std::set<Warning::WarningType>& types);

  
  std::set<Warning::WarningType> GetWarningTypesAffectingExtension(
      const std::string& extension_id) const;

  
  std::vector<std::string> GetWarningMessagesForExtension(
      const std::string& extension_id) const;

  const WarningSet& warnings() const { return warnings_; }

  
  void AddWarnings(const WarningSet& warnings);

  
  
  static void NotifyWarningsOnUI(void* profile_id, const WarningSet& warnings);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  void NotifyWarningsChanged();

  
  virtual void OnExtensionUnloaded(content::BrowserContext* browser_context,
                                   const Extension* extension,
                                   UnloadedExtensionInfo::Reason reason)
      OVERRIDE;

  
  WarningSet warnings_;

  content::BrowserContext* const browser_context_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  ObserverList<Observer> observer_list_;
};

}  

#endif  
