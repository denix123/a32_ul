// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_SERIAL_IO_HANDLER_H_
#define DEVICE_SERIAL_SERIAL_IO_HANDLER_H_

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/threading/non_thread_safe.h"
#include "device/serial/buffer.h"
#include "device/serial/serial.mojom.h"

namespace device {

class SerialIoHandler : public base::NonThreadSafe,
                        public base::RefCounted<SerialIoHandler> {
 public:
  
  static scoped_refptr<SerialIoHandler> Create(
      scoped_refptr<base::MessageLoopProxy> file_thread_message_loop);

  typedef base::Callback<void(bool success)> OpenCompleteCallback;

  
  virtual void Open(const std::string& port,
                    const OpenCompleteCallback& callback);

  
  
  
  void Read(scoped_ptr<WritableBuffer> buffer);

  
  
  
  void Write(scoped_ptr<ReadOnlyBuffer> buffer);

  
  bool IsReadPending() const;

  
  bool IsWritePending() const;

  
  void CancelRead(serial::ReceiveError reason);

  
  void CancelWrite(serial::SendError reason);

  
  virtual bool Flush() const = 0;

  
  
  
  virtual serial::DeviceControlSignalsPtr GetControlSignals() const = 0;

  
  
  
  virtual bool SetControlSignals(
      const serial::HostControlSignals& control_signals) = 0;

  
  
  virtual bool ConfigurePort(const serial::ConnectionOptions& options) = 0;

  
  
  
  virtual serial::ConnectionInfoPtr GetPortInfo() const = 0;

 protected:
  explicit SerialIoHandler(
      scoped_refptr<base::MessageLoopProxy> file_thread_message_loop);
  virtual ~SerialIoHandler();

  
  
  
  
  
  virtual void ReadImpl() = 0;

  
  
  
  
  
  virtual void WriteImpl() = 0;

  
  virtual void CancelReadImpl() = 0;

  
  virtual void CancelWriteImpl() = 0;

  
  virtual bool PostOpen();

  
  
  
  void ReadCompleted(int bytes_read, serial::ReceiveError error);

  
  
  
  void WriteCompleted(int bytes_written, serial::SendError error);

  
  
  
  void QueueReadCompleted(int bytes_read, serial::ReceiveError error);

  
  
  
  void QueueWriteCompleted(int bytes_written, serial::SendError error);

  const base::File& file() const { return file_; }

  char* pending_read_buffer() const {
    return pending_read_buffer_ ? pending_read_buffer_->GetData() : NULL;
  }

  uint32_t pending_read_buffer_len() const {
    return pending_read_buffer_ ? pending_read_buffer_->GetSize() : 0;
  }

  serial::ReceiveError read_cancel_reason() const {
    return read_cancel_reason_;
  }

  bool read_canceled() const { return read_canceled_; }

  const char* pending_write_buffer() const {
    return pending_write_buffer_ ? pending_write_buffer_->GetData() : NULL;
  }

  uint32_t pending_write_buffer_len() const {
    return pending_write_buffer_ ? pending_write_buffer_->GetSize() : 0;
  }

  serial::SendError write_cancel_reason() const { return write_cancel_reason_; }

  bool write_canceled() const { return write_canceled_; }

  
  static std::string MaybeFixUpPortName(const std::string& port_name);

 private:
  friend class base::RefCounted<SerialIoHandler>;

  
  void StartOpen(const std::string& port,
                 scoped_refptr<base::MessageLoopProxy> io_message_loop);

  
  void FinishOpen(base::File file);

  void Close();

  
  static void DoClose(base::File port);

  
  
  base::File file_;

  scoped_ptr<WritableBuffer> pending_read_buffer_;
  serial::ReceiveError read_cancel_reason_;
  bool read_canceled_;

  scoped_ptr<ReadOnlyBuffer> pending_write_buffer_;
  serial::SendError write_cancel_reason_;
  bool write_canceled_;

  
  OpenCompleteCallback open_complete_;

  scoped_refptr<base::MessageLoopProxy> file_thread_message_loop_;

  DISALLOW_COPY_AND_ASSIGN(SerialIoHandler);
};

}  

#endif  
