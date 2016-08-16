// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_UTIL_PROXY_H_
#define BASE_FILES_FILE_UTIL_PROXY_H_

#include "base/base_export.h"
#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_path.h"

namespace base {

class TaskRunner;
class Time;

class BASE_EXPORT FileUtilProxy {
 public:
  
  
  
  typedef Callback<void(File::Error)> StatusCallback;

  typedef Callback<void(File::Error,
                        const File::Info&)> GetFileInfoCallback;

  
  
  
  static bool GetFileInfo(
      TaskRunner* task_runner,
      const FilePath& file_path,
      const GetFileInfoCallback& callback);

  
  
  
  static bool DeleteFile(TaskRunner* task_runner,
                         const FilePath& file_path,
                         bool recursive,
                         const StatusCallback& callback);

  
  
  static bool Touch(
      TaskRunner* task_runner,
      const FilePath& file_path,
      const Time& last_access_time,
      const Time& last_modified_time,
      const StatusCallback& callback);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(FileUtilProxy);
};

}  

#endif  
