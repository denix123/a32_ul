// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_SCRIPT_EXECUTOR_H_
#define EXTENSIONS_BROWSER_SCRIPT_EXECUTOR_H_

#include "base/callback_forward.h"
#include "base/observer_list.h"
#include "extensions/common/user_script.h"

class GURL;
struct ExtensionMsg_ExecuteCode_Params;

namespace base {
class ListValue;
}  

namespace content {
class WebContents;
}

namespace extensions {
class ScriptExecutionObserver;

class ScriptExecutor {
 public:
  ScriptExecutor(
      content::WebContents* web_contents,
      
      
      ObserverList<ScriptExecutionObserver>* script_observers);

  ~ScriptExecutor();

  
  enum ScriptType {
    JAVASCRIPT,
    CSS,
  };

  
  enum FrameScope {
    TOP_FRAME,
    ALL_FRAMES,
  };

  
  
  enum MatchAboutBlank {
    DONT_MATCH_ABOUT_BLANK,
    MATCH_ABOUT_BLANK,
  };

  
  enum WorldType {
    MAIN_WORLD,
    ISOLATED_WORLD,
  };

  
  enum ProcessType {
    DEFAULT_PROCESS,
    WEB_VIEW_PROCESS,
  };

  
  enum ResultType {
    NO_RESULT,
    JSON_SERIALIZED_RESULT,
  };

  
  
  typedef base::Callback<
      void(const std::string&, const GURL&, const base::ListValue&)>
      ExecuteScriptCallback;

  
  
  
  
  
  
  void ExecuteScript(const std::string& extension_id,
                     ScriptType script_type,
                     const std::string& code,
                     FrameScope frame_scope,
                     MatchAboutBlank match_about_blank,
                     UserScript::RunLocation run_at,
                     WorldType world_type,
                     ProcessType process_type,
                     const GURL& webview_src,
                     const GURL& file_url,
                     bool user_gesture,
                     ResultType result_type,
                     const ExecuteScriptCallback& callback);

 private:
  
  int next_request_id_;

  content::WebContents* web_contents_;

  ObserverList<ScriptExecutionObserver>* script_observers_;
};

}  

#endif  
