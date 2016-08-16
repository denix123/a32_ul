// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_CHOOSER_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_CHOOSER_VIEW_H_

#include <map>
#include <vector>

#include "chrome/browser/profiles/avatar_menu.h"
#include "chrome/browser/profiles/avatar_menu_observer.h"
#include "chrome/browser/profiles/profile_metrics.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/profile_chooser_constants.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/link_listener.h"
#include "ui/views/controls/styled_label_listener.h"
#include "ui/views/controls/textfield/textfield_controller.h"

class EditableProfilePhoto;
class EditableProfileName;

namespace gfx {
class Image;
}

namespace views {
class GridLayout;
class ImageButton;
class Link;
class LabelButton;
}

class Browser;

class ProfileChooserView : public views::BubbleDelegateView,
                           public views::ButtonListener,
                           public views::LinkListener,
                           public views::StyledLabelListener,
                           public views::TextfieldController,
                           public AvatarMenuObserver,
                           public OAuth2TokenService::Observer {
 public:
  
  
  
  
  
  static void ShowBubble(
      profiles::BubbleViewMode view_mode,
      profiles::TutorialMode tutorial_mode,
      const signin::ManageAccountsParams& manage_accounts_params,
      views::View* anchor_view,
      views::BubbleBorder::Arrow arrow,
      views::BubbleBorder::BubbleAlignment border_alignment,
      Browser* browser);
  static bool IsShowing();
  static void Hide();

  
  
  
  static void clear_close_on_deactivate_for_testing() {
    close_on_deactivate_for_testing_ = false;
  }

 private:
  friend class NewAvatarMenuButtonTest;
  FRIEND_TEST_ALL_PREFIXES(NewAvatarMenuButtonTest, SignOut);

  typedef std::vector<size_t> Indexes;
  typedef std::map<views::Button*, int> ButtonIndexes;
  typedef std::map<views::Button*, std::string> AccountButtonIndexes;

  ProfileChooserView(views::View* anchor_view,
                     views::BubbleBorder::Arrow arrow,
                     Browser* browser,
                     profiles::BubbleViewMode view_mode,
                     profiles::TutorialMode tutorial_mode,
                     signin::GAIAServiceType service_type);
  virtual ~ProfileChooserView();

  
  virtual void Init() OVERRIDE;
  virtual void WindowClosing() OVERRIDE;
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void LinkClicked(views::Link* sender, int event_flags) OVERRIDE;

  
  virtual void StyledLabelLinkClicked(
      const gfx::Range& range, int event_flags) OVERRIDE;

  
  virtual bool HandleKeyEvent(views::Textfield* sender,
                              const ui::KeyEvent& key_event) OVERRIDE;

  
  virtual void OnAvatarMenuChanged(AvatarMenu* avatar_menu) OVERRIDE;

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_id) OVERRIDE;

  static ProfileChooserView* profile_bubble_;
  static bool close_on_deactivate_for_testing_;

  void ResetView();

  
  void ShowView(profiles::BubbleViewMode view_to_display,
                AvatarMenu* avatar_menu);

  
  views::View* CreateProfileChooserView(AvatarMenu* avatar_menu);

  
  
  
  views::View* CreateCurrentProfileView(
      const AvatarMenu::Item& avatar_item,
      bool is_guest);
  views::View* CreateGuestProfileView();
  views::View* CreateOtherProfilesView(const Indexes& avatars_to_show);
  views::View* CreateOptionsView(bool display_lock);
  views::View* CreateSupervisedUserDisclaimerView();

  
  views::View* CreateCurrentProfileAccountsView(
      const AvatarMenu::Item& avatar_item);
  void CreateAccountButton(views::GridLayout* layout,
                           const std::string& account_id,
                           bool is_primary_account,
                           bool reauth_required,
                           int width);

  
  views::View* CreateGaiaSigninView();

  
  views::View* CreateAccountRemovalView();

  
  void RemoveAccount();

  
  void DismissTutorial();

  
  
  
  
  views::View* CreateWelcomeUpgradeTutorialViewIfNeeded(
      bool tutorial_shown, const AvatarMenu::Item& avatar_item);

  
  
  
  views::View* CreateSigninConfirmationView();

  
  views::View* CreateSigninErrorView();

  
  
  
  
  
  views::View*  CreateTutorialView(
      profiles::TutorialMode tutorial_mode,
      const base::string16& title_text,
      const base::string16& content_text,
      const base::string16& link_text,
      const base::string16& button_text,
      bool stack_button,
      views::Link** link,
      views::LabelButton** button,
      views::ImageButton** close_button);

  
  
  views::View* CreateSwitchUserView();

  bool ShouldShowGoIncognito() const;

  
  void PostActionPerformed(ProfileMetrics::ProfileDesktopMenu action_performed);

  scoped_ptr<AvatarMenu> avatar_menu_;
  Browser* browser_;

  
  ButtonIndexes open_other_profile_indexes_map_;

  
  AccountButtonIndexes delete_account_button_map_;
  AccountButtonIndexes reauth_account_button_map_;

  
  views::LabelButton* tutorial_sync_settings_ok_button_;
  views::Link* tutorial_sync_settings_link_;
  views::LabelButton* tutorial_see_whats_new_button_;
  views::Link* tutorial_not_you_link_;
  views::Link* tutorial_learn_more_link_;
  views::ImageButton* tutorial_close_button_;

  
  views::Link* manage_accounts_link_;
  views::LabelButton* signin_current_profile_link_;
  views::LabelButton* auth_error_email_button_;

  
  
  EditableProfilePhoto* current_profile_photo_;
  EditableProfileName* current_profile_name_;

  
  views::LabelButton* users_button_;
  views::LabelButton* go_incognito_button_;
  views::LabelButton* lock_button_;
  views::Link* add_account_link_;

  
  views::ImageButton* gaia_signin_cancel_button_;

  
  views::LabelButton* remove_account_button_;
  views::ImageButton* account_removal_cancel_button_;

  
  views::LabelButton* add_person_button_;
  views::LabelButton* disconnect_button_;
  views::ImageButton* switch_user_cancel_button_;

  
  std::string account_id_to_remove_;

  
  profiles::BubbleViewMode view_mode_;

  
  profiles::TutorialMode tutorial_mode_;

  
  signin::GAIAServiceType gaia_service_type_;

  DISALLOW_COPY_AND_ASSIGN(ProfileChooserView);
};

#endif  
