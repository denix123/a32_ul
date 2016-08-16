// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_BROWSER_OPTIONS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_BROWSER_OPTIONS_HANDLER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/prefs/pref_member.h"
#include "base/scoped_observer.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/shell_integration.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "chrome/browser/ui/host_desktop.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "components/search_engines/template_url_service_observer.h"
#include "components/signin/core/browser/signin_manager_base.h"
#include "content/public/browser/notification_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "ui/base/models/table_model_observer.h"
#include "ui/shell_dialogs/select_file_dialog.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/policy/consumer_management_service.h"
#include "chrome/browser/chromeos/system/pointer_device_observer.h"
#endif  

class AutocompleteController;
class CloudPrintSetupHandler;
class CustomHomePagesTableModel;
class TemplateURLService;

namespace base {
class Value;
}

namespace policy {
class PolicyChangeRegistrar;
}

namespace options {

class BrowserOptionsHandler
    : public OptionsPageUIHandler,
      public ProfileSyncServiceObserver,
      public SigninManagerBase::Observer,
      public ui::SelectFileDialog::Listener,
      public ShellIntegration::DefaultWebClientObserver,
#if defined(OS_CHROMEOS)
      public chromeos::system::PointerDeviceObserver::Observer,
      public policy::ConsumerManagementService::Observer,
#endif
      public TemplateURLServiceObserver,
      public extensions::ExtensionRegistryObserver,
      public content::NotificationObserver {
 public:
  BrowserOptionsHandler();
  virtual ~BrowserOptionsHandler();

  
  virtual void GetLocalizedValues(base::DictionaryValue* values) OVERRIDE;
  virtual void PageLoadStarted() OVERRIDE;
  virtual void InitializeHandler() OVERRIDE;
  virtual void InitializePage() OVERRIDE;
  virtual void RegisterMessages() OVERRIDE;
  virtual void Uninitialize() OVERRIDE;

  
  virtual void OnStateChanged() OVERRIDE;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  virtual void SetDefaultWebClientUIState(
      ShellIntegration::DefaultWebClientUIState state) OVERRIDE;
  virtual bool IsInteractiveSetDefaultPermitted() OVERRIDE;

  
  virtual void OnTemplateURLServiceChanged() OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

#if defined(ENABLE_FULL_PRINTING) && !defined(OS_CHROMEOS)
  void OnCloudPrintPrefsChanged();
#endif

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;

#if defined(OS_CHROMEOS)
  
  virtual void TouchpadExists(bool exists) OVERRIDE;
  virtual void MouseExists(bool exists) OVERRIDE;

  
  void OnUserImagePolicyChanged(const base::Value* previous_policy,
                                const base::Value* current_policy);

  
  void OnWallpaperPolicyChanged(const base::Value* previous_policy,
                                const base::Value* current_policy);

  
  void OnPowerwashDialogShow(const base::ListValue* args);

  
  virtual void OnConsumerManagementStatusChanged() OVERRIDE;
#endif

  void UpdateSyncState();

  
  void OnSigninAllowedPrefChange();

  
  void BecomeDefaultBrowser(const base::ListValue* args);

  
  void SetDefaultSearchEngine(const base::ListValue* args);

  
  void ToggleAutoLaunch(const base::ListValue* args);

  
  
  
  
  
  static void CheckAutoLaunch(base::WeakPtr<BrowserOptionsHandler> weak_this,
                              const base::FilePath& profile_path);

  
  
  
  void CheckAutoLaunchCallback(bool is_in_auto_launch_group,
                               bool will_launch_at_login);

  
  int StatusStringIdForState(ShellIntegration::DefaultWebClientState state);

  
  bool ShouldShowSetDefaultBrowser();

  
  bool ShouldShowMultiProfilesUserList();

  
  bool ShouldAllowAdvancedSettings();

  
  
  void UpdateDefaultBrowserState();

  
  void SetDefaultBrowserUIString(int status_string_id);

  
  void AddTemplateUrlServiceObserver();

  
  
  
  
  
  
  
  scoped_ptr<base::ListValue> GetProfilesInfoList();

  
  void SendProfilesInfo();

  
  
  void DeleteProfile(const base::ListValue* args);

  void ObserveThemeChanged();
  void ThemesReset(const base::ListValue* args);
#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
  void ThemesSetNative(const base::ListValue* args);
#endif

#if defined(OS_CHROMEOS)
  void UpdateAccountPicture();

  
  
  
  void OnAccountPictureManagedChanged(bool managed);

  
  
  
  void OnWallpaperManagedChanged(bool managed);
#endif

  
  
  void HandleSelectDownloadLocation(const base::ListValue* args);

  
  
  void HandleAutoOpenButton(const base::ListValue* args);

  
  
  
  void HandleDefaultFontSize(const base::ListValue* args);

  
  
  
  void HandleDefaultZoomFactor(const base::ListValue* args);

  
  
  void HandleUseSSL3Checkbox(const base::ListValue* args);

  
  
  void HandleUseTLS1Checkbox(const base::ListValue* args);

  
  void HandleRestartBrowser(const base::ListValue* args);

  
  void HandleRequestProfilesInfo(const base::ListValue* args);

#if !defined(OS_CHROMEOS)
  
  
  void ShowNetworkProxySettings(const base::ListValue* args);
#endif

#if !defined(USE_NSS)
  
  
  void ShowManageSSLCertificates(const base::ListValue* args);
#endif

#if defined(ENABLE_SERVICE_DISCOVERY)
  void ShowCloudPrintDevicesPage(const base::ListValue* args);
#endif

#if defined(ENABLE_FULL_PRINTING)
  
  void RegisterCloudPrintValues(base::DictionaryValue* values);
#endif

  
  
  void SendHotwordAvailable();

  
  void HandleRequestHotwordAvailable(const base::ListValue* args);

  
  void HandleLaunchHotwordAudioVerificationApp(const base::ListValue* args);

  
  void HandleLaunchEasyUnlockSetup(const base::ListValue* args);

  
  void HandleRefreshExtensionControlIndicators(const base::ListValue* args);

#if defined(OS_CHROMEOS)
  
  void HandleOpenWallpaperManager(const base::ListValue* args);

  
  
  
  void VirtualKeyboardChangeCallback(const base::ListValue* args);

  
  
  void PerformFactoryResetRestart(const base::ListValue* args);
#endif

  
  void SetupMetricsReportingSettingVisibility();

  
  void SetupNetworkPredictionControl();

  
  void SetupFontSizeSelector();

  
  void SetupPageZoomSelector();

  
  void SetupAutoOpenFileTypes();

  
  void SetupProxySettingsSection();

  
  void SetupManageCertificatesSection();

  
  void SetupManagingSupervisedUsers();

  
  void SetupEasyUnlock();

  
  void SetupExtensionControlledIndicators();

  
  
  void SetupMetricsReportingCheckbox();

  
  
  void HandleMetricsReportingChange(const base::ListValue* args);

  
  void MetricsReportingChangeCallback(bool enabled);

  
  void SetMetricsReportingCheckbox(bool checked, bool disabled);

#if defined(OS_CHROMEOS)
  
  void SetupAccessibilityFeatures();
#endif

  
  
  scoped_ptr<base::DictionaryValue> GetSyncStateDictionary();

  scoped_refptr<ShellIntegration::DefaultBrowserWorker> default_browser_worker_;

  bool page_initialized_;

  StringPrefMember homepage_;
  BooleanPrefMember default_browser_policy_;

  TemplateURLService* template_url_service_;  

  scoped_refptr<ui::SelectFileDialog> select_folder_dialog_;

  bool cloud_print_mdns_ui_enabled_;

  StringPrefMember auto_open_files_;
  DoublePrefMember default_zoom_level_;

  PrefChangeRegistrar profile_pref_registrar_;
#if defined(OS_CHROMEOS)
  scoped_ptr<policy::PolicyChangeRegistrar> policy_registrar_;
#endif

  ScopedObserver<SigninManagerBase, SigninManagerBase::Observer>
      signin_observer_;

  
  base::WeakPtrFactory<BrowserOptionsHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserOptionsHandler);
};

}  

#endif  
