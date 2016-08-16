// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_OUTPUT_OVERLAY_CANDIDATE_VALIDATOR_H_
#define CC_OUTPUT_OVERLAY_CANDIDATE_VALIDATOR_H_

#include <vector>

#include "cc/base/cc_export.h"
#include "cc/output/overlay_candidate.h"

namespace cc {

class CC_EXPORT OverlayCandidateValidator {
 public:
  
  
  
  
  virtual void CheckOverlaySupport(OverlayCandidateList* surfaces) = 0;

  virtual ~OverlayCandidateValidator() {}
};

}  

#endif  
