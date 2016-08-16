// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_WATCHER_MANAGER_H_
#define STORAGE_BROWSER_FILEAPI_WATCHER_MANAGER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file.h"

namespace base {
class Time;
}

namespace storage {

class FileSystemOperationContext;
class FileSystemURL;

class WatcherManager {
 public:
  typedef base::Callback<void(base::File::Error result)> StatusCallback;

  
  class Observer {
   public:
    Observer() {}
    virtual ~Observer() {}

    
    virtual void OnEntryChanged(const FileSystemURL& url) = 0;

    
    virtual void OnEntryRemoved(const FileSystemURL& url) = 0;
  };

  virtual ~WatcherManager() {}

  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;
  virtual bool HasObserver(Observer* observer) const = 0;

  
  
  
  
  
  virtual void WatchDirectory(const FileSystemURL& url,
                              bool recursive,
                              const StatusCallback& callback) = 0;

  
  virtual void UnwatchEntry(const FileSystemURL& url,
                            const StatusCallback& callback) = 0;
};

}  

#endif  
