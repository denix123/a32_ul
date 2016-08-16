// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_TABS_CUSTOM_BINDINGS_H_
#define CHROME_RENDERER_EXTENSIONS_TABS_CUSTOM_BINDINGS_H_

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {

class TabsCustomBindings : public ObjectBackedNativeHandler {
 public:
  explicit TabsCustomBindings(ScriptContext* context);

 private:
  
  void OpenChannelToTab(const v8::FunctionCallbackInfo<v8::Value>& args);
};

}  

#endif  
