// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_WIN_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_WIN_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_task_manager_win.h"

namespace device {

class BluetoothAdapterWin;
class BluetoothServiceRecordWin;
class BluetoothSocketThread;

class BluetoothDeviceWin : public BluetoothDevice {
 public:
  explicit BluetoothDeviceWin(
      const BluetoothTaskManagerWin::DeviceState& device_state,
      const scoped_refptr<base::SequencedTaskRunner>& ui_task_runner,
      const scoped_refptr<BluetoothSocketThread>& socket_thread,
      net::NetLog* net_log,
      const net::NetLog::Source& net_log_source);
  virtual ~BluetoothDeviceWin();

  
  virtual uint32 GetBluetoothClass() const OVERRIDE;
  virtual std::string GetAddress() const OVERRIDE;
  virtual VendorIDSource GetVendorIDSource() const OVERRIDE;
  virtual uint16 GetVendorID() const OVERRIDE;
  virtual uint16 GetProductID() const OVERRIDE;
  virtual uint16 GetDeviceID() const OVERRIDE;
  virtual int GetRSSI() const OVERRIDE;
  virtual int GetCurrentHostTransmitPower() const OVERRIDE;
  virtual int GetMaximumHostTransmitPower() const OVERRIDE;
  virtual bool IsPaired() const OVERRIDE;
  virtual bool IsConnected() const OVERRIDE;
  virtual bool IsConnectable() const OVERRIDE;
  virtual bool IsConnecting() const OVERRIDE;
  virtual UUIDList GetUUIDs() const OVERRIDE;
  virtual bool ExpectingPinCode() const OVERRIDE;
  virtual bool ExpectingPasskey() const OVERRIDE;
  virtual bool ExpectingConfirmation() const OVERRIDE;
  virtual void Connect(
      PairingDelegate* pairing_delegate,
      const base::Closure& callback,
      const ConnectErrorCallback& error_callback) OVERRIDE;
  virtual void SetPinCode(const std::string& pincode) OVERRIDE;
  virtual void SetPasskey(uint32 passkey) OVERRIDE;
  virtual void ConfirmPairing() OVERRIDE;
  virtual void RejectPairing() OVERRIDE;
  virtual void CancelPairing() OVERRIDE;
  virtual void Disconnect(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void Forget(const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConnectToService(
      const BluetoothUUID& uuid,
      const ConnectToServiceCallback& callback,
      const ConnectToServiceErrorCallback& error_callback) OVERRIDE;
  virtual void CreateGattConnection(
      const GattConnectionCallback& callback,
      const ConnectErrorCallback& error_callback) OVERRIDE;
  virtual void StartConnectionMonitor(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  
  
  const BluetoothServiceRecordWin* GetServiceRecord(
      const device::BluetoothUUID& uuid) const;

  
  
  bool IsEqual(const BluetoothTaskManagerWin::DeviceState& device_state);

  
  
  void Update(const BluetoothTaskManagerWin::DeviceState& device_state);

 protected:
  
  virtual std::string GetDeviceName() const OVERRIDE;

 private:
  friend class BluetoothAdapterWin;

  
  
  void SetVisible(bool visible);

  
  void UpdateServices(const BluetoothTaskManagerWin::DeviceState& device_state);

  scoped_refptr<base::SequencedTaskRunner> ui_task_runner_;
  scoped_refptr<BluetoothSocketThread> socket_thread_;
  net::NetLog* net_log_;
  net::NetLog::Source net_log_source_;

  
  
  uint32 bluetooth_class_;

  
  std::string name_;

  
  std::string address_;

  
  
  bool paired_;
  bool connected_;

  
  
  bool visible_;

  
  UUIDList uuids_;

  
  typedef ScopedVector<BluetoothServiceRecordWin> ServiceRecordList;
  ServiceRecordList service_record_list_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothDeviceWin);
};

}  

#endif  
