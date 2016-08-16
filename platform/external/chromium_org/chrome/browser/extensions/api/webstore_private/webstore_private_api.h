// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_WEBSTORE_PRIVATE_WEBSTORE_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_WEBSTORE_PRIVATE_WEBSTORE_PRIVATE_API_H_

#include <string>

#include "chrome/browser/extensions/active_install_data.h"
#include "chrome/browser/extensions/bundle_installer.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/extensions/extension_install_prompt.h"
#include "chrome/browser/extensions/webstore_install_helper.h"
#include "chrome/browser/extensions/webstore_installer.h"
#include "chrome/common/extensions/api/webstore_private.h"
#include "chrome/common/extensions/webstore_install_result.h"
#include "content/public/browser/gpu_data_manager_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "third_party/skia/include/core/SkBitmap.h"

class ProfileSyncService;

namespace content {
class GpuDataManager;
}

class GPUFeatureChecker;

namespace extensions {

class WebstorePrivateApi {
 public:
  
  static void SetWebstoreInstallerDelegateForTesting(
      WebstoreInstaller::Delegate* delegate);

  
  
  
  static scoped_ptr<WebstoreInstaller::Approval> PopApprovalForTesting(
      Profile* profile, const std::string& extension_id);
};

class WebstorePrivateInstallBundleFunction
    : public ChromeAsyncExtensionFunction,
      public extensions::BundleInstaller::Delegate {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.installBundle",
                             WEBSTOREPRIVATE_INSTALLBUNDLE)

  WebstorePrivateInstallBundleFunction();

  
  virtual void OnBundleInstallApproved() OVERRIDE;
  virtual void OnBundleInstallCanceled(bool user_initiated) OVERRIDE;
  virtual void OnBundleInstallCompleted() OVERRIDE;

 protected:
  virtual ~WebstorePrivateInstallBundleFunction();

  
  virtual bool RunAsync() OVERRIDE;

  
  bool ReadBundleInfo(
      const api::webstore_private::InstallBundle::Params& details,
          extensions::BundleInstaller::ItemList* items);

 private:
  scoped_refptr<extensions::BundleInstaller> bundle_;
};

class WebstorePrivateBeginInstallWithManifest3Function
    : public ChromeAsyncExtensionFunction,
      public ExtensionInstallPrompt::Delegate,
      public WebstoreInstallHelper::Delegate {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.beginInstallWithManifest3",
                             WEBSTOREPRIVATE_BEGININSTALLWITHMANIFEST3)

  
  
  
  enum ResultCode {
    ERROR_NONE = 0,

    
    UNKNOWN_ERROR,

    
    USER_CANCELLED,

    
    MANIFEST_ERROR,

    
    ICON_ERROR,

    
    INVALID_ID,

    
    PERMISSION_DENIED,

    
    INVALID_ICON_URL,

    
    ALREADY_INSTALLED,
  };

  WebstorePrivateBeginInstallWithManifest3Function();

  
  virtual void OnWebstoreParseSuccess(
      const std::string& id,
      const SkBitmap& icon,
      base::DictionaryValue* parsed_manifest) OVERRIDE;
  virtual void OnWebstoreParseFailure(
      const std::string& id,
      InstallHelperResultCode result_code,
      const std::string& error_message) OVERRIDE;

  
  virtual void InstallUIProceed() OVERRIDE;
  virtual void InstallUIAbort(bool user_initiated) OVERRIDE;

 protected:
  virtual ~WebstorePrivateBeginInstallWithManifest3Function();

  
  virtual bool RunAsync() OVERRIDE;

  
  void SetResultCode(ResultCode code);

 private:
  const char* ResultCodeToString(ResultCode code);

  
  scoped_ptr<api::webstore_private::BeginInstallWithManifest3::Params> params_;

  
  scoped_ptr<base::DictionaryValue> parsed_manifest_;
  SkBitmap icon_;

  
  
  scoped_refptr<extensions::Extension> dummy_extension_;

  
  scoped_ptr<ExtensionInstallPrompt> install_prompt_;

  scoped_ptr<ScopedActiveInstall> scoped_active_install_;

  
  
  std::string authuser_;
};

class WebstorePrivateCompleteInstallFunction
    : public ChromeAsyncExtensionFunction,
      public WebstoreInstaller::Delegate {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.completeInstall",
                             WEBSTOREPRIVATE_COMPLETEINSTALL)

  WebstorePrivateCompleteInstallFunction();

  
  virtual void OnExtensionInstallSuccess(const std::string& id) OVERRIDE;
  virtual void OnExtensionInstallFailure(
      const std::string& id,
      const std::string& error,
      WebstoreInstaller::FailureReason reason) OVERRIDE;

 protected:
  virtual ~WebstorePrivateCompleteInstallFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  scoped_ptr<WebstoreInstaller::Approval> approval_;
  scoped_ptr<ScopedActiveInstall> scoped_active_install_;

  void OnInstallSuccess(const std::string& id);
};

class WebstorePrivateEnableAppLauncherFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.enableAppLauncher",
                             WEBSTOREPRIVATE_ENABLEAPPLAUNCHER)

  WebstorePrivateEnableAppLauncherFunction();

 protected:
  virtual ~WebstorePrivateEnableAppLauncherFunction();

  
  virtual bool RunSync() OVERRIDE;
};

class WebstorePrivateGetBrowserLoginFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.getBrowserLogin",
                             WEBSTOREPRIVATE_GETBROWSERLOGIN)

 protected:
  virtual ~WebstorePrivateGetBrowserLoginFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class WebstorePrivateGetStoreLoginFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.getStoreLogin",
                             WEBSTOREPRIVATE_GETSTORELOGIN)

 protected:
  virtual ~WebstorePrivateGetStoreLoginFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class WebstorePrivateSetStoreLoginFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.setStoreLogin",
                             WEBSTOREPRIVATE_SETSTORELOGIN)

 protected:
  virtual ~WebstorePrivateSetStoreLoginFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class WebstorePrivateGetWebGLStatusFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.getWebGLStatus",
                             WEBSTOREPRIVATE_GETWEBGLSTATUS)

  WebstorePrivateGetWebGLStatusFunction();

 protected:
  virtual ~WebstorePrivateGetWebGLStatusFunction();

  void OnFeatureCheck(bool feature_allowed);

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void CreateResult(bool webgl_allowed);

  scoped_refptr<GPUFeatureChecker> feature_checker_;
};

class WebstorePrivateGetIsLauncherEnabledFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.getIsLauncherEnabled",
                             WEBSTOREPRIVATE_GETISLAUNCHERENABLED)

  WebstorePrivateGetIsLauncherEnabledFunction() {}

 protected:
  virtual ~WebstorePrivateGetIsLauncherEnabledFunction() {}

  
  virtual bool RunSync() OVERRIDE;

 private:
  void OnIsLauncherCheckCompleted(bool is_enabled);
};

class WebstorePrivateIsInIncognitoModeFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.isInIncognitoMode",
                             WEBSTOREPRIVATE_ISININCOGNITOMODEFUNCTION)

  WebstorePrivateIsInIncognitoModeFunction() {}

 protected:
  virtual ~WebstorePrivateIsInIncognitoModeFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class WebstorePrivateLaunchEphemeralAppFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.launchEphemeralApp",
                             WEBSTOREPRIVATE_LAUNCHEPHEMERALAPP)

  WebstorePrivateLaunchEphemeralAppFunction();

 protected:
  virtual ~WebstorePrivateLaunchEphemeralAppFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnLaunchComplete(webstore_install::Result result,
                        const std::string& error);
  void SetResult(
      api::webstore_private::LaunchEphemeralApp::Results::Result result,
      const std::string& error);
};

class WebstorePrivateGetEphemeralAppsEnabledFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webstorePrivate.getEphemeralAppsEnabled",
                             WEBSTOREPRIVATE_GETEPHEMERALAPPSENABLED)

  WebstorePrivateGetEphemeralAppsEnabledFunction();

 protected:
  virtual ~WebstorePrivateGetEphemeralAppsEnabledFunction();

  
  virtual bool RunSync() OVERRIDE;
};

}  

#endif  
