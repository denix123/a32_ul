// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_SYNCABLE_SERVICE_H__
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_SYNCABLE_SERVICE_H__

#if !defined(PASSWORD_MANAGER_ENABLE_SYNC)
#error "Only build this file when sync is enabled in Password Manager."
#endif

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "components/password_manager/core/browser/password_store_change.h"
#include "sync/api/sync_change.h"
#include "sync/api/sync_data.h"
#include "sync/api/sync_error.h"
#include "sync/api/syncable_service.h"
#include "sync/protocol/password_specifics.pb.h"
#include "sync/protocol/sync.pb.h"

namespace autofill {
struct PasswordForm;
}

namespace syncer {
class SyncErrorFactory;
}

namespace password_manager {

class PasswordStoreSync;

class PasswordSyncableService : public syncer::SyncableService,
                                public base::NonThreadSafe {
 public:
  
  
  
  explicit PasswordSyncableService(PasswordStoreSync* password_store);
  virtual ~PasswordSyncableService();

  
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

  
  void ActOnPasswordStoreChanges(const PasswordStoreChangeList& changes);

  
  
  void InjectStartSyncFlare(
      const syncer::SyncableService::StartSyncFlare& flare);

 private:
  typedef std::vector<autofill::PasswordForm*> PasswordForms;
  
  typedef std::map<std::string, autofill::PasswordForm*> PasswordEntryMap;

  
  
  typedef PasswordStoreChangeList(PasswordStoreSync::*DatabaseOperation)(
      const autofill::PasswordForm& form);

  struct SyncEntries;

  
  
  bool ReadFromPasswordStore(
      ScopedVector<autofill::PasswordForm>* password_entries,
      PasswordEntryMap* passwords_entry_map) const;

  
  void WriteToPasswordStore(const SyncEntries& entries);

  
  
  
  void CreateOrUpdateEntry(
      const syncer::SyncData& data,
      PasswordEntryMap* unmatched_data_from_password_db,
      SyncEntries* sync_entries,
      syncer::SyncChangeList* updated_db_entries);

  
  
  void WriteEntriesToDatabase(
      DatabaseOperation operation,
      const PasswordForms& entries,
      PasswordStoreChangeList* all_changes);

  
  
  scoped_ptr<syncer::SyncErrorFactory> sync_error_factory_;

  
  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;

  
  PasswordStoreSync* const password_store_;

  
  syncer::SyncableService::StartSyncFlare flare_;

  
  bool is_processing_sync_changes_;

  DISALLOW_COPY_AND_ASSIGN(PasswordSyncableService);
};

}  

#endif  
