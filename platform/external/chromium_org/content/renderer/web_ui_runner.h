// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_WEB_UI_RUNNER_H_
#define CONTENT_RENDERER_WEB_UI_RUNNER_H_

#include "gin/runner.h"

namespace blink {
class WebFrame;
}

namespace content {

class WebUIRunner : public gin::Runner {
 public:
  
  WebUIRunner(blink::WebFrame* frame, gin::ContextHolder* context_holder);
  virtual ~WebUIRunner();

  void RegisterBuiltinModules();

  
  virtual void Run(const std::string& source,
                   const std::string& resource_name) OVERRIDE;
  virtual v8::Handle<v8::Value> Call(v8::Handle<v8::Function> function,
                                     v8::Handle<v8::Value> receiver,
                                     int argc,
                                     v8::Handle<v8::Value> argv[]) OVERRIDE;
  virtual gin::ContextHolder* GetContextHolder() OVERRIDE;

 private:
  
  blink::WebFrame* frame_;

  
  gin::ContextHolder* context_holder_;

  DISALLOW_COPY_AND_ASSIGN(WebUIRunner);
};

}  

#endif  
