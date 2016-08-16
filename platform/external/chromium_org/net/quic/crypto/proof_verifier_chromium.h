// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_PROOF_VERIFIER_CHROMIUM_H_
#define NET_QUIC_CRYPTO_PROOF_VERIFIER_CHROMIUM_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/base/net_log.h"
#include "net/cert/cert_verify_result.h"
#include "net/cert/x509_certificate.h"
#include "net/quic/crypto/proof_verifier.h"

namespace net {

class CertVerifier;
class TransportSecurityState;

class NET_EXPORT_PRIVATE ProofVerifyDetailsChromium
    : public ProofVerifyDetails {
 public:

  
  virtual ProofVerifyDetails* Clone() const OVERRIDE;

  CertVerifyResult cert_verify_result;

  
  
  
  std::string pinning_failure_log;
};

struct ProofVerifyContextChromium : public ProofVerifyContext {
 public:
  explicit ProofVerifyContextChromium(const BoundNetLog& net_log)
      : net_log(net_log) {}

  BoundNetLog net_log;
};

class NET_EXPORT_PRIVATE ProofVerifierChromium : public ProofVerifier {
 public:
  ProofVerifierChromium(CertVerifier* cert_verifier,
                        TransportSecurityState* transport_security_state);
  virtual ~ProofVerifierChromium();

  
  virtual QuicAsyncStatus VerifyProof(
      const std::string& hostname,
      const std::string& server_config,
      const std::vector<std::string>& certs,
      const std::string& signature,
      const ProofVerifyContext* verify_context,
      std::string* error_details,
      scoped_ptr<ProofVerifyDetails>* verify_details,
      ProofVerifierCallback* callback) OVERRIDE;

 private:
  class Job;
  typedef std::set<Job*> JobSet;

  void OnJobComplete(Job* job);

  
  JobSet active_jobs_;

  
  CertVerifier* const cert_verifier_;

  TransportSecurityState* const transport_security_state_;

  DISALLOW_COPY_AND_ASSIGN(ProofVerifierChromium);
};

}  

#endif  
