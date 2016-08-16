// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CRYPTO_SERVER_STREAM_H_
#define NET_QUIC_QUIC_CRYPTO_SERVER_STREAM_H_

#include <string>

#include "net/quic/crypto/crypto_handshake.h"
#include "net/quic/crypto/quic_crypto_server_config.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_crypto_stream.h"

namespace net {

class CachedNetworkParameters;
class CryptoHandshakeMessage;
class QuicCryptoServerConfig;
class QuicCryptoServerStream;
class QuicSession;

namespace test {
class CryptoTestUtils;
}  

class NET_EXPORT_PRIVATE ServerHelloNotifier : public
    QuicAckNotifier::DelegateInterface {
 public:
  explicit ServerHelloNotifier(QuicCryptoServerStream* stream)
      : server_stream_(stream) {}

  
  virtual void OnAckNotification(
      int num_original_packets,
      int num_original_bytes,
      int num_retransmitted_packets,
      int num_retransmitted_bytes,
      QuicTime::Delta delta_largest_observed) OVERRIDE;

 private:
  virtual ~ServerHelloNotifier() {}

  QuicCryptoServerStream* server_stream_;

  DISALLOW_COPY_AND_ASSIGN(ServerHelloNotifier);
};

class NET_EXPORT_PRIVATE QuicCryptoServerStream : public QuicCryptoStream {
 public:
  QuicCryptoServerStream(const QuicCryptoServerConfig& crypto_config,
                         QuicSession* session);
  virtual ~QuicCryptoServerStream();

  
  
  void CancelOutstandingCallbacks();

  
  virtual void OnHandshakeMessage(
      const CryptoHandshakeMessage& message) OVERRIDE;

  
  
  
  bool GetBase64SHA256ClientChannelID(std::string* output) const;

  uint8 num_handshake_messages() const { return num_handshake_messages_; }

  int num_server_config_update_messages_sent() const {
    return num_server_config_update_messages_sent_;
  }

  
  virtual void SendServerConfigUpdate(
      const CachedNetworkParameters* cached_network_params);

  
  
  void OnServerHelloAcked();

 protected:
  virtual QuicErrorCode ProcessClientHello(
      const CryptoHandshakeMessage& message,
      const ValidateClientHelloResultCallback::Result& result,
      CryptoHandshakeMessage* reply,
      std::string* error_details);

  
  
  virtual void OverrideQuicConfigDefaults(QuicConfig* config);

 private:
  friend class test::CryptoTestUtils;

  class ValidateCallback : public ValidateClientHelloResultCallback {
   public:
    explicit ValidateCallback(QuicCryptoServerStream* parent);
    
    void Cancel();

    
    virtual void RunImpl(const CryptoHandshakeMessage& client_hello,
                         const Result& result) OVERRIDE;

   private:
    QuicCryptoServerStream* parent_;

    DISALLOW_COPY_AND_ASSIGN(ValidateCallback);
  };

  
  
  
  void FinishProcessingHandshakeMessage(
      const CryptoHandshakeMessage& message,
      const ValidateClientHelloResultCallback::Result& result);

  
  const QuicCryptoServerConfig& crypto_config_;

  
  
  
  
  ValidateCallback* validate_client_hello_cb_;

  
  uint8 num_handshake_messages_;

  
  int num_server_config_update_messages_sent_;

  DISALLOW_COPY_AND_ASSIGN(QuicCryptoServerStream);
};

}  

#endif  
