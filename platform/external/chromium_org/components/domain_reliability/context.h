// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_CONTEXT_H_
#define COMPONENTS_DOMAIN_RELIABILITY_CONTEXT_H_

#include <deque>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "components/domain_reliability/beacon.h"
#include "components/domain_reliability/config.h"
#include "components/domain_reliability/domain_reliability_export.h"
#include "components/domain_reliability/scheduler.h"

class GURL;

namespace base {
class Value;
}

namespace domain_reliability {

class DomainReliabilityDispatcher;
class DomainReliabilityUploader;
class MockableTime;

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityContext {
 public:
  DomainReliabilityContext(
      MockableTime* time,
      const DomainReliabilityScheduler::Params& scheduler_params,
      const std::string& upload_reporter_string,
      DomainReliabilityDispatcher* dispatcher,
      DomainReliabilityUploader* uploader,
      scoped_ptr<const DomainReliabilityConfig> config);
  ~DomainReliabilityContext();

  
  
  
  void OnBeacon(const GURL& url, const DomainReliabilityBeacon& beacon);

  
  void ClearBeacons();

  
  
  scoped_ptr<base::Value> GetWebUIData() const;

  void GetQueuedBeaconsForTesting(
      std::vector<DomainReliabilityBeacon>* beacons_out) const;

  void GetRequestCountsForTesting(
      size_t resource_index,
      uint32* successful_requests_out,
      uint32* failed_requests_out) const;

  const DomainReliabilityConfig& config() const { return *config_.get(); }

  
  
  static const size_t kMaxQueuedBeacons;

 private:
  class ResourceState;

  typedef std::deque<DomainReliabilityBeacon> BeaconDeque;
  typedef ScopedVector<ResourceState> ResourceStateVector;
  typedef ResourceStateVector::const_iterator ResourceStateIterator;

  void InitializeResourceStates();
  void ScheduleUpload(base::TimeDelta min_delay, base::TimeDelta max_delay);
  void StartUpload();
  void OnUploadComplete(bool success);

  scoped_ptr<const base::Value> CreateReport(base::TimeTicks upload_time) const;

  
  
  
  void MarkUpload();

  
  
  void CommitUpload();

  void RollbackUpload();

  
  
  void RemoveOldestBeacon();

  scoped_ptr<const DomainReliabilityConfig> config_;
  MockableTime* time_;
  const std::string& upload_reporter_string_;
  DomainReliabilityScheduler scheduler_;
  DomainReliabilityDispatcher* dispatcher_;
  DomainReliabilityUploader* uploader_;

  BeaconDeque beacons_;
  size_t uploading_beacons_size_;
  
  
  ResourceStateVector states_;
  base::TimeTicks upload_time_;
  base::TimeTicks last_upload_time_;

  base::WeakPtrFactory<DomainReliabilityContext> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DomainReliabilityContext);
};

}  

#endif  
