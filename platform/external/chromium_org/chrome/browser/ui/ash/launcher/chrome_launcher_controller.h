// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_LAUNCHER_CHROME_LAUNCHER_CONTROLLER_H_
#define CHROME_BROWSER_UI_ASH_LAUNCHER_CHROME_LAUNCHER_CONTROLLER_H_

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "ash/display/display_controller.h"
#include "ash/shelf/shelf_delegate.h"
#include "ash/shelf/shelf_item_delegate.h"
#include "ash/shelf/shelf_item_types.h"
#include "ash/shelf/shelf_layout_manager_observer.h"
#include "ash/shelf/shelf_model_observer.h"
#include "ash/shelf/shelf_types.h"
#include "ash/shell_observer.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/prefs/pref_change_registrar.h"
#include "chrome/browser/extensions/app_icon_loader.h"
#include "chrome/browser/prefs/pref_service_syncable_observer.h"
#include "chrome/browser/ui/ash/app_sync_ui_state_observer.h"
#include "chrome/browser/ui/ash/launcher/chrome_launcher_app_menu_item.h"
#include "chrome/browser/ui/ash/launcher/chrome_launcher_types.h"
#include "chrome/browser/ui/extensions/extension_enable_flow_delegate.h"
#include "chrome/common/extensions/extension_constants.h"
#include "extensions/browser/extension_registry_observer.h"
#include "ui/aura/window_observer.h"

class AppSyncUIState;
class Browser;
class BrowserShortcutLauncherItemController;
class BrowserStatusMonitor;
class ExtensionEnableFlow;
class GURL;
class LauncherItemController;
class Profile;
class AppWindowLauncherController;
class TabContents;

namespace ash {
class ShelfItemDelegateManager;
class ShelfModel;
}

namespace aura {
class Window;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class Extension;
}

namespace ui {
class BaseWindow;
}

typedef ScopedVector<ChromeLauncherAppMenuItem> ChromeLauncherAppMenuItems;

// A class which needs to be overwritten dependent on the used OS to moitor
class ChromeLauncherControllerUserSwitchObserver {
 public:
  ChromeLauncherControllerUserSwitchObserver() {}
  virtual ~ChromeLauncherControllerUserSwitchObserver() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeLauncherControllerUserSwitchObserver);
};

class ChromeLauncherController : public ash::ShelfDelegate,
                                 public ash::ShelfModelObserver,
                                 public ash::ShellObserver,
                                 public ash::DisplayController::Observer,
                                 public extensions::ExtensionRegistryObserver,
                                 public extensions::AppIconLoader::Delegate,
                                 public PrefServiceSyncableObserver,
                                 public AppSyncUIStateObserver,
                                 public ExtensionEnableFlowDelegate,
                                 public ash::ShelfLayoutManagerObserver {
 public:
  
  enum IncognitoState {
    STATE_INCOGNITO,
    STATE_NOT_INCOGNITO,
  };

  
  enum AppState {
    APP_STATE_ACTIVE,
    APP_STATE_WINDOW_ACTIVE,
    APP_STATE_INACTIVE,
    APP_STATE_REMOVED
  };

  
  class AppTabHelper {
   public:
    virtual ~AppTabHelper() {}

    
    
    virtual std::string GetAppID(content::WebContents* tab) = 0;

    
    
    
    
    virtual bool IsValidIDForCurrentUser(const std::string& id) = 0;

    
    virtual void SetCurrentUser(Profile* profile) = 0;
  };

  ChromeLauncherController(Profile* profile, ash::ShelfModel* model);
  virtual ~ChromeLauncherController();

  
  void Init();

  
  static ChromeLauncherController* CreateInstance(Profile* profile,
                                                  ash::ShelfModel* model);

  
  static ChromeLauncherController* instance() { return instance_; }

  
  ash::ShelfID CreateAppLauncherItem(LauncherItemController* controller,
                                     const std::string& app_id,
                                     ash::ShelfItemStatus status);

  
  
  void SetItemStatus(ash::ShelfID id, ash::ShelfItemStatus status);

  
  
  void SetItemController(ash::ShelfID id, LauncherItemController* controller);

  
  void CloseLauncherItem(ash::ShelfID id);

  
  void Pin(ash::ShelfID id);

  
  void Unpin(ash::ShelfID id);

  
  bool IsPinned(ash::ShelfID id);

  
  void TogglePinned(ash::ShelfID id);

  
  
  bool IsPinnable(ash::ShelfID id) const;

  
  
  void Install(ash::ShelfID id);

  
  
  bool CanInstall(ash::ShelfID id);

  
  
  
  void LockV1AppWithID(const std::string& app_id);

  
  
  void UnlockV1AppWithID(const std::string& app_id);

  
  
  
  void Launch(ash::ShelfID id, int event_flags);

  
  void Close(ash::ShelfID id);

  
  bool IsOpen(ash::ShelfID id);

  
  bool IsPlatformApp(ash::ShelfID id);

  
  
  void LaunchApp(const std::string& app_id,
                 ash::LaunchSource source,
                 int event_flags);

  
  
  
  void ActivateApp(const std::string& app_id,
                   ash::LaunchSource source,
                   int event_flags);

  
  extensions::LaunchType GetLaunchType(ash::ShelfID id);

  
  void SetLauncherItemImage(ash::ShelfID shelf_id, const gfx::ImageSkia& image);

  
  
  bool IsWindowedAppInLauncher(const std::string& app_id);

  
  void SetLaunchType(ash::ShelfID id, extensions::LaunchType launch_type);

  
  
  virtual bool IsLoggedInAsGuest();

  
  
  void CreateNewWindow();

  
  
  void CreateNewIncognitoWindow();

  
  
  
  void PersistPinnedState();

  ash::ShelfModel* model();

  
  
  Profile* profile();

  
  ash::ShelfAutoHideBehavior GetShelfAutoHideBehavior(
      aura::Window* root_window) const;

  
  
  bool CanUserModifyShelfAutoHideBehavior(aura::Window* root_window) const;

  
  
  void ToggleShelfAutoHideBehavior(aura::Window* root_window);

  
  
  void UpdateAppState(content::WebContents* contents, AppState app_state);

  
  
  ash::ShelfID GetShelfIDForWebContents(content::WebContents* contents);

  
  void SetRefocusURLPatternForTest(ash::ShelfID id, const GURL& url);

  
  const extensions::Extension* GetExtensionForAppID(
      const std::string& app_id) const;

  
  
  void ActivateWindowOrMinimizeIfActive(ui::BaseWindow* window,
                                        bool allow_minimize);

  
  virtual void OnShelfCreated(ash::Shelf* shelf) OVERRIDE;
  virtual void OnShelfDestroyed(ash::Shelf* shelf) OVERRIDE;
  virtual ash::ShelfID GetShelfIDForAppID(const std::string& app_id) OVERRIDE;
  virtual const std::string& GetAppIDForShelfID(ash::ShelfID id) OVERRIDE;
  virtual void PinAppWithID(const std::string& app_id) OVERRIDE;
  virtual bool IsAppPinned(const std::string& app_id) OVERRIDE;
  virtual bool CanPin() const OVERRIDE;
  virtual void UnpinAppWithID(const std::string& app_id) OVERRIDE;

  
  virtual void ShelfItemAdded(int index) OVERRIDE;
  virtual void ShelfItemRemoved(int index, ash::ShelfID id) OVERRIDE;
  virtual void ShelfItemMoved(int start_index, int target_index) OVERRIDE;
  virtual void ShelfItemChanged(int index,
                                const ash::ShelfItem& old_item) OVERRIDE;
  virtual void ShelfStatusChanged() OVERRIDE;

  
  virtual void OnShelfAlignmentChanged(aura::Window* root_window) OVERRIDE;

  
  virtual void OnDisplayConfigurationChanged() OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  virtual void OnIsSyncingChanged() OVERRIDE;

  
  virtual void OnAppSyncUIStatusChanged() OVERRIDE;

  
  virtual void ExtensionEnableFlowFinished() OVERRIDE;
  virtual void ExtensionEnableFlowAborted(bool user_initiated) OVERRIDE;

  
  virtual void SetAppImage(const std::string& app_id,
                           const gfx::ImageSkia& image) OVERRIDE;

  
  virtual void OnAutoHideBehaviorChanged(
      aura::Window* root_window,
      ash::ShelfAutoHideBehavior new_behavior) OVERRIDE;

  
  void ActiveUserChanged(const std::string& user_email);

  
  void AdditionalUserAddedToSession(Profile* profile);

  
  
  
  ChromeLauncherAppMenuItems GetApplicationList(const ash::ShelfItem& item,
                                                int event_flags);

  
  std::vector<content::WebContents*> GetV1ApplicationsFromAppId(
      std::string app_id);

  
  void ActivateShellApp(const std::string& app_id, int index);

  
  
  bool IsWebContentHandledByApplication(content::WebContents* web_contents,
                                        const std::string& app_id);

  
  
  bool ContentCanBeHandledByGmailApp(content::WebContents* web_contents);

  
  
  
  gfx::Image GetAppListIcon(content::WebContents* web_contents) const;

  
  
  base::string16 GetAppListTitle(content::WebContents* web_contents) const;

  
  BrowserShortcutLauncherItemController*
      GetBrowserShortcutLauncherItemController();

  LauncherItemController* GetLauncherItemController(const ash::ShelfID id);

  
  bool IsBrowserFromActiveUser(Browser* browser);

  
  
  
  
  bool ShelfBoundsChangesProbablyWithUser(aura::Window* root_window,
                                          const std::string& user_id) const;

  
  BrowserStatusMonitor* browser_status_monitor_for_test() {
    return browser_status_monitor_.get();
  }

  
  AppWindowLauncherController* app_window_controller_for_test() {
    return app_window_controller_.get();
  }

 protected:
  
  
  ash::ShelfID CreateAppShortcutLauncherItem(const std::string& app_id,
                                             int index);

  
  
  void SetAppTabHelperForTest(AppTabHelper* helper);
  void SetAppIconLoaderForTest(extensions::AppIconLoader* loader);
  const std::string& GetAppIdFromShelfIdForTest(ash::ShelfID id);

  
  
  void SetShelfItemDelegateManagerForTest(
      ash::ShelfItemDelegateManager* manager);

 private:
  friend class ChromeLauncherControllerTest;
  friend class ShelfAppBrowserTest;
  friend class LauncherPlatformAppBrowserTest;

  typedef std::map<ash::ShelfID, LauncherItemController*> IDToItemControllerMap;
  typedef std::map<content::WebContents*, std::string> WebContentsToAppIDMap;

  
  
  
  void RememberUnpinnedRunningApplicationOrder();
  void RestoreUnpinnedRunningApplicationOrder(const std::string& user_id);

  
  
  ash::ShelfID CreateAppShortcutLauncherItemWithType(
      const std::string& app_id,
      int index,
      ash::ShelfItemType shelf_item_type);

  
  void LauncherItemClosed(ash::ShelfID id);

  
  
  void DoPinAppWithID(const std::string& app_id);
  void DoUnpinAppWithID(const std::string& app_id);

  
  
  int PinRunningAppInternal(int index, ash::ShelfID shelf_id);

  
  
  
  void UnpinRunningAppInternal(int index);

  
  void UpdateAppLaunchersFromPref();

  
  void SetShelfAutoHideBehaviorPrefs(ash::ShelfAutoHideBehavior behavior,
                                     aura::Window* root_window);

  
  void SetShelfAutoHideBehaviorFromPrefs();

  
  void SetShelfAlignmentFromPrefs();

  
  void SetShelfBehaviorsFromPrefs();

#if defined(OS_CHROMEOS)
  
  void SetVirtualKeyboardBehaviorFromPrefs();
#endif  

  
  
  
  ash::ShelfItemStatus GetAppState(const std::string& app_id);

  
  
  
  ash::ShelfID InsertAppLauncherItem(LauncherItemController* controller,
                                        const std::string& app_id,
                                        ash::ShelfItemStatus status,
                                        int index,
                                        ash::ShelfItemType shelf_item_type);

  bool HasItemController(ash::ShelfID id) const;

  
  std::vector<content::WebContents*> GetV1ApplicationsFromController(
      LauncherItemController* controller);

  
  ash::ShelfID CreateBrowserShortcutLauncherItem();

  
  bool IsIncognito(const content::WebContents* web_contents) const;

  
  void PersistChromeItemIndex(int index);

  
  int GetChromeIconIndexFromPref() const;

  
  
  
  
  
  void MoveChromeOrApplistToFinalPosition(
      bool is_chrome,
      bool is_app_list,
      int target_index,
      int* chrome_index,
      int* app_list_index);

  
  int FindInsertionPoint(bool is_app_list);

  
  
  int GetChromeIconIndexForCreation();

  
  std::vector<std::string> GetListOfPinnedAppsAndBrowser();

  
  
  void CloseWindowedAppsFromRemovedExtension(const std::string& app_id,
                                             const Profile* profile);

  
  
  void SetShelfItemDelegate(ash::ShelfID id,
                            ash::ShelfItemDelegate* item_delegate);

  
  void AttachProfile(Profile* proifile);

  
  void ReleaseProfile();

  
  
  
  bool LaunchedInNativeDesktop(const std::string& app_id);

  static ChromeLauncherController* instance_;

  ash::ShelfModel* model_;

  ash::ShelfItemDelegateManager* item_delegate_manager_;

  
  
  Profile* profile_;

  IDToItemControllerMap id_to_item_controller_map_;

  
  WebContentsToAppIDMap web_contents_to_app_id_;

  
  scoped_ptr<AppWindowLauncherController> app_window_controller_;

  
  scoped_ptr<AppTabHelper> app_tab_helper_;

  
  scoped_ptr<extensions::AppIconLoader> app_icon_loader_;

  PrefChangeRegistrar pref_change_registrar_;

  AppSyncUIState* app_sync_ui_state_;

  scoped_ptr<ExtensionEnableFlow> extension_enable_flow_;

  
  std::set<ash::Shelf*> shelves_;

  
  scoped_ptr<BrowserStatusMonitor> browser_status_monitor_;

  
  scoped_ptr<ChromeLauncherControllerUserSwitchObserver> user_switch_observer_;

  
  bool ignore_persist_pinned_state_change_;

  
  bool multi_profile_desktop_separation_;

  
  
  typedef std::vector<std::string> RunningAppListIds;
  typedef std::map<std::string, RunningAppListIds> RunningAppListIdMap;
  RunningAppListIdMap last_used_running_application_order_;

  DISALLOW_COPY_AND_ASSIGN(ChromeLauncherController);
};

#endif  
