// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_SIMPLE_DISPATCHER_H_
#define MOJO_SYSTEM_SIMPLE_DISPATCHER_H_

#include <list>

#include "base/macros.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/system_impl_export.h"
#include "mojo/system/waiter_list.h"

namespace mojo {
namespace system {

class MOJO_SYSTEM_IMPL_EXPORT SimpleDispatcher : public Dispatcher {
 protected:
  SimpleDispatcher();
  virtual ~SimpleDispatcher();

  
  
  
  void HandleSignalsStateChangedNoLock();

  
  virtual void CancelAllWaitersNoLock() OVERRIDE;
  virtual MojoResult AddWaiterImplNoLock(
      Waiter* waiter,
      MojoHandleSignals signals,
      uint32_t context,
      HandleSignalsState* signals_state) OVERRIDE;
  virtual void RemoveWaiterImplNoLock(
      Waiter* waiter,
      HandleSignalsState* signals_state) OVERRIDE;

 private:
  
  WaiterList waiter_list_;

  DISALLOW_COPY_AND_ASSIGN(SimpleDispatcher);
};

}  
}  

#endif  
