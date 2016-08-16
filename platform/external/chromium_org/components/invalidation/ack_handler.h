// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_ACK_HANDLER_H_
#define COMPONENTS_INVALIDATION_ACK_HANDLER_H_

#include <vector>

#include "components/invalidation/invalidation_export.h"

namespace invalidation {
class ObjectId;
}  

namespace syncer {

class AckHandle;

class INVALIDATION_EXPORT AckHandler {
 public:
  AckHandler();
  virtual ~AckHandler() = 0;

  
  virtual void Acknowledge(const invalidation::ObjectId& id,
                           const AckHandle& handle) = 0;

  
  virtual void Drop(const invalidation::ObjectId& id,
                    const AckHandle& handle) = 0;
};

}  

#endif  
