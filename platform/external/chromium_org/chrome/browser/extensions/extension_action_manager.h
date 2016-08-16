// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_MANAGER_H_

#include <map>
#include <string>

#include "base/scoped_observer.h"
#include "chrome/common/extensions/api/extension_action/action_info.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/extension_registry_observer.h"

class ExtensionAction;
class Profile;

namespace extensions {

class Extension;
class ExtensionRegistry;

class ExtensionActionManager : public KeyedService,
                               public ExtensionRegistryObserver {
 public:
  explicit ExtensionActionManager(Profile* profile);
  virtual ~ExtensionActionManager();

  
  
  static ExtensionActionManager* Get(content::BrowserContext* browser_context);

  
  
  
  
  ExtensionAction* GetPageAction(const Extension& extension) const;
  ExtensionAction* GetBrowserAction(const Extension& extension) const;
  ExtensionAction* GetSystemIndicator(const Extension& extension) const;

  
  
  
  
  
  ExtensionAction* GetExtensionAction(const Extension& extension) const;

  
  
  
  scoped_ptr<ExtensionAction> GetBestFitAction(
      const Extension& extension, ActionInfo::Type type) const;

 private:
  
  virtual void OnExtensionUnloaded(content::BrowserContext* browser_context,
                                   const Extension* extension,
                                   UnloadedExtensionInfo::Reason reason)
      OVERRIDE;

  Profile* profile_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  
  
  
  
  typedef std::map<std::string, linked_ptr<ExtensionAction> > ExtIdToActionMap;
  mutable ExtIdToActionMap page_actions_;
  mutable ExtIdToActionMap browser_actions_;
  mutable ExtIdToActionMap system_indicators_;
};

}  

#endif  
