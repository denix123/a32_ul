// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_SCOPED_GPU_RASTER_H_
#define CC_RESOURCES_SCOPED_GPU_RASTER_H_

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "cc/output/context_provider.h"

namespace cc {

class CC_EXPORT ScopedGpuRaster {
 public:
  ScopedGpuRaster(ContextProvider* context_provider);
  ~ScopedGpuRaster();

 private:
  void BeginGpuRaster();
  void EndGpuRaster();

  ContextProvider* context_provider_;

  DISALLOW_COPY_AND_ASSIGN(ScopedGpuRaster);
};

}  

#endif  
