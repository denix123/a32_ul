// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_TEST_FAKE_SYNC_MANAGER_H_
#define SYNC_INTERNAL_API_PUBLIC_TEST_FAKE_SYNC_MANAGER_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "sync/internal_api/public/sync_manager.h"
#include "sync/internal_api/public/test/null_sync_context_proxy.h"
#include "sync/internal_api/public/test/test_user_share.h"

class GURL;

namespace base {
class SequencedTaskRunner;
}

namespace syncer {

class FakeSyncEncryptionHandler;

class FakeSyncManager : public SyncManager {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  FakeSyncManager(ModelTypeSet initial_sync_ended_types,
                  ModelTypeSet progress_marker_types,
                  ModelTypeSet configure_fail_types);
  virtual ~FakeSyncManager();

  
  
  
  ModelTypeSet GetAndResetCleanedTypes();

  
  
  ModelTypeSet GetAndResetDownloadedTypes();

  
  
  
  ModelTypeSet GetAndResetEnabledTypes();

  
  ModelTypeSet GetLastRefreshRequestTypes();

  
  
  ConfigureReason GetAndResetConfigureReason();

  
  virtual void OnIncomingInvalidation(
      syncer::ModelType type,
      scoped_ptr<InvalidationInterface> interface) OVERRIDE;

  
  virtual void SetInvalidatorEnabled(bool invalidator_enabled) OVERRIDE;

  
  void WaitForSyncThread();

  
  
  
  virtual void Init(InitArgs* args) OVERRIDE;
  virtual ModelTypeSet InitialSyncEndedTypes() OVERRIDE;
  virtual ModelTypeSet GetTypesWithEmptyProgressMarkerToken(
      ModelTypeSet types) OVERRIDE;
  virtual bool PurgePartiallySyncedTypes() OVERRIDE;
  virtual void UpdateCredentials(const SyncCredentials& credentials) OVERRIDE;
  virtual void StartSyncingNormally(
      const ModelSafeRoutingInfo& routing_info) OVERRIDE;
  virtual void ConfigureSyncer(
      ConfigureReason reason,
      ModelTypeSet to_download,
      ModelTypeSet to_purge,
      ModelTypeSet to_journal,
      ModelTypeSet to_unapply,
      const ModelSafeRoutingInfo& new_routing_info,
      const base::Closure& ready_task,
      const base::Closure& retry_task) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual SyncStatus GetDetailedStatus() const OVERRIDE;
  virtual void SaveChanges() OVERRIDE;
  virtual void ShutdownOnSyncThread(ShutdownReason reason) OVERRIDE;
  virtual UserShare* GetUserShare() OVERRIDE;
  virtual syncer::SyncContextProxy* GetSyncContextProxy() OVERRIDE;
  virtual const std::string cache_guid() OVERRIDE;
  virtual bool ReceivedExperiment(Experiments* experiments) OVERRIDE;
  virtual bool HasUnsyncedItems() OVERRIDE;
  virtual SyncEncryptionHandler* GetEncryptionHandler() OVERRIDE;
  virtual ScopedVector<syncer::ProtocolEvent>
      GetBufferedProtocolEvents() OVERRIDE;
  virtual scoped_ptr<base::ListValue> GetAllNodesForType(
      syncer::ModelType type) OVERRIDE;
  virtual void RefreshTypes(ModelTypeSet types) OVERRIDE;
  virtual void RegisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void UnregisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual bool HasDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void RequestEmitDebugInfo() OVERRIDE;

 private:
  scoped_refptr<base::SequencedTaskRunner> sync_task_runner_;

  ObserverList<SyncManager::Observer> observers_;

  
  ModelTypeSet initial_sync_ended_types_;
  ModelTypeSet progress_marker_types_;

  
  
  
  ModelTypeSet configure_fail_types_;
  
  ModelTypeSet cleaned_types_;
  
  ModelTypeSet downloaded_types_;
  
  ModelTypeSet enabled_types_;

  
  ModelTypeSet last_refresh_request_types_;

  
  ConfigureReason last_configure_reason_;

  scoped_ptr<FakeSyncEncryptionHandler> fake_encryption_handler_;

  TestUserShare test_user_share_;

  NullSyncContextProxy null_sync_context_proxy_;

  DISALLOW_COPY_AND_ASSIGN(FakeSyncManager);
};

}  

#endif  
