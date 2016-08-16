// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_NET_CERT_VERIFY_PROC_CHROMEOS_H_
#define CHROME_BROWSER_CHROMEOS_NET_CERT_VERIFY_PROC_CHROMEOS_H_

#include "crypto/scoped_nss_types.h"
#include "net/cert/cert_verify_proc_nss.h"
#include "net/cert/nss_profile_filter_chromeos.h"

namespace chromeos {

class CertVerifyProcChromeOS : public net::CertVerifyProcNSS {
 public:
  
  CertVerifyProcChromeOS();

  
  
  explicit CertVerifyProcChromeOS(crypto::ScopedPK11Slot public_slot);

 protected:
  virtual ~CertVerifyProcChromeOS();

 private:
  
  virtual int VerifyInternal(
      net::X509Certificate* cert,
      const std::string& hostname,
      int flags,
      net::CRLSet* crl_set,
      const net::CertificateList& additional_trust_anchors,
      net::CertVerifyResult* verify_result) OVERRIDE;

  
  
  
  
  
  
  
  static SECStatus IsChainValidFunc(void* is_chain_valid_arg,
                                    const CERTCertList* current_chain,
                                    PRBool* chain_ok);

  net::NSSProfileFilterChromeOS profile_filter_;
};

}  

#endif  
