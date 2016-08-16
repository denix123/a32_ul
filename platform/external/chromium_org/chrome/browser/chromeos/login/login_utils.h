// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_LOGIN_UTILS_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_LOGIN_UTILS_H_

#include <string>

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"

class GURL;
class PrefService;
class Profile;

namespace base {
class CommandLine;
}

namespace chromeos {

class Authenticator;
class LoginDisplayHost;
class AuthStatusConsumer;
class UserContext;

class LoginUtils {
 public:
  class Delegate {
   public:
    
    virtual void OnProfilePrepared(Profile* profile) = 0;

#if defined(ENABLE_RLZ)
    
    virtual void OnRlzInitialized() {}
#endif
   protected:
    virtual ~Delegate() {}
  };

  
  
  static LoginUtils* Get();

  
  static void Set(LoginUtils* ptr);

  
  
  
  static bool IsWhitelisted(const std::string& username, bool* wildcard_match);

  virtual ~LoginUtils() {}

  
  virtual void RespectLocalePreference(Profile* profile,
                                       const base::Closure& callback) = 0;

  
  
  
  virtual void DoBrowserLaunch(Profile* profile,
                               LoginDisplayHost* login_host) = 0;

  
  
  
  
  
  virtual void PrepareProfile(
      const UserContext& user_context,
      bool has_auth_cookies,
      bool has_active_session,
      Delegate* delegate) = 0;

  
  virtual void DelegateDeleted(Delegate* delegate) = 0;

  
  
  
  virtual void CompleteOffTheRecordLogin(const GURL& start_url) = 0;

  
  
  
  
  
  
  
  
  
  virtual scoped_refptr<Authenticator> CreateAuthenticator(
      AuthStatusConsumer* consumer) = 0;

  
  
  
  
  
  
  virtual bool RestartToApplyPerSessionFlagsIfNeed(Profile* profile,
                                                   bool early_restart) = 0;
};

}  

#endif  
