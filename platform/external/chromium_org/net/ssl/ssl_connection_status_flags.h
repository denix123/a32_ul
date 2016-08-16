// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_SSL_CONNECTION_STATUS_FLAGS_H_
#define NET_SSL_SSL_CONNECTION_STATUS_FLAGS_H_

#include "base/logging.h"
#include "base/macros.h"

namespace net {

enum {
  
  SSL_CONNECTION_CIPHERSUITE_SHIFT = 0,
  SSL_CONNECTION_CIPHERSUITE_MASK = 0xffff,

  
  SSL_CONNECTION_COMPRESSION_SHIFT = 16,
  SSL_CONNECTION_COMPRESSION_MASK = 3,

  
  SSL_CONNECTION_VERSION_FALLBACK = 1 << 18,

  
  
  
  
  SSL_CONNECTION_NO_RENEGOTIATION_EXTENSION = 1 << 19,

  
  SSL_CONNECTION_VERSION_SHIFT = 20,
  SSL_CONNECTION_VERSION_MASK = 7,

  
  
};

enum {
  SSL_CONNECTION_VERSION_UNKNOWN = 0,  
  SSL_CONNECTION_VERSION_SSL2 = 1,
  SSL_CONNECTION_VERSION_SSL3 = 2,
  SSL_CONNECTION_VERSION_TLS1 = 3,
  SSL_CONNECTION_VERSION_TLS1_1 = 4,
  SSL_CONNECTION_VERSION_TLS1_2 = 5,
  
  SSL_CONNECTION_VERSION_QUIC = 7,
  SSL_CONNECTION_VERSION_MAX,
};
COMPILE_ASSERT(SSL_CONNECTION_VERSION_MAX - 1 <= SSL_CONNECTION_VERSION_MASK,
               SSL_CONNECTION_VERSION_MASK_too_small);

inline int SSLConnectionStatusToCipherSuite(int connection_status) {
  return (connection_status >> SSL_CONNECTION_CIPHERSUITE_SHIFT) &
         SSL_CONNECTION_CIPHERSUITE_MASK;
}

inline int SSLConnectionStatusToVersion(int connection_status) {
  return (connection_status >> SSL_CONNECTION_VERSION_SHIFT) &
         SSL_CONNECTION_VERSION_MASK;
}

inline void SSLConnectionStatusSetCipherSuite(int cipher_suite,
                                              int* connection_status) {
  
  *connection_status &=
      ~(SSL_CONNECTION_CIPHERSUITE_MASK << SSL_CONNECTION_CIPHERSUITE_SHIFT);
  
  *connection_status |= ((cipher_suite & SSL_CONNECTION_CIPHERSUITE_MASK)
                         << SSL_CONNECTION_CIPHERSUITE_SHIFT);
}

inline void SSLConnectionStatusSetVersion(int version, int* connection_status) {
  DCHECK_GT(version, 0);
  DCHECK_LT(version, SSL_CONNECTION_VERSION_MAX);

  
  *connection_status &=
      ~(SSL_CONNECTION_VERSION_MASK << SSL_CONNECTION_VERSION_SHIFT);
  
  *connection_status |=
      ((version & SSL_CONNECTION_VERSION_MASK) << SSL_CONNECTION_VERSION_SHIFT);
}

}  

#endif  
