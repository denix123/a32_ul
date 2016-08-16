// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_PROFILES_PROFILE_MANAGER_H_
#define CHROME_BROWSER_PROFILES_PROFILE_MANAGER_H_

#include <list>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_shortcut_manager.h"
#include "chrome/browser/ui/browser_list_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class NewProfileLauncher;
class ProfileInfoCache;

class ProfileManager : public base::NonThreadSafe,
                       public content::NotificationObserver,
                       public Profile::Delegate {
 public:
  typedef base::Callback<void(Profile*, Profile::CreateStatus)> CreateCallback;

  explicit ProfileManager(const base::FilePath& user_data_dir);
  virtual ~ProfileManager();

#if defined(ENABLE_SESSION_SERVICE)
  
  static void ShutdownSessionServices();
#endif

  
  static void NukeDeletedProfilesFromDisk();

  
  
  
  static Profile* GetLastUsedProfile();

  
  
  
  static Profile* GetLastUsedProfileAllowedByPolicy();

  
  static std::vector<Profile*> GetLastOpenedProfiles();

  
  
  
  
  
  static Profile* GetPrimaryUserProfile();

  
  
  
  
  
  static Profile* GetActiveUserProfile();

  
  
  
  Profile* GetProfile(const base::FilePath& profile_dir);

  
  size_t GetNumberOfProfiles();

  
  
  
  void CreateProfileAsync(const base::FilePath& profile_path,
                          const CreateCallback& callback,
                          const base::string16& name,
                          const base::string16& icon_url,
                          const std::string& supervised_user_id);

  
  
  bool IsValidProfile(Profile* profile);

  
  
  base::FilePath GetInitialProfileDir();

  
  
  
  Profile* GetLastUsedProfile(const base::FilePath& user_data_dir);

  
  
  base::FilePath GetLastUsedProfileDir(const base::FilePath& user_data_dir);

  
  
  
  
  
  std::vector<Profile*> GetLastOpenedProfiles(
      const base::FilePath& user_data_dir);

  
  
  std::vector<Profile*> GetLoadedProfiles() const;

  
  
  
  Profile* GetProfileByPath(const base::FilePath& path) const;

  
  
  
  
  
  
  
  
  static base::FilePath CreateMultiProfileAsync(
      const base::string16& name,
      const base::string16& icon_url,
      const CreateCallback& callback,
      const std::string& supervised_user_id);

  
  static base::FilePath GetGuestProfilePath();

  
  
  
  
  
  base::FilePath GenerateNextProfileDirectoryPath();

  
  
  ProfileInfoCache& GetProfileInfoCache();

  
  
  ProfileShortcutManager* profile_shortcut_manager();

  
  
  
  void ScheduleProfileForDeletion(const base::FilePath& profile_dir,
                                  const CreateCallback& callback);

  
  
  
  static void CleanUpStaleProfiles(
      const std::vector<base::FilePath>& profile_paths);

  
  void AutoloadProfiles();

  
  
  void InitProfileUserPrefs(Profile* profile);

  
  
  
  
  
  void RegisterTestingProfile(Profile* profile,
                              bool addToCache,
                              bool start_deferred_task_runners);

  const base::FilePath& user_data_dir() const { return user_data_dir_; }

  
  bool IsLoggedIn() const { return logged_in_; }

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnProfileCreated(Profile* profile,
                                bool success,
                                bool is_new_profile) OVERRIDE;

 protected:
  
  virtual void DoFinalInit(Profile* profile, bool go_off_the_record);
  virtual void DoFinalInitForServices(Profile* profile, bool go_off_the_record);
  virtual void DoFinalInitLogging(Profile* profile);

  
  
  
  virtual Profile* CreateProfileHelper(const base::FilePath& path);

  
  
  
  virtual Profile* CreateProfileAsyncHelper(const base::FilePath& path,
                                            Delegate* delegate);

 private:
  friend class TestingProfileManager;
  FRIEND_TEST_ALL_PREFIXES(ProfileManagerBrowserTest, DeleteAllProfiles);
  FRIEND_TEST_ALL_PREFIXES(ProfileManagerBrowserTest, SwitchToProfile);

  
  
  struct ProfileInfo {
    ProfileInfo(Profile* profile, bool created);

    ~ProfileInfo();

    scoped_ptr<Profile> profile;
    
    bool created;
    
    bool create_shortcut;
    
    
    std::vector<CreateCallback> callbacks;

   private:
    DISALLOW_COPY_AND_ASSIGN(ProfileInfo);
  };

  
  
  
  
  
  Profile* GetActiveUserOrOffTheRecordProfileFromPath(
               const base::FilePath& user_data_dir);

  
  
  
  
  bool AddProfile(Profile* profile);

  
  void FinishDeletingProfile(const base::FilePath& profile_dir);

  
  
  ProfileInfo* RegisterProfile(Profile* profile, bool created);

  
  
  ProfileInfo* GetProfileInfoByPath(const base::FilePath& path) const;

  
  void AddProfileToCache(Profile* profile);

  
  void SetGuestProfilePrefs(Profile* profile);

  
  bool ShouldGoOffTheRecord(Profile* profile);

  void RunCallbacks(const std::vector<CreateCallback>& callbacks,
                    Profile* profile,
                    Profile::CreateStatus status);

#if !defined(OS_ANDROID) && !defined(OS_IOS)
  
  
  
  
  void UpdateLastUser(Profile* last_active);

  class BrowserListObserver : public chrome::BrowserListObserver {
   public:
    explicit BrowserListObserver(ProfileManager* manager);
    virtual ~BrowserListObserver();

    
    virtual void OnBrowserAdded(Browser* browser) OVERRIDE;
    virtual void OnBrowserRemoved(Browser* browser) OVERRIDE;
    virtual void OnBrowserSetLastActive(Browser* browser) OVERRIDE;

   private:
    ProfileManager* profile_manager_;
    DISALLOW_COPY_AND_ASSIGN(BrowserListObserver);
  };
#endif  

#if defined(OS_MACOSX)
  
  
  
  
  
  void OnNewActiveProfileLoaded(
      const base::FilePath& profile_to_delete_path,
      const base::FilePath& last_non_supervised_profile_path,
      const CreateCallback& original_callback,
      Profile* loaded_profile,
      Profile::CreateStatus status);
#endif

  content::NotificationRegistrar registrar_;

  
  const base::FilePath user_data_dir_;

  
  
  
  bool logged_in_;

#if !defined(OS_ANDROID) && !defined(OS_IOS)
  BrowserListObserver browser_list_observer_;
#endif  

  
  
  
  typedef std::map<base::FilePath, linked_ptr<ProfileInfo> > ProfilesInfoMap;
  ProfilesInfoMap profiles_info_;

  
  
  
  scoped_ptr<ProfileInfoCache> profile_info_cache_;

  
  scoped_ptr<ProfileShortcutManager> profile_shortcut_manager_;

  
  std::map<Profile*, int> browser_counts_;
  
  
  std::vector<Profile*> active_profiles_;
  bool closing_all_browsers_;

  DISALLOW_COPY_AND_ASSIGN(ProfileManager);
};

class ProfileManagerWithoutInit : public ProfileManager {
 public:
  explicit ProfileManagerWithoutInit(const base::FilePath& user_data_dir);

 protected:
  virtual void DoFinalInitForServices(Profile*, bool) OVERRIDE {}
  virtual void DoFinalInitLogging(Profile*) OVERRIDE {}
};

#endif  
