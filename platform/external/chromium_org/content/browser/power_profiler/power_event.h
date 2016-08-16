// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_POWER_PROFILER_POWER_EVENT_H_
#define CONTENT_BROWSER_POWER_PROFILER_POWER_EVENT_H_

#include "base/time/time.h"

namespace content {

struct PowerEvent {
  enum Type {
    
    
    SOC_PACKAGE,

    
    DEVICE,

    
    ID_COUNT
  };

  Type type;

  base::TimeTicks time;  

  
  
  
  
  
  
  double value;
};

extern const char* kPowerTypeNames[];

}  

#endif  
