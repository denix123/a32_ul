// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_SCRIPT_EXECUTION_OBSERVER_H_
#define EXTENSIONS_BROWSER_SCRIPT_EXECUTION_OBSERVER_H_

#include <map>
#include <set>
#include <string>

class GURL;

namespace content {
class WebContents;
}

namespace extensions {

class ScriptExecutionObserver {
 public:
  
  typedef std::map<std::string, std::set<std::string> > ExecutingScriptsMap;

  
  
  
  
  
  
  virtual void OnScriptsExecuted(
      const content::WebContents* web_contents,
      const ExecutingScriptsMap& executing_scripts_map,
      const GURL& on_url) = 0;

 protected:
  virtual ~ScriptExecutionObserver();
};

}  

#endif  
