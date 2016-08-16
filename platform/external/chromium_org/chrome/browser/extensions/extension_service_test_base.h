// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_TEST_BASE_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_TEST_BASE_H_

#include "base/at_exit.h"
#include "base/files/file_path.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/test/test_browser_thread_bundle.h"
#include "content/public/test/test_utils.h"
#include "testing/gtest/include/gtest/gtest.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/login/users/scoped_test_user_manager.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#endif

class ExtensionService;
class Profile;
class TestingProfile;

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionRegistry;
class ManagementPolicy;

class ExtensionServiceTestBase : public testing::Test {
 public:
  struct ExtensionServiceInitParams {
    base::FilePath profile_path;
    base::FilePath pref_file;
    base::FilePath extensions_install_dir;
    bool autoupdate_enabled;    
    bool is_first_run;          
    bool profile_is_supervised; 

    
    
    ExtensionServiceInitParams();
  };

 protected:
  ExtensionServiceTestBase();
  virtual ~ExtensionServiceTestBase();

  
  virtual void SetUp() OVERRIDE;
  static void SetUpTestCase();  

  
  ExtensionServiceInitParams CreateDefaultInitParams();

  
  void InitializeExtensionService(const ExtensionServiceInitParams& params);

  
  void InitializeEmptyExtensionService();

  
  
  void InitializeInstalledExtensionService(
      const base::FilePath& prefs_file,
      const base::FilePath& source_install_dir);

  
  void InitializeGoodInstalledExtensionService();

  
  void InitializeExtensionServiceWithUpdater();

  
  void InitializeProcessManager();

  
  
  

  content::BrowserContext* browser_context();
  Profile* profile();
  ExtensionService* service() { return service_; }
  ExtensionRegistry* registry() { return registry_; }
  const base::FilePath& extensions_install_dir() const {
    return extensions_install_dir_;
  }
  const base::FilePath& data_dir() const { return data_dir_; }
  const base::ScopedTempDir& temp_dir() const { return temp_dir_; }

  
  
  

  
  scoped_ptr<TestingProfile> profile_;

  
  
  ExtensionService* service_;

 private:
  void CreateExtensionService(const ExtensionServiceInitParams& params);

  
  
  base::ScopedTempDir temp_dir_;

  
  
  base::ShadowingAtExitManager at_exit_manager_;
  content::TestBrowserThreadBundle thread_bundle_;

  
  base::FilePath extensions_install_dir_;

  
  base::FilePath data_dir_;

  content::InProcessUtilityThreadHelper in_process_utility_thread_helper_;

  
  extensions::ExtensionRegistry* registry_;

#if defined OS_CHROMEOS
  chromeos::ScopedTestDeviceSettingsService test_device_settings_service_;
  chromeos::ScopedTestCrosSettings test_cros_settings_;
  chromeos::ScopedTestUserManager test_user_manager_;
#endif
};

}  

#endif  
