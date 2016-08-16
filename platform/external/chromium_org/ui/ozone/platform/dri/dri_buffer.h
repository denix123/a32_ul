// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_BUFFER_H_
#define UI_OZONE_PLATFORM_DRI_DRI_BUFFER_H_

#include "base/macros.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "ui/ozone/platform/dri/scanout_buffer.h"

namespace ui {

class DriWrapper;

class DriBuffer : public ScanoutBuffer {
 public:
  DriBuffer(DriWrapper* dri);

  
  
  bool Initialize(const SkImageInfo& info);

  SkCanvas* GetCanvas() const;

  
  virtual uint32_t GetFramebufferId() const OVERRIDE;
  virtual uint32_t GetHandle() const OVERRIDE;
  virtual gfx::Size GetSize() const OVERRIDE;

 protected:
  virtual ~DriBuffer();

  DriWrapper* dri_;  

  
  skia::RefPtr<SkSurface> surface_;

  
  uint32_t stride_;

  
  uint32_t handle_;

  
  
  uint32_t framebuffer_;

  DISALLOW_COPY_AND_ASSIGN(DriBuffer);
};

class DriBufferGenerator : public ScanoutBufferGenerator {
 public:
  DriBufferGenerator(DriWrapper* dri);
  virtual ~DriBufferGenerator();

  
  virtual scoped_refptr<ScanoutBuffer> Create(const gfx::Size& size) OVERRIDE;

 private:
  DriWrapper* dri_;  

  DISALLOW_COPY_AND_ASSIGN(DriBufferGenerator);
};

}  

#endif  
