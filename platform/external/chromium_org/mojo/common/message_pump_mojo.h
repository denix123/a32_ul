// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_COMMON_MESSAGE_PUMP_MOJO_H_
#define MOJO_COMMON_MESSAGE_PUMP_MOJO_H_

#include <map>

#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_pump.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "mojo/common/mojo_common_export.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {
namespace common {

class MessagePumpMojoHandler;

class MOJO_COMMON_EXPORT MessagePumpMojo : public base::MessagePump {
 public:
  MessagePumpMojo();
  virtual ~MessagePumpMojo();

  
  
  static scoped_ptr<base::MessagePump> Create();

  
  static MessagePumpMojo* current();

  static bool IsCurrent() { return !!current(); }

  
  
  
  void AddHandler(MessagePumpMojoHandler* handler,
                  const Handle& handle,
                  MojoHandleSignals wait_signals,
                  base::TimeTicks deadline);

  void RemoveHandler(const Handle& handle);

  
  virtual void Run(Delegate* delegate) OVERRIDE;
  virtual void Quit() OVERRIDE;
  virtual void ScheduleWork() OVERRIDE;
  virtual void ScheduleDelayedWork(
      const base::TimeTicks& delayed_work_time) OVERRIDE;

 private:
  struct RunState;
  struct WaitState;

  
  struct Handler {
    Handler() : handler(NULL), wait_signals(MOJO_HANDLE_SIGNAL_NONE), id(0) {}

    MessagePumpMojoHandler* handler;
    MojoHandleSignals wait_signals;
    base::TimeTicks deadline;
    
    int id;
  };

  typedef std::map<Handle, Handler> HandleToHandler;

  
  void DoRunLoop(RunState* run_state, Delegate* delegate);

  
  
  void DoInternalWork(const RunState& run_state, bool block);

  
  
  void RemoveFirstInvalidHandle(const WaitState& wait_state);

  void SignalControlPipe(const RunState& run_state);

  WaitState GetWaitState(const RunState& run_state) const;

  
  MojoDeadline GetDeadlineForWait(const RunState& run_state) const;

  
  
  RunState* run_state_;

  
  
  
  base::Lock run_state_lock_;

  HandleToHandler handlers_;

  
  
  
  
  
  int next_handler_id_;

  DISALLOW_COPY_AND_ASSIGN(MessagePumpMojo);
};

}  
}  

#endif  
