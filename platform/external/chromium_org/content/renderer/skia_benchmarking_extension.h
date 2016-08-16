// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_SKIA_BENCHMARKING_EXTENSION_H_
#define CONTENT_RENDERER_SKIA_BENCHMARKING_EXTENSION_H_

#include "base/basictypes.h"
#include "gin/wrappable.h"

namespace blink {
class WebFrame;
}

namespace gin {
class Arguments;
}

namespace content {

class SkiaBenchmarking : public gin::Wrappable<SkiaBenchmarking> {
 public:
  static gin::WrapperInfo kWrapperInfo;
  static void Install(blink::WebFrame* frame);

  
  static void Initialize();

 private:
  SkiaBenchmarking();
  virtual ~SkiaBenchmarking();

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void Rasterize(gin::Arguments* args);

  
  
  
  
  void GetOps(gin::Arguments* args);

  
  
  
  
  void GetOpTimings(gin::Arguments* args);

  
  
  
  
  void GetInfo(gin::Arguments* args);

  DISALLOW_COPY_AND_ASSIGN(SkiaBenchmarking);
};

}  

#endif 
