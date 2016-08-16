// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_CLIENT_GPU_CONTROL_H_
#define GPU_COMMAND_BUFFER_CLIENT_GPU_CONTROL_H_

#include <stdint.h>

#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "gpu/command_buffer/common/capabilities.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "gpu/gpu_export.h"

namespace gfx {
class GpuMemoryBuffer;
}

namespace gpu {

class GPU_EXPORT GpuControl {
 public:
  GpuControl() {}
  virtual ~GpuControl() {}

  virtual Capabilities GetCapabilities() = 0;

  
  
  virtual gfx::GpuMemoryBuffer* CreateGpuMemoryBuffer(
      size_t width,
      size_t height,
      unsigned internalformat,
      unsigned usage,
      int32_t* id) = 0;

  
  virtual void DestroyGpuMemoryBuffer(int32_t id) = 0;

  
  
  virtual uint32_t InsertSyncPoint() = 0;

  
  
  
  virtual uint32_t InsertFutureSyncPoint() = 0;

  
  
  virtual void RetireSyncPoint(uint32_t sync_point) = 0;

  
  virtual void SignalSyncPoint(uint32_t sync_point,
                               const base::Closure& callback) = 0;

  
  
  virtual void SignalQuery(uint32_t query, const base::Closure& callback) = 0;

  virtual void SetSurfaceVisible(bool visible) = 0;

  
  virtual void Echo(const base::Closure& callback) = 0;

  
  
  virtual uint32_t CreateStreamTexture(uint32_t texture_id) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(GpuControl);
};

}  

#endif  
