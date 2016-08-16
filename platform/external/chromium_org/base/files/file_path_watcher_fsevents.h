// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_PATH_WATCHER_FSEVENTS_H_
#define BASE_FILES_FILE_PATH_WATCHER_FSEVENTS_H_

#include <CoreServices/CoreServices.h>

#include <vector>

#include "base/files/file_path.h"
#include "base/files/file_path_watcher.h"

namespace base {

class FilePathWatcherFSEvents : public FilePathWatcher::PlatformDelegate {
 public:
  FilePathWatcherFSEvents();

  
  void OnFilePathsChanged(const std::vector<FilePath>& paths);

  
  
  void UpdateEventStream(FSEventStreamEventId start_event);

  
  
  bool ResolveTargetPath();

  
  virtual bool Watch(const FilePath& path,
                     bool recursive,
                     const FilePathWatcher::Callback& callback) OVERRIDE;
  virtual void Cancel() OVERRIDE;

 private:
  virtual ~FilePathWatcherFSEvents();

  
  void DestroyEventStream();

  
  void StartEventStream(FSEventStreamEventId start_event);

  
  virtual void CancelOnMessageLoopThread() OVERRIDE;

  
  FilePathWatcher::Callback callback_;

  
  FilePath target_;

  
  FilePath resolved_target_;

  
  FSEventStreamRef fsevent_stream_;

  DISALLOW_COPY_AND_ASSIGN(FilePathWatcherFSEvents);
};

}  

#endif  
