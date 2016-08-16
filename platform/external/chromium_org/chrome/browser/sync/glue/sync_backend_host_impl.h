// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_IMPL_H_
#define CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_IMPL_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "chrome/browser/sync/glue/extensions_activity_monitor.h"
#include "chrome/browser/sync/glue/sync_backend_host.h"
#include "components/invalidation/invalidation_handler.h"
#include "components/sync_driver/backend_data_type_configurer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/configure_reason.h"
#include "sync/internal_api/public/sessions/sync_session_snapshot.h"
#include "sync/internal_api/public/sessions/type_debug_info_observer.h"
#include "sync/internal_api/public/sync_manager.h"
#include "sync/internal_api/public/util/report_unrecoverable_error_function.h"
#include "sync/internal_api/public/util/unrecoverable_error_handler.h"
#include "sync/internal_api/public/util/weak_handle.h"
#include "sync/protocol/encryption.pb.h"
#include "sync/protocol/sync_protocol_error.h"
#include "sync/util/extensions_activity.h"

class GURL;
class Profile;

namespace base {
class MessageLoop;
}

namespace invalidation {
class InvalidationService;
}

namespace syncer {
class NetworkResources;
class SyncManagerFactory;
}

namespace sync_driver {
class SyncPrefs;
}

namespace browser_sync {

class ChangeProcessor;
class SyncBackendHostCore;
class SyncBackendRegistrar;
struct DoInitializeOptions;

class SyncBackendHostImpl
    : public SyncBackendHost,
      public content::NotificationObserver,
      public syncer::InvalidationHandler {
 public:
  typedef syncer::SyncStatus Status;

  
  
  
  
  SyncBackendHostImpl(const std::string& name,
                      Profile* profile,
                      invalidation::InvalidationService* invalidator,
                      const base::WeakPtr<sync_driver::SyncPrefs>& sync_prefs,
                      const base::FilePath& sync_folder);
  virtual ~SyncBackendHostImpl();

  
  virtual void Initialize(
      sync_driver::SyncFrontend* frontend,
      scoped_ptr<base::Thread> sync_thread,
      const syncer::WeakHandle<syncer::JsEventHandler>& event_handler,
      const GURL& service_url,
      const syncer::SyncCredentials& credentials,
      bool delete_sync_data_folder,
      scoped_ptr<syncer::SyncManagerFactory> sync_manager_factory,
      scoped_ptr<syncer::UnrecoverableErrorHandler> unrecoverable_error_handler,
      syncer::ReportUnrecoverableErrorFunction
          report_unrecoverable_error_function,
      syncer::NetworkResources* network_resources) OVERRIDE;
  virtual void UpdateCredentials(
      const syncer::SyncCredentials& credentials) OVERRIDE;
  virtual void StartSyncingWithServer() OVERRIDE;
  virtual void SetEncryptionPassphrase(
      const std::string& passphrase,
      bool is_explicit) OVERRIDE;
  virtual bool SetDecryptionPassphrase(const std::string& passphrase)
      OVERRIDE WARN_UNUSED_RESULT;
  virtual void StopSyncingForShutdown() OVERRIDE;
  virtual scoped_ptr<base::Thread> Shutdown(syncer::ShutdownReason reason)
      OVERRIDE;
  virtual void UnregisterInvalidationIds() OVERRIDE;
  virtual void ConfigureDataTypes(
      syncer::ConfigureReason reason,
      const DataTypeConfigStateMap& config_state_map,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task,
      const base::Callback<void()>& retry_callback) OVERRIDE;
  virtual void ActivateDataType(
     syncer::ModelType type, syncer::ModelSafeGroup group,
     sync_driver::ChangeProcessor* change_processor) OVERRIDE;
  virtual void DeactivateDataType(syncer::ModelType type) OVERRIDE;
  virtual void EnableEncryptEverything() OVERRIDE;
  virtual syncer::UserShare* GetUserShare() const OVERRIDE;
  virtual scoped_ptr<syncer::SyncContextProxy> GetSyncContextProxy() OVERRIDE;
  virtual Status GetDetailedStatus() OVERRIDE;
  virtual syncer::sessions::SyncSessionSnapshot
      GetLastSessionSnapshot() const OVERRIDE;
  virtual bool HasUnsyncedItems() const OVERRIDE;
  virtual bool IsNigoriEnabled() const OVERRIDE;
  virtual syncer::PassphraseType GetPassphraseType() const OVERRIDE;
  virtual base::Time GetExplicitPassphraseTime() const OVERRIDE;
  virtual bool IsCryptographerReady(
      const syncer::BaseTransaction* trans) const OVERRIDE;
  virtual void GetModelSafeRoutingInfo(
      syncer::ModelSafeRoutingInfo* out) const OVERRIDE;
  virtual void RequestBufferedProtocolEventsAndEnableForwarding() OVERRIDE;
  virtual void DisableProtocolEventForwarding() OVERRIDE;
  virtual void EnableDirectoryTypeDebugInfoForwarding() OVERRIDE;
  virtual void DisableDirectoryTypeDebugInfoForwarding() OVERRIDE;
  virtual void GetAllNodesForTypes(
      syncer::ModelTypeSet types,
      base::Callback<void(const std::vector<syncer::ModelType>&,
                          ScopedVector<base::ListValue>)> type) OVERRIDE;
  virtual base::MessageLoop* GetSyncLoopForTesting() OVERRIDE;

 protected:
  
  

  
  virtual void InitCore(scoped_ptr<DoInitializeOptions> options);

  
  
  virtual void RequestConfigureSyncer(
      syncer::ConfigureReason reason,
      syncer::ModelTypeSet to_download,
      syncer::ModelTypeSet to_purge,
      syncer::ModelTypeSet to_journal,
      syncer::ModelTypeSet to_unapply,
      syncer::ModelTypeSet to_ignore,
      const syncer::ModelSafeRoutingInfo& routing_info,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task,
      const base::Closure& retry_callback);

  
  void FinishConfigureDataTypesOnFrontendLoop(
      const syncer::ModelTypeSet enabled_types,
      const syncer::ModelTypeSet succeeded_configuration_types,
      const syncer::ModelTypeSet failed_configuration_types,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task);

  
  
  
  
  
  
  virtual void HandleInitializationSuccessOnFrontendLoop(
      const syncer::WeakHandle<syncer::JsBackend> js_backend,
      const syncer::WeakHandle<syncer::DataTypeDebugInfoListener>
          debug_info_listener,
      syncer::SyncContextProxy* sync_context_proxy,
      const std::string& cache_guid);

  
  
  void HandleControlTypesDownloadRetry();

  
  
  
  void HandleProtocolEventOnFrontendLoop(syncer::ProtocolEvent* event);

  
  
  
  void HandleDirectoryCommitCountersUpdatedOnFrontendLoop(
      syncer::ModelType type,
      const syncer::CommitCounters& counters);

  
  
  
  void HandleDirectoryUpdateCountersUpdatedOnFrontendLoop(
      syncer::ModelType type,
      const syncer::UpdateCounters& counters);

  
  
  
  void HandleDirectoryStatusCountersUpdatedOnFrontendLoop(
      syncer::ModelType type,
      const syncer::StatusCounters& counters);

  sync_driver::SyncFrontend* frontend() { return frontend_; }

 private:
  friend class SyncBackendHostCore;

  
  
  
  void AddExperimentalTypes();

  
  void HandleInitializationFailureOnFrontendLoop();

  
  
  void HandleSyncCycleCompletedOnFrontendLoop(
      const syncer::sessions::SyncSessionSnapshot& snapshot);

  
  
  
  void RetryConfigurationOnFrontendLoop(const base::Closure& retry_callback);

  
  
  
  
  void PersistEncryptionBootstrapToken(
      const std::string& token,
      syncer::BootstrapTokenType token_type);

  
  bool initialized() const { return initialized_; }

  
  void HandleActionableErrorEventOnFrontendLoop(
      const syncer::SyncProtocolError& sync_error);

  
  void HandleMigrationRequestedOnFrontendLoop(const syncer::ModelTypeSet types);

  
  
  
  
  bool CheckPassphraseAgainstCachedPendingKeys(
      const std::string& passphrase) const;

  
  
  
  
  
  
  void NotifyPassphraseRequired(syncer::PassphraseRequiredReason reason,
                                sync_pb::EncryptedData pending_keys);

  
  void NotifyPassphraseAccepted();

  
  
  void NotifyEncryptedTypesChanged(
      syncer::ModelTypeSet encrypted_types,
      bool encrypt_everything);

  
  void NotifyEncryptionComplete();

  
  
  
  
  
  void HandlePassphraseTypeChangedOnFrontendLoop(
      syncer::PassphraseType type,
      base::Time explicit_passphrase_time);

  void HandleStopSyncingPermanentlyOnFrontendLoop();

  
  
  void HandleConnectionStatusChangeOnFrontendLoop(
      syncer::ConnectionStatus status);

  
  virtual void Observe(
    int type,
    const content::NotificationSource& source,
    const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnInvalidatorStateChange(
      syncer::InvalidatorState state) OVERRIDE;
  virtual void OnIncomingInvalidation(
      const syncer::ObjectIdInvalidationMap& invalidation_map) OVERRIDE;
  virtual std::string GetOwnerName() const OVERRIDE;

  content::NotificationRegistrar notification_registrar_;

  
  
  base::MessageLoop* const frontend_loop_;

  Profile* const profile_;

  
  const std::string name_;

  
  
  
  scoped_refptr<SyncBackendHostCore> core_;

  
  scoped_ptr<syncer::SyncContextProxy> sync_context_proxy_;

  bool initialized_;

  const base::WeakPtr<sync_driver::SyncPrefs> sync_prefs_;

  ExtensionsActivityMonitor extensions_activity_monitor_;

  scoped_ptr<SyncBackendRegistrar> registrar_;

  
  sync_driver::SyncFrontend* frontend_;

  
  
  
  
  
  
  
  
  sync_pb::EncryptedData cached_pending_keys_;

  
  
  
  
  syncer::PassphraseType cached_passphrase_type_;

  
  
  base::Time cached_explicit_passphrase_time_;

  
  syncer::sessions::SyncSessionSnapshot last_snapshot_;

  invalidation::InvalidationService* invalidator_;
  bool invalidation_handler_registered_;

  base::WeakPtrFactory<SyncBackendHostImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncBackendHostImpl);
};

}  

#endif  

