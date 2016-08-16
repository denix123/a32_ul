// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_STORAGE_SYNC_STORAGE_BACKEND_H_
#define CHROME_BROWSER_EXTENSIONS_API_STORAGE_SYNC_STORAGE_BACKEND_H_

#include <map>
#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/api/storage/settings_observer.h"
#include "extensions/browser/api/storage/settings_storage_factory.h"
#include "extensions/browser/api/storage/settings_storage_quota_enforcer.h"
#include "sync/api/syncable_service.h"

namespace syncer {
class SyncErrorFactory;
}

namespace extensions {

class SettingsSyncProcessor;
class SyncableSettingsStorage;

class SyncStorageBackend : public syncer::SyncableService {
 public:
  
  
  
  
  SyncStorageBackend(
      const scoped_refptr<SettingsStorageFactory>& storage_factory,
      const base::FilePath& base_path,
      const SettingsStorageQuotaEnforcer::Limits& quota,
      const scoped_refptr<SettingsObserverList>& observers,
      syncer::ModelType sync_type,
      const syncer::SyncableService::StartSyncFlare& flare);

  virtual ~SyncStorageBackend();

  virtual ValueStore* GetStorage(const std::string& extension_id);
  virtual void DeleteStorage(const std::string& extension_id);

  
  virtual syncer::SyncDataList GetAllSyncData(syncer::ModelType type)
      const OVERRIDE;
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> sync_error_factory) OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;

 private:
  
  
  SyncableSettingsStorage* GetOrCreateStorageWithSyncData(
      const std::string& extension_id,
      const base::DictionaryValue& sync_data) const;

  
  
  std::set<std::string> GetKnownExtensionIDs() const;

  
  scoped_ptr<SettingsSyncProcessor> CreateSettingsSyncProcessor(
      const std::string& extension_id) const;

  
  const scoped_refptr<SettingsStorageFactory> storage_factory_;

  
  const base::FilePath base_path_;

  
  const SettingsStorageQuotaEnforcer::Limits quota_;

  
  const scoped_refptr<SettingsObserverList> observers_;

  
  
  typedef std::map<std::string, linked_ptr<SyncableSettingsStorage> >
      StorageObjMap;
  mutable StorageObjMap storage_objs_;

  
  syncer::ModelType sync_type_;

  
  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;

  
  scoped_ptr<syncer::SyncErrorFactory> sync_error_factory_;

  syncer::SyncableService::StartSyncFlare flare_;

  DISALLOW_COPY_AND_ASSIGN(SyncStorageBackend);
};

}  

#endif  
