// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_METRICS_H_
#define CHROME_BROWSER_PROFILES_PROFILE_METRICS_H_

#include <stddef.h>
#include <string>

#include "base/basictypes.h"
#include "chrome/browser/signin/signin_header_helper.h"

class Profile;
class ProfileManager;

namespace base {
class FilePath;
}

class ProfileMetrics {
 public:
  struct ProfileCounts {
    size_t total;
    size_t signedin;
    size_t supervised;
    size_t unused;
    size_t gaia_icon;

    ProfileCounts()
        : total(0), signedin(0), supervised(0), unused(0), gaia_icon(0) {}
  };

  
  enum ProfileAdd {
    ADD_NEW_USER_ICON = 0,      
    ADD_NEW_USER_MENU,          
    ADD_NEW_USER_DIALOG,        
    ADD_NEW_USER_MANAGER,       
    ADD_NEW_USER_LAST_DELETED,  
    NUM_PROFILE_ADD_METRICS
  };

  enum ProfileDelete {
    DELETE_PROFILE_SETTINGS = 0,  
    DELETE_PROFILE_USER_MANAGER,  
    NUM_DELETE_PROFILE_METRICS
  };

  
  enum ProfileOpen {
    NTP_AVATAR_BUBBLE = 0,    
    ICON_AVATAR_BUBBLE,       
    SWITCH_PROFILE_ICON,      
    SWITCH_PROFILE_MENU,      
    SWITCH_PROFILE_DOCK,      
    OPEN_USER_MANAGER,        
    SWITCH_PROFILE_MANAGER,   
    SWITCH_PROFILE_UNLOCK,    
    SWITCH_PROFILE_GUEST,     
    NUM_PROFILE_OPEN_METRICS
  };

  
  enum ProfileNetUserCounts {
    ADD_NEW_USER = 0,         
    PROFILE_DELETED,          
    NUM_PROFILE_NET_METRICS
  };

  
  
  
  enum ProfileSync {
    SYNC_CUSTOMIZE = 0,       
    SYNC_CHOOSE,              
    SYNC_ENCRYPT,             
    SYNC_PASSPHRASE,          
    NUM_PROFILE_SYNC_METRICS
  };

  enum ProfileType {
    ORIGINAL = 0,             
    SECONDARY,                
    NUM_PROFILE_TYPE_METRICS
  };

  enum ProfileGaia {
    GAIA_OPT_IN = 0,          
    GAIA_OPT_OUT,             
    NUM_PROFILE_GAIA_METRICS
  };

  enum ProfileAuth {
    AUTH_UNNECESSARY,     
    AUTH_LOCAL,           
    AUTH_ONLINE,          
    AUTH_FAILED,          
    AUTH_FAILED_OFFLINE,  
    NUM_PROFILE_AUTH_METRICS
  };

  
  
  
  
  
  enum ProfileDesktopMenu {
    
    PROFILE_DESKTOP_MENU_LOCK = 0,
    
    PROFILE_DESKTOP_MENU_REMOVE_ACCT,
    
    PROFILE_DESKTOP_MENU_ADD_ACCT,
    
    PROFILE_DESKTOP_MENU_EDIT_NAME,
    
    PROFILE_DESKTOP_MENU_EDIT_IMAGE,
    
    PROFILE_DESKTOP_MENU_OPEN_USER_MANAGER,
    NUM_PROFILE_DESKTOP_MENU_METRICS,
  };

#if defined(OS_ANDROID)
  
  
  
  
  enum ProfileAndroidAccountManagementMenu {
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_VIEW = 0,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_ADD_ACCOUNT,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_GO_INCOGNITO,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_CLICK_PRIMARY_ACCOUNT,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_CLICK_SECONDARY_ACCOUNT,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_TOGGLE_SIGNOUT,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_SIGNOUT_SIGNOUT,
    
    PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_SIGNOUT_CANCEL,
    NUM_PROFILE_ANDROID_ACCOUNT_MANAGEMENT_MENU_METRICS,
  };
#endif  

  
  
  enum ProfileNewAvatarMenuNotYou {
    
    PROFILE_AVATAR_MENU_NOT_YOU_VIEW = 0,
    
    PROFILE_AVATAR_MENU_NOT_YOU_BACK,
    
    PROFILE_AVATAR_MENU_NOT_YOU_ADD_PERSON,
    
    PROFILE_AVATAR_MENU_NOT_YOU_DISCONNECT,
    NUM_PROFILE_AVATAR_MENU_NOT_YOU_METRICS,
  };

  
  
  enum ProfileNewAvatarMenuSignin {
    
    PROFILE_AVATAR_MENU_SIGNIN_VIEW = 0,
    
    PROFILE_AVATAR_MENU_SIGNIN_OK,
    
    PROFILE_AVATAR_MENU_SIGNIN_SETTINGS,
    NUM_PROFILE_AVATAR_MENU_SIGNIN_METRICS,
  };

  
  
  enum ProfileNewAvatarMenuUpgrade {
    
    PROFILE_AVATAR_MENU_UPGRADE_VIEW = 0,
    
    PROFILE_AVATAR_MENU_UPGRADE_DISMISS,
    
    PROFILE_AVATAR_MENU_UPGRADE_WHATS_NEW,
    
    PROFILE_AVATAR_MENU_UPGRADE_NOT_YOU,
    NUM_PROFILE_AVATAR_MENU_UPGRADE_METRICS,
  };

  static void UpdateReportedProfilesStatistics(ProfileManager* manager);
  
  
  static bool CountProfileInformation(ProfileManager* manager,
                                      ProfileCounts* counts);

  static void LogNumberOfProfiles(ProfileManager* manager);
  static void LogProfileAddNewUser(ProfileAdd metric);
  static void LogProfileAvatarSelection(size_t icon_index);
  static void LogProfileDeleteUser(ProfileDelete metric);
  static void LogProfileOpenMethod(ProfileOpen metric);
  static void LogProfileSwitchGaia(ProfileGaia metric);
  static void LogProfileSwitchUser(ProfileOpen metric);
  static void LogProfileSyncInfo(ProfileSync metric);
  static void LogProfileAuthResult(ProfileAuth metric);
  static void LogProfileDesktopMenu(ProfileDesktopMenu metric,
                                    signin::GAIAServiceType gaia_service);
  static void LogProfileDelete(bool profile_was_signed_in);
  static void LogProfileNewAvatarMenuNotYou(ProfileNewAvatarMenuNotYou metric);
  static void LogProfileNewAvatarMenuSignin(ProfileNewAvatarMenuSignin metric);
  static void LogProfileNewAvatarMenuUpgrade(
      ProfileNewAvatarMenuUpgrade metric);

#if defined(OS_ANDROID)
  static void LogProfileAndroidAccountManagementMenu(
      ProfileAndroidAccountManagementMenu metric,
      signin::GAIAServiceType gaia_service);
#endif  

  
  
  static void LogProfileLaunch(Profile* profile);
  static void LogProfileSyncSignIn(const base::FilePath& profile_path);
  static void LogProfileUpdate(const base::FilePath& profile_path);
};


#endif  
