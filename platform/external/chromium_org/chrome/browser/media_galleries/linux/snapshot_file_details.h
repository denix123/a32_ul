// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_LINUX_SNAPSHOT_FILE_DETAILS_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_LINUX_SNAPSHOT_FILE_DETAILS_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "chrome/browser/media_galleries/fileapi/mtp_device_async_delegate.h"

struct SnapshotRequestInfo {
  SnapshotRequestInfo(
      uint32 file_id,
      const base::FilePath& snapshot_file_path,
      const MTPDeviceAsyncDelegate::CreateSnapshotFileSuccessCallback&
          success_callback,
      const MTPDeviceAsyncDelegate::ErrorCallback& error_callback);
  ~SnapshotRequestInfo();

  
  const uint32 file_id;

  
  const base::FilePath snapshot_file_path;

  
  const MTPDeviceAsyncDelegate::CreateSnapshotFileSuccessCallback
      success_callback;

  
  const MTPDeviceAsyncDelegate::ErrorCallback error_callback;
};

// many bytes written to the snapshot file, source file details, snapshot file
class SnapshotFileDetails {
 public:
  SnapshotFileDetails(const SnapshotRequestInfo& request_info,
                      const base::File::Info& file_info);

  ~SnapshotFileDetails();

  uint32 file_id() const {
    return request_info_.file_id;
  }

  base::FilePath snapshot_file_path() const {
    return request_info_.snapshot_file_path;
  }

  uint32 bytes_written() const {
    return bytes_written_;
  }

  const base::File::Info file_info() const {
    return file_info_;
  }

  const MTPDeviceAsyncDelegate::CreateSnapshotFileSuccessCallback
      success_callback() const {
    return request_info_.success_callback;
  }

  const MTPDeviceAsyncDelegate::ErrorCallback error_callback() const {
    return request_info_.error_callback;
  }

  bool error_occurred() const {
    return error_occurred_;
  }

  void set_error_occurred(bool error);

  // Adds |bytes_written| to |bytes_written_|.
  // |bytes_written| specifies the total number of bytes transferred during the
  
  // If |bytes_written| is valid, returns true and adds |bytes_written| to
  // |bytes_written_|.
  // If |bytes_written| is invalid, returns false and does not add
  // |bytes_written| to |bytes_written_|.
  bool AddBytesWritten(uint32 bytes_written);

  
  
  bool IsSnapshotFileWriteComplete() const;

  uint32 BytesToRead() const;

 private:
  
  const SnapshotRequestInfo request_info_;

  
  const base::File::Info file_info_;

  // Number of bytes written into the snapshot file.
  uint32 bytes_written_;

  
  bool error_occurred_;

  DISALLOW_COPY_AND_ASSIGN(SnapshotFileDetails);
};

#endif  
