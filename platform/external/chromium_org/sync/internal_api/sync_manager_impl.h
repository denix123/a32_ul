// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_SYNC_MANAGER_H_
#define SYNC_INTERNAL_API_SYNC_MANAGER_H_

#include <string>
#include <vector>

#include "net/base/network_change_notifier.h"
#include "sync/base/sync_export.h"
#include "sync/engine/all_status.h"
#include "sync/engine/net/server_connection_manager.h"
#include "sync/engine/nudge_handler.h"
#include "sync/engine/sync_engine_event_listener.h"
#include "sync/internal_api/change_reorder_buffer.h"
#include "sync/internal_api/debug_info_event_listener.h"
#include "sync/internal_api/js_mutation_event_observer.h"
#include "sync/internal_api/js_sync_encryption_handler_observer.h"
#include "sync/internal_api/js_sync_manager_observer.h"
#include "sync/internal_api/protocol_event_buffer.h"
#include "sync/internal_api/public/sync_context_proxy.h"
#include "sync/internal_api/public/sync_manager.h"
#include "sync/internal_api/public/user_share.h"
#include "sync/internal_api/sync_encryption_handler_impl.h"
#include "sync/js/js_backend.h"
#include "sync/syncable/directory_change_delegate.h"
#include "sync/util/cryptographer.h"
#include "sync/util/time.h"

class GURL;

namespace syncer {

class ModelTypeRegistry;
class SyncAPIServerConnectionManager;
class SyncContext;
class TypeDebugInfoObserver;
class WriteNode;
class WriteTransaction;

namespace sessions {
class SyncSessionContext;
}

class SYNC_EXPORT_PRIVATE SyncManagerImpl
    : public SyncManager,
      public net::NetworkChangeNotifier::IPAddressObserver,
      public net::NetworkChangeNotifier::ConnectionTypeObserver,
      public JsBackend,
      public SyncEngineEventListener,
      public ServerConnectionEventListener,
      public syncable::DirectoryChangeDelegate,
      public SyncEncryptionHandler::Observer,
      public NudgeHandler {
 public:
  
  explicit SyncManagerImpl(const std::string& name);
  virtual ~SyncManagerImpl();

  
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
  virtual void SetInvalidatorEnabled(bool invalidator_enabled) OVERRIDE;
  virtual void OnIncomingInvalidation(
      syncer::ModelType type,
      scoped_ptr<InvalidationInterface> invalidation) OVERRIDE;
  virtual void AddObserver(SyncManager::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(SyncManager::Observer* observer) OVERRIDE;
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
  virtual void RegisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void UnregisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual bool HasDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer) OVERRIDE;
  virtual void RequestEmitDebugInfo() OVERRIDE;

  
  virtual void OnPassphraseRequired(
      PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) OVERRIDE;
  virtual void OnPassphraseAccepted() OVERRIDE;
  virtual void OnBootstrapTokenUpdated(
      const std::string& bootstrap_token,
      BootstrapTokenType type) OVERRIDE;
  virtual void OnEncryptedTypesChanged(
      ModelTypeSet encrypted_types,
      bool encrypt_everything) OVERRIDE;
  virtual void OnEncryptionComplete() OVERRIDE;
  virtual void OnCryptographerStateChanged(
      Cryptographer* cryptographer) OVERRIDE;
  virtual void OnPassphraseTypeChanged(
      PassphraseType type,
      base::Time explicit_passphrase_time) OVERRIDE;

  
  virtual void OnSyncCycleEvent(const SyncCycleEvent& event) OVERRIDE;
  virtual void OnActionableError(const SyncProtocolError& error) OVERRIDE;
  virtual void OnRetryTimeChanged(base::Time retry_time) OVERRIDE;
  virtual void OnThrottledTypesChanged(ModelTypeSet throttled_types) OVERRIDE;
  virtual void OnMigrationRequested(ModelTypeSet types) OVERRIDE;
  virtual void OnProtocolEvent(const ProtocolEvent& event) OVERRIDE;

  
  virtual void OnServerConnectionEvent(
      const ServerConnectionEvent& event) OVERRIDE;

  
  virtual void SetJsEventHandler(
      const WeakHandle<JsEventHandler>& event_handler) OVERRIDE;

  
  
  
  
  virtual void HandleTransactionCompleteChangeEvent(
      ModelTypeSet models_with_changes) OVERRIDE;
  virtual ModelTypeSet HandleTransactionEndingChangeEvent(
      const syncable::ImmutableWriteTransactionInfo& write_transaction_info,
      syncable::BaseTransaction* trans) OVERRIDE;
  virtual void HandleCalculateChangesChangeEventFromSyncApi(
      const syncable::ImmutableWriteTransactionInfo& write_transaction_info,
      syncable::BaseTransaction* trans,
      std::vector<int64>* entries_changed) OVERRIDE;
  virtual void HandleCalculateChangesChangeEventFromSyncer(
      const syncable::ImmutableWriteTransactionInfo& write_transaction_info,
      syncable::BaseTransaction* trans,
      std::vector<int64>* entries_changed) OVERRIDE;

  
  virtual void RefreshTypes(ModelTypeSet types) OVERRIDE;

  
  
  virtual void OnIPAddressChanged() OVERRIDE;
  
  virtual void OnConnectionTypeChanged(
      net::NetworkChangeNotifier::ConnectionType) OVERRIDE;

  
  virtual void NudgeForInitialDownload(syncer::ModelType type) OVERRIDE;
  virtual void NudgeForCommit(syncer::ModelType type) OVERRIDE;
  virtual void NudgeForRefresh(syncer::ModelType type) OVERRIDE;

  const SyncScheduler* scheduler() const;

  bool GetHasInvalidAuthTokenForTest() const;

 protected:
  
  virtual void NotifyInitializationSuccess();
  virtual void NotifyInitializationFailure();

 private:
  friend class SyncManagerTest;
  FRIEND_TEST_ALL_PREFIXES(SyncManagerTest, NudgeDelayTest);
  FRIEND_TEST_ALL_PREFIXES(SyncManagerTest, PurgeDisabledTypes);
  FRIEND_TEST_ALL_PREFIXES(SyncManagerTest, PurgeUnappliedTypes);

  struct NotificationInfo {
    NotificationInfo();
    ~NotificationInfo();

    int total_count;
    std::string payload;

    
    base::DictionaryValue* ToValue() const;
  };

  base::TimeDelta GetNudgeDelayTimeDelta(const ModelType& model_type);

  typedef std::map<ModelType, NotificationInfo> NotificationInfoMap;

  
  
  
  
  
  bool VisiblePositionsDiffer(
      const syncable::EntryKernelMutation& mutation) const;

  
  
  
  bool VisiblePropertiesDiffer(
      const syncable::EntryKernelMutation& mutation,
      Cryptographer* cryptographer) const;

  
  bool OpenDirectory(const std::string& username);

  
  
  
  
  bool PurgeDisabledTypes(ModelTypeSet to_purge,
                          ModelTypeSet to_journal,
                          ModelTypeSet to_unapply);

  void RequestNudgeForDataTypes(
      const tracked_objects::Location& nudge_location,
      ModelTypeSet type);

  
  
  
  void SetExtraChangeRecordData(int64 id,
                                ModelType type,
                                ChangeReorderBuffer* buffer,
                                Cryptographer* cryptographer,
                                const syncable::EntryKernel& original,
                                bool existed_before,
                                bool exists_now);

  
  void OnNetworkConnectivityChangedImpl();

  syncable::Directory* directory();

  base::FilePath database_path_;

  const std::string name_;

  base::ThreadChecker thread_checker_;

  
  
  
  
  
  
  
  
  
  WeakHandle<SyncManagerImpl> weak_handle_this_;

  
  
  UserShare share_;

  
  
  WeakHandle<SyncManager::ChangeObserver> change_observer_;

  ObserverList<SyncManager::Observer> observers_;

  
  
  scoped_ptr<SyncAPIServerConnectionManager> connection_manager_;

  
  
  scoped_ptr<ModelTypeRegistry> model_type_registry_;

  
  scoped_ptr<SyncContext> sync_context_;
  scoped_ptr<SyncContextProxy> sync_context_proxy_;

  
  
  scoped_ptr<sessions::SyncSessionContext> session_context_;

  
  
  scoped_ptr<SyncScheduler> scheduler_;

  
  
  AllStatus allstatus_;

  
  
  
  
  
  
  typedef std::map<int, ImmutableChangeRecordList> ChangeRecordMap;
  ChangeRecordMap change_records_;

  SyncManager::ChangeDelegate* change_delegate_;

  
  bool initialized_;

  bool observing_network_connectivity_changes_;

  
  
  NotificationInfoMap notification_info_map_;

  
  JsSyncManagerObserver js_sync_manager_observer_;
  JsMutationEventObserver js_mutation_event_observer_;
  JsSyncEncryptionHandlerObserver js_sync_encryption_handler_observer_;

  
  DebugInfoEventListener debug_info_event_listener_;

  ProtocolEventBuffer protocol_event_buffer_;

  scoped_ptr<UnrecoverableErrorHandler> unrecoverable_error_handler_;
  ReportUnrecoverableErrorFunction report_unrecoverable_error_function_;

  
  
  
  scoped_ptr<SyncEncryptionHandlerImpl> sync_encryption_handler_;

  base::WeakPtrFactory<SyncManagerImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncManagerImpl);
};

}  

#endif  
