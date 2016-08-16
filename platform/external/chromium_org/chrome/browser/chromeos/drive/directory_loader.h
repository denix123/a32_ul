// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_DIRECTORY_LOADER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_DIRECTORY_LOADER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/file_system_interface.h"
#include "google_apis/drive/drive_common_callbacks.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace base {
class SequencedTaskRunner;
}  

namespace google_apis {
class AboutResource;
}  

namespace drive {

class EventLogger;
class JobScheduler;
class ResourceEntry;

namespace internal {

class AboutResourceLoader;
class ChangeList;
class ChangeListLoaderObserver;
class DirectoryFetchInfo;
class LoaderController;
class ResourceMetadata;

class DirectoryLoader {
 public:
  DirectoryLoader(EventLogger* logger,
                  base::SequencedTaskRunner* blocking_task_runner,
                  ResourceMetadata* resource_metadata,
                  JobScheduler* scheduler,
                  AboutResourceLoader* about_resource_loader,
                  LoaderController* apply_task_controller);
  ~DirectoryLoader();

  
  void AddObserver(ChangeListLoaderObserver* observer);
  void RemoveObserver(ChangeListLoaderObserver* observer);

  
  
  
  void ReadDirectory(const base::FilePath& directory_path,
                     const ReadDirectoryEntriesCallback& entries_callback,
                     const FileOperationCallback& completion_callback);

 private:
  class FeedFetcher;
  struct ReadDirectoryCallbackState;

  
  void ReadDirectoryAfterGetEntry(
      const base::FilePath& directory_path,
      const ReadDirectoryEntriesCallback& entries_callback,
      const FileOperationCallback& completion_callback,
      bool should_try_loading_parent,
      const ResourceEntry* entry,
      FileError error);
  void ReadDirectoryAfterLoadParent(
      const base::FilePath& directory_path,
      const ReadDirectoryEntriesCallback& entries_callback,
      const FileOperationCallback& completion_callback,
      FileError error);
  void ReadDirectoryAfterGetAboutResource(
      const std::string& local_id,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::AboutResource> about_resource);
  void ReadDirectoryAfterCheckLocalState(
      scoped_ptr<google_apis::AboutResource> about_resource,
      const std::string& local_id,
      const ResourceEntry* entry,
      const int64* local_changestamp,
      FileError error);

  
  
  
  void OnDirectoryLoadComplete(const std::string& local_id, FileError error);
  void OnDirectoryLoadCompleteAfterRead(const std::string& local_id,
                                        const ResourceEntryVector* entries,
                                        FileError error);

  
  void SendEntries(const std::string& local_id,
                   const ResourceEntryVector& entries);

  
  
  
  void LoadDirectoryFromServer(const DirectoryFetchInfo& directory_fetch_info);

  
  void LoadDirectoryFromServerAfterLoad(
      const DirectoryFetchInfo& directory_fetch_info,
      FeedFetcher* fetcher,
      FileError error);

  
  void LoadDirectoryFromServerAfterUpdateChangestamp(
      const DirectoryFetchInfo& directory_fetch_info,
      const base::FilePath* directory_path,
      FileError error);

  EventLogger* logger_;  
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  ResourceMetadata* resource_metadata_;  
  JobScheduler* scheduler_;  
  AboutResourceLoader* about_resource_loader_;  
  LoaderController* loader_controller_;  
  ObserverList<ChangeListLoaderObserver> observers_;
  typedef std::map<std::string, std::vector<ReadDirectoryCallbackState> >
      LoadCallbackMap;
  LoadCallbackMap pending_load_callback_;

  
  std::set<FeedFetcher*> fast_fetch_feed_fetcher_set_;

  
  
  base::WeakPtrFactory<DirectoryLoader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(DirectoryLoader);
};

}  
}  

#endif  
