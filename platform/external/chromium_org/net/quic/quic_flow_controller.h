// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_FLOW_CONTROLLER_H_
#define NET_QUIC_QUIC_FLOW_CONTROLLER_H_

#include "base/basictypes.h"
#include "net/base/net_export.h"
#include "net/quic/quic_protocol.h"

namespace net {

namespace test {
class QuicFlowControllerPeer;
}  

class QuicConnection;

const QuicStreamId kConnectionLevelId = 0;

class NET_EXPORT_PRIVATE QuicFlowController {
 public:
  QuicFlowController(QuicConnection* connection,
                     QuicStreamId id,
                     bool is_server,
                     uint64 send_window_offset,
                     uint64 receive_window_offset,
                     uint64 max_receive_window);
  ~QuicFlowController() {}

  
  
  
  
  bool UpdateHighestReceivedOffset(uint64 new_offset);

  
  
  void AddBytesConsumed(uint64 bytes_consumed);

  
  void AddBytesSent(uint64 bytes_sent);

  
  
  bool UpdateSendWindowOffset(uint64 new_send_window_offset);

  
  uint64 SendWindowSize() const;

  
  void MaybeSendBlocked();

  
  void Disable();

  
  bool IsEnabled() const;

  
  bool IsBlocked() const;

  
  bool FlowControlViolation();

  uint64 bytes_consumed() const { return bytes_consumed_; }

  uint64 highest_received_byte_offset() const {
    return highest_received_byte_offset_;
  }

 private:
  friend class test::QuicFlowControllerPeer;

  
  void MaybeSendWindowUpdate();

  
  
  
  QuicConnection* connection_;

  
  
  QuicStreamId id_;

  
  bool is_enabled_;

  
  bool is_server_;

  
  
  uint64 bytes_consumed_;

  
  
  uint64 highest_received_byte_offset_;

  
  uint64 bytes_sent_;

  
  
  uint64 send_window_offset_;

  
  
  uint64 receive_window_offset_;

  
  uint64 max_receive_window_;

  
  
  uint64 last_blocked_send_window_offset_;

  DISALLOW_COPY_AND_ASSIGN(QuicFlowController);
};

}  

#endif  
