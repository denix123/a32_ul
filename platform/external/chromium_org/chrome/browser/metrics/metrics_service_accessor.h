// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_METRICS_SERVICE_ACCESSOR_H_
#define CHROME_BROWSER_METRICS_METRICS_SERVICE_ACCESSOR_H_

#include <stdint.h>

#include "base/macros.h"

namespace metrics {
class MetricsService;
}

class MetricsServiceAccessor {
 protected:
  
  
  MetricsServiceAccessor() {}

  
  
  
  
  static bool RegisterSyntheticFieldTrial(
      metrics::MetricsService* metrics_service,
      uint32_t trial_name_hash,
      uint32_t group_name_hash);

 private:
  DISALLOW_COPY_AND_ASSIGN(MetricsServiceAccessor);
};

#endif  
