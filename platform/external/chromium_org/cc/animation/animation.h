// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_ANIMATION_ANIMATION_H_
#define CC_ANIMATION_ANIMATION_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "cc/base/cc_export.h"

namespace cc {

class AnimationCurve;

class CC_EXPORT Animation {
 public:
  
  
  
  
  
  
  
  
  enum RunState {
    WaitingForTargetAvailability = 0,
    WaitingForDeletion,
    Starting,
    Running,
    Paused,
    Finished,
    Aborted,
    
    RunStateEnumSize
  };

  enum TargetProperty {
    Transform = 0,
    Opacity,
    Filter,
    ScrollOffset,
    BackgroundColor,
    
    TargetPropertyEnumSize
  };

  enum Direction { Normal, Reverse, Alternate, AlternateReverse };

  enum FillMode {
    FillModeNone,
    FillModeForwards,
    FillModeBackwards,
    FillModeBoth
  };

  static scoped_ptr<Animation> Create(scoped_ptr<AnimationCurve> curve,
                                      int animation_id,
                                      int group_id,
                                      TargetProperty target_property);

  virtual ~Animation();

  int id() const { return id_; }
  int group() const { return group_; }
  TargetProperty target_property() const { return target_property_; }

  RunState run_state() const { return run_state_; }
  void SetRunState(RunState run_state, base::TimeTicks monotonic_time);

  
  
  
  double iterations() const { return iterations_; }
  void set_iterations(double n) { iterations_ = n; }

  double iteration_start() const { return iteration_start_; }
  void set_iteration_start(double iteration_start) {
    iteration_start_ = iteration_start;
  }

  base::TimeTicks start_time() const { return start_time_; }

  void set_start_time(base::TimeTicks monotonic_time) {
    start_time_ = monotonic_time;
  }
  bool has_set_start_time() const { return !start_time_.is_null(); }

  base::TimeDelta time_offset() const { return time_offset_; }
  void set_time_offset(base::TimeDelta monotonic_time) {
    time_offset_ = monotonic_time;
  }

  void Suspend(base::TimeTicks monotonic_time);
  void Resume(base::TimeTicks monotonic_time);

  Direction direction() { return direction_; }
  void set_direction(Direction direction) { direction_ = direction; }

  FillMode fill_mode() { return fill_mode_; }
  void set_fill_mode(FillMode fill_mode) { fill_mode_ = fill_mode; }

  double playback_rate() { return playback_rate_; }
  void set_playback_rate(double playback_rate) {
    playback_rate_ = playback_rate;
  }

  bool IsFinishedAt(base::TimeTicks monotonic_time) const;
  bool is_finished() const {
    return run_state_ == Finished ||
        run_state_ == Aborted ||
        run_state_ == WaitingForDeletion;
  }

  bool InEffect(base::TimeTicks monotonic_time) const;

  AnimationCurve* curve() { return curve_.get(); }
  const AnimationCurve* curve() const { return curve_.get(); }

  
  
  
  bool needs_synchronized_start_time() const {
    return needs_synchronized_start_time_;
  }
  void set_needs_synchronized_start_time(bool needs_synchronized_start_time) {
    needs_synchronized_start_time_ = needs_synchronized_start_time;
  }

  
  
  bool received_finished_event() const {
    return received_finished_event_;
  }
  void set_received_finished_event(bool received_finished_event) {
    received_finished_event_ = received_finished_event;
  }

  
  
  double TrimTimeToCurrentIteration(base::TimeTicks monotonic_time) const;

  scoped_ptr<Animation> CloneAndInitialize(RunState initial_run_state) const;

  bool is_controlling_instance() const { return is_controlling_instance_; }

  void PushPropertiesTo(Animation* other) const;

  void set_is_impl_only(bool is_impl_only) { is_impl_only_ = is_impl_only; }
  bool is_impl_only() const { return is_impl_only_; }

  void set_affects_active_observers(bool affects_active_observers) {
    affects_active_observers_ = affects_active_observers;
  }
  bool affects_active_observers() const { return affects_active_observers_; }

  void set_affects_pending_observers(bool affects_pending_observers) {
    affects_pending_observers_ = affects_pending_observers;
  }
  bool affects_pending_observers() const { return affects_pending_observers_; }

 private:
  Animation(scoped_ptr<AnimationCurve> curve,
            int animation_id,
            int group_id,
            TargetProperty target_property);

  double ConvertToActiveTime(base::TimeTicks monotonic_time) const;

  scoped_ptr<AnimationCurve> curve_;

  
  int id_;

  
  
  
  
  
  int group_;

  TargetProperty target_property_;
  RunState run_state_;
  double iterations_;
  double iteration_start_;
  base::TimeTicks start_time_;
  Direction direction_;
  double playback_rate_;
  FillMode fill_mode_;

  
  
  
  
  base::TimeDelta time_offset_;

  bool needs_synchronized_start_time_;
  bool received_finished_event_;

  
  
  
  bool suspended_;

  
  
  
  
  base::TimeTicks pause_time_;
  base::TimeDelta total_paused_time_;

  
  
  
  
  
  
  
  bool is_controlling_instance_;

  bool is_impl_only_;

  
  
  
  
  
  
  
  
  
  
  
  bool affects_active_observers_;
  bool affects_pending_observers_;

  DISALLOW_COPY_AND_ASSIGN(Animation);
};

}  

#endif  
