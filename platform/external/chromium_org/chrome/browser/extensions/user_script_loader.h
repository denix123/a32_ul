// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_USER_SCRIPT_LOADER_H_
#define CHROME_BROWSER_EXTENSIONS_USER_SCRIPT_LOADER_H_

#include <map>
#include <set>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_set.h"
#include "extensions/common/user_script.h"

namespace base {
class SharedMemory;
}

namespace content {
class BrowserContext;
class RenderProcessHost;
}

class Profile;

namespace extensions {

class ContentVerifier;
class ExtensionRegistry;

typedef std::map<ExtensionId, ExtensionSet::ExtensionPathAndDefaultLocale>
    ExtensionsInfo;

class UserScriptLoader : public content::NotificationObserver,
                         public ExtensionRegistryObserver {
 public:
  
  static bool ParseMetadataHeader(const base::StringPiece& script_text,
                                  UserScript* script);

  
  
  static void LoadScriptsForTest(UserScriptList* user_scripts);

  UserScriptLoader(Profile* profile,
                   const ExtensionId& owner_extension_id,
                   bool listen_for_extension_system_loaded);
  virtual ~UserScriptLoader();

  
  void AddScripts(const std::set<UserScript>& scripts);

  
  void RemoveScripts(const std::set<UserScript>& scripts);

  
  void ClearScripts();

  
  void StartLoad();

  
  bool scripts_ready() const { return shared_memory_.get() != NULL; }

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  
  void OnExtensionSystemReady();

  
  
  
  bool ScriptsMayHaveChanged() const;

  
  void AttemptLoad();

  
  void OnScriptsLoaded(scoped_ptr<UserScriptList> user_scripts,
                       scoped_ptr<base::SharedMemory> shared_memory);

  
  
  
  
  void SendUpdate(content::RenderProcessHost* process,
                  base::SharedMemory* shared_memory,
                  const std::set<ExtensionId>& changed_extensions);

  
  void ExpandChangedExtensions(const std::set<UserScript>& scripts);

  
  
  void UpdateExtensionsInfo();

  bool is_loading() const {
    
    return user_scripts_.get() == NULL;
  }

  
  content::NotificationRegistrar registrar_;

  
  scoped_ptr<base::SharedMemory> shared_memory_;

  
  scoped_ptr<UserScriptList> user_scripts_;

  
  ExtensionsInfo extensions_info_;

  
  
  std::set<UserScript> added_scripts_;
  std::set<UserScript> removed_scripts_;

  
  
  bool clear_scripts_;

  
  
  ExtensionIdSet changed_extensions_;

  
  
  bool extension_system_ready_;

  
  
  
  bool pending_load_;

  
  bool is_loading_;

  
  Profile* profile_;

  
  
  ExtensionId owner_extension_id_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  base::WeakPtrFactory<UserScriptLoader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserScriptLoader);
};

}  

#endif  
