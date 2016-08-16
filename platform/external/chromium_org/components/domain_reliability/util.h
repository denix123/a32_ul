// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_UTIL_H_
#define COMPONENTS_DOMAIN_RELIABILITY_UTIL_H_

#include <map>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/tracked_objects.h"
#include "components/domain_reliability/domain_reliability_export.h"
#include "net/http/http_response_info.h"

namespace domain_reliability {

bool GetDomainReliabilityBeaconStatus(
    int net_error,
    int http_response_code,
    std::string* beacon_status_out);

std::string GetDomainReliabilityProtocol(
    net::HttpResponseInfo::ConnectionInfo connection_info,
    bool ssl_info_populated);

class DOMAIN_RELIABILITY_EXPORT MockableTime {
 public:
  
  class DOMAIN_RELIABILITY_EXPORT Timer {
   public:
    virtual ~Timer();

    virtual void Start(const tracked_objects::Location& posted_from,
                       base::TimeDelta delay,
                       const base::Closure& user_task) = 0;
    virtual void Stop() = 0;
    virtual bool IsRunning() = 0;

   protected:
    Timer();
  };

  virtual ~MockableTime();

  
  virtual base::Time Now() = 0;
  
  virtual base::TimeTicks NowTicks() = 0;
  
  virtual scoped_ptr<MockableTime::Timer> CreateTimer() = 0;

 protected:
  MockableTime();

 private:
  DISALLOW_COPY_AND_ASSIGN(MockableTime);
};

class DOMAIN_RELIABILITY_EXPORT ActualTime : public MockableTime {
 public:
  ActualTime();

  virtual ~ActualTime();

  
  virtual base::Time Now() OVERRIDE;
  virtual base::TimeTicks NowTicks() OVERRIDE;
  virtual scoped_ptr<MockableTime::Timer> CreateTimer() OVERRIDE;
};

}  

#endif  
