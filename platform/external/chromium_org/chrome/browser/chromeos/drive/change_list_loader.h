// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_CHANGE_LIST_LOADER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_CHANGE_LIST_LOADER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "google_apis/drive/drive_common_callbacks.h"
#include "google_apis/drive/gdata_errorcode.h"

class GURL;

namespace base {
class ScopedClosureRunner;
class SequencedTaskRunner;
class Time;
}  

namespace google_apis {
class AboutResource;
class ResourceList;
}  

namespace drive {

class EventLogger;
class JobScheduler;
class ResourceEntry;

namespace internal {

class ChangeList;
class ChangeListLoaderObserver;
class ChangeListProcessor;
class DirectoryLoader;
class ResourceMetadata;

class LoaderController {
 public:
  LoaderController();
  ~LoaderController();

  
  
  
  scoped_ptr<base::ScopedClosureRunner> GetLock();

  
  void ScheduleRun(const base::Closure& task);

 private:
  
  void Unlock();

  int lock_count_;
  std::vector<base::Closure> pending_tasks_;

  base::WeakPtrFactory<LoaderController> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(LoaderController);
};

class AboutResourceLoader {
 public:
  explicit AboutResourceLoader(JobScheduler* scheduler);
  ~AboutResourceLoader();

  
  
  const google_apis::AboutResource* cached_about_resource() const {
    return cached_about_resource_.get();
  }

  
  
  
  
  
  void GetAboutResource(const google_apis::AboutResourceCallback& callback);

  
  
  
  void UpdateAboutResource(const google_apis::AboutResourceCallback& callback);

 private:
  
  
  
  
  void UpdateAboutResourceAfterGetAbout(
      int task_id,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::AboutResource> about_resource);

  JobScheduler* scheduler_;
  scoped_ptr<google_apis::AboutResource> cached_about_resource_;

  
  int current_update_task_id_;
  
  
  
  std::map<int, std::vector<google_apis::AboutResourceCallback> >
      pending_callbacks_;

  base::WeakPtrFactory<AboutResourceLoader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(AboutResourceLoader);
};

class ChangeListLoader {
 public:
  
  class FeedFetcher;

  ChangeListLoader(EventLogger* logger,
                   base::SequencedTaskRunner* blocking_task_runner,
                   ResourceMetadata* resource_metadata,
                   JobScheduler* scheduler,
                   AboutResourceLoader* about_resource_loader,
                   LoaderController* apply_task_controller);
  ~ChangeListLoader();

  
  
  
  bool IsRefreshing() const;

  
  void AddObserver(ChangeListLoaderObserver* observer);
  void RemoveObserver(ChangeListLoaderObserver* observer);

  
  
  
  
  void CheckForUpdates(const FileOperationCallback& callback);

  
  
  
  
  
  
  
  void LoadIfNeeded(const FileOperationCallback& callback);

 private:
  
  void Load(const FileOperationCallback& callback);
  void LoadAfterGetLargestChangestamp(bool is_initial_load,
                                      const int64* local_changestamp,
                                      FileError error);
  void LoadAfterGetAboutResource(
      int64 local_changestamp,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::AboutResource> about_resource);

  
  
  
  void OnChangeListLoadComplete(FileError error);

  
  
  void OnAboutResourceUpdated(google_apis::GDataErrorCode error,
                              scoped_ptr<google_apis::AboutResource> resource);

  

  
  
  
  void LoadChangeListFromServer(int64 start_changestamp);

  
  
  void LoadChangeListFromServerAfterLoadChangeList(
      scoped_ptr<google_apis::AboutResource> about_resource,
      bool is_delta_update,
      FileError error,
      ScopedVector<ChangeList> change_lists);

  
  
  void LoadChangeListFromServerAfterUpdate(
      ChangeListProcessor* change_list_processor,
      bool should_notify_changed_directories,
      const base::Time& start_time,
      FileError error);

  EventLogger* logger_;  
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  ResourceMetadata* resource_metadata_;  
  JobScheduler* scheduler_;  
  AboutResourceLoader* about_resource_loader_;  
  LoaderController* loader_controller_;  
  ObserverList<ChangeListLoaderObserver> observers_;
  std::vector<FileOperationCallback> pending_load_callback_;
  FileOperationCallback pending_update_check_callback_;

  
  scoped_ptr<FeedFetcher> change_feed_fetcher_;

  
  
  bool loaded_;

  
  
  base::WeakPtrFactory<ChangeListLoader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(ChangeListLoader);
};

}  
}  

#endif  
