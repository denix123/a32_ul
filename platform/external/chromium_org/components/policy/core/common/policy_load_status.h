// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_POLICY_LOAD_STATUS_H_
#define COMPONENTS_POLICY_CORE_COMMON_POLICY_LOAD_STATUS_H_

#include <bitset>

#include "base/basictypes.h"
#include "components/policy/policy_export.h"

namespace base {
class HistogramBase;
}

namespace policy {

enum PolicyLoadStatus {
  
  
  
  POLICY_LOAD_STATUS_STARTED = 0,
  
  POLICY_LOAD_STATUS_QUERY_FAILED = 1,
  
  POLICY_LOAD_STATUS_NO_POLICY = 2,
  
  POLICY_LOAD_STATUS_INACCCESSIBLE = 3,
  
  POLICY_LOAD_STATUS_MISSING = 4,
  
  POLICY_LOAD_STATUS_WOW64_REDIRECTION_DISABLED = 5,
  
  POLICY_LOAD_STATUS_READ_ERROR = 6,
  
  POLICY_LOAD_STATUS_TOO_BIG = 7,
  
  POLICY_LOAD_STATUS_PARSE_ERROR = 8,

  
  POLICY_LOAD_STATUS_SIZE
};

class POLICY_EXPORT PolicyLoadStatusSample {
 public:
  PolicyLoadStatusSample();
  ~PolicyLoadStatusSample();

  
  void Add(PolicyLoadStatus status);

 private:
  std::bitset<POLICY_LOAD_STATUS_SIZE> status_bits_;
  base::HistogramBase* histogram_;

  DISALLOW_COPY_AND_ASSIGN(PolicyLoadStatusSample);
};

}  

#endif  
