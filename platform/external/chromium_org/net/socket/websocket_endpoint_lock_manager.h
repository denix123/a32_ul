// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_WEBSOCKET_ENDPOINT_LOCK_MANAGER_H_
#define NET_SOCKET_WEBSOCKET_ENDPOINT_LOCK_MANAGER_H_

#include <map>

#include "base/containers/linked_list.h"
#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/singleton.h"
#include "net/base/ip_endpoint.h"
#include "net/base/net_export.h"
#include "net/socket/websocket_transport_client_socket_pool.h"

namespace net {

class StreamSocket;

class NET_EXPORT_PRIVATE WebSocketEndpointLockManager {
 public:
  class NET_EXPORT_PRIVATE Waiter : public base::LinkNode<Waiter> {
   public:
    
    virtual ~Waiter();

    virtual void GotEndpointLock() = 0;
  };

  static WebSocketEndpointLockManager* GetInstance();

  
  
  
  
  int LockEndpoint(const IPEndPoint& endpoint, Waiter* waiter);

  
  
  
  
  
  
  void RememberSocket(StreamSocket* socket, const IPEndPoint& endpoint);

  
  
  
  
  
  void UnlockSocket(StreamSocket* socket);

  
  
  
  void UnlockEndpoint(const IPEndPoint& endpoint);

  
  
  bool IsEmpty() const;

 private:
  struct LockInfo {
    typedef base::LinkedList<Waiter> WaiterQueue;

    LockInfo();
    ~LockInfo();

    
    
    LockInfo(const LockInfo& rhs);

    
    LockInfo& operator=(const LockInfo& rhs);

    
    
    
    scoped_ptr<WaiterQueue> queue;

    
    
    
    
    
    StreamSocket* socket;
  };

  
  
  
  typedef std::map<IPEndPoint, LockInfo> LockInfoMap;
  typedef std::map<StreamSocket*, LockInfoMap::iterator> SocketLockInfoMap;

  WebSocketEndpointLockManager();
  ~WebSocketEndpointLockManager();

  void UnlockEndpointByIterator(LockInfoMap::iterator lock_info_it);
  void EraseSocket(LockInfoMap::iterator lock_info_it);

  
  
  
  LockInfoMap lock_info_map_;

  
  
  
  
  SocketLockInfoMap socket_lock_info_map_;

  friend struct DefaultSingletonTraits<WebSocketEndpointLockManager>;

  DISALLOW_COPY_AND_ASSIGN(WebSocketEndpointLockManager);
};

}  

#endif  
