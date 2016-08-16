// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_SURFACES_SURFACE_RESOURCE_HOLDER_H_
#define CC_SURFACES_SURFACE_RESOURCE_HOLDER_H_

#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "cc/resources/resource_provider.h"
#include "cc/resources/returned_resource.h"
#include "cc/surfaces/surfaces_export.h"

namespace cc {
class SurfaceFactoryClient;

class CC_SURFACES_EXPORT SurfaceResourceHolder {
 public:
  explicit SurfaceResourceHolder(SurfaceFactoryClient* client);
  ~SurfaceResourceHolder();

  void ReceiveFromChild(const TransferableResourceArray& resources);
  void RefResources(const TransferableResourceArray& resources);
  void UnrefResources(const ReturnedResourceArray& resources);

 private:
  SurfaceFactoryClient* client_;

  struct ResourceRefs {
    ResourceRefs();

    int refs_received_from_child;
    int refs_holding_resource_alive;
  };
  
  
  
  typedef base::hash_map<ResourceProvider::ResourceId, ResourceRefs>
      ResourceIdCountMap;
  ResourceIdCountMap resource_id_use_count_map_;

  DISALLOW_COPY_AND_ASSIGN(SurfaceResourceHolder);
};

}  

#endif  
