// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_NETWORK_SETTINGS_H_
#define REMOTING_PROTOCOL_NETWORK_SETTINGS_H_

#include <string>

#include "base/basictypes.h"
#include "base/logging.h"

namespace remoting {
namespace protocol {

struct NetworkSettings {

  
  
  
  static const int kDefaultMinPort = 12400;
  static const int kDefaultMaxPort = 12409;

  enum Flags {
    
    
    
    
    NAT_TRAVERSAL_DISABLED = 0x0,

    
    NAT_TRAVERSAL_OUTGOING = 0x1,

    
    NAT_TRAVERSAL_STUN = 0x2,

    
    NAT_TRAVERSAL_RELAY = 0x4,

    
    NAT_TRAVERSAL_FULL = NAT_TRAVERSAL_STUN | NAT_TRAVERSAL_RELAY |
        NAT_TRAVERSAL_OUTGOING
  };

  NetworkSettings()
      : flags(NAT_TRAVERSAL_DISABLED),
        min_port(0),
        max_port(0) {
    DCHECK(!(flags & (NAT_TRAVERSAL_STUN | NAT_TRAVERSAL_RELAY)) ||
           (flags & NAT_TRAVERSAL_OUTGOING));
  }

  explicit NetworkSettings(uint32 flags)
      : flags(flags),
        min_port(0),
        max_port(0) {
  }

  
  
  static bool ParsePortRange(const std::string& port_range,
                             int* out_min_port,
                             int* out_max_port);

  uint32 flags;

  
  
  int min_port;
  int max_port;
};

}  
}  

#endif  
