// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/extensions/blacklist.h"
#include "chrome/browser/extensions/extension_management.h"
#include "chrome/browser/extensions/pending_extension_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/external_provider_interface.h"
#include "extensions/browser/install_flag.h"
#include "extensions/browser/management_policy.h"
#include "extensions/browser/process_manager.h"
#include "extensions/browser/uninstall_reason.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_set.h"
#include "extensions/common/manifest.h"
#include "sync/api/string_ordinal.h"

class ExtensionSyncService;
class GURL;
class HostContentSettingsMap;
class Profile;

namespace base {
class CommandLine;
class SequencedTaskRunner;
class Version;
}

namespace content {
class DevToolsAgentHost;
}

namespace extensions {
class ComponentLoader;
class CrxInstaller;
class ExtensionActionStorageManager;
class ExtensionDownloader;
class ExtensionDownloaderDelegate;
class ExtensionErrorController;
class ExtensionRegistry;
class ExtensionSystem;
class ExtensionUpdater;
class OneShotEvent;
class ExternalInstallManager;
class SharedModuleService;
class UpdateObserver;
}  

class ExtensionServiceInterface
    : public base::SupportsWeakPtr<ExtensionServiceInterface> {
 public:
  virtual ~ExtensionServiceInterface() {}

  
  
  
  virtual const extensions::ExtensionSet* extensions() const = 0;

  
  virtual extensions::PendingExtensionManager* pending_extension_manager() = 0;

  
  
  
  
  
  virtual bool UpdateExtension(
      const std::string& id,
      const base::FilePath& path,
      bool file_ownership_passed,
      extensions::CrxInstaller** out_crx_installer) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual const extensions::Extension* GetExtensionById(
      const std::string& id,
      bool include_disabled) const = 0;

  
  
  
  
  
  
  virtual const extensions::Extension* GetInstalledExtension(
      const std::string& id) const = 0;

  
  
  
  virtual const extensions::Extension* GetPendingExtensionUpdate(
      const std::string& extension_id) const = 0;

  
  
  
  virtual void FinishDelayedInstallation(const std::string& extension_id) = 0;

  
  
  virtual bool IsExtensionEnabled(const std::string& extension_id) const = 0;

  
  
  
  virtual void CheckManagementPolicy() = 0;

  
  
  
  
  virtual void CheckForUpdatesSoon() = 0;

  
  
  virtual void AddExtension(const extensions::Extension* extension) = 0;

  
  
  
  virtual void AddComponentExtension(
      const extensions::Extension* extension) = 0;

  
  virtual void UnloadExtension(
      const std::string& extension_id,
      extensions::UnloadedExtensionInfo::Reason reason) = 0;

  
  virtual void RemoveComponentExtension(const std::string& extension_id) = 0;

  
  virtual bool is_ready() = 0;

  
  virtual base::SequencedTaskRunner* GetFileTaskRunner() = 0;
};

class ExtensionService
    : public ExtensionServiceInterface,
      public extensions::ExternalProviderInterface::VisitorInterface,
      public content::NotificationObserver,
      public extensions::Blacklist::Observer,
      public extensions::ExtensionManagement::Observer {
 public:
  
  
  static bool UninstallExtensionHelper(ExtensionService* extensions_service,
                                       const std::string& extension_id,
                                       extensions::UninstallReason reason);

  
  
  ExtensionService(Profile* profile,
                   const base::CommandLine* command_line,
                   const base::FilePath& install_directory,
                   extensions::ExtensionPrefs* extension_prefs,
                   extensions::Blacklist* blacklist,
                   bool autoupdate_enabled,
                   bool extensions_enabled,
                   extensions::OneShotEvent* ready);

  virtual ~ExtensionService();

  
  
  
  virtual const extensions::ExtensionSet* extensions() const OVERRIDE;
  virtual extensions::PendingExtensionManager*
      pending_extension_manager() OVERRIDE;
  virtual const extensions::Extension* GetExtensionById(
      const std::string& id, bool include_disabled) const OVERRIDE;
  virtual const extensions::Extension* GetInstalledExtension(
      const std::string& id) const OVERRIDE;
  virtual bool UpdateExtension(
      const std::string& id,
      const base::FilePath& extension_path,
      bool file_ownership_passed,
      extensions::CrxInstaller** out_crx_installer) OVERRIDE;
  virtual bool IsExtensionEnabled(
      const std::string& extension_id) const OVERRIDE;
  virtual void UnloadExtension(
      const std::string& extension_id,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void RemoveComponentExtension(const std::string& extension_id)
      OVERRIDE;
  virtual void AddExtension(const extensions::Extension* extension) OVERRIDE;
  virtual void AddComponentExtension(const extensions::Extension* extension)
      OVERRIDE;
  virtual const extensions::Extension* GetPendingExtensionUpdate(
      const std::string& extension_id) const OVERRIDE;
  virtual void FinishDelayedInstallation(
     const std::string& extension_id) OVERRIDE;
  virtual void CheckManagementPolicy() OVERRIDE;
  virtual void CheckForUpdatesSoon() OVERRIDE;
  virtual bool is_ready() OVERRIDE;
  virtual base::SequencedTaskRunner* GetFileTaskRunner() OVERRIDE;

  
  
  virtual bool OnExternalExtensionFileFound(
      const std::string& id,
      const base::Version* version,
      const base::FilePath& path,
      extensions::Manifest::Location location,
      int creation_flags,
      bool mark_acknowledged) OVERRIDE;
  virtual bool OnExternalExtensionUpdateUrlFound(
      const std::string& id,
      const std::string& install_parameter,
      const GURL& update_url,
      extensions::Manifest::Location location,
      int creation_flags,
      bool mark_acknowledged) OVERRIDE;
  virtual void OnExternalProviderReady(
      const extensions::ExternalProviderInterface* provider) OVERRIDE;

  
  virtual void OnExtensionManagementSettingsChanged() OVERRIDE;

  
  void Init();

  
  void Shutdown();

  
  
  
  
  
  
  void ReloadExtension(const std::string& extension_id);

  
  void ReloadExtensionWithQuietFailure(const std::string& extension_id);

  
  
  
  
  
  
  virtual bool UninstallExtension(const std::string& extension_id,
                                  extensions::UninstallReason reason,
                                  const base::Closure& deletion_done_callback,
                                  base::string16* error);

  
  
  virtual void EnableExtension(const std::string& extension_id);

  
  
  virtual void DisableExtension(
      const std::string& extension_id,
      extensions::Extension::DisableReason disable_reason);

  
  
  
  void DisableUserExtensions(const std::vector<std::string>& except_ids);

  
  
  
  void GrantPermissionsAndEnableExtension(
      const extensions::Extension* extension);

  
  
  void GrantPermissions(const extensions::Extension* extension);

  
  void CheckForExternalUpdates();

  
  virtual void OnLoadedInstalledExtensions();

  
  
  
  
  
  void OnExtensionInstalled(const extensions::Extension* extension,
                            const syncer::StringOrdinal& page_ordinal,
                            int install_flags);
  void OnExtensionInstalled(const extensions::Extension* extension,
                            const syncer::StringOrdinal& page_ordinal) {
    OnExtensionInstalled(extension,
                         page_ordinal,
                         static_cast<int>(extensions::kInstallFlagNone));
  }

  
  void MaybeFinishDelayedInstallations();

  
  
  
  
  void PromoteEphemeralApp(
      const extensions::Extension* extension, bool is_from_sync);

  
  
  void DidCreateRenderViewForBackgroundPage(extensions::ExtensionHost* host);

  
  void SetFileTaskRunnerForTesting(
      const scoped_refptr<base::SequencedTaskRunner>& task_runner);

  
  
  void OnGarbageCollectIsolatedStorageStart();

  
  
  void OnGarbageCollectIsolatedStorageFinished();

  
  
  
  
  static void RecordPermissionMessagesHistogram(
      const extensions::Extension* extension, const char* histogram);

  
  
  
  void TerminateExtension(const std::string& extension_id);

  
  void RegisterContentSettings(
      HostContentSettingsMap* host_content_settings_map);

  
  void AddUpdateObserver(extensions::UpdateObserver* observer);
  void RemoveUpdateObserver(extensions::UpdateObserver* observer);

  
  

  
  base::WeakPtr<ExtensionService> AsWeakPtr() { return base::AsWeakPtr(this); }

  
  content::BrowserContext* GetBrowserContext() const;

  bool extensions_enabled() const { return extensions_enabled_; }
  void set_extensions_enabled(bool enabled) { extensions_enabled_ = enabled; }

  const base::FilePath& install_directory() const { return install_directory_; }

  const extensions::ExtensionSet* delayed_installs() const {
    return &delayed_installs_;
  }

  bool show_extensions_prompts() const { return show_extensions_prompts_; }
  void set_show_extensions_prompts(bool show_extensions_prompts) {
    show_extensions_prompts_ = show_extensions_prompts;
  }

  Profile* profile() { return profile_; }

  void set_extension_sync_service(
      ExtensionSyncService* extension_sync_service) {
    extension_sync_service_ = extension_sync_service;
  }

  
  extensions::ExtensionUpdater* updater() { return updater_.get(); }

  extensions::ComponentLoader* component_loader() {
    return component_loader_.get();
  }

  bool browser_terminating() const { return browser_terminating_; }

  extensions::SharedModuleService* shared_module_service() {
    return shared_module_service_.get();
  }

  extensions::ExternalInstallManager* external_install_manager() {
    return external_install_manager_.get();
  }

  
  

  
  void UnloadAllExtensionsForTest();

  
  void ReloadExtensionsForTest();

  
  void ClearProvidersForTesting();

  
  
  void AddProviderForTesting(
      extensions::ExternalProviderInterface* test_provider);

  
  void BlacklistExtensionForTest(const std::string& extension_id);

#if defined(UNIT_TEST)
  void TrackTerminatedExtensionForTest(const extensions::Extension* extension) {
    TrackTerminatedExtension(extension);
  }

  void FinishInstallationForTest(const extensions::Extension* extension) {
    FinishInstallation(extension, false );
  }
#endif

  void set_browser_terminating_for_test(bool value) {
    browser_terminating_ = value;
  }

  
  
  
  void set_install_updates_when_idle_for_test(bool value) {
    install_updates_when_idle_ = value;
  }

  
  
  void set_external_updates_finished_callback_for_test(
      const base::Closure& callback) {
    external_updates_finished_callback_ = callback;
  }


 private:
  
  scoped_ptr<extensions::ExtensionDownloader> CreateExtensionDownloader(
      extensions::ExtensionDownloaderDelegate* delegate);

  
  
  
  void ReloadExtensionImpl(const std::string& extension_id, bool be_noisy);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnBlacklistUpdated() OVERRIDE;

  
  
  void MaybeFinishDelayedInstallation(const std::string& extension_id);

  
  
  void CheckExternalUninstall(const std::string& id);

  
  void LoadGreylistFromPrefs();

  
  void SetReadyAndNotifyListeners();

  
  bool AreAllExternalProvidersReady() const;

  
  
  void OnAllExternalProvidersReady();

  
  
  void TrackTerminatedExtension(const extensions::Extension* extension);

  
  
  void UntrackTerminatedExtension(const std::string& id);

  
  
  
  
  
  void AddNewOrUpdatedExtension(const extensions::Extension* extension,
                                extensions::Extension::State initial_state,
                                int install_flags,
                                const syncer::StringOrdinal& page_ordinal,
                                const std::string& install_parameter);

  
  void NotifyExtensionLoaded(const extensions::Extension* extension);

  
  void NotifyExtensionUnloaded(
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason);

  
  
  void FinishInstallation(const extensions::Extension* extension,
                          bool was_ephemeral);

  
  
  void CheckPermissionsIncrease(const extensions::Extension* extension,
                                bool is_extension_installed);

  
  void UpdateActiveExtensionsInCrashReporter();

  
  
  bool ShouldEnableOnInstall(const extensions::Extension* extension);

  
  
  bool ShouldDelayExtensionUpdate(const std::string& extension_id,
                                  bool install_immediately) const;

  
  
  void ManageBlacklist(
      const extensions::Blacklist::BlacklistStateMap& blacklisted_ids);

  
  
  void UpdateBlockedExtensions(const extensions::ExtensionIdSet& blocked,
                               const extensions::ExtensionIdSet& unchanged);

  void UpdateGreylistedExtensions(
      const extensions::ExtensionIdSet& greylist,
      const extensions::ExtensionIdSet& unchanged,
      const extensions::Blacklist::BlacklistStateMap& state_map);

  
  void UnloadAllExtensionsInternal();

  
  
  
  void OnProfileDestructionStarted();

  
  static void UninstallExtensionOnFileThread(
      const std::string& id,
      Profile* profile,
      const base::FilePath& install_dir,
      const base::FilePath& extension_path);

  
  Profile* profile_;

  
  extensions::ExtensionSystem* system_;

  
  extensions::ExtensionPrefs* extension_prefs_;

  
  extensions::Blacklist* blacklist_;

  
  ExtensionSyncService* extension_sync_service_;

  
  extensions::ExtensionRegistry* registry_;

  
  
  
  
  
  
  extensions::ExtensionSet greylist_;

  
  
  
  extensions::ExtensionSet delayed_installs_;

  
  extensions::PendingExtensionManager pending_extension_manager_;

  
  base::FilePath install_directory_;

  
  bool extensions_enabled_;

  
  bool show_extensions_prompts_;

  
  
  bool install_updates_when_idle_;

  
  extensions::OneShotEvent* const ready_;

  
  scoped_ptr<extensions::ExtensionUpdater> updater_;

  
  
  
  typedef std::map<std::string, base::FilePath> UnloadedExtensionPathMap;
  UnloadedExtensionPathMap unloaded_extension_paths_;

  
  
  typedef std::map<std::string, scoped_refptr<content::DevToolsAgentHost> >
      OrphanedDevTools;
  OrphanedDevTools orphaned_dev_tools_;

  content::NotificationRegistrar registrar_;

  
  scoped_ptr<extensions::ComponentLoader> component_loader_;

  
  
  
  extensions::ProviderCollection external_extension_providers_;

  
  
  
  
  
  bool update_once_all_providers_are_ready_;

  
  
  
  base::Closure external_updates_finished_callback_;

  
  
  
  bool browser_terminating_;

  
  
  
  
  bool installs_delayed_for_gc_;

  
  
  
  bool is_first_run_;

  
  
  std::set<std::string> reloading_extensions_;

  
  
  std::set<std::string> extensions_being_terminated_;

  
  
  scoped_ptr<extensions::ExtensionErrorController> error_controller_;

  
  
  scoped_ptr<extensions::ExternalInstallManager> external_install_manager_;

  
  scoped_refptr<base::SequencedTaskRunner> file_task_runner_;

  scoped_ptr<extensions::ExtensionActionStorageManager>
      extension_action_storage_manager_;
  scoped_ptr<extensions::ManagementPolicy::Provider>
      shared_module_policy_provider_;

  
  scoped_ptr<extensions::SharedModuleService> shared_module_service_;

  ObserverList<extensions::UpdateObserver, true> update_observers_;

  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           DestroyingProfileClearsExtensions);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest, SetUnsetBlacklistInPrefs);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           BlacklistedExtensionWillNotInstall);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           UnloadBlacklistedExtensionPolicy);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           WillNotLoadBlacklistedExtensionsFromDirectory);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest, ReloadBlacklistedExtension);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest, BlacklistedInPrefsFromStartup);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           GreylistedExtensionDisabled);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           GreylistDontEnableManuallyDisabled);
  FRIEND_TEST_ALL_PREFIXES(ExtensionServiceTest,
                           GreylistUnknownDontChange);

  DISALLOW_COPY_AND_ASSIGN(ExtensionService);
};

#endif  
