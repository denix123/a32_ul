// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_RAPPOR_METRIC_H_
#define COMPONENTS_RAPPOR_RAPPOR_METRIC_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "components/rappor/bloom_filter.h"
#include "components/rappor/byte_vector_utils.h"
#include "components/rappor/rappor_parameters.h"

namespace rappor {

class RapporMetric {
 public:
  
  
  
  
  RapporMetric(const std::string& metric_name,
               const RapporParameters& parameters,
               int32_t cohort);
  ~RapporMetric();

  
  
  
  void AddSample(const std::string& str);

  
  const ByteVector& bytes() const { return bloom_filter_.bytes(); }

  
  const RapporParameters& parameters() const { return parameters_; }

  
  
  
  ByteVector GetReport(const std::string& secret) const;

  
  void SetBytesForTesting(const ByteVector& bytes);

 private:
  const std::string metric_name_;
  const RapporParameters parameters_;
  uint32_t sample_count_;
  BloomFilter bloom_filter_;

  DISALLOW_COPY_AND_ASSIGN(RapporMetric);
};

}  

#endif  
