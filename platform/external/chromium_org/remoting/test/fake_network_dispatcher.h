// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_TEST_FAKE_NETWORK_DISPATCHER_H_
#define REMOTING_TEST_FAKE_NETWORK_DISPATCHER_H_

#include <map>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "third_party/libjingle/source/talk/p2p/base/packetsocketfactory.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace net {
class IOBuffer;
}  

namespace remoting {

class FakeNetworkDispatcher
    : public base::RefCountedThreadSafe<FakeNetworkDispatcher> {
 public:
  class Node {
   public:
    virtual ~Node() {};

    
    virtual const scoped_refptr<base::SingleThreadTaskRunner>& GetThread()
        const = 0;
    virtual const rtc::IPAddress& GetAddress() const = 0;

    
    virtual void ReceivePacket(const rtc::SocketAddress& from,
                               const rtc::SocketAddress& to,
                               const scoped_refptr<net::IOBuffer>& data,
                               int data_size) = 0;
  };

  FakeNetworkDispatcher();

  rtc::IPAddress AllocateAddress();

  
  void AddNode(Node* node);
  void RemoveNode(Node* node);

  void DeliverPacket(const rtc::SocketAddress& from,
                     const rtc::SocketAddress& to,
                     const scoped_refptr<net::IOBuffer>& data,
                     int data_size);

 private:
  typedef std::map<rtc::IPAddress, Node*> NodesMap;

  friend class base::RefCountedThreadSafe<FakeNetworkDispatcher>;
  virtual ~FakeNetworkDispatcher();

  NodesMap nodes_;
  base::Lock nodes_lock_;

  
  int allocated_address_;

  DISALLOW_COPY_AND_ASSIGN(FakeNetworkDispatcher);
};

}  

#endif  