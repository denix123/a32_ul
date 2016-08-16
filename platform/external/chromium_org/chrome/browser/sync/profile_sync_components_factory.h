// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_PROFILE_SYNC_COMPONENTS_FACTORY_H__
#define CHROME_BROWSER_SYNC_PROFILE_SYNC_COMPONENTS_FACTORY_H__

#include <string>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "components/invalidation/invalidation_service.h"
#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/data_type_error_handler.h"
#include "components/sync_driver/sync_api_component_factory.h"
#include "sync/api/sync_merge_result.h"
#include "sync/internal_api/public/util/unrecoverable_error_handler.h"
#include "sync/internal_api/public/util/weak_handle.h"

class PasswordStore;
class Profile;
class ProfileSyncService;

namespace browser_sync {
class SyncBackendHost;
}  

namespace sync_driver {
class AssociatorInterface;
class ChangeProcessor;
class DataTypeEncryptionHandler;
class DataTypeErrorHandler;
class DataTypeManager;
class DataTypeManagerObserver;
class DataTypeStatusTable;
class GenericChangeProcessor;
class LocalDeviceInfoProvider;
class SyncPrefs;
}  

namespace syncer {
class DataTypeDebugInfoListener;
class SyncableService;
}  

namespace history {
class HistoryBackend;
}  

class ProfileSyncComponentsFactory
    : public sync_driver::SyncApiComponentFactory {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  struct SyncComponents {
    sync_driver::AssociatorInterface* model_associator;
    sync_driver::ChangeProcessor* change_processor;
    SyncComponents(sync_driver::AssociatorInterface* ma,
                   sync_driver::ChangeProcessor* cp)
        : model_associator(ma), change_processor(cp) {}
  };

  virtual ~ProfileSyncComponentsFactory() OVERRIDE {}

  
  
  virtual void RegisterDataTypes(ProfileSyncService* pss) = 0;

  
  
  
  virtual sync_driver::DataTypeManager* CreateDataTypeManager(
      const syncer::WeakHandle<syncer::DataTypeDebugInfoListener>&
          debug_info_listener,
      const sync_driver::DataTypeController::TypeMap* controllers,
      const sync_driver::DataTypeEncryptionHandler* encryption_handler,
      browser_sync::SyncBackendHost* backend,
      sync_driver::DataTypeManagerObserver* observer) = 0;

  
  virtual browser_sync::SyncBackendHost* CreateSyncBackendHost(
      const std::string& name,
      Profile* profile,
      invalidation::InvalidationService* invalidator,
      const base::WeakPtr<sync_driver::SyncPrefs>& sync_prefs,
      const base::FilePath& sync_folder) = 0;

  
  virtual scoped_ptr<sync_driver::LocalDeviceInfoProvider>
      CreateLocalDeviceInfoProvider() = 0;

  
  virtual SyncComponents CreateBookmarkSyncComponents(
      ProfileSyncService* profile_sync_service,
      sync_driver::DataTypeErrorHandler* error_handler) = 0;
  virtual SyncComponents CreateTypedUrlSyncComponents(
      ProfileSyncService* profile_sync_service,
      history::HistoryBackend* history_backend,
      sync_driver::DataTypeErrorHandler* error_handler) = 0;
};

#endif  
