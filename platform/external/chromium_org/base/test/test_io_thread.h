// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_TEST_IO_THREAD_H_
#define BASE_TEST_TEST_IO_THREAD_H_

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/task_runner.h"
#include "base/threading/thread.h"
#include "base/time/time.h"

namespace base {

class TestIOThread {
 public:
  enum Mode { kAutoStart, kManualStart };
  explicit TestIOThread(Mode mode);
  
  ~TestIOThread();

  
  
  
  void Start();
  void Stop();

  
  void PostTask(const tracked_objects::Location& from_here,
                const base::Closure& task);
  
  
  void PostTaskAndWait(const tracked_objects::Location& from_here,
                       const base::Closure& task);

  base::MessageLoopForIO* message_loop() {
    return static_cast<base::MessageLoopForIO*>(io_thread_.message_loop());
  }

  scoped_refptr<SingleThreadTaskRunner> task_runner() {
    return message_loop()->task_runner();
  }

 private:
  base::Thread io_thread_;
  bool io_thread_started_;

  DISALLOW_COPY_AND_ASSIGN(TestIOThread);
};

}  

#endif  
