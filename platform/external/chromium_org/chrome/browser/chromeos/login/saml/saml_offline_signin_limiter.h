// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SAML_SAML_OFFLINE_SIGNIN_LIMITER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SAML_SAML_OFFLINE_SIGNIN_LIMITER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/time/default_clock.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chromeos/login/auth/user_context.h"
#include "components/keyed_service/core/keyed_service.h"

class Profile;

namespace base {
class Clock;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chromeos {

class SAMLOfflineSigninLimiter : public KeyedService {
 public:
  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  void SignedIn(UserContext::AuthFlow auth_flow);

  
  virtual void Shutdown() OVERRIDE;

 private:
  friend class SAMLOfflineSigninLimiterFactory;
  friend class SAMLOfflineSigninLimiterTest;

  
  
  SAMLOfflineSigninLimiter(Profile* profile, base::Clock* clock);
  virtual ~SAMLOfflineSigninLimiter();

  
  
  
  void UpdateLimit();

  
  
  void ForceOnlineLogin();

  base::DefaultClock default_clock_;

  Profile* profile_;
  base::Clock* clock_;

  PrefChangeRegistrar pref_change_registrar_;

  scoped_ptr<base::OneShotTimer<SAMLOfflineSigninLimiter> >
      offline_signin_limit_timer_;

  DISALLOW_COPY_AND_ASSIGN(SAMLOfflineSigninLimiter);
};

}  

#endif  
