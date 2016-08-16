// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_HANDLER_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_HANDLER_H_

#include <string>

#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidator_state.h"

namespace syncer {

class ObjectIdInvalidationMap;

class INVALIDATION_EXPORT InvalidationHandler {
 public:
  InvalidationHandler();

  
  virtual void OnInvalidatorStateChange(InvalidatorState state) = 0;

  
  
  
  virtual void OnIncomingInvalidation(
      const ObjectIdInvalidationMap& invalidation_map) = 0;

  virtual std::string GetOwnerName() const = 0;

 protected:
  virtual ~InvalidationHandler();
};

}  

#endif  
