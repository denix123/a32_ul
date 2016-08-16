// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_PROFILE_AUTH_DATA_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_PROFILE_AUTH_DATA_H_

#include "base/callback_forward.h"
#include "base/macros.h"

namespace content {
class BrowserContext;
}

namespace chromeos {

class ProfileAuthData {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  static void Transfer(
      content::BrowserContext* from_context,
      content::BrowserContext* to_context,
      bool transfer_auth_cookies_and_channel_ids_on_first_login,
      bool transfer_saml_auth_cookies_on_subsequent_login,
      const base::Closure& completion_callback);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(ProfileAuthData);
};

}  

#endif  
