// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_TASK_QUEUE_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_TASK_QUEUE_H_

#include <deque>
#include <set>

#include "base/bind.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/base/backoff_entry.h"

namespace syncer {

template <typename T>
class TaskQueue : base::NonThreadSafe {
 public:
  
  
  
  
  
  typedef base::Callback<void(const T&)> HandleTaskCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  TaskQueue(const HandleTaskCallback& callback,
            const base::TimeDelta& initial_backoff_delay,
            const base::TimeDelta& max_backoff_delay);

  
  
  
  void AddToQueue(const T& task);

  
  
  
  
  
  
  
  void MarkAsSucceeded(const T& task);

  
  
  
  
  
  
  
  void MarkAsFailed(const T& task);

  
  
  
  
  
  
  
  void Cancel(const T& task);

  
  
  
  
  
  void ResetBackoff();

  
  
  
  void SetTimerForTest(scoped_ptr<base::Timer> timer);

 private:
  void FinishTask(const T& task);
  void ScheduleDispatch();
  void Dispatch();
  
  bool ShouldDispatch();

  const HandleTaskCallback process_callback_;
  net::BackoffEntry::Policy backoff_policy_;
  scoped_ptr<net::BackoffEntry> backoff_entry_;
  
  int num_in_progress_;
  std::deque<T> queue_;
  
  std::set<T> tasks_;
  base::Closure dispatch_closure_;
  scoped_ptr<base::Timer> backoff_timer_;
  base::TimeDelta delay_;

  
  base::WeakPtrFactory<TaskQueue> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(TaskQueue);
};

const int kMaxConcurrentTasks = 1;

template <typename T>
TaskQueue<T>::TaskQueue(const HandleTaskCallback& callback,
                        const base::TimeDelta& initial_backoff_delay,
                        const base::TimeDelta& max_backoff_delay)
    : process_callback_(callback),
      backoff_policy_({}),
      num_in_progress_(0),
      weak_ptr_factory_(this) {
  DCHECK_LE(initial_backoff_delay.InMicroseconds(),
            max_backoff_delay.InMicroseconds());
  backoff_policy_.initial_delay_ms = initial_backoff_delay.InMilliseconds();
  backoff_policy_.multiply_factor = 2.0;
  backoff_policy_.jitter_factor = 0.1;
  backoff_policy_.maximum_backoff_ms = max_backoff_delay.InMilliseconds();
  backoff_policy_.entry_lifetime_ms = -1;
  backoff_policy_.always_use_initial_delay = false;
  backoff_entry_.reset(new net::BackoffEntry(&backoff_policy_));
  dispatch_closure_ =
      base::Bind(&TaskQueue::Dispatch, weak_ptr_factory_.GetWeakPtr());
  backoff_timer_.reset(new base::Timer(false, false));
}

template <typename T>
void TaskQueue<T>::AddToQueue(const T& task) {
  DCHECK(CalledOnValidThread());
  
  if (tasks_.find(task) == tasks_.end()) {
    queue_.push_back(task);
    tasks_.insert(task);
  }
  ScheduleDispatch();
}

template <typename T>
void TaskQueue<T>::MarkAsSucceeded(const T& task) {
  DCHECK(CalledOnValidThread());
  FinishTask(task);
  
  
  backoff_timer_->Stop();
  backoff_entry_->Reset();
  ScheduleDispatch();
}

template <typename T>
void TaskQueue<T>::MarkAsFailed(const T& task) {
  DCHECK(CalledOnValidThread());
  FinishTask(task);
  backoff_entry_->InformOfRequest(false);
  ScheduleDispatch();
}

template <typename T>
void TaskQueue<T>::Cancel(const T& task) {
  DCHECK(CalledOnValidThread());
  FinishTask(task);
  ScheduleDispatch();
}

template <typename T>
void TaskQueue<T>::ResetBackoff() {
  backoff_timer_->Stop();
  backoff_entry_->Reset();
  ScheduleDispatch();
}

template <typename T>
void TaskQueue<T>::SetTimerForTest(scoped_ptr<base::Timer> timer) {
  DCHECK(CalledOnValidThread());
  DCHECK(timer.get());
  backoff_timer_ = timer.Pass();
}

template <typename T>
void TaskQueue<T>::FinishTask(const T& task) {
  DCHECK(CalledOnValidThread());
  DCHECK_GE(num_in_progress_, 1);
  --num_in_progress_;
  const size_t num_erased = tasks_.erase(task);
  DCHECK_EQ(1U, num_erased);
}

template <typename T>
void TaskQueue<T>::ScheduleDispatch() {
  DCHECK(CalledOnValidThread());
  if (backoff_timer_->IsRunning() || !ShouldDispatch()) {
    return;
  }

  backoff_timer_->Start(
      FROM_HERE, backoff_entry_->GetTimeUntilRelease(), dispatch_closure_);
}

template <typename T>
void TaskQueue<T>::Dispatch() {
  DCHECK(CalledOnValidThread());
  if (!ShouldDispatch()) {
    return;
  }

  DCHECK(!queue_.empty());
  const T& task = queue_.front();
  ++num_in_progress_;
  DCHECK_LE(num_in_progress_, kMaxConcurrentTasks);
  base::MessageLoop::current()->PostTask(FROM_HERE,
                                         base::Bind(process_callback_, task));
  queue_.pop_front();
}

template <typename T>
bool TaskQueue<T>::ShouldDispatch() {
  return num_in_progress_ < kMaxConcurrentTasks && !queue_.empty();
}

}  

#endif  
