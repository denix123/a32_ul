// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_CHROME_PREF_SERVICE_FACTORY_H_
#define CHROME_BROWSER_PREFS_CHROME_PREF_SERVICE_FACTORY_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class DictionaryValue;
class FilePath;
class SequencedTaskRunner;
class Time;
}

namespace policy {
class PolicyService;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefHashStore;
class PrefRegistry;
class PrefRegistrySimple;
class PrefService;
class PrefServiceSyncable;
class PrefStore;
class Profile;
class SupervisedUserSettingsService;
class TrackedPreferenceValidationDelegate;

namespace chrome_prefs {

namespace internals {

extern const char kSettingsEnforcementTrialName[];
extern const char kSettingsEnforcementGroupNoEnforcement[];
extern const char kSettingsEnforcementGroupEnforceAlways[];
extern const char kSettingsEnforcementGroupEnforceAlwaysWithDSE[];
extern const char kSettingsEnforcementGroupEnforceAlwaysWithExtensionsAndDSE[];

}  


scoped_ptr<PrefService> CreateLocalState(
    const base::FilePath& pref_filename,
    base::SequencedTaskRunner* pref_io_task_runner,
    policy::PolicyService* policy_service,
    const scoped_refptr<PrefRegistry>& pref_registry,
    bool async);

scoped_ptr<PrefServiceSyncable> CreateProfilePrefs(
    const base::FilePath& pref_filename,
    base::SequencedTaskRunner* pref_io_task_runner,
    TrackedPreferenceValidationDelegate* validation_delegate,
    policy::PolicyService* policy_service,
    SupervisedUserSettingsService* supervised_user_settings,
    const scoped_refptr<PrefStore>& extension_prefs,
    const scoped_refptr<user_prefs::PrefRegistrySyncable>& pref_registry,
    bool async);

void SchedulePrefsFilePathVerification(const base::FilePath& profile_path);

void DisableDelaysAndDomainCheckForTesting();

void SchedulePrefHashStoresUpdateCheck(
    const base::FilePath& initial_profile_path);

bool InitializePrefsFromMasterPrefs(
    const base::FilePath& profile_path,
    const base::DictionaryValue& master_prefs);

base::Time GetResetTime(Profile* profile);

void ClearResetTime(Profile* profile);

void RegisterPrefs(PrefRegistrySimple* registry);

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

}  

#endif  
