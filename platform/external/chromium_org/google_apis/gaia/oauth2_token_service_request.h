// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_OAUTH2_TOKEN_SERVICE_REQUEST_H_
#define GOOGLE_APIS_GAIA_OAUTH2_TOKEN_SERVICE_REQUEST_H_

#include <set>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/non_thread_safe.h"
#include "google_apis/gaia/oauth2_token_service.h"

class OAuth2TokenServiceRequest : public OAuth2TokenService::Request,
                                  public base::NonThreadSafe {
 public:
  class Core;

  
  
  
  
  
  
  
  class TokenServiceProvider
      : public base::RefCountedThreadSafe<TokenServiceProvider> {
   public:
    TokenServiceProvider();

    
    
    
    virtual scoped_refptr<base::SingleThreadTaskRunner>
        GetTokenServiceTaskRunner() = 0;

    
    
    
    
    
    
    
    virtual OAuth2TokenService* GetTokenService() = 0;

   protected:
    friend class base::RefCountedThreadSafe<TokenServiceProvider>;
    virtual ~TokenServiceProvider();
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  static scoped_ptr<OAuth2TokenServiceRequest> CreateAndStart(
      const scoped_refptr<TokenServiceProvider>& provider,
      const std::string& account_id,
      const OAuth2TokenService::ScopeSet& scopes,
      OAuth2TokenService::Consumer* consumer);

  
  
  
  
  
  
  
  static void InvalidateToken(
      const scoped_refptr<TokenServiceProvider>& provider,
      const std::string& account_id,
      const OAuth2TokenService::ScopeSet& scopes,
      const std::string& access_token);

  virtual ~OAuth2TokenServiceRequest();

  
  virtual std::string GetAccountId() const OVERRIDE;

 private:
  OAuth2TokenServiceRequest(const std::string& account_id);

  void StartWithCore(const scoped_refptr<Core>& core);

  const std::string account_id_;
  scoped_refptr<Core> core_;

  DISALLOW_COPY_AND_ASSIGN(OAuth2TokenServiceRequest);
};

#endif  
