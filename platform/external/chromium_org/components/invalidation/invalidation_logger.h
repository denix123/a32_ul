// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_LOGGER_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_LOGGER_H_

#include <map>
#include <set>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/invalidator_state.h"

namespace base {
class DictionaryValue;
}  

namespace syncer {
class InvalidationHandler;
class ObjectIdInvalidationMap;
}  

namespace invalidation {

class InvalidationLoggerObserver;


class InvalidationLogger {

 public:
  InvalidationLogger();
  ~InvalidationLogger();

  
  
  void OnRegistration(const std::string& details);
  void OnUnregistration(const std::string& details);
  void OnStateChange(const syncer::InvalidatorState& new_state);
  void OnUpdateIds(std::map<std::string, syncer::ObjectIdSet> updated_ids);
  void OnDebugMessage(const base::DictionaryValue& details);
  void OnInvalidation(const syncer::ObjectIdInvalidationMap& details);

  
  
  void EmitContent();

  
  void RegisterObserver(InvalidationLoggerObserver* debug_observer);
  void UnregisterObserver(InvalidationLoggerObserver* debug_observer);
  bool IsObserverRegistered(InvalidationLoggerObserver* debug_observer);

 private:
  
  void EmitState();

  
  
  void EmitUpdatedIds();

  
  
  void EmitRegisteredHandlers();

  
  ObserverList<InvalidationLoggerObserver> observer_list_;

  
  syncer::InvalidatorState last_invalidator_state_;
  base::Time last_invalidator_state_timestamp_;

  
  
  std::map<std::string, syncer::ObjectIdSet> latest_ids_;

  
  syncer::ObjectIdCountMap invalidation_count_;

  
  
  
  std::multiset<std::string> registered_handlers_;

  DISALLOW_COPY_AND_ASSIGN(InvalidationLogger);
};

}  

#endif  
