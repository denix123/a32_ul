// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PROFILE_PREF_STORE_MANAGER_H_
#define CHROME_BROWSER_PREFS_PROFILE_PREF_STORE_MANAGER_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/prefs/pref_hash_filter.h"

class PersistentPrefStore;
class PrefHashStore;
class PrefService;
class TrackedPreferenceValidationDelegate;

namespace base {
class DictionaryValue;
class SequencedTaskRunner;
}  

namespace user_prefs {
class PrefRegistrySyncable;
}  

class PrefRegistrySimple;

class ProfilePrefStoreManager {
 public:
  
  
  
  
  
  
  
  ProfilePrefStoreManager(
      const base::FilePath& profile_path,
      const std::vector<PrefHashFilter::TrackedPreferenceMetadata>&
          tracking_configuration,
      size_t reporting_ids_count,
      const std::string& seed,
      const std::string& device_id,
      PrefService* local_state);

  ~ProfilePrefStoreManager();

  static const bool kPlatformSupportsPreferenceTracking;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  static base::FilePath GetPrefFilePathFromProfilePath(
      const base::FilePath& profile_path);

  
  static void ResetAllPrefHashStores(PrefService* local_state);

  
  
  
  
  static base::Time GetResetTime(PrefService* pref_service);

  
  
  
  static void ClearResetTime(PrefService* pref_service);

  
  
  
  
  
  PersistentPrefStore* CreateProfilePrefStore(
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner,
      const base::Closure& on_reset_on_load,
      TrackedPreferenceValidationDelegate* validation_delegate);

  
  
  
  bool InitializePrefsFromMasterPrefs(
      const base::DictionaryValue& master_prefs);

  
  
  PersistentPrefStore* CreateDeprecatedCombinedProfilePrefStore(
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);

 private:
  
  
  
  
  
  scoped_ptr<PrefHashStore> GetPrefHashStore(bool use_super_mac);

  const base::FilePath profile_path_;
  const std::vector<PrefHashFilter::TrackedPreferenceMetadata>
      tracking_configuration_;
  const size_t reporting_ids_count_;
  const std::string seed_;
  const std::string device_id_;
  PrefService* local_state_;

  DISALLOW_COPY_AND_ASSIGN(ProfilePrefStoreManager);
};

#endif  
