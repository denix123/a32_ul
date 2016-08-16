// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_AVATAR_MENU_H_
#define CHROME_BROWSER_PROFILES_AVATAR_MENU_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/scoped_observer.h"
#include "base/strings/string16.h"
#include "chrome/browser/profiles/profile_metrics.h"
#include "chrome/browser/ui/host_desktop.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "ui/gfx/image/image.h"

#if defined(ENABLE_MANAGED_USERS)
#include "chrome/browser/supervised_user/supervised_user_service_observer.h"
#endif

class AvatarMenuActions;
class AvatarMenuObserver;
class Browser;
class Profile;
class ProfileInfoInterface;
class ProfileList;
class SupervisedUserService;

class AvatarMenu :
#if defined(ENABLE_MANAGED_USERS)
    public SupervisedUserServiceObserver,
#endif
    public content::NotificationObserver {
 public:
  
  struct Item {
    Item(size_t menu_index, size_t profile_index, const gfx::Image& icon);
    ~Item();

    
    gfx::Image icon;

    
    bool active;

    
    base::string16 name;

    
    base::string16 sync_state;

    
    
    bool signed_in;

    
    bool signin_required;

    
    
    bool supervised;

    
    
    size_t menu_index;

    
    size_t profile_index;

    
    base::FilePath profile_path;
  };

  
  
  AvatarMenu(ProfileInfoInterface* profile_cache,
             AvatarMenuObserver* observer,
             Browser* browser);
  virtual ~AvatarMenu();

  
  static bool ShouldShowAvatarMenu();

  
  
  static void GetImageForMenuButton(Profile* profile,
                                    gfx::Image* image,
                                    bool* is_rectangle);

  
  static bool CompareItems(const Item* item1, const Item* item2);

  
  
  
  void SwitchToProfile(size_t index,
                       bool always_create,
                       ProfileMetrics::ProfileOpen metric);

  
  void AddNewProfile(ProfileMetrics::ProfileAdd type);

  
  
  void EditProfile(size_t index);

  
  void RebuildMenu();

  
  size_t GetNumberOfItems() const;

  
  const Item& GetItemAt(size_t index) const;

  
  size_t GetActiveProfileIndex();

  
  
  
  base::string16 GetSupervisedUserInformation() const;

  
  
  const gfx::Image& GetSupervisedUserIcon() const;

  
  
  void ActiveBrowserChanged(Browser* browser);

  
  bool ShouldShowAddNewProfileLink() const;

  
  bool ShouldShowEditProfileLink() const;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
#if defined(ENABLE_MANAGED_USERS)
  
  virtual void OnCustodianInfoChanged() OVERRIDE;
#endif

  
  scoped_ptr<ProfileList> profile_list_;

  
  scoped_ptr<AvatarMenuActions> menu_actions_;

#if defined(ENABLE_MANAGED_USERS)
  
  ScopedObserver<SupervisedUserService, SupervisedUserServiceObserver>
      supervised_user_observer_;
#endif

  
  ProfileInfoInterface* profile_info_;

  
  AvatarMenuObserver* observer_;

  
  Browser* browser_;

  
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(AvatarMenu);
};

#endif  
