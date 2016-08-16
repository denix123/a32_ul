// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_CLONED_INSTALL_DETECTOR_H_
#define COMPONENTS_METRICS_CLONED_INSTALL_DETECTOR_H_

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"

class PrefRegistrySimple;
class PrefService;

namespace base {
class SingleThreadTaskRunner;
}

namespace metrics {

class MachineIdProvider;

class ClonedInstallDetector {
 public:
  explicit ClonedInstallDetector(MachineIdProvider* raw_id_provider);
  virtual ~ClonedInstallDetector();

  
  
  
  
  
  
  void CheckForClonedInstall(
      PrefService* local_state,
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  FRIEND_TEST_ALL_PREFIXES(ClonedInstallDetectorTest, SaveId);
  FRIEND_TEST_ALL_PREFIXES(ClonedInstallDetectorTest, DetectClone);

  
  
  
  void SaveMachineId(PrefService* local_state, std::string raw_id);

  scoped_refptr<MachineIdProvider> raw_id_provider_;
  base::WeakPtrFactory<ClonedInstallDetector> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ClonedInstallDetector);
};

}  

#endif  
