// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_EXTENSIONS_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_EXTENSIONS_METRICS_PROVIDER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "components/metrics/metrics_provider.h"

class Profile;

namespace extensions {
class ExtensionSet;
}

namespace metrics {
class MetricsStateManager;
class SystemProfileProto;
}

class ExtensionsMetricsProvider : public metrics::MetricsProvider {
 public:
  
  
  explicit ExtensionsMetricsProvider(
      metrics::MetricsStateManager* metrics_state_manager);
  virtual ~ExtensionsMetricsProvider();

  
  virtual void ProvideSystemProfileMetrics(
      metrics::SystemProfileProto* system_profile) OVERRIDE;

 protected:
  

  
  virtual scoped_ptr<extensions::ExtensionSet> GetInstalledExtensions(
      Profile* profile);

  
  virtual uint64 GetClientID();

  
  
  
  static int HashExtension(const std::string& extension_id, uint32 client_key);

 private:
  
  
  
  Profile* GetMetricsProfile();

  
  void ProvideOffStoreMetric(metrics::SystemProfileProto* system_profile);

  
  
  void ProvideOccupiedBucketMetric(metrics::SystemProfileProto* system_profile);

  
  metrics::MetricsStateManager* metrics_state_manager_;

  
  
  
  Profile* cached_profile_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionsMetricsProvider);
};

#endif  
