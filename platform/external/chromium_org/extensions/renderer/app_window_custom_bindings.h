// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_APP_WINDOW_CUSTOM_BINDINGS_H_
#define EXTENSIONS_RENDERER_APP_WINDOW_CUSTOM_BINDINGS_H_

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {
class Dispatcher;

class AppWindowCustomBindings : public ObjectBackedNativeHandler {
 public:
  AppWindowCustomBindings(Dispatcher* dispatcher, ScriptContext* context);

 private:
  void GetView(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  void GetWindowControlsHtmlTemplate(
      const v8::FunctionCallbackInfo<v8::Value>& args);

  
  Dispatcher* dispatcher_;

  DISALLOW_COPY_AND_ASSIGN(AppWindowCustomBindings);
};

}  

#endif  
