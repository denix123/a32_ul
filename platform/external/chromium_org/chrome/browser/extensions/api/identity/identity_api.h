// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_IDENTITY_IDENTITY_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_IDENTITY_IDENTITY_API_H_

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/extensions/api/identity/extension_token_key.h"
#include "chrome/browser/extensions/api/identity/gaia_web_auth_flow.h"
#include "chrome/browser/extensions/api/identity/identity_mint_queue.h"
#include "chrome/browser/extensions/api/identity/identity_signin_flow.h"
#include "chrome/browser/extensions/api/identity/web_auth_flow.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/signin/profile_identity_provider.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "google_apis/gaia/account_tracker.h"
#include "google_apis/gaia/oauth2_mint_token_flow.h"
#include "google_apis/gaia/oauth2_token_service.h"

class GoogleServiceAuthError;
class MockGetAuthTokenFunction;

namespace content {
class BrowserContext;
}

namespace extensions {

class GetAuthTokenFunctionTest;
class MockGetAuthTokenFunction;

namespace identity_constants {
extern const char kInvalidClientId[];
extern const char kInvalidScopes[];
extern const char kAuthFailure[];
extern const char kNoGrant[];
extern const char kUserRejected[];
extern const char kUserNotSignedIn[];
extern const char kInteractionRequired[];
extern const char kInvalidRedirect[];
extern const char kOffTheRecord[];
extern const char kPageLoadFailure[];
extern const char kCanceled[];
}  

class IdentityTokenCacheValue {
 public:
  IdentityTokenCacheValue();
  explicit IdentityTokenCacheValue(const IssueAdviceInfo& issue_advice);
  IdentityTokenCacheValue(const std::string& token,
                          base::TimeDelta time_to_live);
  ~IdentityTokenCacheValue();

  
  
  enum CacheValueStatus {
    CACHE_STATUS_NOTFOUND,
    CACHE_STATUS_ADVICE,
    CACHE_STATUS_TOKEN
  };

  CacheValueStatus status() const;
  const IssueAdviceInfo& issue_advice() const;
  const std::string& token() const;
  const base::Time& expiration_time() const;

 private:
  bool is_expired() const;

  CacheValueStatus status_;
  IssueAdviceInfo issue_advice_;
  std::string token_;
  base::Time expiration_time_;
};

class IdentityAPI : public BrowserContextKeyedAPI,
                    public gaia::AccountTracker::Observer {
 public:
  typedef std::map<ExtensionTokenKey, IdentityTokenCacheValue> CachedTokens;

  class ShutdownObserver {
   public:
    virtual void OnShutdown() = 0;
  };

  explicit IdentityAPI(content::BrowserContext* context);
  virtual ~IdentityAPI();

  
  IdentityMintRequestQueue* mint_queue();

  
  void SetCachedToken(const ExtensionTokenKey& key,
                      const IdentityTokenCacheValue& token_data);
  void EraseCachedToken(const std::string& extension_id,
                        const std::string& token);
  void EraseAllCachedTokens();
  const IdentityTokenCacheValue& GetCachedToken(const ExtensionTokenKey& key);

  const CachedTokens& GetAllCachedTokens();

  
  std::vector<std::string> GetAccounts() const;
  std::string FindAccountKeyByGaiaId(const std::string& gaia_id);

  
  virtual void Shutdown() OVERRIDE;
  static BrowserContextKeyedAPIFactory<IdentityAPI>* GetFactoryInstance();

  
  virtual void OnAccountAdded(const gaia::AccountIds& ids) OVERRIDE;
  virtual void OnAccountRemoved(const gaia::AccountIds& ids) OVERRIDE;
  virtual void OnAccountSignInChanged(const gaia::AccountIds& ids,
                                      bool is_signed_in) OVERRIDE;

  void AddShutdownObserver(ShutdownObserver* observer);
  void RemoveShutdownObserver(ShutdownObserver* observer);

  void SetAccountStateForTest(gaia::AccountIds ids, bool is_signed_in);

 private:
  friend class BrowserContextKeyedAPIFactory<IdentityAPI>;

  
  static const char* service_name() { return "IdentityAPI"; }
  static const bool kServiceIsNULLWhileTesting = true;

  content::BrowserContext* browser_context_;
  IdentityMintRequestQueue mint_queue_;
  CachedTokens token_cache_;
  ProfileIdentityProvider profile_identity_provider_;
  gaia::AccountTracker account_tracker_;
  ObserverList<ShutdownObserver> shutdown_observer_list_;
};

template <>
void BrowserContextKeyedAPIFactory<IdentityAPI>::DeclareFactoryDependencies();

class IdentityGetAccountsFunction : public ChromeUIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("identity.getAccounts",
                             IDENTITY_GETACCOUNTS);

  IdentityGetAccountsFunction();

 private:
  virtual ~IdentityGetAccountsFunction();

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class IdentityGetAuthTokenFunction : public ChromeAsyncExtensionFunction,
                                     public GaiaWebAuthFlow::Delegate,
                                     public IdentityMintRequestQueue::Request,
                                     public OAuth2MintTokenFlow::Delegate,
                                     public IdentitySigninFlow::Delegate,
                                     public OAuth2TokenService::Consumer,
                                     public IdentityAPI::ShutdownObserver {
 public:
  DECLARE_EXTENSION_FUNCTION("identity.getAuthToken",
                             EXPERIMENTAL_IDENTITY_GETAUTHTOKEN);

  IdentityGetAuthTokenFunction();

  const ExtensionTokenKey* GetExtensionTokenKeyForTest() {
    return token_key_.get();
  }

 protected:
  virtual ~IdentityGetAuthTokenFunction();

  
  virtual void SigninSuccess() OVERRIDE;
  virtual void SigninFailed() OVERRIDE;

  
  virtual void OnGaiaFlowFailure(GaiaWebAuthFlow::Failure failure,
                                 GoogleServiceAuthError service_error,
                                 const std::string& oauth_error) OVERRIDE;
  virtual void OnGaiaFlowCompleted(const std::string& access_token,
                                   const std::string& expiration) OVERRIDE;

  
  virtual void StartLoginAccessTokenRequest();

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

  scoped_ptr<OAuth2TokenService::Request> login_token_request_;

 private:
  FRIEND_TEST_ALL_PREFIXES(GetAuthTokenFunctionTest,
                           ComponentWithChromeClientId);
  FRIEND_TEST_ALL_PREFIXES(GetAuthTokenFunctionTest,
                           ComponentWithNormalClientId);
  FRIEND_TEST_ALL_PREFIXES(GetAuthTokenFunctionTest, InteractiveQueueShutdown);
  FRIEND_TEST_ALL_PREFIXES(GetAuthTokenFunctionTest, NoninteractiveShutdown);

  
  virtual bool RunAsync() OVERRIDE;

  
  void StartAsyncRun();
  void CompleteAsyncRun(bool success);
  void CompleteFunctionWithResult(const std::string& access_token);
  void CompleteFunctionWithError(const std::string& error);

  
  void StartSigninFlow();
  void StartMintTokenFlow(IdentityMintRequestQueue::MintType type);
  void CompleteMintTokenFlow();

  
  virtual void StartMintToken(IdentityMintRequestQueue::MintType type) OVERRIDE;

  
  virtual void OnMintTokenSuccess(const std::string& access_token,
                                  int time_to_live) OVERRIDE;
  virtual void OnMintTokenFailure(
      const GoogleServiceAuthError& error) OVERRIDE;
  virtual void OnIssueAdviceSuccess(
      const IssueAdviceInfo& issue_advice) OVERRIDE;

  
  virtual void OnShutdown() OVERRIDE;

#if defined(OS_CHROMEOS)
  
  
  virtual void StartDeviceLoginAccessTokenRequest();
#endif

  
  void StartGaiaRequest(const std::string& login_access_token);

  
  virtual void ShowLoginPopup();
  virtual void ShowOAuthApprovalDialog(const IssueAdviceInfo& issue_advice);
  
  virtual OAuth2MintTokenFlow* CreateMintTokenFlow(
      const std::string& login_access_token);

  
  bool HasLoginToken() const;

  
  
  std::string MapOAuth2ErrorToDescription(const std::string& error);

  std::string GetOAuth2ClientId() const;

  bool should_prompt_for_scopes_;
  IdentityMintRequestQueue::MintType mint_token_flow_type_;
  scoped_ptr<OAuth2MintTokenFlow> mint_token_flow_;
  OAuth2MintTokenFlow::Mode gaia_mint_token_mode_;
  bool should_prompt_for_signin_;

  scoped_ptr<ExtensionTokenKey> token_key_;
  std::string oauth2_client_id_;
  
  
  IssueAdviceInfo issue_advice_;
  scoped_ptr<GaiaWebAuthFlow> gaia_web_auth_flow_;
  scoped_ptr<IdentitySigninFlow> signin_flow_;
};

class IdentityGetProfileUserInfoFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("identity.getProfileUserInfo",
                             IDENTITY_GETPROFILEUSERINFO);

  IdentityGetProfileUserInfoFunction();

 private:
  virtual ~IdentityGetProfileUserInfoFunction();

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class IdentityRemoveCachedAuthTokenFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("identity.removeCachedAuthToken",
                             EXPERIMENTAL_IDENTITY_REMOVECACHEDAUTHTOKEN)
  IdentityRemoveCachedAuthTokenFunction();

 protected:
  virtual ~IdentityRemoveCachedAuthTokenFunction();

  
  virtual bool RunSync() OVERRIDE;
};

class IdentityLaunchWebAuthFlowFunction : public ChromeAsyncExtensionFunction,
                                          public WebAuthFlow::Delegate {
 public:
  DECLARE_EXTENSION_FUNCTION("identity.launchWebAuthFlow",
                             EXPERIMENTAL_IDENTITY_LAUNCHWEBAUTHFLOW);

  IdentityLaunchWebAuthFlowFunction();

  
  void InitFinalRedirectURLPrefixForTest(const std::string& extension_id);

 private:
  virtual ~IdentityLaunchWebAuthFlowFunction();
  virtual bool RunAsync() OVERRIDE;

  
  virtual void OnAuthFlowFailure(WebAuthFlow::Failure failure) OVERRIDE;
  virtual void OnAuthFlowURLChange(const GURL& redirect_url) OVERRIDE;
  virtual void OnAuthFlowTitleChange(const std::string& title) OVERRIDE {}

  
  void InitFinalRedirectURLPrefix(const std::string& extension_id);

  scoped_ptr<WebAuthFlow> auth_flow_;
  GURL final_url_prefix_;
};

}  

#endif  
