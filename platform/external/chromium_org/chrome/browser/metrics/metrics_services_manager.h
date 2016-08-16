// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_METRICS_SERVICES_MANAGER_H_
#define CHROME_BROWSER_METRICS_METRICS_SERVICES_MANAGER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"

class ChromeMetricsServiceClient;
class PrefService;

namespace base {
class FilePath;
}

namespace metrics {
class MetricsService;
class MetricsStateManager;
}

namespace rappor {
class RapporService;
}

namespace chrome_variations {
class VariationsService;
}

class MetricsServicesManager {
 public:
  
  explicit MetricsServicesManager(PrefService* local_state);
  virtual ~MetricsServicesManager();

  
  
  metrics::MetricsService* GetMetricsService();

  
  rappor::RapporService* GetRapporService();

  
  chrome_variations::VariationsService* GetVariationsService();

  
  void OnPluginLoadingError(const base::FilePath& plugin_path);

 private:
  
  
  ChromeMetricsServiceClient* GetChromeMetricsServiceClient();

  metrics::MetricsStateManager* GetMetricsStateManager();

  
  bool IsMetricsReportingEnabled() const;

  
  base::ThreadChecker thread_checker_;

  
  PrefService* local_state_;

  
  scoped_ptr<metrics::MetricsStateManager> metrics_state_manager_;

  
  
  scoped_ptr<ChromeMetricsServiceClient> metrics_service_client_;

  
  scoped_ptr<rappor::RapporService> rappor_service_;

  
  scoped_ptr<chrome_variations::VariationsService> variations_service_;

  DISALLOW_COPY_AND_ASSIGN(MetricsServicesManager);
};

#endif  
