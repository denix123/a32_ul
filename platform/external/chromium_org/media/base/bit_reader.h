// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_BIT_READER_H_
#define MEDIA_BASE_BIT_READER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/bit_reader_core.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT BitReader
    : NON_EXPORTED_BASE(private BitReaderCore::ByteStreamProvider)  {
 public:
  
  
  BitReader(const uint8* data, int size);
  virtual ~BitReader();

  template<typename T> bool ReadBits(int num_bits, T* out) {
    return bit_reader_core_.ReadBits(num_bits, out);
  }

  bool ReadFlag(bool* flag) {
    return bit_reader_core_.ReadFlag(flag);
  }

  bool SkipBits(int num_bits) {
    return bit_reader_core_.SkipBits(num_bits);
  }

  int bits_available() const {
    return initial_size_ * 8 - bits_read();
  }

  int bits_read() const {
    return bit_reader_core_.bits_read();
  }

 private:
  
  virtual int GetBytes(int max_n, const uint8** out) OVERRIDE;

  
  const int initial_size_;

  
  const uint8* data_;

  
  int bytes_left_;

  BitReaderCore bit_reader_core_;

  DISALLOW_COPY_AND_ASSIGN(BitReader);
};

}  

#endif  