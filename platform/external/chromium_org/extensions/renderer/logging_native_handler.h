// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_LOGGING_NATIVE_HANDLER_H_
#define EXTENSIONS_RENDERER_LOGGING_NATIVE_HANDLER_H_

#include <string>

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {
class ScriptContext;

class LoggingNativeHandler : public ObjectBackedNativeHandler {
 public:
  explicit LoggingNativeHandler(ScriptContext* context);
  virtual ~LoggingNativeHandler();

  
  
  
  void Check(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  void Dcheck(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  void DcheckIsOn(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  void Log(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  void Warning(const v8::FunctionCallbackInfo<v8::Value>& args);

  void ParseArgs(const v8::FunctionCallbackInfo<v8::Value>& args,
                 bool* check_value,
                 std::string* error_message);

  std::string ToStringOrDefault(const v8::Handle<v8::String>& v8_string,
                                const std::string& dflt);
};

}  

#endif  
