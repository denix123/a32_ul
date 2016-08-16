// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_HOME_HOME_CARD_GESTURE_MANAGER_H_
#define ATHENA_HOME_HOME_CARD_GESTURE_MANAGER_H_

#include "athena/home/public/home_card.h"
#include "athena/athena_export.h"
#include "ui/gfx/geometry/rect.h"

namespace ui {
class GestureEvent;
}

namespace athena {

class ATHENA_EXPORT HomeCardGestureManager {
 public:
  class Delegate {
   public:
    
    
    
    virtual void OnGestureEnded(HomeCard::State final_state,
                                bool is_fling) = 0;

    
    
    
    
    
    
    
    virtual void OnGestureProgressed(
        HomeCard::State from_state,
        HomeCard::State to_state,
        float progress) = 0;
  };

  HomeCardGestureManager(Delegate* delegate,
                         const gfx::Rect& screen_bounds);
  ~HomeCardGestureManager();

  void ProcessGestureEvent(ui::GestureEvent* event);

 private:
  
  HomeCard::State GetFinalState() const;

  
  void UpdateScrollState(const ui::GestureEvent& event);

  Delegate* delegate_;  

  
  HomeCard::State original_state_;

  
  
  int y_offset_;

  
  int last_estimated_height_;

  
  gfx::Rect screen_bounds_;

  DISALLOW_COPY_AND_ASSIGN(HomeCardGestureManager);
};

}  

#endif  
