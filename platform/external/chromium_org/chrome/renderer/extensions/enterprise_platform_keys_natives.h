// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_ENTERPRISE_PLATFORM_KEYS_NATIVES_H_
#define CHROME_RENDERER_EXTENSIONS_ENTERPRISE_PLATFORM_KEYS_NATIVES_H_

#include "extensions/renderer/object_backed_native_handler.h"
#include "v8/include/v8.h"

namespace extensions {
class ScriptContext;

class EnterprisePlatformKeysNatives : public ObjectBackedNativeHandler {
 public:
  explicit EnterprisePlatformKeysNatives(ScriptContext* context);

 private:
  
  
  
  
  
  
  
  
  
  void NormalizeAlgorithm(const v8::FunctionCallbackInfo<v8::Value>& call_info);

  DISALLOW_COPY_AND_ASSIGN(EnterprisePlatformKeysNatives);
};

}  

#endif  