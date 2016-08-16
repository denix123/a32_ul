// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_PANEL_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_APP_INFO_DIALOG_APP_INFO_PANEL_H_

#include "ui/views/view.h"

class Profile;

namespace extensions {
class Extension;
}
namespace views {
class Label;
}

class AppInfoPanel : public views::View {
 public:
  AppInfoPanel(Profile* profile, const extensions::Extension* app);

  virtual ~AppInfoPanel();

 protected:
  
  views::Label* CreateHeading(const base::string16& text) const;

  
  
  
  views::View* CreateVerticalStack(int child_spacing) const;
  views::View* CreateVerticalStack() const;

  
  
  
  views::View* CreateHorizontalStack(int child_spacing) const;
  views::View* CreateHorizontalStack() const;

  
  
  views::View* CreateKeyValueField(views::View* key, views::View* value) const;

  Profile* profile_;
  const extensions::Extension* app_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AppInfoPanel);
};

#endif  
