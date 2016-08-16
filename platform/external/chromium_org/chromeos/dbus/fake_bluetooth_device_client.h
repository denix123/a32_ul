// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_DEVICE_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_DEVICE_CLIENT_H_

#include <map>
#include <vector>

#include "base/bind.h"
#include "base/callback.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_agent_service_provider.h"
#include "chromeos/dbus/bluetooth_device_client.h"
#include "chromeos/dbus/bluetooth_profile_service_provider.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeBluetoothDeviceClient
    : public BluetoothDeviceClient {
 public:
  struct Properties : public BluetoothDeviceClient::Properties {
    explicit Properties(const PropertyChangedCallback & callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeBluetoothDeviceClient();
  virtual ~FakeBluetoothDeviceClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetDevicesForAdapter(
      const dbus::ObjectPath& adapter_path) OVERRIDE;
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path)
      OVERRIDE;
  virtual void Connect(const dbus::ObjectPath& object_path,
                       const base::Closure& callback,
                       const ErrorCallback& error_callback) OVERRIDE;
  virtual void Disconnect(const dbus::ObjectPath& object_path,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConnectProfile(const dbus::ObjectPath& object_path,
                              const std::string& uuid,
                              const base::Closure& callback,
                              const ErrorCallback& error_callback) OVERRIDE;
  virtual void DisconnectProfile(const dbus::ObjectPath& object_path,
                                 const std::string& uuid,
                                 const base::Closure& callback,
                                 const ErrorCallback& error_callback) OVERRIDE;
  virtual void Pair(const dbus::ObjectPath& object_path,
                    const base::Closure& callback,
                    const ErrorCallback& error_callback) OVERRIDE;
  virtual void CancelPairing(const dbus::ObjectPath& object_path,
                             const base::Closure& callback,
                             const ErrorCallback& error_callback) OVERRIDE;
  virtual void StartConnectionMonitor(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void StopConnectionMonitor(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  void SetSimulationIntervalMs(int interval_ms);

  
  void BeginDiscoverySimulation(const dbus::ObjectPath& adapter_path);
  void EndDiscoverySimulation(const dbus::ObjectPath& adapter_path);

  
  void BeginIncomingPairingSimulation(const dbus::ObjectPath& adapter_path);
  void EndIncomingPairingSimulation(const dbus::ObjectPath& adapter_path);

  
  void CreateDevice(const dbus::ObjectPath& adapter_path,
                    const dbus::ObjectPath& device_path);

  
  void RemoveDevice(const dbus::ObjectPath& adapter_path,
                    const dbus::ObjectPath& device_path);

  
  
  
  
  void SimulatePairing(const dbus::ObjectPath& object_path,
                       bool incoming_request,
                       const base::Closure& callback,
                       const ErrorCallback& error_callback);

  
  
  static const char kPairedDevicePath[];
  static const char kPairedDeviceName[];
  static const char kPairedDeviceAddress[];
  static const uint32 kPairedDeviceClass;

  static const char kLegacyAutopairPath[];
  static const char kLegacyAutopairName[];
  static const char kLegacyAutopairAddress[];
  static const uint32 kLegacyAutopairClass;

  static const char kDisplayPinCodePath[];
  static const char kDisplayPinCodeName[];
  static const char kDisplayPinCodeAddress[];
  static const uint32 kDisplayPinCodeClass;

  static const char kVanishingDevicePath[];
  static const char kVanishingDeviceName[];
  static const char kVanishingDeviceAddress[];
  static const uint32 kVanishingDeviceClass;

  static const char kConnectUnpairablePath[];
  static const char kConnectUnpairableName[];
  static const char kConnectUnpairableAddress[];
  static const uint32 kConnectUnpairableClass;

  static const char kDisplayPasskeyPath[];
  static const char kDisplayPasskeyName[];
  static const char kDisplayPasskeyAddress[];
  static const uint32 kDisplayPasskeyClass;

  static const char kRequestPinCodePath[];
  static const char kRequestPinCodeName[];
  static const char kRequestPinCodeAddress[];
  static const uint32 kRequestPinCodeClass;

  static const char kConfirmPasskeyPath[];
  static const char kConfirmPasskeyName[];
  static const char kConfirmPasskeyAddress[];
  static const uint32 kConfirmPasskeyClass;

  static const char kRequestPasskeyPath[];
  static const char kRequestPasskeyName[];
  static const char kRequestPasskeyAddress[];
  static const uint32 kRequestPasskeyClass;

  static const char kUnconnectableDevicePath[];
  static const char kUnconnectableDeviceName[];
  static const char kUnconnectableDeviceAddress[];
  static const uint32 kUnconnectableDeviceClass;

  static const char kUnpairableDevicePath[];
  static const char kUnpairableDeviceName[];
  static const char kUnpairableDeviceAddress[];
  static const uint32 kUnpairableDeviceClass;

  static const char kJustWorksPath[];
  static const char kJustWorksName[];
  static const char kJustWorksAddress[];
  static const uint32 kJustWorksClass;

  static const char kLowEnergyPath[];
  static const char kLowEnergyName[];
  static const char kLowEnergyAddress[];
  static const uint32 kLowEnergyClass;

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  void DiscoverySimulationTimer();
  void IncomingPairingSimulationTimer();

  void CompleteSimulatedPairing(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback);
  void TimeoutSimulatedPairing(
      const dbus::ObjectPath& object_path,
      const ErrorCallback& error_callback);
  void CancelSimulatedPairing(
      const dbus::ObjectPath& object_path,
      const ErrorCallback& error_callback);
  void RejectSimulatedPairing(
      const dbus::ObjectPath& object_path,
      const ErrorCallback& error_callback);
  void FailSimulatedPairing(
      const dbus::ObjectPath& object_path,
      const ErrorCallback& error_callback);
  void AddInputDeviceIfNeeded(
      const dbus::ObjectPath& object_path,
      Properties* properties);

  
  
  void UpdateDeviceRSSI(const dbus::ObjectPath& object_path, int16 rssi);

  void PinCodeCallback(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback,
      BluetoothAgentServiceProvider::Delegate::Status status,
      const std::string& pincode);
  void PasskeyCallback(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback,
      BluetoothAgentServiceProvider::Delegate::Status status,
      uint32 passkey);
  void ConfirmationCallback(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback,
      BluetoothAgentServiceProvider::Delegate::Status status);
  void SimulateKeypress(
      uint16 entered,
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback);

  void ConnectionCallback(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback,
      BluetoothProfileServiceProvider::Delegate::Status status);
  void DisconnectionCallback(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const ErrorCallback& error_callback,
      BluetoothProfileServiceProvider::Delegate::Status status);

  
  ObserverList<Observer> observers_;

  
  typedef std::map<const dbus::ObjectPath, Properties *> PropertiesMap;
  PropertiesMap properties_map_;
  std::vector<dbus::ObjectPath> device_list_;

  int simulation_interval_ms_;
  uint32_t discovery_simulation_step_;
  uint32_t incoming_pairing_simulation_step_;
  bool pairing_cancelled_;
  bool connection_monitor_started_;
};

}  

#endif  