// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_DELAYED_CALLBACK_RUNNER_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_DELAYED_CALLBACK_RUNNER_H_

#include <list>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/task_runner.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "base/timer/timer.h"

namespace safe_browsing {

class DelayedCallbackRunner {
 public:
  
  
  DelayedCallbackRunner(base::TimeDelta delay,
                        const scoped_refptr<base::TaskRunner>& task_runner);
  ~DelayedCallbackRunner();

  
  
  void RegisterCallback(const base::Closure& callback);

  
  void Start();

 private:
  typedef std::list<base::Closure> CallbackList;

  
  
  void OnTimer();

  base::ThreadChecker thread_checker_;

  
  scoped_refptr<base::TaskRunner> task_runner_;

  
  CallbackList callbacks_;

  
  CallbackList::iterator next_callback_;

  
  base::DelayTimer<DelayedCallbackRunner> timer_;

  DISALLOW_COPY_AND_ASSIGN(DelayedCallbackRunner);
};

}  

#endif  
