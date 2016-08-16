// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_LOGGER_OBSERVER_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_LOGGER_OBSERVER_H_

#include "base/memory/scoped_ptr.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/invalidator_state.h"
#include "components/invalidation/object_id_invalidation_map.h"

namespace base {
class DictionaryValue;
}  

namespace syncer {
class InvalidationHandler;
class ObjectIdInvalidationMap;
}  

namespace invalidation {
class InvalidationLoggerObserver {
 public:
  virtual void OnRegistrationChange(
      const std::multiset<std::string>& registered_handlers) = 0;
  virtual void OnStateChange(const syncer::InvalidatorState& new_state,
                             const base::Time& last_change_timestamp) = 0;
  virtual void OnUpdateIds(const std::string& handler_name,
                           const syncer::ObjectIdCountMap& details) = 0;
  virtual void OnDebugMessage(const base::DictionaryValue& details) = 0;
  virtual void OnInvalidation(
      const syncer::ObjectIdInvalidationMap& details) = 0;
  virtual void OnDetailedStatus(const base::DictionaryValue& details) = 0;

 protected:
  virtual ~InvalidationLoggerObserver() {}
};

}  

#endif  
