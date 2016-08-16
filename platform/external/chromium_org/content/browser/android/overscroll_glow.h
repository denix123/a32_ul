// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ANDROID_OVERSCROLL_GLOW_H_
#define CONTENT_BROWSER_ANDROID_OVERSCROLL_GLOW_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/gfx/size_f.h"
#include "ui/gfx/vector2d_f.h"

namespace cc {
class Layer;
}

namespace content {

class EdgeEffectBase;

class OverscrollGlow {
 public:
  enum Edge { EDGE_TOP = 0, EDGE_LEFT, EDGE_BOTTOM, EDGE_RIGHT, EDGE_COUNT };

  
  typedef base::Callback<scoped_ptr<EdgeEffectBase>(void)> EdgeEffectProvider;

  
  
  
  explicit OverscrollGlow(const EdgeEffectProvider& edge_effect_provider);

  ~OverscrollGlow();

  
  
  void Enable();

  
  
  void Disable();

  
  
  
  
  bool OnOverscrolled(cc::Layer* overscrolling_layer,
                      base::TimeTicks current_time,
                      gfx::Vector2dF accumulated_overscroll,
                      gfx::Vector2dF overscroll_delta,
                      gfx::Vector2dF velocity,
                      gfx::Vector2dF overscroll_location);

  
  
  bool Animate(base::TimeTicks current_time);

  
  
  struct DisplayParameters {
    DisplayParameters();
    gfx::SizeF size;
    float edge_offsets[EDGE_COUNT];
  };
  void UpdateDisplayParameters(const DisplayParameters& params);

 private:
  enum Axis { AXIS_X, AXIS_Y };

  
  bool InitializeIfNecessary();
  bool NeedsAnimate() const;
  void UpdateLayerAttachment(cc::Layer* parent);
  void Detach();
  void Pull(base::TimeTicks current_time,
            const gfx::Vector2dF& overscroll_delta,
            const gfx::Vector2dF& overscroll_location);
  void Absorb(base::TimeTicks current_time,
              const gfx::Vector2dF& velocity,
              bool x_overscroll_started,
              bool y_overscroll_started);
  void Release(base::TimeTicks current_time);

  EdgeEffectBase* GetOppositeEdge(int edge_index);

  EdgeEffectProvider edge_effect_provider_;
  scoped_ptr<EdgeEffectBase> edge_effects_[EDGE_COUNT];

  DisplayParameters display_params_;
  bool enabled_;
  bool initialized_;

  scoped_refptr<cc::Layer> root_layer_;

  DISALLOW_COPY_AND_ASSIGN(OverscrollGlow);
};

}  

#endif  
