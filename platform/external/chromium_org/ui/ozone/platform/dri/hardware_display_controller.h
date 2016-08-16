// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_HARDWARE_DISPLAY_CONTROLLER_H_
#define UI_OZONE_PLATFORM_DRI_HARDWARE_DISPLAY_CONTROLLER_H_

#include <stddef.h>
#include <stdint.h>
#include <xf86drmMode.h>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "ui/ozone/platform/dri/dri_wrapper.h"

namespace gfx {
class Point;
}

namespace ui {

class CrtcState;
class ScanoutBuffer;

struct OverlayPlane {
  
  explicit OverlayPlane(scoped_refptr<ScanoutBuffer> buffer);

  OverlayPlane(scoped_refptr<ScanoutBuffer> buffer,
               int z_order,
               gfx::OverlayTransform plane_transform,
               const gfx::Rect& display_bounds,
               const gfx::RectF& crop_rect);

  ~OverlayPlane();

  scoped_refptr<ScanoutBuffer> buffer;
  int z_order;
  gfx::OverlayTransform plane_transform;
  gfx::Rect display_bounds;
  gfx::RectF crop_rect;
  int overlay_plane;
};

typedef std::vector<OverlayPlane> OverlayPlaneList;

class HardwareDisplayController
    : public base::SupportsWeakPtr<HardwareDisplayController> {
 public:
  HardwareDisplayController(DriWrapper* drm,
                            scoped_ptr<CrtcState> state);

  ~HardwareDisplayController();

  
  
  bool Modeset(const OverlayPlane& primary,
               drmModeModeInfo mode);

  
  bool Enable();

  
  void Disable();

  void QueueOverlayPlane(const OverlayPlane& plane);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool SchedulePageFlip();

  
  
  void WaitForPageFlipEvent();

  
  
  
  
  
  
  void OnPageFlipEvent(unsigned int frame,
                       unsigned int seconds,
                       unsigned int useconds);

  
  bool SetCursor(scoped_refptr<ScanoutBuffer> buffer);

  bool UnsetCursor();

  
  bool MoveCursor(const gfx::Point& location);

  void AddCrtc(scoped_ptr<CrtcState> state);
  scoped_ptr<CrtcState> RemoveCrtc(uint32_t crtc);
  bool HasCrtc(uint32_t crtc) const;
  bool IsMirrored() const;
  bool IsDisabled() const;
  gfx::Size GetModeSize() const;

  gfx::Point origin() const { return origin_; }
  void set_origin(const gfx::Point& origin) { origin_ = origin; }

  const drmModeModeInfo& get_mode() const { return mode_; };
  uint64_t get_time_of_last_flip() const {
    return time_of_last_flip_;
  };

 private:
  bool ModesetCrtc(const scoped_refptr<ScanoutBuffer>& buffer,
                   drmModeModeInfo mode,
                   CrtcState* state);

  bool SchedulePageFlipOnCrtc(const OverlayPlaneList& overlays,
                              CrtcState* state);

  
  
  OverlayPlaneList current_planes_;
  OverlayPlaneList pending_planes_;
  scoped_refptr<ScanoutBuffer> cursor_buffer_;

  
  
  DriWrapper* drm_;

  
  
  ScopedVector<CrtcState> crtc_states_;
  gfx::Point origin_;
  drmModeModeInfo mode_;
  bool is_disabled_;
  uint64_t time_of_last_flip_;

  
  
  
  
  
  
  uint32_t pending_page_flips_;

  DISALLOW_COPY_AND_ASSIGN(HardwareDisplayController);
};

}  

#endif  
