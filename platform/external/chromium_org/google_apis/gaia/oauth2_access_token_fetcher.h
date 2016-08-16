// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_OAUTH2_ACCESS_TOKEN_FETCHER_H_
#define GOOGLE_APIS_GAIA_OAUTH2_ACCESS_TOKEN_FETCHER_H_

#include <string>
#include <vector>

#include "google_apis/gaia/oauth2_access_token_consumer.h"
#include "net/url_request/url_fetcher_delegate.h"

class OAuth2AccessTokenConsumer;

class OAuth2AccessTokenFetcher {
 public:
  explicit OAuth2AccessTokenFetcher(OAuth2AccessTokenConsumer* consumer);
  virtual ~OAuth2AccessTokenFetcher();

  
  
  
  
  
  
  virtual void Start(const std::string& client_id,
                     const std::string& client_secret,
                     const std::vector<std::string>& scopes) = 0;

  
  virtual void CancelRequest() = 0;

 protected:
  
  void FireOnGetTokenSuccess(const std::string& access_token,
                             const base::Time& expiration_time);

  
  void FireOnGetTokenFailure(const GoogleServiceAuthError& error);

 private:
  OAuth2AccessTokenConsumer* const consumer_;

  DISALLOW_COPY_AND_ASSIGN(OAuth2AccessTokenFetcher);
};

#endif  
