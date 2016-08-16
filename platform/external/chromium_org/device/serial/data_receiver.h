// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_DATA_RECEIVER_H_
#define DEVICE_SERIAL_DATA_RECEIVER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "device/serial/buffer.h"
#include "device/serial/data_stream.mojom.h"
#include "mojo/public/cpp/system/data_pipe.h"

namespace device {

class AsyncWaiter;

class DataReceiver : public base::RefCounted<DataReceiver>,
                     public serial::DataSourceClient,
                     public mojo::ErrorHandler {
 public:
  typedef base::Callback<void(scoped_ptr<ReadOnlyBuffer>)> ReceiveDataCallback;
  typedef base::Callback<void(int32_t error)> ReceiveErrorCallback;

  
  
  
  DataReceiver(mojo::InterfacePtr<serial::DataSource> source,
               uint32_t buffer_size,
               int32_t fatal_error_value);

  
  
  
  
  bool Receive(const ReceiveDataCallback& callback,
               const ReceiveErrorCallback& error_callback);

 private:
  class PendingReceive;
  struct PendingError;
  friend class base::RefCounted<DataReceiver>;

  virtual ~DataReceiver();

  
  
  virtual void OnError(uint32_t bytes_since_last_error, int32_t error) OVERRIDE;

  
  virtual void OnConnectionError() OVERRIDE;

  
  
  void Done(uint32_t bytes_read);

  
  
  void OnDoneWaiting(MojoResult result);

  
  
  
  
  
  void ReceiveInternal();

  
  
  
  
  
  bool CheckErrorNotInReadRange(uint32_t num_bytes);

  
  
  void ShutDown();

  
  mojo::InterfacePtr<serial::DataSource> source_;

  
  mojo::ScopedDataPipeConsumerHandle handle_;

  
  const int32_t fatal_error_value_;

  
  uint32_t bytes_received_;

  
  bool shut_down_;

  
  scoped_ptr<AsyncWaiter> waiter_;

  
  scoped_ptr<PendingReceive> pending_receive_;

  
  scoped_ptr<PendingError> pending_error_;

  base::WeakPtrFactory<DataReceiver> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DataReceiver);
};

}  

#endif  
