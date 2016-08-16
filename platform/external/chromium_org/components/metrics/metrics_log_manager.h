// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_LOG_MANAGER_H_
#define COMPONENTS_METRICS_METRICS_LOG_MANAGER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "components/metrics/metrics_log.h"
#include "components/metrics/persisted_logs.h"

namespace metrics {

class MetricsLogManager {
 public:
  
  
  
  MetricsLogManager(PrefService* local_state, size_t max_ongoing_log_size);
  ~MetricsLogManager();

  
  
  void BeginLoggingWithLog(scoped_ptr<MetricsLog> log);

  
  MetricsLog* current_log() { return current_log_.get(); }

  
  
  void FinishCurrentLog();

  
  bool has_unsent_logs() const {
    return initial_log_queue_.size() || ongoing_log_queue_.size();
  }

  
  
  void StageNextLogForUpload();

  
  bool has_staged_log() const {
    return initial_log_queue_.has_staged_log() ||
        ongoing_log_queue_.has_staged_log();
  }

  
  
  const std::string& staged_log() const {
    return initial_log_queue_.has_staged_log() ?
        initial_log_queue_.staged_log() : ongoing_log_queue_.staged_log();
  }

  
  
  const std::string& staged_log_hash() const {
    return initial_log_queue_.has_staged_log() ?
        initial_log_queue_.staged_log_hash() :
        ongoing_log_queue_.staged_log_hash();
  }

  
  void DiscardStagedLog();

  
  void DiscardCurrentLog();

  
  
  
  
  
  void PauseCurrentLog();

  
  
  void ResumePausedLog();

  
  void PersistUnsentLogs();

  
  void LoadPersistedUnsentLogs();

 private:
  
  void StoreLog(const std::string& log_data, MetricsLog::LogType log_type);

  
  bool unsent_logs_loaded_;

  
  scoped_ptr<MetricsLog> current_log_;

  
  scoped_ptr<MetricsLog> paused_log_;

  
  PersistedLogs initial_log_queue_;
  PersistedLogs ongoing_log_queue_;

  DISALLOW_COPY_AND_ASSIGN(MetricsLogManager);
};

}  

#endif  
