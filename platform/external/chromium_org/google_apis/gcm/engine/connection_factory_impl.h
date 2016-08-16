// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_CONNECTION_FACTORY_IMPL_H_
#define GOOGLE_APIS_GCM_ENGINE_CONNECTION_FACTORY_IMPL_H_

#include "google_apis/gcm/engine/connection_factory.h"

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "google_apis/gcm/protocol/mcs.pb.h"
#include "net/base/backoff_entry.h"
#include "net/base/network_change_notifier.h"
#include "net/proxy/proxy_info.h"
#include "net/proxy/proxy_service.h"
#include "net/socket/client_socket_handle.h"
#include "url/gurl.h"

namespace net {
class HttpNetworkSession;
class NetLog;
}

namespace gcm {

class ConnectionHandlerImpl;
class GCMStatsRecorder;

class GCM_EXPORT ConnectionFactoryImpl :
    public ConnectionFactory,
    public net::NetworkChangeNotifier::NetworkChangeObserver {
 public:
  
  
  
  
  ConnectionFactoryImpl(
      const std::vector<GURL>& mcs_endpoints,
      const net::BackoffEntry::Policy& backoff_policy,
      const scoped_refptr<net::HttpNetworkSession>& gcm_network_session,
      const scoped_refptr<net::HttpNetworkSession>& http_network_session,
      net::NetLog* net_log,
      GCMStatsRecorder* recorder);
  virtual ~ConnectionFactoryImpl();

  
  virtual void Initialize(
      const BuildLoginRequestCallback& request_builder,
      const ConnectionHandler::ProtoReceivedCallback& read_callback,
      const ConnectionHandler::ProtoSentCallback& write_callback) OVERRIDE;
  virtual ConnectionHandler* GetConnectionHandler() const OVERRIDE;
  virtual void Connect() OVERRIDE;
  virtual bool IsEndpointReachable() const OVERRIDE;
  virtual std::string GetConnectionStateString() const OVERRIDE;
  virtual base::TimeTicks NextRetryAttempt() const OVERRIDE;
  virtual void SignalConnectionReset(ConnectionResetReason reason) OVERRIDE;
  virtual void SetConnectionListener(ConnectionListener* listener) OVERRIDE;

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  
  
  GURL GetCurrentEndpoint() const;

  
  
  net::IPEndPoint GetPeerIP();

 protected:
  
  
  
  
  virtual void ConnectImpl();

  
  
  virtual void InitHandler();

  
  
  virtual scoped_ptr<net::BackoffEntry> CreateBackoffEntry(
      const net::BackoffEntry::Policy* const policy);

  
  
  virtual scoped_ptr<ConnectionHandler> CreateConnectionHandler(
      base::TimeDelta read_timeout,
      const ConnectionHandler::ProtoReceivedCallback& read_callback,
      const ConnectionHandler::ProtoSentCallback& write_callback,
      const ConnectionHandler::ConnectionChangedCallback& connection_callback);

  
  
  virtual base::TimeTicks NowTicks();

  
  void OnConnectDone(int result);

  
  void ConnectionHandlerCallback(int result);

 private:
  
  
  void ConnectWithBackoff();

  
  void OnProxyResolveDone(int status);
  void OnProxyConnectDone(int status);
  int ReconsiderProxyAfterError(int error);
  void ReportSuccessfulProxyConnection();

  
  void CloseSocket();

  
  
  void RebuildNetworkSessionAuthCache();

  
  const std::vector<GURL> mcs_endpoints_;
  
  size_t next_endpoint_;
  
  size_t last_successful_endpoint_;

  
  const net::BackoffEntry::Policy backoff_policy_;

  
  
  const scoped_refptr<net::HttpNetworkSession> gcm_network_session_;
  
  
  const scoped_refptr<net::HttpNetworkSession> http_network_session_;
  
  net::BoundNetLog bound_net_log_;
  
  net::ProxyService::PacRequest* pac_request_;
  
  net::ProxyInfo proxy_info_;
  
  net::ClientSocketHandle socket_handle_;
  
  scoped_ptr<net::BackoffEntry> backoff_entry_;
  
  
  scoped_ptr<net::BackoffEntry> previous_backoff_;

  
  bool connecting_;

  
  
  
  bool waiting_for_backoff_;

  
  
  
  bool waiting_for_network_online_;

  
  
  
  bool logging_in_;

  
  
  base::TimeTicks last_login_time_;

  
  scoped_ptr<ConnectionHandler> connection_handler_;

  
  BuildLoginRequestCallback request_builder_;

  
  GCMStatsRecorder* recorder_;

  
  ConnectionListener* listener_;

  base::WeakPtrFactory<ConnectionFactoryImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ConnectionFactoryImpl);
};

}  

#endif  
