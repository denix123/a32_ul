// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_GOOGLE_CHROME_DISTRIBUTION_H_
#define CHROME_INSTALLER_UTIL_GOOGLE_CHROME_DISTRIBUTION_H_

#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "chrome/installer/util/browser_distribution.h"

namespace base {
class FilePath;
}

class AppRegistrationData;

class GoogleChromeDistribution : public BrowserDistribution {
 public:
  
  
  
  
  
  
  
  
  
  virtual void DoPostUninstallOperations(
      const Version& version,
      const base::FilePath& local_data_path,
      const base::string16& distribution_data) OVERRIDE;

  virtual base::string16 GetActiveSetupGuid() OVERRIDE;

  virtual base::string16 GetShortcutName(ShortcutType shortcut_type) OVERRIDE;

  virtual base::string16 GetIconFilename() OVERRIDE;

  virtual int GetIconIndex(ShortcutType shortcut_type) OVERRIDE;

  virtual base::string16 GetBaseAppName() OVERRIDE;

  virtual base::string16 GetBaseAppId() OVERRIDE;

  virtual base::string16 GetBrowserProgIdPrefix() OVERRIDE;

  virtual base::string16 GetBrowserProgIdDesc() OVERRIDE;

  virtual base::string16 GetInstallSubDir() OVERRIDE;

  virtual base::string16 GetPublisherName() OVERRIDE;

  virtual base::string16 GetAppDescription() OVERRIDE;

  virtual std::string GetSafeBrowsingName() OVERRIDE;

  virtual std::string GetNetworkStatsServer() const OVERRIDE;

  
  
  
  virtual base::string16 GetDistributionData(HKEY root_key) OVERRIDE;

  virtual base::string16 GetUninstallLinkName() OVERRIDE;

  virtual base::string16 GetUninstallRegPath() OVERRIDE;

  virtual bool GetCommandExecuteImplClsid(
      base::string16* handler_class_uuid) OVERRIDE;

  virtual bool AppHostIsSupported() OVERRIDE;

  virtual void UpdateInstallStatus(
      bool system_install,
      installer::ArchiveType archive_type,
      installer::InstallStatus install_status) OVERRIDE;

  virtual bool ShouldSetExperimentLabels() OVERRIDE;

  virtual bool HasUserExperiments() OVERRIDE;

 protected:
  
  GoogleChromeDistribution();

  explicit GoogleChromeDistribution(
      scoped_ptr<AppRegistrationData> app_reg_data);

 private:
  friend class BrowserDistribution;
};

#endif  
