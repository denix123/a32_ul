// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_SETTINGS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_SETTINGS_HANDLER_H_

#include <set>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/error_console/error_console.h"
#include "chrome/browser/extensions/extension_install_prompt.h"
#include "chrome/browser/extensions/extension_install_ui.h"
#include "chrome/browser/extensions/extension_management.h"
#include "chrome/browser/extensions/extension_uninstall_dialog.h"
#include "chrome/browser/extensions/requirements_checker.h"
#include "chrome/common/extensions/webstore_install_result.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_prefs_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/warning_service.h"
#include "url/gurl.h"

class ExtensionService;

namespace base {
class DictionaryValue;
class FilePath;
class ListValue;
}

namespace content {
class WebUIDataSource;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace extensions {
class Extension;
class ExtensionRegistry;
class ManagementPolicy;

struct ExtensionPage {
  ExtensionPage(const GURL& url,
                int render_process_id,
                int render_view_id,
                bool incognito,
                bool generated_background_page);
  GURL url;
  int render_process_id;
  int render_view_id;
  bool incognito;
  bool generated_background_page;
};

class ExtensionSettingsHandler
    : public content::WebUIMessageHandler,
      public content::NotificationObserver,
      public content::WebContentsObserver,
      public ErrorConsole::Observer,
      public ExtensionInstallPrompt::Delegate,
      public ExtensionManagement::Observer,
      public ExtensionPrefsObserver,
      public ExtensionRegistryObserver,
      public ExtensionUninstallDialog::Delegate,
      public WarningService::Observer,
      public base::SupportsWeakPtr<ExtensionSettingsHandler> {
 public:
  ExtensionSettingsHandler();
  virtual ~ExtensionSettingsHandler();

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  
  base::DictionaryValue* CreateExtensionDetailValue(
      const Extension* extension,
      const std::vector<ExtensionPage>& pages,
      const WarningService* warning_service);

  void GetLocalizedValues(content::WebUIDataSource* source);

 private:
  friend class ExtensionUITest;
  friend class BrokerDelegate;

  
  virtual void RenderViewDeleted(
      content::RenderViewHost* render_view_host) OVERRIDE;
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;

  
  ExtensionSettingsHandler(ExtensionService* service,
                           ManagementPolicy* policy);

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void OnErrorAdded(const ExtensionError* error) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void OnExtensionDisableReasonsChanged(const std::string& extension_id,
                                                int disable_reasons) OVERRIDE;

  
  virtual void OnExtensionManagementSettingsChanged() OVERRIDE;

  
  
  virtual void ExtensionUninstallAccepted() OVERRIDE;
  virtual void ExtensionUninstallCanceled() OVERRIDE;

  
  virtual void ExtensionWarningsChanged() OVERRIDE;

  
  virtual void InstallUIProceed() OVERRIDE;
  virtual void InstallUIAbort(bool user_initiated) OVERRIDE;

  
  void ReloadUnpackedExtensions();

  
  void HandleRequestExtensionsData(const base::ListValue* args);

  
  void HandleToggleDeveloperMode(const base::ListValue* args);

  
  void HandleInspectMessage(const base::ListValue* args);

  
  void HandleLaunchMessage(const base::ListValue* args);

  
  void HandleReloadMessage(const base::ListValue* args);

  
  void HandleRepairMessage(const base::ListValue* args);

  
  void HandleEnableMessage(const base::ListValue* args);

  
  void HandleEnableIncognitoMessage(const base::ListValue* args);

  
  void HandleEnableErrorCollectionMessage(const base::ListValue* args);

  
  void HandleAllowFileAccessMessage(const base::ListValue* args);

  
  void HandleAllowOnAllUrlsMessage(const base::ListValue* args);

  
  void HandleUninstallMessage(const base::ListValue* args);

  
  void HandleOptionsMessage(const base::ListValue* args);

  
  void HandlePermissionsMessage(const base::ListValue* args);

  
  void HandleShowButtonMessage(const base::ListValue* args);

  
  void HandleAutoUpdateMessage(const base::ListValue* args);

  
  void HandleDismissADTPromoMessage(const base::ListValue* args);

  
  void HandleShowPath(const base::ListValue* args);

  
  void ShowAlert(const std::string& message);

  
  
  const Extension* GetActiveExtension(const base::ListValue* args);

  
  void MaybeUpdateAfterNotification();

  
  void MaybeRegisterForNotifications();

  
  std::vector<ExtensionPage> GetInspectablePagesForExtension(
      const Extension* extension, bool extension_is_enabled);
  void GetInspectablePagesForExtensionProcess(
      const Extension* extension,
      const std::set<content::RenderViewHost*>& views,
      std::vector<ExtensionPage>* result);
  void GetAppWindowPagesForExtensionProfile(const Extension* extension,
                                            Profile* profile,
                                            std::vector<ExtensionPage>* result);

  
  
  ExtensionUninstallDialog* GetExtensionUninstallDialog();

  
  void OnReinstallComplete(bool success,
                           const std::string& error,
                           webstore_install::Result result);

  
  void OnRequirementsChecked(std::string extension_id,
                             std::vector<std::string> requirement_errors);

  
  
  
  
  
  
  
  void HandleLoadRetryMessage(bool retry, const base::FilePath& path);

  
  ExtensionService* extension_service_;

  
  ManagementPolicy* management_policy_;

  
  scoped_ptr<ExtensionUninstallDialog> extension_uninstall_dialog_;

  
  std::string extension_id_prompting_;

  
  
  
  bool ignore_notifications_;

  
  
  
  
  
  content::RenderViewHost* deleting_rvh_;
  
  int deleting_rwh_id_;
  int deleting_rph_id_;

  
  
  
  
  bool registered_for_notifications_;

  content::NotificationRegistrar registrar_;

  
  
  
  scoped_ptr<RequirementsChecker> requirements_checker_;

  
  scoped_ptr<ExtensionInstallPrompt> prompt_;

  ScopedObserver<WarningService, WarningService::Observer>
      warning_service_observer_;

  
  ScopedObserver<ErrorConsole, ErrorConsole::Observer> error_console_observer_;

  
  
  ScopedObserver<ExtensionPrefs, ExtensionPrefsObserver>
      extension_prefs_observer_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  ScopedObserver<ExtensionManagement, ExtensionManagement::Observer>
      extension_management_observer_;

  
  
  bool should_do_verification_check_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionSettingsHandler);
};

}  

#endif  
