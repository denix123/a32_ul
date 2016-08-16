// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_TASK_MANAGER_WIN_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_TASK_MANAGER_WIN_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "base/win/scoped_handle.h"
#include "device/bluetooth/bluetooth_adapter.h"

namespace base {

class SequencedTaskRunner;
class SequencedWorkerPool;

}  

namespace device {

class BluetoothTaskManagerWin
    : public base::RefCountedThreadSafe<BluetoothTaskManagerWin> {
 public:
  struct AdapterState {
    AdapterState();
    ~AdapterState();
    std::string name;
    std::string address;
    bool powered;
  };

  struct ServiceRecordState {
    ServiceRecordState();
    ~ServiceRecordState();
    
    std::string name;
    
    std::vector<uint8> sdp_bytes;
    
    BluetoothUUID gatt_uuid;
  };

  struct DeviceState {
    DeviceState();
    ~DeviceState();

    bool is_bluetooth_classic() const { return path.empty(); }

    
    std::string address;  
    std::string name;     
    bool visible;
    bool connected;
    bool authenticated;
    ScopedVector<ServiceRecordState> service_record_states;
    
    uint32 bluetooth_class;
    
    base::FilePath path;
  };

  class Observer {
   public:
     virtual ~Observer() {}

     virtual void AdapterStateChanged(const AdapterState& state) {}
     virtual void DiscoveryStarted(bool success) {}
     virtual void DiscoveryStopped() {}
     
     
     
     
     
     
     
     virtual void DevicesPolled(const ScopedVector<DeviceState>& devices) {}
  };

  explicit BluetoothTaskManagerWin(
      scoped_refptr<base::SequencedTaskRunner> ui_task_runner);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  void Initialize();
  void InitializeWithBluetoothTaskRunner(
      scoped_refptr<base::SequencedTaskRunner> bluetooth_task_runner);
  void Shutdown();

  void PostSetPoweredBluetoothTask(
      bool powered,
      const base::Closure& callback,
      const BluetoothAdapter::ErrorCallback& error_callback);
  void PostStartDiscoveryTask();
  void PostStopDiscoveryTask();

 private:
  friend class base::RefCountedThreadSafe<BluetoothTaskManagerWin>;
  friend class BluetoothTaskManagerWinTest;

  static const int kPollIntervalMs;

  virtual ~BluetoothTaskManagerWin();

  
  
  void LogPollingError(const char* message, int win32_error);

  
  
  void OnAdapterStateChanged(const AdapterState* state);
  void OnDiscoveryStarted(bool success);
  void OnDiscoveryStopped();
  void OnDevicesPolled(const ScopedVector<DeviceState>* devices);

  
  void StartPolling();
  void PollAdapter();
  void PostAdapterStateToUi();
  void SetPowered(bool powered,
                  const base::Closure& callback,
                  const BluetoothAdapter::ErrorCallback& error_callback);

  
  
  
  
  void StartDiscovery();
  void StopDiscovery();

  
  
  
  
  void DiscoverDevices(int timeout_multiplier);

  
  
  
  void GetKnownDevices();

  
  
  bool SearchDevices(int timeout_multiplier,
                     bool search_cached_devices_only,
                     ScopedVector<DeviceState>* device_list);

  
  
  bool SearchClassicDevices(int timeout_multiplier,
                            bool search_cached_devices_only,
                            ScopedVector<DeviceState>* device_list);

  
  bool SearchLowEnergyDevices(ScopedVector<DeviceState>* device_list);

  
  bool DiscoverServices(ScopedVector<DeviceState>* device_list,
                        bool search_cached_services_only);

  
  bool DiscoverClassicDeviceServices(
      const std::string& device_address,
      const GUID& protocol_uuid,
      bool search_cached_services_only,
      ScopedVector<ServiceRecordState>* service_record_states);

  
  
  int DiscoverClassicDeviceServicesWorker(
      const std::string& device_address,
      const GUID& protocol_uuid,
      bool search_cached_services_only,
      ScopedVector<ServiceRecordState>* service_record_states);

  
  bool DiscoverLowEnergyDeviceServices(
      const base::FilePath& device_path,
      ScopedVector<ServiceRecordState>* service_record_states);

  
  scoped_refptr<base::SequencedTaskRunner> ui_task_runner_;

  scoped_refptr<base::SequencedWorkerPool> worker_pool_;
  scoped_refptr<base::SequencedTaskRunner> bluetooth_task_runner_;

  
  ObserverList<Observer> observers_;

  
  base::win::ScopedHandle adapter_handle_;

  
  bool discovering_;

  
  base::TimeTicks current_logging_batch_ticks_;
  int current_logging_batch_count_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothTaskManagerWin);
};

}  

#endif  
