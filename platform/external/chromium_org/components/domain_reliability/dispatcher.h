// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_DISPATCHER_H_
#define COMPONENTS_DOMAIN_RELIABILITY_DISPATCHER_H_

#include <set>

#include "base/callback_forward.h"
#include "base/time/time.h"
#include "components/domain_reliability/domain_reliability_export.h"

namespace tracked_objects {
class Location;
}  

namespace domain_reliability {

class MockableTime;

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityDispatcher {
 public:
  explicit DomainReliabilityDispatcher(MockableTime* time);
  ~DomainReliabilityDispatcher();

  
  
  
  
  void ScheduleTask(const base::Closure& task,
                    base::TimeDelta min_delay,
                    base::TimeDelta max_delay);

  
  void RunEligibleTasks();

 private:
  struct Task;

  
  void MakeTaskWaiting(Task* task);

  
  
  void MakeTaskEligible(Task* task);

  
  void RunAndDeleteTask(Task* task);

  MockableTime* time_;
  std::set<Task*> tasks_;
  std::set<Task*> eligible_tasks_;
};

}  

#endif
