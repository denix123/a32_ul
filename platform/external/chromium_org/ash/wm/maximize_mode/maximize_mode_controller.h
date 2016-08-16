// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_CONTROLLER_H_
#define ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_CONTROLLER_H_

#include "ash/accelerometer/accelerometer_observer.h"
#include "ash/ash_export.h"
#include "ash/display/display_controller.h"
#include "ash/display/display_manager.h"
#include "ash/shell_observer.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "ui/gfx/display.h"

#if defined(OS_CHROMEOS)
#include "chromeos/dbus/power_manager_client.h"
#endif  

namespace base {
class TickClock;
}

namespace ui {
class EventHandler;
}

namespace ash {

class MaximizeModeControllerTest;
class ScopedDisableInternalMouseAndKeyboard;
class MaximizeModeWindowManager;
class MaximizeModeWindowManagerTest;
namespace test {
class MultiUserWindowManagerChromeOSTest;
}

class ASH_EXPORT MaximizeModeController
    : public AccelerometerObserver,
#if defined(OS_CHROMEOS)
      public chromeos::PowerManagerClient::Observer,
#endif  
      public ShellObserver,
      public DisplayController::Observer {
 public:
  
  
  class Observer {
   public:
    
    virtual void OnRotationLockChanged(bool rotation_locked) {}

   protected:
    virtual ~Observer() {}
  };

  MaximizeModeController();
  virtual ~MaximizeModeController();

  bool ignore_display_configuration_updates() const {
    return ignore_display_configuration_updates_;
  }

  
  
  bool rotation_locked() {
    return rotation_locked_;
  }

  
  
  void SetRotationLocked(bool rotation_locked);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  bool CanEnterMaximizeMode();

  
  
  
  
  
  void EnableMaximizeModeWindowManager(bool enable);

  
  bool IsMaximizeModeWindowManagerEnabled() const;

  
  
  
  
  void AddWindow(aura::Window* window);

  
  
  
  
  
  void Shutdown();

  
  virtual void OnAccelerometerUpdated(
      const ui::AccelerometerUpdate& update) OVERRIDE;

  
  virtual void OnAppTerminating() OVERRIDE;
  virtual void OnMaximizeModeStarted() OVERRIDE;
  virtual void OnMaximizeModeEnded() OVERRIDE;

  
  virtual void OnDisplayConfigurationChanged() OVERRIDE;

#if defined(OS_CHROMEOS)
  
  virtual void LidEventReceived(bool open,
                                const base::TimeTicks& time) OVERRIDE;
  virtual void SuspendImminent() OVERRIDE;
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;
#endif  

 private:
  friend class MaximizeModeControllerTest;
  friend class MaximizeModeWindowManagerTest;
  friend class test::MultiUserWindowManagerChromeOSTest;

  
  
  void SetTickClockForTest(scoped_ptr<base::TickClock> tick_clock);

  
  
  void HandleHingeRotation(const gfx::Vector3dF& base,
                           const gfx::Vector3dF& lid);

  
  
  void HandleScreenRotation(const gfx::Vector3dF& lid);

  
  void SetDisplayRotation(DisplayManager* display_manager,
                          gfx::Display::Rotation rotation);

  
  bool WasLidOpenedRecently() const;

  
  
  void EnterMaximizeMode();

  
  
  void LeaveMaximizeMode();

  
  void RecordTouchViewStateTransition();

  
  
  void LoadDisplayRotationProperties();

  
  scoped_ptr<MaximizeModeWindowManager> maximize_mode_window_manager_;

  
  
  scoped_ptr<ScopedDisableInternalMouseAndKeyboard> event_blocker_;

  
  bool rotation_locked_;

  
  bool have_seen_accelerometer_data_;

  
  
  bool ignore_display_configuration_updates_;

  
  
  
  bool shutting_down_;

  
  
  gfx::Display::Rotation user_rotation_;

  
  
  
  gfx::Display::Rotation current_rotation_;

  
  ObserverList<Observer> observers_;

  
  base::Time last_touchview_transition_time_;
  base::TimeDelta total_touchview_time_;
  base::TimeDelta total_non_touchview_time_;

  
  
  
  base::TimeTicks last_lid_open_time_;

  
  scoped_ptr<base::TickClock> tick_clock_;

  
  bool lid_is_closed_;

  DISALLOW_COPY_AND_ASSIGN(MaximizeModeController);
};

}  

#endif  
