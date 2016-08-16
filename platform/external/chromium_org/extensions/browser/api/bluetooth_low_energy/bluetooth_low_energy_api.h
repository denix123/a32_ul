// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_API_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_API_H_

#include "base/memory/scoped_ptr.h"
#include "extensions/browser/api/bluetooth_low_energy/bluetooth_low_energy_event_router.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_function.h"
#include "extensions/browser/extension_function_histogram_value.h"

namespace extensions {

class BluetoothLowEnergyEventRouter;

class BluetoothLowEnergyAPI : public BrowserContextKeyedAPI {
 public:
  static BrowserContextKeyedAPIFactory<BluetoothLowEnergyAPI>*
      GetFactoryInstance();

  
  static BluetoothLowEnergyAPI* Get(content::BrowserContext* context);

  explicit BluetoothLowEnergyAPI(content::BrowserContext* context);
  virtual ~BluetoothLowEnergyAPI();

  
  virtual void Shutdown() OVERRIDE;

  BluetoothLowEnergyEventRouter* event_router() const {
    return event_router_.get();
  }

  
  static const char* service_name() { return "BluetoothLowEnergyAPI"; }
  static const bool kServiceRedirectedInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

 private:
  friend class BrowserContextKeyedAPIFactory<BluetoothLowEnergyAPI>;

  scoped_ptr<BluetoothLowEnergyEventRouter> event_router_;

  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothLowEnergyAPI);
};

namespace core_api {

class BluetoothLowEnergyExtensionFunction : public AsyncExtensionFunction {
 public:
  BluetoothLowEnergyExtensionFunction();

 protected:
  virtual ~BluetoothLowEnergyExtensionFunction();

  
  virtual bool RunAsync() OVERRIDE;

  
  
  
  
  virtual bool DoWork() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothLowEnergyExtensionFunction);
};

class BluetoothLowEnergyConnectFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.connect",
                             BLUETOOTHLOWENERGY_CONNECT);

 protected:
  virtual ~BluetoothLowEnergyConnectFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);
};

class BluetoothLowEnergyDisconnectFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.disconnect",
                             BLUETOOTHLOWENERGY_DISCONNECT);

 protected:
  virtual ~BluetoothLowEnergyDisconnectFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);
};

class BluetoothLowEnergyGetServiceFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getService",
                             BLUETOOTHLOWENERGY_GETSERVICE);

 protected:
  virtual ~BluetoothLowEnergyGetServiceFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetServicesFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getServices",
                             BLUETOOTHLOWENERGY_GETSERVICES);

 protected:
  virtual ~BluetoothLowEnergyGetServicesFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetCharacteristicFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getCharacteristic",
                             BLUETOOTHLOWENERGY_GETCHARACTERISTIC);

 protected:
  virtual ~BluetoothLowEnergyGetCharacteristicFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetCharacteristicsFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getCharacteristics",
                             BLUETOOTHLOWENERGY_GETCHARACTERISTICS);

 protected:
  virtual ~BluetoothLowEnergyGetCharacteristicsFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetIncludedServicesFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getIncludedServices",
                             BLUETOOTHLOWENERGY_GETINCLUDEDSERVICES);

 protected:
  virtual ~BluetoothLowEnergyGetIncludedServicesFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetDescriptorFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getDescriptor",
                             BLUETOOTHLOWENERGY_GETDESCRIPTOR);

 protected:
  virtual ~BluetoothLowEnergyGetDescriptorFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyGetDescriptorsFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.getDescriptors",
                             BLUETOOTHLOWENERGY_GETDESCRIPTORS);

 protected:
  virtual ~BluetoothLowEnergyGetDescriptorsFunction() {}

  
  virtual bool DoWork() OVERRIDE;
};

class BluetoothLowEnergyReadCharacteristicValueFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.readCharacteristicValue",
                             BLUETOOTHLOWENERGY_READCHARACTERISTICVALUE);

 protected:
  virtual ~BluetoothLowEnergyReadCharacteristicValueFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);

  
  std::string instance_id_;
};

class BluetoothLowEnergyWriteCharacteristicValueFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.writeCharacteristicValue",
                             BLUETOOTHLOWENERGY_WRITECHARACTERISTICVALUE);

 protected:
  virtual ~BluetoothLowEnergyWriteCharacteristicValueFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);

  
  std::string instance_id_;
};

class BluetoothLowEnergyStartCharacteristicNotificationsFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "bluetoothLowEnergy.startCharacteristicNotifications",
      BLUETOOTHLOWENERGY_STARTCHARACTERISTICNOTIFICATIONS);

 protected:
  virtual ~BluetoothLowEnergyStartCharacteristicNotificationsFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);
};

class BluetoothLowEnergyStopCharacteristicNotificationsFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "bluetoothLowEnergy.stopCharacteristicNotifications",
      BLUETOOTHLOWENERGY_STOPCHARACTERISTICNOTIFICATIONS);

 protected:
  virtual ~BluetoothLowEnergyStopCharacteristicNotificationsFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);
};

class BluetoothLowEnergyReadDescriptorValueFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.readDescriptorValue",
                             BLUETOOTHLOWENERGY_READDESCRIPTORVALUE);

 protected:
  virtual ~BluetoothLowEnergyReadDescriptorValueFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);

  
  std::string instance_id_;
};

class BluetoothLowEnergyWriteDescriptorValueFunction
    : public BluetoothLowEnergyExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bluetoothLowEnergy.writeDescriptorValue",
                             BLUETOOTHLOWENERGY_WRITEDESCRIPTORVALUE);

 protected:
  virtual ~BluetoothLowEnergyWriteDescriptorValueFunction() {}

  
  virtual bool DoWork() OVERRIDE;

 private:
  
  
  void SuccessCallback();
  void ErrorCallback(BluetoothLowEnergyEventRouter::Status status);

  
  std::string instance_id_;
};

}  
}  

#endif  
