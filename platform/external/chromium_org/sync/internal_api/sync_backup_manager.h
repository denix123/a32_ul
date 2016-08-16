// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_SYNC_BACKUP_MANAGER_H_
#define SYNC_INTERNAL_API_SYNC_BACKUP_MANAGER_H_

#include <set>

#include "sync/internal_api/sync_rollback_manager_base.h"
#include "url/gurl.h"

namespace syncer {

class SYNC_EXPORT_PRIVATE SyncBackupManager : public SyncRollbackManagerBase {
 public:
  SyncBackupManager();
  virtual ~SyncBackupManager();

  
  virtual void Init(InitArgs* args) OVERRIDE;
  virtual void SaveChanges() OVERRIDE;
  virtual SyncStatus GetDetailedStatus() const OVERRIDE;
  virtual void ShutdownOnSyncThread(ShutdownReason reason) OVERRIDE;

  
  virtual ModelTypeSet HandleTransactionEndingChangeEvent(
      const syncable::ImmutableWriteTransactionInfo& write_transaction_info,
      syncable::BaseTransaction* trans) OVERRIDE;

  virtual void RegisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void UnregisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual bool HasDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void RequestEmitDebugInfo() OVERRIDE;

 private:
  
  
  void NormalizeEntries();

  // Manipulate preference nodes so that they'll be overwritten by local
  
  
  
  void HideSyncPreference(ModelType pref_type);

  
  std::set<int64> unsynced_;

  
  bool in_normalization_;

  SyncStatus status_;

  DISALLOW_COPY_AND_ASSIGN(SyncBackupManager);
};

}  

#endif  
