// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OPERATION_TEST_BASE_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OPERATION_TEST_BASE_H_

#include <set>

#include "base/files/scoped_temp_dir.h"
#include "chrome/browser/chromeos/drive/drive.pb.h"
#include "chrome/browser/chromeos/drive/file_change.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/file_system/operation_delegate.h"
#include "chrome/browser/chromeos/drive/test_util.h"
#include "content/public/test/test_browser_thread_bundle.h"
#include "testing/gtest/include/gtest/gtest.h"

class TestingPrefServiceSimple;

namespace base {
class SequencedTaskRunner;
}  

namespace drive {

class EventLogger;
class FakeDriveService;
class FakeFreeDiskSpaceGetter;
class JobScheduler;

namespace internal {
class AboutResourceLoader;
class ChangeListLoader;
class FileCache;
class LoaderController;
class ResourceMetadata;
class ResourceMetadataStorage;
}  

namespace file_system {

class OperationTestBase : public testing::Test {
 protected:
  
  class LoggingDelegate : public OperationDelegate {
   public:
    typedef base::Callback<bool(
        const std::string& local_id,
        const FileOperationCallback& callback)> WaitForSyncCompleteHandler;

    LoggingDelegate();
    ~LoggingDelegate();

    
    virtual void OnFileChangedByOperation(
        const FileChange& changed_files) OVERRIDE;
    virtual void OnEntryUpdatedByOperation(
        const std::string& local_id) OVERRIDE;
    virtual void OnDriveSyncError(DriveSyncErrorType type,
                                  const std::string& local_id) OVERRIDE;
    virtual bool WaitForSyncComplete(
        const std::string& local_id,
        const FileOperationCallback& callback) OVERRIDE;

    
    const FileChange& get_changed_files() { return changed_files_; }

    
    const std::set<std::string>& updated_local_ids() const {
      return updated_local_ids_;
    }

    
    const std::vector<DriveSyncErrorType>& drive_sync_errors() const {
      return drive_sync_errors_;
    }

    
    void set_wait_for_sync_complete_handler(
        const WaitForSyncCompleteHandler& wait_for_sync_complete_handler) {
      wait_for_sync_complete_handler_ = wait_for_sync_complete_handler;
    }

   private:
    FileChange changed_files_;
    std::set<std::string> updated_local_ids_;
    std::vector<DriveSyncErrorType> drive_sync_errors_;
    WaitForSyncCompleteHandler wait_for_sync_complete_handler_;
  };

  OperationTestBase();
  explicit OperationTestBase(int test_thread_bundle_options);
  virtual ~OperationTestBase();

  
  virtual void SetUp() OVERRIDE;

  
  base::FilePath temp_dir() const { return temp_dir_.path(); }

  
  
  FileError GetLocalResourceEntry(const base::FilePath& path,
                                  ResourceEntry* entry);

  
  
  FileError GetLocalResourceEntryById(const std::string& local_id,
                                      ResourceEntry* entry);

  
  std::string GetLocalId(const base::FilePath& path);

  
  
  FileError CheckForUpdates();

  
  FakeDriveService* fake_service() {
    return fake_drive_service_.get();
  }
  EventLogger* logger() { return logger_.get(); }
  LoggingDelegate* delegate() { return &delegate_; }
  JobScheduler* scheduler() { return scheduler_.get(); }
  base::SequencedTaskRunner* blocking_task_runner() {
    return blocking_task_runner_.get();
  }
  FakeFreeDiskSpaceGetter* fake_free_disk_space_getter() {
    return fake_free_disk_space_getter_.get();
  }
  internal::FileCache* cache() { return cache_.get(); }
  internal::ResourceMetadata* metadata() { return metadata_.get(); }
  internal::LoaderController* loader_controller() {
    return loader_controller_.get();
  }
  internal::ChangeListLoader* change_list_loader() {
    return change_list_loader_.get();
  }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  scoped_ptr<TestingPrefServiceSimple> pref_service_;
  base::ScopedTempDir temp_dir_;

  LoggingDelegate delegate_;
  scoped_ptr<EventLogger> logger_;
  scoped_ptr<FakeDriveService> fake_drive_service_;
  scoped_ptr<JobScheduler> scheduler_;
  scoped_ptr<internal::ResourceMetadataStorage,
             test_util::DestroyHelperForTests> metadata_storage_;
  scoped_ptr<FakeFreeDiskSpaceGetter> fake_free_disk_space_getter_;
  scoped_ptr<internal::FileCache, test_util::DestroyHelperForTests> cache_;
  scoped_ptr<internal::ResourceMetadata, test_util::DestroyHelperForTests>
      metadata_;
  scoped_ptr<internal::AboutResourceLoader> about_resource_loader_;
  scoped_ptr<internal::LoaderController> loader_controller_;
  scoped_ptr<internal::ChangeListLoader> change_list_loader_;
};

}  
}  

#endif  
