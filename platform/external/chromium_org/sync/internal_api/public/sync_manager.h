// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_SYNC_MANAGER_H_
#define SYNC_INTERNAL_API_PUBLIC_SYNC_MANAGER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/task_runner.h"
#include "base/threading/thread_checker.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/invalidation_interface.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/change_record.h"
#include "sync/internal_api/public/configure_reason.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/internal_api/public/engine/sync_status.h"
#include "sync/internal_api/public/events/protocol_event.h"
#include "sync/internal_api/public/http_post_provider_factory.h"
#include "sync/internal_api/public/internal_components_factory.h"
#include "sync/internal_api/public/shutdown_reason.h"
#include "sync/internal_api/public/sync_context_proxy.h"
#include "sync/internal_api/public/sync_encryption_handler.h"
#include "sync/internal_api/public/util/report_unrecoverable_error_function.h"
#include "sync/internal_api/public/util/unrecoverable_error_handler.h"
#include "sync/internal_api/public/util/weak_handle.h"
#include "sync/protocol/sync_protocol_error.h"

class GURL;

namespace sync_pb {
class EncryptedData;
}  

namespace syncer {

class BaseTransaction;
class CancelationSignal;
class DataTypeDebugInfoListener;
class Encryptor;
class ExtensionsActivity;
class InternalComponentsFactory;
class JsBackend;
class JsEventHandler;
class ProtocolEvent;
class SyncContextProxy;
class SyncEncryptionHandler;
class SyncScheduler;
class TypeDebugInfoObserver;
struct Experiments;
struct UserShare;

namespace sessions {
class SyncSessionSnapshot;
}  

enum ConnectionStatus {
  CONNECTION_NOT_ATTEMPTED,
  CONNECTION_OK,
  CONNECTION_AUTH_ERROR,
  CONNECTION_SERVER_ERROR
};

struct SYNC_EXPORT SyncCredentials {
  SyncCredentials();
  ~SyncCredentials();

  
  std::string email;

  
  std::string sync_token;

  
  OAuth2TokenService::ScopeSet scope_set;
};

class SYNC_EXPORT SyncManager {
 public:
  
  
  
  class SYNC_EXPORT ChangeDelegate {
   public:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnChangesApplied(
        ModelType model_type,
        int64 model_version,
        const BaseTransaction* trans,
        const ImmutableChangeRecordList& changes) = 0;

    
    
    
    
    
    
    
    
    
    
    
    virtual void OnChangesComplete(ModelType model_type) = 0;

   protected:
    virtual ~ChangeDelegate();
  };

  
  
  
  class SYNC_EXPORT_PRIVATE ChangeObserver {
   public:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnChangesApplied(
        ModelType model_type,
        int64 write_transaction_id,
        const ImmutableChangeRecordList& changes) = 0;

    virtual void OnChangesComplete(ModelType model_type) = 0;

   protected:
    virtual ~ChangeObserver();
  };

  
  
  
  
  class SYNC_EXPORT Observer {
   public:
    
    
    virtual void OnSyncCycleCompleted(
        const sessions::SyncSessionSnapshot& snapshot) = 0;

    
    
    virtual void OnConnectionStatusChange(ConnectionStatus status) = 0;

    
    
    
    
    
    
    

    virtual void OnInitializationComplete(
        const WeakHandle<JsBackend>& js_backend,
        const WeakHandle<DataTypeDebugInfoListener>& debug_info_listener,
        bool success,
        ModelTypeSet restored_types) = 0;

    virtual void OnActionableError(
        const SyncProtocolError& sync_protocol_error) = 0;

    virtual void OnMigrationRequested(ModelTypeSet types) = 0;

    virtual void OnProtocolEvent(const ProtocolEvent& event) = 0;

   protected:
    virtual ~Observer();
  };

  
  struct SYNC_EXPORT InitArgs {
    InitArgs();
    ~InitArgs();

    
    
    base::FilePath database_location;

    
    WeakHandle<JsEventHandler> event_handler;

    
    GURL service_url;

    
    scoped_ptr<HttpPostProviderFactory> post_factory;

    std::vector<scoped_refptr<ModelSafeWorker> > workers;

    
    ExtensionsActivity* extensions_activity;

    
    ChangeDelegate* change_delegate;

    
    SyncCredentials credentials;

    
    std::string invalidator_client_id;

    
    std::string restored_key_for_bootstrapping;
    std::string restored_keystore_key_for_bootstrapping;

    scoped_ptr<InternalComponentsFactory> internal_components_factory;

    
    Encryptor* encryptor;

    scoped_ptr<UnrecoverableErrorHandler> unrecoverable_error_handler;
    ReportUnrecoverableErrorFunction report_unrecoverable_error_function;

    
    
    
    
    CancelationSignal* cancelation_signal;
  };

  SyncManager();
  virtual ~SyncManager();

  
  
  
  
  virtual void Init(InitArgs* args) = 0;

  virtual ModelTypeSet InitialSyncEndedTypes() = 0;

  
  
  virtual ModelTypeSet GetTypesWithEmptyProgressMarkerToken(
      ModelTypeSet types) = 0;

  
  
  
  virtual bool PurgePartiallySyncedTypes() = 0;

  
  virtual void UpdateCredentials(const SyncCredentials& credentials) = 0;

  
  virtual void StartSyncingNormally(
      const ModelSafeRoutingInfo& routing_info) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void ConfigureSyncer(
      ConfigureReason reason,
      ModelTypeSet to_download,
      ModelTypeSet to_purge,
      ModelTypeSet to_journal,
      ModelTypeSet to_unapply,
      const ModelSafeRoutingInfo& new_routing_info,
      const base::Closure& ready_task,
      const base::Closure& retry_task) = 0;

  
  virtual void SetInvalidatorEnabled(bool invalidator_enabled) = 0;

  
  virtual void OnIncomingInvalidation(
      syncer::ModelType type,
      scoped_ptr<syncer::InvalidationInterface> invalidation) = 0;

  
  
  
  virtual void AddObserver(Observer* observer) = 0;

  
  
  
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual SyncStatus GetDetailedStatus() const = 0;

  
  
  virtual void SaveChanges() = 0;

  
  virtual void ShutdownOnSyncThread(ShutdownReason reason) = 0;

  
  virtual UserShare* GetUserShare() = 0;

  
  virtual syncer::SyncContextProxy* GetSyncContextProxy() = 0;

  
  
  virtual const std::string cache_guid() = 0;

  
  
  
  virtual bool ReceivedExperiment(Experiments* experiments) = 0;

  
  
  virtual bool HasUnsyncedItems() = 0;

  
  virtual SyncEncryptionHandler* GetEncryptionHandler() = 0;

  virtual scoped_ptr<base::ListValue> GetAllNodesForType(
      syncer::ModelType type) = 0;

  
  virtual void RefreshTypes(ModelTypeSet types) = 0;

  
  virtual ScopedVector<syncer::ProtocolEvent> GetBufferedProtocolEvents() = 0;

  
  virtual void RegisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) = 0;
  virtual void UnregisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) = 0;
  virtual bool HasDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) = 0;

  
  
  virtual void RequestEmitDebugInfo() = 0;
};

}  

#endif  
