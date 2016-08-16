// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_TEST_PENDING_TASK_H_
#define BASE_TEST_TEST_PENDING_TASK_H_

#include <string>

#include "base/callback.h"
#include "base/debug/trace_event_argument.h"
#include "base/location.h"
#include "base/time/time.h"

namespace base {


struct TestPendingTask {
  enum TestNestability { NESTABLE, NON_NESTABLE };

  TestPendingTask();
  TestPendingTask(const tracked_objects::Location& location,
                  const Closure& task,
                  TimeTicks post_time,
                  TimeDelta delay,
                  TestNestability nestability);
  ~TestPendingTask();

  
  TimeTicks GetTimeToRun() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool ShouldRunBefore(const TestPendingTask& other) const;

  tracked_objects::Location location;
  Closure task;
  TimeTicks post_time;
  TimeDelta delay;
  TestNestability nestability;

  
  
  void AsValueInto(base::debug::TracedValue* state) const;
  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  std::string ToString() const;
};

std::ostream& operator<<(std::ostream& os, const TestPendingTask& task);
void PrintTo(const TestPendingTask& task, std::ostream* os);

}  

#endif  
