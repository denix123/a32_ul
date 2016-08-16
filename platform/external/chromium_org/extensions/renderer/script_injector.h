// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPT_INJECTOR_H_
#define EXTENSIONS_RENDERER_SCRIPT_INJECTOR_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "extensions/common/permissions/permissions_data.h"
#include "extensions/common/user_script.h"
#include "third_party/WebKit/public/web/WebScriptSource.h"

class GURL;

namespace blink {
class WebFrame;
}

namespace extensions {
class Extension;
struct ScriptsRunInfo;

class ScriptInjector {
 public:
  
  enum InjectFailureReason {
    EXTENSION_REMOVED,  
    NOT_ALLOWED,        
    WONT_INJECT         
                        
  };

  virtual ~ScriptInjector() {}

  
  virtual UserScript::InjectionType script_type() const = 0;

  
  virtual bool ShouldExecuteInChildFrames() const = 0;

  
  virtual bool ShouldExecuteInMainWorld() const = 0;

  
  virtual bool IsUserGesture() const = 0;

  
  virtual bool ExpectsResults() const = 0;

  
  
  virtual bool ShouldInjectJs(UserScript::RunLocation run_location) const = 0;

  
  virtual bool ShouldInjectCss(UserScript::RunLocation run_location) const = 0;

  
  virtual PermissionsData::AccessType CanExecuteOnFrame(
      const Extension* extension,
      blink::WebFrame* web_frame,
      int tab_id,
      const GURL& top_url) const = 0;

  
  
  virtual std::vector<blink::WebScriptSource> GetJsSources(
      UserScript::RunLocation run_location) const = 0;

  
  
  virtual std::vector<std::string> GetCssSources(
      UserScript::RunLocation run_location) const = 0;

  
  
  virtual void OnInjectionComplete(
      scoped_ptr<base::ListValue> execution_results,
      ScriptsRunInfo* scripts_run_info,
      UserScript::RunLocation run_location) = 0;

  
  virtual void OnWillNotInject(InjectFailureReason reason) = 0;
};

}  

#endif  
