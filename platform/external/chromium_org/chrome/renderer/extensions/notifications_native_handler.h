// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_NOTIFICATIONS_NATIVE_HANDLER_H_
#define CHROME_RENDERER_EXTENSIONS_NOTIFICATIONS_NATIVE_HANDLER_H_

#include "base/compiler_specific.h"
#include "extensions/renderer/object_backed_native_handler.h"

namespace base {
class Value;
}

namespace extensions {

class NotificationsNativeHandler : public ObjectBackedNativeHandler {
 public:
  explicit NotificationsNativeHandler(ScriptContext* context);

 private:
  
  
  
  
  
  
  
  
  
  
  
  
  void GetNotificationImageSizes(
      const v8::FunctionCallbackInfo<v8::Value>& args);

  DISALLOW_COPY_AND_ASSIGN(NotificationsNativeHandler);
};

}  

#endif  
