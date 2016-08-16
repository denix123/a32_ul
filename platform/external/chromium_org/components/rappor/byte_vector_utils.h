// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_BYTE_VECTOR_UTILS_H_
#define COMPONENTS_RAPPOR_BYTE_VECTOR_UTILS_H_

#include <vector>

#include "base/basictypes.h"
#include "base/macros.h"
#include "components/rappor/rappor_parameters.h"
#include "crypto/hmac.h"

namespace rappor {

typedef std::vector<uint8_t> ByteVector;

ByteVector* ByteVectorAnd(const ByteVector& lhs, ByteVector* rhs);

ByteVector* ByteVectorOr(const ByteVector& lhs, ByteVector* rhs);

ByteVector* ByteVectorMerge(const ByteVector& mask,
                            const ByteVector& lhs,
                            ByteVector* rhs);

int CountBits(const ByteVector& vector);

class ByteVectorGenerator {
 public:
  explicit ByteVectorGenerator(size_t byte_count);

  virtual ~ByteVectorGenerator();

  
  
  ByteVector GetWeightedRandomByteVector(Probability probability);

 protected:
  
  size_t byte_count() const { return byte_count_; }

  
  virtual ByteVector GetRandomByteVector();

 private:
  size_t byte_count_;

  DISALLOW_COPY_AND_ASSIGN(ByteVectorGenerator);
};

class HmacByteVectorGenerator : public ByteVectorGenerator {
 public:
  
  
  
  HmacByteVectorGenerator(size_t byte_count,
                          const std::string& entropy_input,
                          const std::string& personalization_string);

  virtual ~HmacByteVectorGenerator();

  
  
  static std::string GenerateEntropyInput();

  
  static const size_t kEntropyInputSize;

 protected:
  
  
  explicit HmacByteVectorGenerator(const HmacByteVectorGenerator& prev_request);

  
  virtual ByteVector GetRandomByteVector() OVERRIDE;

 private:
  
  crypto::HMAC hmac_;

  
  ByteVector value_;

  
  size_t generated_bytes_;

  DISALLOW_ASSIGN(HmacByteVectorGenerator);
};

}  

#endif  
