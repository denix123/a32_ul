// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_DATAGRAM_CHANNEL_FACTORY_H_
#define REMOTING_PROTOCOL_DATAGRAM_CHANNEL_FACTORY_H_

#include <string>

#include "base/callback_forward.h"

namespace net {
class Socket;
}  

namespace remoting {
namespace protocol {

class DatagramChannelFactory {
 public:
  typedef base::Callback<void(scoped_ptr<net::Socket>)>
      ChannelCreatedCallback;

  DatagramChannelFactory() {}

  
  
  
  
  
  virtual void CreateChannel(const std::string& name,
                             const ChannelCreatedCallback& callback) = 0;

  
  
  
  virtual void CancelChannelCreation(const std::string& name) = 0;

 protected:
  virtual ~DatagramChannelFactory() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(DatagramChannelFactory);
};

}  
}  

#endif  
