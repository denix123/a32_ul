// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_BLOOM_FILTER_H_
#define COMPONENTS_RAPPOR_BLOOM_FILTER_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "components/rappor/byte_vector_utils.h"

namespace rappor {

class BloomFilter {
 public:
  
  
  
  
  BloomFilter(uint32_t bytes_size,
              uint32_t hash_function_count,
              uint32_t hash_seed_offset);
  ~BloomFilter();

  
  void SetString(const std::string& str);

  
  const ByteVector& bytes() const { return bytes_; };

  
  void SetBytesForTesting(const ByteVector& bytes);

 private:
  
  ByteVector bytes_;

  
  uint32_t hash_function_count_;

  
  uint32_t hash_seed_offset_;

  DISALLOW_COPY_AND_ASSIGN(BloomFilter);
};

}  

#endif  
