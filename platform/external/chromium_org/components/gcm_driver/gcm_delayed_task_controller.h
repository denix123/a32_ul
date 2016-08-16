// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_DELAYED_TASK_CONTROLLER_H_
#define COMPONENTS_GCM_DRIVER_GCM_DELAYED_TASK_CONTROLLER_H_

#include <vector>

#include "base/callback.h"

namespace gcm {

class GCMDelayedTaskController {
 public:
  GCMDelayedTaskController();
  ~GCMDelayedTaskController();

  
  void AddTask(const base::Closure& task);

  
  void SetReady();

  
  bool CanRunTaskWithoutDelay() const;

 private:
  void RunTasks();

  
  bool ready_;

  std::vector<base::Closure> delayed_tasks_;

  DISALLOW_COPY_AND_ASSIGN(GCMDelayedTaskController);
};

}  

#endif  
