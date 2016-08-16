// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_APP_LIST_SYNCABLE_SERVICE_H_
#define CHROME_BROWSER_UI_APP_LIST_APP_LIST_SYNCABLE_SERVICE_H_

#include <map>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/sync/glue/sync_start_util.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "sync/api/string_ordinal.h"
#include "sync/api/sync_change.h"
#include "sync/api/sync_change_processor.h"
#include "sync/api/sync_error_factory.h"
#include "sync/api/syncable_service.h"
#include "sync/protocol/app_list_specifics.pb.h"

class DriveAppProvider;
class ExtensionAppModelBuilder;
class Profile;

namespace extensions {
class ExtensionSystem;
}

namespace sync_pb {
class AppListSpecifics;
}

namespace app_list {

class AppListFolderItem;
class AppListItem;
class AppListModel;

class AppListSyncableService : public syncer::SyncableService,
                               public KeyedService,
                               public content::NotificationObserver {
 public:
  struct SyncItem {
    SyncItem(const std::string& id,
             sync_pb::AppListSpecifics::AppListItemType type);
    ~SyncItem();
    const std::string item_id;
    sync_pb::AppListSpecifics::AppListItemType item_type;
    std::string item_name;
    std::string parent_id;
    syncer::StringOrdinal page_ordinal;
    syncer::StringOrdinal item_ordinal;

    std::string ToString() const;
  };

  
  AppListSyncableService(Profile* profile,
                         extensions::ExtensionSystem* extension_system);

  virtual ~AppListSyncableService();

  
  
  void AddItem(scoped_ptr<AppListItem> app_item);

  
  void RemoveItem(const std::string& id);

  
  void UpdateItem(AppListItem* app_item);

  
  const SyncItem* GetSyncItem(const std::string& id) const;

  
  void SetOemFolderName(const std::string& name);

  Profile* profile() { return profile_; }
  AppListModel* model() { return model_.get(); }
  size_t GetNumSyncItemsForTest() const { return sync_items_.size(); }
  const std::string& GetOemFolderNameForTest() const {
    return oem_folder_name_;
  }
  void ResetDriveAppProviderForTest();

  
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

 private:
  class ModelObserver;
  typedef std::map<std::string, SyncItem*> SyncItemMap;

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  void BuildModel();

  
  bool SyncStarted();

  
  
  
  SyncItem* FindOrAddSyncItem(AppListItem* app_item);

  
  SyncItem* CreateSyncItemFromAppItem(AppListItem* app_item);

  
  
  void AddOrUpdateFromSyncItem(AppListItem* app_item);

  
  
  
  bool RemoveDefaultApp(AppListItem* item, SyncItem* sync_item);

  
  void DeleteSyncItem(SyncItem* sync_item);

  
  void UpdateSyncItem(AppListItem* app_item);

  
  void RemoveSyncItem(const std::string& id);

  
  void ResolveFolderPositions();

  
  
  void PruneEmptySyncFolders();

  
  
  bool ProcessSyncItemSpecifics(const sync_pb::AppListSpecifics& specifics);

  
  
  void ProcessNewSyncItem(SyncItem* sync_item);

  
  void ProcessExistingSyncItem(SyncItem* sync_item);

  
  void UpdateAppItemFromSyncItem(const SyncItem* sync_item,
                                 AppListItem* app_item);

  
  void SendSyncChange(SyncItem* sync_item,
                      syncer::SyncChange::SyncChangeType sync_change_type);

  
  SyncItem* FindSyncItem(const std::string& item_id);

  
  SyncItem* CreateSyncItem(
      const std::string& item_id,
      sync_pb::AppListSpecifics::AppListItemType item_type);

  
  void DeleteSyncItemSpecifics(const sync_pb::AppListSpecifics& specifics);

  
  
  std::string FindOrCreateOemFolder();

  
  
  syncer::StringOrdinal GetOemFolderPos();

  
  
  bool AppIsOem(const std::string& id);

  Profile* profile_;
  extensions::ExtensionSystem* extension_system_;
  content::NotificationRegistrar registrar_;
  scoped_ptr<AppListModel> model_;
  scoped_ptr<ModelObserver> model_observer_;
  scoped_ptr<ExtensionAppModelBuilder> apps_builder_;
  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;
  scoped_ptr<syncer::SyncErrorFactory> sync_error_handler_;
  SyncItemMap sync_items_;
  syncer::SyncableService::StartSyncFlare flare_;
  bool initial_sync_data_processed_;
  bool first_app_list_sync_;
  std::string oem_folder_name_;

  
  scoped_ptr<DriveAppProvider> drive_app_provider_;

  DISALLOW_COPY_AND_ASSIGN(AppListSyncableService);
};

}  

#endif  
