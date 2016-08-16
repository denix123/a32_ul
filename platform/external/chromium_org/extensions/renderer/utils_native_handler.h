// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_UTILS_NATIVE_HANDLER_H_
#define EXTENSIONS_RENDERER_UTILS_NATIVE_HANDLER_H_

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {
class ScriptContext;

class UtilsNativeHandler : public ObjectBackedNativeHandler {
 public:
  explicit UtilsNativeHandler(ScriptContext* context);
  virtual ~UtilsNativeHandler();

 private:
  
  
  
  void CreateClassWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  void DeepCopy(const v8::FunctionCallbackInfo<v8::Value>& args);

  DISALLOW_COPY_AND_ASSIGN(UtilsNativeHandler);
};

}  

#endif  
