// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_PERF_PROVIDER_CHROMEOS_H_
#define CHROME_BROWSER_METRICS_PERF_PROVIDER_CHROMEOS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chromeos/dbus/power_manager_client.h"
#include "chromeos/login/login_state.h"
#include "components/metrics/proto/sampled_profile.pb.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace metrics {

class WindowedIncognitoObserver;

class PerfProvider : public base::NonThreadSafe,
                     public chromeos::PowerManagerClient::Observer,
                     public content::NotificationObserver {
 public:
  PerfProvider();
  virtual ~PerfProvider();

  
  
  bool GetSampledProfiles(std::vector<SampledProfile>* sampled_profiles);

 private:
  
  
  class LoginObserver : public chromeos::LoginState::Observer {
   public:
    explicit LoginObserver(PerfProvider* perf_provider);

    
    
    virtual void LoggedInStateChanged() OVERRIDE;

   private:
    
    
    PerfProvider* perf_provider_;
  };

  
  
  
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;

  
  
  void OnUserLoggedIn();

  
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  void Deactivate();

  
  
  
  void ScheduleIntervalCollection();

  
  
  void CollectIfNecessary(scoped_ptr<SampledProfile> sampled_profile);

  
  
  void DoPeriodicCollection();

  
  
  
  void CollectPerfDataAfterResume(const base::TimeDelta& sleep_duration,
                                  const base::TimeDelta& time_after_resume);

  
  
  void CollectPerfDataAfterSessionRestore(
      const base::TimeDelta& time_after_restore);

  
  
  
  
  void ParseProtoIfValid(
      scoped_ptr<WindowedIncognitoObserver> incognito_observer,
      scoped_ptr<SampledProfile> sampled_profile,
      const std::vector<uint8>& data);

  
  std::vector<SampledProfile> cached_perf_data_;

  
  base::OneShotTimer<PerfProvider> timer_;

  
  LoginObserver login_observer_;

  
  base::TimeTicks login_time_;

  
  base::TimeTicks next_profiling_interval_start_;

  
  
  content::NotificationRegistrar session_restore_registrar_;

  
  base::TimeTicks last_session_restore_collection_time_;

  
  base::WeakPtrFactory<PerfProvider> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PerfProvider);
};

}  

#endif  
