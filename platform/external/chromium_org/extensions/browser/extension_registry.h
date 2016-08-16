// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_REGISTRY_H_
#define EXTENSIONS_BROWSER_EXTENSION_REGISTRY_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/uninstall_reason.h"
#include "extensions/common/extension_set.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
class ExtensionRegistryObserver;

class ExtensionRegistry : public KeyedService {
 public:
  
  enum IncludeFlag {
    NONE        = 0,
    ENABLED     = 1 << 0,
    DISABLED    = 1 << 1,
    TERMINATED  = 1 << 2,
    BLACKLISTED = 1 << 3,
    EVERYTHING = (1 << 4) - 1,
  };

  explicit ExtensionRegistry(content::BrowserContext* browser_context);
  virtual ~ExtensionRegistry();

  
  static ExtensionRegistry* Get(content::BrowserContext* browser_context);

  content::BrowserContext* browser_context() const { return browser_context_; }

  
  
  const ExtensionSet& enabled_extensions() const {
    return enabled_extensions_;
  }
  const ExtensionSet& disabled_extensions() const {
    return disabled_extensions_;
  }
  const ExtensionSet& terminated_extensions() const {
    return terminated_extensions_;
  }
  const ExtensionSet& blacklisted_extensions() const {
    return blacklisted_extensions_;
  }

  
  
  scoped_ptr<ExtensionSet> GenerateInstalledExtensionsSet() const;

  
  void AddObserver(ExtensionRegistryObserver* observer);
  void RemoveObserver(ExtensionRegistryObserver* observer);

  
  
  void TriggerOnLoaded(const Extension* extension);

  
  
  void TriggerOnUnloaded(const Extension* extension,
                         UnloadedExtensionInfo::Reason reason);

  
  
  
  
  
  
  
  void TriggerOnWillBeInstalled(const Extension* extension,
                                bool is_update,
                                bool from_ephemeral,
                                const std::string& old_name);

  
  
  void TriggerOnInstalled(const Extension* extension,
                          bool is_update);

  
  
  void TriggerOnUninstalled(const Extension* extension, UninstallReason reason);

  
  
  
  
  
  
  const Extension* GetExtensionById(const std::string& id,
                                    int include_mask) const;

  
  
  
  
  
  bool AddEnabled(const scoped_refptr<const Extension>& extension);

  
  
  
  
  bool RemoveEnabled(const std::string& id);

  
  bool AddDisabled(const scoped_refptr<const Extension>& extension);
  bool RemoveDisabled(const std::string& id);

  
  bool AddTerminated(const scoped_refptr<const Extension>& extension);
  bool RemoveTerminated(const std::string& id);

  
  bool AddBlacklisted(const scoped_refptr<const Extension>& extension);
  bool RemoveBlacklisted(const std::string& id);

  
  void ClearAll();

  
  
  
  void SetDisabledModificationCallback(
      const ExtensionSet::ModificationCallback& callback);

  
  virtual void Shutdown() OVERRIDE;

 private:
  
  ExtensionSet enabled_extensions_;

  
  ExtensionSet disabled_extensions_;

  
  ExtensionSet terminated_extensions_;

  
  
  
  
  ExtensionSet blacklisted_extensions_;

  ObserverList<ExtensionRegistryObserver> observers_;

  content::BrowserContext* const browser_context_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionRegistry);
};

}  

#endif  
