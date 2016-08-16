// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_CRYPTO_PROVIDER_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_CRYPTO_PROVIDER_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"

namespace local_discovery {

class PrivetV3CryptoProvider {
 public:
  enum HandshakeState {
    
    
    IN_PROGRESS,
    
    
    AWAITING_RESPONSE,
    
    
    
    AWAITING_USER_VERIFICATION,
    
    HANDSHAKE_COMPLETE,
    
    HANDSHAKE_ERROR
  };

  virtual ~PrivetV3CryptoProvider() {}

  static scoped_ptr<PrivetV3CryptoProvider> Create(
      const std::vector<std::string>& available_auth_methods);

  
  virtual HandshakeState GetState() = 0;

  
  virtual std::string GetAuthMethod() = 0;

  
  
  
  virtual HandshakeState GetNextStep(int* step, std::string* package) = 0;

  
  
  
  virtual HandshakeState SetStepResponse(int step,
                                         const std::string& state,
                                         const std::string& package) = 0;

  
  virtual std::string GetVerificationCode() = 0;

  
  
  virtual HandshakeState AcceptVerificationCode() = 0;

  
  virtual bool EncryptData(const std::string& input, std::string* output) = 0;
};

}  

#endif  
