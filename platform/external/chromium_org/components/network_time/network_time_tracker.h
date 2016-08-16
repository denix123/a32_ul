// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NETWORK_TIME_NETWORK_TIME_TRACKER_H_
#define COMPONENTS_NETWORK_TIME_NETWORK_TIME_TRACKER_H_

#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"

class PrefRegistrySimple;
class PrefService;

namespace base {
class TickClock;
}

namespace network_time {

class NetworkTimeTracker {
 public:
  static void RegisterPrefs(PrefRegistrySimple* registry);

  NetworkTimeTracker(scoped_ptr<base::TickClock> tick_clock,
                     PrefService* pref_service);
  ~NetworkTimeTracker();

  
  
  
  bool GetNetworkTime(base::TimeTicks time_ticks,
                      base::Time* network_time,
                      base::TimeDelta* uncertainty) const;

  
  
  
  
  void UpdateNetworkTime(base::Time network_time,
                         base::TimeDelta resolution,
                         base::TimeDelta latency,
                         base::TimeTicks post_time);

  bool received_network_time() const {
    return received_network_time_;
  }

 private:
  
  scoped_ptr<base::TickClock> tick_clock_;

  PrefService* pref_service_;

  
  base::Time network_time_;

  
  
  
  
  
  base::TimeTicks network_time_ticks_;

  
  
  base::TimeDelta network_time_uncertainty_;

  base::ThreadChecker thread_checker_;

  bool received_network_time_;

  DISALLOW_COPY_AND_ASSIGN(NetworkTimeTracker);
};

}  

#endif  
