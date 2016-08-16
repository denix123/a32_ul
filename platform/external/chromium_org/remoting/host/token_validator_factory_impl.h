// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_TOKEN_VALIDATOR_FACTORY_IMPL_H_
#define REMOTING_HOST_TOKEN_VALIDATOR_FACTORY_IMPL_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "net/url_request/url_request_context_getter.h"
#include "remoting/host/token_validator_base.h"
#include "remoting/protocol/token_validator.h"

namespace remoting {

class TokenValidatorFactoryImpl : public protocol::TokenValidatorFactory {
 public:
  
  
  
  TokenValidatorFactoryImpl(
      const ThirdPartyAuthConfig& third_party_auth_config,
      scoped_refptr<RsaKeyPair> key_pair,
      scoped_refptr<net::URLRequestContextGetter> request_context_getter);

  virtual ~TokenValidatorFactoryImpl();

  
  virtual scoped_ptr<protocol::TokenValidator> CreateTokenValidator(
      const std::string& local_jid,
      const std::string& remote_jid) OVERRIDE;

 private:
  ThirdPartyAuthConfig third_party_auth_config_;
  scoped_refptr<RsaKeyPair> key_pair_;
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;

  DISALLOW_COPY_AND_ASSIGN(TokenValidatorFactoryImpl);
};

}  

#endif  
