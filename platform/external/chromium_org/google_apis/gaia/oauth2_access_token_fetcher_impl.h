// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_OAUTH2_ACCESS_TOKEN_FETCHER_IMPL_H_
#define GOOGLE_APIS_GAIA_OAUTH2_ACCESS_TOKEN_FETCHER_IMPL_H_

#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "google_apis/gaia/oauth2_access_token_consumer.h"
#include "google_apis/gaia/oauth2_access_token_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

class OAuth2AccessTokenFetcherImplTest;

namespace base {
class Time;
}

namespace net {
class URLFetcher;
class URLRequestContextGetter;
class URLRequestStatus;
}

class OAuth2AccessTokenFetcherImpl : public OAuth2AccessTokenFetcher,
                                     public net::URLFetcherDelegate {
 public:
  OAuth2AccessTokenFetcherImpl(OAuth2AccessTokenConsumer* consumer,
                               net::URLRequestContextGetter* getter,
                               const std::string& refresh_token);
  virtual ~OAuth2AccessTokenFetcherImpl();

  
  virtual void Start(const std::string& client_id,
                     const std::string& client_secret,
                     const std::vector<std::string>& scopes) OVERRIDE;

  virtual void CancelRequest() OVERRIDE;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 private:
  enum State {
    INITIAL,
    GET_ACCESS_TOKEN_STARTED,
    GET_ACCESS_TOKEN_DONE,
    ERROR_STATE,
  };

  
  void StartGetAccessToken();
  void EndGetAccessToken(const net::URLFetcher* source);

  
  void OnGetTokenSuccess(const std::string& access_token,
                         const base::Time& expiration_time);
  void OnGetTokenFailure(const GoogleServiceAuthError& error);

  
  static GURL MakeGetAccessTokenUrl();
  static std::string MakeGetAccessTokenBody(
      const std::string& client_id,
      const std::string& client_secret,
      const std::string& refresh_token,
      const std::vector<std::string>& scopes);

  static bool ParseGetAccessTokenSuccessResponse(const net::URLFetcher* source,
                                                 std::string* access_token,
                                                 int* expires_in);

  static bool ParseGetAccessTokenFailureResponse(const net::URLFetcher* source,
                                                 std::string* error);

  
  net::URLRequestContextGetter* const getter_;
  std::string refresh_token_;
  State state_;

  
  scoped_ptr<net::URLFetcher> fetcher_;
  std::string client_id_;
  std::string client_secret_;
  std::vector<std::string> scopes_;

  friend class OAuth2AccessTokenFetcherImplTest;
  FRIEND_TEST_ALL_PREFIXES(OAuth2AccessTokenFetcherImplTest,
                           ParseGetAccessTokenResponse);
  FRIEND_TEST_ALL_PREFIXES(OAuth2AccessTokenFetcherImplTest,
                           MakeGetAccessTokenBody);

  DISALLOW_COPY_AND_ASSIGN(OAuth2AccessTokenFetcherImpl);
};

#endif  
