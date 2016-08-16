// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_ROTATION_TRAY_ROTATION_LOCK_H_
#define ASH_SYSTEM_CHROMEOS_ROTATION_TRAY_ROTATION_LOCK_H_

#include "ash/shell_observer.h"
#include "ash/system/tray/tray_image_item.h"
#include "ash/wm/maximize_mode/maximize_mode_controller.h"

namespace ash {

namespace tray {
class RotationLockDefaultView;
}  

class ASH_EXPORT TrayRotationLock : public TrayImageItem,
                                    public MaximizeModeController::Observer,
                                    public ShellObserver {
 public:
  explicit TrayRotationLock(SystemTray* system_tray);
  virtual ~TrayRotationLock();

  
  virtual void OnRotationLockChanged(bool rotation_locked) OVERRIDE;

  
  virtual views::View* CreateDefaultView(user::LoginStatus status) OVERRIDE;

  
  virtual void OnMaximizeModeStarted() OVERRIDE;
  virtual void OnMaximizeModeEnded() OVERRIDE;

 protected:
  
  virtual bool GetInitialVisibility() OVERRIDE;

 private:
  friend class TrayRotationLockTest;

  
  
  bool ShouldBeVisible();

  
  bool on_primary_display_;

  DISALLOW_COPY_AND_ASSIGN(TrayRotationLock);
};

}  

#endif  
