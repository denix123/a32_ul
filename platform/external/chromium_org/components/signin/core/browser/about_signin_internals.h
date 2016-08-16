// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_ABOUT_SIGNIN_INTERNALS_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_ABOUT_SIGNIN_INTERNALS_H_

#include <map>
#include <string>

#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/values.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_client.h"
#include "components/signin/core/browser/signin_internals_util.h"
#include "components/signin/core/browser/signin_manager.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/oauth2_token_service.h"

class GaiaAuthFetcher;
class ProfileOAuth2TokenService;
class SigninClient;
class SigninManagerBase;

typedef std::pair<std::string, std::string> TimedSigninStatusValue;

class AboutSigninInternals
    : public KeyedService,
      public signin_internals_util::SigninDiagnosticsObserver,
      public OAuth2TokenService::DiagnosticsObserver,
      public GaiaAuthConsumer {
 public:
  class Observer {
   public:
    
    
    virtual void OnSigninStateChanged(const base::DictionaryValue* info) = 0;

    
    virtual void OnCookieAccountsFetched(const base::DictionaryValue* info) = 0;
  };

  AboutSigninInternals(ProfileOAuth2TokenService* token_service,
                       SigninManagerBase* signin_manager);
  virtual ~AboutSigninInternals();

  
  
  void AddSigninObserver(Observer* observer);
  void RemoveSigninObserver(Observer* observer);

  
  void RefreshSigninPrefs();

  
  virtual void NotifySigninValueChanged(
      const signin_internals_util::UntimedSigninStatusField& field,
      const std::string& value) OVERRIDE;

  virtual void NotifySigninValueChanged(
      const signin_internals_util::TimedSigninStatusField& field,
      const std::string& value) OVERRIDE;

  void Initialize(SigninClient* client);

  
  virtual void Shutdown() OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  scoped_ptr<base::DictionaryValue> GetSigninStatus();

  
  
  void GetCookieAccountsAsync();

  
  virtual void OnAccessTokenRequested(
      const std::string& account_id,
      const std::string& consumer_id,
      const OAuth2TokenService::ScopeSet& scopes) OVERRIDE;
  virtual void OnFetchAccessTokenComplete(
      const std::string& account_id,
      const std::string& consumer_id,
      const OAuth2TokenService::ScopeSet& scopes,
      GoogleServiceAuthError error,
      base::Time expiration_time) OVERRIDE;
  virtual void OnTokenRemoved(const std::string& account_id,
                              const OAuth2TokenService::ScopeSet& scopes)
      OVERRIDE;

    void OnRefreshTokenReceived(std::string status);
    void OnAuthenticationResultReceived(std::string status);

 private:
  
  struct TokenInfo {
    TokenInfo(const std::string& consumer_id,
              const OAuth2TokenService::ScopeSet& scopes);
    ~TokenInfo();
    base::DictionaryValue* ToValue() const;

    static bool LessThan(const TokenInfo* a, const TokenInfo* b);

    
    void Invalidate();

    std::string consumer_id;              
    OAuth2TokenService::ScopeSet scopes;  
    base::Time request_time;
    base::Time receive_time;
    base::Time expiration_time;
    GoogleServiceAuthError error;
    bool removed_;
  };

  
  typedef std::map<std::string, std::vector<TokenInfo*> > TokenInfoMap;

  
  
  
  struct SigninStatus {
    std::vector<std::string> untimed_signin_fields;
    std::vector<TimedSigninStatusValue> timed_signin_fields;
    TokenInfoMap token_info_map;

    SigninStatus();
    ~SigninStatus();

    TokenInfo* FindToken(const std::string& account_id,
                         const std::string& consumer_id,
                         const OAuth2TokenService::ScopeSet& scopes);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    scoped_ptr<base::DictionaryValue> ToValue(std::string product_version);
  };

  void NotifyObservers();


  
  virtual void OnListAccountsSuccess(const std::string& data) OVERRIDE;
  virtual void OnListAccountsFailure(const GoogleServiceAuthError& error)
      OVERRIDE;

  
  
  void OnListAccountsComplete(
      std::vector<std::pair<std::string, bool> >& gaia_accounts);

  
  
  void OnCookieChanged(const net::CanonicalCookie* cookie);

  
  ProfileOAuth2TokenService* token_service_;

  
  SigninManagerBase* signin_manager_;

  
  SigninClient* client_;

  
  scoped_ptr<GaiaAuthFetcher> gaia_fetcher_;

  
  
  SigninStatus signin_status_;

  ObserverList<Observer> signin_observers_;

  scoped_ptr<SigninClient::CookieChangedCallbackList::Subscription>
      cookie_changed_subscription_;

  DISALLOW_COPY_AND_ASSIGN(AboutSigninInternals);
};

#endif  
