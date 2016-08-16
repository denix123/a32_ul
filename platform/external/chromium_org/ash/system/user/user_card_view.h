// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_USER_CARD_VIEW_H_
#define ASH_SYSTEM_USER_USER_CARD_VIEW_H_

#include "ash/system/user/login_status.h"
#include "base/macros.h"
#include "ui/views/view.h"

namespace ash {
namespace tray {

class UserCardView : public views::View {
 public:
  
  UserCardView(user::LoginStatus login_status,
               int max_width,
               int multiprofile_index);
  virtual ~UserCardView();

 private:
  
  void AddRetailModeUserContent();

  
  void AddPublicModeUserContent(int max_width);

  void AddUserContent(user::LoginStatus login_status, int multiprofile_index);

  
  views::View* CreateIcon(user::LoginStatus login_status,
                          int multiprofile_index);

  DISALLOW_COPY_AND_ASSIGN(UserCardView);
};

}  
}  

#endif  
