// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_OAUTH_TOKEN_GETTER_H_
#define REMOTING_HOST_OAUTH_TOKEN_GETTER_H_

#include <queue>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "google_apis/gaia/gaia_oauth_client.h"

namespace net {
class URLRequestContextGetter;
}  

namespace remoting {

class OAuthTokenGetter :
      public base::NonThreadSafe,
      public gaia::GaiaOAuthClient::Delegate {
 public:
  
  enum Status {
    
    SUCCESS,
    
    NETWORK_ERROR,
    
    AUTH_ERROR,
  };

  typedef base::Callback<void(Status status,
                              const std::string& user_email,
                              const std::string& access_token)> TokenCallback;

  
  
  struct OAuthCredentials {
    OAuthCredentials(const std::string& login,
                     const std::string& refresh_token,
                     bool is_service_account);

    
    std::string login;

    
    std::string refresh_token;

    
    bool is_service_account;
  };

  OAuthTokenGetter(
      scoped_ptr<OAuthCredentials> oauth_credentials,
      scoped_refptr<net::URLRequestContextGetter> url_request_context_getter,
      bool auto_refresh);
  virtual ~OAuthTokenGetter();

  
  void CallWithToken(const OAuthTokenGetter::TokenCallback& on_access_token);

  
  virtual void OnGetTokensResponse(const std::string& user_email,
                                   const std::string& access_token,
                                   int expires_seconds) OVERRIDE;
  virtual void OnRefreshTokenResponse(const std::string& access_token,
                                      int expires_in_seconds) OVERRIDE;
  virtual void OnGetUserEmailResponse(const std::string& user_email) OVERRIDE;
  virtual void OnOAuthError() OVERRIDE;
  virtual void OnNetworkError(int response_code) OVERRIDE;

 private:
  void NotifyCallbacks(Status status,
                       const std::string& user_email,
                       const std::string& access_token);
  void RefreshOAuthToken();

  scoped_ptr<OAuthCredentials> oauth_credentials_;
  scoped_ptr<gaia::GaiaOAuthClient> gaia_oauth_client_;
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;

  bool refreshing_oauth_token_;
  std::string oauth_access_token_;
  std::string verified_email_;
  base::Time auth_token_expiry_time_;
  std::queue<OAuthTokenGetter::TokenCallback> pending_callbacks_;
  scoped_ptr<base::OneShotTimer<OAuthTokenGetter> > refresh_timer_;

  DISALLOW_COPY_AND_ASSIGN(OAuthTokenGetter);
};

}  

#endif  
