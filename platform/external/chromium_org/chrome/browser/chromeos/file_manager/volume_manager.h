// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_VOLUME_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_VOLUME_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "chrome/browser/chromeos/drive/drive_integration_service.h"
#include "chrome/browser/chromeos/file_system_provider/observer.h"
#include "chrome/browser/chromeos/file_system_provider/service.h"
#include "chromeos/dbus/cros_disks_client.h"
#include "chromeos/disks/disk_mount_manager.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/storage_monitor/removable_storage_observer.h"

class Profile;

namespace chromeos {
class PowerManagerClient;
}  

namespace content {
class BrowserContext;
}  

namespace file_manager {

class MountedDiskMonitor;
class SnapshotManager;
class VolumeManagerObserver;

enum VolumeType {
  VOLUME_TYPE_TESTING = -1,  
  VOLUME_TYPE_GOOGLE_DRIVE = 0,
  VOLUME_TYPE_DOWNLOADS_DIRECTORY,
  VOLUME_TYPE_REMOVABLE_DISK_PARTITION,
  VOLUME_TYPE_MOUNTED_ARCHIVE_FILE,
  VOLUME_TYPE_CLOUD_DEVICE,
  VOLUME_TYPE_PROVIDED,  
  VOLUME_TYPE_MTP,
  
  
  
  
  NUM_VOLUME_TYPE,
};

struct VolumeInfo {
  VolumeInfo();
  ~VolumeInfo();

  
  std::string volume_id;

  
  
  std::string file_system_id;

  
  
  std::string extension_id;

  
  VolumeType type;

  
  chromeos::DeviceType device_type;

  
  
  
  base::FilePath source_path;

  
  
  
  
  
  base::FilePath mount_path;

  
  chromeos::disks::MountCondition mount_condition;

  
  
  base::FilePath system_path_prefix;

  
  
  
  std::string volume_label;

  
  bool is_parent;

  
  bool is_read_only;
};

class VolumeManager : public KeyedService,
                      public drive::DriveIntegrationServiceObserver,
                      public chromeos::disks::DiskMountManager::Observer,
                      public chromeos::file_system_provider::Observer,
                      public storage_monitor::RemovableStorageObserver {
 public:
  VolumeManager(
      Profile* profile,
      drive::DriveIntegrationService* drive_integration_service,
      chromeos::PowerManagerClient* power_manager_client,
      chromeos::disks::DiskMountManager* disk_mount_manager,
      chromeos::file_system_provider::Service* file_system_provider_service);
  virtual ~VolumeManager();

  
  static VolumeManager* Get(content::BrowserContext* context);

  
  void Initialize();

  
  virtual void Shutdown() OVERRIDE;

  
  void AddObserver(VolumeManagerObserver* observer);

  
  void RemoveObserver(VolumeManagerObserver* observer);

  
  std::vector<VolumeInfo> GetVolumeInfoList() const;

  
  // result is written into |result|. Returns false otherwise.
  bool FindVolumeInfoById(const std::string& volume_id,
                          VolumeInfo* result) const;

  
  
  bool RegisterDownloadsDirectoryForTesting(const base::FilePath& path);

  
  
  void AddVolumeInfoForTesting(const base::FilePath& path,
                               VolumeType volume_type,
                               chromeos::DeviceType device_type);

  
  virtual void OnFileSystemMounted() OVERRIDE;
  virtual void OnFileSystemBeingUnmounted() OVERRIDE;

  
  virtual void OnDiskEvent(
      chromeos::disks::DiskMountManager::DiskEvent event,
      const chromeos::disks::DiskMountManager::Disk* disk) OVERRIDE;
  virtual void OnDeviceEvent(
      chromeos::disks::DiskMountManager::DeviceEvent event,
      const std::string& device_path) OVERRIDE;
  virtual void OnMountEvent(
      chromeos::disks::DiskMountManager::MountEvent event,
      chromeos::MountError error_code,
      const chromeos::disks::DiskMountManager::MountPointInfo& mount_info)
      OVERRIDE;
  virtual void OnFormatEvent(
      chromeos::disks::DiskMountManager::FormatEvent event,
      chromeos::FormatError error_code,
      const std::string& device_path) OVERRIDE;

  
  virtual void OnProvidedFileSystemMount(
      const chromeos::file_system_provider::ProvidedFileSystemInfo&
          file_system_info,
      base::File::Error error) OVERRIDE;
  virtual void OnProvidedFileSystemUnmount(
      const chromeos::file_system_provider::ProvidedFileSystemInfo&
          file_system_info,
      base::File::Error error) OVERRIDE;

  
  void OnExternalStorageDisabledChanged();

  
  virtual void OnRemovableStorageAttached(
      const storage_monitor::StorageInfo& info) OVERRIDE;
  virtual void OnRemovableStorageDetached(
      const storage_monitor::StorageInfo& info) OVERRIDE;

  SnapshotManager* snapshot_manager() { return snapshot_manager_.get(); }

 private:
  void OnDiskMountManagerRefreshed(bool success);
  void OnStorageMonitorInitialized();
  void DoMountEvent(chromeos::MountError error_code,
                    const VolumeInfo& volume_info);
  void DoUnmountEvent(chromeos::MountError error_code,
                      const VolumeInfo& volume_info);

  Profile* profile_;
  drive::DriveIntegrationService* drive_integration_service_;  
  chromeos::disks::DiskMountManager* disk_mount_manager_;      
  PrefChangeRegistrar pref_change_registrar_;
  ObserverList<VolumeManagerObserver> observers_;
  chromeos::file_system_provider::Service*
      file_system_provider_service_;  
  std::map<std::string, VolumeInfo> mounted_volumes_;
  scoped_ptr<SnapshotManager> snapshot_manager_;

  
  
  base::WeakPtrFactory<VolumeManager> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(VolumeManager);
};

}  

#endif  
