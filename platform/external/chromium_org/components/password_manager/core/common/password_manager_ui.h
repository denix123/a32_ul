// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_COMMON_PASSWORD_MANAGER_UI_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_COMMON_PASSWORD_MANAGER_UI_H_

#include "base/basictypes.h"

namespace password_manager {

namespace ui {

enum State {
  
  INACTIVE_STATE,

  
  
  
  PENDING_PASSWORD_AND_BUBBLE_STATE,

  
  PENDING_PASSWORD_STATE,

  
  
  CONFIRMATION_STATE,

  
  
  MANAGE_STATE,

  
  
  BLACKLIST_STATE,
};

enum PasswordItemPosition {
  
  FIRST_ITEM,

  
  SUBSEQUENT_ITEM,
};

bool IsPendingState(State state);

bool IsAutomaticDisplayState(State state);

State GetEndStateForAutomaticState(State state);

}  

}  

#endif  
