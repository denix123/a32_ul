// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPT_CONTEXT_H_
#define EXTENSIONS_RENDERER_SCRIPT_CONTEXT_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "extensions/common/features/feature.h"
#include "extensions/renderer/module_system.h"
#include "extensions/renderer/request_sender.h"
#include "extensions/renderer/safe_builtins.h"
#include "extensions/renderer/scoped_persistent.h"
#include "gin/runner.h"
#include "v8/include/v8.h"

namespace blink {
class WebFrame;
}

namespace content {
class RenderFrame;
class RenderView;
}

namespace extensions {
class Extension;

class ScriptContext : public RequestSender::Source, public gin::Runner {
 public:
  ScriptContext(const v8::Handle<v8::Context>& context,
                blink::WebFrame* frame,
                const Extension* extension,
                Feature::Context context_type,
                const Extension* effective_extension,
                Feature::Context effective_context_type);
  virtual ~ScriptContext();

  
  
  void Invalidate();

  
  
  bool is_valid() const { return !v8_context_.IsEmpty(); }

  v8::Handle<v8::Context> v8_context() const {
    return v8_context_.NewHandle(isolate());
  }

  const Extension* extension() const { return extension_.get(); }

  const Extension* effective_extension() const {
    return effective_extension_.get();
  }

  blink::WebFrame* web_frame() const { return web_frame_; }

  Feature::Context context_type() const { return context_type_; }

  Feature::Context effective_context_type() const {
    return effective_context_type_;
  }

  void set_module_system(scoped_ptr<ModuleSystem> module_system) {
    module_system_ = module_system.Pass();
  }

  ModuleSystem* module_system() { return module_system_.get(); }

  SafeBuiltins* safe_builtins() { return &safe_builtins_; }

  const SafeBuiltins* safe_builtins() const { return &safe_builtins_; }

  
  
  const std::string& GetExtensionID() const;

  
  
  content::RenderView* GetRenderView() const;

  
  
  content::RenderFrame* GetRenderFrame() const;

  
  
  
  
  v8::Local<v8::Value> CallFunction(v8::Handle<v8::Function> function,
                                    int argc,
                                    v8::Handle<v8::Value> argv[]) const;

  void DispatchEvent(const char* event_name, v8::Handle<v8::Array> args) const;

  
  void DispatchOnUnloadEvent();

  
  Feature::Availability GetAvailability(const std::string& api_name);

  
  std::string GetContextTypeDescription();

  
  std::string GetEffectiveContextTypeDescription();

  v8::Isolate* isolate() const { return isolate_; }

  
  GURL GetURL() const;

  
  
  
  bool IsAnyFeatureAvailableToContext(const extensions::Feature& api);

  
  
  
  static GURL GetDataSourceURLForFrame(const blink::WebFrame* frame);

  
  
  
  static GURL GetEffectiveDocumentURL(const blink::WebFrame* frame,
                                      const GURL& document_url,
                                      bool match_about_blank);

  
  virtual ScriptContext* GetContext() OVERRIDE;
  virtual void OnResponseReceived(const std::string& name,
                                  int request_id,
                                  bool success,
                                  const base::ListValue& response,
                                  const std::string& error) OVERRIDE;

  
  virtual void Run(const std::string& source,
                   const std::string& resource_name) OVERRIDE;
  virtual v8::Handle<v8::Value> Call(v8::Handle<v8::Function> function,
                                     v8::Handle<v8::Value> receiver,
                                     int argc,
                                     v8::Handle<v8::Value> argv[]) OVERRIDE;
  virtual gin::ContextHolder* GetContextHolder() OVERRIDE;

 protected:
  
  ScopedPersistent<v8::Context> v8_context_;

 private:
  
  
  blink::WebFrame* web_frame_;

  
  
  scoped_refptr<const Extension> extension_;

  
  Feature::Context context_type_;

  
  
  
  scoped_refptr<const Extension> effective_extension_;

  
  Feature::Context effective_context_type_;

  
  scoped_ptr<ModuleSystem> module_system_;

  
  SafeBuiltins safe_builtins_;

  v8::Isolate* isolate_;

  DISALLOW_COPY_AND_ASSIGN(ScriptContext);
};

}  

#endif  
