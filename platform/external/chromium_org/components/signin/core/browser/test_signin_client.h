// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_TEST_SIGNIN_CLIENT_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_TEST_SIGNIN_CLIENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "components/signin/core/browser/signin_client.h"
#include "net/url_request/url_request_test_util.h"

#if defined(OS_IOS)
#include "ios/public/test/fake_profile_oauth2_token_service_ios_provider.h"
#endif

class PrefService;

class TestSigninClient : public SigninClient {
 public:
  TestSigninClient();
  TestSigninClient(PrefService* pref_service);
  virtual ~TestSigninClient();

  

  
  
  
  virtual PrefService* GetPrefs() OVERRIDE;

  
  virtual scoped_refptr<TokenWebData> GetDatabase() OVERRIDE;

  
  virtual bool CanRevokeCredentials() OVERRIDE;

  
  virtual std::string GetSigninScopedDeviceId() OVERRIDE;

  
  virtual void ClearSigninScopedDeviceId() OVERRIDE;

  
  virtual std::string GetProductVersion() OVERRIDE;

  
  
  virtual net::URLRequestContextGetter* GetURLRequestContext() OVERRIDE;

  
  
  void SetURLRequestContext(net::URLRequestContextGetter* request_context);

#if defined(OS_IOS)
  virtual ios::ProfileOAuth2TokenServiceIOSProvider* GetIOSProvider() OVERRIDE;
#endif

  
  virtual bool ShouldMergeSigninCredentialsIntoCookieJar() OVERRIDE;

  
  virtual scoped_ptr<CookieChangedCallbackList::Subscription>
      AddCookieChangedCallback(const CookieChangedCallback& callback) OVERRIDE;

#if defined(OS_IOS)
  ios::FakeProfileOAuth2TokenServiceIOSProvider* GetIOSProviderAsFake();
#endif

  
  virtual void SetSigninProcess(int host_id) OVERRIDE;
  virtual void ClearSigninProcess() OVERRIDE;
  virtual bool IsSigninProcess(int host_id) const OVERRIDE;
  virtual bool HasSigninProcess() const OVERRIDE;
  virtual bool IsFirstRun() const OVERRIDE;
  virtual base::Time GetInstallDate() OVERRIDE;

 private:
  
  void LoadDatabase();

  base::ScopedTempDir temp_dir_;
  scoped_refptr<net::URLRequestContextGetter> request_context_;
  scoped_refptr<TokenWebData> database_;
  int signin_host_id_;
  CookieChangedCallbackList cookie_callbacks_;

  PrefService* pref_service_;

#if defined(OS_IOS)
  scoped_ptr<ios::FakeProfileOAuth2TokenServiceIOSProvider> iosProvider_;
#endif

  DISALLOW_COPY_AND_ASSIGN(TestSigninClient);
};

#endif  
