// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UPGRADE_DETECTOR_IMPL_H_
#define CHROME_BROWSER_UPGRADE_DETECTOR_IMPL_H_

#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "base/version.h"
#include "chrome/browser/metrics/variations/variations_service.h"
#include "chrome/browser/upgrade_detector.h"

template <typename T> struct DefaultSingletonTraits;

class UpgradeDetectorImpl :
    public UpgradeDetector,
    public chrome_variations::VariationsService::Observer {
 public:
  virtual ~UpgradeDetectorImpl();

  
  
  
  static base::Version GetCurrentlyInstalledVersion();

  
  static UpgradeDetectorImpl* GetInstance();

 protected:
  UpgradeDetectorImpl();

  
  virtual void OnExperimentChangesDetected(Severity severity) OVERRIDE;

  
  
  void NotifyOnUpgradeWithTimePassed(base::TimeDelta time_passed);

 private:
  friend struct DefaultSingletonTraits<UpgradeDetectorImpl>;

  
  void StartTimerForUpgradeCheck();

  
  void CheckForUpgrade();

  
  
  
  void StartUpgradeNotificationTimer();

  
  
  void UpgradeDetected(UpgradeAvailable upgrade_available);

  
  bool DetectOutdatedInstall();

  
  
  
  void NotifyOnUpgrade();

  
  
  
  
  
  
  static void DetectUpgradeTask(
      base::WeakPtr<UpgradeDetectorImpl> upgrade_detector);

  
  base::RepeatingTimer<UpgradeDetectorImpl> detect_upgrade_timer_;

  
  
  base::RepeatingTimer<UpgradeDetectorImpl> upgrade_notification_timer_;

  
  bool is_unstable_channel_;

  
  bool is_auto_update_enabled_;

  
  
  base::TimeTicks upgrade_detected_time_;

  
  base::Time build_date_;

  
  
  
  base::WeakPtrFactory<UpgradeDetectorImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UpgradeDetectorImpl);
};


#endif  
