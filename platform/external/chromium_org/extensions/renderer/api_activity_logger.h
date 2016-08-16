// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_API_ACTIVITY_LOGGER_H_
#define EXTENSIONS_RENDERER_API_ACTIVITY_LOGGER_H_

#include <string>

#include "extensions/common/features/feature.h"
#include "extensions/renderer/object_backed_native_handler.h"
#include "v8/include/v8.h"

namespace extensions {

class APIActivityLogger : public ObjectBackedNativeHandler {
 public:
  explicit APIActivityLogger(ScriptContext* context);

 private:
  
  enum CallType { APICALL, EVENT };

  
  
  
  
  
  static void LogAPICall(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  
  
  static void LogEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  static void LogInternal(const CallType call_type,
                          const v8::FunctionCallbackInfo<v8::Value>& args);

  DISALLOW_COPY_AND_ASSIGN(APIActivityLogger);
};

}  

#endif  
