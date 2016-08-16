// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_DEVICE_EVENT_ROUTER_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_DEVICE_EVENT_ROUTER_H_

#include <map>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "chrome/browser/chromeos/file_manager/volume_manager_observer.h"
#include "chrome/common/extensions/api/file_manager_private.h"
#include "chromeos/dbus/power_manager_client.h"

namespace file_manager {

enum DeviceState {
  
  DEVICE_STATE_USUAL,
  
  DEVICE_HARD_UNPLUGGED,
  
  DEVICE_HARD_UNPLUGGED_AND_REPORTED
};

class DeviceEventRouter : public VolumeManagerObserver,
                          public chromeos::PowerManagerClient::Observer {
 public:
  DeviceEventRouter();

  
  
  explicit DeviceEventRouter(base::TimeDelta overriding_time_delta);

  virtual ~DeviceEventRouter();

  
  void Startup();

  
  virtual void OnDiskAdded(const chromeos::disks::DiskMountManager::Disk& disk,
                           bool mounting) OVERRIDE;
  virtual void OnDiskRemoved(
      const chromeos::disks::DiskMountManager::Disk& disk) OVERRIDE;
  virtual void OnDeviceAdded(const std::string& device_path) OVERRIDE;
  virtual void OnDeviceRemoved(const std::string& device_path) OVERRIDE;
  virtual void OnVolumeMounted(chromeos::MountError error_code,
                               const VolumeInfo& volume_info) OVERRIDE;
  virtual void OnVolumeUnmounted(chromeos::MountError error_code,
                                 const VolumeInfo& volume_info) OVERRIDE;
  virtual void OnFormatStarted(const std::string& device_path,
                               bool success) OVERRIDE;
  virtual void OnFormatCompleted(const std::string& device_path,
                                 bool success) OVERRIDE;

  
  virtual void SuspendImminent() OVERRIDE;
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;

  bool is_resuming() const { return is_resuming_; }
  bool is_starting_up() const { return is_starting_up_; }

 protected:
  
  virtual void OnDeviceEvent(
      extensions::api::file_manager_private::DeviceEventType type,
      const std::string& device_path) = 0;
  
  virtual bool IsExternalStorageDisabled() = 0;

 private:
  void StartupDelayed();
  void OnDeviceAddedDelayed(const std::string& device_path);
  void SuspendDoneDelayed();

  
  DeviceState GetDeviceState(const std::string& device_path) const;

  
  void SetDeviceState(const std::string& device_path, DeviceState state);

  
  const base::TimeDelta resume_time_delta_;
  const base::TimeDelta startup_time_delta_;

  
  bool is_starting_up_;

  
  bool is_resuming_;

  
  std::map<std::string, DeviceState> device_states_;

  
  base::ThreadChecker thread_checker_;

  
  
  base::WeakPtrFactory<DeviceEventRouter> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(DeviceEventRouter);
};
}  

#endif  
