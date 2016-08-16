// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_SOCKET_UTILS_H_
#define NET_TOOLS_QUIC_QUIC_SOCKET_UTILS_H_

#include <stddef.h>
#include <sys/socket.h>
#include <string>

#include "base/basictypes.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/quic_types.h"

namespace net {
namespace tools {

class QuicSocketUtils {
 public:
  
  
  
  static IPAddressNumber GetAddressFromMsghdr(struct msghdr *hdr);

  
  
  static bool GetOverflowFromMsghdr(struct msghdr *hdr,
                                    uint32 *dropped_packets);

  
  
  static int SetGetAddressInfo(int fd, int address_family);

  
  static bool SetSendBufferSize(int fd, size_t size);

  
  static bool SetReceiveBufferSize(int fd, size_t size);

  
  
  
  
  
  
  
  
  
  static int ReadPacket(int fd,
                        char* buffer,
                        size_t buf_len,
                        uint32* dropped_packets,
                        IPAddressNumber* self_address,
                        IPEndPoint* peer_address);

  
  // status to WRITE_STATUS_OK and sets bytes_written.  Otherwise sets the
  
  
  static WriteResult WritePacket(int fd,
                                 const char* buffer,
                                 size_t buf_len,
                                 const IPAddressNumber& self_address,
                                 const IPEndPoint& peer_address);

  
  
  
  static size_t SetIpInfoInCmsg(const IPAddressNumber& self_address,
                                cmsghdr* cmsg);

 private:
  DISALLOW_COPY_AND_ASSIGN(QuicSocketUtils);
};

}  
}  

#endif  
