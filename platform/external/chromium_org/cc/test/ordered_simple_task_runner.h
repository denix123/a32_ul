// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TEST_ORDERED_SIMPLE_TASK_RUNNER_H_
#define CC_TEST_ORDERED_SIMPLE_TASK_RUNNER_H_

#include <limits>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/debug/trace_event.h"
#include "base/logging.h"
#include "base/test/test_simple_task_runner.h"
#include "cc/test/test_now_source.h"

namespace cc {

class TestOrderablePendingTask : public base::TestPendingTask {
 public:
  TestOrderablePendingTask();
  TestOrderablePendingTask(const tracked_objects::Location& location,
                           const base::Closure& task,
                           base::TimeTicks post_time,
                           base::TimeDelta delay,
                           TestNestability nestability);
  ~TestOrderablePendingTask();

  
  bool operator==(const TestOrderablePendingTask& other) const;
  bool operator<(const TestOrderablePendingTask& other) const;

  
  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  void AsValueInto(base::debug::TracedValue* state) const;

 private:
  static size_t task_id_counter;
  const size_t task_id_;
};

class OrderedSimpleTaskRunner : public base::SingleThreadTaskRunner {
 public:
  OrderedSimpleTaskRunner();
  OrderedSimpleTaskRunner(scoped_refptr<TestNowSource> now_src,
                          bool advance_now);

  
  virtual bool PostDelayedTask(const tracked_objects::Location& from_here,
                               const base::Closure& task,
                               base::TimeDelta delay) OVERRIDE;
  virtual bool PostNonNestableDelayedTask(
      const tracked_objects::Location& from_here,
      const base::Closure& task,
      base::TimeDelta delay) OVERRIDE;

  virtual bool RunsTasksOnCurrentThread() const OVERRIDE;

  
  
  static const size_t kAbsoluteMaxTasks;
  void SetRunTaskLimit(size_t max_tasks) { max_tasks_ = max_tasks; }
  void ClearRunTaskLimit() { max_tasks_ = kAbsoluteMaxTasks; }

  
  void SetAutoAdvanceNowToPendingTasks(bool advance_now) {
    advance_now_ = advance_now;
  }

  base::TimeTicks NextTaskTime();
  base::TimeDelta DelayToNextTaskTime();

  
  
  bool RunTasksWhile(base::Callback<bool(void)> condition);

  
  
  
  
  
  bool RunTasksWhile(
      const std::vector<base::Callback<bool(void)> >& conditions);

  

  
  
  bool RunPendingTasks();
  
  
  
  bool RunUntilIdle();
  
  
  bool RunUntilTime(base::TimeTicks time);
  bool RunForPeriod(base::TimeDelta period);

  
  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  virtual void AsValueInto(base::debug::TracedValue* state) const;

  
  
  

  
  
  
  
  base::Callback<bool(void)> TaskRunCountBelow(size_t max_tasks);

  
  base::Callback<bool(void)> TaskExistedInitially();

  
  base::Callback<bool(void)> NowBefore(base::TimeTicks stop_at);

  
  base::Callback<bool(void)> AdvanceNow();

 protected:
  static bool TaskRunCountBelowCallback(size_t max_tasks, size_t* task_run);
  bool TaskExistedInitiallyCallback(
      const std::set<TestOrderablePendingTask>& existing_tasks);
  bool NowBeforeCallback(base::TimeTicks stop_at);
  bool AdvanceNowCallback();

  virtual ~OrderedSimpleTaskRunner();

  base::ThreadChecker thread_checker_;

  bool advance_now_;
  scoped_refptr<TestNowSource> now_src_;

  size_t max_tasks_;

  bool inside_run_tasks_until_;
  std::set<TestOrderablePendingTask> pending_tasks_;

 private:
  DISALLOW_COPY_AND_ASSIGN(OrderedSimpleTaskRunner);
};

}  

#endif  
