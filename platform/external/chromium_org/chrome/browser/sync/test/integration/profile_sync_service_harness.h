// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_PROFILE_SYNC_SERVICE_HARNESS_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_PROFILE_SYNC_SERVICE_HARNESS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/sessions/sync_session_snapshot.h"

class Profile;
class ProfileSyncService;

class ProfileSyncServiceHarness {
 public:
  static ProfileSyncServiceHarness* Create(
      Profile* profile,
      const std::string& username,
      const std::string& password);
  virtual ~ProfileSyncServiceHarness();

  
  void SetCredentials(const std::string& username, const std::string& password);

  
  
  
  
  bool SetupSync();

  
  
  bool SetupSync(syncer::ModelTypeSet synced_datatypes);

  
  
  
  
  
  
  
  bool AwaitMutualSyncCycleCompletion(ProfileSyncServiceHarness* partner);

  
  
  
  
  bool AwaitGroupSyncCycleCompletion(
      std::vector<ProfileSyncServiceHarness*>& partners);

  
  
  
  
  static bool AwaitQuiescence(
      std::vector<ProfileSyncServiceHarness*>& clients);

  
  ProfileSyncService* service() const { return service_; }

  
  const std::string& profile_debug_name() const { return profile_debug_name_; }

  
  bool EnableSyncForDatatype(syncer::ModelType datatype);

  
  bool DisableSyncForDatatype(syncer::ModelType datatype);

  
  bool EnableSyncForAllDatatypes();

  
  bool DisableSyncForAllDatatypes();

  
  syncer::sessions::SyncSessionSnapshot GetLastSessionSnapshot() const;

  
  bool IsTypePreferred(syncer::ModelType type);

  
  
  
  std::string GenerateFakeOAuth2RefreshTokenString();

  
  
  std::string GetClientInfoString(const std::string& message) const;

 private:
  ProfileSyncServiceHarness(
      Profile* profile,
      const std::string& username,
      const std::string& password);

  
  void FinishSyncSetup();

  
  std::string GetServiceStatus();

  
  bool IsSyncDisabled() const;

  
  Profile* profile_;

  
  ProfileSyncService* service_;

  
  std::string username_;
  std::string password_;

  
  
  int oauth2_refesh_token_number_;

  
  const std::string profile_debug_name_;

  DISALLOW_COPY_AND_ASSIGN(ProfileSyncServiceHarness);
};

#endif  
