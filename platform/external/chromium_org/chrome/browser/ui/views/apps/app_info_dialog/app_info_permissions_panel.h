// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_PERMISSIONS_PANEL_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_PERMISSIONS_PANEL_H_

#include <vector>

#include "chrome/browser/ui/views/apps/app_info_dialog/app_info_panel.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/controls/button/button.h"

class Profile;

namespace extensions {
class Extension;
}

namespace ui {
class Event;
}

namespace views {
class Label;
class LabelButton;
class View;
}

class AppInfoPermissionsPanel : public AppInfoPanel,
                                public views::ButtonListener {
 public:
  AppInfoPermissionsPanel(Profile* profile, const extensions::Extension* app);

  virtual ~AppInfoPermissionsPanel();

 private:
  FRIEND_TEST_ALL_PREFIXES(AppInfoPermissionsPanelTest,
                           NoPermissionsObtainedCorrectly);
  FRIEND_TEST_ALL_PREFIXES(AppInfoPermissionsPanelTest,
                           RequiredPermissionsObtainedCorrectly);
  FRIEND_TEST_ALL_PREFIXES(AppInfoPermissionsPanelTest,
                           OptionalPermissionsObtainedCorrectly);
  FRIEND_TEST_ALL_PREFIXES(AppInfoPermissionsPanelTest,
                           RetainedFilePermissionsObtainedCorrectly);

  
  
  
  views::View* CreateBulletedListView(
      const std::vector<base::string16>& messages,
      bool allow_multiline,
      gfx::ElideBehavior elide_behavior);

  
  void CreateActivePermissionsControl();
  void CreateRetainedFilesControl();

  void LayoutActivePermissionsControl();
  void LayoutRetainedFilesControl();

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  const std::vector<base::string16> GetActivePermissionMessages() const;
  const std::vector<base::string16> GetRetainedFilePaths() const;
  void RevokeFilePermissions();

  
  views::Label* active_permissions_heading_;
  views::View* active_permissions_list_;

  views::Label* retained_files_heading_;
  views::View* retained_files_list_;
  views::LabelButton* revoke_file_permissions_button_;

  DISALLOW_COPY_AND_ASSIGN(AppInfoPermissionsPanel);
};

#endif  
