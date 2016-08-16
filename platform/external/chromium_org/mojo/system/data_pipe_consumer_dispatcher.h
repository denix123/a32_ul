// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_DATA_PIPE_CONSUMER_DISPATCHER_H_
#define MOJO_SYSTEM_DATA_PIPE_CONSUMER_DISPATCHER_H_

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class DataPipe;

class MOJO_SYSTEM_IMPL_EXPORT DataPipeConsumerDispatcher : public Dispatcher {
 public:
  DataPipeConsumerDispatcher();

  
  void Init(scoped_refptr<DataPipe> data_pipe);

  
  virtual Type GetType() const OVERRIDE;

 private:
  virtual ~DataPipeConsumerDispatcher();

  
  virtual void CancelAllWaitersNoLock() OVERRIDE;
  virtual void CloseImplNoLock() OVERRIDE;
  virtual scoped_refptr<Dispatcher>
      CreateEquivalentDispatcherAndCloseImplNoLock() OVERRIDE;
  virtual MojoResult ReadDataImplNoLock(UserPointer<void> elements,
                                        UserPointer<uint32_t> num_bytes,
                                        MojoReadDataFlags flags) OVERRIDE;
  virtual MojoResult BeginReadDataImplNoLock(
      UserPointer<const void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      MojoReadDataFlags flags) OVERRIDE;
  virtual MojoResult EndReadDataImplNoLock(uint32_t num_bytes_read) OVERRIDE;
  virtual HandleSignalsState GetHandleSignalsStateImplNoLock() const OVERRIDE;
  virtual MojoResult AddWaiterImplNoLock(
      Waiter* waiter,
      MojoHandleSignals signals,
      uint32_t context,
      HandleSignalsState* signals_state) OVERRIDE;
  virtual void RemoveWaiterImplNoLock(
      Waiter* waiter,
      HandleSignalsState* signals_state) OVERRIDE;
  virtual bool IsBusyNoLock() const OVERRIDE;

  
  scoped_refptr<DataPipe> data_pipe_;  

  DISALLOW_COPY_AND_ASSIGN(DataPipeConsumerDispatcher);
};

}  
}  

#endif  
