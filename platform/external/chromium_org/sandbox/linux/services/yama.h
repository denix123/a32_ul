// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SERVICES_YAMA_H_
#define SANDBOX_LINUX_SERVICES_YAMA_H_

#include "base/basictypes.h"
#include "base/process/process_handle.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT Yama {
 public:
  
  
  enum GlobalStatus {
    STATUS_KNOWN = 1 << 0,
    STATUS_PRESENT = 1 << 1,
    STATUS_ENFORCING = 1 << 2,
    
    
    
    STATUS_STRICT_ENFORCING = 1 << 3
  };

  
  
  
  static bool RestrictPtracersToAncestors();

  
  
  
  
  static bool DisableYamaRestrictions();

  
  
  
  static int GetStatus();

  
  static bool IsPresent();
  
  static bool IsEnforcing();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Yama);
};

}  

#endif  
