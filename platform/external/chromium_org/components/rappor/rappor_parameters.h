// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_RAPPOR_PARAMETERS_H_
#define COMPONENTS_RAPPOR_RAPPOR_PARAMETERS_H_

#include <string>

namespace rappor {

enum Probability {
  PROBABILITY_75,    
  PROBABILITY_50,    
  PROBABILITY_25,    
};

struct RapporParameters {
  
  std::string ToString() const;

  
  static const int kMaxCohorts;

  
  int num_cohorts;

  
  int bloom_filter_size_bytes;
  
  int bloom_filter_hash_function_count;

  
  Probability fake_prob;
  
  Probability fake_one_prob;

  
  Probability one_coin_prob;
  
  Probability zero_coin_prob;
};

}  

#endif  
