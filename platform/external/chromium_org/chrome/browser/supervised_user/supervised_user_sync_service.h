// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SYNC_SERVICE_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SYNC_SERVICE_H_

#include <vector>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "chrome/browser/supervised_user/supervised_user_sync_service_observer.h"
#include "chrome/browser/supervised_user/supervised_users.h"
#include "components/keyed_service/core/keyed_service.h"
#include "sync/api/syncable_service.h"

namespace base {
class DictionaryValue;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefService;

class SupervisedUserSyncService : public KeyedService,
                                  public syncer::SyncableService {
 public:
  
  typedef base::Callback<void(const base::DictionaryValue*)>
      SupervisedUsersCallback;

  
  static const char kAcknowledged[];
  static const char kChromeAvatar[];
  static const char kChromeOsAvatar[];
  static const char kMasterKey[];
  static const char kPasswordSignatureKey[];
  static const char kPasswordEncryptionKey[];
  static const char kName[];

  
  static const int kNoAvatar;

  virtual ~SupervisedUserSyncService();

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  
  
  
  
  
  static bool GetAvatarIndex(const std::string& avatar_str,
                             int* avatar_index);

  
  
  
  static std::string BuildAvatarString(int avatar_index);

  void AddObserver(SupervisedUserSyncServiceObserver* observer);
  void RemoveObserver(SupervisedUserSyncServiceObserver* observer);

  void AddSupervisedUser(const std::string& id,
                         const std::string& name,
                         const std::string& master_key,
                         const std::string& signature_key,
                         const std::string& encryption_key,
                         int avatar_index);
  void UpdateSupervisedUser(const std::string& id,
                            const std::string& name,
                            const std::string& master_key,
                            const std::string& signature_key,
                            const std::string& encryption_key,
                            int avatar_index);

  void DeleteSupervisedUser(const std::string& id);

  
  
  
  
  
  
  
  
  bool UpdateSupervisedUserAvatarIfNeeded(const std::string& id,
                                          int avatar_index);
  void ClearSupervisedUserAvatar(const std::string& id);

  
  
  
  
  
  const base::DictionaryValue* GetSupervisedUsers();

  
  
  void GetSupervisedUsersAsync(const SupervisedUsersCallback& callback);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> error_handler) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(syncer::ModelType type) const
      OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;

 private:
  friend class SupervisedUserSyncServiceFactory;

  
  
  explicit SupervisedUserSyncService(PrefService* prefs);

  void OnLastSignedInUsernameChange();

  scoped_ptr<base::DictionaryValue> CreateDictionary(
      const std::string& name,
      const std::string& master_key,
      const std::string& signature_key,
      const std::string& encryption_key,
      int avatar_index);

  void UpdateSupervisedUserImpl(const std::string& id,
                                const std::string& name,
                                const std::string& master_key,
                                const std::string& signature_key,
                                const std::string& encryption_key,
                                int avatar_index,
                                bool add_user);

  void NotifySupervisedUserAcknowledged(const std::string& supervised_user_id);
  void NotifySupervisedUsersSyncingStopped();
  void NotifySupervisedUsersChanged();

  void DispatchCallbacks();

  PrefService* prefs_;
  PrefChangeRegistrar pref_change_registrar_;

  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;
  scoped_ptr<syncer::SyncErrorFactory> error_handler_;

  ObserverList<SupervisedUserSyncServiceObserver> observers_;

  std::vector<SupervisedUsersCallback> callbacks_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserSyncService);
};

#endif  
