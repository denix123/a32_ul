// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_RAPPOR_SERVICE_H_
#define COMPONENTS_RAPPOR_RAPPOR_SERVICE_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "components/metrics/daily_event.h"

class PrefRegistrySimple;
class PrefService;

namespace net {
class URLRequestContextGetter;
}

namespace rappor {

class LogUploader;
class RapporMetric;
class RapporReports;
struct RapporParameters;

enum RapporType {
  
  ETLD_PLUS_ONE_RAPPOR_TYPE = 0,
  NUM_RAPPOR_TYPES
};

class RapporService {
 public:
  
  
  
  explicit RapporService(PrefService* pref_service);
  virtual ~RapporService();

  
  void AddDailyObserver(scoped_ptr<metrics::DailyEvent::Observer> observer);

  
  void Start(net::URLRequestContextGetter* context,
             bool metrics_enabled);

  
  
  void RecordSample(const std::string& metric_name,
                    RapporType type,
                    const std::string& sample);

  
  void SetCohortForTesting(uint32_t cohort) { cohort_ = cohort; }

  
  void SetSecretForTesting(const std::string& secret) { secret_ = secret; }

  
  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 protected:
  
  
  void LoadCohort();

  
  
  
  void LoadSecret();

  
  
  
  bool ExportMetrics(RapporReports* reports);

  
  
  
  void RecordSampleInternal(const std::string& metric_name,
                            const RapporParameters& parameters,
                            const std::string& sample);

 private:
  
  bool IsInitialized() const;

  
  
  void OnLogInterval();

  
  
  RapporMetric* LookUpMetric(const std::string& metric_name,
                             const RapporParameters& parameters);

  
  PrefService* pref_service_;

  
  std::string secret_;

  
  int32_t cohort_;

  
  base::OneShotTimer<RapporService> log_rotation_timer_;

  
  metrics::DailyEvent daily_event_;

  
  scoped_ptr<LogUploader> uploader_;

  
  
  std::map<std::string, RapporMetric*> metrics_map_;

  DISALLOW_COPY_AND_ASSIGN(RapporService);
};

}  

#endif  
