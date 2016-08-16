// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_UTILITY_RUN_LOOP_H_
#define MOJO_PUBLIC_CPP_UTILITY_RUN_LOOP_H_

#include <map>
#include <queue>

#include "mojo/public/cpp/bindings/callback.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {

class RunLoopHandler;

class RunLoop {
 public:
  RunLoop();
  ~RunLoop();

  
  
  static void SetUp();

  
  static void TearDown();

  
  
  static RunLoop* current();

  
  
  void AddHandler(RunLoopHandler* handler,
                  const Handle& handle,
                  MojoHandleSignals handle_signals,
                  MojoDeadline deadline);
  void RemoveHandler(const Handle& handle);
  bool HasHandler(const Handle& handle) const;

  
  
  void Run();

  
  
  
  void RunUntilIdle();

  void Quit();

  
  
  void PostDelayedTask(const Closure& task, MojoTimeTicks delay);

 private:
  struct RunState;
  struct WaitState;

  
  struct HandlerData {
    HandlerData()
        : handler(NULL),
          handle_signals(MOJO_HANDLE_SIGNAL_NONE),
          deadline(0),
          id(0) {}

    RunLoopHandler* handler;
    MojoHandleSignals handle_signals;
    MojoTimeTicks deadline;
    
    int id;
  };

  typedef std::map<Handle, HandlerData> HandleToHandlerData;

  
  
  enum CheckDeadline {
    CHECK_DEADLINE,
    IGNORE_DEADLINE
  };

  
  enum RunMode {
    UNTIL_EMPTY,
    UNTIL_IDLE
  };

  
  
  
  void RunInternal(RunMode run_mode);

  
  bool DoDelayedWork();

  
  
  
  
  
  bool Wait(bool non_blocking);

  
  
  
  bool NotifyHandlers(MojoResult error, CheckDeadline check);

  
  
  bool RemoveFirstInvalidHandle(const WaitState& wait_state);

  
  WaitState GetWaitState(bool non_blocking) const;

  HandleToHandlerData handler_data_;

  
  
  RunState* run_state_;

  
  
  
  
  
  int next_handler_id_;

  struct PendingTask {
    PendingTask(const Closure& task,
                MojoTimeTicks runtime,
                uint64_t sequence_number);
    ~PendingTask();

    bool operator<(const PendingTask& other) const;

    Closure task;
    MojoTimeTicks run_time;
    uint64_t sequence_number;
  };
  
  
  uint64_t next_sequence_number_;
  typedef std::priority_queue<PendingTask> DelayedTaskQueue;
  DelayedTaskQueue delayed_tasks_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(RunLoop);
};

}  

#endif  
