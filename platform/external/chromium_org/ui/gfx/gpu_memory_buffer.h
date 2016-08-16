// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_GPU_MEMORY_BUFFER_H_
#define UI_GFX_GPU_MEMORY_BUFFER_H_

#include "base/memory/shared_memory.h"
#include "build/build_config.h"
#include "ui/gfx/gfx_export.h"

#if defined(USE_X11)
#include "ui/gfx/x/x11_types.h"
#endif

namespace gfx {

enum GpuMemoryBufferType {
  EMPTY_BUFFER,
  SHARED_MEMORY_BUFFER,
  IO_SURFACE_BUFFER,
  ANDROID_NATIVE_BUFFER,
  SURFACE_TEXTURE_BUFFER,
  X11_PIXMAP_BUFFER,
  OZONE_NATIVE_BUFFER,
  GPU_MEMORY_BUFFER_TYPE_LAST = OZONE_NATIVE_BUFFER
};

#if defined(OS_ANDROID)
struct SurfaceTextureId {
  SurfaceTextureId() : primary_id(0), secondary_id(0) {}
  SurfaceTextureId(int32 primary_id, int32 secondary_id)
      : primary_id(primary_id), secondary_id(secondary_id) {}
  int32 primary_id;
  int32 secondary_id;
};
#endif

struct GpuMemoryBufferId {
  GpuMemoryBufferId() : primary_id(0), secondary_id(0) {}
  GpuMemoryBufferId(int32 primary_id, int32 secondary_id)
      : primary_id(primary_id), secondary_id(secondary_id) {}
  int32 primary_id;
  int32 secondary_id;
};

struct GFX_EXPORT GpuMemoryBufferHandle {
  GpuMemoryBufferHandle();
  bool is_null() const { return type == EMPTY_BUFFER; }
  GpuMemoryBufferType type;
  base::SharedMemoryHandle handle;
  GpuMemoryBufferId global_id;
#if defined(OS_MACOSX)
  uint32 io_surface_id;
#endif
#if defined(OS_ANDROID)
  long buffer_id;
  SurfaceTextureId surface_texture_id;
#endif
#if defined(USE_X11)
  XID pixmap;
#endif
};

// shared with the GPU. A GPU memory buffer can be written to directly by
class GFX_EXPORT GpuMemoryBuffer {
 public:
  GpuMemoryBuffer();
  virtual ~GpuMemoryBuffer();

  // Maps the buffer into the client's address space so it can be written to by
  
  
  
  virtual void* Map() = 0;

  
  
  virtual void Unmap() = 0;

  
  virtual bool IsMapped() const = 0;

  
  virtual uint32 GetStride() const = 0;

  
  virtual GpuMemoryBufferHandle GetHandle() const = 0;
};

}  

#endif  
