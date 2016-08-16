// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_SURFACES_SURFACE_ID_ALLOCATOR_H_
#define CC_SURFACES_SURFACE_ID_ALLOCATOR_H_

#include "cc/surfaces/surface_id.h"
#include "cc/surfaces/surfaces_export.h"

namespace cc {

class CC_SURFACES_EXPORT SurfaceIdAllocator {
 public:
  explicit SurfaceIdAllocator(uint32_t id_namespace);

  SurfaceId GenerateId();

  static uint32_t NamespaceForId(SurfaceId id);

 private:
  uint32_t id_namespace_;
  uint32_t next_id_;

  DISALLOW_COPY_AND_ASSIGN(SurfaceIdAllocator);
};

}  

#endif  
