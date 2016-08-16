// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_USER_SCRIPT_SET_MANAGER_H_
#define EXTENSIONS_RENDERER_USER_SCRIPT_SET_MANAGER_H_

#include <map>
#include <set>
#include <string>

#include "base/memory/linked_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/observer_list.h"
#include "content/public/renderer/render_process_observer.h"
#include "extensions/common/extension.h"
#include "extensions/common/user_script.h"
#include "extensions/renderer/user_script_set.h"

namespace IPC {
class Message;
}

namespace blink {
class WebFrame;
}

namespace extensions {

class ExtensionSet;
class ScriptInjection;

class UserScriptSetManager : public content::RenderProcessObserver {
 public:
  
  
  class Observer {
   public:
    virtual void OnUserScriptsUpdated(
        const std::set<std::string>& changed_extensions,
        const std::vector<UserScript*>& scripts) = 0;
  };

  UserScriptSetManager(const ExtensionSet* extensions);

  virtual ~UserScriptSetManager();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  scoped_ptr<ScriptInjection> GetInjectionForDeclarativeScript(
      int script_id,
      blink::WebFrame* web_frame,
      int tab_id,
      const GURL& url,
      const Extension* extension);

  
  
  void GetAllInjections(ScopedVector<ScriptInjection>* injections,
                        blink::WebFrame* web_frame,
                        int tab_id,
                        UserScript::RunLocation run_location);

  
  
  void GetAllActiveExtensionIds(std::set<std::string>* ids) const;

  const UserScriptSet* static_scripts() const { return &static_scripts_; }

 private:
  
  typedef std::map<ExtensionId, linked_ptr<UserScriptSet> > UserScriptSetMap;

  
  virtual bool OnControlMessageReceived(const IPC::Message& message) OVERRIDE;

  UserScriptSet* GetProgrammaticScriptsByExtension(
      const ExtensionId& extensionId);

  
  void OnUpdateUserScripts(base::SharedMemoryHandle shared_memory,
                           const ExtensionId& extension_id,
                           const std::set<std::string>& changed_extensions);

  
  UserScriptSet static_scripts_;

  
  
  UserScriptSetMap programmatic_scripts_;

  
  const ExtensionSet* extensions_;

  
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(UserScriptSetManager);
};

}  

#endif  
