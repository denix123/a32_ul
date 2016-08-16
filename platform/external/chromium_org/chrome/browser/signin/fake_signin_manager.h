// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_FAKE_SIGNIN_MANAGER_H_
#define CHROME_BROWSER_SIGNIN_FAKE_SIGNIN_MANAGER_H_

#include <string>

#include "base/compiler_specific.h"
#include "components/signin/core/browser/signin_manager.h"
#include "components/signin/core/browser/signin_metrics.h"

namespace content {
class BrowserContext;
}

class Profile;


class FakeSigninManagerBase : public SigninManagerBase {
 public:
  explicit FakeSigninManagerBase(Profile* profile);
  virtual ~FakeSigninManagerBase();

  
  
  
  
  
  static KeyedService* Build(content::BrowserContext* context);
};

#if !defined(OS_CHROMEOS)

class FakeSigninManager : public SigninManager {
 public:
  explicit FakeSigninManager(Profile* profile);
  virtual ~FakeSigninManager();

  void set_auth_in_progress(const std::string& username) {
    possibly_invalid_username_ = username;
  }

  void set_password(const std::string& password) { password_ = password; }

  void SignIn(const std::string& username, const std::string& password);

  void FailSignin(const GoogleServiceAuthError& error);

  virtual void StartSignInWithRefreshToken(
      const std::string& refresh_token,
      const std::string& username,
      const std::string& password,
      const OAuthTokenFetchedCallback& oauth_fetched_callback) OVERRIDE;

  virtual void SignOut(signin_metrics::ProfileSignout signout_source_metric)
      OVERRIDE;

  virtual void CompletePendingSignin() OVERRIDE;
};

#endif  

#if defined(OS_CHROMEOS)
typedef FakeSigninManagerBase FakeSigninManagerForTesting;
#else
typedef FakeSigninManager FakeSigninManagerForTesting;
#endif

#endif  
