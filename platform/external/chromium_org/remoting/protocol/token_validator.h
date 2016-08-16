// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_TOKEN_VALIDATOR_H_
#define REMOTING_PROTOCOL_TOKEN_VALIDATOR_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "url/gurl.h"

namespace remoting {

class RsaKeyPair;

namespace protocol {

class TokenValidator {
 public:
  
  
  
  
  typedef base::Callback<void(
      const std::string& shared_secret)> TokenValidatedCallback;

  virtual ~TokenValidator() {}

  
  
  
  
  virtual void ValidateThirdPartyToken(
      const std::string& token,
      const TokenValidatedCallback& token_validated_callback) = 0;

  
  virtual const GURL& token_url() const = 0;

  
  
  virtual const std::string& token_scope() const = 0;
};

class TokenValidatorFactory {
 public:
  virtual ~TokenValidatorFactory() {}

  
  
  virtual scoped_ptr<TokenValidator> CreateTokenValidator(
      const std::string& local_jid,
      const std::string& remote_jid) = 0;
};

}  
}  

#endif  
