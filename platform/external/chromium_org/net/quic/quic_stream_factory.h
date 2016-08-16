// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_STREAM_FACTORY_H_
#define NET_QUIC_QUIC_STREAM_FACTORY_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "base/logging.h"
#include "base/memory/weak_ptr.h"
#include "net/base/address_list.h"
#include "net/base/completion_callback.h"
#include "net/base/host_port_pair.h"
#include "net/base/net_log.h"
#include "net/base/network_change_notifier.h"
#include "net/cert/cert_database.h"
#include "net/proxy/proxy_server.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_crypto_stream.h"
#include "net/quic/quic_http_stream.h"
#include "net/quic/quic_protocol.h"

namespace net {

class CertVerifier;
class ChannelIDService;
class ClientSocketFactory;
class HostResolver;
class HttpServerProperties;
class QuicClock;
class QuicClientSession;
class QuicConnectionHelper;
class QuicCryptoClientStreamFactory;
class QuicRandom;
class QuicServerInfoFactory;
class QuicServerId;
class QuicStreamFactory;
class TransportSecurityState;

namespace test {
class QuicStreamFactoryPeer;
}  

class NET_EXPORT_PRIVATE QuicStreamRequest {
 public:
  explicit QuicStreamRequest(QuicStreamFactory* factory);
  ~QuicStreamRequest();

  
  int Request(const HostPortPair& host_port_pair,
              bool is_https,
              PrivacyMode privacy_mode,
              base::StringPiece method,
              const BoundNetLog& net_log,
              const CompletionCallback& callback);

  void OnRequestComplete(int rv);

  scoped_ptr<QuicHttpStream> ReleaseStream();

  void set_stream(scoped_ptr<QuicHttpStream> stream);

  const BoundNetLog& net_log() const{
    return net_log_;
  }

 private:
  QuicStreamFactory* factory_;
  HostPortPair host_port_pair_;
  bool is_https_;
  BoundNetLog net_log_;
  CompletionCallback callback_;
  scoped_ptr<QuicHttpStream> stream_;

  DISALLOW_COPY_AND_ASSIGN(QuicStreamRequest);
};

class NET_EXPORT_PRIVATE QuicStreamFactory
    : public NetworkChangeNotifier::IPAddressObserver,
      public CertDatabase::Observer {
 public:
  QuicStreamFactory(
      HostResolver* host_resolver,
      ClientSocketFactory* client_socket_factory,
      base::WeakPtr<HttpServerProperties> http_server_properties,
      CertVerifier* cert_verifier,
      ChannelIDService* channel_id_service,
      TransportSecurityState* transport_security_state,
      QuicCryptoClientStreamFactory* quic_crypto_client_stream_factory,
      QuicRandom* random_generator,
      QuicClock* clock,
      size_t max_packet_length,
      const std::string& user_agent_id,
      const QuicVersionVector& supported_versions,
      bool enable_port_selection,
      bool enable_time_based_loss_detection,
      bool always_require_handshake_confirmation,
      bool disable_connection_pooling,
      const QuicTagVector& connection_options);
  virtual ~QuicStreamFactory();

  
  
  
  
  
  int Create(const HostPortPair& host_port_pair,
             bool is_https,
             PrivacyMode privacy_mode,
             base::StringPiece method,
             const BoundNetLog& net_log,
             QuicStreamRequest* request);

  
  void OnIdleSession(QuicClientSession* session);

  
  
  void OnSessionGoingAway(QuicClientSession* session);

  
  void OnSessionClosed(QuicClientSession* session);

  
  void OnSessionConnectTimeout(QuicClientSession* session);

  
  void CancelRequest(QuicStreamRequest* request);

  
  void CloseAllSessions(int error);

  base::Value* QuicStreamFactoryInfoToValue() const;

  
  void ClearCachedStatesInCryptoConfig();

  

  
  
  virtual void OnIPAddressChanged() OVERRIDE;

  

  
  virtual void OnCertAdded(const X509Certificate* cert) OVERRIDE;
  virtual void OnCACertChanged(const X509Certificate* cert) OVERRIDE;

  bool require_confirmation() const {
    return require_confirmation_;
  }

  void set_require_confirmation(bool require_confirmation);

  QuicConnectionHelper* helper() { return helper_.get(); }

  bool enable_port_selection() const { return enable_port_selection_; }

  bool has_quic_server_info_factory() {
    return quic_server_info_factory_ != NULL;
  }

  void set_quic_server_info_factory(
      QuicServerInfoFactory* quic_server_info_factory) {
    DCHECK(!quic_server_info_factory_);
    quic_server_info_factory_ = quic_server_info_factory;
  }

 private:
  class Job;
  friend class test::QuicStreamFactoryPeer;

  
  
  struct NET_EXPORT_PRIVATE IpAliasKey {
    IpAliasKey();
    IpAliasKey(IPEndPoint ip_endpoint, bool is_https);
    ~IpAliasKey();

    IPEndPoint ip_endpoint;
    bool is_https;

    
    bool operator<(const IpAliasKey &other) const;
    bool operator==(const IpAliasKey &other) const;
  };

  typedef std::map<QuicServerId, QuicClientSession*> SessionMap;
  typedef std::map<QuicClientSession*, QuicServerId> SessionIdMap;
  typedef std::set<QuicServerId> AliasSet;
  typedef std::map<QuicClientSession*, AliasSet> SessionAliasMap;
  typedef std::set<QuicClientSession*> SessionSet;
  typedef std::map<IpAliasKey, SessionSet> IPAliasMap;
  typedef std::map<QuicServerId, QuicCryptoClientConfig*> CryptoConfigMap;
  typedef std::map<QuicServerId, Job*> JobMap;
  typedef std::map<QuicStreamRequest*, Job*> RequestMap;
  typedef std::set<QuicStreamRequest*> RequestSet;
  typedef std::map<Job*, RequestSet> JobRequestsMap;

  
  
  scoped_ptr<QuicHttpStream> CreateIfSessionExists(const QuicServerId& key,
                                                   const BoundNetLog& net_log);

  bool OnResolution(const QuicServerId& server_id,
                    const AddressList& address_list);
  void OnJobComplete(Job* job, int rv);
  bool HasActiveSession(const QuicServerId& server_id) const;
  bool HasActiveJob(const QuicServerId& server_id) const;
  int CreateSession(const QuicServerId& server_id,
                    scoped_ptr<QuicServerInfo> quic_server_info,
                    const AddressList& address_list,
                    const BoundNetLog& net_log,
                    QuicClientSession** session);
  void ActivateSession(const QuicServerId& key,
                       QuicClientSession* session);

  
  
  void InitializeCachedStateInCryptoConfig(
      const QuicServerId& server_id,
      const scoped_ptr<QuicServerInfo>& server_info);

  void ProcessGoingAwaySession(QuicClientSession* session,
                               const QuicServerId& server_id,
                               bool was_session_active);

  bool require_confirmation_;
  HostResolver* host_resolver_;
  ClientSocketFactory* client_socket_factory_;
  base::WeakPtr<HttpServerProperties> http_server_properties_;
  TransportSecurityState* transport_security_state_;
  QuicServerInfoFactory* quic_server_info_factory_;
  QuicCryptoClientStreamFactory* quic_crypto_client_stream_factory_;
  QuicRandom* random_generator_;
  scoped_ptr<QuicClock> clock_;
  const size_t max_packet_length_;

  
  scoped_ptr<QuicConnectionHelper> helper_;

  
  SessionIdMap all_sessions_;
  
  
  SessionMap active_sessions_;
  
  SessionAliasMap session_aliases_;
  
  IPAliasMap ip_aliases_;

  
  AliasSet gone_away_aliases_;

  const QuicConfig config_;
  QuicCryptoClientConfig crypto_config_;

  JobMap active_jobs_;
  JobRequestsMap job_requests_map_;
  RequestMap active_requests_;

  QuicVersionVector supported_versions_;

  
  
  
  bool enable_port_selection_;

  
  
  bool always_require_handshake_confirmation_;

  
  bool disable_connection_pooling_;

  
  
  
  
  
  
  uint64 port_seed_;

  
  IPEndPoint local_address_;
  bool check_persisted_supports_quic_;

  base::WeakPtrFactory<QuicStreamFactory> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(QuicStreamFactory);
};

}  

#endif  
