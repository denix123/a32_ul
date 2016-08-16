// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_QUADS_SHARED_QUAD_STATE_H_
#define CC_QUADS_SHARED_QUAD_STATE_H_

#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "third_party/skia/include/core/SkXfermode.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/transform.h"

namespace base {
namespace debug {
class TracedValue;
}
class Value;
}

namespace cc {

class CC_EXPORT SharedQuadState {
 public:
  SharedQuadState();
  ~SharedQuadState();

  void CopyFrom(const SharedQuadState* other);

  void SetAll(const gfx::Transform& content_to_target_transform,
              const gfx::Size& content_bounds,
              const gfx::Rect& visible_content_rect,
              const gfx::Rect& clip_rect,
              bool is_clipped,
              float opacity,
              SkXfermode::Mode blend_mode,
              int sorting_context_id);
  void AsValueInto(base::debug::TracedValue* dict) const;

  
  gfx::Transform content_to_target_transform;
  
  gfx::Size content_bounds;
  
  gfx::Rect visible_content_rect;
  
  gfx::Rect clip_rect;
  bool is_clipped;
  float opacity;
  SkXfermode::Mode blend_mode;
  int sorting_context_id;
};

}  

#endif  
