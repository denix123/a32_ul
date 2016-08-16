// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_HEADERS_STREAM_H_
#define NET_QUIC_QUIC_HEADERS_STREAM_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/reliable_quic_stream.h"
#include "net/spdy/spdy_framer.h"

namespace net {

class NET_EXPORT_PRIVATE QuicHeadersStream : public ReliableQuicStream {
 public:
  explicit QuicHeadersStream(QuicSession* session);
  virtual ~QuicHeadersStream();

  
  
  
  
  size_t WriteHeaders(
      QuicStreamId stream_id,
      const SpdyHeaderBlock& headers,
      bool fin,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  virtual uint32 ProcessRawData(const char* data, uint32 data_len) OVERRIDE;
  virtual QuicPriority EffectivePriority() const OVERRIDE;

 private:
  class SpdyFramerVisitor;

  

  
  void OnSynStream(SpdyStreamId stream_id,
                   SpdyPriority priority,
                   bool fin);

  
  void OnSynReply(SpdyStreamId stream_id, bool fin);

  
  
  
  
  
  
  void OnControlFrameHeaderData(SpdyStreamId stream_id,
                                const char* header_data,
                                size_t len);

  
  void OnCompressedFrameSize(size_t frame_len);

  
  bool IsConnected();

  
  QuicStreamId stream_id_;
  bool fin_;
  size_t frame_len_;

  SpdyFramer spdy_framer_;
  scoped_ptr<SpdyFramerVisitor> spdy_framer_visitor_;

  DISALLOW_COPY_AND_ASSIGN(QuicHeadersStream);
};

}  

#endif  
