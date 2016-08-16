// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_LAST_DOWNLOAD_FINDER_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_LAST_DOWNLOAD_FINDER_H_

#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/history/download_row.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class HistoryService;
class Profile;

namespace content {
class NotificationDetails;
class NotificationSource;
}

namespace history {
struct DownloadRow;
}

namespace safe_browsing {

class ClientIncidentReport_DownloadDetails;

class LastDownloadFinder : public content::NotificationObserver {
 public:
  
  
  
  typedef base::Callback<void(scoped_ptr<ClientIncidentReport_DownloadDetails>)>
      LastDownloadCallback;

  virtual ~LastDownloadFinder();

  
  
  
  
  
  static scoped_ptr<LastDownloadFinder> Create(
      const LastDownloadCallback& callback);

 protected:
  
  LastDownloadFinder();

 private:
  LastDownloadFinder(const std::vector<Profile*>& profiles,
                     const LastDownloadCallback& callback);

  
  
  
  void SearchInProfile(Profile* profile);

  
  
  void OnProfileHistoryLoaded(Profile* profile,
                              HistoryService* history_service);

  
  
  void AbandonSearchInProfile(Profile* profile);

  
  
  
  void OnDownloadQuery(
      Profile* profile,
      scoped_ptr<std::vector<history::DownloadRow> > downloads);

  
  
  void RemoveProfileAndReportIfDone(std::vector<Profile*>::iterator it);

  
  void ReportResults();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  LastDownloadCallback callback_;

  
  std::vector<Profile*> profiles_;

  
  content::NotificationRegistrar notification_registrar_;

  
  history::DownloadRow most_recent_row_;

  
  base::WeakPtrFactory<LastDownloadFinder> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(LastDownloadFinder);
};

}  

#endif  
