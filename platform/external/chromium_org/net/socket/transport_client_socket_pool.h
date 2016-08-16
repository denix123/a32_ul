// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_TRANSPORT_CLIENT_SOCKET_POOL_H_
#define NET_SOCKET_TRANSPORT_CLIENT_SOCKET_POOL_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/base/host_port_pair.h"
#include "net/dns/host_resolver.h"
#include "net/dns/single_request_host_resolver.h"
#include "net/socket/client_socket_pool.h"
#include "net/socket/client_socket_pool_base.h"
#include "net/socket/client_socket_pool_histograms.h"

namespace net {

class ClientSocketFactory;

typedef base::Callback<int(const AddressList&, const BoundNetLog& net_log)>
OnHostResolutionCallback;

class NET_EXPORT_PRIVATE TransportSocketParams
    : public base::RefCounted<TransportSocketParams> {
 public:
  
  
  
  
  
  
  
  enum CombineConnectAndWritePolicy {
    COMBINE_CONNECT_AND_WRITE_DEFAULT,    
                                          
    COMBINE_CONNECT_AND_WRITE_DESIRED,    
    COMBINE_CONNECT_AND_WRITE_PROHIBITED  
  };

  
  
  
  
  TransportSocketParams(
      const HostPortPair& host_port_pair,
      bool disable_resolver_cache,
      bool ignore_limits,
      const OnHostResolutionCallback& host_resolution_callback,
      CombineConnectAndWritePolicy combine_connect_and_write);

  const HostResolver::RequestInfo& destination() const { return destination_; }
  bool ignore_limits() const { return ignore_limits_; }
  const OnHostResolutionCallback& host_resolution_callback() const {
    return host_resolution_callback_;
  }

  CombineConnectAndWritePolicy combine_connect_and_write() const {
    return combine_connect_and_write_;
  }

 private:
  friend class base::RefCounted<TransportSocketParams>;
  ~TransportSocketParams();

  HostResolver::RequestInfo destination_;
  bool ignore_limits_;
  const OnHostResolutionCallback host_resolution_callback_;
  CombineConnectAndWritePolicy combine_connect_and_write_;

  DISALLOW_COPY_AND_ASSIGN(TransportSocketParams);
};

class NET_EXPORT_PRIVATE TransportConnectJobHelper {
 public:
  enum State {
    STATE_RESOLVE_HOST,
    STATE_RESOLVE_HOST_COMPLETE,
    STATE_TRANSPORT_CONNECT,
    STATE_TRANSPORT_CONNECT_COMPLETE,
    STATE_NONE,
  };

  
  enum ConnectionLatencyHistogram {
    CONNECTION_LATENCY_UNKNOWN,
    CONNECTION_LATENCY_IPV4_WINS_RACE,
    CONNECTION_LATENCY_IPV4_NO_RACE,
    CONNECTION_LATENCY_IPV6_RACEABLE,
    CONNECTION_LATENCY_IPV6_SOLO,
  };

  TransportConnectJobHelper(const scoped_refptr<TransportSocketParams>& params,
                            ClientSocketFactory* client_socket_factory,
                            HostResolver* host_resolver,
                            LoadTimingInfo::ConnectTiming* connect_timing);
  ~TransportConnectJobHelper();

  ClientSocketFactory* client_socket_factory() {
    return client_socket_factory_;
  }

  const AddressList& addresses() const { return addresses_; }
  State next_state() const { return next_state_; }
  void set_next_state(State next_state) { next_state_ = next_state; }
  CompletionCallback on_io_complete() const { return on_io_complete_; }
  const TransportSocketParams* params() { return params_.get(); }

  int DoResolveHost(RequestPriority priority, const BoundNetLog& net_log);
  int DoResolveHostComplete(int result, const BoundNetLog& net_log);

  template <class T>
  int DoConnectInternal(T* job);

  template <class T>
  void SetOnIOComplete(T* job);

  template <class T>
  void OnIOComplete(T* job, int result);

  
  
  base::TimeDelta HistogramDuration(ConnectionLatencyHistogram race_result);

  static const int kIPv6FallbackTimerInMs;

 private:
  template <class T>
  int DoLoop(T* job, int result);

  scoped_refptr<TransportSocketParams> params_;
  ClientSocketFactory* const client_socket_factory_;
  SingleRequestHostResolver resolver_;
  AddressList addresses_;
  State next_state_;
  CompletionCallback on_io_complete_;
  LoadTimingInfo::ConnectTiming* connect_timing_;

  DISALLOW_COPY_AND_ASSIGN(TransportConnectJobHelper);
};

class NET_EXPORT_PRIVATE TransportConnectJob : public ConnectJob {
 public:
  TransportConnectJob(const std::string& group_name,
                      RequestPriority priority,
                      const scoped_refptr<TransportSocketParams>& params,
                      base::TimeDelta timeout_duration,
                      ClientSocketFactory* client_socket_factory,
                      HostResolver* host_resolver,
                      Delegate* delegate,
                      NetLog* net_log);
  virtual ~TransportConnectJob();

  
  virtual LoadState GetLoadState() const OVERRIDE;

  
  
  static void MakeAddressListStartWithIPv4(AddressList* addrlist);

 private:
  enum ConnectInterval {
    CONNECT_INTERVAL_LE_10MS,
    CONNECT_INTERVAL_LE_20MS,
    CONNECT_INTERVAL_GT_20MS,
  };

  friend class TransportConnectJobHelper;

  int DoResolveHost();
  int DoResolveHostComplete(int result);
  int DoTransportConnect();
  int DoTransportConnectComplete(int result);

  
  void DoIPv6FallbackTransportConnect();
  void DoIPv6FallbackTransportConnectComplete(int result);

  
  
  
  virtual int ConnectInternal() OVERRIDE;

  TransportConnectJobHelper helper_;

  scoped_ptr<StreamSocket> transport_socket_;

  scoped_ptr<StreamSocket> fallback_transport_socket_;
  scoped_ptr<AddressList> fallback_addresses_;
  base::TimeTicks fallback_connect_start_time_;
  base::OneShotTimer<TransportConnectJob> fallback_timer_;

  
  ConnectInterval interval_between_connects_;

  DISALLOW_COPY_AND_ASSIGN(TransportConnectJob);
};

class NET_EXPORT_PRIVATE TransportClientSocketPool : public ClientSocketPool {
 public:
  typedef TransportSocketParams SocketParams;

  TransportClientSocketPool(
      int max_sockets,
      int max_sockets_per_group,
      ClientSocketPoolHistograms* histograms,
      HostResolver* host_resolver,
      ClientSocketFactory* client_socket_factory,
      NetLog* net_log);

  virtual ~TransportClientSocketPool();

  
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
  virtual void AddHigherLayeredPool(HigherLayeredPool* higher_pool) OVERRIDE;
  virtual void RemoveHigherLayeredPool(HigherLayeredPool* higher_pool) OVERRIDE;

 protected:
  
  void NetLogTcpClientSocketPoolRequestedSocket(
      const BoundNetLog& net_log,
      const scoped_refptr<TransportSocketParams>* casted_params);

 private:
  typedef ClientSocketPoolBase<TransportSocketParams> PoolBase;

  class TransportConnectJobFactory
      : public PoolBase::ConnectJobFactory {
   public:
    TransportConnectJobFactory(ClientSocketFactory* client_socket_factory,
                         HostResolver* host_resolver,
                         NetLog* net_log)
        : client_socket_factory_(client_socket_factory),
          host_resolver_(host_resolver),
          net_log_(net_log) {}

    virtual ~TransportConnectJobFactory() {}

    

    virtual scoped_ptr<ConnectJob> NewConnectJob(
        const std::string& group_name,
        const PoolBase::Request& request,
        ConnectJob::Delegate* delegate) const OVERRIDE;

    virtual base::TimeDelta ConnectionTimeout() const OVERRIDE;

   private:
    ClientSocketFactory* const client_socket_factory_;
    HostResolver* const host_resolver_;
    NetLog* net_log_;

    DISALLOW_COPY_AND_ASSIGN(TransportConnectJobFactory);
  };

  PoolBase base_;

  DISALLOW_COPY_AND_ASSIGN(TransportClientSocketPool);
};

template <class T>
int TransportConnectJobHelper::DoConnectInternal(T* job) {
  next_state_ = STATE_RESOLVE_HOST;
  return this->DoLoop(job, OK);
}

template <class T>
void TransportConnectJobHelper::SetOnIOComplete(T* job) {
  
  
  on_io_complete_ = base::Bind(&TransportConnectJobHelper::OnIOComplete<T>,
                               base::Unretained(this),
                               base::Unretained(job));
}

template <class T>
void TransportConnectJobHelper::OnIOComplete(T* job, int result) {
  result = this->DoLoop(job, result);
  if (result != ERR_IO_PENDING)
    job->NotifyDelegateOfCompletion(result);  
}

template <class T>
int TransportConnectJobHelper::DoLoop(T* job, int result) {
  DCHECK_NE(next_state_, STATE_NONE);

  int rv = result;
  do {
    State state = next_state_;
    next_state_ = STATE_NONE;
    switch (state) {
      case STATE_RESOLVE_HOST:
        DCHECK_EQ(OK, rv);
        rv = job->DoResolveHost();
        break;
      case STATE_RESOLVE_HOST_COMPLETE:
        rv = job->DoResolveHostComplete(rv);
        break;
      case STATE_TRANSPORT_CONNECT:
        DCHECK_EQ(OK, rv);
        rv = job->DoTransportConnect();
        break;
      case STATE_TRANSPORT_CONNECT_COMPLETE:
        rv = job->DoTransportConnectComplete(rv);
        break;
      default:
        NOTREACHED();
        rv = ERR_FAILED;
        break;
    }
  } while (rv != ERR_IO_PENDING && next_state_ != STATE_NONE);

  return rv;
}

}  

#endif  
