// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_SESSION_STATE_ANIMATOR_H_
#define ASH_WM_SESSION_STATE_ANIMATOR_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/time/time.h"

namespace ash {

class ASH_EXPORT SessionStateAnimator {
 public:
  
  enum AnimationType {
    ANIMATION_PARTIAL_CLOSE = 0,
    ANIMATION_UNDO_PARTIAL_CLOSE,
    ANIMATION_FULL_CLOSE,
    ANIMATION_FADE_IN,
    ANIMATION_FADE_OUT,
    ANIMATION_HIDE_IMMEDIATELY,
    ANIMATION_RESTORE,
    
    
    ANIMATION_LIFT,
    ANIMATION_UNDO_LIFT,
    ANIMATION_DROP,
    
    ANIMATION_RAISE_TO_SCREEN,
    ANIMATION_LOWER_BELOW_SCREEN,
    ANIMATION_PARTIAL_FADE_IN,
    ANIMATION_UNDO_PARTIAL_FADE_IN,
    ANIMATION_FULL_FADE_IN,
    ANIMATION_GRAYSCALE_BRIGHTNESS,
    ANIMATION_UNDO_GRAYSCALE_BRIGHTNESS,
  };

  
  enum AnimationSpeed {
    
    ANIMATION_SPEED_IMMEDIATE = 0,
    
    
    ANIMATION_SPEED_UNDOABLE,
    
    
    ANIMATION_SPEED_REVERT,
    
    
    
    ANIMATION_SPEED_FAST,
    
    ANIMATION_SPEED_SHOW_LOCK_SCREEN,
    
    ANIMATION_SPEED_MOVE_WINDOWS,
    
    ANIMATION_SPEED_UNDO_MOVE_WINDOWS,
    
    ANIMATION_SPEED_SHUTDOWN,
    
    ANIMATION_SPEED_REVERT_SHUTDOWN,
  };

  
  enum Container {
    DESKTOP_BACKGROUND = 1 << 0,
    LAUNCHER = 1 << 1,

    
    
    NON_LOCK_SCREEN_CONTAINERS = 1 << 2,

    
    
    
    
    LOCK_SCREEN_BACKGROUND = 1 << 3,

    
    LOCK_SCREEN_CONTAINERS = 1 << 4,

    
    
    LOCK_SCREEN_RELATED_CONTAINERS = 1 << 5,

    
    ROOT_CONTAINER = 1 << 6,
  };

  
  
  static const int kAllLockScreenContainersMask;

  
  static const int kAllNonRootContainersMask;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  class ASH_EXPORT AnimationSequence {
   public:
    virtual ~AnimationSequence();

    
    
    virtual void StartAnimation(int container_mask,
                                AnimationType type,
                                AnimationSpeed speed) = 0;

    
    
    
    
    
    
    virtual void EndSequence();

   protected:
    
    
    explicit AnimationSequence(base::Closure callback);

    
    
    
    
    virtual void OnAnimationCompleted();

    
    
    
    
    virtual void OnAnimationAborted();

   private:
    
    
    void CleanupIfSequenceCompleted();

    
    bool sequence_ended_;

    
    
    bool animation_completed_;

    
    
    bool invoke_callback_;

    
    base::Closure callback_;

    DISALLOW_COPY_AND_ASSIGN(AnimationSequence);
  };

  SessionStateAnimator();
  virtual ~SessionStateAnimator();

  
  virtual base::TimeDelta GetDuration(AnimationSpeed speed);

  
  
  virtual void StartAnimation(int container_mask,
                              AnimationType type,
                              AnimationSpeed speed) = 0;

  
  
  
  virtual void StartAnimationWithCallback(
      int container_mask,
      AnimationType type,
      AnimationSpeed speed,
      base::Closure callback) = 0;

  
  
  
  virtual AnimationSequence* BeginAnimationSequence(
      base::Closure callback) = 0;

  
  virtual bool IsBackgroundHidden() const = 0;

  
  virtual void ShowBackground() = 0;

  
  virtual void HideBackground() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(SessionStateAnimator);
};

}  

#endif  
