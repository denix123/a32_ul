// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_WEBSOCKET_TRANSPORT_CLIENT_SOCKET_POOL_H_
#define NET_SOCKET_WEBSOCKET_TRANSPORT_CLIENT_SOCKET_POOL_H_

#include <list>
#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/base/net_export.h"
#include "net/base/net_log.h"
#include "net/socket/client_socket_pool.h"
#include "net/socket/client_socket_pool_base.h"
#include "net/socket/transport_client_socket_pool.h"

namespace net {

class ClientSocketFactory;
class ClientSocketPoolHistograms;
class HostResolver;
class NetLog;
class WebSocketEndpointLockManager;
class WebSocketTransportConnectSubJob;

class NET_EXPORT_PRIVATE WebSocketTransportConnectJob : public ConnectJob {
 public:
  WebSocketTransportConnectJob(
      const std::string& group_name,
      RequestPriority priority,
      const scoped_refptr<TransportSocketParams>& params,
      base::TimeDelta timeout_duration,
      const CompletionCallback& callback,
      ClientSocketFactory* client_socket_factory,
      HostResolver* host_resolver,
      ClientSocketHandle* handle,
      Delegate* delegate,
      NetLog* pool_net_log,
      const BoundNetLog& request_net_log);
  virtual ~WebSocketTransportConnectJob();

  
  
  ClientSocketHandle* handle() const { return handle_; }

  
  const CompletionCallback& callback() const { return callback_; }

  const BoundNetLog& request_net_log() const { return request_net_log_; }

  
  virtual LoadState GetLoadState() const OVERRIDE;

 private:
  friend class WebSocketTransportConnectSubJob;
  friend class TransportConnectJobHelper;
  friend class WebSocketEndpointLockManager;

  
  
  enum SubJobType { SUB_JOB_IPV4, SUB_JOB_IPV6 };

  int DoResolveHost();
  int DoResolveHostComplete(int result);
  int DoTransportConnect();
  int DoTransportConnectComplete(int result);

  
  void OnSubJobComplete(int result, WebSocketTransportConnectSubJob* job);

  
  void StartIPv4JobAsync();

  
  
  
  virtual int ConnectInternal() OVERRIDE;

  TransportConnectJobHelper helper_;

  
  
  
  
  scoped_ptr<WebSocketTransportConnectSubJob> ipv4_job_;
  scoped_ptr<WebSocketTransportConnectSubJob> ipv6_job_;

  base::OneShotTimer<WebSocketTransportConnectJob> fallback_timer_;
  TransportConnectJobHelper::ConnectionLatencyHistogram race_result_;
  ClientSocketHandle* const handle_;
  CompletionCallback callback_;
  BoundNetLog request_net_log_;

  bool had_ipv4_;
  bool had_ipv6_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketTransportConnectJob);
};

class NET_EXPORT_PRIVATE WebSocketTransportClientSocketPool
    : public TransportClientSocketPool {
 public:
  WebSocketTransportClientSocketPool(int max_sockets,
                                     int max_sockets_per_group,
                                     ClientSocketPoolHistograms* histograms,
                                     HostResolver* host_resolver,
                                     ClientSocketFactory* client_socket_factory,
                                     NetLog* net_log);

  virtual ~WebSocketTransportClientSocketPool();

  
  
  
  
  
  static void UnlockEndpoint(ClientSocketHandle* handle);

  
  virtual int RequestSocket(const std::string& group_name,
                            const void* resolve_info,
                            RequestPriority priority,
                            ClientSocketHandle* handle,
                            const CompletionCallback& callback,
                            const BoundNetLog& net_log) OVERRIDE;
  virtual void RequestSockets(const std::string& group_name,
                              const void* params,
                              int num_sockets,
                              const BoundNetLog& net_log) OVERRIDE;
  virtual void CancelRequest(const std::string& group_name,
                             ClientSocketHandle* handle) OVERRIDE;
  virtual void ReleaseSocket(const std::string& group_name,
                             scoped_ptr<StreamSocket> socket,
                             int id) OVERRIDE;
  virtual void FlushWithError(int error) OVERRIDE;
  virtual void CloseIdleSockets() OVERRIDE;
  virtual int IdleSocketCount() const OVERRIDE;
  virtual int IdleSocketCountInGroup(
      const std::string& group_name) const OVERRIDE;
  virtual LoadState GetLoadState(
      const std::string& group_name,
      const ClientSocketHandle* handle) const OVERRIDE;
  virtual base::DictionaryValue* GetInfoAsValue(
      const std::string& name,
      const std::string& type,
      bool include_nested_pools) const OVERRIDE;
  virtual base::TimeDelta ConnectionTimeout() const OVERRIDE;
  virtual ClientSocketPoolHistograms* histograms() const OVERRIDE;

  
  virtual bool IsStalled() const OVERRIDE;

 private:
  class ConnectJobDelegate : public ConnectJob::Delegate {
   public:
    explicit ConnectJobDelegate(WebSocketTransportClientSocketPool* owner);
    virtual ~ConnectJobDelegate();

    virtual void OnConnectJobComplete(int result, ConnectJob* job) OVERRIDE;

   private:
    WebSocketTransportClientSocketPool* owner_;

    DISALLOW_COPY_AND_ASSIGN(ConnectJobDelegate);
  };

  
  
  struct StalledRequest {
    StalledRequest(const scoped_refptr<TransportSocketParams>& params,
                   RequestPriority priority,
                   ClientSocketHandle* handle,
                   const CompletionCallback& callback,
                   const BoundNetLog& net_log);
    ~StalledRequest();
    const scoped_refptr<TransportSocketParams> params;
    const RequestPriority priority;
    ClientSocketHandle* const handle;
    const CompletionCallback callback;
    const BoundNetLog net_log;
  };
  friend class ConnectJobDelegate;
  typedef std::map<const ClientSocketHandle*, WebSocketTransportConnectJob*>
      PendingConnectsMap;
  
  
  
  typedef std::list<StalledRequest> StalledRequestQueue;
  typedef std::map<const ClientSocketHandle*, StalledRequestQueue::iterator>
      StalledRequestMap;

  void OnConnectJobComplete(int result, WebSocketTransportConnectJob* job);
  void InvokeUserCallbackLater(ClientSocketHandle* handle,
                               const CompletionCallback& callback,
                               int rv);
  void InvokeUserCallback(ClientSocketHandle* handle,
                          const CompletionCallback& callback,
                          int rv);
  bool ReachedMaxSocketsLimit() const;
  void HandOutSocket(scoped_ptr<StreamSocket> socket,
                     const LoadTimingInfo::ConnectTiming& connect_timing,
                     ClientSocketHandle* handle,
                     const BoundNetLog& net_log);
  void AddJob(ClientSocketHandle* handle,
              scoped_ptr<WebSocketTransportConnectJob> connect_job);
  bool DeleteJob(ClientSocketHandle* handle);
  const WebSocketTransportConnectJob* LookupConnectJob(
      const ClientSocketHandle* handle) const;
  void ActivateStalledRequest();
  bool DeleteStalledRequest(ClientSocketHandle* handle);

  ConnectJobDelegate connect_job_delegate_;
  std::set<const ClientSocketHandle*> pending_callbacks_;
  PendingConnectsMap pending_connects_;
  StalledRequestQueue stalled_request_queue_;
  StalledRequestMap stalled_request_map_;
  ClientSocketPoolHistograms* const histograms_;
  NetLog* const pool_net_log_;
  ClientSocketFactory* const client_socket_factory_;
  HostResolver* const host_resolver_;
  const int max_sockets_;
  int handed_out_socket_count_;
  bool flushing_;

  base::WeakPtrFactory<WebSocketTransportClientSocketPool> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketTransportClientSocketPool);
};

}  

#endif  
