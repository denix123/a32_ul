// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SERIAL_SERIAL_CONNECTION_H_
#define EXTENSIONS_BROWSER_API_SERIAL_SERIAL_CONNECTION_H_

#include <string>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "content/public/browser/browser_thread.h"
#include "device/serial/serial_io_handler.h"
#include "extensions/browser/api/api_resource.h"
#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/common/api/serial.h"
#include "net/base/io_buffer.h"

using content::BrowserThread;

namespace extensions {

class SerialConnection : public ApiResource,
                         public base::SupportsWeakPtr<SerialConnection> {
 public:
  typedef device::SerialIoHandler::OpenCompleteCallback OpenCompleteCallback;

  
  
  
  typedef base::Callback<
      void(const std::string& data, core_api::serial::ReceiveError error)>
      ReceiveCompleteCallback;

  
  
  
  typedef base::Callback<
      void(int bytes_sent, core_api::serial::SendError error)>
      SendCompleteCallback;

  SerialConnection(const std::string& port,
                   const std::string& owner_extension_id);
  virtual ~SerialConnection();

  
  virtual bool IsPersistent() const OVERRIDE;

  void set_persistent(bool persistent) { persistent_ = persistent; }
  bool persistent() const { return persistent_; }

  void set_name(const std::string& name) { name_ = name; }
  const std::string& name() const { return name_; }

  void set_buffer_size(int buffer_size);
  int buffer_size() const { return buffer_size_; }

  void set_receive_timeout(int receive_timeout);
  int receive_timeout() const { return receive_timeout_; }

  void set_send_timeout(int send_timeout);
  int send_timeout() const { return send_timeout_; }

  void set_paused(bool paused);
  bool paused() const { return paused_; }

  
  
  
  void Open(const OpenCompleteCallback& callback);

  
  
  
  bool Receive(const ReceiveCompleteCallback& callback);

  
  
  
  bool Send(const std::string& data, const SendCompleteCallback& callback);

  
  bool Flush() const;

  
  
  
  bool Configure(const core_api::serial::ConnectionOptions& options);

  
  
  
  bool GetInfo(core_api::serial::ConnectionInfo* info) const;

  
  
  
  bool GetControlSignals(
      core_api::serial::DeviceControlSignals* control_signals) const;

  
  
  
  bool SetControlSignals(
      const core_api::serial::HostControlSignals& control_signals);

  
  void SetIoHandlerForTest(scoped_refptr<device::SerialIoHandler> handler);

  static const BrowserThread::ID kThreadId = BrowserThread::IO;

 private:
  friend class ApiResourceManager<SerialConnection>;
  static const char* service_name() { return "SerialConnectionManager"; }

  
  
  
  class TimeoutTask {
   public:
    TimeoutTask(const base::Closure& closure, const base::TimeDelta& delay);
    ~TimeoutTask();

   private:
    void Run() const;

    base::WeakPtrFactory<TimeoutTask> weak_factory_;
    base::Closure closure_;
    base::TimeDelta delay_;
  };

  
  void OnReceiveTimeout();

  
  void OnSendTimeout();

  
  void OnAsyncReadComplete(int bytes_read, device::serial::ReceiveError error);

  
  void OnAsyncWriteComplete(int bytes_sent, device::serial::SendError error);

  
  std::string port_;

  
  
  bool persistent_;

  
  std::string name_;

  
  int buffer_size_;

  
  
  int receive_timeout_;

  
  
  int send_timeout_;

  
  
  bool paused_;

  
  ReceiveCompleteCallback receive_complete_;

  
  SendCompleteCallback send_complete_;

  
  
  scoped_ptr<TimeoutTask> receive_timeout_task_;

  
  
  scoped_ptr<TimeoutTask> send_timeout_task_;

  scoped_refptr<net::IOBuffer> receive_buffer_;

  
  scoped_refptr<device::SerialIoHandler> io_handler_;
};

}  

namespace mojo {

template <>
struct TypeConverter<device::serial::HostControlSignalsPtr,
                     extensions::core_api::serial::HostControlSignals> {
  static device::serial::HostControlSignalsPtr Convert(
      const extensions::core_api::serial::HostControlSignals& input);
};

template <>
struct TypeConverter<device::serial::ConnectionOptionsPtr,
                     extensions::core_api::serial::ConnectionOptions> {
  static device::serial::ConnectionOptionsPtr Convert(
      const extensions::core_api::serial::ConnectionOptions& input);
};

}  

#endif  
