// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_PORTAL_DETECTOR_NETWORK_PORTAL_DETECTOR_STRATEGY_H_
#define CHROMEOS_NETWORK_PORTAL_DETECTOR_NETWORK_PORTAL_DETECTOR_STRATEGY_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "chromeos/chromeos_export.h"
#include "net/base/backoff_entry.h"

namespace chromeos {

class CHROMEOS_EXPORT PortalDetectorStrategy {
 public:
  enum StrategyId {
    STRATEGY_ID_LOGIN_SCREEN,
    STRATEGY_ID_ERROR_SCREEN,
    STRATEGY_ID_SESSION
  };

  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    virtual int NoResponseResultCount() = 0;

    
    virtual base::TimeTicks AttemptStartTime() = 0;

    
    virtual base::TimeTicks GetCurrentTimeTicks() = 0;
  };

  virtual ~PortalDetectorStrategy();

  static scoped_ptr<PortalDetectorStrategy> CreateById(StrategyId id,
                                                       Delegate* delegate);

  
  
  base::TimeDelta GetDelayTillNextAttempt();

  
  base::TimeDelta GetNextAttemptTimeout();

  virtual StrategyId Id() const = 0;

  
  void Reset();

  const net::BackoffEntry::Policy& policy() const { return policy_; }

  
  void SetPolicyAndReset(const net::BackoffEntry::Policy& policy);

  
  
  void OnDetectionCompleted();

 protected:
  class BackoffEntryImpl;

  explicit PortalDetectorStrategy(Delegate* delegate);

  
  virtual base::TimeDelta GetNextAttemptTimeoutImpl();

  Delegate* delegate_;
  net::BackoffEntry::Policy policy_;
  scoped_ptr<BackoffEntryImpl> backoff_entry_;

 private:
  friend class NetworkPortalDetectorImplTest;
  friend class NetworkPortalDetectorImplBrowserTest;

  static void set_delay_till_next_attempt_for_testing(
      const base::TimeDelta& timeout) {
    delay_till_next_attempt_for_testing_ = timeout;
    delay_till_next_attempt_for_testing_initialized_ = true;
  }

  static void set_next_attempt_timeout_for_testing(
      const base::TimeDelta& timeout) {
    next_attempt_timeout_for_testing_ = timeout;
    next_attempt_timeout_for_testing_initialized_ = true;
  }

  static void reset_fields_for_testing() {
    delay_till_next_attempt_for_testing_initialized_ = false;
    next_attempt_timeout_for_testing_initialized_ = false;
  }

  
  static base::TimeDelta delay_till_next_attempt_for_testing_;

  
  static bool delay_till_next_attempt_for_testing_initialized_;

  
  static base::TimeDelta next_attempt_timeout_for_testing_;

  
  static bool next_attempt_timeout_for_testing_initialized_;

  DISALLOW_COPY_AND_ASSIGN(PortalDetectorStrategy);
};

}  

#endif  
