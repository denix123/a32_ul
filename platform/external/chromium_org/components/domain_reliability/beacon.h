// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_BEACON_H_
#define COMPONENTS_DOMAIN_RELIABILITY_BEACON_H_

#include <string>

#include "base/time/time.h"
#include "components/domain_reliability/domain_reliability_export.h"

namespace base {
class Value;
}  

namespace domain_reliability {

struct DOMAIN_RELIABILITY_EXPORT DomainReliabilityBeacon {
 public:
  DomainReliabilityBeacon();
  ~DomainReliabilityBeacon();

  
  
  base::Value* ToValue(base::TimeTicks upload_time) const;

  
  std::string url;
  
  std::string domain;
  
  std::string resource;
  
  std::string status;
  
  int chrome_error;
  
  std::string server_ip;
  
  std::string protocol;
  
  int http_response_code;
  
  base::TimeDelta elapsed;
  
  base::TimeTicks start_time;

  
};

}  

#endif  
