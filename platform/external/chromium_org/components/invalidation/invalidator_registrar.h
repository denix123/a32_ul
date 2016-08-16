// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATOR_REGISTRAR_H_
#define COMPONENTS_INVALIDATION_INVALIDATOR_REGISTRAR_H_

#include <map>

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "base/threading/thread_checker.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_handler.h"
#include "components/invalidation/invalidation_util.h"

namespace invalidation {
class ObjectId;
}  

namespace syncer {

class ObjectIdInvalidationMap;

class INVALIDATION_EXPORT InvalidatorRegistrar {
 public:
  InvalidatorRegistrar();

  
  ~InvalidatorRegistrar();

  
  
  void RegisterHandler(InvalidationHandler* handler);

  
  
  
  void UpdateRegisteredIds(InvalidationHandler* handler,
                           const ObjectIdSet& ids);

  
  
  
  void UnregisterHandler(InvalidationHandler* handler);

  ObjectIdSet GetRegisteredIds(InvalidationHandler* handler) const;

  
  
  ObjectIdSet GetAllRegisteredIds() const;

  
  
  
  
  void DispatchInvalidationsToHandlers(
      const ObjectIdInvalidationMap& invalidation_map);

  
  
  
  void UpdateInvalidatorState(InvalidatorState state);

  
  
  
  InvalidatorState GetInvalidatorState() const;

  
  
  
  std::map<std::string, ObjectIdSet> GetSanitizedHandlersIdsMap();

  bool IsHandlerRegisteredForTest(InvalidationHandler* handler) const;

  
  void DetachFromThreadForTest();

 private:
  typedef std::map<InvalidationHandler*, ObjectIdSet> HandlerIdsMap;

  base::ThreadChecker thread_checker_;
  ObserverList<InvalidationHandler, true> handlers_;
  HandlerIdsMap handler_to_ids_map_;
  InvalidatorState state_;

  DISALLOW_COPY_AND_ASSIGN(InvalidatorRegistrar);
};

}  

#endif  
