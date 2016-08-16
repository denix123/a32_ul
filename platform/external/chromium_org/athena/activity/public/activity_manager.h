// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ACTIVITY_PUBLIC_ACTIVITY_MANAGER_H_
#define ATHENA_ACTIVITY_PUBLIC_ACTIVITY_MANAGER_H_

#include "athena/athena_export.h"

namespace aura {
class Window;
}

namespace athena {

class Activity;
class ActivityManagerObserver;

class ATHENA_EXPORT ActivityManager {
 public:
  static ActivityManager* Create();
  static ActivityManager* Get();
  static void Shutdown();

  virtual ~ActivityManager() {}

  
  virtual void AddActivity(Activity* activity) = 0;
  virtual void RemoveActivity(Activity* activity) = 0;

  
  
  virtual Activity* GetActivityForWindow(aura::Window* window) = 0;

  
  virtual void UpdateActivity(Activity* activity) = 0;

  virtual void AddObserver(ActivityManagerObserver* observer) = 0;
  virtual void RemoveObserver(ActivityManagerObserver* observer) = 0;
};

}  

#endif  
