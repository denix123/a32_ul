// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PROFILES_NEW_AVATAR_BUTTON_H_
#define CHROME_BROWSER_UI_VIEWS_PROFILES_NEW_AVATAR_BUTTON_H_

#include "chrome/browser/profiles/profile_info_cache_observer.h"
#include "components/signin/core/browser/signin_error_controller.h"
#include "ui/views/controls/button/label_button.h"

class Browser;

class NewAvatarButton : public views::LabelButton,
                        public ProfileInfoCacheObserver,
                        public SigninErrorController::Observer {
 public:
  
  enum AvatarButtonStyle {
    THEMED_BUTTON,   
    NATIVE_BUTTON,    
  };

  NewAvatarButton(views::ButtonListener* listener,
                  AvatarButtonStyle button_style,
                  Browser* browser);
  virtual ~NewAvatarButton();

  
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;

 private:
  friend class NewAvatarMenuButtonTest;
  friend class ProfileChooserViewBrowserTest;
  FRIEND_TEST_ALL_PREFIXES(NewAvatarMenuButtonTest, SignOut);
  FRIEND_TEST_ALL_PREFIXES(ProfileChooserViewBrowserTest, ViewProfileUMA);

  
  virtual void OnProfileAdded(const base::FilePath& profile_path) OVERRIDE;
  virtual void OnProfileWasRemoved(
      const base::FilePath& profile_path,
      const base::string16& profile_name) OVERRIDE;
  virtual void OnProfileNameChanged(
      const base::FilePath& profile_path,
      const base::string16& old_profile_name) OVERRIDE;
  virtual void OnProfileAvatarChanged(
      const base::FilePath& profile_path) OVERRIDE;
  virtual void OnProfileSupervisedUserIdChanged(
      const base::FilePath& profile_path) OVERRIDE;

  
  virtual void OnErrorChanged() OVERRIDE;

  
  
  void UpdateAvatarButtonAndRelayoutParent();

  Browser* browser_;

  
  
  bool has_auth_error_;

  
  
  gfx::ImageSkia generic_avatar_;

  
  
  
  bool suppress_mouse_released_action_;

  DISALLOW_COPY_AND_ASSIGN(NewAvatarButton);
};

#endif  
