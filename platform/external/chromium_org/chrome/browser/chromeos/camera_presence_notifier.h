// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_CAMERA_PRESENCE_NOTIFIER_H_
#define CHROME_BROWSER_CHROMEOS_CAMERA_PRESENCE_NOTIFIER_H_

#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"

namespace chromeos {

class CameraPresenceNotifier {
 public:
  class Observer {
   public:
    virtual void OnCameraPresenceCheckDone(bool is_camera_present) = 0;
   protected:
    virtual ~Observer() {}
  };

  static CameraPresenceNotifier* GetInstance();

  void AddObserver(CameraPresenceNotifier::Observer* observer);
  void RemoveObserver(CameraPresenceNotifier::Observer* observer);

 private:
  friend struct DefaultSingletonTraits<CameraPresenceNotifier>;
  CameraPresenceNotifier();
  ~CameraPresenceNotifier();

  void CheckCameraPresence();

  
  void OnCameraPresenceCheckDone();

  bool camera_present_on_last_check_;

  
  base::RepeatingTimer<CameraPresenceNotifier> camera_check_timer_;

  ObserverList<Observer> observers_;

  base::WeakPtrFactory<CameraPresenceNotifier> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CameraPresenceNotifier);
};

}  

#endif  
