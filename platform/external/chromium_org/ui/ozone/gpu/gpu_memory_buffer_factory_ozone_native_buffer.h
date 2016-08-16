// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_GPU_GPU_MEMORY_BUFFER_FACTORY_OZONE_NATIVE_BUFFER_H_
#define UI_OZONE_GPU_GPU_MEMORY_BUFFER_FACTORY_OZONE_NATIVE_BUFFER_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/ozone/gpu/ozone_gpu_export.h"

namespace gfx {
class GLImage;
}

namespace ui {
class NativePixmap;

class OZONE_GPU_EXPORT GpuMemoryBufferFactoryOzoneNativeBuffer {
  typedef std::map<std::pair<uint32_t, uint32_t>, scoped_refptr<NativePixmap> >
      BufferToPixmapMap;

 public:
  GpuMemoryBufferFactoryOzoneNativeBuffer();
  virtual ~GpuMemoryBufferFactoryOzoneNativeBuffer();

  
  bool CreateGpuMemoryBuffer(const gfx::GpuMemoryBufferId& id,
                             const gfx::Size& size,
                             unsigned internalformat,
                             unsigned usage);

  
  void DestroyGpuMemoryBuffer(const gfx::GpuMemoryBufferId& id);

  
  scoped_refptr<gfx::GLImage> CreateImageForGpuMemoryBuffer(
      const gfx::GpuMemoryBufferId& id,
      const gfx::Size& size,
      unsigned internalformat);

 private:
  BufferToPixmapMap native_pixmap_map_;
};

}  

#endif  
