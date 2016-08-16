// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_RELIABLE_QUIC_STREAM_H_
#define NET_QUIC_RELIABLE_QUIC_STREAM_H_

#include <sys/types.h>

#include <list>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string_piece.h"
#include "net/base/iovec.h"
#include "net/base/net_export.h"
#include "net/quic/quic_ack_notifier.h"
#include "net/quic/quic_flow_controller.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_stream_sequencer.h"
#include "net/quic/quic_types.h"

namespace net {

namespace test {
class ReliableQuicStreamPeer;
}  

class QuicSession;

class NET_EXPORT_PRIVATE ReliableQuicStream {
 public:
  ReliableQuicStream(QuicStreamId id,
                     QuicSession* session);

  virtual ~ReliableQuicStream();

  
  
  virtual void OnStreamFrame(const QuicStreamFrame& frame);

  
  
  virtual void OnCanWrite();

  
  virtual void OnClose();

  
  virtual void OnStreamReset(const QuicRstStreamFrame& frame);

  
  
  
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer);

  
  virtual void OnFinRead();

  virtual uint32 ProcessRawData(const char* data, uint32 data_len) = 0;

  
  virtual void Reset(QuicRstStreamErrorCode error);

  
  virtual void CloseConnection(QuicErrorCode error);
  virtual void CloseConnectionWithDetails(QuicErrorCode error,
                                          const string& details);

  
  
  virtual QuicPriority EffectivePriority() const = 0;

  QuicStreamId id() const { return id_; }

  QuicRstStreamErrorCode stream_error() const { return stream_error_; }
  QuicErrorCode connection_error() const { return connection_error_; }

  bool read_side_closed() const { return read_side_closed_; }
  bool write_side_closed() const { return write_side_closed_; }

  uint64 stream_bytes_read() const { return stream_bytes_read_; }
  uint64 stream_bytes_written() const { return stream_bytes_written_; }

  QuicVersion version() const;

  void set_fin_sent(bool fin_sent) { fin_sent_ = fin_sent; }
  void set_rst_sent(bool rst_sent) { rst_sent_ = rst_sent; }

  void set_fec_policy(FecPolicy fec_policy) { fec_policy_ = fec_policy; }
  FecPolicy fec_policy() const { return fec_policy_; }

  
  virtual void OnWindowUpdateFrame(const QuicWindowUpdateFrame& frame);

  int num_frames_received() const;

  int num_duplicate_frames_received() const;

  QuicFlowController* flow_controller() { return &flow_controller_; }

  
  
  bool MaybeIncreaseHighestReceivedOffset(uint64 new_offset);
  
  void AddBytesSent(uint64 bytes);
  
  
  
  void AddBytesConsumed(uint64 bytes);

  
  
  void UpdateSendWindowOffset(uint64 new_offset);

  
  
  bool IsFlowControlBlocked();

  
  
  
  
  bool HasFinalReceivedByteOffset() const {
    return fin_received_ || rst_received_;
  }

  
  bool HasBufferedData() const;

 protected:
  
  
  void WriteOrBufferData(
      base::StringPiece data,
      bool fin,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  
  
  
  
  QuicConsumedData WritevData(
      const struct iovec* iov,
      int iov_count,
      bool fin,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  FecProtection GetFecProtection();

  
  virtual void CloseReadSide();

  
  void CloseWriteSide();

  bool fin_buffered() const { return fin_buffered_; }

  const QuicSession* session() const { return session_; }
  QuicSession* session() { return session_; }

  const QuicStreamSequencer* sequencer() const { return &sequencer_; }
  QuicStreamSequencer* sequencer() { return &sequencer_; }

  
  void DisableFlowControl() {
    flow_controller_.Disable();
  }

  void DisableConnectionFlowControlForThisStream() {
    stream_contributes_to_connection_flow_control_ = false;
  }

 private:
  friend class test::ReliableQuicStreamPeer;
  friend class QuicStreamUtils;
  class ProxyAckNotifierDelegate;

  struct PendingData {
    PendingData(string data_in,
                scoped_refptr<ProxyAckNotifierDelegate> delegate_in);
    ~PendingData();

    string data;
    
    
    scoped_refptr<ProxyAckNotifierDelegate> delegate;
  };

  
  
  
  void MaybeSendBlocked();

  std::list<PendingData> queued_data_;

  QuicStreamSequencer sequencer_;
  QuicStreamId id_;
  QuicSession* session_;
  // Bytes read and written refer to payload bytes only: they do not include
  
  uint64 stream_bytes_read_;
  uint64 stream_bytes_written_;

  
  
  QuicRstStreamErrorCode stream_error_;
  
  
  
  QuicErrorCode connection_error_;

  
  bool read_side_closed_;
  
  bool write_side_closed_;

  bool fin_buffered_;
  bool fin_sent_;

  
  
  bool fin_received_;

  
  
  bool rst_sent_;

  
  bool rst_received_;

  
  FecPolicy fec_policy_;

  
  bool is_server_;

  QuicFlowController flow_controller_;

  
  QuicFlowController* connection_flow_controller_;

  
  
  
  bool stream_contributes_to_connection_flow_control_;

  DISALLOW_COPY_AND_ASSIGN(ReliableQuicStream);
};

}  

#endif  
