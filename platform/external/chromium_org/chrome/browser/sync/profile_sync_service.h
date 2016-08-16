// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_PROFILE_SYNC_SERVICE_H_
#define CHROME_BROWSER_SYNC_PROFILE_SYNC_SERVICE_H_

#include <set>
#include <string>
#include <utility>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/location.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/browsing_data/browsing_data_remover.h"
#include "chrome/browser/sync/backend_unrecoverable_error_handler.h"
#include "chrome/browser/sync/backup_rollback_controller.h"
#include "chrome/browser/sync/glue/sync_backend_host.h"
#include "chrome/browser/sync/profile_sync_service_base.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "chrome/browser/sync/protocol_event_observer.h"
#include "chrome/browser/sync/sessions/sessions_sync_manager.h"
#include "chrome/browser/sync/startup_controller.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_manager_base.h"
#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/data_type_encryption_handler.h"
#include "components/sync_driver/data_type_manager.h"
#include "components/sync_driver/data_type_manager_observer.h"
#include "components/sync_driver/data_type_status_table.h"
#include "components/sync_driver/device_info_sync_service.h"
#include "components/sync_driver/local_device_info_provider.h"
#include "components/sync_driver/non_blocking_data_type_manager.h"
#include "components/sync_driver/sync_frontend.h"
#include "components/sync_driver/sync_prefs.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "net/base/backoff_entry.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/internal_api/public/shutdown_reason.h"
#include "sync/internal_api/public/sync_manager_factory.h"
#include "sync/internal_api/public/util/experiments.h"
#include "sync/internal_api/public/util/unrecoverable_error_handler.h"
#include "sync/js/sync_js_controller.h"
#include "url/gurl.h"

class Profile;
class ProfileOAuth2TokenService;
class ProfileSyncComponentsFactory;
class SupervisedUserSigninManagerWrapper;
class SyncErrorController;
class SyncTypePreferenceProvider;

namespace base {
class CommandLine;
};

namespace browser_sync {
class BackendMigrator;
class FaviconCache;
class JsController;
class OpenTabsUIDelegate;

namespace sessions {
class SyncSessionSnapshot;
}  
}  

namespace sync_driver {
class ChangeProcessor;
class DataTypeManager;
class DeviceInfoSyncService;
class LocalDeviceInfoProvider;
}  

namespace syncer {
class BaseTransaction;
class NetworkResources;
struct CommitCounters;
struct StatusCounters;
struct SyncCredentials;
struct UpdateCounters;
struct UserShare;
}  

namespace sync_pb {
class EncryptedData;
}  

class ProfileSyncService : public ProfileSyncServiceBase,
                           public sync_driver::SyncFrontend,
                           public sync_driver::SyncPrefObserver,
                           public sync_driver::DataTypeManagerObserver,
                           public syncer::UnrecoverableErrorHandler,
                           public KeyedService,
                           public sync_driver::DataTypeEncryptionHandler,
                           public OAuth2TokenService::Consumer,
                           public OAuth2TokenService::Observer,
                           public SigninManagerBase::Observer {
 public:
  typedef browser_sync::SyncBackendHost::Status Status;

  
  struct SyncTokenStatus {
    SyncTokenStatus();
    ~SyncTokenStatus();

    
    base::Time connection_status_update_time;
    syncer::ConnectionStatus connection_status;

    
    base::Time token_request_time;
    base::Time token_receive_time;

    
    
    GoogleServiceAuthError last_get_token_error;
    base::Time next_token_request_time;
  };

  enum SyncEventCodes  {
    MIN_SYNC_EVENT_CODE = 0,

    
    START_FROM_NTP = 1,      
    START_FROM_WRENCH = 2,   
    START_FROM_OPTIONS = 3,  
    START_FROM_BOOKMARK_MANAGER = 4,  
    START_FROM_PROFILE_MENU = 5,  
    START_FROM_URL = 6,  

    
    CANCEL_FROM_SIGNON_WITHOUT_AUTH = 10,   
                                            
    CANCEL_DURING_SIGNON = 11,              
    CANCEL_DURING_CONFIGURE = 12,           
                                            
    
    STOP_FROM_OPTIONS = 20,  
    STOP_FROM_ADVANCED_DIALOG = 21,  

    

    MAX_SYNC_EVENT_CODE
  };

  
  enum PassphraseType {
    IMPLICIT,  
               
    EXPLICIT,  
               
  };

  enum SyncStatusSummary {
    UNRECOVERABLE_ERROR,
    NOT_ENABLED,
    SETUP_INCOMPLETE,
    DATATYPES_NOT_INITIALIZED,
    INITIALIZED,
    BACKUP_USER_DATA,
    ROLLBACK_USER_DATA,
    UNKNOWN_ERROR,
  };

  enum BackendMode {
    IDLE,       
    SYNC,       
    BACKUP,     
    ROLLBACK    
  };

  
  static const char* kSyncServerUrl;
  
  static const char* kDevServerUrl;

  
  ProfileSyncService(
      scoped_ptr<ProfileSyncComponentsFactory> factory,
      Profile* profile,
      scoped_ptr<SupervisedUserSigninManagerWrapper> signin_wrapper,
      ProfileOAuth2TokenService* oauth2_token_service,
      browser_sync::ProfileSyncServiceStartBehavior start_behavior);
  virtual ~ProfileSyncService();

  
  
  void Initialize();

  virtual void SetSyncSetupCompleted();

  
  virtual bool HasSyncSetupCompleted() const OVERRIDE;
  virtual bool ShouldPushChanges() OVERRIDE;
  virtual syncer::ModelTypeSet GetActiveDataTypes() const OVERRIDE;
  virtual void AddObserver(ProfileSyncServiceBase::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(
      ProfileSyncServiceBase::Observer* observer) OVERRIDE;
  virtual bool HasObserver(
      ProfileSyncServiceBase::Observer* observer) const OVERRIDE;


  void AddProtocolEventObserver(browser_sync::ProtocolEventObserver* observer);
  void RemoveProtocolEventObserver(
      browser_sync::ProtocolEventObserver* observer);

  void AddTypeDebugInfoObserver(syncer::TypeDebugInfoObserver* observer);
  void RemoveTypeDebugInfoObserver(syncer::TypeDebugInfoObserver* observer);

  
  void AddPreferenceProvider(SyncTypePreferenceProvider* provider);
  
  
  
  void RemovePreferenceProvider(SyncTypePreferenceProvider* provider);
  
  bool HasPreferenceProvider(SyncTypePreferenceProvider* provider) const;

  
  
  
  
  
  
  void GetAllNodes(
      const base::Callback<void(scoped_ptr<base::ListValue>)>& callback);

  void RegisterAuthNotifications();
  void UnregisterAuthNotifications();

  
  
  
  
  
  
  
  
  virtual bool IsSyncEnabledAndLoggedIn();

  
  
  virtual bool IsOAuthRefreshTokenAvailable();

  
  
  
  
  void RegisterDataTypeController(
      sync_driver::DataTypeController* data_type_controller);

  
  
  
  
  void RegisterNonBlockingType(syncer::ModelType type);

  
  
  
  
  
  
  
  void InitializeNonBlockingType(
      syncer::ModelType type,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner,
      const base::WeakPtr<syncer::ModelTypeSyncProxyImpl>& proxy);

  
  
  virtual browser_sync::OpenTabsUIDelegate* GetOpenTabsUIDelegate();

  
  virtual browser_sync::SyncedWindowDelegatesGetter*
  GetSyncedWindowDelegatesGetter() const;

  
  virtual syncer::SyncableService* GetSessionsSyncableService();

  
  virtual syncer::SyncableService* GetDeviceInfoSyncableService();

  
  virtual sync_driver::LocalDeviceInfoProvider* GetLocalDeviceInfoProvider();

  
  
  virtual sync_driver::DeviceInfoTracker* GetDeviceInfoTracker() const;

  
  
  void GetDataTypeControllerStates(
    sync_driver::DataTypeController::StateMap* state_map) const;

  
  virtual void DisableForUser();

  
  virtual void StopSyncingPermanently();

  
  virtual void OnBackendInitialized(
      const syncer::WeakHandle<syncer::JsBackend>& js_backend,
      const syncer::WeakHandle<syncer::DataTypeDebugInfoListener>&
          debug_info_listener,
      const std::string& cache_guid,
      bool success) OVERRIDE;
  virtual void OnSyncCycleCompleted() OVERRIDE;
  virtual void OnProtocolEvent(const syncer::ProtocolEvent& event) OVERRIDE;
  virtual void OnDirectoryTypeCommitCounterUpdated(
      syncer::ModelType type,
      const syncer::CommitCounters& counters) OVERRIDE;
  virtual void OnDirectoryTypeUpdateCounterUpdated(
      syncer::ModelType type,
      const syncer::UpdateCounters& counters) OVERRIDE;
  virtual void OnDirectoryTypeStatusCounterUpdated(
      syncer::ModelType type,
      const syncer::StatusCounters& counters) OVERRIDE;
  virtual void OnSyncConfigureRetry() OVERRIDE;
  virtual void OnConnectionStatusChange(
      syncer::ConnectionStatus status) OVERRIDE;
  virtual void OnPassphraseRequired(
      syncer::PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) OVERRIDE;
  virtual void OnPassphraseAccepted() OVERRIDE;
  virtual void OnEncryptedTypesChanged(
      syncer::ModelTypeSet encrypted_types,
      bool encrypt_everything) OVERRIDE;
  virtual void OnEncryptionComplete() OVERRIDE;
  virtual void OnMigrationNeededForTypes(
      syncer::ModelTypeSet types) OVERRIDE;
  virtual void OnExperimentsChanged(
      const syncer::Experiments& experiments) OVERRIDE;
  virtual void OnActionableError(
      const syncer::SyncProtocolError& error) OVERRIDE;

  
  virtual void OnConfigureDone(
      const sync_driver::DataTypeManager::ConfigureResult& result) OVERRIDE;
  virtual void OnConfigureRetry() OVERRIDE;
  virtual void OnConfigureStart() OVERRIDE;

  
  virtual bool IsPassphraseRequired() const OVERRIDE;
  virtual syncer::ModelTypeSet GetEncryptedDataTypes() const OVERRIDE;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  
  
  
  
  virtual void OnUserChoseDatatypes(bool sync_everything,
      syncer::ModelTypeSet chosen_types);

  
  SyncStatusSummary QuerySyncStatusSummary();

  
  std::string QuerySyncStatusSummaryString();

  
  
  
  virtual bool QueryDetailedSyncStatus(
      browser_sync::SyncBackendHost::Status* result);

  virtual const GoogleServiceAuthError& GetAuthError() const;

  
  
  
  
  virtual bool FirstSetupInProgress() const;

  
  
  
  
  
  
  
  virtual void SetSetupInProgress(bool setup_in_progress);

  
  
  
  
  
  
  
  
  virtual bool sync_initialized() const;

  virtual bool HasUnrecoverableError() const;
  const std::string& unrecoverable_error_message() {
    return unrecoverable_error_message_;
  }
  tracked_objects::Location unrecoverable_error_location() {
    return unrecoverable_error_location_;
  }

  
  
  virtual bool IsPassphraseRequiredForDecryption() const;

  syncer::PassphraseRequiredReason passphrase_required_reason() const {
    return passphrase_required_reason_;
  }

  
  virtual base::string16 GetLastSyncedTimeString() const;

  
  std::string GetBackendInitializationStateString() const;

  
  
  virtual bool IsStartSuppressed() const;

  ProfileSyncComponentsFactory* factory() { return factory_.get(); }

  
  Profile* profile() const { return profile_; }

  
  
  virtual base::WeakPtr<syncer::JsController> GetJsController();

  
  static void SyncEvent(SyncEventCodes code);

  
  
  
  
  
  
  static bool IsSyncEnabled();

  
  
  virtual bool IsManaged() const;

  
  virtual void OnUnrecoverableError(
      const tracked_objects::Location& from_here,
      const std::string& message) OVERRIDE;

  
  
  
  void ReenableDatatype(syncer::ModelType type);

  
  

  
  
  
  
  virtual syncer::UserShare* GetUserShare() const;

  
  
  

  virtual syncer::sessions::SyncSessionSnapshot
      GetLastSessionSnapshot() const;

  
  
  
  bool HasUnsyncedItems() const;

  
  browser_sync::BackendMigrator* GetBackendMigratorForTest();

  
  bool IsRetryingAccessTokenFetchForTest() const;

  
  std::string GetAccessTokenForTest() const;

  
  void GetModelSafeRoutingInfo(syncer::ModelSafeRoutingInfo* out) const;

  
  
  
  
  
  
  
  
  
  
  
  base::Value* GetTypeStatusMap() const;

  
  
  virtual void DeactivateDataType(syncer::ModelType type);

  
  virtual void OnSyncManagedPrefChange(bool is_sync_managed) OVERRIDE;

  
  
  
  
  virtual void ChangePreferredDataTypes(
      syncer::ModelTypeSet preferred_types);

  
  
  virtual syncer::ModelTypeSet GetPreferredDataTypes() const;

  
  virtual syncer::ModelTypeSet GetPreferredDirectoryDataTypes() const;

  
  virtual syncer::ModelTypeSet GetPreferredNonBlockingDataTypes() const;

  
  
  virtual syncer::ModelTypeSet GetForcedDataTypes() const;

  
  
  
  
  virtual syncer::ModelTypeSet GetRegisteredDataTypes() const;

  
  virtual syncer::ModelTypeSet GetRegisteredDirectoryDataTypes() const;

  
  virtual syncer::ModelTypeSet GetRegisteredNonBlockingDataTypes() const;

  
  
  
  virtual bool IsCryptographerReady(
      const syncer::BaseTransaction* trans) const;

  
  
  virtual bool IsUsingSecondaryPassphrase() const;

  
  virtual syncer::PassphraseType GetPassphraseType() const;

  
  
  
  virtual base::Time GetExplicitPassphraseTime() const;

  
  
  
  
  
  

  
  
  
  
  
  virtual void SetEncryptionPassphrase(const std::string& passphrase,
                                       PassphraseType type);

  
  
  
  virtual bool SetDecryptionPassphrase(const std::string& passphrase)
      WARN_UNUSED_RESULT;

  
  
  virtual bool EncryptEverythingAllowed() const;

  
  virtual void SetEncryptEverythingAllowed(bool allowed);

  
  
  virtual void EnableEncryptEverything();

  
  
  
  
  virtual bool EncryptEverythingEnabled() const;

  
  virtual bool encryption_pending() const;

  const GURL& sync_service_url() const { return sync_service_url_; }
  SigninManagerBase* signin() const;

  
  bool auto_start_enabled() const;
  bool setup_in_progress() const;

  
  void StopAndSuppress();

  
  virtual void UnsuppressAndStart();

  
  
  void AcknowledgeSyncedTypes();

  SyncErrorController* sync_error_controller() {
    return sync_error_controller_.get();
  }

  
  const sync_driver::DataTypeStatusTable& data_type_status_table() const;

  sync_driver::DataTypeManager::ConfigureStatus configure_status() {
    return configure_status_;
  }

  
  
  
  
  
  virtual bool waiting_for_auth() const;

  
  const syncer::Experiments& current_experiments() const;

  
  virtual void OnGetTokenSuccess(
      const OAuth2TokenService::Request* request,
      const std::string& access_token,
      const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(
      const OAuth2TokenService::Request* request,
      const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokensLoaded() OVERRIDE;

  
  
  virtual void Shutdown() OVERRIDE;

  
  
  
  
  void OnDataTypeRequestsSyncStartup(syncer::ModelType type);

  
  SyncTokenStatus GetSyncTokenStatus() const;

  browser_sync::FaviconCache* GetFaviconCache();

  
  
  void OverrideNetworkResourcesForTest(
      scoped_ptr<syncer::NetworkResources> network_resources);

  virtual bool IsDataTypeControllerRunning(syncer::ModelType type) const;

  BackendMode backend_mode() const {
    return backend_mode_;
  }

  
  void SetBrowsingDataRemoverObserverForTesting(
      BrowsingDataRemover::Observer* observer);
  void SetClearingBrowseringDataForTesting(base::Callback<
      void(BrowsingDataRemover::Observer*, Profile*, base::Time, base::Time)>
                                               c);

  
  static GURL GetSyncServiceURL(const base::CommandLine& command_line);

  base::Time GetDeviceBackupTimeForTesting() const;

 protected:
  
  void ConfigurePriorityDataTypes();

  
  void ConfigureDataTypeManager();

  
  
  
  void ShutdownImpl(syncer::ShutdownReason reason);

  
  syncer::SyncCredentials GetCredentials();

  virtual syncer::WeakHandle<syncer::JsEventHandler> GetJsEventHandler();

  const sync_driver::DataTypeController::TypeMap&
      directory_data_type_controllers() {
    return directory_data_type_controllers_;
  }

  
  bool IsEncryptedDatatypeEnabled() const;

  
  
  
  void OnUnrecoverableErrorImpl(
      const tracked_objects::Location& from_here,
      const std::string& message,
      bool delete_sync_database);

  virtual bool NeedBackup() const;

  
  
  
  GoogleServiceAuthError last_auth_error_;

  
  
  scoped_ptr<browser_sync::SyncBackendHost> backend_;

  
  
  
  syncer::PassphraseRequiredReason passphrase_required_reason_;

 private:
  enum UnrecoverableErrorReason {
    ERROR_REASON_UNSET,
    ERROR_REASON_SYNCER,
    ERROR_REASON_BACKEND_INIT_FAILURE,
    ERROR_REASON_CONFIGURATION_RETRY,
    ERROR_REASON_CONFIGURATION_FAILURE,
    ERROR_REASON_ACTIONABLE_ERROR,
    ERROR_REASON_LIMIT
  };

  enum AuthErrorMetric {
    AUTH_ERROR_ENCOUNTERED,
    AUTH_ERROR_FIXED,
    AUTH_ERROR_LIMIT
  };

  friend class ProfileSyncServicePasswordTest;
  friend class SyncTest;
  friend class TestProfileSyncService;
  FRIEND_TEST_ALL_PREFIXES(ProfileSyncServiceTest, InitialState);

  
  void UpdateAuthErrorState(const GoogleServiceAuthError& error);

  
  
  
  void TrySyncDatatypePrefRecovery();

  
  
  void StartSyncingWithServer();

  
  
  
  void ResolvePassphraseRequired();

  
  
  
  
  void ConsumeCachedPassphraseIfPossible();

  
  
  
  
  virtual void RequestAccessToken();

  
  bool ShouldDeleteSyncFolder();

  
  
  void InitializeBackend(bool delete_sync_data_folder);

  
  void InitSettings();

  
  void UpdateLastSyncedTime();

  void NotifyObservers();
  void NotifySyncCycleCompleted();

  void ClearStaleErrors();

  void ClearUnrecoverableError();

  
  
  virtual void StartUpSlowBackendComponents(BackendMode mode);

  
  
  static std::string GetExperimentNameForDataType(
      syncer::ModelType data_type);

  
  void RegisterNewDataType(syncer::ModelType data_type);

  
  
  
  
  
  
  virtual void ReconfigureDatatypeManager();

  
  syncer::ModelTypeSet GetDataTypesFromPreferenceProviders() const;

  
  
  void UpdateSelectedTypesHistogram(
      bool sync_everything,
      const syncer::ModelTypeSet chosen_types) const;

#if defined(OS_CHROMEOS)
  
  
  void RefreshSpareBootstrapToken(const std::string& passphrase);
#endif

  
  
  void OnInternalUnrecoverableError(const tracked_objects::Location& from_here,
                                    const std::string& message,
                                    bool delete_sync_database,
                                    UnrecoverableErrorReason reason);

  
  syncer::SyncManagerFactory::MANAGER_TYPE GetManagerType() const;

  
  void UpdateBackendInitUMA(bool success);

  
  void PostBackendInitialization();

  
  bool HasSyncingBackend() const;

  
  void UpdateFirstSyncTimePref();

  
  void ClearBrowsingDataSinceFirstSync();

  
  void CheckSyncBackupIfNeeded();

  
  void CheckSyncBackupCallback(base::Time backup_time);

  
  
  void TryStartSyncAfterBackup();

  
  void CleanUpBackup();

 
  scoped_ptr<ProfileSyncComponentsFactory> factory_;

  
  Profile* profile_;

  
  
  sync_driver::SyncPrefs sync_prefs_;

  
  
  const GURL sync_service_url_;

  
  
  
  base::Time sync_configure_start_time_;

  
  
  bool is_first_time_sync_configure_;

  
  sync_driver::DataTypeController::TypeMap directory_data_type_controllers_;

  
  bool backend_initialized_;

  
  
  
  bool sync_disabled_by_admin_;

  
  
  bool is_auth_in_progress_;

  
  
  const scoped_ptr<SupervisedUserSigninManagerWrapper> signin_;

  
  UnrecoverableErrorReason unrecoverable_error_reason_;
  std::string unrecoverable_error_message_;
  tracked_objects::Location unrecoverable_error_location_;

  
  scoped_ptr<sync_driver::DataTypeManager> directory_data_type_manager_;

  
  sync_driver::NonBlockingDataTypeManager non_blocking_data_type_manager_;

  ObserverList<ProfileSyncServiceBase::Observer> observers_;
  ObserverList<browser_sync::ProtocolEventObserver> protocol_event_observers_;
  ObserverList<syncer::TypeDebugInfoObserver> type_debug_info_observers_;

  std::set<SyncTypePreferenceProvider*> preference_providers_;

  syncer::SyncJsController sync_js_controller_;

  
  
  
  bool expect_sync_configuration_aborted_;

  
  
  
  
  std::string cached_passphrase_;

  
  
  syncer::ModelTypeSet encrypted_types_;

  
  bool encrypt_everything_allowed_;

  
  bool encrypt_everything_;

  
  
  
  bool encryption_pending_;

  scoped_ptr<browser_sync::BackendMigrator> migrator_;

  
  
  syncer::SyncProtocolError last_actionable_error_;

  
  scoped_ptr<SyncErrorController> sync_error_controller_;

  
  
  sync_driver::DataTypeStatusTable data_type_status_table_;

  sync_driver::DataTypeManager::ConfigureStatus configure_status_;

  
  syncer::Experiments current_experiments_;

  
  
  syncer::WeakHandle<syncer::DataTypeDebugInfoListener> debug_info_listener_;

  
  
  
  
  
  scoped_ptr<base::Thread> sync_thread_;

  
  ProfileOAuth2TokenService* const oauth2_token_service_;

  
  
  std::string access_token_;

  
  
  scoped_ptr<OAuth2TokenService::Request> access_token_request_;

  
  
  base::OneShotTimer<ProfileSyncService> request_access_token_retry_timer_;
  net::BackoffEntry request_access_token_backoff_;

  base::WeakPtrFactory<ProfileSyncService> weak_factory_;

  
  
  
  
  
  
  base::WeakPtrFactory<ProfileSyncService> startup_controller_weak_factory_;

  
  base::Time connection_status_update_time_;
  syncer::ConnectionStatus connection_status_;
  base::Time token_request_time_;
  base::Time token_receive_time_;
  GoogleServiceAuthError last_get_token_error_;
  base::Time next_token_request_time_;

  scoped_ptr<sync_driver::LocalDeviceInfoProvider> local_device_;

  
  scoped_ptr<browser_sync::SessionsSyncManager> sessions_sync_manager_;
  scoped_ptr<sync_driver::DeviceInfoSyncService> device_info_sync_service_;

  scoped_ptr<syncer::NetworkResources> network_resources_;

  browser_sync::StartupController startup_controller_;

  browser_sync::BackupRollbackController backup_rollback_controller_;

  
  BackendMode backend_mode_;

  
  bool need_backup_;

  
  bool backup_finished_;

  base::Time backup_start_time_;

  base::Callback<
      void(BrowsingDataRemover::Observer*, Profile*, base::Time, base::Time)>
      clear_browsing_data_;

  
  
  scoped_ptr<base::Time> last_backup_time_;

  BrowsingDataRemover::Observer* browsing_data_remover_observer_;

  DISALLOW_COPY_AND_ASSIGN(ProfileSyncService);
};

bool ShouldShowActionOnUI(
    const syncer::SyncProtocolError& error);


#endif  
