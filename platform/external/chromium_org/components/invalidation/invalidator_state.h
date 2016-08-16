// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATOR_STATE_H_
#define COMPONENTS_INVALIDATION_INVALIDATOR_STATE_H_

#include "components/invalidation/invalidation_export.h"

namespace syncer {

enum InvalidatorState {
  
  
  
  
  TRANSIENT_INVALIDATION_ERROR,
  DEFAULT_INVALIDATION_ERROR = TRANSIENT_INVALIDATION_ERROR,
  
  INVALIDATION_CREDENTIALS_REJECTED,

  
  INVALIDATIONS_ENABLED
};

INVALIDATION_EXPORT const char* InvalidatorStateToString(
    InvalidatorState state);

}  

#endif  
