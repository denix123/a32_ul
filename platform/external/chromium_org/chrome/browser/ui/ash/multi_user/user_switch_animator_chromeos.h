// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_MULTI_USER_USER_SWITCH_ANIMATOR_CHROMEOS_H_
#define CHROME_BROWSER_UI_ASH_MULTI_USER_USER_SWITCH_ANIMATOR_CHROMEOS_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"

namespace aura {
class Window;
}  

namespace chrome {

class MultiUserWindowManagerChromeOS;

class UserSwichAnimatorChromeOS {
 public:
  
  enum AnimationStep {
    ANIMATION_STEP_HIDE_OLD_USER,  
    ANIMATION_STEP_SHOW_NEW_USER,  
    ANIMATION_STEP_FINALIZE,       
    ANIMATION_STEP_ENDED           
  };

  UserSwichAnimatorChromeOS(MultiUserWindowManagerChromeOS* owner,
                            const std::string& new_user_id,
                            int animation_speed_ms);
  ~UserSwichAnimatorChromeOS();

  
  static bool CoversScreen(aura::Window* window);

  bool IsAnimationFinished() {
    return animation_step_ == ANIMATION_STEP_ENDED;
  }

  
  
  const std::string& wallpaper_user_id_for_test() { return wallpaper_user_id_; }

  
  
  
  
  void AdvanceUserTransitionAnimation();

  
  
  void CancelAnimation();

 private:
  
  enum TransitioningScreenCover {
    NO_USER_COVERS_SCREEN,   
    OLD_USER_COVERS_SCREEN,  
                             
    NEW_USER_COVERS_SCREEN,  
                             
    BOTH_USERS_COVER_SCREEN  
                             
  };

  
  void FinalizeAnimation();

  
  void TransitionWallpaper(AnimationStep animtion_step);

  
  void TransitionUserShelf(AnimationStep animtion_step);

  
  void TransitionWindows(AnimationStep animation_step);

  
  
  
  TransitioningScreenCover GetScreenCover(aura::Window* root_window);

  
  MultiUserWindowManagerChromeOS* owner_;

  
  std::string new_user_id_;

  
  int animation_speed_ms_;

  
  AnimationStep animation_step_;

  
  TransitioningScreenCover screen_cover_;

  
  
  scoped_ptr<base::Timer> user_changed_animation_timer_;

  
  std::string wallpaper_user_id_;

  DISALLOW_COPY_AND_ASSIGN(UserSwichAnimatorChromeOS);
};

}  

#endif  
