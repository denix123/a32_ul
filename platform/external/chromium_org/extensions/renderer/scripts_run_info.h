// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPTS_RUN_INFO_H_
#define EXTENSIONS_RENDERER_SCRIPTS_RUN_INFO_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/timer/elapsed_timer.h"
#include "extensions/common/user_script.h"

namespace blink {
class WebFrame;
}

namespace extensions {

struct ScriptsRunInfo {
  
  typedef std::map<std::string, std::set<std::string> > ExecutingScriptsMap;

  ScriptsRunInfo();
  ~ScriptsRunInfo();

  
  size_t num_css;
  
  size_t num_js;
  
  ExecutingScriptsMap executing_scripts;
  
  base::ElapsedTimer timer;

  
  void LogRun(blink::WebFrame* web_frame, UserScript::RunLocation location);

 private:
  DISALLOW_COPY_AND_ASSIGN(ScriptsRunInfo);
};

}  

#endif  
