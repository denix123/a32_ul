// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_PROVIDER_H_
#define COMPONENTS_METRICS_METRICS_PROVIDER_H_

#include "base/basictypes.h"

namespace metrics {

class ChromeUserMetricsExtension;
class SystemProfileProto;
class SystemProfileProto_Stability;

class MetricsProvider {
 public:
  MetricsProvider();
  virtual ~MetricsProvider();

  
  virtual void OnDidCreateMetricsLog();

  
  virtual void OnRecordingEnabled();

  
  virtual void OnRecordingDisabled();

  
  virtual void ProvideSystemProfileMetrics(
      SystemProfileProto* system_profile_proto);

  
  
  virtual bool HasStabilityMetrics();

  
  
  
  virtual void ProvideStabilityMetrics(
      SystemProfileProto* system_profile_proto);

  
  
  virtual void ClearSavedStabilityMetrics();

  
  
  
  virtual void ProvideGeneralMetrics(
      ChromeUserMetricsExtension* uma_proto);

 private:
  DISALLOW_COPY_AND_ASSIGN(MetricsProvider);
};

}  

#endif  
