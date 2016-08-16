// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DEVICE_INFO_SYNC_SERVICE_H_
#define COMPONENTS_SYNC_DRIVER_DEVICE_INFO_SYNC_SERVICE_H_

#include "base/observer_list.h"
#include "components/sync_driver/device_info_tracker.h"
#include "sync/api/sync_change_processor.h"
#include "sync/api/sync_data.h"
#include "sync/api/sync_error_factory.h"
#include "sync/api/syncable_service.h"

namespace sync_driver {

class LocalDeviceInfoProvider;

class DeviceInfoSyncService : public syncer::SyncableService,
                              public DeviceInfoTracker {
 public:
  explicit DeviceInfoSyncService(
      LocalDeviceInfoProvider* local_device_info_provider);
  virtual ~DeviceInfoSyncService();

  
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> error_handler) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(
      syncer::ModelType type) const OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;

  
  virtual scoped_ptr<DeviceInfo> GetDeviceInfo(
      const std::string& client_id) const OVERRIDE;
  virtual ScopedVector<DeviceInfo> GetAllDeviceInfo() const OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;

  
  void UpdateLocalDeviceBackupTime(base::Time backup_time);
  
  base::Time GetLocalDeviceBackupTime() const;

 private:
  
  syncer::SyncData CreateLocalData(const DeviceInfo* info);
  
  static syncer::SyncData CreateLocalData(
      const sync_pb::EntitySpecifics& entity);

  
  static DeviceInfo* CreateDeviceInfo(const syncer::SyncData sync_data);
  
  void StoreSyncData(const std::string& client_id,
                     const syncer::SyncData& sync_data);
  
  void DeleteSyncData(const std::string& client_id);
  
  void NotifyObservers();

  
  
  
  bool UpdateBackupTime(syncer::SyncData* sync_data);

  
  int64 local_device_backup_time() const { return local_device_backup_time_; }
  bool has_local_device_backup_time() const {
    return local_device_backup_time_ >= 0;
  }
  void set_local_device_backup_time(int64 value) {
    local_device_backup_time_ = value;
  }
  void clear_local_device_backup_time() { local_device_backup_time_ = -1; }

  
  
  int64 local_device_backup_time_;

  
  const LocalDeviceInfoProvider* const local_device_info_provider_;

  
  
  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;
  scoped_ptr<syncer::SyncErrorFactory> error_handler_;

  
  typedef std::map<std::string, syncer::SyncData> SyncDataMap;
  SyncDataMap all_data_;

  
  ObserverList<Observer, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(DeviceInfoSyncService);
};

}  

#endif  
