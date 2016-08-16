// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_PROOF_VERIFIER_H_
#define NET_QUIC_CRYPTO_PROOF_VERIFIER_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/quic/quic_types.h"

namespace net {

class NET_EXPORT_PRIVATE ProofVerifyDetails {
 public:
  virtual ~ProofVerifyDetails() {}

  
  
  virtual ProofVerifyDetails* Clone() const = 0;
};

class NET_EXPORT_PRIVATE ProofVerifyContext {
 public:
  virtual ~ProofVerifyContext() {}
};

class NET_EXPORT_PRIVATE ProofVerifierCallback {
 public:
  virtual ~ProofVerifierCallback() {}

  
  
  
  
  
  
  virtual void Run(bool ok,
                   const std::string& error_details,
                   scoped_ptr<ProofVerifyDetails>* details) = 0;
};

class NET_EXPORT_PRIVATE ProofVerifier {
 public:
  virtual ~ProofVerifier() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual QuicAsyncStatus VerifyProof(const std::string& hostname,
                                      const std::string& server_config,
                                      const std::vector<std::string>& certs,
                                      const std::string& signature,
                                      const ProofVerifyContext* context,
                                      std::string* error_details,
                                      scoped_ptr<ProofVerifyDetails>* details,
                                      ProofVerifierCallback* callback) = 0;
};

}  

#endif  
