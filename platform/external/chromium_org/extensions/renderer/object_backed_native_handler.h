// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_OBJECT_BACKED_NATIVE_HANDLER_H_
#define EXTENSIONS_RENDERER_OBJECT_BACKED_NATIVE_HANDLER_H_

#include <string>
#include <vector>

#include "base/bind.h"
#include "base/memory/linked_ptr.h"
#include "extensions/renderer/native_handler.h"
#include "extensions/renderer/scoped_persistent.h"
#include "v8/include/v8-util.h"
#include "v8/include/v8.h"

namespace extensions {
class ScriptContext;

class ObjectBackedNativeHandler : public NativeHandler {
 public:
  explicit ObjectBackedNativeHandler(ScriptContext* context);
  virtual ~ObjectBackedNativeHandler();

  
  
  virtual v8::Handle<v8::Object> NewInstance() OVERRIDE;

  v8::Isolate* GetIsolate() const;

 protected:
  typedef base::Callback<void(const v8::FunctionCallbackInfo<v8::Value>&)>
      HandlerFunction;

  
  
  
  void RouteFunction(const std::string& name,
                     const HandlerFunction& handler_function);

  ScriptContext* context() const { return context_; }

  virtual void Invalidate() OVERRIDE;

 private:
  
  
  static void Router(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef v8::PersistentValueVector<v8::Object> RouterData;
  RouterData router_data_;

  ScriptContext* context_;

  ScopedPersistent<v8::ObjectTemplate> object_template_;

  DISALLOW_COPY_AND_ASSIGN(ObjectBackedNativeHandler);
};

}  

#endif  
