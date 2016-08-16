// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_EASY_UNLOCK_EASY_UNLOCK_REAUTH_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_EASY_UNLOCK_EASY_UNLOCK_REAUTH_H_

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace chromeos {

class UserContext;

class EasyUnlockReauth {
 public:
  typedef base::Callback<void(const UserContext&)> UserContextCallback;

  
  
  static bool ReauthForUserContext(UserContextCallback callback);

  DISALLOW_IMPLICIT_CONSTRUCTORS(EasyUnlockReauth);
};

}  

#endif  
