// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_DECLARATIVE_USER_SCRIPT_MASTER_H_
#define CHROME_BROWSER_EXTENSIONS_DECLARATIVE_USER_SCRIPT_MASTER_H_

#include "base/scoped_observer.h"
#include "chrome/browser/extensions/user_script_loader.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension.h"

class Profile;

namespace extensions {

class ExtensionRegistry;
class UserScript;

class DeclarativeUserScriptMaster : public ExtensionRegistryObserver {
 public:
  DeclarativeUserScriptMaster(Profile* profile,
                              const ExtensionId& extension_id);
  virtual ~DeclarativeUserScriptMaster();

  
  
  void AddScript(const UserScript& script);

  
  
  void RemoveScript(const UserScript& script);

  
  
  void ClearScripts();

  const ExtensionId& extension_id() const { return extension_id_; }

 private:
  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  ExtensionId extension_id_;

  
  
  UserScriptLoader loader_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(DeclarativeUserScriptMaster);
};

}  

#endif  
