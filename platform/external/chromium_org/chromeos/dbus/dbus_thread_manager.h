// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_DBUS_THREAD_MANAGER_H_
#define CHROMEOS_DBUS_DBUS_THREAD_MANAGER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client_bundle.h"

namespace base {
class Thread;
}  

namespace dbus {
class Bus;
class ObjectPath;
}  

namespace chromeos {

class BluetoothAdapterClient;
class BluetoothAgentManagerClient;
class BluetoothDeviceClient;
class BluetoothGattCharacteristicClient;
class BluetoothGattDescriptorClient;
class BluetoothGattManagerClient;
class BluetoothGattServiceClient;
class BluetoothInputClient;
class BluetoothProfileManagerClient;
class CrasAudioClient;
class CrosDisksClient;
class CryptohomeClient;
class DBusClient;
class DBusThreadManager;
class DBusThreadManagerSetter;
class DebugDaemonClient;
class EasyUnlockClient;
class GsmSMSClient;
class ImageBurnerClient;
class IntrospectableClient;
class LorgnetteManagerClient;
class ModemMessagingClient;
class NfcAdapterClient;
class NfcDeviceClient;
class NfcManagerClient;
class NfcRecordClient;
class NfcTagClient;
class PermissionBrokerClient;
class PowerManagerClient;
class PowerPolicyController;
class SessionManagerClient;
class ShillDeviceClient;
class ShillIPConfigClient;
class ShillManagerClient;
class ShillProfileClient;
class ShillServiceClient;
class SMSClient;
class SystemClockClient;
class UpdateEngineClient;

class CHROMEOS_EXPORT DBusThreadManager {
 public:
  
  
  
  
  
  static void Initialize();

  
  
  
  static scoped_ptr<DBusThreadManagerSetter> GetSetterForTesting();

  
  
  static bool IsInitialized();

  
  static void Shutdown();

  
  static DBusThreadManager* Get();

  
  bool IsUsingStub(DBusClientBundle::DBusClientType client);

  
  dbus::Bus* GetSystemBus();

  
  
  BluetoothAdapterClient* GetBluetoothAdapterClient();
  BluetoothAgentManagerClient* GetBluetoothAgentManagerClient();
  BluetoothDeviceClient* GetBluetoothDeviceClient();
  BluetoothGattCharacteristicClient* GetBluetoothGattCharacteristicClient();
  BluetoothGattDescriptorClient* GetBluetoothGattDescriptorClient();
  BluetoothGattManagerClient* GetBluetoothGattManagerClient();
  BluetoothGattServiceClient* GetBluetoothGattServiceClient();
  BluetoothInputClient* GetBluetoothInputClient();
  BluetoothProfileManagerClient* GetBluetoothProfileManagerClient();
  CrasAudioClient* GetCrasAudioClient();
  CrosDisksClient* GetCrosDisksClient();
  CryptohomeClient* GetCryptohomeClient();
  DebugDaemonClient* GetDebugDaemonClient();
  EasyUnlockClient* GetEasyUnlockClient();
  GsmSMSClient* GetGsmSMSClient();
  ImageBurnerClient* GetImageBurnerClient();
  IntrospectableClient* GetIntrospectableClient();
  LorgnetteManagerClient* GetLorgnetteManagerClient();
  ModemMessagingClient* GetModemMessagingClient();
  NfcAdapterClient* GetNfcAdapterClient();
  NfcDeviceClient* GetNfcDeviceClient();
  NfcManagerClient* GetNfcManagerClient();
  NfcRecordClient* GetNfcRecordClient();
  NfcTagClient* GetNfcTagClient();
  PermissionBrokerClient* GetPermissionBrokerClient();
  PowerManagerClient* GetPowerManagerClient();
  PowerPolicyController* GetPowerPolicyController();
  SessionManagerClient* GetSessionManagerClient();
  ShillDeviceClient* GetShillDeviceClient();
  ShillIPConfigClient* GetShillIPConfigClient();
  ShillManagerClient* GetShillManagerClient();
  ShillServiceClient* GetShillServiceClient();
  ShillProfileClient* GetShillProfileClient();
  SMSClient* GetSMSClient();
  SystemClockClient* GetSystemClockClient();
  UpdateEngineClient* GetUpdateEngineClient();

 private:
  friend class DBusThreadManagerSetter;

  
  
  explicit DBusThreadManager(scoped_ptr<DBusClientBundle> client_bundle);
  ~DBusThreadManager();

  
  
  
  
  static void CreateGlobalInstance(
      DBusClientBundle::DBusClientTypeMask unstub_client_mask);

  
  
  static void InitializeWithRealClients();

  
  
  static void InitializeWithStubs();

  
  
  static void InitializeWithPartialStub(const std::string& unstub_clients);

  
  
  void InitializeClients();

  scoped_ptr<base::Thread> dbus_thread_;
  scoped_refptr<dbus::Bus> system_bus_;
  scoped_ptr<DBusClientBundle> client_bundle_;
  scoped_ptr<PowerPolicyController> power_policy_controller_;

  DISALLOW_COPY_AND_ASSIGN(DBusThreadManager);
};

class CHROMEOS_EXPORT DBusThreadManagerSetter {
 public:
  ~DBusThreadManagerSetter();

  void SetBluetoothAdapterClient(scoped_ptr<BluetoothAdapterClient> client);
  void SetBluetoothAgentManagerClient(
      scoped_ptr<BluetoothAgentManagerClient> client);
  void SetBluetoothDeviceClient(scoped_ptr<BluetoothDeviceClient> client);
  void SetBluetoothGattCharacteristicClient(
      scoped_ptr<BluetoothGattCharacteristicClient> client);
  void SetBluetoothGattDescriptorClient(
      scoped_ptr<BluetoothGattDescriptorClient> client);
  void SetBluetoothGattManagerClient(
      scoped_ptr<BluetoothGattManagerClient> client);
  void SetBluetoothGattServiceClient(
      scoped_ptr<BluetoothGattServiceClient> client);
  void SetBluetoothInputClient(scoped_ptr<BluetoothInputClient> client);
  void SetBluetoothProfileManagerClient(
      scoped_ptr<BluetoothProfileManagerClient> client);
  void SetCrasAudioClient(scoped_ptr<CrasAudioClient> client);
  void SetCrosDisksClient(scoped_ptr<CrosDisksClient> client);
  void SetCryptohomeClient(scoped_ptr<CryptohomeClient> client);
  void SetDebugDaemonClient(scoped_ptr<DebugDaemonClient> client);
  void SetEasyUnlockClient(scoped_ptr<EasyUnlockClient> client);
  void SetLorgnetteManagerClient(scoped_ptr<LorgnetteManagerClient> client);
  void SetShillDeviceClient(scoped_ptr<ShillDeviceClient> client);
  void SetShillIPConfigClient(scoped_ptr<ShillIPConfigClient> client);
  void SetShillManagerClient(scoped_ptr<ShillManagerClient> client);
  void SetShillServiceClient(scoped_ptr<ShillServiceClient> client);
  void SetShillProfileClient(scoped_ptr<ShillProfileClient> client);
  void SetGsmSMSClient(scoped_ptr<GsmSMSClient> client);
  void SetImageBurnerClient(scoped_ptr<ImageBurnerClient> client);
  void SetIntrospectableClient(scoped_ptr<IntrospectableClient> client);
  void SetModemMessagingClient(scoped_ptr<ModemMessagingClient> client);
  void SetNfcAdapterClient(scoped_ptr<NfcAdapterClient> client);
  void SetNfcDeviceClient(scoped_ptr<NfcDeviceClient> client);
  void SetNfcManagerClient(scoped_ptr<NfcManagerClient> client);
  void SetNfcRecordClient(scoped_ptr<NfcRecordClient> client);
  void SetNfcTagClient(scoped_ptr<NfcTagClient> client);
  void SetPermissionBrokerClient(scoped_ptr<PermissionBrokerClient> client);
  void SetPowerManagerClient(scoped_ptr<PowerManagerClient> client);
  void SetSessionManagerClient(scoped_ptr<SessionManagerClient> client);
  void SetSMSClient(scoped_ptr<SMSClient> client);
  void SetSystemClockClient(scoped_ptr<SystemClockClient> client);
  void SetUpdateEngineClient(scoped_ptr<UpdateEngineClient> client);

 private:
  friend class DBusThreadManager;

  DBusThreadManagerSetter();

  DISALLOW_COPY_AND_ASSIGN(DBusThreadManagerSetter);
};

}  

#endif  
