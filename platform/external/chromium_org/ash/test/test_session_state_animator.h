// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_TEST_SESSION_STATE_ANIMATOR_H_
#define ASH_TEST_TEST_SESSION_STATE_ANIMATOR_H_

#include <map>
#include <vector>

#include "ash/ash_export.h"
#include "ash/wm/session_state_animator.h"
#include "base/basictypes.h"
#include "base/time/time.h"

namespace ash {
namespace test {

class TestSessionStateAnimator : public SessionStateAnimator {
 public:
  TestSessionStateAnimator();
  virtual ~TestSessionStateAnimator();

  int last_animation_epoch() {
    return last_animation_epoch_;
  }

  
  
  void ResetAnimationEpoch();

  
  
  
  void Advance(const base::TimeDelta& duration);

  
  
  
  void CompleteAnimations(int animation_epoch, bool completed_successfully);

  
  
  
  void CompleteAllAnimations(bool completed_successfully);

  
  
  bool IsContainerAnimated(SessionStateAnimator::Container container,
                           SessionStateAnimator::AnimationType type) const;

  
  
  bool AreContainersAnimated(int container_mask,
                             SessionStateAnimator::AnimationType type) const;

  
  size_t GetAnimationCount() const;

  
  virtual void StartAnimation(int container_mask,
                              AnimationType type,
                              AnimationSpeed speed) OVERRIDE;
  virtual void StartAnimationWithCallback(
      int container_mask,
      AnimationType type,
      AnimationSpeed speed,
      base::Closure callback) OVERRIDE;
  virtual AnimationSequence* BeginAnimationSequence(
      base::Closure callback) OVERRIDE;
  virtual bool IsBackgroundHidden() const OVERRIDE;
  virtual void ShowBackground() OVERRIDE;
  virtual void HideBackground() OVERRIDE;

 private:
  class AnimationSequence;
  friend class AnimationSequence;

  
  
  struct ActiveAnimation {
    ActiveAnimation(
        int animation_epoch,
        base::TimeDelta duration,
        SessionStateAnimator::Container container,
        AnimationType type,
        AnimationSpeed speed,
        base::Closure success_callback,
        base::Closure failed_callback);
    virtual ~ActiveAnimation();

    
    int animation_epoch;

    
    base::TimeDelta remaining_duration;

    
    SessionStateAnimator::Container container;

    
    AnimationType type;

    
    AnimationSpeed speed;

    
    base::Closure success_callback;

    
    base::Closure failed_callback;
  };

  typedef std::vector<ActiveAnimation> AnimationList;
  typedef std::map<SessionStateAnimator::Container, AnimationList>
      ActiveAnimationsMap;

  
  
  virtual void StartAnimationInSequence(
      int container_mask,
      AnimationType type,
      AnimationSpeed speed,
      AnimationSequence* animation_sequence);

  
  
  
  
  void AddAnimation(SessionStateAnimator::Container container,
                    AnimationType type,
                    AnimationSpeed speed,
                    base::Closure success_callback,
                    base::Closure failed_callback);

  
  
  
  void AbortAnimation(SessionStateAnimator::Container container);

  
  static const SessionStateAnimator::Container kAllContainers[];

  
  ActiveAnimationsMap active_animations_;

  
  
  int last_animation_epoch_;

  
  bool is_background_hidden_;

  DISALLOW_COPY_AND_ASSIGN(TestSessionStateAnimator);
};

}  
}  

#endif  
