// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_FILE_SYSTEM_ENTRY_WATCHER_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_API_FILE_SYSTEM_ENTRY_WATCHER_SERVICE_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "storage/browser/fileapi/file_system_url.h"
#include "storage/browser/fileapi/watcher_manager.h"

namespace content {
class BrowserContext;
}  

namespace storage {
class FileSystemContext;
}  

namespace extensions {
struct Event;
class EventRouter;

class EntryWatcherService : public KeyedService,
                            public storage::WatcherManager::Observer {
 public:
  typedef base::Callback<
      void(const std::string& extension_id, scoped_ptr<Event> event)>
      DispatchEventImplCallback;

  typedef base::Callback<storage::FileSystemContext*(
      const std::string& extension_id,
      content::BrowserContext* context)> GetFileSystemContextImplCallback;

  explicit EntryWatcherService(content::BrowserContext* context);
  virtual ~EntryWatcherService();

  
  
  void WatchDirectory(const std::string& extension_id,
                      const storage::FileSystemURL& url,
                      bool recursive,
                      const storage::WatcherManager::StatusCallback& callback);

  
  void UnwatchEntry(const std::string& extension_id,
                    const storage::FileSystemURL& url,
                    const storage::WatcherManager::StatusCallback& callback);

  std::vector<storage::FileSystemURL> GetWatchedEntries(
      const std::string& extension_id);

  
  virtual void OnEntryChanged(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnEntryRemoved(const storage::FileSystemURL& url) OVERRIDE;

  
  
  void SetDispatchEventImplForTesting(
      const DispatchEventImplCallback& callback);

  
  
  void SetGetFileSystemContextImplForTesting(
      const GetFileSystemContextImplCallback& callback);

 private:
  
  struct EntryWatcher {
    EntryWatcher();
    EntryWatcher(const storage::FileSystemURL& url,
                 bool directory,
                 bool recursive);
    ~EntryWatcher();

    storage::FileSystemURL url;
    bool directory;
    bool recursive;
  };

  
  
  typedef std::map<storage::FileSystemURL,
                   std::map<std::string, EntryWatcher>,
                   storage::FileSystemURL::Comparator> WatcherMap;

  
  
  void OnWatchDirectoryCompleted(
      storage::WatcherManager* watcher_manager,
      const std::string& extension_id,
      const storage::FileSystemURL& url,
      bool recursive,
      const storage::WatcherManager::StatusCallback& callback,
      base::File::Error result);

  
  
  void OnUnwatchEntryCompleted(
      const std::string& extension_id,
      const storage::FileSystemURL& url,
      const storage::WatcherManager::StatusCallback& callback,
      base::File::Error result);

  content::BrowserContext* context_;
  WatcherMap watchers_;
  DispatchEventImplCallback dispatch_event_impl_;
  GetFileSystemContextImplCallback get_file_system_context_impl_;
  ScopedObserver<storage::WatcherManager, storage::WatcherManager::Observer>
      observing_;
  base::WeakPtrFactory<EntryWatcherService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EntryWatcherService);
};

}  

#endif  
