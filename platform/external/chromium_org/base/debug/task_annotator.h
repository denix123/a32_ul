// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_DEBUG_TASK_ANNOTATOR_H_
#define BASE_DEBUG_TASK_ANNOTATOR_H_

#include "base/base_export.h"
#include "base/basictypes.h"

namespace base {
struct PendingTask;
namespace debug {

class BASE_EXPORT TaskAnnotator {
 public:
  TaskAnnotator();
  ~TaskAnnotator();

  
  
  void DidQueueTask(const char* queue_function,
                    const PendingTask& pending_task);

  
  
  
  void RunTask(const char* queue_function,
               const char* run_function,
               const PendingTask& pending_task);

 private:
  
  
  
  uint64 GetTaskTraceID(const PendingTask& task) const;

  DISALLOW_COPY_AND_ASSIGN(TaskAnnotator);
};

}  
}  

#endif  
