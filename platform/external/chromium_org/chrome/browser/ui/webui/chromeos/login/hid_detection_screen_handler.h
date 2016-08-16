// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_HID_DETECTION_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_HID_DETECTION_SCREEN_HANDLER_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_registry_simple.h"
#include "base/values.h"
#include "chrome/browser/chromeos/device/input_service_proxy.h"
#include "chrome/browser/chromeos/login/screens/hid_detection_screen_actor.h"
#include "chrome/browser/ui/webui/chromeos/login/base_screen_handler.h"
#include "content/public/browser/web_ui.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_discovery_session.h"

namespace base {
class DictionaryValue;
}

namespace chromeos {

class CoreOobeActor;

class HIDDetectionScreenHandler
    : public HIDDetectionScreenActor,
      public BaseScreenHandler,
      public device::BluetoothAdapter::Observer,
      public device::BluetoothDevice::PairingDelegate,
      public InputServiceProxy::Observer {
 public:
  typedef device::InputServiceLinux::InputDeviceInfo InputDeviceInfo;

  explicit HIDDetectionScreenHandler(CoreOobeActor* core_oobe_actor);
  virtual ~HIDDetectionScreenHandler();

  
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void SetDelegate(Delegate* delegate) OVERRIDE;
  virtual void CheckIsScreenRequired(
      const base::Callback<void(bool)>& on_check_done) OVERRIDE;

  
  virtual void DeclareLocalizedValues(LocalizedValuesBuilder* builder) OVERRIDE;
  virtual void Initialize() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void RequestPinCode(device::BluetoothDevice* device) OVERRIDE;
  virtual void RequestPasskey(device::BluetoothDevice* device) OVERRIDE;
  virtual void DisplayPinCode(device::BluetoothDevice* device,
                              const std::string& pincode) OVERRIDE;
  virtual void DisplayPasskey(
      device::BluetoothDevice* device, uint32 passkey) OVERRIDE;
  virtual void KeysEntered(device::BluetoothDevice* device,
                           uint32 entered) OVERRIDE;
  virtual void ConfirmPasskey(
      device::BluetoothDevice* device, uint32 passkey) OVERRIDE;
  virtual void AuthorizePairing(device::BluetoothDevice* device) OVERRIDE;

  
  virtual void AdapterPresentChanged(device::BluetoothAdapter* adapter,
                                     bool present) OVERRIDE;
  virtual void DeviceAdded(device::BluetoothAdapter* adapter,
                           device::BluetoothDevice* device) OVERRIDE;
  virtual void DeviceChanged(device::BluetoothAdapter* adapter,
                             device::BluetoothDevice* device) OVERRIDE;
  virtual void DeviceRemoved(device::BluetoothAdapter* adapter,
                             device::BluetoothDevice* device) OVERRIDE;

  
  virtual void OnInputDeviceAdded(const InputDeviceInfo& info) OVERRIDE;
  virtual void OnInputDeviceRemoved(const std::string& id) OVERRIDE;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  
  enum ContinueScenarioType {
    
    POINTING_DEVICE_ONLY_DETECTED,

    
    KEYBOARD_DEVICE_ONLY_DETECTED,

    
    All_DEVICES_DETECTED,

    
    CONTINUE_SCENARIO_TYPE_SIZE
  };

  void InitializeAdapter(scoped_refptr<device::BluetoothAdapter> adapter);

  
  
  void SendPointingDeviceNotification();

  
  
  void SendKeyboardDeviceNotification(base::DictionaryValue* params);

  
  void ProcessConnectedDevicesList(const std::vector<InputDeviceInfo>& devices);

  
  
  void TryInitiateBTDevicesUpdate();

  
  
  void OnGetInputDevicesListForCheck(
      const base::Callback<void(bool)>& on_check_done,
      const std::vector<InputDeviceInfo>& devices);

  
  
  void OnGetInputDevicesList(const std::vector<InputDeviceInfo>& devices);

  void StartBTDiscoverySession();

  
  
  void BTConnected(device::BluetoothDevice::DeviceType device_type);

  
  
  
  void BTConnectError(const std::string& address,
                      device::BluetoothDevice::DeviceType device_type,
                      device::BluetoothDevice::ConnectErrorCode error_code);

  
  void HandleOnContinue();

  Delegate* delegate_;

  CoreOobeActor* core_oobe_actor_;

  
  bool show_on_init_;

  
  void DeviceConnecting(device::BluetoothDevice* device);

  
  
  void OnStartDiscoverySession(
      scoped_ptr<device::BluetoothDiscoverySession> discovery_session);

  
  
  void FindDevicesError();

  
  
  void SetPoweredError();

  
  
  void SetPoweredOffError();

  
  
  
  void UpdateDevices();

  
  
  void UpdateBTDevices();

  
  void ConnectBTDevice(device::BluetoothDevice* device);

  
  void TryPairingAsPointingDevice(device::BluetoothDevice* device);

  
  void TryPairingAsKeyboardDevice(device::BluetoothDevice* device);

  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  InputServiceProxy input_service_proxy_;

  
  
  
  scoped_ptr<device::BluetoothDiscoverySession> discovery_session_;

  
  std::string pointing_device_name_;
  std::string pointing_device_id_;
  bool mouse_is_pairing_;
  InputDeviceInfo::Type pointing_device_connect_type_;

  
  std::string keyboard_device_name_;
  std::string keyboard_device_id_;
  bool keyboard_is_pairing_;
  InputDeviceInfo::Type keyboard_device_connect_type_;

  bool switch_on_adapter_when_ready_;

  
  scoped_ptr<bool> adapter_initially_powered_;

  base::WeakPtrFactory<HIDDetectionScreenHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HIDDetectionScreenHandler);
};

}  

#endif  

