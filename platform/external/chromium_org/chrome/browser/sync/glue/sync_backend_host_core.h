// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_CORE_H_
#define CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_CORE_H_

#include "base/memory/ref_counted.h"

#include "base/timer/timer.h"
#include "chrome/browser/sync/glue/sync_backend_host_impl.h"
#include "components/sync_driver/system_encryptor.h"
#include "sync/internal_api/public/base/cancelation_signal.h"
#include "sync/internal_api/public/sessions/type_debug_info_observer.h"
#include "sync/internal_api/public/shutdown_reason.h"
#include "sync/internal_api/public/sync_encryption_handler.h"
#include "url/gurl.h"

namespace browser_sync {

class SyncBackendHostImpl;

struct DoInitializeOptions {
  DoInitializeOptions(
      base::MessageLoop* sync_loop,
      SyncBackendRegistrar* registrar,
      const syncer::ModelSafeRoutingInfo& routing_info,
      const std::vector<scoped_refptr<syncer::ModelSafeWorker> >& workers,
      const scoped_refptr<syncer::ExtensionsActivity>& extensions_activity,
      const syncer::WeakHandle<syncer::JsEventHandler>& event_handler,
      const GURL& service_url,
      scoped_ptr<syncer::HttpPostProviderFactory> http_bridge_factory,
      const syncer::SyncCredentials& credentials,
      const std::string& invalidator_client_id,
      scoped_ptr<syncer::SyncManagerFactory> sync_manager_factory,
      bool delete_sync_data_folder,
      const std::string& restored_key_for_bootstrapping,
      const std::string& restored_keystore_key_for_bootstrapping,
      scoped_ptr<syncer::InternalComponentsFactory> internal_components_factory,
      scoped_ptr<syncer::UnrecoverableErrorHandler> unrecoverable_error_handler,
      syncer::ReportUnrecoverableErrorFunction
          report_unrecoverable_error_function);
  ~DoInitializeOptions();

  base::MessageLoop* sync_loop;
  SyncBackendRegistrar* registrar;
  syncer::ModelSafeRoutingInfo routing_info;
  std::vector<scoped_refptr<syncer::ModelSafeWorker> > workers;
  scoped_refptr<syncer::ExtensionsActivity> extensions_activity;
  syncer::WeakHandle<syncer::JsEventHandler> event_handler;
  GURL service_url;
  
  scoped_ptr<syncer::HttpPostProviderFactory> http_bridge_factory;
  syncer::SyncCredentials credentials;
  const std::string invalidator_client_id;
  scoped_ptr<syncer::SyncManagerFactory> sync_manager_factory;
  std::string lsid;
  bool delete_sync_data_folder;
  std::string restored_key_for_bootstrapping;
  std::string restored_keystore_key_for_bootstrapping;
  scoped_ptr<syncer::InternalComponentsFactory> internal_components_factory;
  scoped_ptr<syncer::UnrecoverableErrorHandler> unrecoverable_error_handler;
  syncer::ReportUnrecoverableErrorFunction
      report_unrecoverable_error_function;
};

struct DoConfigureSyncerTypes {
  DoConfigureSyncerTypes();
  ~DoConfigureSyncerTypes();
  syncer::ModelTypeSet to_download;
  syncer::ModelTypeSet to_purge;
  syncer::ModelTypeSet to_journal;
  syncer::ModelTypeSet to_unapply;
};

class SyncBackendHostCore
    : public base::RefCountedThreadSafe<SyncBackendHostCore>,
      public syncer::SyncEncryptionHandler::Observer,
      public syncer::SyncManager::Observer,
      public syncer::TypeDebugInfoObserver {
 public:
  SyncBackendHostCore(const std::string& name,
       const base::FilePath& sync_data_folder_path,
       bool has_sync_setup_completed,
       const base::WeakPtr<SyncBackendHostImpl>& backend);

  
  
  
  virtual void OnSyncCycleCompleted(
      const syncer::sessions::SyncSessionSnapshot& snapshot) OVERRIDE;
  virtual void OnInitializationComplete(
      const syncer::WeakHandle<syncer::JsBackend>& js_backend,
      const syncer::WeakHandle<syncer::DataTypeDebugInfoListener>&
          debug_info_listener,
      bool success,
      syncer::ModelTypeSet restored_types) OVERRIDE;
  virtual void OnConnectionStatusChange(
      syncer::ConnectionStatus status) OVERRIDE;
  virtual void OnActionableError(
      const syncer::SyncProtocolError& sync_error) OVERRIDE;
  virtual void OnMigrationRequested(syncer::ModelTypeSet types) OVERRIDE;
  virtual void OnProtocolEvent(const syncer::ProtocolEvent& event) OVERRIDE;

  
  virtual void OnPassphraseRequired(
      syncer::PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) OVERRIDE;
  virtual void OnPassphraseAccepted() OVERRIDE;
  virtual void OnBootstrapTokenUpdated(
      const std::string& bootstrap_token,
      syncer::BootstrapTokenType type) OVERRIDE;
  virtual void OnEncryptedTypesChanged(
      syncer::ModelTypeSet encrypted_types,
      bool encrypt_everything) OVERRIDE;
  virtual void OnEncryptionComplete() OVERRIDE;
  virtual void OnCryptographerStateChanged(
      syncer::Cryptographer* cryptographer) OVERRIDE;
  virtual void OnPassphraseTypeChanged(syncer::PassphraseType type,
                                       base::Time passphrase_time) OVERRIDE;

  
  virtual void OnCommitCountersUpdated(
      syncer::ModelType type,
      const syncer::CommitCounters& counters) OVERRIDE;
  virtual void OnUpdateCountersUpdated(
      syncer::ModelType type,
      const syncer::UpdateCounters& counters) OVERRIDE;
  virtual void OnStatusCountersUpdated(
      syncer::ModelType type,
      const syncer::StatusCounters& counters) OVERRIDE;

  
  void DoOnInvalidatorStateChange(syncer::InvalidatorState state);

  
  void DoOnIncomingInvalidation(
      const syncer::ObjectIdInvalidationMap& invalidation_map);

  
  
  
  
  
  
  
  
  
  void DoInitialize(scoped_ptr<DoInitializeOptions> options);

  
  
  void DoUpdateCredentials(const syncer::SyncCredentials& credentials);

  
  
  void DoStartSyncing(const syncer::ModelSafeRoutingInfo& routing_info);

  
  void DoSetEncryptionPassphrase(const std::string& passphrase,
                                 bool is_explicit);

  
  void DoSetDecryptionPassphrase(const std::string& passphrase);

  
  
  void DoEnableEncryptEverything();

  
  void DoRefreshTypes(syncer::ModelTypeSet types);

  
  
  void OnControlTypesDownloadRetry();

  
  
  void DoInitialProcessControlTypes();

  
  
  
  
  
  void ShutdownOnUIThread();
  void DoShutdown(syncer::ShutdownReason reason);
  void DoDestroySyncManager(syncer::ShutdownReason reason);

  
  void DoConfigureSyncer(
      syncer::ConfigureReason reason,
      const DoConfigureSyncerTypes& config_types,
      const syncer::ModelSafeRoutingInfo routing_info,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task,
      const base::Closure& retry_callback);
  void DoFinishConfigureDataTypes(
      syncer::ModelTypeSet types_to_config,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task);
  void DoRetryConfiguration(
      const base::Closure& retry_callback);

  
  
  

  syncer::SyncManager* sync_manager() { return sync_manager_.get(); }

  void SendBufferedProtocolEventsAndEnableForwarding();
  void DisableProtocolEventForwarding();

  
  
  
  void EnableDirectoryTypeDebugInfoForwarding();

  
  void DisableDirectoryTypeDebugInfoForwarding();

  
  
  
  void DeleteSyncDataFolder();

  
  
  syncer::CancelationSignal* GetRequestContextCancelationSignal() {
    return &release_request_context_signal_;
  }

  void GetAllNodesForTypes(
      syncer::ModelTypeSet types,
      scoped_refptr<base::SequencedTaskRunner> task_runner,
      base::Callback<void(const std::vector<syncer::ModelType>& type,
                          ScopedVector<base::ListValue>) > callback);

 private:
  friend class base::RefCountedThreadSafe<SyncBackendHostCore>;
  friend class SyncBackendHostForProfileSyncTest;

  virtual ~SyncBackendHostCore();

  
  
  
  
  void StartSavingChanges();

  
  
  
  
  
  void SaveChanges();

  
  const std::string name_;

  
  const base::FilePath sync_data_folder_path_;

  
  syncer::WeakHandle<SyncBackendHostImpl> host_;

  
  
  base::MessageLoop* sync_loop_;

  
  
  SyncBackendRegistrar* registrar_;

  
  scoped_ptr<base::RepeatingTimer<SyncBackendHostCore> > save_changes_timer_;

  
  sync_driver::SystemEncryptor encryptor_;

  
  scoped_ptr<syncer::SyncManager> sync_manager_;

  
  
  
  syncer::WeakHandle<syncer::JsBackend> js_backend_;
  syncer::WeakHandle<syncer::DataTypeDebugInfoListener> debug_info_listener_;

  
  
  
  
  
  syncer::CancelationSignal release_request_context_signal_;
  syncer::CancelationSignal stop_syncing_signal_;

  
  
  const bool has_sync_setup_completed_;

  
  bool forward_protocol_events_;

  
  bool forward_type_info_;

  base::WeakPtrFactory<SyncBackendHostCore> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncBackendHostCore);
};

}  

#endif  
