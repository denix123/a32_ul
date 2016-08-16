// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_OVERLAY_CANDIDATES_OZONE_H_
#define UI_OZONE_PUBLIC_OVERLAY_CANDIDATES_OZONE_H_

#include <vector>

#include "base/basictypes.h"
#include "ui/gfx/rect_f.h"
#include "ui/ozone/ozone_base_export.h"
#include "ui/ozone/public/surface_factory_ozone.h"

namespace ui {

class OZONE_BASE_EXPORT OverlayCandidatesOzone {
 public:
  struct OverlaySurfaceCandidate {
    OverlaySurfaceCandidate();
    ~OverlaySurfaceCandidate();

    
    gfx::OverlayTransform transform;
    
    SurfaceFactoryOzone::BufferFormat format;
    
    gfx::Rect display_rect;
    
    gfx::RectF crop_rect;
    
    
    int plane_z_order;

    
    
    bool overlay_handled;
  };

  typedef std::vector<OverlaySurfaceCandidate> OverlaySurfaceCandidateList;

  
  
  
  
  virtual void CheckOverlaySupport(OverlaySurfaceCandidateList* surfaces);

  virtual ~OverlayCandidatesOzone();
};

}  

#endif  
