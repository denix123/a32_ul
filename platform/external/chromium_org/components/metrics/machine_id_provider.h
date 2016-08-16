// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_MACHINE_ID_PROVIDER_H_
#define COMPONENTS_METRICS_MACHINE_ID_PROVIDER_H_

#include <string>

#include "base/macros.h"
#include "base/memory/ref_counted.h"

namespace metrics {

class MachineIdProvider : public base::RefCountedThreadSafe<MachineIdProvider> {
 public:
  
  
  
  
  std::string GetMachineId();

  
  
  
  static MachineIdProvider* CreateInstance();

 private:
  friend class base::RefCountedThreadSafe<MachineIdProvider>;

  MachineIdProvider();
  virtual ~MachineIdProvider();

  DISALLOW_COPY_AND_ASSIGN(MachineIdProvider);
};

}  

#endif  
