// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_INPUT_PAGE_SCALE_ANIMATION_H_
#define CC_INPUT_PAGE_SCALE_ANIMATION_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "cc/base/cc_export.h"
#include "ui/gfx/size.h"
#include "ui/gfx/vector2d_f.h"

namespace cc {

class TimingFunction;

class CC_EXPORT PageScaleAnimation {
 public:
  
  static scoped_ptr<PageScaleAnimation> Create(
      const gfx::Vector2dF& start_scroll_offset,
      float start_page_scale_factor,
      const gfx::SizeF& viewport_size,
      const gfx::SizeF& root_layer_size,
      scoped_ptr<TimingFunction> timing_function);

  ~PageScaleAnimation();

  
  

  
  void ZoomTo(const gfx::Vector2dF& target_scroll_offset,
              float target_page_scale_factor,
              double duration);

  
  
  
  
  void ZoomWithAnchor(const gfx::Vector2dF& anchor,
                      float target_page_scale_factor,
                      double duration);

  
  
  bool IsAnimationStarted() const;
  void StartAnimation(base::TimeTicks time);

  
  
  gfx::Vector2dF ScrollOffsetAtTime(base::TimeTicks time) const;
  float PageScaleFactorAtTime(base::TimeTicks time) const;
  bool IsAnimationCompleteAtTime(base::TimeTicks time) const;

  
  
  base::TimeTicks start_time() const { return start_time_; }
  base::TimeDelta duration() const { return duration_; }
  base::TimeTicks end_time() const { return start_time_ + duration_; }
  gfx::Vector2dF target_scroll_offset() const { return target_scroll_offset_; }
  float target_page_scale_factor() const { return target_page_scale_factor_; }

 protected:
  PageScaleAnimation(const gfx::Vector2dF& start_scroll_offset,
                     float start_page_scale_factor,
                     const gfx::SizeF& viewport_size,
                     const gfx::SizeF& root_layer_size,
                     scoped_ptr<TimingFunction> timing_function);

 private:
  void ClampTargetScrollOffset();
  void InferTargetScrollOffsetFromStartAnchor();
  void InferTargetAnchorFromScrollOffsets();

  gfx::SizeF StartViewportSize() const;
  gfx::SizeF TargetViewportSize() const;
  float InterpAtTime(base::TimeTicks time) const;
  gfx::SizeF ViewportSizeAt(float interp) const;
  gfx::Vector2dF ScrollOffsetAt(float interp) const;
  gfx::Vector2dF AnchorAt(float interp) const;
  gfx::Vector2dF ViewportRelativeAnchorAt(float interp) const;
  float PageScaleFactorAt(float interp) const;

  float start_page_scale_factor_;
  float target_page_scale_factor_;
  gfx::Vector2dF start_scroll_offset_;
  gfx::Vector2dF target_scroll_offset_;

  gfx::Vector2dF start_anchor_;
  gfx::Vector2dF target_anchor_;

  gfx::SizeF viewport_size_;
  gfx::SizeF root_layer_size_;

  base::TimeTicks start_time_;
  base::TimeDelta duration_;

  scoped_ptr<TimingFunction> timing_function_;

  DISALLOW_COPY_AND_ASSIGN(PageScaleAnimation);
};

}  

#endif  
