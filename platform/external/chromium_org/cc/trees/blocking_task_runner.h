// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_BLOCKING_TASK_RUNNER_H_
#define CC_TREES_BLOCKING_TASK_RUNNER_H_

#include <vector>

#include "base/location.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/synchronization/lock.h"
#include "base/threading/platform_thread.h"
#include "cc/base/cc_export.h"

namespace cc {

class CC_EXPORT BlockingTaskRunner {
 public:
  
  
  
  
  static scoped_ptr<BlockingTaskRunner> Create(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  ~BlockingTaskRunner();

  
  
  
  class CC_EXPORT CapturePostTasks {
   public:
    explicit CapturePostTasks(BlockingTaskRunner* blocking_runner);
    ~CapturePostTasks();

   private:
    BlockingTaskRunner* blocking_runner_;

    DISALLOW_COPY_AND_ASSIGN(CapturePostTasks);
  };

  
  
  bool BelongsToCurrentThread();

  
  
  
  
  bool PostTask(const tracked_objects::Location& from_here,
                const base::Closure& task);

 private:
  explicit BlockingTaskRunner(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  void SetCapture(bool capture);

  base::PlatformThreadId thread_id_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  base::Lock lock_;
  int capture_;
  std::vector<base::Closure> captured_tasks_;

  DISALLOW_COPY_AND_ASSIGN(BlockingTaskRunner);
};

}  

#endif  
