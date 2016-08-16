// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_H264_BITSTREAM_BUFFER_H_
#define MEDIA_FILTERS_H264_BITSTREAM_BUFFER_H_

#include "base/gtest_prod_util.h"
#include "base/numerics/safe_conversions.h"
#include "media/base/media_export.h"
#include "media/base/video_frame.h"
#include "media/filters/h264_parser.h"

namespace media {

class MEDIA_EXPORT H264BitstreamBuffer {
 public:
  H264BitstreamBuffer();
  ~H264BitstreamBuffer();

  
  void Reset();

  
  
  template <typename T>
  void AppendBits(size_t num_bits, T val) {
    AppendU64(num_bits, static_cast<uint64>(val));
  }

  void AppendBits(size_t num_bits, bool val) {
    DCHECK_EQ(num_bits, 1ul);
    AppendBool(val);
  }

  
  void AppendBool(bool val);

  
  void AppendSE(int val);

  
  void AppendUE(unsigned int val);

  
  
  
  
  void BeginNALU(H264NALU::Type nalu_type, int nal_ref_idc);

  
  
  
  void FinishNALU();

  
  
  size_t BytesInBuffer();

  
  
  
  uint8* data();

 private:
  FRIEND_TEST_ALL_PREFIXES(H264BitstreamBufferAppendBitsTest,
                           AppendAndVerifyBits);

  
  void Grow();

  
  void AppendU64(size_t num_bits, uint64 val);

  
  
  void FlushReg();

  typedef uint64 RegType;
  enum {
    
    kRegByteSize = sizeof(RegType),
    kRegBitSize = kRegByteSize * 8,
    
    
    kGrowBytes = 4096,
  };

  COMPILE_ASSERT(kGrowBytes >= kRegByteSize,
                 kGrowBytes_must_be_larger_than_kRegByteSize);

  
  size_t bits_left_in_reg_;

  
  
  
  RegType reg_;

  
  size_t capacity_;

  // Current byte offset in data_ (points to the start of unwritten bits).
  size_t pos_;

  
  uint8* data_;
};

}  

#endif  
