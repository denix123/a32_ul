// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICE_CLIENT_H_
#define CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICE_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "chrome/browser/memory_details.h"
#include "chrome/browser/metrics/network_stats_uploader.h"
#include "components/metrics/metrics_service_client.h"
#include "components/metrics/profiler/tracking_synchronizer_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class ChromeOSMetricsProvider;
class GoogleUpdateMetricsProviderWin;
class PluginMetricsProvider;
class PrefRegistrySimple;

#if !defined(OS_CHROMEOS) && !defined(OS_IOS)
class SigninStatusMetricsProvider;
#endif

namespace base {
class FilePath;
}

namespace metrics {
class MetricsService;
class MetricsStateManager;
class ProfilerMetricsProvider;
}

class ChromeMetricsServiceClient
    : public metrics::MetricsServiceClient,
      public metrics::TrackingSynchronizerObserver,
      public content::NotificationObserver {
 public:
  virtual ~ChromeMetricsServiceClient();

  
  static scoped_ptr<ChromeMetricsServiceClient> Create(
      metrics::MetricsStateManager* state_manager,
      PrefService* local_state);

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual void SetMetricsClientId(const std::string& client_id) OVERRIDE;
  virtual bool IsOffTheRecordSessionActive() OVERRIDE;
  virtual std::string GetApplicationLocale() OVERRIDE;
  virtual bool GetBrand(std::string* brand_code) OVERRIDE;
  virtual metrics::SystemProfileProto::Channel GetChannel() OVERRIDE;
  virtual std::string GetVersionString() OVERRIDE;
  virtual void OnLogUploadComplete() OVERRIDE;
  virtual void StartGatheringMetrics(
      const base::Closure& done_callback) OVERRIDE;
  virtual void CollectFinalMetrics(const base::Closure& done_callback)
      OVERRIDE;
  virtual scoped_ptr<metrics::MetricsLogUploader> CreateUploader(
      const std::string& server_url,
      const std::string& mime_type,
      const base::Callback<void(int)>& on_upload_complete) OVERRIDE;
  virtual base::string16 GetRegistryBackupKey() OVERRIDE;

  metrics::MetricsService* metrics_service() { return metrics_service_.get(); }

  void LogPluginLoadingError(const base::FilePath& plugin_path);

 private:
  explicit ChromeMetricsServiceClient(
      metrics::MetricsStateManager* state_manager);

  
  void Initialize();

  
  void OnInitTaskGotHardwareClass();

  
  
  void OnInitTaskGotPluginInfo();

  
  
  void OnInitTaskGotGoogleUpdateData();

  
  virtual void ReceivedProfilerData(
      const tracked_objects::ProcessDataSnapshot& process_data,
      int process_type) OVERRIDE;
  virtual void FinishedReceivingProfilerData() OVERRIDE;

  
  
  void OnMemoryDetailCollectionDone();
  void OnHistogramSynchronizationDone();

  
  void RecordCommandLineMetrics();

  
  
  
  
  void RegisterForNotifications();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

#if defined(OS_WIN)
  
  
  void CountBrowserCrashDumpAttempts();
#endif  

  base::ThreadChecker thread_checker_;

  
  metrics::MetricsStateManager* metrics_state_manager_;

  
  scoped_ptr<metrics::MetricsService> metrics_service_;

  content::NotificationRegistrar registrar_;

  
  
  ChromeOSMetricsProvider* chromeos_metrics_provider_;

  NetworkStatsUploader network_stats_uploader_;

  
  base::Closure collect_final_metrics_done_callback_;

  
  bool waiting_for_collect_final_metrics_step_;

  
  int num_async_histogram_fetches_in_progress_;

  
  
  metrics::ProfilerMetricsProvider* profiler_metrics_provider_;

#if defined(ENABLE_PLUGINS)
  
  
  PluginMetricsProvider* plugin_metrics_provider_;
#endif

#if defined(OS_WIN)
  
  
  GoogleUpdateMetricsProviderWin* google_update_metrics_provider_;
#endif

  
  base::Closure finished_gathering_initial_metrics_callback_;

  
  
  MemoryGrowthTracker memory_growth_tracker_;

  base::WeakPtrFactory<ChromeMetricsServiceClient> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromeMetricsServiceClient);
};

#endif  
