// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_FAKE_GAIA_H_
#define GOOGLE_APIS_GAIA_FAKE_GAIA_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "url/gurl.h"

namespace base {
class DictionaryValue;
}

namespace net {
namespace test_server {
class BasicHttpResponse;
struct HttpRequest;
class HttpResponse;
}
}

class FakeGaia {
 public:
  typedef std::set<std::string> ScopeSet;

  
  struct AccessTokenInfo {
    AccessTokenInfo();
    ~AccessTokenInfo();

    std::string token;
    std::string issued_to;
    std::string audience;
    std::string user_id;
    ScopeSet scopes;
    int expires_in;
    std::string email;
  };

  
  struct MergeSessionParams {
    MergeSessionParams();
    ~MergeSessionParams();

    
    
    std::string auth_sid_cookie;
    std::string auth_lsid_cookie;

    
    std::string auth_code;

    
    
    std::string refresh_token;
    std::string access_token;

    
    std::string gaia_uber_token;

    
    std::string session_sid_cookie;
    std::string session_lsid_cookie;

    
    std::string email;
  };

  FakeGaia();
  virtual ~FakeGaia();

  void SetFakeMergeSessionParams(const std::string& email,
                                 const std::string& auth_sid_cookie,
                                 const std::string& auth_lsid_cookie);

  
  void SetMergeSessionParams(const MergeSessionParams& params);

  
  
  void Initialize();

  
  
  
  scoped_ptr<net::test_server::HttpResponse> HandleRequest(
      const net::test_server::HttpRequest& request);

  
  
  
  
  void IssueOAuthToken(const std::string& auth_token,
                       const AccessTokenInfo& token_info);

  
  
  
  void RegisterSamlUser(const std::string& account_id, const GURL& saml_idp);

  
  
  static bool GetQueryParameter(const std::string& query,
                                const std::string& key,
                                std::string* value);
 protected:
  
  virtual void HandleMergeSession(
      const net::test_server::HttpRequest& request,
      net::test_server::BasicHttpResponse* http_response);

 private:
  typedef std::multimap<std::string, AccessTokenInfo> AccessTokenInfoMap;
  typedef std::map<std::string, GURL> SamlAccountIdpMap;

  
  void FormatJSONResponse(const base::DictionaryValue& response_dict,
                          net::test_server::BasicHttpResponse* http_response);

  typedef base::Callback<void(
      const net::test_server::HttpRequest& request,
      net::test_server::BasicHttpResponse* http_response)>
          HttpRequestHandlerCallback;
  typedef std::map<std::string, HttpRequestHandlerCallback> RequestHandlerMap;

  
  void HandleProgramaticAuth(
      const net::test_server::HttpRequest& request,
      net::test_server::BasicHttpResponse* http_response);
  void HandleServiceLogin(const net::test_server::HttpRequest& request,
                          net::test_server::BasicHttpResponse* http_response);
  void HandleOAuthLogin(const net::test_server::HttpRequest& request,
                        net::test_server::BasicHttpResponse* http_response);
  void HandleServiceLoginAuth(
      const net::test_server::HttpRequest& request,
      net::test_server::BasicHttpResponse* http_response);
  void HandleSSO(const net::test_server::HttpRequest& request,
                 net::test_server::BasicHttpResponse* http_response);
  void HandleAuthToken(const net::test_server::HttpRequest& request,
                       net::test_server::BasicHttpResponse* http_response);
  void HandleTokenInfo(const net::test_server::HttpRequest& request,
                       net::test_server::BasicHttpResponse* http_response);
  void HandleIssueToken(const net::test_server::HttpRequest& request,
                        net::test_server::BasicHttpResponse* http_response);
  void HandleListAccounts(const net::test_server::HttpRequest& request,
                          net::test_server::BasicHttpResponse* http_response);
  void HandlePeopleGet(const net::test_server::HttpRequest& request,
                       net::test_server::BasicHttpResponse* http_response);
  void HandleGetUserInfo(const net::test_server::HttpRequest& request,
                         net::test_server::BasicHttpResponse* http_response);

  
  
  
  
  const AccessTokenInfo* FindAccessTokenInfo(const std::string& auth_token,
                                             const std::string& client_id,
                                             const std::string& scope_string)
      const;

  MergeSessionParams merge_session_params_;
  AccessTokenInfoMap access_token_info_map_;
  RequestHandlerMap request_handlers_;
  std::string service_login_response_;
  SamlAccountIdpMap saml_account_idp_map_;

  DISALLOW_COPY_AND_ASSIGN(FakeGaia);
};

#endif  
