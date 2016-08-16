// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_CLIENT_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_CLIENT_H_

#include "base/callback.h"
#include "base/callback_list.h"
#include "base/time/time.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/webdata/token_web_data.h"

class PrefService;
class SigninManagerBase;
class TokenWebData;

namespace net {
class CanonicalCookie;
class URLRequestContextGetter;
}

#if defined(OS_IOS)
namespace ios {
class ProfileOAuth2TokenServiceIOSProvider;
}
#endif

class SigninClient : public KeyedService {
 public:
  typedef base::Callback<void(const net::CanonicalCookie* cookie)>
      CookieChangedCallback;

  typedef base::CallbackList<void(const net::CanonicalCookie* cookie)>
      CookieChangedCallbackList;

  virtual ~SigninClient() {}

  
  virtual PrefService* GetPrefs() = 0;

  
  virtual scoped_refptr<TokenWebData> GetDatabase() = 0;

  
  virtual bool CanRevokeCredentials() = 0;

  
  
  
  
  virtual std::string GetSigninScopedDeviceId() = 0;

  
  
  virtual void ClearSigninScopedDeviceId() = 0;

  
  virtual net::URLRequestContextGetter* GetURLRequestContext() = 0;

  
  
  virtual bool ShouldMergeSigninCredentialsIntoCookieJar() = 0;

  
  
  virtual std::string GetProductVersion() = 0;

  
  
  
  
  virtual scoped_ptr<CookieChangedCallbackList::Subscription>
      AddCookieChangedCallback(const CookieChangedCallback& callback) = 0;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) {}

  virtual void SetSigninProcess(int host_id) = 0;
  virtual void ClearSigninProcess() = 0;
  virtual bool IsSigninProcess(int host_id) const = 0;
  virtual bool HasSigninProcess() const = 0;

  virtual bool IsFirstRun() const = 0;
  virtual base::Time GetInstallDate() = 0;

#if defined(OS_IOS)
  
  
  virtual ios::ProfileOAuth2TokenServiceIOSProvider* GetIOSProvider() = 0;
#endif
};

#endif  
