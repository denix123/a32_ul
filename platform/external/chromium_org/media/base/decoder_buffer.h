// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_DECODER_BUFFER_H_
#define MEDIA_BASE_DECODER_BUFFER_H_

#include <string>
#include <utility>

#include "base/logging.h"
#include "base/memory/aligned_memory.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "build/build_config.h"
#include "media/base/buffers.h"
#include "media/base/decrypt_config.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT DecoderBuffer
    : public base::RefCountedThreadSafe<DecoderBuffer> {
 public:
  enum {
    kPaddingSize = 32,
#if defined(ARCH_CPU_ARM_FAMILY)
    kAlignmentSize = 16
#else
    kAlignmentSize = 32
#endif
  };

  
  
  explicit DecoderBuffer(int size);

  
  
  static scoped_refptr<DecoderBuffer> CopyFrom(const uint8* data, int size);

  
  
  
  static scoped_refptr<DecoderBuffer> CopyFrom(const uint8* data, int size,
                                               const uint8* side_data,
                                               int side_data_size);

  
  
  
  
  static scoped_refptr<DecoderBuffer> CreateEOSBuffer();

  base::TimeDelta timestamp() const {
    DCHECK(!end_of_stream());
    return timestamp_;
  }

  
  
  virtual void set_timestamp(base::TimeDelta timestamp);

  base::TimeDelta duration() const {
    DCHECK(!end_of_stream());
    return duration_;
  }

  void set_duration(base::TimeDelta duration) {
    DCHECK(!end_of_stream());
    DCHECK(duration == kNoTimestamp() ||
           (duration >= base::TimeDelta() && duration != kInfiniteDuration()))
        << duration.InSecondsF();
    duration_ = duration;
  }

  const uint8* data() const {
    DCHECK(!end_of_stream());
    return data_.get();
  }

  uint8* writable_data() const {
    DCHECK(!end_of_stream());
    return data_.get();
  }

  int data_size() const {
    DCHECK(!end_of_stream());
    return size_;
  }

  const uint8* side_data() const {
    DCHECK(!end_of_stream());
    return side_data_.get();
  }

  int side_data_size() const {
    DCHECK(!end_of_stream());
    return side_data_size_;
  }

  
  
  
  
  
  typedef std::pair<base::TimeDelta, base::TimeDelta> DiscardPadding;
  const DiscardPadding& discard_padding() const {
    DCHECK(!end_of_stream());
    return discard_padding_;
  }

  void set_discard_padding(const DiscardPadding& discard_padding) {
    DCHECK(!end_of_stream());
    discard_padding_ = discard_padding;
  }

  const DecryptConfig* decrypt_config() const {
    DCHECK(!end_of_stream());
    return decrypt_config_.get();
  }

  void set_decrypt_config(scoped_ptr<DecryptConfig> decrypt_config) {
    DCHECK(!end_of_stream());
    decrypt_config_ = decrypt_config.Pass();
  }

  
  bool end_of_stream() const {
    return data_ == NULL;
  }

  
  
  base::TimeDelta splice_timestamp() const {
    DCHECK(!end_of_stream());
    return splice_timestamp_;
  }

  
  
  void set_splice_timestamp(base::TimeDelta splice_timestamp) {
    DCHECK(!end_of_stream());
    splice_timestamp_ = splice_timestamp;
  }

  
  std::string AsHumanReadableString();

 protected:
  friend class base::RefCountedThreadSafe<DecoderBuffer>;

  
  
  
  DecoderBuffer(const uint8* data, int size,
                const uint8* side_data, int side_data_size);
  virtual ~DecoderBuffer();

 private:
  base::TimeDelta timestamp_;
  base::TimeDelta duration_;

  int size_;
  scoped_ptr<uint8, base::AlignedFreeDeleter> data_;
  int side_data_size_;
  scoped_ptr<uint8, base::AlignedFreeDeleter> side_data_;
  scoped_ptr<DecryptConfig> decrypt_config_;
  DiscardPadding discard_padding_;
  base::TimeDelta splice_timestamp_;

  
  void Initialize();

  DISALLOW_COPY_AND_ASSIGN(DecoderBuffer);
};

}  

#endif  
