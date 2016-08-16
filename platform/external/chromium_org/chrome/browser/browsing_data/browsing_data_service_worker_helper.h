// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_SERVICE_WORKER_HELPER_H_
#define CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_SERVICE_WORKER_HELPER_H_

#include <list>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "content/public/browser/service_worker_context.h"
#include "content/public/browser/service_worker_usage_info.h"
#include "url/gurl.h"

class Profile;

class BrowsingDataServiceWorkerHelper
    : public base::RefCountedThreadSafe<BrowsingDataServiceWorkerHelper> {
 public:
  
  
  explicit BrowsingDataServiceWorkerHelper(
      content::ServiceWorkerContext* context);

  
  
  virtual void StartFetching(const base::Callback<
      void(const std::list<content::ServiceWorkerUsageInfo>&)>& callback);
  
  virtual void DeleteServiceWorkers(const GURL& origin);

 protected:
  virtual ~BrowsingDataServiceWorkerHelper();

  
  content::ServiceWorkerContext* service_worker_context_;

  
  
  
  
  
  
  std::list<content::ServiceWorkerUsageInfo> service_worker_info_;

  
  base::Callback<void(const std::list<content::ServiceWorkerUsageInfo>&)>
      completion_callback_;

  
  
  
  
  bool is_fetching_;

 private:
  friend class base::RefCountedThreadSafe<BrowsingDataServiceWorkerHelper>;

  
  void FetchServiceWorkerUsageInfoOnIOThread();

  
  void NotifyOnUIThread();

  
  void DeleteServiceWorkersOnIOThread(const GURL& origin);

  
  void GetAllOriginsInfoCallback(
      const std::vector<content::ServiceWorkerUsageInfo>& origins);

  DISALLOW_COPY_AND_ASSIGN(BrowsingDataServiceWorkerHelper);
};

class CannedBrowsingDataServiceWorkerHelper
    : public BrowsingDataServiceWorkerHelper {
 public:
  
  struct PendingServiceWorkerUsageInfo {
    PendingServiceWorkerUsageInfo(const GURL& origin,
                                  const std::vector<GURL>& scopes);
    ~PendingServiceWorkerUsageInfo();

    bool operator<(const PendingServiceWorkerUsageInfo& other) const;

    GURL origin;
    std::vector<GURL> scopes;
  };

  explicit CannedBrowsingDataServiceWorkerHelper(
      content::ServiceWorkerContext* context);

  
  
  void AddServiceWorker(const GURL& origin, const std::vector<GURL>& scopes);

  
  void Reset();

  
  bool empty() const;

  
  size_t GetServiceWorkerCount() const;

  
  const std::set<
      CannedBrowsingDataServiceWorkerHelper::PendingServiceWorkerUsageInfo>&
      GetServiceWorkerUsageInfo() const;

  
  virtual void StartFetching(const base::Callback<void(
      const std::list<content::ServiceWorkerUsageInfo>&)>& callback) OVERRIDE;
  virtual void DeleteServiceWorkers(const GURL& origin) OVERRIDE;

 private:
  virtual ~CannedBrowsingDataServiceWorkerHelper();

  std::set<PendingServiceWorkerUsageInfo> pending_service_worker_info_;

  DISALLOW_COPY_AND_ASSIGN(CannedBrowsingDataServiceWorkerHelper);
};

#endif  
