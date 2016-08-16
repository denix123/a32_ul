// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_UBERTOKEN_FETCHER_H_
#define GOOGLE_APIS_GAIA_UBERTOKEN_FETCHER_H_

#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/oauth2_token_service.h"


class GaiaAuthFetcher;
class GoogleServiceAuthError;

namespace net {
class URLRequestContextGetter;
}

class UbertokenConsumer {
 public:
  UbertokenConsumer() {}
  virtual ~UbertokenConsumer() {}
  virtual void OnUbertokenSuccess(const std::string& token) {}
  virtual void OnUbertokenFailure(const GoogleServiceAuthError& error) {}
};

class UbertokenFetcher : public GaiaAuthConsumer,
                         public OAuth2TokenService::Consumer {
 public:
  
  static const int kMaxRetries;

  UbertokenFetcher(OAuth2TokenService* token_service,
                   UbertokenConsumer* consumer,
                   net::URLRequestContextGetter* request_context);
  virtual ~UbertokenFetcher();

  
  virtual void StartFetchingToken(const std::string& account_id);

  
  virtual void OnUberAuthTokenSuccess(const std::string& token) OVERRIDE;
  virtual void OnUberAuthTokenFailure(
      const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

 private:
  
  void RequestAccessToken();

  
  void ExchangeTokens();

  OAuth2TokenService* token_service_;
  UbertokenConsumer* consumer_;
  net::URLRequestContextGetter* request_context_;
  scoped_ptr<GaiaAuthFetcher> gaia_auth_fetcher_;
  scoped_ptr<OAuth2TokenService::Request> access_token_request_;
  std::string account_id_;
  std::string access_token_;
  int retry_number_;
  base::OneShotTimer<UbertokenFetcher> retry_timer_;
  bool second_access_token_request_;

  DISALLOW_COPY_AND_ASSIGN(UbertokenFetcher);
};

#endif  
