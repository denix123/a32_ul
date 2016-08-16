// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_APP_MODE_STARTUP_APP_LAUNCHER_H_
#define CHROME_BROWSER_CHROMEOS_APP_MODE_STARTUP_APP_LAUNCHER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/app_mode/kiosk_app_launch_error.h"
#include "chrome/browser/chromeos/app_mode/kiosk_app_manager_observer.h"
#include "chrome/browser/extensions/install_observer.h"
#include "google_apis/gaia/oauth2_token_service.h"

class Profile;

namespace chromeos {

class StartupAppLauncher : public base::SupportsWeakPtr<StartupAppLauncher>,
                           public OAuth2TokenService::Observer,
                           public extensions::InstallObserver,
                           public KioskAppManagerObserver {
 public:
  class Delegate {
   public:
    
    
    virtual void InitializeNetwork() = 0;

    
    virtual bool IsNetworkReady() = 0;

    virtual void OnLoadingOAuthFile() = 0;
    virtual void OnInitializingTokenService() = 0;
    virtual void OnInstallingApp() = 0;
    virtual void OnReadyToLaunch() = 0;
    virtual void OnLaunchSucceeded() = 0;
    virtual void OnLaunchFailed(KioskAppLaunchError::Error error) = 0;
    virtual bool IsShowingNetworkConfigScreen() = 0;

   protected:
    virtual ~Delegate() {}
  };

  StartupAppLauncher(Profile* profile,
                     const std::string& app_id,
                     bool diagnostic_mode,
                     Delegate* delegate);

  virtual ~StartupAppLauncher();

  
  void Initialize();

  
  void ContinueWithNetworkReady();

  
  void LaunchApp();

  
  void RestartLauncher();

 private:
  
  struct KioskOAuthParams {
    std::string refresh_token;
    std::string client_id;
    std::string client_secret;
  };

  void OnLaunchSuccess();
  void OnLaunchFailure(KioskAppLaunchError::Error error);

  
  void OnUpdateCheckFinished();

  void BeginInstall();
  void OnReadyToLaunch();
  void UpdateAppData();

  void InitializeTokenService();
  void MaybeInitializeNetwork();
  void MaybeLaunchApp();

  void StartLoadingOAuthFile();
  static void LoadOAuthFileOnBlockingPool(KioskOAuthParams* auth_params);
  void OnOAuthFileLoaded(KioskOAuthParams* auth_params);

  void OnKioskAppDataLoadStatusChanged(const std::string& app_id);

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokensLoaded() OVERRIDE;

  
  virtual void OnFinishCrxInstall(const std::string& extension_id,
                                  bool success) OVERRIDE;

  
  virtual void OnKioskExtensionLoadedInCache(
      const std::string& app_id) OVERRIDE;
  virtual void OnKioskExtensionDownloadFailed(
      const std::string& app_id) OVERRIDE;

  Profile* profile_;
  const std::string app_id_;
  const bool diagnostic_mode_;
  Delegate* delegate_;
  bool network_ready_handled_;
  int launch_attempt_;
  bool ready_to_launch_;
  bool wait_for_crx_update_;

  KioskOAuthParams auth_params_;

  DISALLOW_COPY_AND_ASSIGN(StartupAppLauncher);
};

}  

#endif  
