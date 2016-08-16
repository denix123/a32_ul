// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_SUMMARY_PANEL_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_SUMMARY_PANEL_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/views/apps/app_info_dialog/app_info_panel.h"
#include "chrome/common/extensions/extension_constants.h"
#include "ui/views/controls/combobox/combobox_listener.h"

class LaunchOptionsComboboxModel;
class Profile;

namespace extensions {
class Extension;
}

namespace views {
class Combobox;
class Label;
}

class AppInfoSummaryPanel : public AppInfoPanel,
                            public views::ComboboxListener,
                            public base::SupportsWeakPtr<AppInfoSummaryPanel> {
 public:
  AppInfoSummaryPanel(Profile* profile, const extensions::Extension* app);

  virtual ~AppInfoSummaryPanel();

 private:
  
  void CreateDescriptionControl();
  void CreateDetailsControl();
  void CreateLaunchOptionControl();

  void LayoutDescriptionControl();
  void LayoutDetailsControl();

  
  virtual void OnPerformAction(views::Combobox* combobox) OVERRIDE;

  
  
  void StartCalculatingAppSize();
  void OnAppSizeCalculated(int64 app_size_in_bytes);

  
  base::Time GetInstalledTime() const;

  
  
  base::Time GetLastLaunchedTime() const;

  
  extensions::LaunchType GetLaunchType() const;

  
  
  void SetLaunchType(extensions::LaunchType) const;
  bool CanSetLaunchType() const;

  
  views::Label* description_heading_;
  views::Label* description_label_;

  views::Label* details_heading_;
  views::Label* size_title_;
  views::Label* size_value_;
  views::Label* version_title_;
  views::Label* version_value_;
  views::Label* installed_time_title_;
  views::Label* installed_time_value_;
  views::Label* last_run_time_title_;
  views::Label* last_run_time_value_;

  scoped_ptr<LaunchOptionsComboboxModel> launch_options_combobox_model_;
  views::Combobox* launch_options_combobox_;

  base::WeakPtrFactory<AppInfoSummaryPanel> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AppInfoSummaryPanel);
};

#endif  
