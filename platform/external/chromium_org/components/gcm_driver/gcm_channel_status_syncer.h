// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_CHANNEL_STATUS_SYNCER_H_
#define COMPONENTS_GCM_DRIVER_GCM_CHANNEL_STATUS_SYNCER_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"

class PrefService;
class PrefRegistrySimple;

namespace net {
class URLRequestContextGetter;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace gcm {

class GCMChannelStatusRequest;
class GCMDriver;

class GCMChannelStatusSyncer {
 public:
  static void RegisterPrefs(PrefRegistrySimple* registry);
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  GCMChannelStatusSyncer(
      GCMDriver* driver,
      PrefService* prefs,
      const std::string& channel_status_request_url,
      const std::string& user_agent,
      const scoped_refptr<net::URLRequestContextGetter>& request_context);
  ~GCMChannelStatusSyncer();

  void EnsureStarted();
  void Stop();

  bool gcm_enabled() const { return gcm_enabled_; }

  
  void set_delay_removed_for_testing(bool delay_removed) {
    delay_removed_for_testing_ = delay_removed;
  }
  base::TimeDelta current_request_delay_interval() const {
    return current_request_delay_interval_;
  }
  static int first_time_delay_seconds();

 private:
  
  void OnRequestCompleted(bool update_received,
                          bool enabled,
                          int poll_interval_seconds);

  
  void ScheduleRequest();

  
  void StartRequest();

  
  
  base::TimeDelta GetRequestDelayInterval() const;

  
  GCMDriver* driver_;
  PrefService* prefs_;
  const std::string channel_status_request_url_;
  const std::string user_agent_;

  scoped_refptr<net::URLRequestContextGetter> request_context_;
  scoped_ptr<GCMChannelStatusRequest> request_;

  bool started_;
  bool gcm_enabled_;
  int poll_interval_seconds_;
  base::Time last_check_time_;

  
  
  
  
  int custom_poll_interval_use_count_;

  
  
  bool delay_removed_for_testing_;

  
  base::TimeDelta current_request_delay_interval_;

  
  base::WeakPtrFactory<GCMChannelStatusSyncer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GCMChannelStatusSyncer);
};

}  

#endif  
