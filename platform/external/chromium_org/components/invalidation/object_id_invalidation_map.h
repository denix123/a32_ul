// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_OBJECT_ID_INVALIDATION_MAP_H_
#define COMPONENTS_INVALIDATION_OBJECT_ID_INVALIDATION_MAP_H_

#include <map>
#include <vector>

#include "components/invalidation/invalidation.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/single_object_invalidation_set.h"

namespace syncer {

class INVALIDATION_EXPORT ObjectIdInvalidationMap {
  public:
   
   
   static ObjectIdInvalidationMap InvalidateAll(const ObjectIdSet& ids);

   ObjectIdInvalidationMap();
   ~ObjectIdInvalidationMap();

   
   ObjectIdSet GetObjectIds() const;

   
   bool Empty() const;

   
   bool operator==(const ObjectIdInvalidationMap& other) const;

   
   void Insert(const Invalidation& invalidation);

   
   
   ObjectIdInvalidationMap GetSubsetWithObjectIds(const ObjectIdSet& ids) const;

   
   const SingleObjectInvalidationSet& ForObject(
       invalidation::ObjectId id) const;

   
   void GetAllInvalidations(std::vector<syncer::Invalidation>* out) const;

   
   void AcknowledgeAll() const;

   
   scoped_ptr<base::ListValue> ToValue() const;

   
   bool ResetFromValue(const base::ListValue& value);

   
   std::string ToString() const;

  private:
   typedef std::map<invalidation::ObjectId,
                    SingleObjectInvalidationSet,
                    ObjectIdLessThan> IdToListMap;

   ObjectIdInvalidationMap(const IdToListMap& map);

   IdToListMap map_;
};

}  

#endif  
