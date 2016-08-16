// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_OAUTH2_TOKEN_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_OAUTH2_TOKEN_SERVICE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/stl_util.h"
#include "base/time/time.h"
#include "google_apis/gaia/gaia_oauth_client.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "net/url_request/url_request_context_getter.h"

namespace gaia {
class GaiaOAuthClient;
}

namespace net {
class URLRequestContextGetter;
}

class PrefRegistrySimple;
class PrefService;

namespace chromeos {

class DeviceOAuth2TokenService : public OAuth2TokenService,
                                 public gaia::GaiaOAuthClient::Delegate {
 public:
  typedef base::Callback<void(bool)> StatusCallback;

  
  
  
  void SetAndSaveRefreshToken(const std::string& refresh_token,
                              const StatusCallback& callback);

  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual bool RefreshTokenIsAvailable(const std::string& account_id)
      const OVERRIDE;

  
  virtual std::string GetRobotAccountId() const;

  
  virtual void OnRefreshTokenResponse(const std::string& access_token,
                                      int expires_in_seconds) OVERRIDE;
  virtual void OnGetTokenInfoResponse(
      scoped_ptr<base::DictionaryValue> token_info) OVERRIDE;
  virtual void OnOAuthError() OVERRIDE;
  virtual void OnNetworkError(int response_code) OVERRIDE;

 protected:
  
  virtual net::URLRequestContextGetter* GetRequestContext() OVERRIDE;
  virtual void FetchOAuth2Token(RequestImpl* request,
                                const std::string& account_id,
                                net::URLRequestContextGetter* getter,
                                const std::string& client_id,
                                const std::string& client_secret,
                                const ScopeSet& scopes) OVERRIDE;
  virtual OAuth2AccessTokenFetcher* CreateAccessTokenFetcher(
      const std::string& account_id,
      net::URLRequestContextGetter* getter,
      OAuth2AccessTokenConsumer* consumer) OVERRIDE;

 private:
  struct PendingRequest;
  friend class DeviceOAuth2TokenServiceFactory;
  friend class DeviceOAuth2TokenServiceTest;

  
  enum State {
    
    STATE_LOADING,
    
    STATE_NO_TOKEN,
    
    STATE_VALIDATION_PENDING,
    
    STATE_VALIDATION_STARTED,
    
    STATE_TOKEN_INVALID,
    
    STATE_TOKEN_VALID,
  };

  
  
  explicit DeviceOAuth2TokenService(net::URLRequestContextGetter* getter,
                                    PrefService* local_state);
  virtual ~DeviceOAuth2TokenService();

  
  std::string GetRefreshToken(const std::string& account_id) const;

  
  void DidGetSystemSalt(const std::string& system_salt);

  
  
  void CheckRobotAccountId(const std::string& gaia_robot_id);

  
  
  void EncryptAndSaveToken();

  
  void StartValidation();

  
  void FlushPendingRequests(bool token_is_valid,
                            GoogleServiceAuthError::State error);

  
  void FlushTokenSaveCallbacks(bool result);

  
  void FailRequest(RequestImpl* request, GoogleServiceAuthError::State error);

  
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;
  PrefService* local_state_;

  
  State state_;

  
  std::vector<StatusCallback> token_save_callbacks_;

  
  
  std::vector<PendingRequest*> pending_requests_;

  
  std::string system_salt_;

  int max_refresh_token_validation_retries_;

  
  std::string refresh_token_;

  scoped_ptr<gaia::GaiaOAuthClient> gaia_oauth_client_;

  base::WeakPtrFactory<DeviceOAuth2TokenService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DeviceOAuth2TokenService);
};

}  

#endif  
