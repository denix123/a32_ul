// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_ICON_H_
#define CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_ICON_H_

#include "base/basictypes.h"
#include "components/password_manager/core/common/password_manager_ui.h"

class ManagePasswordsIcon {
 public:
  
  
  
  void SetState(password_manager::ui::State state);
  password_manager::ui::State state() const { return state_; }

  void SetActive(bool active);
  bool active() const { return active_; }

 protected:
  
  int icon_id_;
  int tooltip_text_id_;

  ManagePasswordsIcon();
  ~ManagePasswordsIcon();

  
  
  virtual void UpdateVisibleUI() = 0;

 private:
  
  void UpdateIDs();

  password_manager::ui::State state_;
  bool active_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsIcon);
};

#endif  
