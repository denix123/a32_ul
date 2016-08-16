// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_H_
#define COMPONENTS_USER_MANAGER_USER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "components/user_manager/user_image/user_image.h"
#include "components/user_manager/user_info.h"
#include "components/user_manager/user_manager_export.h"
#include "components/user_manager/user_type.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/image/image_skia.h"

namespace chromeos {
class ChromeUserManagerImpl;
class FakeLoginUtils;
class FakeUserManager;
class MockUserManager;
class SupervisedUserManagerImpl;
class UserAddingScreenTest;
class UserImageManagerImpl;
class UserSessionManager;
}

namespace user_manager {

class UserManagerBase;

class USER_MANAGER_EXPORT User : public UserInfo {
 public:
  
  
  
  typedef enum {
    OAUTH_TOKEN_STATUS_UNKNOWN = 0,
    OAUTH2_TOKEN_STATUS_INVALID = 3,
    OAUTH2_TOKEN_STATUS_VALID = 4,
  } OAuthTokenStatus;

  
  typedef enum {
    USER_IMAGE_INVALID = -3,

    
    USER_IMAGE_PROFILE = -2,

    
    
    USER_IMAGE_EXTERNAL = -1,
  } UserImageType;

  
  
  
  
  enum WallpaperType {
        
    CUSTOMIZED = 1,    
    DEFAULT = 2,       
      
    ONLINE = 4,        
    POLICY = 5,        
    WALLPAPER_TYPE_COUNT = 6
  };

  
  virtual UserType GetType() const = 0;

  
  const std::string& email() const { return email_; }

  
  base::string16 display_name() const { return display_name_; }

  
  virtual std::string GetEmail() const OVERRIDE;
  virtual base::string16 GetDisplayName() const OVERRIDE;
  virtual base::string16 GetGivenName() const OVERRIDE;
  virtual const gfx::ImageSkia& GetImage() const OVERRIDE;
  virtual std::string GetUserID() const OVERRIDE;

  
  virtual bool IsSupervised() const;
  virtual void SetIsSupervised(bool is_supervised);

  
  
  std::string GetAccountName(bool use_display_email) const;

  
  bool HasDefaultImage() const;

  
  virtual bool CanSyncImage() const;

  int image_index() const { return image_index_; }
  bool has_raw_image() const { return user_image_.has_raw_image(); }
  
  const UserImage::RawImage& raw_image() const {
    return user_image_.raw_image();
  }

  
  
  bool image_is_safe_format() const { return user_image_.is_safe_format(); }

  
  
  GURL image_url() const { return user_image_.url(); }

  
  bool image_is_stub() const { return image_is_stub_; }

  
  bool image_is_loading() const { return image_is_loading_; }

  
  virtual std::string display_email() const;

  
  OAuthTokenStatus oauth_token_status() const { return oauth_token_status_; }

  
  
  bool force_online_signin() const { return force_online_signin_; }

  
  
  bool can_lock() const;

  
  std::string username_hash() const;

  
  bool is_logged_in() const;

  
  bool is_active() const;

  
  bool is_profile_created() const { return profile_is_created_; }

 protected:
  friend class UserManagerBase;
  friend class chromeos::ChromeUserManagerImpl;
  friend class chromeos::SupervisedUserManagerImpl;
  friend class chromeos::UserImageManagerImpl;
  friend class chromeos::UserSessionManager;

  
  friend class chromeos::MockUserManager;
  friend class chromeos::FakeLoginUtils;
  friend class chromeos::FakeUserManager;
  friend class chromeos::UserAddingScreenTest;

  
  static User* CreateRegularUser(const std::string& email);
  static User* CreateGuestUser();
  static User* CreateKioskAppUser(const std::string& kiosk_app_username);
  static User* CreateSupervisedUser(const std::string& username);
  static User* CreateRetailModeUser();
  static User* CreatePublicAccountUser(const std::string& email);

  explicit User(const std::string& email);
  virtual ~User();

  const std::string* GetAccountLocale() const { return account_locale_.get(); }

  
  void SetAccountLocale(const std::string& resolved_account_locale);

  void SetImage(const UserImage& user_image, int image_index);

  void SetImageURL(const GURL& image_url);

  
  
  
  void SetStubImage(const UserImage& stub_user_image,
                    int image_index,
                    bool is_loading);

  void set_display_name(const base::string16& display_name) {
    display_name_ = display_name;
  }

  void set_given_name(const base::string16& given_name) {
    given_name_ = given_name;
  }

  void set_display_email(const std::string& display_email) {
    display_email_ = display_email;
  }

  const UserImage& user_image() const { return user_image_; }

  void set_oauth_token_status(OAuthTokenStatus status) {
    oauth_token_status_ = status;
  }

  void set_force_online_signin(bool force_online_signin) {
    force_online_signin_ = force_online_signin;
  }

  void set_username_hash(const std::string& username_hash) {
    username_hash_ = username_hash;
  }

  void set_is_logged_in(bool is_logged_in) { is_logged_in_ = is_logged_in; }

  void set_can_lock(bool can_lock) { can_lock_ = can_lock; }

  void set_is_active(bool is_active) { is_active_ = is_active; }

  void set_profile_is_created() { profile_is_created_ = true; }

  
  bool has_gaia_account() const;

 private:
  std::string email_;
  base::string16 display_name_;
  base::string16 given_name_;
  
  std::string display_email_;
  UserImage user_image_;
  OAuthTokenStatus oauth_token_status_;
  bool force_online_signin_;

  
  
  
  
  scoped_ptr<std::string> account_locale_;

  
  std::string username_hash_;

  
  
  int image_index_;

  
  bool image_is_stub_;

  
  bool image_is_loading_;

  
  bool can_lock_;

  
  bool is_logged_in_;

  
  bool is_active_;

  
  bool profile_is_created_;

  DISALLOW_COPY_AND_ASSIGN(User);
};

typedef std::vector<User*> UserList;

}  

#endif  
