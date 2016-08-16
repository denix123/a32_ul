// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_STREAM_PARSER_BUFFER_H_
#define MEDIA_BASE_STREAM_PARSER_BUFFER_H_

#include <deque>

#include "media/base/decoder_buffer.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_export.h"
#include "media/base/stream_parser.h"

namespace media {

class DecodeTimestamp {
 public:
  DecodeTimestamp() {}
  DecodeTimestamp(const DecodeTimestamp& rhs) : ts_(rhs.ts_) { }
  DecodeTimestamp& operator=(const DecodeTimestamp& rhs) {
    if (&rhs != this)
      ts_ = rhs.ts_;
    return *this;
  }

  
  
  bool operator<(const DecodeTimestamp& rhs) const { return ts_ < rhs.ts_; }
  bool operator>(const DecodeTimestamp& rhs) const  { return ts_ > rhs.ts_; }
  bool operator==(const DecodeTimestamp& rhs) const  { return ts_ == rhs.ts_; }
  bool operator!=(const DecodeTimestamp& rhs) const  { return ts_ != rhs.ts_; }
  bool operator>=(const DecodeTimestamp& rhs) const  { return ts_ >= rhs.ts_; }
  bool operator<=(const DecodeTimestamp& rhs) const  { return ts_ <= rhs.ts_; }

  base::TimeDelta operator-(const DecodeTimestamp& rhs) const {
    return ts_ - rhs.ts_;
  }

  DecodeTimestamp& operator+=(const base::TimeDelta& rhs) {
    ts_ += rhs;
    return *this;
  }

  DecodeTimestamp& operator-=(const base::TimeDelta& rhs)  {
    ts_ -= rhs;
    return *this;
  }

  DecodeTimestamp operator+(const base::TimeDelta& rhs) const {
    return DecodeTimestamp(ts_ + rhs);
  }

  DecodeTimestamp operator-(const base::TimeDelta& rhs) const {
    return DecodeTimestamp(ts_ - rhs);
  }

  int64 operator/(const base::TimeDelta& rhs) const {
    return ts_ / rhs;
  }

  static DecodeTimestamp FromSecondsD(double seconds) {
    return DecodeTimestamp(base::TimeDelta::FromSecondsD(seconds));
  }

  static DecodeTimestamp FromMilliseconds(int64 milliseconds) {
    return DecodeTimestamp(base::TimeDelta::FromMilliseconds(milliseconds));
  }

  static DecodeTimestamp FromMicroseconds(int64 microseconds) {
    return DecodeTimestamp(base::TimeDelta::FromMicroseconds(microseconds));
  }

  
  
  static DecodeTimestamp FromPresentationTime(base::TimeDelta timestamp) {
    return DecodeTimestamp(timestamp);
  }

  double InSecondsF() const { return ts_.InSecondsF(); }
  int64 InMilliseconds() const { return ts_.InMilliseconds(); }
  int64 InMicroseconds() const { return ts_.InMicroseconds(); }

  
  
  base::TimeDelta ToPresentationTime() const { return ts_; }

 private:
  explicit DecodeTimestamp(base::TimeDelta timestamp) : ts_(timestamp) { }

  base::TimeDelta ts_;
};

MEDIA_EXPORT extern inline DecodeTimestamp kNoDecodeTimestamp() {
  return DecodeTimestamp::FromPresentationTime(kNoTimestamp());
}

class MEDIA_EXPORT StreamParserBuffer : public DecoderBuffer {
 public:
  
  enum { kInvalidConfigId = -1 };

  typedef DemuxerStream::Type Type;
  typedef StreamParser::TrackId TrackId;

  static scoped_refptr<StreamParserBuffer> CreateEOSBuffer();

  static scoped_refptr<StreamParserBuffer> CopyFrom(
      const uint8* data, int data_size, bool is_keyframe, Type type,
      TrackId track_id);
  static scoped_refptr<StreamParserBuffer> CopyFrom(
      const uint8* data, int data_size,
      const uint8* side_data, int side_data_size, bool is_keyframe, Type type,
      TrackId track_id);
  bool IsKeyframe() const { return is_keyframe_; }

  
  
  DecodeTimestamp GetDecodeTimestamp() const;
  void SetDecodeTimestamp(DecodeTimestamp timestamp);

  
  int GetConfigId() const;
  void SetConfigId(int config_id);

  
  
  
  int GetSpliceBufferConfigId(size_t index) const;

  
  
  Type type() const { return type_; }

  
  
  TrackId track_id() const { return track_id_; }

  
  
  
  
  
  
  
  
  
  
  typedef StreamParser::BufferQueue BufferQueue;
  void ConvertToSpliceBuffer(const BufferQueue& pre_splice_buffers);
  const BufferQueue& splice_buffers() const { return splice_buffers_; }

  
  
  
  
  
  
  
  
  
  
  void SetPrerollBuffer(const scoped_refptr<StreamParserBuffer>& preroll);
  const scoped_refptr<StreamParserBuffer>& preroll_buffer() {
    return preroll_buffer_;
  }

  virtual void set_timestamp(base::TimeDelta timestamp) OVERRIDE;

 private:
  StreamParserBuffer(const uint8* data, int data_size,
                     const uint8* side_data, int side_data_size,
                     bool is_keyframe, Type type,
                     TrackId track_id);
  virtual ~StreamParserBuffer();

  bool is_keyframe_;
  DecodeTimestamp decode_timestamp_;
  int config_id_;
  Type type_;
  TrackId track_id_;
  BufferQueue splice_buffers_;
  scoped_refptr<StreamParserBuffer> preroll_buffer_;

  DISALLOW_COPY_AND_ASSIGN(StreamParserBuffer);
};

}  

#endif  
