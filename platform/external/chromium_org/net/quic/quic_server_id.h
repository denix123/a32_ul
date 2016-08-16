// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SERVER_ID_H_
#define NET_QUIC_QUIC_SERVER_ID_H_

#include <string>

#include "net/base/host_port_pair.h"
#include "net/base/net_export.h"
#include "net/base/privacy_mode.h"

namespace net {

class NET_EXPORT_PRIVATE QuicServerId {
 public:
  QuicServerId();
  QuicServerId(const HostPortPair& host_port_pair,
               bool is_https,
               PrivacyMode privacy_mode);
  QuicServerId(const std::string& host,
               uint16 port,
               bool is_https);
  QuicServerId(const std::string& host,
               uint16 port,
               bool is_https,
               PrivacyMode privacy_mode);
  ~QuicServerId();

  
  bool operator<(const QuicServerId& other) const;
  bool operator==(const QuicServerId& other) const;

  
  
  
  std::string ToString() const;

  const HostPortPair& host_port_pair() const { return host_port_pair_; }

  const std::string& host() const { return host_port_pair_.host(); }

  uint16 port() const { return host_port_pair_.port(); }

  bool is_https() const { return is_https_; }

  PrivacyMode privacy_mode() const { return privacy_mode_; }

 private:
  HostPortPair host_port_pair_;
  bool is_https_;
  PrivacyMode privacy_mode_;
};

}  

#endif  
