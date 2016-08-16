// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_HID_DETECTION_SCREEN_ACTOR_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_HID_DETECTION_SCREEN_ACTOR_H_

#include <string>

#include "base/callback_forward.h"

namespace chromeos {

class HIDDetectionScreenActor {
 public:
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    virtual void OnExit() = 0;

    
    
    virtual void OnActorDestroyed(HIDDetectionScreenActor* actor) = 0;
  };

  virtual ~HIDDetectionScreenActor() {}

  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void SetDelegate(Delegate* delegate) = 0;

  
  
  virtual void CheckIsScreenRequired(
      const base::Callback<void(bool)>& on_check_done) = 0;
};

}  

#endif  

