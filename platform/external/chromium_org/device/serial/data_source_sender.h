// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_DATA_SOURCE_SENDER_H_
#define DEVICE_SERIAL_DATA_SOURCE_SENDER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "device/serial/buffer.h"
#include "device/serial/data_stream.mojom.h"
#include "mojo/public/cpp/system/data_pipe.h"

namespace device {

class AsyncWaiter;

class DataSourceSender : public base::RefCounted<DataSourceSender>,
                         public mojo::InterfaceImpl<serial::DataSource> {
 public:
  typedef base::Callback<void(scoped_ptr<WritableBuffer>)> ReadyCallback;
  typedef base::Callback<void()> ErrorCallback;

  
  
  
  
  
  DataSourceSender(const ReadyCallback& ready_callback,
                   const ErrorCallback& error_callback);

  
  
  void ShutDown();

 private:
  friend class base::RefCounted<DataSourceSender>;
  class PendingSend;

  virtual ~DataSourceSender();

  
  virtual void Init(mojo::ScopedDataPipeProducerHandle handle) OVERRIDE;
  virtual void Resume() OVERRIDE;
  
  virtual void OnConnectionError() OVERRIDE;

  
  void StartWaiting();

  
  void OnDoneWaiting(MojoResult result);

  // Reports a successful write of |bytes_written|.
  void Done(uint32_t bytes_written);

  // Reports a partially successful or unsuccessful write of |bytes_written|
  
  void DoneWithError(uint32_t bytes_written, int32_t error);

  
  void DoneInternal(uint32_t bytes_written);

  
  void DispatchFatalError();

  
  mojo::ScopedDataPipeProducerHandle handle_;

  
  ReadyCallback ready_callback_;

  
  ErrorCallback error_callback_;

  
  scoped_ptr<PendingSend> pending_send_;

  
  scoped_ptr<AsyncWaiter> waiter_;

  
  uint32_t bytes_sent_;

  
  bool shut_down_;

  DISALLOW_COPY_AND_ASSIGN(DataSourceSender);
};

}  

#endif  
