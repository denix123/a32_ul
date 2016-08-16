// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PROFILES_AVATAR_LABEL_H_
#define CHROME_BROWSER_UI_VIEWS_PROFILES_AVATAR_LABEL_H_

#include "base/compiler_specific.h"
#include "ui/views/controls/button/label_button.h"

class BrowserView;

class AvatarLabel : public views::LabelButton {
 public:
  explicit AvatarLabel(BrowserView* browser_view);
  virtual ~AvatarLabel();

  
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;

  
  void UpdateLabelStyle();

  
  
  
  void SetLabelOnRight(bool label_on_right);

 private:
  BrowserView* browser_view_;

  DISALLOW_COPY_AND_ASSIGN(AvatarLabel);
};

#endif  
