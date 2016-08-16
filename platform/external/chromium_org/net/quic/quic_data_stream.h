// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_DATA_STREAM_H_
#define NET_QUIC_QUIC_DATA_STREAM_H_

#include <sys/types.h>

#include <list>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/iovec.h"
#include "net/base/net_export.h"
#include "net/quic/quic_ack_notifier.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_stream_sequencer.h"
#include "net/quic/reliable_quic_stream.h"
#include "net/spdy/spdy_framer.h"

namespace net {

namespace test {
class QuicDataStreamPeer;
class ReliableQuicStreamPeer;
}  

class IPEndPoint;
class QuicSession;
class SSLInfo;

class NET_EXPORT_PRIVATE QuicDataStream : public ReliableQuicStream {
 public:
  
  class Visitor {
   public:
    Visitor() {}

    
    virtual void OnClose(QuicDataStream* stream) = 0;

   protected:
    virtual ~Visitor() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(Visitor);
  };

  QuicDataStream(QuicStreamId id, QuicSession* session);

  virtual ~QuicDataStream();

  
  virtual void OnClose() OVERRIDE;
  virtual uint32 ProcessRawData(const char* data, uint32 data_len) OVERRIDE;
  
  
  // compressed but not written headers it can write the headers with a higher
  
  virtual QuicPriority EffectivePriority() const OVERRIDE;

  
  
  virtual uint32 ProcessData(const char* data, uint32 data_len) = 0;

  
  
  
  
  virtual void OnStreamHeaders(base::StringPiece headers_data);

  
  
  virtual void OnStreamHeadersPriority(QuicPriority priority);

  
  
  
  virtual void OnStreamHeadersComplete(bool fin, size_t frame_len);

  
  
  virtual size_t WriteHeaders(
      const SpdyHeaderBlock& header_block,
      bool fin,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  
  
  virtual size_t Readv(const struct iovec* iov, size_t iov_len);
  virtual int GetReadableRegions(iovec* iov, size_t iov_len);
  
  virtual bool IsDoneReading() const;
  virtual bool HasBytesToRead() const;

  void set_visitor(Visitor* visitor) { visitor_ = visitor; }

  bool headers_decompressed() const { return headers_decompressed_; }

  const IPEndPoint& GetPeerAddress();

  
  bool GetSSLInfo(SSLInfo* ssl_info);

 protected:
  
  // written to the server.
  void set_priority(QuicPriority priority);
  
  
  QuicPriority priority() const { return priority_; }

 private:
  friend class test::QuicDataStreamPeer;
  friend class test::ReliableQuicStreamPeer;
  friend class QuicStreamUtils;

  uint32 ProcessHeaderData();

  bool FinishedReadingHeaders();

  Visitor* visitor_;
  
  bool headers_decompressed_;
  
  QuicPriority priority_;
  
  
  string decompressed_headers_;
  
  bool decompression_failed_;
  
  bool priority_parsed_;

  DISALLOW_COPY_AND_ASSIGN(QuicDataStream);
};

}  

#endif  
