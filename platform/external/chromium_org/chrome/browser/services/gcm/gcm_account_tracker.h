// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SERVICES_GCM_GCM_ACCOUNT_TRACKER_H_
#define CHROME_BROWSER_SERVICES_GCM_GCM_ACCOUNT_TRACKER_H_

#include <map>
#include <string>

#include "base/memory/scoped_vector.h"
#include "google_apis/gaia/account_tracker.h"
#include "google_apis/gaia/oauth2_token_service.h"

namespace gcm {

class GCMAccountTracker : public gaia::AccountTracker::Observer,
                          public OAuth2TokenService::Consumer {
 public:
  
  
  
  
  
  
  
  
  
  enum AccountState {
    TOKEN_NEEDED,     
                      
    GETTING_TOKEN,    
    TOKEN_PRESENT,    
    ACCOUNT_REMOVED,  
  };

  
  struct AccountInfo {
    AccountInfo(const std::string& email, AccountState state);
    ~AccountInfo();

    
    std::string email;
    
    std::string access_token;
    
    AccountState state;
  };

  
  
  typedef base::Callback<void(const std::map<std::string, std::string>&
                                  account_tokens)> UpdateAccountsCallback;

  
  
  
  
  
  
  GCMAccountTracker(scoped_ptr<gaia::AccountTracker> account_tracker,
                    const UpdateAccountsCallback& callback);
  virtual ~GCMAccountTracker();

  
  
  
  void Shutdown();

  
  void Start();
  
  void Stop();

 private:
  
  
  typedef std::map<std::string, AccountInfo> AccountInfos;

  
  virtual void OnAccountAdded(const gaia::AccountIds& ids) OVERRIDE;
  virtual void OnAccountRemoved(const gaia::AccountIds& ids) OVERRIDE;
  virtual void OnAccountSignInChanged(const gaia::AccountIds& ids,
                                      bool is_signed_in) OVERRIDE;

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

  
  
  void CompleteCollectingTokens();
  
  
  void DeleteTokenRequest(const OAuth2TokenService::Request* request);
  
  
  void GetAllNeededTokens();
  
  void GetToken(AccountInfos::iterator& account_iter);

  
  void OnAccountSignedIn(const gaia::AccountIds& ids);
  void OnAccountSignedOut(const gaia::AccountIds& ids);

  OAuth2TokenService* GetTokenService();

  
  scoped_ptr<gaia::AccountTracker> account_tracker_;

  
  
  UpdateAccountsCallback callback_;

  
  AccountInfos account_infos_;

  
  bool shutdown_called_;

  ScopedVector<OAuth2TokenService::Request> pending_token_requests_;

  DISALLOW_COPY_AND_ASSIGN(GCMAccountTracker);
};

}  

#endif  
