// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_PROXY_H_
#define BASE_FILES_FILE_PROXY_H_

#include "base/base_export.h"
#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"

namespace tracked_objects {
class Location;
};

namespace base {

class TaskRunner;
class Time;

class BASE_EXPORT FileProxy : public SupportsWeakPtr<FileProxy> {
 public:
  
  
  
  typedef Callback<void(File::Error)> StatusCallback;

  typedef Callback<void(File::Error,
                        const FilePath&)> CreateTemporaryCallback;
  typedef Callback<void(File::Error,
                        const File::Info&)> GetFileInfoCallback;
  typedef Callback<void(File::Error,
                        const char* data,
                        int bytes_read)> ReadCallback;
  typedef Callback<void(File::Error,
                        int bytes_written)> WriteCallback;

  FileProxy();
  explicit FileProxy(TaskRunner* task_runner);
  ~FileProxy();

  
  
  
  
  
  
  bool CreateOrOpen(const FilePath& file_path,
                    uint32 file_flags,
                    const StatusCallback& callback);

  
  
  
  
  
  
  
  
  bool CreateTemporary(uint32 additional_file_flags,
                       const CreateTemporaryCallback& callback);

  
  bool IsValid() const;

  
  
  bool created() const { return file_.created(); }

  
  
  void SetFile(File file);

  File TakeFile();

  PlatformFile GetPlatformFile() const;

  
  
  bool Close(const StatusCallback& callback);

  
  
  bool GetInfo(const GetFileInfoCallback& callback);

  
  
  
  bool Read(int64 offset, int bytes_to_read, const ReadCallback& callback);

  
  
  
  bool Write(int64 offset,
             const char* buffer,
             int bytes_to_write,
             const WriteCallback& callback);

  
  
  bool SetTimes(Time last_access_time,
                Time last_modified_time,
                const StatusCallback& callback);

  
  
  bool SetLength(int64 length, const StatusCallback& callback);

  
  
  bool Flush(const StatusCallback& callback);

 private:
  friend class FileHelper;
  TaskRunner* task_runner() { return task_runner_.get(); }

  scoped_refptr<TaskRunner> task_runner_;
  File file_;
  DISALLOW_COPY_AND_ASSIGN(FileProxy);
};

}  

#endif  
