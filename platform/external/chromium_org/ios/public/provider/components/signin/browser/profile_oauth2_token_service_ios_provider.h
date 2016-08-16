// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_PUBLIC_PROVIDER_COMPONENTS_SIGNIN_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_IOS_PROVIDER_H_
#define IOS_PUBLIC_PROVIDER_COMPONENTS_SIGNIN_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_IOS_PROVIDER_H_

#if defined(__OBJC__)
@class NSDate;
@class NSError;
@class NSString;
#else
class NSDate;
class NSError;
class NSString;
#endif  

#include <set>
#include <string>
#include <vector>

#include "base/callback.h"

namespace ios {

enum AuthenticationErrorCategory {
  
  kAuthenticationErrorCategoryUnknownErrors,
  
  kAuthenticationErrorCategoryAuthorizationErrors,
  
  kAuthenticationErrorCategoryAuthorizationForbiddenErrors,
  
  
  kAuthenticationErrorCategoryNetworkServerErrors,
  
  kAuthenticationErrorCategoryUserCancellationErrors,
  
  kAuthenticationErrorCategoryUnknownIdentityErrors,
};

class ProfileOAuth2TokenServiceIOSProvider {
 public:
  typedef base::Callback<void(NSString* token,
                              NSDate* expiration,
                              NSError* error)> AccessTokenCallback;

  ProfileOAuth2TokenServiceIOSProvider() {};
  virtual ~ProfileOAuth2TokenServiceIOSProvider() {};

  
  
  
  virtual void InitializeSharedAuthentication() = 0;

  
  virtual std::vector<std::string> GetAllAccountIds() = 0;

  
  
  virtual void GetAccessToken(const std::string& account_id,
                              const std::string& client_id,
                              const std::string& client_secret,
                              const std::set<std::string>& scopes,
                              const AccessTokenCallback& callback) = 0;

  
  virtual AuthenticationErrorCategory GetAuthenticationErrorCategory(
      NSError* error) const = 0;
};

}  

#endif  
