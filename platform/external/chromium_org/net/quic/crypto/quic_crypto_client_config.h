// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_QUIC_CRYPTO_CLIENT_CONFIG_H_
#define NET_QUIC_CRYPTO_QUIC_CRYPTO_CLIENT_CONFIG_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/quic/crypto/crypto_handshake.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_server_id.h"

namespace net {

class ChannelIDKey;
class ChannelIDSource;
class CryptoHandshakeMessage;
class ProofVerifier;
class ProofVerifyDetails;
class QuicRandom;

class NET_EXPORT_PRIVATE QuicCryptoClientConfig : public QuicCryptoConfig {
 public:
  
  
  
  class NET_EXPORT_PRIVATE CachedState {
   public:
    CachedState();
    ~CachedState();

    
    
    
    bool IsComplete(QuicWallTime now) const;

    
    bool IsEmpty() const;

    
    
    
    const CryptoHandshakeMessage* GetServerConfig() const;

    
    
    
    QuicErrorCode SetServerConfig(base::StringPiece server_config,
                                  QuicWallTime now,
                                  std::string* error_details);

    
    void InvalidateServerConfig();

    
    void SetProof(const std::vector<std::string>& certs,
                  base::StringPiece signature);

    
    void Clear();

    
    void ClearProof();

    
    
    
    void SetProofValid();

    
    
    
    void SetProofInvalid();

    const std::string& server_config() const;
    const std::string& source_address_token() const;
    const std::vector<std::string>& certs() const;
    const std::string& signature() const;
    bool proof_valid() const;
    uint64 generation_counter() const;
    const ProofVerifyDetails* proof_verify_details() const;

    void set_source_address_token(base::StringPiece token);

    
    void SetProofVerifyDetails(ProofVerifyDetails* details);

    
    
    
    
    void InitializeFrom(const CachedState& other);

    
    
    bool Initialize(base::StringPiece server_config,
                    base::StringPiece source_address_token,
                    const std::vector<std::string>& certs,
                    base::StringPiece signature,
                    QuicWallTime now);

   private:
    std::string server_config_;         
    std::string source_address_token_;  
    std::vector<std::string> certs_;    
                                        
    std::string server_config_sig_;     
    bool server_config_valid_;          
                                        
                                        
    
    
    
    uint64 generation_counter_;

    scoped_ptr<ProofVerifyDetails> proof_verify_details_;

    
    mutable scoped_ptr<CryptoHandshakeMessage> scfg_;

    DISALLOW_COPY_AND_ASSIGN(CachedState);
  };

  QuicCryptoClientConfig();
  ~QuicCryptoClientConfig();

  
  void SetDefaults();

  
  
  CachedState* LookupOrCreate(const QuicServerId& server_id);

  
  void ClearCachedStates();

  
  
  
  
  
  
  
  void FillInchoateClientHello(const QuicServerId& server_id,
                               const QuicVersion preferred_version,
                               const CachedState* cached,
                               QuicCryptoNegotiatedParameters* out_params,
                               CryptoHandshakeMessage* out) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  QuicErrorCode FillClientHello(const QuicServerId& server_id,
                                QuicConnectionId connection_id,
                                const QuicVersion preferred_version,
                                const CachedState* cached,
                                QuicWallTime now,
                                QuicRandom* rand,
                                const ChannelIDKey* channel_id_key,
                                QuicCryptoNegotiatedParameters* out_params,
                                CryptoHandshakeMessage* out,
                                std::string* error_details) const;

  
  
  
  
  
  
  
  QuicErrorCode ProcessRejection(const CryptoHandshakeMessage& rej,
                                 QuicWallTime now,
                                 CachedState* cached,
                                 bool is_https,
                                 QuicCryptoNegotiatedParameters* out_params,
                                 std::string* error_details);

  
  
  
  
  
  
  
  
  QuicErrorCode ProcessServerHello(const CryptoHandshakeMessage& server_hello,
                                   QuicConnectionId connection_id,
                                   const QuicVersionVector& negotiated_versions,
                                   CachedState* cached,
                                   QuicCryptoNegotiatedParameters* out_params,
                                   std::string* error_details);

  
  
  
  
  
  QuicErrorCode ProcessServerConfigUpdate(
      const CryptoHandshakeMessage& server_update,
      QuicWallTime now,
      CachedState* cached,
      QuicCryptoNegotiatedParameters* out_params,
      std::string* error_details);

  ProofVerifier* proof_verifier() const;

  
  
  
  
  void SetProofVerifier(ProofVerifier* verifier);

  ChannelIDSource* channel_id_source() const;

  
  
  
  
  void SetChannelIDSource(ChannelIDSource* source);

  
  
  
  void InitializeFrom(const QuicServerId& server_id,
                      const QuicServerId& canonical_server_id,
                      QuicCryptoClientConfig* canonical_crypto_config);

  
  
  
  
  void AddCanonicalSuffix(const std::string& suffix);

  
  
  
  void PreferAesGcm();

  
  
  
  void DisableEcdsa();

  
  void set_user_agent_id(const std::string& user_agent_id) {
    user_agent_id_ = user_agent_id;
  }

 private:
  typedef std::map<QuicServerId, CachedState*> CachedStateMap;

  
  
  
  
  QuicErrorCode CacheNewServerConfig(
      const CryptoHandshakeMessage& message,
      QuicWallTime now,
      const std::vector<std::string>& cached_certs,
      CachedState* cached,
      std::string* error_details);

  
  
  
  void PopulateFromCanonicalConfig(const QuicServerId& server_id,
                                   CachedState* cached);

  
  
  CachedStateMap cached_states_;

  
  
  
  
  std::map<QuicServerId, QuicServerId> canonical_server_map_;

  
  
  std::vector<std::string> canoncial_suffixes_;

  scoped_ptr<ProofVerifier> proof_verifier_;
  scoped_ptr<ChannelIDSource> channel_id_source_;

  
  bool disable_ecdsa_;

  
  std::string user_agent_id_;

  DISALLOW_COPY_AND_ASSIGN(QuicCryptoClientConfig);
};

}  

#endif  
