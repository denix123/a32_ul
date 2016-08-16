// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_GOOGLE_UPDATE_SETTINGS_H_
#define CHROME_INSTALLER_UTIL_GOOGLE_UPDATE_SETTINGS_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "base/version.h"
#include "chrome/installer/util/util_constants.h"
#include "components/metrics/client_info.h"

class AppRegistrationData;
class BrowserDistribution;

namespace installer {
class ChannelInfo;
class InstallationState;
}

class GoogleUpdateSettings {
 public:
  
  enum UpdatePolicy {
    UPDATES_DISABLED    = 0,
    AUTOMATIC_UPDATES   = 1,
    MANUAL_UPDATES_ONLY = 2,
    AUTO_UPDATES_ONLY   = 3,
    UPDATE_POLICIES_COUNT
  };

  static const wchar_t kPoliciesKey[];
  static const wchar_t kUpdatePolicyValue[];
  static const wchar_t kUpdateOverrideValuePrefix[];
  static const wchar_t kCheckPeriodOverrideMinutes[];
  static const int kCheckPeriodOverrideMinutesDefault;
  static const int kCheckPeriodOverrideMinutesMax;
  static const GoogleUpdateSettings::UpdatePolicy kDefaultUpdatePolicy;

  
  struct ProductData {
    
    std::string version;
    
    
    
    base::Time last_success;
    
    int last_result;
    
    
    int last_error_code;
    
    
    
    int last_extra_code;
  };

  
  static bool IsSystemInstall();

  
  
  
  static bool GetCollectStatsConsent();

  
  
  static bool SetCollectStatsConsent(bool consented);

#if defined(OS_WIN)
  
  
  
  static bool GetCollectStatsConsentAtLevel(bool system_install);

  
  
  static bool SetCollectStatsConsentAtLevel(bool system_install,
                                            bool consented);
#endif

  
  
  
  
  static scoped_ptr<metrics::ClientInfo> LoadMetricsClientInfo();

  
  
  static void StoreMetricsClientInfo(const metrics::ClientInfo& client_info);

  
  
  static bool SetEULAConsent(const installer::InstallationState& machine_state,
                             BrowserDistribution* dist,
                             bool consented);

  
  
  
  static int GetLastRunTime();

  
  
  
  static bool SetLastRunTime();

  
  
  
  static bool RemoveLastRunTime();

  
  
  static bool GetBrowser(base::string16* browser);

  
  
  
  static bool GetLanguage(base::string16* language);

  
  
  
  
  
  static bool GetBrand(base::string16* brand);

  
  
  
  
  
  
  
  static bool GetReactivationBrand(base::string16* brand);

  
  
  static bool GetClient(base::string16* client);

  
  
  static bool SetClient(const base::string16& client);

  
  
  static bool GetReferral(base::string16* referral);

  
  
  static bool ClearReferral();

  
  
  
  static bool UpdateDidRunStateForApp(const AppRegistrationData& app_reg_data,
                                      bool did_run);

  
  
  
  static bool UpdateDidRunState(bool did_run, bool system_level);

  
  
  
  static base::string16 GetChromeChannel(bool system_install);

  
  
  
  
  
  static bool GetChromeChannelAndModifiers(bool system_install,
                                           base::string16* channel);

  
  
  
  
  
  
  
  
  
  
  static void UpdateInstallStatus(bool system_install,
                                  installer::ArchiveType archive_type,
                                  int install_return_code,
                                  const base::string16& product_guid);

  
  
  
  
  
  
  
  
  
  
  
  
  
  static bool UpdateGoogleUpdateApKey(installer::ArchiveType archive_type,
                                      int install_return_code,
                                      installer::ChannelInfo* value);

  
  
  static void UpdateProfileCounts(int profiles_active, int profiles_signedin);

  
  
  
  
  
  
  
  
  
  static int DuplicateGoogleUpdateSystemClientKey();

  
  
  static bool WriteGoogleUpdateSystemClientKey(int handle,
                                               const base::string16& key,
                                               const base::string16& value);

  
  
  
  static UpdatePolicy GetAppUpdatePolicy(const base::string16& app_guid,
                                         bool* is_overridden);

  
  
  
  
  
  
  static bool AreAutoupdatesEnabled();

  
  
  
  
  
  
  
  
  
  static bool ReenableAutoupdates();

  
  static void RecordChromeUpdatePolicyHistograms();

  
  
  static base::string16 GetUninstallCommandLine(bool system_install);

  
  static Version GetGoogleUpdateVersion(bool system_install);

  
  
  static base::Time GetGoogleUpdateLastStartedAU(bool system_install);

  
  
  
  static base::Time GetGoogleUpdateLastChecked(bool system_install);

  
  
  
  static bool GetUpdateDetailForApp(bool system_install,
                                    const wchar_t* app_guid,
                                    ProductData* data);

  
  
  static bool GetUpdateDetailForGoogleUpdate(bool system_install,
                                             ProductData* data);

  
  
  static bool GetUpdateDetail(bool system_install, ProductData* data);

  
  
  
  
  
  
  static bool SetExperimentLabels(bool system_install,
                                  const base::string16& experiment_labels);

  
  
  
  
  
  
  static bool ReadExperimentLabels(bool system_install,
                                   base::string16* experiment_labels);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(GoogleUpdateSettings);
};

#endif  
