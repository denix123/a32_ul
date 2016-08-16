// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPT_INJECTION_H_
#define EXTENSIONS_RENDERER_SCRIPT_INJECTION_H_

#include "base/basictypes.h"
#include "base/macros.h"
#include "extensions/common/user_script.h"
#include "extensions/renderer/script_injector.h"

namespace blink {
class WebLocalFrame;
}

namespace extensions {
class Extension;
struct ScriptsRunInfo;

class ScriptInjection {
 public:
  
  static std::string GetExtensionIdForIsolatedWorld(int world_id);

  
  static void RemoveIsolatedWorld(const std::string& extension_id);

  ScriptInjection(scoped_ptr<ScriptInjector> injector,
                  blink::WebLocalFrame* web_frame,
                  const std::string& extension_id,
                  UserScript::RunLocation run_location,
                  int tab_id);
  ~ScriptInjection();

  
  
  
  
  
  bool TryToInject(UserScript::RunLocation current_location,
                   const Extension* extension,
                   ScriptsRunInfo* scripts_run_info);

  
  
  bool OnPermissionGranted(const Extension* extension,
                           ScriptsRunInfo* scripts_run_info);

  
  blink::WebLocalFrame* web_frame() const { return web_frame_; }
  const std::string& extension_id() const { return extension_id_; }
  int64 request_id() const { return request_id_; }

 private:
  
  void RequestPermission();

  
  void Inject(const Extension* extension, ScriptsRunInfo* scripts_run_info);

  
  
  void InjectJs(const Extension* extension,
                blink::WebLocalFrame* frame,
                base::ListValue* execution_results);

  
  void InjectCss(blink::WebLocalFrame* frame);

  
  void NotifyWillNotInject(ScriptInjector::InjectFailureReason reason);

  
  scoped_ptr<ScriptInjector> injector_;

  
  blink::WebLocalFrame* web_frame_;

  
  std::string extension_id_;

  
  UserScript::RunLocation run_location_;

  
  int tab_id_;

  
  
  int64 request_id_;

  
  
  bool complete_;

  DISALLOW_COPY_AND_ASSIGN(ScriptInjection);
};

}  

#endif  
