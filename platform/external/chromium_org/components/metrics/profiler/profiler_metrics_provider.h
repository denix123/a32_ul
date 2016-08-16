// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_PROFILER_PROFILER_METRICS_PROVIDER_H_
#define COMPONENTS_METRICS_PROFILER_PROFILER_METRICS_PROVIDER_H_

#include "base/basictypes.h"
#include "components/metrics/metrics_provider.h"
#include "components/metrics/proto/chrome_user_metrics_extension.pb.h"

namespace tracked_objects {
struct ProcessDataSnapshot;
}

namespace metrics {

class ProfilerMetricsProvider : public MetricsProvider {
 public:
  ProfilerMetricsProvider();
  virtual ~ProfilerMetricsProvider();

  
  virtual void ProvideGeneralMetrics(
      ChromeUserMetricsExtension* uma_proto) OVERRIDE;

  
  
  void RecordProfilerData(
      const tracked_objects::ProcessDataSnapshot& process_data,
      int process_type);

 private:
  
  
  ProfilerEventProto profiler_event_cache_;

  
  
  bool has_profiler_data_;

  DISALLOW_COPY_AND_ASSIGN(ProfilerMetricsProvider);
};

}  

#endif  
