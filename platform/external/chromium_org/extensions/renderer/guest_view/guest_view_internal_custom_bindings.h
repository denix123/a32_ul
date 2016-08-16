// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_GUEST_VIEW_GUEST_VIEW_INTERNAL_CUSTOM_BINDINGS_H_
#define EXTENSIONS_RENDERER_GUEST_VIEW_GUEST_VIEW_INTERNAL_CUSTOM_BINDINGS_H_

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {
class Dispatcher;

class GuestViewInternalCustomBindings : public ObjectBackedNativeHandler {
 public:
  explicit GuestViewInternalCustomBindings(ScriptContext* context);

 private:
  
  
  
  
  
  
  
  
  
  
  
  void AttachGuest(const v8::FunctionCallbackInfo<v8::Value>& args);
};

}  

#endif  
