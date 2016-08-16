// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CLIENT_SESSION_H_
#define NET_QUIC_QUIC_CLIENT_SESSION_H_

#include <string>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "net/base/completion_callback.h"
#include "net/proxy/proxy_server.h"
#include "net/quic/quic_client_session_base.h"
#include "net/quic/quic_connection_logger.h"
#include "net/quic/quic_crypto_client_stream.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_reliable_client_stream.h"

namespace net {

class CertVerifyResult;
class DatagramClientSocket;
class QuicConnectionHelper;
class QuicCryptoClientStreamFactory;
class QuicServerId;
class QuicServerInfo;
class QuicStreamFactory;
class SSLInfo;
class TransportSecurityState;

namespace test {
class QuicClientSessionPeer;
}  

class NET_EXPORT_PRIVATE QuicClientSession : public QuicClientSessionBase {
 public:
  
  class NET_EXPORT_PRIVATE Observer {
   public:
    virtual ~Observer() {}
    virtual void OnCryptoHandshakeConfirmed() = 0;
    virtual void OnSessionClosed(int error) = 0;
  };

  
  class NET_EXPORT_PRIVATE StreamRequest {
   public:
    StreamRequest();
    ~StreamRequest();

    
    
    
    
    int StartRequest(const base::WeakPtr<QuicClientSession>& session,
                     QuicReliableClientStream** stream,
                     const CompletionCallback& callback);

    
    
    void CancelRequest();

   private:
    friend class QuicClientSession;

    
    
    void OnRequestCompleteSuccess(QuicReliableClientStream* stream);

    
    
    
    void OnRequestCompleteFailure(int rv);

    base::WeakPtr<QuicClientSession> session_;
    CompletionCallback callback_;
    QuicReliableClientStream** stream_;

    DISALLOW_COPY_AND_ASSIGN(StreamRequest);
  };

  
  
  
  QuicClientSession(QuicConnection* connection,
                    scoped_ptr<DatagramClientSocket> socket,
                    QuicStreamFactory* stream_factory,
                    TransportSecurityState* transport_security_state,
                    scoped_ptr<QuicServerInfo> server_info,
                    const QuicConfig& config,
                    base::TaskRunner* task_runner,
                    NetLog* net_log);
  virtual ~QuicClientSession();

  
  void InitializeSession(
      const QuicServerId& server_id,
      QuicCryptoClientConfig* config,
      QuicCryptoClientStreamFactory* crypto_client_stream_factory);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  
  
  
  
  int TryCreateStream(StreamRequest* request,
                      QuicReliableClientStream** stream);

  
  void CancelRequest(StreamRequest* request);

  
  virtual void OnStreamFrames(
      const std::vector<QuicStreamFrame>& frames) OVERRIDE;
  virtual QuicReliableClientStream* CreateOutgoingDataStream() OVERRIDE;
  virtual QuicCryptoClientStream* GetCryptoStream() OVERRIDE;
  virtual void CloseStream(QuicStreamId stream_id) OVERRIDE;
  virtual void SendRstStream(QuicStreamId id,
                             QuicRstStreamErrorCode error,
                             QuicStreamOffset bytes_written) OVERRIDE;
  virtual void OnCryptoHandshakeEvent(CryptoHandshakeEvent event) OVERRIDE;
  virtual void OnCryptoHandshakeMessageSent(
      const CryptoHandshakeMessage& message) OVERRIDE;
  virtual void OnCryptoHandshakeMessageReceived(
      const CryptoHandshakeMessage& message) OVERRIDE;
  virtual bool GetSSLInfo(SSLInfo* ssl_info) const OVERRIDE;

  
  virtual void OnProofValid(
      const QuicCryptoClientConfig::CachedState& cached) OVERRIDE;
  virtual void OnProofVerifyDetailsAvailable(
      const ProofVerifyDetails& verify_details) OVERRIDE;

  
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) OVERRIDE;
  virtual void OnSuccessfulVersionNegotiation(
      const QuicVersion& version) OVERRIDE;

  
  int CryptoConnect(bool require_confirmation,
                    const CompletionCallback& callback);

  
  int ResumeCryptoConnect(const CompletionCallback& callback);

  
  
  void StartReading();

  
  
  void CloseSessionOnError(int error);

  base::Value* GetInfoAsValue(const std::set<HostPortPair>& aliases);

  const BoundNetLog& net_log() const { return net_log_; }

  base::WeakPtr<QuicClientSession> GetWeakPtr();

  
  
  
  int GetNumSentClientHellos() const;

  
  
  
  bool CanPool(const std::string& hostname) const;

 protected:
  
  virtual QuicDataStream* CreateIncomingDataStream(QuicStreamId id) OVERRIDE;

 private:
  friend class test::QuicClientSessionPeer;

  typedef std::set<Observer*> ObserverSet;
  typedef std::list<StreamRequest*> StreamRequestQueue;

  QuicReliableClientStream* CreateOutgoingReliableStreamImpl();
  
  void OnReadComplete(int result);

  void OnClosedStream();

  
  
  
  
  
  
  
  void CloseSessionOnErrorInner(int net_error, QuicErrorCode quic_error);

  void CloseAllStreams(int net_error);
  void CloseAllObservers(int net_error);

  
  
  
  void NotifyFactoryOfSessionGoingAway();

  
  void NotifyFactoryOfSessionClosedLater();

  
  
  void NotifyFactoryOfSessionClosed();

  void OnConnectTimeout();

  HostPortPair server_host_port_;
  bool require_confirmation_;
  scoped_ptr<QuicCryptoClientStream> crypto_stream_;
  QuicStreamFactory* stream_factory_;
  scoped_ptr<DatagramClientSocket> socket_;
  scoped_refptr<IOBufferWithSize> read_buffer_;
  TransportSecurityState* transport_security_state_;
  scoped_ptr<QuicServerInfo> server_info_;
  scoped_ptr<CertVerifyResult> cert_verify_result_;
  std::string pinning_failure_log_;
  ObserverSet observers_;
  StreamRequestQueue stream_requests_;
  bool read_pending_;
  CompletionCallback callback_;
  size_t num_total_streams_;
  base::TaskRunner* task_runner_;
  BoundNetLog net_log_;
  base::TimeTicks handshake_start_;  
  QuicConnectionLogger* logger_;  
  
  size_t num_packets_read_;
  
  
  bool going_away_;
  base::WeakPtrFactory<QuicClientSession> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(QuicClientSession);
};

}  

#endif  
