// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_DATA_SENDER_H_
#define DEVICE_SERIAL_DATA_SENDER_H_

#include <queue>

#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/strings/string_piece.h"
#include "device/serial/buffer.h"
#include "device/serial/data_stream.mojom.h"
#include "mojo/public/cpp/system/data_pipe.h"

namespace device {

class AsyncWaiter;

class DataSender : public serial::DataSinkClient, public mojo::ErrorHandler {
 public:
  typedef base::Callback<void(uint32_t bytes_sent)> DataSentCallback;
  typedef base::Callback<void(uint32_t bytes_sent, int32_t error)>
      SendErrorCallback;
  typedef base::Callback<void()> CancelCallback;

  
  
  
  DataSender(mojo::InterfacePtr<serial::DataSink> sink,
             uint32_t buffer_size,
             int32_t fatal_error_value);

  virtual ~DataSender();

  
  
  
  
  
  
  bool Send(const base::StringPiece& data,
            const DataSentCallback& callback,
            const SendErrorCallback& error_callback);

  
  
  bool Cancel(int32_t error, const CancelCallback& callback);

 private:
  class PendingSend;

  
  virtual void ReportBytesSent(uint32_t bytes_sent) OVERRIDE;
  virtual void ReportBytesSentAndError(
      uint32_t bytes_sent,
      int32_t error,
      const mojo::Callback<void(uint32_t)>& callback) OVERRIDE;

  
  virtual void OnConnectionError() OVERRIDE;

  
  
  
  void SendInternal();

  
  void OnDoneWaiting(MojoResult result);

  
  void RunCancelCallback();

  
  
  void ShutDown();

  
  mojo::InterfacePtr<serial::DataSink> sink_;

  
  mojo::ScopedDataPipeProducerHandle handle_;

  
  const int32_t fatal_error_value_;

  
  scoped_ptr<AsyncWaiter> waiter_;

  // A queue of PendingSend that have not yet been fully written to the data
  
  std::queue<linked_ptr<PendingSend> > pending_sends_;

  // A queue of PendingSend that have been written to the data pipe, but have
  
  std::queue<linked_ptr<PendingSend> > sends_awaiting_ack_;

  
  
  CancelCallback pending_cancel_;

  
  bool shut_down_;

  DISALLOW_COPY_AND_ASSIGN(DataSender);
};

}  

#endif  
