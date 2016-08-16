// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SERVICE_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SERVICE_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "base/strings/string16.h"
#include "chrome/browser/supervised_user/experimental/supervised_user_blacklist.h"
#include "chrome/browser/supervised_user/supervised_user_url_filter.h"
#include "chrome/browser/supervised_user/supervised_users.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "chrome/browser/sync/sync_type_preference_provider.h"
#include "chrome/browser/ui/browser_list_observer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/web_contents.h"

#if defined(ENABLE_EXTENSIONS)
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/management_policy.h"
#endif

class Browser;
class GoogleServiceAuthError;
class PermissionRequestCreator;
class Profile;
class SupervisedUserBlacklistDownloader;
class SupervisedUserRegistrationUtility;
class SupervisedUserServiceObserver;
class SupervisedUserSettingsService;
class SupervisedUserSiteList;
class SupervisedUserURLFilter;

namespace base {
class FilePath;
}

namespace extensions {
class ExtensionRegistry;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class SupervisedUserService : public KeyedService,
#if defined(ENABLE_EXTENSIONS)
                              public extensions::ManagementPolicy::Provider,
                              public extensions::ExtensionRegistryObserver,
#endif
                              public SyncTypePreferenceProvider,
                              public ProfileSyncServiceObserver,
                              public chrome::BrowserListObserver {
 public:
  typedef std::vector<base::string16> CategoryList;
  typedef base::Callback<void(content::WebContents*)> NavigationBlockedCallback;
  typedef base::Callback<void(const GoogleServiceAuthError&)> AuthErrorCallback;

  enum ManualBehavior {
    MANUAL_NONE = 0,
    MANUAL_ALLOW,
    MANUAL_BLOCK
  };

  class Delegate {
   public:
    virtual ~Delegate() {}
    
    
    virtual bool SetActive(bool active) = 0;
    
    
    virtual base::FilePath GetBlacklistPath() const = 0;
    
    
    virtual GURL GetBlacklistURL() const = 0;
  };

  virtual ~SupervisedUserService();

  
  virtual void Shutdown() OVERRIDE;

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  void SetDelegate(Delegate* delegate);

  
  
  scoped_refptr<const SupervisedUserURLFilter> GetURLFilterForIOThread();

  
  
  SupervisedUserURLFilter* GetURLFilterForUIThread();

  
  int GetCategory(const GURL& url);

  
  
  
  void GetCategoryNames(CategoryList* list);

  
  bool AccessRequestsEnabled();

  void OnPermissionRequestIssued();

  
  
  
  void AddAccessRequest(const GURL& url);

  
  std::string GetCustodianEmailAddress() const;

  
  
  std::string GetCustodianName() const;

  
  
  

  
  ManualBehavior GetManualBehaviorForHost(const std::string& hostname);

  
  ManualBehavior GetManualBehaviorForURL(const GURL& url);

  
  void GetManualExceptionsForHost(const std::string& host,
                                  std::vector<GURL>* urls);

  
  
  void Init();

  
  
  void InitSync(const std::string& refresh_token);

  
  
  
  
  
  void RegisterAndInitSync(
      SupervisedUserRegistrationUtility* registration_utility,
      Profile* custodian_profile,
      const std::string& supervised_user_id,
      const AuthErrorCallback& callback);

  void set_elevated_for_testing(bool skip) {
    elevated_for_testing_ = skip;
  }

  void AddNavigationBlockedCallback(const NavigationBlockedCallback& callback);
  void DidBlockNavigation(content::WebContents* web_contents);

  void AddObserver(SupervisedUserServiceObserver* observer);
  void RemoveObserver(SupervisedUserServiceObserver* observer);

#if defined(ENABLE_EXTENSIONS)
  
  virtual std::string GetDebugPolicyProviderName() const OVERRIDE;
  virtual bool UserMayLoad(const extensions::Extension* extension,
                           base::string16* error) const OVERRIDE;
  virtual bool UserMayModifySettings(const extensions::Extension* extension,
                                     base::string16* error) const OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;
#endif

  
  virtual syncer::ModelTypeSet GetPreferredDataTypes() const OVERRIDE;

  
  virtual void OnStateChanged() OVERRIDE;

  
  virtual void OnBrowserSetLastActive(Browser* browser) OVERRIDE;

 private:
  friend class SupervisedUserServiceExtensionTestBase;
  friend class SupervisedUserServiceFactory;
  FRIEND_TEST_ALL_PREFIXES(SupervisedUserServiceTest, ClearOmitOnRegistration);

  
  
  
  class URLFilterContext {
   public:
    URLFilterContext();
    ~URLFilterContext();

    SupervisedUserURLFilter* ui_url_filter() const;
    SupervisedUserURLFilter* io_url_filter() const;

    void SetDefaultFilteringBehavior(
        SupervisedUserURLFilter::FilteringBehavior behavior);
    void LoadWhitelists(ScopedVector<SupervisedUserSiteList> site_lists);
    void LoadBlacklist(const base::FilePath& path);
    void SetManualHosts(scoped_ptr<std::map<std::string, bool> > host_map);
    void SetManualURLs(scoped_ptr<std::map<GURL, bool> > url_map);

   private:
    void OnBlacklistLoaded();

    
    
    
    
    
    
    scoped_refptr<SupervisedUserURLFilter> ui_url_filter_;
    scoped_refptr<SupervisedUserURLFilter> io_url_filter_;

    SupervisedUserBlacklist blacklist_;

    DISALLOW_COPY_AND_ASSIGN(URLFilterContext);
  };

  
  
  explicit SupervisedUserService(Profile* profile);

  void SetActive(bool active);

  void OnCustodianProfileDownloaded(const base::string16& full_name);

  void OnSupervisedUserRegistered(const AuthErrorCallback& callback,
                                  Profile* custodian_profile,
                                  const GoogleServiceAuthError& auth_error,
                                  const std::string& token);

  void SetupSync();
  void StartSetupSync();
  void FinishSetupSyncWhenReady();
  void FinishSetupSync();

  bool ProfileIsSupervised() const;

  void OnCustodianInfoChanged();

#if defined(ENABLE_EXTENSIONS)
  
  
  
  bool ExtensionManagementPolicyImpl(const extensions::Extension* extension,
                                     base::string16* error) const;

  
  
  ScopedVector<SupervisedUserSiteList> GetActiveSiteLists();

  
  void SetExtensionsActive();
#endif

  SupervisedUserSettingsService* GetSettingsService();

  void OnSupervisedUserIdChanged();

  void OnDefaultFilteringBehaviorChanged();

  void UpdateSiteLists();

  
  
  
  void LoadBlacklist(const base::FilePath& path, const GURL& url);

  
  
  void LoadBlacklistFromFile(const base::FilePath& path);

  void OnBlacklistDownloadDone(const base::FilePath& path, bool success);

  
  
  void UpdateManualHosts();

  
  
  void UpdateManualURLs();

  
  std::string GetSupervisedUserName() const;

  
  Profile* profile_;

  bool active_;

  Delegate* delegate_;

#if defined(ENABLE_EXTENSIONS)
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;
#endif

  PrefChangeRegistrar pref_change_registrar_;

  
  bool waiting_for_sync_initialization_;
  bool is_profile_active_;

  std::vector<NavigationBlockedCallback> navigation_blocked_callbacks_;

  
  bool elevated_for_testing_;

  
  bool did_init_;

  
  bool did_shutdown_;

  URLFilterContext url_filter_context_;
  scoped_ptr<SupervisedUserBlacklistDownloader> blacklist_downloader_;

  
  scoped_ptr<PermissionRequestCreator> permissions_creator_;

  ObserverList<SupervisedUserServiceObserver> observer_list_;

  base::WeakPtrFactory<SupervisedUserService> weak_ptr_factory_;
};

#endif  
