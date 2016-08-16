// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_API_DEFINITIONS_NATIVES_H_
#define EXTENSIONS_RENDERER_API_DEFINITIONS_NATIVES_H_

#include "extensions/renderer/object_backed_native_handler.h"
#include "v8/include/v8.h"

namespace extensions {
class Dispatcher;
class ScriptContext;

class ApiDefinitionsNatives : public ObjectBackedNativeHandler {
 public:
  ApiDefinitionsNatives(Dispatcher* dispatcher, ScriptContext* context);

 private:
  
  void GetExtensionAPIDefinitionsForTest(
      const v8::FunctionCallbackInfo<v8::Value>& args);

  
  Dispatcher* dispatcher_;

  DISALLOW_COPY_AND_ASSIGN(ApiDefinitionsNatives);
};

}  

#endif  
