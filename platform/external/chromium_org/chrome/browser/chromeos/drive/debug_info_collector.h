// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_DEBUG_INFO_COLLECTOR_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_DEBUG_INFO_COLLECTOR_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "chrome/browser/chromeos/drive/file_system_interface.h"

namespace drive {

class DebugInfoCollector {
 public:
  
  typedef base::Callback<void(FileError error,
                              scoped_ptr<ResourceEntryVector> entries)>
      ReadDirectoryCallback;

  
  typedef base::Callback<void(const std::string& id,
                              const FileCacheEntry& cache_entry)>
      IterateFileCacheCallback;

  DebugInfoCollector(internal::ResourceMetadata* metadata,
                     FileSystemInterface* file_system,
                     base::SequencedTaskRunner* blocking_task_runner);
  ~DebugInfoCollector();

  
  
  void GetResourceEntry(const base::FilePath& file_path,
                        const GetResourceEntryCallback& callback);

  
  
  void ReadDirectory(const base::FilePath& file_path,
                     const ReadDirectoryCallback& callback);


  
  
  
  void IterateFileCache(const IterateFileCacheCallback& iteration_callback,
                        const base::Closure& completion_callback);

  
  
  void GetMetadata(const GetFilesystemMetadataCallback& callback);

 private:
  internal::ResourceMetadata* metadata_;  
  FileSystemInterface* file_system_;  
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(DebugInfoCollector);
};

}  

#endif  
