// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_EXTERNAL_UPDATER_H_
#define CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_EXTERNAL_UPDATER_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/sequenced_task_runner.h"
#include "chrome/browser/chromeos/app_mode/kiosk_external_update_validator.h"
#include "chromeos/disks/disk_mount_manager.h"

namespace chromeos {

class KioskExternalUpdateNotification;

class KioskExternalUpdater : public disks::DiskMountManager::Observer,
                             public KioskExternalUpdateValidatorDelegate {
 public:
  enum ExternalUpdateErrorCode {
    ERROR_NONE,
    ERROR_NO_MANIFEST,
    ERROR_INVALID_MANIFEST,
  };

  KioskExternalUpdater(
      const scoped_refptr<base::SequencedTaskRunner>& backend_task_runner,
      const base::FilePath& crx_cache_dir,
      const base::FilePath& crx_unpack_dir);

  virtual ~KioskExternalUpdater();

 private:
  enum ExternalUpdateStatus {
    PENDING,
    SUCCESS,
    FAILED,
  };
  struct ExternalUpdate {
    ExternalUpdate();

    std::string app_name;
    base::FilePath external_crx;
    ExternalUpdateStatus update_status;
    base::string16 error;
  };

  
  virtual void OnDiskEvent(disks::DiskMountManager::DiskEvent event,
                           const disks::DiskMountManager::Disk* disk) OVERRIDE;
  virtual void OnDeviceEvent(disks::DiskMountManager::DeviceEvent event,
                             const std::string& device_path) OVERRIDE;
  virtual void OnMountEvent(
      disks::DiskMountManager::MountEvent event,
      MountError error_code,
      const disks::DiskMountManager::MountPointInfo& mount_info) OVERRIDE;
  virtual void OnFormatEvent(disks::DiskMountManager::FormatEvent event,
                             FormatError error_code,
                             const std::string& device_path) OVERRIDE;

  
  virtual void OnExtenalUpdateUnpackSuccess(
      const std::string& app_id,
      const std::string& version,
      const std::string& min_browser_version,
      const base::FilePath& temp_dir) OVERRIDE;
  virtual void OnExternalUpdateUnpackFailure(
      const std::string& app_id) OVERRIDE;

  
  
  void ProcessParsedManifest(ExternalUpdateErrorCode* parsing_error,
                             const base::FilePath& external_update_dir,
                             base::DictionaryValue* parsed_manifest);

  
  
  bool CheckExternalUpdateInterrupted();

  
  void ValidateExternalUpdates();

  
  bool IsExternalUpdatePending();

  
  
  bool IsAllExternalUpdatesSucceeded();

  
  
  bool ShouldDoExternalUpdate(const std::string& app_id,
                              const std::string& version,
                              const std::string& min_browser_version);

  
  
  void PutValidatedExtension(bool* crx_copied,
                             const std::string& app_id,
                             const base::FilePath& crx_file,
                             const std::string& version);

  
  
  void OnPutValidatedExtension(const std::string& app_id, bool success);

  void NotifyKioskUpdateProgress(const base::string16& message);

  void MaybeValidateNextExternalUpdate();

  
  
  void MayBeNotifyKioskAppUpdate();

  void NotifyKioskAppUpdateAvailable();

  
  void DismissKioskUpdateNotification();

  
  base::string16 GetUpdateReportMessage();

  
  const scoped_refptr<base::SequencedTaskRunner> backend_task_runner_;

  
  const base::FilePath crx_cache_dir_;

  
  const base::FilePath crx_unpack_dir_;

  
  base::FilePath external_update_path_;

  
  typedef std::map<std::string, ExternalUpdate> ExternalUpdateMap;
  ExternalUpdateMap external_updates_;
  scoped_ptr<KioskExternalUpdateNotification> notification_;

  base::WeakPtrFactory<KioskExternalUpdater> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(KioskExternalUpdater);
};

}  

#endif  
