// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_OUTPUT_OVERLAY_CANDIDATE_H_
#define CC_OUTPUT_OVERLAY_CANDIDATE_H_

#include <vector>

#include "cc/base/cc_export.h"
#include "cc/resources/resource_format.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/gfx/transform.h"

namespace cc {

class CC_EXPORT OverlayCandidate {
 public:
  static gfx::OverlayTransform GetOverlayTransform(
      const gfx::Transform& quad_transform,
      bool flipped);
  static gfx::Rect GetOverlayRect(const gfx::Transform& quad_transform,
                                  const gfx::Rect& rect);

  OverlayCandidate();
  ~OverlayCandidate();

  
  gfx::OverlayTransform transform;
  
  ResourceFormat format;
  
  gfx::Rect display_rect;
  
  gfx::RectF uv_rect;
  
  unsigned resource_id;
  
  
  int plane_z_order;

  
  
  bool overlay_handled;
};

typedef std::vector<OverlayCandidate> OverlayCandidateList;

}  

#endif  
