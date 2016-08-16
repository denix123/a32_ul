// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UPGRADE_DETECTOR_H_
#define CHROME_BROWSER_UPGRADE_DETECTOR_H_

#include "base/timer/timer.h"
#include "chrome/browser/chrome_notification_types.h"
#include "chrome/browser/idle.h"
#include "ui/gfx/image/image.h"

class PrefRegistrySimple;

class UpgradeDetector {
 public:
  
  enum UpgradeNotificationAnnoyanceLevel {
    UPGRADE_ANNOYANCE_NONE = 0,  
    UPGRADE_ANNOYANCE_LOW,       
    UPGRADE_ANNOYANCE_ELEVATED,  
    UPGRADE_ANNOYANCE_HIGH,      
    UPGRADE_ANNOYANCE_SEVERE,    
    UPGRADE_ANNOYANCE_CRITICAL,  
  };

  
  static UpgradeDetector* GetInstance();

  virtual ~UpgradeDetector();

  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  bool notify_upgrade() const { return notify_upgrade_; }

  
  bool is_outdated_install() const {
    return upgrade_available_ == UPGRADE_NEEDED_OUTDATED_INSTALL;
  }

  
  
  bool is_outdated_install_no_au() const {
    return upgrade_available_ == UPGRADE_NEEDED_OUTDATED_INSTALL_NO_AU;
  }

  
  
  void acknowledge_critical_update() {
    critical_update_acknowledged_ = true;
  }

  
  bool critical_update_acknowledged() const {
    return critical_update_acknowledged_;
  }

  
  
  
  int GetIconResourceID();

  UpgradeNotificationAnnoyanceLevel upgrade_notification_stage() const {
    return upgrade_notification_stage_;
  }

 protected:
  enum UpgradeAvailable {
    
    UPGRADE_AVAILABLE_NONE,
    
    UPGRADE_AVAILABLE_REGULAR,
    
    
    UPGRADE_AVAILABLE_CRITICAL,
    
    
    UPGRADE_NEEDED_OUTDATED_INSTALL,
    
    
    UPGRADE_NEEDED_OUTDATED_INSTALL_NO_AU,
  };

  UpgradeDetector();

  
  void NotifyUpgradeRecommended();

  
  
  virtual void TriggerCriticalUpdate();

  UpgradeAvailable upgrade_available() const { return upgrade_available_; }
  void set_upgrade_available(UpgradeAvailable available) {
    upgrade_available_ = available;
  }

  void set_best_effort_experiment_updates_available(bool available) {
    best_effort_experiment_updates_available_ = available;
  }

  bool critical_experiment_updates_available() const {
    return critical_experiment_updates_available_;
  }
  void set_critical_experiment_updates_available(bool available) {
    critical_experiment_updates_available_ = available;
  }

  void set_critical_update_acknowledged(bool acknowledged) {
    critical_update_acknowledged_ = acknowledged;
  }

  void set_upgrade_notification_stage(UpgradeNotificationAnnoyanceLevel stage) {
    upgrade_notification_stage_ = stage;
  }

 private:
  
  void CheckIdle();

  
  
  void IdleCallback(IdleState state);

  
  void TriggerNotification(chrome::NotificationType type);

  
  
  UpgradeAvailable upgrade_available_;

  
  bool best_effort_experiment_updates_available_;

  
  bool critical_experiment_updates_available_;

  
  bool critical_update_acknowledged_;

  
  
  
  base::RepeatingTimer<UpgradeDetector> idle_check_timer_;

  
  UpgradeNotificationAnnoyanceLevel upgrade_notification_stage_;

  
  
  bool notify_upgrade_;

  DISALLOW_COPY_AND_ASSIGN(UpgradeDetector);
};

#endif  
