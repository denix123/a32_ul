// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_CHROMIUM_PORT_ALLOCATOR_H_
#define REMOTING_PROTOCOL_CHROMIUM_PORT_ALLOCATOR_H_

#include <set>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/libjingle/source/talk/p2p/client/httpportallocator.h"

namespace net {
class URLRequestContextGetter;
}  

namespace remoting {
namespace protocol {

struct NetworkSettings;

class ChromiumPortAllocator : public cricket::HttpPortAllocatorBase {
 public:
  static scoped_ptr<ChromiumPortAllocator> Create(
      const scoped_refptr<net::URLRequestContextGetter>& url_context,
      const NetworkSettings& network_settings);

  virtual ~ChromiumPortAllocator();

  
  virtual cricket::PortAllocatorSession* CreateSessionInternal(
      const std::string& content_name,
      int component,
      const std::string& ice_username_fragment,
      const std::string& ice_password) OVERRIDE;

 private:
  ChromiumPortAllocator(
      const scoped_refptr<net::URLRequestContextGetter>& url_context,
      scoped_ptr<rtc::NetworkManager> network_manager,
      scoped_ptr<rtc::PacketSocketFactory> socket_factory);

  scoped_refptr<net::URLRequestContextGetter> url_context_;
  scoped_ptr<rtc::NetworkManager> network_manager_;
  scoped_ptr<rtc::PacketSocketFactory> socket_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromiumPortAllocator);
};

}  
}  

#endif  
