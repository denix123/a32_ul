// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_RESOURCE_MANAGER_PUBLIC_RESOURCE_MANAGER_DLEGATE_H_
#define ATHENA_RESOURCE_MANAGER_PUBLIC_RESOURCE_MANAGER_DLEGATE_H_

#include <string>

#include "athena/athena_export.h"
#include "base/macros.h"

namespace athena {

class ATHENA_EXPORT ResourceManagerDelegate {
 public:
  static ResourceManagerDelegate* CreateResourceManagerDelegate();

  ResourceManagerDelegate() {}
  virtual ~ResourceManagerDelegate() {}

  
  virtual int GetUsedMemoryInPercent() = 0;

  
  
  
  virtual int MemoryPressureIntervalInMS() = 0;
};

}  

#endif  
