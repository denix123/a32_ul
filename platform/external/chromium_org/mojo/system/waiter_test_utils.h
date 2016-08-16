// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_WAITER_TEST_UTILS_H_
#define MOJO_SYSTEM_WAITER_TEST_UTILS_H_

#include <stdint.h>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/threading/simple_thread.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/handle_signals_state.h"
#include "mojo/system/waiter.h"

namespace mojo {
namespace system {
namespace test {

class SimpleWaiterThread : public base::SimpleThread {
 public:
  
  
  SimpleWaiterThread(MojoResult* result, uint32_t* context);
  virtual ~SimpleWaiterThread();  

  Waiter* waiter() { return &waiter_; }

 private:
  virtual void Run() OVERRIDE;

  MojoResult* const result_;
  uint32_t* const context_;
  Waiter waiter_;

  DISALLOW_COPY_AND_ASSIGN(SimpleWaiterThread);
};

class WaiterThread : public base::SimpleThread {
 public:
  
  
  
  WaiterThread(scoped_refptr<Dispatcher> dispatcher,
               MojoHandleSignals handle_signals,
               MojoDeadline deadline,
               uint32_t context,
               bool* did_wait_out,
               MojoResult* result_out,
               uint32_t* context_out,
               HandleSignalsState* signals_state_out);
  virtual ~WaiterThread();

 private:
  virtual void Run() OVERRIDE;

  const scoped_refptr<Dispatcher> dispatcher_;
  const MojoHandleSignals handle_signals_;
  const MojoDeadline deadline_;
  const uint32_t context_;
  bool* const did_wait_out_;
  MojoResult* const result_out_;
  uint32_t* const context_out_;
  HandleSignalsState* const signals_state_out_;

  Waiter waiter_;

  DISALLOW_COPY_AND_ASSIGN(WaiterThread);
};

}  
}  
}  

#endif  
