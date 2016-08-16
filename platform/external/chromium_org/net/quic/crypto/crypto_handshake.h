// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_CRYPTO_HANDSHAKE_H_
#define NET_QUIC_CRYPTO_CRYPTO_HANDSHAKE_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/quic/quic_protocol.h"

namespace net {

class CommonCertSets;
class KeyExchange;
class QuicDecrypter;
class QuicEncrypter;

enum HandshakeFailureReason {
  HANDSHAKE_OK = 0,

  
  
  
  
  CLIENT_NONCE_UNKNOWN_FAILURE = 1,
  
  CLIENT_NONCE_INVALID_FAILURE = 2,
  
  CLIENT_NONCE_NOT_UNIQUE_FAILURE = 3,
  
  CLIENT_NONCE_INVALID_ORBIT_FAILURE = 4,
  
  CLIENT_NONCE_INVALID_TIME_FAILURE = 5,
  
  CLIENT_NONCE_STRIKE_REGISTER_TIMEOUT = 6,
  
  CLIENT_NONCE_STRIKE_REGISTER_FAILURE = 7,

  
  
  
  SERVER_NONCE_DECRYPTION_FAILURE = 8,
  
  SERVER_NONCE_INVALID_FAILURE = 9,
  
  SERVER_NONCE_NOT_UNIQUE_FAILURE = 10,
  
  SERVER_NONCE_INVALID_TIME_FAILURE = 11,

  
  
  
  SERVER_CONFIG_INCHOATE_HELLO_FAILURE = 12,
  
  SERVER_CONFIG_UNKNOWN_CONFIG_FAILURE = 13,

  
  
  
  SOURCE_ADDRESS_TOKEN_INVALID_FAILURE = 14,
  
  SOURCE_ADDRESS_TOKEN_DECRYPTION_FAILURE = 15,
  
  SOURCE_ADDRESS_TOKEN_PARSE_FAILURE = 16,
  
  SOURCE_ADDRESS_TOKEN_DIFFERENT_IP_ADDRESS_FAILURE = 17,
  
  SOURCE_ADDRESS_TOKEN_CLOCK_SKEW_FAILURE = 18,
  
  SOURCE_ADDRESS_TOKEN_EXPIRED_FAILURE = 19,

  MAX_FAILURE_REASON,
};

COMPILE_ASSERT(MAX_FAILURE_REASON <= 32, failure_reason_out_of_sync);

struct NET_EXPORT_PRIVATE CrypterPair {
  CrypterPair();
  ~CrypterPair();
  scoped_ptr<QuicEncrypter> encrypter;
  scoped_ptr<QuicDecrypter> decrypter;
};

struct NET_EXPORT_PRIVATE QuicCryptoNegotiatedParameters {
  
  QuicCryptoNegotiatedParameters();
  ~QuicCryptoNegotiatedParameters();

  QuicTag key_exchange;
  QuicTag aead;
  std::string initial_premaster_secret;
  std::string forward_secure_premaster_secret;
  
  std::string subkey_secret;
  CrypterPair initial_crypters;
  CrypterPair forward_secure_crypters;
  
  std::string sni;
  std::string client_nonce;
  std::string server_nonce;
  
  
  
  
  std::string hkdf_input_suffix;
  
  
  std::vector<std::string> cached_certs;
  
  
  scoped_ptr<KeyExchange> client_key_exchange;
  
  
  
  
  std::string channel_id;

  
  bool x509_ecdsa_supported;

  
  std::string client_common_set_hashes;
  std::string client_cached_cert_hashes;
};

class NET_EXPORT_PRIVATE QuicCryptoConfig {
 public:
  
  
  
  static const char kInitialLabel[];

  
  
  static const char kCETVLabel[];

  
  
  
  static const char kForwardSecureLabel[];

  QuicCryptoConfig();
  ~QuicCryptoConfig();

  
  
  QuicTagVector kexs;
  
  QuicTagVector aead;

  const CommonCertSets* common_cert_sets;

 private:
  DISALLOW_COPY_AND_ASSIGN(QuicCryptoConfig);
};

}  

#endif  
