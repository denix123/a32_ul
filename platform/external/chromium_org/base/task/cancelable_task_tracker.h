// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TASK_CANCELABLE_TASK_TRACKER_H_
#define BASE_TASK_CANCELABLE_TASK_TRACKER_H_

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/weak_ptr.h"
#include "base/task_runner_util.h"
#include "base/threading/thread_checker.h"

namespace tracked_objects {
class Location;
}  

namespace base {

class CancellationFlag;
class TaskRunner;

class BASE_EXPORT CancelableTaskTracker {
 public:
  
  typedef int64 TaskId;
  static const TaskId kBadTaskId;

  typedef base::Callback<bool()> IsCanceledCallback;

  CancelableTaskTracker();

  
  ~CancelableTaskTracker();

  TaskId PostTask(base::TaskRunner* task_runner,
                  const tracked_objects::Location& from_here,
                  const base::Closure& task);

  TaskId PostTaskAndReply(base::TaskRunner* task_runner,
                          const tracked_objects::Location& from_here,
                          const base::Closure& task,
                          const base::Closure& reply);

  template <typename TaskReturnType, typename ReplyArgType>
  TaskId PostTaskAndReplyWithResult(
      base::TaskRunner* task_runner,
      const tracked_objects::Location& from_here,
      const base::Callback<TaskReturnType(void)>& task,
      const base::Callback<void(ReplyArgType)>& reply) {
    TaskReturnType* result = new TaskReturnType();
    return PostTaskAndReply(
        task_runner,
        from_here,
        base::Bind(&base::internal::ReturnAsParamAdapter<TaskReturnType>,
                   task,
                   base::Unretained(result)),
        base::Bind(&base::internal::ReplyAdapter<TaskReturnType, ReplyArgType>,
                   reply,
                   base::Owned(result)));
  }

  
  
  
  
  
  
  
  
  
  TaskId NewTrackedTaskId(IsCanceledCallback* is_canceled_cb);

  
  
  
  
  
  
  
  void TryCancel(TaskId id);

  
  
  void TryCancelAll();

  
  
  bool HasTrackedTasks() const;

 private:
  void Track(TaskId id, base::CancellationFlag* flag);
  void Untrack(TaskId id);

  base::hash_map<TaskId, base::CancellationFlag*> task_flags_;

  TaskId next_id_;
  base::ThreadChecker thread_checker_;

  base::WeakPtrFactory<CancelableTaskTracker> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CancelableTaskTracker);
};

}  

#endif  
