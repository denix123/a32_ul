// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_SCOPED_TASK_RUNNER_OBSERVER_H_
#define MEDIA_AUDIO_SCOPED_TASK_RUNNER_OBSERVER_H_

#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop.h"

namespace base {
class SingleThreadTaskRunner;
class WaitableEvent;
}

namespace media {

class ScopedTaskRunnerObserver
    : public base::MessageLoop::DestructionObserver {
 public:
  explicit ScopedTaskRunnerObserver(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner);

 protected:
  virtual ~ScopedTaskRunnerObserver();

  
  const scoped_refptr<base::SingleThreadTaskRunner>& task_runner() {
    return task_runner_;
  }

 private:
  
  
  void ObserveLoopDestruction(bool enable, base::WaitableEvent* done);

  
  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTaskRunnerObserver);
};

}  

#endif  
