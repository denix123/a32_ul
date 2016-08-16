// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORTING_SERVICE_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORTING_SERVICE_H_

#include <stdint.h>

#include <map>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/safe_browsing/incident_reporting/add_incident_callback.h"
#include "chrome/browser/safe_browsing/incident_reporting/delayed_analysis_callback.h"
#include "chrome/browser/safe_browsing/incident_reporting/delayed_callback_runner.h"
#include "chrome/browser/safe_browsing/incident_reporting/incident_report_uploader.h"
#include "chrome/browser/safe_browsing/incident_reporting/last_download_finder.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;
class SafeBrowsingDatabaseManager;
class SafeBrowsingService;
class TrackedPreferenceValidationDelegate;

namespace base {
class TaskRunner;
}

namespace content {
class NotificationDetails;
class NotificationSource;
}

namespace net {
class URLRequestContextGetter;
}

namespace safe_browsing {

class ClientIncidentReport;
class ClientIncidentReport_DownloadDetails;
class ClientIncidentReport_EnvironmentData;
class ClientIncidentReport_IncidentData;

class IncidentReportingService : public content::NotificationObserver {
 public:
  IncidentReportingService(SafeBrowsingService* safe_browsing_service,
                           const scoped_refptr<net::URLRequestContextGetter>&
                               request_context_getter);

  
  
  virtual ~IncidentReportingService();

  
  
  
  
  AddIncidentCallback GetAddIncidentCallback(Profile* profile);

  
  
  
  
  
  scoped_ptr<TrackedPreferenceValidationDelegate>
      CreatePreferenceValidationDelegate(Profile* profile);

  
  void RegisterDelayedAnalysisCallback(const DelayedAnalysisCallback& callback);

 protected:
  
  typedef void (*CollectEnvironmentDataFn)(
      ClientIncidentReport_EnvironmentData*);

  
  
  IncidentReportingService(
      SafeBrowsingService* safe_browsing_service,
      const scoped_refptr<net::URLRequestContextGetter>& request_context_getter,
      base::TimeDelta delayed_task_interval,
      const scoped_refptr<base::TaskRunner>& delayed_task_runner);

  
  
  
  void SetCollectEnvironmentHook(
      CollectEnvironmentDataFn collect_environment_data_hook,
      const scoped_refptr<base::TaskRunner>& task_runner);

  
  
  
  
  
  
  virtual void OnProfileAdded(Profile* profile);

  
  
  virtual scoped_ptr<LastDownloadFinder> CreateDownloadFinder(
      const LastDownloadFinder::LastDownloadCallback& callback);

  
  virtual scoped_ptr<IncidentReportUploader> StartReportUpload(
      const IncidentReportUploader::OnResultCallback& callback,
      const scoped_refptr<net::URLRequestContextGetter>& request_context_getter,
      const ClientIncidentReport& report);

  
  bool IsProcessingReport() const;

 private:
  struct ProfileContext;
  class UploadContext;

  
  typedef std::map<Profile*, ProfileContext*> ProfileContextCollection;

  
  ProfileContext* GetOrCreateProfileContext(Profile* profile);

  
  ProfileContext* GetProfileContext(Profile* profile);

  
  
  void OnProfileDestroyed(Profile* profile);

  
  
  Profile* FindEligibleProfile() const;

  
  
  void AddIncident(Profile* profile,
                   scoped_ptr<ClientIncidentReport_IncidentData> incident_data);

  
  
  void BeginReportProcessing();

  
  
  void BeginIncidentCollation();

  
  void BeginEnvironmentCollection();

  
  bool WaitingForEnvironmentCollection();

  
  
  void CancelEnvironmentCollection();

  
  
  
  void OnEnvironmentDataCollected(
      scoped_ptr<ClientIncidentReport_EnvironmentData> environment_data);

  
  
  bool WaitingToCollateIncidents();

  
  void CancelIncidentCollection();

  
  
  
  
  void OnCollationTimeout();

  
  
  
  void BeginDownloadCollection();

  
  
  
  bool WaitingForMostRecentDownload();

  
  void CancelDownloadCollection();

  
  
  void OnLastDownloadFound(
      scoped_ptr<ClientIncidentReport_DownloadDetails> last_download);

  
  
  
  void UploadIfCollectionComplete();

  
  void CancelAllReportUploads();

  
  void OnKillSwitchResult(UploadContext* context, bool is_killswitch_on);

  
  void HandleResponse(const UploadContext& context);

  
  void OnReportUploadResult(UploadContext* context,
                            IncidentReportUploader::Result result,
                            scoped_ptr<ClientIncidentResponse> response);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  base::ThreadChecker thread_checker_;

  
  
  scoped_refptr<SafeBrowsingDatabaseManager> database_manager_;

  
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;

  
  
  
  
  CollectEnvironmentDataFn collect_environment_data_fn_;

  
  
  
  scoped_refptr<base::TaskRunner> environment_collection_task_runner_;

  
  content::NotificationRegistrar notification_registrar_;

  
  
  bool environment_collection_pending_;

  
  
  bool collation_timeout_pending_;

  
  
  base::DelayTimer<IncidentReportingService> collation_timer_;

  
  
  
  scoped_ptr<ClientIncidentReport> report_;

  
  base::Time first_incident_time_;

  
  base::TimeTicks last_incident_time_;

  
  base::TimeTicks environment_collection_begin_;

  
  base::TimeTicks last_download_begin_;

  
  
  ProfileContextCollection profiles_;

  
  DelayedCallbackRunner delayed_analysis_callbacks_;

  
  ScopedVector<UploadContext> uploads_;

  
  
  scoped_ptr<LastDownloadFinder> last_download_finder_;

  
  base::WeakPtrFactory<IncidentReportingService> receiver_weak_ptr_factory_;

  
  
  
  base::WeakPtrFactory<IncidentReportingService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(IncidentReportingService);
};

}  

#endif  
