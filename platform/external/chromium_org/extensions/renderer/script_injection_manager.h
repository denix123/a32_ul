// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPT_INJECTION_MANAGER_H_
#define EXTENSIONS_RENDERER_SCRIPT_INJECTION_MANAGER_H_

#include <map>
#include <set>
#include <string>

#include "base/callback.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/shared_memory.h"
#include "base/scoped_observer.h"
#include "extensions/common/user_script.h"
#include "extensions/renderer/script_injection.h"
#include "extensions/renderer/user_script_set_manager.h"

struct ExtensionMsg_ExecuteCode_Params;

namespace blink {
class WebFrame;
class WebLocalFrame;
}

namespace content {
class RenderView;
}

namespace extensions {
class Extension;
class ExtensionSet;

class ScriptInjectionManager : public UserScriptSetManager::Observer {
 public:
  ScriptInjectionManager(const ExtensionSet* extensions,
                         UserScriptSetManager* user_script_set_manager);
  virtual ~ScriptInjectionManager();

  
  void OnRenderViewCreated(content::RenderView* render_view);

 private:
  
  
  
  class RVOHelper;

  typedef std::map<blink::WebFrame*, UserScript::RunLocation> FrameStatusMap;

  
  virtual void OnUserScriptsUpdated(
      const std::set<std::string>& changed_extensions,
      const std::vector<UserScript*>& scripts) OVERRIDE;

  
  void RemoveObserver(RVOHelper* helper);

  
  void InvalidateForFrame(blink::WebFrame* frame);

  
  void InjectScripts(blink::WebFrame* frame,
                     UserScript::RunLocation run_location);

  
  void HandleExecuteCode(const ExtensionMsg_ExecuteCode_Params& params,
                         content::RenderView* render_view);

  
  void HandleExecuteDeclarativeScript(blink::WebFrame* web_frame,
                                      int tab_id,
                                      const ExtensionId& extension_id,
                                      int script_id,
                                      const GURL& url);

  
  void HandlePermitScriptInjection(int64 request_id);

  
  const ExtensionSet* extensions_;

  
  
  FrameStatusMap frame_statuses_;

  
  ScopedVector<RVOHelper> rvo_helpers_;

  
  UserScriptSetManager* user_script_set_manager_;

  
  
  ScopedVector<ScriptInjection> pending_injections_;

  ScopedObserver<UserScriptSetManager, UserScriptSetManager::Observer>
      user_script_set_manager_observer_;

  DISALLOW_COPY_AND_ASSIGN(ScriptInjectionManager);
};

}  

#endif  
