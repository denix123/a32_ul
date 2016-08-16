// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_STATUS_CHANGE_CHECKER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_STATUS_CHANGE_CHECKER_H_

#include <string>

#include "base/time/time.h"

class ProfileSyncServiceHarness;

class StatusChangeChecker {
 public:
  explicit StatusChangeChecker();

  
  
  
  virtual std::string GetDebugMessage() const = 0;

  
  bool TimedOut() const;

  virtual bool IsExitConditionSatisfied() = 0;

 protected:
  virtual ~StatusChangeChecker();

  
  virtual base::TimeDelta GetTimeoutDuration();

  
  
  
  
  
  
  void StartBlockingWait();

  
  void StopWaiting();

  
  
  void CheckExitCondition();

  
  void OnTimeout();

  bool timed_out_;
};

#endif  
