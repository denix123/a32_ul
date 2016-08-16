// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_BALANCED_TASK_RUNNER_FACTORY_H_
#define CHROMECAST_MEDIA_CMA_BASE_BALANCED_TASK_RUNNER_FACTORY_H_

#include <set>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace chromecast {
namespace media {
class BalancedMediaTaskRunner;
class MediaTaskRunner;

class BalancedMediaTaskRunnerFactory
    : public base::RefCountedThreadSafe<BalancedMediaTaskRunnerFactory> {
 public:
  explicit BalancedMediaTaskRunnerFactory(base::TimeDelta max_delta);

  
  
  
  
  
  scoped_refptr<MediaTaskRunner> CreateMediaTaskRunner(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner);

 private:
  typedef std::set<scoped_refptr<BalancedMediaTaskRunner> > MediaTaskRunnerSet;

  friend class base::RefCountedThreadSafe<BalancedMediaTaskRunnerFactory>;
  virtual ~BalancedMediaTaskRunnerFactory();

  
  
  void OnNewTask();

  
  void UnregisterMediaTaskRunner(
      const scoped_refptr<BalancedMediaTaskRunner>& media_task_runner);

  
  const base::TimeDelta max_delta_;

  
  base::Lock lock_;
  MediaTaskRunnerSet task_runners_;

  DISALLOW_COPY_AND_ASSIGN(BalancedMediaTaskRunnerFactory);
};

}  
}  

#endif  
