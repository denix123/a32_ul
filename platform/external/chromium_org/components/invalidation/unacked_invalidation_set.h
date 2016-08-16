// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_UNACKED_INVALIDATION_SET_H_
#define COMPONENTS_INVALIDATION_UNACKED_INVALIDATION_SET_H_

#include <set>

#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "components/invalidation/invalidation.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"

namespace base {
class DictionaryValue;
}  

namespace syncer {

namespace test_util {
class UnackedInvalidationSetEqMatcher;
}  

class SingleObjectInvalidationSet;
class ObjectIdInvalidationMap;
class AckHandle;

class INVALIDATION_EXPORT UnackedInvalidationSet {
 public:
  static const size_t kMaxBufferedInvalidations;

  UnackedInvalidationSet(invalidation::ObjectId id);
  UnackedInvalidationSet(const UnackedInvalidationSet& other);
  ~UnackedInvalidationSet();

  
  const invalidation::ObjectId& object_id() const;

  
  void Add(const Invalidation& invalidation);

  
  void AddSet(const SingleObjectInvalidationSet& invalidations);

  
  
  
  
  
  
  
  void ExportInvalidations(
      base::WeakPtr<AckHandler> ack_handler,
      scoped_refptr<base::SingleThreadTaskRunner> ack_handler_task_runner,
      ObjectIdInvalidationMap* out) const;

  
  void Clear();

  
  
  
  
  
  
  
  
  
  
  
  void SetHandlerIsRegistered();

  
  
  
  
  void SetHandlerIsUnregistered();

  
  
  
  void Acknowledge(const AckHandle& handle);

  
  
  
  void Drop(const AckHandle& handle);

  scoped_ptr<base::DictionaryValue> ToValue() const;
  bool ResetFromValue(const base::DictionaryValue& value);

 private:
  
  friend class test_util::UnackedInvalidationSetEqMatcher;

  typedef std::set<Invalidation, InvalidationVersionLessThan> InvalidationsSet;

  bool ResetListFromValue(const base::ListValue& value);

  
  
  
  void Truncate(size_t max_size);

  bool registered_;
  invalidation::ObjectId object_id_;
  InvalidationsSet invalidations_;
};

typedef std::map<invalidation::ObjectId,
                 UnackedInvalidationSet,
                 ObjectIdLessThan> UnackedInvalidationsMap;

}  

#endif  
