// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_WEBDATA_AUTOFILL_PROFILE_SYNCABLE_SERVICE_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_WEBDATA_AUTOFILL_PROFILE_SYNCABLE_SERVICE_H_

#if !defined(AUTOFILL_ENABLE_SYNC)
#error "This file should be built only when sync is enabled in Autofill"
#endif

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/scoped_observer.h"
#include "base/supports_user_data.h"
#include "base/synchronization/lock.h"
#include "base/threading/non_thread_safe.h"
#include "components/autofill/core/browser/field_types.h"
#include "components/autofill/core/browser/webdata/autofill_change.h"
#include "components/autofill/core/browser/webdata/autofill_entry.h"
#include "components/autofill/core/browser/webdata/autofill_webdata_backend.h"
#include "components/autofill/core/browser/webdata/autofill_webdata_service_observer.h"
#include "sync/api/sync_change.h"
#include "sync/api/sync_data.h"
#include "sync/api/sync_error.h"
#include "sync/api/syncable_service.h"
#include "sync/protocol/autofill_specifics.pb.h"

class ProfileSyncServiceAutofillTest;
class WebDataServiceBase;

namespace autofill {

class AutofillProfile;
class AutofillTable;
class AutofillWebDataService;
class FormGroup;

extern const char kAutofillProfileTag[];

class AutofillProfileSyncableService
    : public base::SupportsUserData::Data,
      public syncer::SyncableService,
      public AutofillWebDataServiceObserverOnDBThread,
      public base::NonThreadSafe {
 public:
  virtual ~AutofillProfileSyncableService();

  
  
  
  static void CreateForWebDataServiceAndBackend(
      AutofillWebDataService* web_data_service,
      AutofillWebDataBackend* webdata_backend,
      const std::string& app_locale);

  
  static AutofillProfileSyncableService* FromWebDataService(
      AutofillWebDataService* web_data_service);

  static syncer::ModelType model_type() { return syncer::AUTOFILL_PROFILE; }

  
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> sync_error_factory) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(
      syncer::ModelType type) const OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;

  
  virtual void AutofillProfileChanged(
      const AutofillProfileChange& change) OVERRIDE;

  
  
  void InjectStartSyncFlare(
      const syncer::SyncableService::StartSyncFlare& flare);

 protected:
  AutofillProfileSyncableService(AutofillWebDataBackend* webdata_backend,
                                 const std::string& app_locale);

  
  
  
  
  struct DataBundle;

  
  
  
  virtual bool LoadAutofillData(std::vector<AutofillProfile*>* profiles);

  
  
  
  virtual bool SaveChangesToWebData(const DataBundle& bundle);

  
  AutofillProfileSyncableService();
  void set_sync_processor(syncer::SyncChangeProcessor* sync_processor) {
    sync_processor_.reset(sync_processor);
  }

  
  
  static syncer::SyncData CreateData(const AutofillProfile& profile);

 private:
  friend class ::ProfileSyncServiceAutofillTest;
  FRIEND_TEST_ALL_PREFIXES(AutofillProfileSyncableServiceTest,
                           UpdateField);
  FRIEND_TEST_ALL_PREFIXES(AutofillProfileSyncableServiceTest,
                           UpdateMultivaluedField);
  FRIEND_TEST_ALL_PREFIXES(AutofillProfileSyncableServiceTest,
                           MergeProfile);

  
  typedef std::map<std::string, AutofillProfile*> GUIDToProfileMap;

  
  
  static bool OverwriteProfileWithServerData(
      const sync_pb::AutofillProfileSpecifics& specifics,
      AutofillProfile* profile,
      const std::string& app_locale);

  
  static void WriteAutofillProfile(const AutofillProfile& profile,
                                   sync_pb::EntitySpecifics* profile_specifics);

  
  
  void CreateGUIDToProfileMap(const std::vector<AutofillProfile*>& profiles,
                              GUIDToProfileMap* profile_map);

  
  
  
  
  
  GUIDToProfileMap::iterator CreateOrUpdateProfile(
      const syncer::SyncData& data,
      GUIDToProfileMap* profile_map,
      DataBundle* bundle);

  
  void ActOnChange(const AutofillProfileChange& change);

  AutofillTable* GetAutofillTable() const;

  
  
  static bool UpdateField(ServerFieldType field_type,
                          const std::string& new_value,
                          AutofillProfile* autofill_profile);
  
  static bool UpdateMultivaluedField(
      ServerFieldType field_type,
      const ::google::protobuf::RepeatedPtrField<std::string>& new_value,
      AutofillProfile* autofill_profile);

  
  
  
  
  
  static bool MergeProfile(const AutofillProfile& merge_from,
                           AutofillProfile* merge_into,
                           const std::string& app_locale);

  AutofillWebDataBackend* webdata_backend_;  
  std::string app_locale_;
  ScopedObserver<AutofillWebDataBackend,
                 AutofillProfileSyncableService> scoped_observer_;

  
  
  ScopedVector<AutofillProfile> profiles_;
  GUIDToProfileMap profiles_map_;

  scoped_ptr<syncer::SyncChangeProcessor> sync_processor_;

  scoped_ptr<syncer::SyncErrorFactory> sync_error_factory_;

  syncer::SyncableService::StartSyncFlare flare_;

  DISALLOW_COPY_AND_ASSIGN(AutofillProfileSyncableService);
};

struct AutofillProfileSyncableService::DataBundle {
  DataBundle();
  ~DataBundle();

  std::vector<std::string> profiles_to_delete;
  std::vector<AutofillProfile*> profiles_to_update;
  std::vector<AutofillProfile*> profiles_to_add;

  
  
  GUIDToProfileMap candidates_to_merge;
  
  std::vector<AutofillProfile*> profiles_to_sync_back;
};

}  

#endif  
