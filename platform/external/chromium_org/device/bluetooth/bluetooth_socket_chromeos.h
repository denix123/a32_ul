// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_CHROMEOS_H_

#include <queue>
#include <string>

#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_profile_manager_client.h"
#include "chromeos/dbus/bluetooth_profile_service_provider.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_socket.h"
#include "device/bluetooth/bluetooth_socket_net.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace dbus {
class FileDescriptor;
}  

namespace chromeos {

class BluetoothDeviceChromeOS;

class CHROMEOS_EXPORT BluetoothSocketChromeOS
    : public device::BluetoothSocketNet,
      public device::BluetoothAdapter::Observer,
      public BluetoothProfileServiceProvider::Delegate {
 public:
  enum SecurityLevel {
    SECURITY_LEVEL_LOW,
    SECURITY_LEVEL_MEDIUM
  };

  static scoped_refptr<BluetoothSocketChromeOS> CreateBluetoothSocket(
      scoped_refptr<base::SequencedTaskRunner> ui_task_runner,
      scoped_refptr<device::BluetoothSocketThread> socket_thread);

  
  
  
  
  
  virtual void Connect(const BluetoothDeviceChromeOS* device,
                       const device::BluetoothUUID& uuid,
                       SecurityLevel security_level,
                       const base::Closure& success_callback,
                       const ErrorCompletionCallback& error_callback);

  
  
  
  
  
  
  enum SocketType { kRfcomm, kL2cap };
  virtual void Listen(
      scoped_refptr<device::BluetoothAdapter> adapter,
      SocketType socket_type,
      const device::BluetoothUUID& uuid,
      const device::BluetoothAdapter::ServiceOptions& service_options,
      const base::Closure& success_callback,
      const ErrorCompletionCallback& error_callback);

  
  virtual void Close() OVERRIDE;
  virtual void Disconnect(const base::Closure& callback) OVERRIDE;
  virtual void Accept(const AcceptCompletionCallback& success_callback,
                      const ErrorCompletionCallback& error_callback) OVERRIDE;

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

 protected:
  virtual ~BluetoothSocketChromeOS();

 private:
  BluetoothSocketChromeOS(
      scoped_refptr<base::SequencedTaskRunner> ui_task_runner,
      scoped_refptr<device::BluetoothSocketThread> socket_thread);

  
  void RegisterProfile(const base::Closure& success_callback,
                       const ErrorCompletionCallback& error_callback);
  void OnRegisterProfile(const base::Closure& success_callback,
                         const ErrorCompletionCallback& error_callback);
  void OnRegisterProfileError(const ErrorCompletionCallback& error_callback,
                              const std::string& error_name,
                              const std::string& error_message);

  
  void OnConnectProfile(const base::Closure& success_callback);
  void OnConnectProfileError(const ErrorCompletionCallback& error_callback,
                             const std::string& error_name,
                             const std::string& error_message);

  
  virtual void AdapterPresentChanged(device::BluetoothAdapter* adapter,
                                     bool present) OVERRIDE;

  
  
  void OnInternalRegisterProfile();
  void OnInternalRegisterProfileError(const std::string& error_name,
                                      const std::string& error_message);

  
  virtual void Released() OVERRIDE;
  virtual void NewConnection(
      const dbus::ObjectPath& device_path,
      scoped_ptr<dbus::FileDescriptor> fd,
      const BluetoothProfileServiceProvider::Delegate::Options& options,
      const ConfirmationCallback& callback) OVERRIDE;
  virtual void RequestDisconnection(
      const dbus::ObjectPath& device_path,
      const ConfirmationCallback& callback) OVERRIDE;
  virtual void Cancel() OVERRIDE;

  
  void AcceptConnectionRequest();

  
  
  void DoNewConnection(
      const dbus::ObjectPath& device_path,
      scoped_ptr<dbus::FileDescriptor> fd,
      const BluetoothProfileServiceProvider::Delegate::Options& options,
      const ConfirmationCallback& callback);

  
  
  
  void OnNewConnection(scoped_refptr<BluetoothSocket> socket,
                       const ConfirmationCallback& callback,
                       Status status);

  
  
  
  void DoConnect(scoped_ptr<dbus::FileDescriptor> fd,
                 const ConfirmationCallback& callback);

  
  void DoCloseListening();

  
  void UnregisterProfile();
  void OnUnregisterProfile(const dbus::ObjectPath& object_path);
  void OnUnregisterProfileError(const dbus::ObjectPath& object_path,
                                const std::string& error_name,
                                const std::string& error_message);

  
  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  
  std::string device_address_;
  dbus::ObjectPath device_path_;

  
  device::BluetoothUUID uuid_;

  
  scoped_ptr<BluetoothProfileManagerClient::Options> options_;

  
  dbus::ObjectPath object_path_;

  
  
  scoped_ptr<BluetoothProfileServiceProvider> profile_;

  
  struct AcceptRequest {
    AcceptRequest();
    ~AcceptRequest();

    AcceptCompletionCallback success_callback;
    ErrorCompletionCallback error_callback;
  };
  scoped_ptr<AcceptRequest> accept_request_;

  
  struct ConnectionRequest {
    ConnectionRequest();
    ~ConnectionRequest();

    dbus::ObjectPath device_path;
    scoped_ptr<dbus::FileDescriptor> fd;
    BluetoothProfileServiceProvider::Delegate::Options options;
    ConfirmationCallback callback;
    bool accepting;
    bool cancelled;
  };
  std::queue<linked_ptr<ConnectionRequest> > connection_request_queue_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothSocketChromeOS);
};

}  

#endif  
