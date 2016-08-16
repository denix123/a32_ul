// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_THIRD_PARTY_HOST_AUTHENTICATOR_H_
#define REMOTING_PROTOCOL_THIRD_PARTY_HOST_AUTHENTICATOR_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "remoting/protocol/third_party_authenticator_base.h"

namespace remoting {

class RsaKeyPair;

namespace protocol {

class TokenValidator;

class ThirdPartyHostAuthenticator : public ThirdPartyAuthenticatorBase {
 public:
  
  
  
  
  ThirdPartyHostAuthenticator(const std::string& local_cert,
                              scoped_refptr<RsaKeyPair> key_pair,
                              scoped_ptr<TokenValidator> token_validator);
  virtual ~ThirdPartyHostAuthenticator();

 protected:
  
  virtual void ProcessTokenMessage(
      const buzz::XmlElement* message,
      const base::Closure& resume_callback) OVERRIDE;
  virtual void AddTokenElements(buzz::XmlElement* message) OVERRIDE;

 private:
  void OnThirdPartyTokenValidated(const buzz::XmlElement* message,
                                  const base::Closure& resume_callback,
                                  const std::string& shared_secret);

  std::string local_cert_;
  scoped_refptr<RsaKeyPair> key_pair_;
  scoped_ptr<TokenValidator> token_validator_;

  DISALLOW_COPY_AND_ASSIGN(ThirdPartyHostAuthenticator);
};

}  
}  

#endif  
