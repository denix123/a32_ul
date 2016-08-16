// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_SERIAL_IO_HANDLER_WIN_H_
#define DEVICE_SERIAL_SERIAL_IO_HANDLER_WIN_H_

#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "device/serial/serial_io_handler.h"

namespace device {

class SerialIoHandlerWin : public SerialIoHandler,
                           public base::MessageLoopForIO::IOHandler {
 protected:
  
  virtual void ReadImpl() OVERRIDE;
  virtual void WriteImpl() OVERRIDE;
  virtual void CancelReadImpl() OVERRIDE;
  virtual void CancelWriteImpl() OVERRIDE;
  virtual bool Flush() const OVERRIDE;
  virtual serial::DeviceControlSignalsPtr GetControlSignals() const OVERRIDE;
  virtual bool SetControlSignals(
      const serial::HostControlSignals& control_signals) OVERRIDE;
  virtual bool ConfigurePort(const serial::ConnectionOptions& options) OVERRIDE;
  virtual serial::ConnectionInfoPtr GetPortInfo() const OVERRIDE;
  virtual bool PostOpen() OVERRIDE;

 private:
  friend class SerialIoHandler;

  explicit SerialIoHandlerWin(
      scoped_refptr<base::MessageLoopProxy> file_thread_message_loop);
  virtual ~SerialIoHandlerWin();

  
  virtual void OnIOCompleted(base::MessageLoopForIO::IOContext* context,
                             DWORD bytes_transfered,
                             DWORD error) OVERRIDE;

  
  scoped_ptr<base::MessageLoopForIO::IOContext> comm_context_;

  
  scoped_ptr<base::MessageLoopForIO::IOContext> read_context_;

  
  scoped_ptr<base::MessageLoopForIO::IOContext> write_context_;

  
  DWORD event_mask_;

  
  
  
  bool is_comm_pending_;

  DISALLOW_COPY_AND_ASSIGN(SerialIoHandlerWin);
};

}  

#endif  
