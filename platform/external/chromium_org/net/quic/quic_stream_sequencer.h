// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_STREAM_SEQUENCER_H_
#define NET_QUIC_QUIC_STREAM_SEQUENCER_H_

#include <map>

#include "base/basictypes.h"
#include "net/base/iovec.h"
#include "net/quic/quic_protocol.h"

using std::map;
using std::string;

namespace net {

namespace test {
class QuicStreamSequencerPeer;
}  

class QuicSession;
class ReliableQuicStream;

class NET_EXPORT_PRIVATE QuicStreamSequencer {
 public:
  explicit QuicStreamSequencer(ReliableQuicStream* quic_stream);
  virtual ~QuicStreamSequencer();

  
  
  
  
  
  void OnStreamFrame(const QuicStreamFrame& frame);

  
  

  
  
  int GetReadableRegions(iovec* iov, size_t iov_len);

  
  
  int Readv(const struct iovec* iov, size_t iov_len);

  
  bool HasBytesToRead() const;

  
  bool IsClosed() const;

  
  bool IsDuplicate(const QuicStreamFrame& frame) const;

  
  
  bool FrameOverlapsBufferedData(const QuicStreamFrame& frame) const;

  
  
  void FlushBufferedFrames();

  
  void SetBlockedUntilFlush();

  size_t num_bytes_buffered() const { return num_bytes_buffered_; }
  QuicStreamOffset num_bytes_consumed() const { return num_bytes_consumed_; }

  int num_frames_received() const { return num_frames_received_; }

  int num_duplicate_frames_received() const {
    return num_duplicate_frames_received_;
  }

 private:
  friend class test::QuicStreamSequencerPeer;

  
  void CloseStreamAtOffset(QuicStreamOffset offset);

  
  
  bool MaybeCloseStream();

  
  
  void RecordBytesConsumed(size_t bytes_consumed);

  
  ReliableQuicStream* stream_;

  
  QuicStreamOffset num_bytes_consumed_;

  
  
  
  
  
  typedef map<QuicStreamOffset, string> FrameMap;

  
  FrameMap buffered_frames_;

  
  
  QuicStreamOffset close_offset_;

  
  
  bool blocked_;

  
  size_t num_bytes_buffered_;

  
  int num_frames_received_;

  
  int num_duplicate_frames_received_;

  DISALLOW_COPY_AND_ASSIGN(QuicStreamSequencer);
};

}  

#endif  
