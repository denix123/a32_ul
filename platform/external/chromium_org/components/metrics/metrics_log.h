// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_METRICS_METRICS_LOG_H_
#define COMPONENTS_METRICS_METRICS_LOG_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/time/time.h"
#include "components/metrics/proto/chrome_user_metrics_extension.pb.h"

class PrefRegistrySimple;
class PrefService;

namespace base {
class DictionaryValue;
class HistogramSamples;
}

namespace content {
struct WebPluginInfo;
}

namespace tracked_objects {
struct ProcessDataSnapshot;
}

namespace variations {
struct ActiveGroupId;
}

namespace metrics {

class MetricsProvider;
class MetricsServiceClient;

class MetricsLog {
 public:
  enum LogType {
    INITIAL_STABILITY_LOG,  
    ONGOING_LOG,            
  };

  
  
  
  
  
  
  
  
  MetricsLog(const std::string& client_id,
             int session_id,
             LogType log_type,
             MetricsServiceClient* client,
             PrefService* local_state);
  virtual ~MetricsLog();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  
  static uint64 Hash(const std::string& value);

  
  
  
  
  static int64 GetBuildTime();

  
  
  
  static int64 GetCurrentTime();

  
  void RecordUserAction(const std::string& key);

  
  void RecordHistogramDelta(const std::string& histogram_name,
                            const base::HistogramSamples& snapshot);

  
  
  
  
  
  
  
  void RecordEnvironment(
      const std::vector<MetricsProvider*>& metrics_providers,
      const std::vector<variations::ActiveGroupId>& synthetic_trials,
      int64 install_date);

  
  
  
  bool LoadSavedEnvironmentFromPrefs();

  
  
  
  
  
  
  
  
  
  void RecordStabilityMetrics(
      const std::vector<MetricsProvider*>& metrics_providers,
      base::TimeDelta incremental_uptime,
      base::TimeDelta uptime);

  
  void RecordGeneralMetrics(
      const std::vector<MetricsProvider*>& metrics_providers);

  
  
  void CloseLog();

  
  
  void GetEncodedLog(std::string* encoded_log);

  const base::TimeTicks& creation_time() const {
    return creation_time_;
  }

  int num_events() const {
    return uma_proto_.omnibox_event_size() +
           uma_proto_.user_action_event_size();
  }

  LogType log_type() const { return log_type_; }

 protected:
  

  
  
  virtual void GetFieldTrialIds(
      std::vector<variations::ActiveGroupId>* field_trial_ids) const;

  ChromeUserMetricsExtension* uma_proto() { return &uma_proto_; }
  const ChromeUserMetricsExtension* uma_proto() const {
    return &uma_proto_;
  }

 private:
  
  
  bool HasEnvironment() const;

  
  
  bool HasStabilityMetrics() const;

  
  void WriteRequiredStabilityAttributes(PrefService* pref);

  
  
  
  
  void WriteRealtimeStabilityAttributes(PrefService* pref,
                                        base::TimeDelta incremental_uptime,
                                        base::TimeDelta uptime);

  
  // no longer be written to.  It is only used for sanity checking.
  bool closed_;

  
  const LogType log_type_;

  
  ChromeUserMetricsExtension uma_proto_;

  
  
  MetricsServiceClient* const client_;

  
  const base::TimeTicks creation_time_;

  PrefService* local_state_;

  DISALLOW_COPY_AND_ASSIGN(MetricsLog);
};

}  

#endif  
