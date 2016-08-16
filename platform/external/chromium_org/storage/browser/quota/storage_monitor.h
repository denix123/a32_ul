// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_QUOTA_STORAGE_MONITOR_H_
#define STORAGE_BROWSER_QUOTA_STORAGE_MONITOR_H_

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "storage/browser/quota/storage_observer.h"

namespace content {
class StorageMonitorTestBase;
}

namespace storage {

class QuotaManager;

class STORAGE_EXPORT_PRIVATE StorageObserverList {
 public:
  StorageObserverList();
  virtual ~StorageObserverList();

  
  void AddObserver(StorageObserver* observer,
                   const StorageObserver::MonitorParams& params);
  void RemoveObserver(StorageObserver* observer);

  
  int ObserverCount() const;

  
  
  
  void OnStorageChange(const StorageObserver::Event& event);

  
  void MaybeDispatchEvent(const StorageObserver::Event& event);

  
  void ScheduleUpdateForObserver(StorageObserver* observer);

 private:
  struct STORAGE_EXPORT_PRIVATE ObserverState {
    GURL origin;
    base::TimeTicks last_notification_time;
    base::TimeDelta rate;
    bool requires_update;

    ObserverState();
  };
  typedef std::map<StorageObserver*, ObserverState> StorageObserverStateMap;

  void DispatchPendingEvent();

  StorageObserverStateMap observers_;
  base::OneShotTimer<StorageObserverList> notification_timer_;
  StorageObserver::Event pending_event_;

  friend class content::StorageMonitorTestBase;

  DISALLOW_COPY_AND_ASSIGN(StorageObserverList);
};


class STORAGE_EXPORT_PRIVATE HostStorageObservers {
 public:
  explicit HostStorageObservers(QuotaManager* quota_manager);
  virtual ~HostStorageObservers();

  bool is_initialized() const { return initialized_; }

  
  void AddObserver(
      StorageObserver* observer,
      const StorageObserver::MonitorParams& params);
  void RemoveObserver(StorageObserver* observer);
  bool ContainsObservers() const;

  
  void NotifyUsageChange(const StorageObserver::Filter& filter, int64 delta);

 private:
  void StartInitialization(const StorageObserver::Filter& filter);
  void GotHostUsageAndQuota(const StorageObserver::Filter& filter,
                            QuotaStatusCode status,
                            int64 usage,
                            int64 quota);
  void DispatchEvent(const StorageObserver::Filter& filter, bool is_update);

  QuotaManager* quota_manager_;
  StorageObserverList observers_;

  
  bool initialized_;
  bool initializing_;
  bool event_occurred_before_init_;
  int64 usage_deltas_during_init_;

  
  int64 cached_usage_;
  int64 cached_quota_;

  base::WeakPtrFactory<HostStorageObservers> weak_factory_;

  friend class content::StorageMonitorTestBase;

  DISALLOW_COPY_AND_ASSIGN(HostStorageObservers);
};


class STORAGE_EXPORT_PRIVATE StorageTypeObservers {
 public:
  explicit StorageTypeObservers(QuotaManager* quota_manager);
  virtual ~StorageTypeObservers();

  
  void AddObserver(StorageObserver* observer,
                   const StorageObserver::MonitorParams& params);
  void RemoveObserver(StorageObserver* observer);
  void RemoveObserverForFilter(StorageObserver* observer,
                               const StorageObserver::Filter& filter);

  
  const HostStorageObservers* GetHostObservers(const std::string& host) const;

  
  void NotifyUsageChange(const StorageObserver::Filter& filter, int64 delta);

 private:
  typedef std::map<std::string, HostStorageObservers*> HostObserversMap;

  QuotaManager* quota_manager_;
  HostObserversMap host_observers_map_;

  DISALLOW_COPY_AND_ASSIGN(StorageTypeObservers);
};


class STORAGE_EXPORT_PRIVATE StorageMonitor {
 public:
  explicit StorageMonitor(QuotaManager* quota_manager);
  virtual ~StorageMonitor();

  
  void AddObserver(StorageObserver* observer,
                   const StorageObserver::MonitorParams& params);
  void RemoveObserver(StorageObserver* observer);
  void RemoveObserverForFilter(StorageObserver* observer,
                               const StorageObserver::Filter& filter);

  
  const StorageTypeObservers* GetStorageTypeObservers(
      StorageType storage_type) const;

  
  void NotifyUsageChange(const StorageObserver::Filter& filter, int64 delta);

 private:
  typedef std::map<StorageType, StorageTypeObservers*> StorageTypeObserversMap;

  QuotaManager* quota_manager_;
  StorageTypeObserversMap storage_type_observers_map_;

  DISALLOW_COPY_AND_ASSIGN(StorageMonitor);
};

}  

#endif  
