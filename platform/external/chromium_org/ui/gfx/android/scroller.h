// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_ANDROID_SCROLLER_H_
#define UI_GFX_ANDROID_SCROLLER_H_

#include "base/time/time.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class GFX_EXPORT Scroller {
 public:
  struct Config {
    Config();

    
    float fling_friction;

    
    bool flywheel_enabled;
  };

  explicit Scroller(const Config& config);
  ~Scroller();

  
  
  void StartScroll(float start_x,
                   float start_y,
                   float dx,
                   float dy,
                   base::TimeTicks start_time);

  
  
  void StartScroll(float start_x,
                   float start_y,
                   float dx,
                   float dy,
                   base::TimeTicks start_time,
                   base::TimeDelta duration);

  
  
  void Fling(float start_x,
             float start_y,
             float velocity_x,
             float velocity_y,
             float min_x,
             float max_x,
             float min_y,
             float max_y,
             base::TimeTicks start_time);

  
  
  bool ComputeScrollOffset(base::TimeTicks time);

  
  
  void ExtendDuration(base::TimeDelta extend);
  void SetFinalX(float new_x);
  void SetFinalY(float new_y);

  
  
  void AbortAnimation();

  
  void ForceFinished(bool finished);

  
  bool IsFinished() const;

  
  base::TimeDelta GetTimePassed() const;

  
  base::TimeDelta GetDuration() const;

  float GetStartX() const;
  float GetStartY() const;
  float GetCurrX() const;
  float GetCurrY() const;
  float GetCurrVelocity() const;
  float GetCurrVelocityX() const;
  float GetCurrVelocityY() const;
  float GetFinalX() const;
  float GetFinalY() const;

  bool IsScrollingInDirection(float xvel, float yvel) const;

 private:
  enum Mode {
    UNDEFINED,
    SCROLL_MODE,
    FLING_MODE,
  };

  void OnDurationChanged();
  void RecomputeDeltas();

  double GetSplineDeceleration(float velocity) const;
  base::TimeDelta GetSplineFlingDuration(float velocity) const;
  double GetSplineFlingDistance(float velocity) const;

  Mode mode_;

  float start_x_;
  float start_y_;
  float final_x_;
  float final_y_;

  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;

  float curr_x_;
  float curr_y_;
  base::TimeTicks start_time_;
  base::TimeTicks curr_time_;
  base::TimeDelta duration_;
  double duration_seconds_reciprocal_;
  float delta_x_;
  float delta_x_norm_;
  float delta_y_;
  float delta_y_norm_;
  bool finished_;
  bool flywheel_enabled_;

  float velocity_;
  float curr_velocity_;
  float distance_;

  float fling_friction_;
  float deceleration_;
  float tuning_coeff_;
};

}  

#endif  
