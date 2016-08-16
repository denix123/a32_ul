// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SHARED_SETTINGS_SERVICE_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SHARED_SETTINGS_SERVICE_H_

#include "base/callback.h"
#include "base/callback_list.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/supervised_user/supervised_users.h"
#include "components/keyed_service/core/keyed_service.h"
#include "sync/api/syncable_service.h"

class PrefService;

namespace base {
class DictionaryValue;
class Value;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class SupervisedUserSharedSettingsService : public KeyedService,
                                            public syncer::SyncableService {
 public:
  
  typedef base::Callback<void(const std::string& ,
                              const std::string& )> ChangeCallback;
  typedef base::CallbackList<
      void(const std::string& , const std::string& )>
      ChangeCallbackList;

  
  
  
  explicit SupervisedUserSharedSettingsService(PrefService* prefs);
  virtual ~SupervisedUserSharedSettingsService();

  
  
  
  
  
  const base::Value* GetValue(const std::string& su_id, const std::string& key);

  
  
  
  void SetValue(const std::string& su_id,
                const std::string& key,
                const base::Value& value);

  
  
  
  
  scoped_ptr<ChangeCallbackList::Subscription> Subscribe(
      const ChangeCallback& cb);

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  void SetValueInternal(const std::string& su_id,
                        const std::string& key,
                        const base::Value& value,
                        bool acknowledged);

  
  static syncer::SyncData CreateSyncDataForSetting(const std::string& su_id,
                                                   const std::string& key,
                                                   const base::Value& value,
                                                   bool acknowledged);

  
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
  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;
  scoped_ptr<syncer::SyncErrorFactory> error_handler_;

  ChangeCallbackList callbacks_;

  PrefService* prefs_;
};

#endif  
