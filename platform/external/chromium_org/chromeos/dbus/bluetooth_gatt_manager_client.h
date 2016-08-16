// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_MANAGER_CLIENT_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_MANAGER_CLIENT_H_

#include <string>

#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattManagerClient : public DBusClient {
 public:
  
  struct CHROMEOS_EXPORT Options {
    
    
  };

  virtual ~BluetoothGattManagerClient();

  
  
  
  typedef base::Callback<void(const std::string& error_name,
                              const std::string& error_message)> ErrorCallback;

  
  
  
  
  
  
  
  
  
  
  
  virtual void RegisterService(const dbus::ObjectPath& service_path,
                               const Options& options,
                               const base::Closure& callback,
                               const ErrorCallback& error_callback) = 0;

  
  
  virtual void UnregisterService(const dbus::ObjectPath& service_path,
                                 const base::Closure& callback,
                                 const ErrorCallback& error_callback) = 0;

  
  static BluetoothGattManagerClient* Create();

  
  static const char kNoResponseError[];

 protected:
  BluetoothGattManagerClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattManagerClient);
};

}  

#endif 
