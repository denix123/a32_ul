// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_SSL_CONFIG_H_
#define NET_SSL_SSL_CONFIG_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "net/base/net_export.h"
#include "net/cert/x509_certificate.h"

namespace net {

enum {
  SSL_PROTOCOL_VERSION_SSL3 = 0x0300,
  SSL_PROTOCOL_VERSION_TLS1 = 0x0301,
  SSL_PROTOCOL_VERSION_TLS1_1 = 0x0302,
  SSL_PROTOCOL_VERSION_TLS1_2 = 0x0303,
};

NET_EXPORT extern const uint16 kDefaultSSLVersionMin;

NET_EXPORT extern const uint16 kDefaultSSLVersionMax;

NET_EXPORT extern const uint16 kDefaultSSLVersionFallbackMin;

struct NET_EXPORT SSLConfig {
  
  
  SSLConfig();
  ~SSLConfig();

  
  // The expected cert status is written to |cert_status|. |*cert_status| can
  
  bool IsAllowedBadCert(X509Certificate* cert, CertStatus* cert_status) const;

  
  
  bool IsAllowedBadCert(const base::StringPiece& der_cert,
                        CertStatus* cert_status) const;

  
  
  
  
  
  bool rev_checking_enabled;

  
  
  
  
  
  
  
  bool rev_checking_required_local_anchors;

  
  
  
  
  
  uint16 version_min;
  uint16 version_max;

  
  
  
  
  uint16 version_fallback_min;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  std::vector<uint16> disabled_cipher_suites;

  bool channel_id_enabled;   
  bool false_start_enabled;  
  
  
  bool signed_cert_timestamps_enabled;

  
  
  
  bool require_forward_secrecy;

  
  

  struct NET_EXPORT CertAndStatus {
    CertAndStatus();
    ~CertAndStatus();

    std::string der_cert;
    CertStatus cert_status;
  };

  
  
  
  
  std::vector<CertAndStatus> allowed_bad_certs;

  
  bool send_client_cert;

  bool verify_ev_cert;  

  bool version_fallback;  
                          
                          

  
  
  
  
  
  bool cert_io_enabled;

  
  
  
  
  
  
  std::vector<std::string> next_protos;

  scoped_refptr<X509Certificate> client_cert;
};

}  

#endif  
