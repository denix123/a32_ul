// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_BLOB_NATIVE_HANDLER_H_
#define EXTENSIONS_RENDERER_BLOB_NATIVE_HANDLER_H_

#include "extensions/renderer/object_backed_native_handler.h"

namespace extensions {
class ScriptContext;

class BlobNativeHandler : public ObjectBackedNativeHandler {
 public:
  explicit BlobNativeHandler(ScriptContext* context);
};

}  

#endif  
