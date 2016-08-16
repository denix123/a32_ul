// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_SINGLE_OBJECT_INVALIDATION_SET_H_
#define COMPONENTS_INVALIDATION_SINGLE_OBJECT_INVALIDATION_SET_H_

#include <set>

#include "base/memory/scoped_ptr.h"
#include "components/invalidation/invalidation.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"

namespace base {
class ListValue;
}  

namespace syncer {

class INVALIDATION_EXPORT SingleObjectInvalidationSet {
 public:
  typedef std::set<Invalidation, InvalidationVersionLessThan> InvalidationsSet;
  typedef InvalidationsSet::const_iterator const_iterator;
  typedef InvalidationsSet::const_reverse_iterator const_reverse_iterator;

  SingleObjectInvalidationSet();
  ~SingleObjectInvalidationSet();

  void Insert(const Invalidation& invalidation);
  void InsertAll(const SingleObjectInvalidationSet& other);
  void Clear();
  void Erase(const_iterator it);

  
  
  
  
  bool StartsWithUnknownVersion() const;
  size_t GetSize() const;
  bool IsEmpty() const;
  bool operator==(const SingleObjectInvalidationSet& other) const;

  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;
  const Invalidation& back() const;

  scoped_ptr<base::ListValue> ToValue() const;
  bool ResetFromValue(const base::ListValue& list);

 private:
  InvalidationsSet invalidations_;
};

}  

#endif  
