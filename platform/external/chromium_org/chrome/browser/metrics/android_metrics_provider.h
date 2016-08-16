// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_ANDROID_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_ANDROID_METRICS_PROVIDER_H_

#include "base/basictypes.h"
#include "chrome/browser/android/activity_type_ids.h"
#include "components/metrics/metrics_provider.h"

class PrefService;
class PrefRegistrySimple;

namespace metrics {
class ChromeUserMetricsExtension;
}

class AndroidMetricsProvider : public metrics::MetricsProvider {
 public:
  
  explicit AndroidMetricsProvider(PrefService* local_state);
  virtual ~AndroidMetricsProvider();

  
  virtual void ProvideGeneralMetrics(
      metrics::ChromeUserMetricsExtension* uma_proto) override;

  
  
  void OnForegroundActivityChanged(ActivityTypeIds::Type type);

  
  virtual void ProvideStabilityMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  
  void LogStabilityToPrefs();

  
  void ConvertStabilityPrefsToHistograms();

  
  PrefService* local_state_;

  DISALLOW_COPY_AND_ASSIGN(AndroidMetricsProvider);
};

#endif  
