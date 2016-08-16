// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ACTIVITY_PUBLIC_ACTIVITY_H_
#define ATHENA_ACTIVITY_PUBLIC_ACTIVITY_H_

#include <string>

#include "athena/athena_export.h"

namespace aura {
class Window;
}

namespace content {
class WebContents;
}

namespace athena {

class ActivityViewModel;

class ATHENA_EXPORT Activity {
 public:
  
  
  enum ActivityState {
    
    ACTIVITY_VISIBLE,
    
    
    
    
    ACTIVITY_INVISIBLE,
    
    
    ACTIVITY_BACKGROUND_LOW_PRIORITY,
    
    
    
    ACTIVITY_PERSISTENT,
    
    ACTIVITY_UNLOADED
  };

  
  
  
  enum ActivityMediaState {
    ACTIVITY_MEDIA_STATE_NONE,
    ACTIVITY_MEDIA_STATE_RECORDING,  
    ACTIVITY_MEDIA_STATE_CAPTURING,  
    ACTIVITY_MEDIA_STATE_AUDIO_PLAYING  
  };

  
  static void Show(Activity* activity);

  
  static void Delete(Activity* activity);

  
  virtual ActivityViewModel* GetActivityViewModel() = 0;

  
  virtual void SetCurrentState(ActivityState state) = 0;

  
  virtual ActivityState GetCurrentState() = 0;

  
  virtual bool IsVisible() = 0;

  
  virtual ActivityMediaState GetMediaState() = 0;

  
  
  
  
  virtual aura::Window* GetWindow() = 0;

  
  
  virtual content::WebContents* GetWebContents() = 0;

 protected:
  virtual ~Activity() {}
};

}  

#endif  
