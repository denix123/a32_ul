// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PASSWORDS_MANAGE_PASSWORD_ITEM_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_PASSWORDS_MANAGE_PASSWORD_ITEM_VIEW_H_

#include "components/autofill/core/common/password_form.h"
#include "components/password_manager/core/common/password_manager_ui.h"
#include "ui/views/view.h"

class ManagePasswordsBubbleModel;

class ManagePasswordItemView : public views::View {
 public:
  ManagePasswordItemView(
      ManagePasswordsBubbleModel* manage_passwords_bubble_model,
      const autofill::PasswordForm& password_form,
      password_manager::ui::PasswordItemPosition position);

 private:
  class ManageView;
  class PendingView;
  class UndoView;

  virtual ~ManagePasswordItemView();

  void NotifyClickedDelete();
  void NotifyClickedUndo();

  
  void Refresh();

  ManagePasswordsBubbleModel* model_;
  autofill::PasswordForm password_form_;
  bool delete_password_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordItemView);
};

#endif  
