// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_DATA_SINK_RECEIVER_H_
#define DEVICE_SERIAL_DATA_SINK_RECEIVER_H_

#include <queue>

#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "device/serial/buffer.h"
#include "device/serial/data_stream.mojom.h"
#include "mojo/public/cpp/system/data_pipe.h"

namespace device {

class AsyncWaiter;

class DataSinkReceiver : public base::RefCounted<DataSinkReceiver>,
                         public mojo::InterfaceImpl<serial::DataSink> {
 public:
  typedef base::Callback<void(scoped_ptr<ReadOnlyBuffer>)> ReadyCallback;
  typedef base::Callback<void(int32_t error)> CancelCallback;
  typedef base::Callback<void()> ErrorCallback;

  
  
  
  
  
  
  
  DataSinkReceiver(const ReadyCallback& ready_callback,
                   const CancelCallback& cancel_callback,
                   const ErrorCallback& error_callback);

  
  
  void ShutDown();

 private:
  class Buffer;
  class PendingFlush;
  friend class base::RefCounted<DataSinkReceiver>;

  virtual ~DataSinkReceiver();

  
  virtual void Init(mojo::ScopedDataPipeConsumerHandle handle) OVERRIDE;
  virtual void Cancel(int32_t error) OVERRIDE;
  virtual void OnConnectionError() OVERRIDE;

  
  void StartWaiting();

  
  void OnDoneWaiting(MojoResult result);

  
  void Done(uint32_t bytes_read);

  
  
  void DoneWithError(uint32_t bytes_read, int32_t error);

  
  bool DoneInternal(uint32_t bytes_read);

  
  void ReportBytesSentAndError(uint32_t bytes_read, int32_t error);

  
  
  void SetNumBytesToFlush(uint32_t bytes_to_flush);

  
  void DispatchFatalError();

  
  mojo::ScopedDataPipeConsumerHandle handle_;

  
  const ReadyCallback ready_callback_;

  
  const CancelCallback cancel_callback_;

  
  const ErrorCallback error_callback_;

  
  std::queue<linked_ptr<PendingFlush> > pending_flushes_;

  
  scoped_ptr<AsyncWaiter> waiter_;

  
  
  Buffer* buffer_in_use_;

  
  bool shut_down_;

  base::WeakPtrFactory<DataSinkReceiver> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DataSinkReceiver);
};

}  

#endif  
