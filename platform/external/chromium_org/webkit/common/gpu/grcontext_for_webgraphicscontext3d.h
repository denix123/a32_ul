// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBKIT_COMMON_GPU_GRCONTEXT_FOR_WEBGRAPHICSCONTEXT3D_H_
#define WEBKIT_COMMON_GPU_GRCONTEXT_FOR_WEBGRAPHICSCONTEXT3D_H_

#include "base/basictypes.h"
#include "skia/ext/refptr.h"
#include "webkit/common/gpu/webkit_gpu_export.h"

class GrContext;

namespace webkit {
namespace gpu {
class WebGraphicsContext3DImpl;

class WEBKIT_GPU_EXPORT GrContextForWebGraphicsContext3D {
 public:
  explicit GrContextForWebGraphicsContext3D(
      WebGraphicsContext3DImpl* context3d);
  virtual ~GrContextForWebGraphicsContext3D();

  GrContext* get() { return gr_context_.get(); }

  void OnLostContext();
  void FreeGpuResources();

 private:
  skia::RefPtr<class GrContext> gr_context_;

  DISALLOW_COPY_AND_ASSIGN(GrContextForWebGraphicsContext3D);
};

}  
}  

#endif  
