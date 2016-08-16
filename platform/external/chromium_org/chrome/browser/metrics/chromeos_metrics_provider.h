// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_CHROMEOS_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_CHROMEOS_METRICS_PROVIDER_H_

#include "base/memory/weak_ptr.h"
#include "chrome/browser/metrics/perf_provider_chromeos.h"
#include "components/metrics/metrics_provider.h"

namespace device {
class BluetoothAdapter;
}

namespace metrics {
class ChromeUserMetricsExtension;
}

class PrefRegistrySimple;
class PrefService;

class ChromeOSMetricsProvider : public metrics::MetricsProvider {
 public:
  ChromeOSMetricsProvider();
  virtual ~ChromeOSMetricsProvider();

  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static void LogCrash(const std::string& crash_type);

  
  
  void InitTaskGetHardwareClass(const base::Closure& callback);

  
  virtual void OnDidCreateMetricsLog() OVERRIDE;
  virtual void ProvideSystemProfileMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;
  virtual void ProvideStabilityMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;
  virtual void ProvideGeneralMetrics(
      metrics::ChromeUserMetricsExtension* uma_proto) OVERRIDE;

 private:
  
  void InitTaskGetHardwareClassOnFileThread();

  
  
  
  void UpdateMultiProfileUserCount(
      metrics::SystemProfileProto* system_profile_proto);

  
  
  void SetBluetoothAdapter(scoped_refptr<device::BluetoothAdapter> adapter);

  
  void WriteBluetoothProto(metrics::SystemProfileProto* system_profile_proto);

  metrics::PerfProvider perf_provider_;

  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  bool registered_user_count_at_log_initialization_;

  
  
  
  uint64 user_count_at_log_initialization_;

  
  
  std::string hardware_class_;

  base::WeakPtrFactory<ChromeOSMetricsProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromeOSMetricsProvider);
};

#endif  
