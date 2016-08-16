// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_WEBSOCKETS_WEBSOCKET_EVENT_INTERFACE_H_
#define NET_WEBSOCKETS_WEBSOCKET_EVENT_INTERFACE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"  
#include "net/base/net_export.h"

class GURL;

namespace net {

class SSLInfo;
struct WebSocketHandshakeRequestInfo;
struct WebSocketHandshakeResponseInfo;

class NET_EXPORT WebSocketEventInterface {
 public:
  typedef int WebSocketMessageType;

  
  
  
  enum ChannelState {
    CHANNEL_ALIVE,
    CHANNEL_DELETED
  };

  virtual ~WebSocketEventInterface() {}

  
  
  
  
  virtual ChannelState OnAddChannelResponse(
      bool fail,
      const std::string& selected_subprotocol,
      const std::string& extensions) WARN_UNUSED_RESULT = 0;

  
  
  virtual ChannelState OnDataFrame(
      bool fin,
      WebSocketMessageType type,
      const std::vector<char>& data) WARN_UNUSED_RESULT = 0;

  
  
  
  virtual ChannelState OnFlowControl(int64 quota) WARN_UNUSED_RESULT = 0;

  
  
  
  
  virtual ChannelState OnClosingHandshake() WARN_UNUSED_RESULT = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual ChannelState OnDropChannel(bool was_clean,
                                     uint16 code,
                                     const std::string& reason)
      WARN_UNUSED_RESULT = 0;

  
  
  
  
  
  
  
  virtual ChannelState OnFailChannel(const std::string& message)
      WARN_UNUSED_RESULT = 0;

  
  virtual ChannelState OnStartOpeningHandshake(
      scoped_ptr<WebSocketHandshakeRequestInfo> request) WARN_UNUSED_RESULT = 0;

  
  virtual ChannelState OnFinishOpeningHandshake(
      scoped_ptr<WebSocketHandshakeResponseInfo> response)
      WARN_UNUSED_RESULT = 0;

  
  
  
  class NET_EXPORT SSLErrorCallbacks {
   public:
    virtual ~SSLErrorCallbacks() {}

    
    virtual void CancelSSLRequest(int error, const SSLInfo* ssl_info) = 0;

    
    virtual void ContinueSSLRequest() = 0;
  };

  
  
  
  
  
  
  virtual ChannelState OnSSLCertificateError(
      scoped_ptr<SSLErrorCallbacks> ssl_error_callbacks,
      const GURL& url,
      const SSLInfo& ssl_info,
      bool fatal) WARN_UNUSED_RESULT = 0;

 protected:
  WebSocketEventInterface() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(WebSocketEventInterface);
};

}  

#endif  
