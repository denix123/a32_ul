// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_MTP_DEVICE_ASYNC_DELEGATE_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_MTP_DEVICE_ASYNC_DELEGATE_H_

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "storage/browser/fileapi/async_file_util.h"

namespace base {
class FilePath;
}

namespace net {
class IOBuffer;
}

class MTPDeviceAsyncDelegate {
 public:
  
  typedef base::Callback<
      void(const base::File::Info& file_info)> GetFileInfoSuccessCallback;

  
  typedef base::Callback<
      void(const storage::AsyncFileUtil::EntryList& file_list, bool has_more)>
      ReadDirectorySuccessCallback;

  
  
  typedef base::Callback<void(base::File::Error error)> ErrorCallback;

  
  typedef base::Callback<
      void(const base::File::Info& file_info,
           const base::FilePath& local_path)> CreateSnapshotFileSuccessCallback;

  
  typedef base::Callback<
      void(const base::File::Info& file_info,
           int bytes_read)> ReadBytesSuccessCallback;

  struct ReadBytesRequest {
    ReadBytesRequest(uint32 file_id,
                     net::IOBuffer* buf, int64 offset, int buf_len,
                     const ReadBytesSuccessCallback& success_callback,
                     const ErrorCallback& error_callback);
    ~ReadBytesRequest();

    uint32 file_id;
    scoped_refptr<net::IOBuffer> buf;
    int64 offset;
    int buf_len;
    ReadBytesSuccessCallback success_callback;
    ErrorCallback error_callback;
  };

  
  
  virtual void GetFileInfo(
      const base::FilePath& file_path,
      const GetFileInfoSuccessCallback& success_callback,
      const ErrorCallback& error_callback) = 0;

  
  
  virtual void ReadDirectory(
      const base::FilePath& root,
      const ReadDirectorySuccessCallback& success_callback,
      const ErrorCallback& error_callback) = 0;

  
  
  virtual void CreateSnapshotFile(
      const base::FilePath& device_file_path,
      const base::FilePath& local_path,
      const CreateSnapshotFileSuccessCallback& success_callback,
      const ErrorCallback& error_callback) = 0;

  
  
  virtual bool IsStreaming() = 0;

  
  
  
  virtual void ReadBytes(const base::FilePath& device_file_path,
                         const scoped_refptr<net::IOBuffer>& buf,
                         int64 offset,
                         int buf_len,
                         const ReadBytesSuccessCallback& success_callback,
                         const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  
  
  
  virtual void CancelPendingTasksAndDeleteDelegate() = 0;

 protected:
  
  virtual ~MTPDeviceAsyncDelegate() {}
};

typedef base::Callback<void(MTPDeviceAsyncDelegate*)>
    CreateMTPDeviceAsyncDelegateCallback;

void CreateMTPDeviceAsyncDelegate(
    const base::FilePath::StringType& device_location,
    const CreateMTPDeviceAsyncDelegateCallback& callback);

#endif  
