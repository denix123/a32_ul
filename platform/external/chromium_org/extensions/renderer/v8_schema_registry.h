// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_V8_SCHEMA_REGISTRY_H_
#define EXTENSIONS_RENDERER_V8_SCHEMA_REGISTRY_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "gin/public/context_holder.h"
#include "v8/include/v8-util.h"
#include "v8/include/v8.h"

namespace extensions {
class NativeHandler;

class V8SchemaRegistry {
 public:
  V8SchemaRegistry();
  ~V8SchemaRegistry();

  
  scoped_ptr<NativeHandler> AsNativeHandler();

  
  v8::Handle<v8::Array> GetSchemas(const std::vector<std::string>& apis);

  
  v8::Handle<v8::Object> GetSchema(const std::string& api);

 private:
  
  
  v8::Handle<v8::Context> GetOrCreateContext(v8::Isolate* isolate);

  
  typedef v8::StdPersistentValueMap<std::string, v8::Object> SchemaCache;
  scoped_ptr<SchemaCache> schema_cache_;

  
  
  scoped_ptr<gin::ContextHolder> context_holder_;

  DISALLOW_COPY_AND_ASSIGN(V8SchemaRegistry);
};

}  

#endif  
