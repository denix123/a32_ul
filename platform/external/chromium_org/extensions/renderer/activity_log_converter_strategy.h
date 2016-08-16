// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_ACTIVITY_LOG_CONVERTER_STRATEGY_H_
#define EXTENSIONS_RENDERER_ACTIVITY_LOG_CONVERTER_STRATEGY_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "content/public/renderer/v8_value_converter.h"
#include "v8/include/v8.h"

namespace extensions {

class ActivityLogConverterStrategy
    : public content::V8ValueConverter::Strategy {
 public:
  typedef content::V8ValueConverter::Strategy::FromV8ValueCallback
      FromV8ValueCallback;

  ActivityLogConverterStrategy();
  virtual ~ActivityLogConverterStrategy();

  
  virtual bool FromV8Object(v8::Handle<v8::Object> value,
                            base::Value** out,
                            v8::Isolate* isolate,
                            const FromV8ValueCallback& callback) const OVERRIDE;
  virtual bool FromV8Array(v8::Handle<v8::Array> value,
                           base::Value** out,
                           v8::Isolate* isolate,
                           const FromV8ValueCallback& callback) const OVERRIDE;

 private:
  bool FromV8Internal(v8::Handle<v8::Object> value,
                      base::Value** out,
                      v8::Isolate* isolate,
                      const FromV8ValueCallback& callback) const;

  DISALLOW_COPY_AND_ASSIGN(ActivityLogConverterStrategy);
};

}  

#endif  
