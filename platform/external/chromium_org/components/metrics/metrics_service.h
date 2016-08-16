// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_METRICS_METRICS_SERVICE_H_
#define COMPONENTS_METRICS_METRICS_SERVICE_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/metrics/field_trial.h"
#include "base/metrics/histogram_flattener.h"
#include "base/metrics/histogram_snapshot_manager.h"
#include "base/metrics/user_metrics.h"
#include "base/time/time.h"
#include "components/metrics/clean_exit_beacon.h"
#include "components/metrics/metrics_log.h"
#include "components/metrics/metrics_log_manager.h"
#include "components/metrics/metrics_provider.h"
#include "components/variations/active_field_trials.h"

class MetricsServiceAccessor;
class PrefService;
class PrefRegistrySimple;

namespace base {
class DictionaryValue;
class HistogramSamples;
class MessageLoopProxy;
class PrefService;
}

namespace variations {
struct ActiveGroupId;
}

namespace net {
class URLFetcher;
}

namespace metrics {

class MetricsLogUploader;
class MetricsReportingScheduler;
class MetricsServiceClient;
class MetricsStateManager;

struct SyntheticTrialGroup {
 public:
  ~SyntheticTrialGroup();

  variations::ActiveGroupId id;
  base::TimeTicks start_time;

 private:
  
  friend class ::MetricsServiceAccessor;
  friend class MetricsService;
  FRIEND_TEST_ALL_PREFIXES(MetricsServiceTest, RegisterSyntheticTrial);

  
  
  
  SyntheticTrialGroup(uint32 trial, uint32 group);
};

class MetricsService : public base::HistogramFlattener {
 public:
  
  enum ExecutionPhase {
    UNINITIALIZED_PHASE = 0,
    START_METRICS_RECORDING = 100,
    CREATE_PROFILE = 200,
    STARTUP_TIMEBOMB_ARM = 300,
    THREAD_WATCHER_START = 400,
    MAIN_MESSAGE_LOOP_RUN = 500,
    SHUTDOWN_TIMEBOMB_ARM = 600,
    SHUTDOWN_COMPLETE = 700,
  };

  
  
  
  
  MetricsService(MetricsStateManager* state_manager,
                 MetricsServiceClient* client,
                 PrefService* local_state);
  virtual ~MetricsService();

  
  
  
  
  void InitializeMetricsRecordingState();

  
  
  
  void Start();

  
  
  bool StartIfMetricsReportingEnabled();

  
  
  
  void StartRecordingForTests();

  
  
  void Stop();

  
  
  
  
  void EnableReporting();
  void DisableReporting();

  
  
  std::string GetClientId();

  
  int64 GetInstallDate();

  
  
  
  
  
  
  
  scoped_ptr<const base::FieldTrial::EntropyProvider> CreateEntropyProvider();

  
  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual void RecordDelta(const base::HistogramBase& histogram,
                           const base::HistogramSamples& snapshot) OVERRIDE;
  virtual void InconsistencyDetected(
      base::HistogramBase::Inconsistency problem) OVERRIDE;
  virtual void UniqueInconsistencyDetected(
      base::HistogramBase::Inconsistency problem) OVERRIDE;
  virtual void InconsistencyDetectedInLoggedCount(int amount) OVERRIDE;

  
  
  void OnApplicationNotIdle();

  
  
  void RecordStartOfSessionEnd();

  
  
  void RecordCompletedSessionEnd();

#if defined(OS_ANDROID) || defined(OS_IOS)
  
  void OnAppEnterBackground();

  
  void OnAppEnterForeground();
#else
  
  void LogNeedForCleanShutdown();
#endif  

  static void SetExecutionPhase(ExecutionPhase execution_phase,
                                PrefService* local_state);

  
  
  void RecordBreakpadRegistration(bool success);

  
  
  void RecordBreakpadHasDebugger(bool has_debugger);

  bool recording_active() const;
  bool reporting_active() const;

  
  
  static bool UmaMetricsProperlyShutdown();

  
  
  
  
  
  
  
  
  void RegisterSyntheticFieldTrial(const SyntheticTrialGroup& trial_group);

  
  
  void RegisterMetricsProvider(scoped_ptr<MetricsProvider> provider);

  
  
  
  void CheckForClonedInstall(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

 protected:
  
  MetricsLogManager* log_manager() { return &log_manager_; }

 private:
  
  
  enum State {
    INITIALIZED,                    
    INIT_TASK_SCHEDULED,            
                                    
    INIT_TASK_DONE,                 
    SENDING_INITIAL_STABILITY_LOG,  
    SENDING_INITIAL_METRICS_LOG,    
    SENDING_OLD_LOGS,               
    SENDING_CURRENT_LOGS,           
  };

  enum ShutdownCleanliness {
    CLEANLY_SHUTDOWN = 0xdeadbeef,
    NEED_TO_SHUTDOWN = ~CLEANLY_SHUTDOWN
  };

  typedef std::vector<SyntheticTrialGroup> SyntheticTrialGroups;

  
  void StartGatheringMetrics();

  
  
  void FinishedGatheringInitialMetrics();

  void OnUserAction(const std::string& action);

  
  
  
  
  
  
  void GetUptimes(PrefService* pref,
                  base::TimeDelta* incremental_uptime,
                  base::TimeDelta* uptime);

  
  
  
  void EnableRecording();
  void DisableRecording();

  
  
  
  
  void HandleIdleSinceLastTransmission(bool in_idle);

  
  void InitializeMetricsState();

  
  void NotifyOnDidCreateMetricsLog();

  
  
  void ScheduleNextStateSave();

  
  
  
  void SaveLocalState();

  
  void OpenNewLog();

  
  void CloseCurrentLog();

  
  
  void PushPendingLogsToPersistentStorage();

  
  
  void StartSchedulerIfNecessary();

  
  void StartScheduledUpload();

  
  void OnFinalLogInfoCollectionDone();

  
  
  void StageNewLog();

  
  
  bool ProvidersHaveStabilityMetrics();

  
  
  
  
  void PrepareInitialStabilityLog();

  
  
  void PrepareInitialMetricsLog();

  
  void SendStagedLog();

  
  void OnLogUploadComplete(int response_code);

  
  void IncrementPrefValue(const char* path);

  
  
  void IncrementLongPrefsValue(const char* path);

  
  void LogCleanShutdown();

  
  
  void RecordCurrentState(PrefService* pref);

  
  bool ShouldLogEvents();

  
  void RecordBooleanPrefValue(const char* path, bool value);

  
  
  void GetCurrentSyntheticFieldTrials(
      std::vector<variations::ActiveGroupId>* synthetic_trials);

  
  scoped_ptr<MetricsLog> CreateLog(MetricsLog::LogType log_type);

  
  
  void RecordCurrentHistograms();

  
  
  void RecordCurrentStabilityHistograms();

  
  MetricsLogManager log_manager_;

  
  base::HistogramSnapshotManager histogram_snapshot_manager_;

  
  
  MetricsStateManager* const state_manager_;

  
  
  MetricsServiceClient* const client_;

  
  ScopedVector<MetricsProvider> metrics_providers_;

  PrefService* local_state_;

  CleanExitBeacon clean_exit_beacon_;

  base::ActionCallback action_callback_;

  
  
  
  bool recording_active_;
  bool reporting_active_;

  
  
  bool test_mode_active_;

  
  
  State state_;

  
  bool has_initial_stability_log_;

  
  
  
  scoped_ptr<MetricsLog> initial_metrics_log_;

  
  scoped_ptr<MetricsLogUploader> log_uploader_;

  
  bool log_upload_in_progress_;

  
  
  bool idle_since_last_transmission_;

  
  int session_id_;

  
  
  base::WeakPtrFactory<MetricsService> self_ptr_factory_;

  
  
  base::WeakPtrFactory<MetricsService> state_saver_factory_;

  
  scoped_ptr<MetricsReportingScheduler> scheduler_;

  
  base::TimeTicks first_updated_time_;

  
  base::TimeTicks last_updated_time_;

  
  SyntheticTrialGroups synthetic_trial_groups_;

  
  static ExecutionPhase execution_phase_;

  
  
  static ShutdownCleanliness clean_shutdown_status_;

  friend class ::MetricsServiceAccessor;

  FRIEND_TEST_ALL_PREFIXES(MetricsServiceTest, IsPluginProcess);
  FRIEND_TEST_ALL_PREFIXES(MetricsServiceTest,
                           PermutedEntropyCacheClearedWhenLowEntropyReset);
  FRIEND_TEST_ALL_PREFIXES(MetricsServiceTest, RegisterSyntheticTrial);

  DISALLOW_COPY_AND_ASSIGN(MetricsService);
};

}  

#endif  
