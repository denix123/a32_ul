// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_SCHEDULER_H_
#define COMPONENTS_DOMAIN_RELIABILITY_SCHEDULER_H_

#include <vector>

#include "base/callback.h"
#include "base/time/time.h"
#include "components/domain_reliability/domain_reliability_export.h"

namespace base {
class Value;
}  

namespace domain_reliability {

class DomainReliabilityConfig;
class MockableTime;

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityScheduler {
 public:
  typedef base::Callback<void(base::TimeDelta, base::TimeDelta)>
      ScheduleUploadCallback;

  struct Params {
   public:
    base::TimeDelta minimum_upload_delay;
    base::TimeDelta maximum_upload_delay;
    base::TimeDelta upload_retry_interval;

    static Params GetFromFieldTrialsOrDefaults();
  };

  DomainReliabilityScheduler(MockableTime* time,
                             size_t num_collectors,
                             const Params& params,
                             const ScheduleUploadCallback& callback);
  ~DomainReliabilityScheduler();

  
  
  
  void OnBeaconAdded();

  
  
  
  
  size_t OnUploadStart();

  
  
  
  void OnUploadComplete(bool success);

  base::Value* GetWebUIData() const;

 private:
  struct CollectorState {
    CollectorState();

    
    
    unsigned failures;
    base::TimeTicks next_upload;
  };

  void MaybeScheduleUpload();

  void GetNextUploadTimeAndCollector(base::TimeTicks now,
                                     base::TimeTicks* upload_time_out,
                                     size_t* collector_index_out);

  base::TimeDelta GetUploadRetryInterval(unsigned failures);

  MockableTime* time_;
  std::vector<CollectorState> collectors_;
  Params params_;
  ScheduleUploadCallback callback_;

  
  
  bool upload_pending_;

  
  
  
  bool upload_scheduled_;

  
  
  bool upload_running_;

  
  
  size_t collector_index_;

  
  
  base::TimeTicks first_beacon_time_;

  
  base::TimeTicks old_first_beacon_time_;

  
  base::TimeTicks scheduled_min_time_;
  base::TimeTicks scheduled_max_time_;
  
  bool last_upload_finished_;
  base::TimeTicks last_upload_start_time_;
  base::TimeTicks last_upload_end_time_;
  size_t last_upload_collector_index_;
  bool last_upload_success_;
};

}  

#endif  
