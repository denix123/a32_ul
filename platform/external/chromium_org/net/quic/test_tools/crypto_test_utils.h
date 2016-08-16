// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_TEST_TOOLS_CRYPTO_TEST_UTILS_H_
#define NET_QUIC_TEST_TOOLS_CRYPTO_TEST_UTILS_H_

#include <stdarg.h>

#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/strings/string_piece.h"
#include "net/quic/crypto/crypto_framer.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_protocol.h"

namespace net {

class ChannelIDSource;
class CommonCertSets;
class ProofSource;
class ProofVerifier;
class ProofVerifyContext;
class QuicClock;
class QuicConfig;
class QuicCryptoClientStream;
class QuicCryptoServerConfig;
class QuicCryptoServerStream;
class QuicCryptoStream;
class QuicRandom;

namespace test {

class PacketSavingConnection;

class CryptoTestUtils {
 public:
  
  
  
  
  
  class CallbackSource {
   public:
    virtual ~CallbackSource() {}

    
    
    virtual void RunPendingCallbacks() = 0;
  };

  
  
  struct FakeClientOptions {
    FakeClientOptions();

    
    
    bool dont_verify_certs;

    
    
    bool channel_id_enabled;

    
    
    bool channel_id_source_async;
  };

  
  static int HandshakeWithFakeServer(PacketSavingConnection* client_conn,
                                     QuicCryptoClientStream* client);

  
  static int HandshakeWithFakeClient(PacketSavingConnection* server_conn,
                                     QuicCryptoServerStream* server,
                                     const FakeClientOptions& options);

  
  
  static void SetupCryptoServerConfigForTest(
      const QuicClock* clock,
      QuicRandom* rand,
      QuicConfig* config,
      QuicCryptoServerConfig* crypto_config);

  
  
  static void CommunicateHandshakeMessages(PacketSavingConnection* a_conn,
                                           QuicCryptoStream* a,
                                           PacketSavingConnection* b_conn,
                                           QuicCryptoStream* b);

  
  
  
  
  static void CommunicateHandshakeMessagesAndRunCallbacks(
      PacketSavingConnection* a_conn,
      QuicCryptoStream* a,
      PacketSavingConnection* b_conn,
      QuicCryptoStream* b,
      CallbackSource* callback_source);

  
  
  static std::pair<size_t, size_t> AdvanceHandshake(
      PacketSavingConnection* a_conn,
      QuicCryptoStream* a,
      size_t a_i,
      PacketSavingConnection* b_conn,
      QuicCryptoStream* b,
      size_t b_i);

  
  static std::string GetValueForTag(const CryptoHandshakeMessage& message,
                                    QuicTag tag);

  
  static ProofSource* ProofSourceForTesting();

  
  static ProofVerifier* ProofVerifierForTesting();

  
  
  static ProofVerifyContext* ProofVerifyContextForTesting();

  
  
  
  
  
  static ProofSource* FakeProofSourceForTesting();
  static ProofVerifier* FakeProofVerifierForTesting();
  static ProofVerifyContext* FakeProofVerifyContextForTesting();

  
  
  static CommonCertSets* MockCommonCertSets(base::StringPiece cert,
                                            uint64 hash,
                                            uint32 index);

  
  
  
  static QuicTag ParseTag(const char* tagstr);

  
  
  
  
  
  
  
  
  
  
  
  
  static CryptoHandshakeMessage Message(const char* message_tag, ...);

  
  
  
  
  static CryptoHandshakeMessage BuildMessage(const char* message_tag,
                                             va_list ap);

  
  
  
  
  static ChannelIDSource* ChannelIDSourceForTesting();

 private:
  static void CompareClientAndServerKeys(QuicCryptoClientStream* client,
                                         QuicCryptoServerStream* server);

  DISALLOW_COPY_AND_ASSIGN(CryptoTestUtils);
};

}  

}  

#endif  
