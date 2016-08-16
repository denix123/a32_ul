// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_SECURE_CHANNEL_FACTORY_H_
#define REMOTING_PROTOCOL_SECURE_CHANNEL_FACTORY_H_

#include <map>

#include "base/basictypes.h"
#include "net/base/net_errors.h"
#include "remoting/protocol/stream_channel_factory.h"

namespace remoting {
namespace protocol {

class Authenticator;
class ChannelAuthenticator;

class SecureChannelFactory : public StreamChannelFactory {
 public:
  
  SecureChannelFactory(StreamChannelFactory* channel_factory,
                       Authenticator* authenticator);
  virtual ~SecureChannelFactory();

  
  virtual void CreateChannel(const std::string& name,
                             const ChannelCreatedCallback& callback) OVERRIDE;
  virtual void CancelChannelCreation(const std::string& name) OVERRIDE;

 private:
  typedef std::map<std::string, ChannelAuthenticator*> AuthenticatorMap;

  void OnBaseChannelCreated(const std::string& name,
                            const ChannelCreatedCallback& callback,
                            scoped_ptr<net::StreamSocket> socket);

  void OnSecureChannelCreated(const std::string& name,
                              const ChannelCreatedCallback& callback,
                              int error,
                              scoped_ptr<net::StreamSocket> socket);

  StreamChannelFactory* channel_factory_;
  Authenticator* authenticator_;

  AuthenticatorMap channel_authenticators_;

  DISALLOW_COPY_AND_ASSIGN(SecureChannelFactory);
};

}  
}  

#endif  
