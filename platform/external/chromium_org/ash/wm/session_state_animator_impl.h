// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_SESSION_STATE_ANIMATOR_IMPL_H_
#define ASH_WM_SESSION_STATE_ANIMATOR_IMPL_H_

#include "ash/ash_export.h"
#include "ash/wm/session_state_animator.h"
#include "base/basictypes.h"
#include "ui/aura/window.h"

namespace ui {
class LayerAnimationObserver;
}

namespace ash {

class ASH_EXPORT SessionStateAnimatorImpl : public SessionStateAnimator {
 public:
  
  class ASH_EXPORT TestApi {
   public:
    explicit TestApi(SessionStateAnimatorImpl* animator)
        : animator_(animator) {}

    
    
    
    bool ContainersAreAnimated(int container_mask,
                               SessionStateAnimator::AnimationType type) const;

    
    
    bool RootWindowIsAnimated(SessionStateAnimator::AnimationType type) const;

   private:
    SessionStateAnimatorImpl* animator_;  

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  SessionStateAnimatorImpl();
  virtual ~SessionStateAnimatorImpl();

  
  static void GetContainers(int container_mask,
                            aura::Window::Windows* containers);

  
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

  virtual void StartAnimationInSequence(int container_mask,
      AnimationType type,
      AnimationSpeed speed,
      AnimationSequence* observer);

  
  
  void RunAnimationForWindow(aura::Window* window,
                             SessionStateAnimator::AnimationType type,
                             SessionStateAnimator::AnimationSpeed speed,
                             ui::LayerAnimationObserver* observer);

  DISALLOW_COPY_AND_ASSIGN(SessionStateAnimatorImpl);
};

}  

#endif  
