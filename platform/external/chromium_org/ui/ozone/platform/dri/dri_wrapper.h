// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_WRAPPER_H_
#define UI_OZONE_PLATFORM_DRI_DRI_WRAPPER_H_

#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/rect_f.h"
#include "ui/ozone/platform/dri/scoped_drm_types.h"

typedef struct _drmEventContext drmEventContext;
typedef struct _drmModeModeInfo drmModeModeInfo;

struct SkImageInfo;

namespace ui {

class DriWrapper {
 public:
  DriWrapper(const char* device_path);
  virtual ~DriWrapper();

  
  virtual void Initialize();

  
  
  
  virtual ScopedDrmCrtcPtr GetCrtc(uint32_t crtc_id);

  
  
  
  
  virtual bool SetCrtc(uint32_t crtc_id,
                       uint32_t framebuffer,
                       std::vector<uint32_t> connectors,
                       drmModeModeInfo* mode);

  
  
  
  virtual bool SetCrtc(drmModeCrtc* crtc, std::vector<uint32_t> connectors);

  virtual bool DisableCrtc(uint32_t crtc_id);

  
  virtual ScopedDrmConnectorPtr GetConnector(uint32_t connector_id);

  
  
  virtual bool AddFramebuffer(uint32_t width,
                              uint32_t height,
                              uint8_t depth,
                              uint8_t bpp,
                              uint32_t stride,
                              uint32_t handle,
                              uint32_t* framebuffer);

  
  virtual bool RemoveFramebuffer(uint32_t framebuffer);

  
  virtual ScopedDrmFramebufferPtr GetFramebuffer(uint32_t framebuffer);

  
  
  
  
  
  virtual bool PageFlip(uint32_t crtc_id, uint32_t framebuffer, void* data);

  
  
  
  virtual bool PageFlipOverlay(uint32_t crtc_id,
                               uint32_t framebuffer,
                               const gfx::Rect& location,
                               const gfx::RectF& source,
                               int overlay_plane);

  
  
  
  virtual ScopedDrmPropertyPtr GetProperty(drmModeConnector* connector,
                                           const char* name);

  
  
  virtual bool SetProperty(uint32_t connector_id,
                           uint32_t property_id,
                           uint64_t value);

  
  
  
  
  virtual ScopedDrmPropertyBlobPtr GetPropertyBlob(drmModeConnector* connector,
                                                   const char* name);

  
  
  virtual bool SetCursor(uint32_t crtc_id,
                         uint32_t handle,
                         const gfx::Size& size);


  
  virtual bool MoveCursor(uint32_t crtc_id, const gfx::Point& point);

  virtual void HandleEvent(drmEventContext& event);

  virtual bool CreateDumbBuffer(const SkImageInfo& info,
                                uint32_t* handle,
                                uint32_t* stride,
                                void** pixels);

  virtual void DestroyDumbBuffer(const SkImageInfo& info,
                                 uint32_t handle,
                                 uint32_t stride,
                                 void* pixels);

  int get_fd() const { return fd_; }

 protected:
  
  
  int fd_;

 private:
  
  const char* device_path_;

  DISALLOW_COPY_AND_ASSIGN(DriWrapper);
};

}  

#endif  
