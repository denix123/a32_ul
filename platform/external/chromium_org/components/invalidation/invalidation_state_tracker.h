// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_STATE_TRACKER_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_STATE_TRACKER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "components/invalidation/invalidation.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/unacked_invalidation_set.h"
#include "google/cacheinvalidation/include/types.h"

namespace base {
class TaskRunner;
}  

namespace syncer {

class INVALIDATION_EXPORT InvalidationStateTracker {
 public:
  InvalidationStateTracker();
  virtual ~InvalidationStateTracker();

  
  
  
  
  virtual void ClearAndSetNewClientId(const std::string& data) = 0;
  virtual std::string GetInvalidatorClientId() const = 0;

  
  
  
  
  virtual void SetBootstrapData(const std::string& data) = 0;
  virtual std::string GetBootstrapData() const = 0;

  
  
  
  virtual void SetSavedInvalidations(const UnackedInvalidationsMap& states) = 0;
  virtual UnackedInvalidationsMap GetSavedInvalidations() const = 0;

  
  virtual void Clear() = 0;
};

}  

#endif  
