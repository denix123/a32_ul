// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_CONNECTION_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_CONNECTION_H_

#include "base/memory/scoped_ptr.h"
#include "device/bluetooth/bluetooth_gatt_connection.h"
#include "extensions/browser/api/api_resource.h"
#include "extensions/browser/api/api_resource_manager.h"

namespace extensions {

class BluetoothLowEnergyConnection : public ApiResource {
 public:
  explicit BluetoothLowEnergyConnection(
      bool persistent,
      const std::string& owner_extension_id,
      scoped_ptr<device::BluetoothGattConnection> connection);
  virtual ~BluetoothLowEnergyConnection();

  
  device::BluetoothGattConnection* GetConnection() const;

  
  virtual bool IsPersistent() const OVERRIDE;

  
  static const content::BrowserThread::ID kThreadId =
      content::BrowserThread::UI;

 private:
  friend class ApiResourceManager<BluetoothLowEnergyConnection>;
  static const char* service_name() {
    return "BluetoothLowEnergyConnectionManager";
  }

  
  bool persistent_;

  
  
  scoped_ptr<device::BluetoothGattConnection> connection_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothLowEnergyConnection);
};

}  

#endif  
