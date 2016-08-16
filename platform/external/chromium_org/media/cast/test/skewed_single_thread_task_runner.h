// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_TEST_SKEWED_TASK_RUNNER_H_
#define MEDIA_CAST_TEST_SKEWED_TASK_RUNNER_H_

#include <map>

#include "base/basictypes.h"
#include "base/single_thread_task_runner.h"
#include "base/test/simple_test_tick_clock.h"
#include "base/test/test_pending_task.h"

namespace media {
namespace cast {
namespace test {

class SkewedSingleThreadTaskRunner : public base::SingleThreadTaskRunner {
 public:
  explicit SkewedSingleThreadTaskRunner(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner);

  
  void SetSkew(double skew);

  
  virtual bool PostDelayedTask(const tracked_objects::Location& from_here,
                               const base::Closure& task,
                               base::TimeDelta delay) OVERRIDE;

  virtual bool RunsTasksOnCurrentThread() const OVERRIDE;

  
  virtual bool PostNonNestableDelayedTask(
      const tracked_objects::Location& from_here,
      const base::Closure& task,
      base::TimeDelta delay) OVERRIDE;

 protected:
  virtual ~SkewedSingleThreadTaskRunner();

 private:
  double skew_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(SkewedSingleThreadTaskRunner);
};

}  
}  
}  

#endif  
