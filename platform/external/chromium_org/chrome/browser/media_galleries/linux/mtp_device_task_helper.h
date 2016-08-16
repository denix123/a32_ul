// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_LINUX_MTP_DEVICE_TASK_HELPER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_LINUX_MTP_DEVICE_TASK_HELPER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/media_galleries/fileapi/mtp_device_async_delegate.h"
#include "device/media_transfer_protocol/mtp_file_entry.pb.h"
#include "storage/browser/fileapi/async_file_util.h"

class MTPReadFileWorker;
struct SnapshotRequestInfo;

class MTPDeviceTaskHelper {
 public:
  typedef base::Callback<void(bool succeeded)> OpenStorageCallback;

  typedef MTPDeviceAsyncDelegate::GetFileInfoSuccessCallback
      GetFileInfoSuccessCallback;

  
  
  typedef base::Callback<void(const storage::AsyncFileUtil::EntryList& entries,
                              bool has_more)> ReadDirectorySuccessCallback;

  typedef MTPDeviceAsyncDelegate::ErrorCallback ErrorCallback;

  MTPDeviceTaskHelper();
  ~MTPDeviceTaskHelper();

  
  
  
  
  
  
  void OpenStorage(const std::string& storage_name,
                   const OpenStorageCallback& callback);

  
  
  
  
  
  
  
  
  
  void GetFileInfo(uint32 file_id,
                   const GetFileInfoSuccessCallback& success_callback,
                   const ErrorCallback& error_callback);

  
  
  
  
  
  
  
  
  
  
  
  
  void ReadDirectory(uint32 dir_id,
                     const ReadDirectorySuccessCallback& success_callback,
                     const ErrorCallback& error_callback);

  
  
  
  
  
  void WriteDataIntoSnapshotFile(
      const SnapshotRequestInfo& request_info,
      const base::File::Info& snapshot_file_info);

  
  
  
  
  
  void ReadBytes(const MTPDeviceAsyncDelegate::ReadBytesRequest& request);

  
  void CloseStorage() const;

 private:
  
  
  
  
  
  
  
  void OnDidOpenStorage(const OpenStorageCallback& callback,
                        const std::string& device_handle,
                        bool error);

  
  
  
  
  
  
  
  
  
  void OnGetFileInfo(const GetFileInfoSuccessCallback& success_callback,
                     const ErrorCallback& error_callback,
                     const MtpFileEntry& file_entry,
                     bool error) const;

  
  
  
  
  
  
  
  
  void OnDidReadDirectory(const ReadDirectorySuccessCallback& success_callback,
                          const ErrorCallback& error_callback,
                          const std::vector<MtpFileEntry>& file_entries,
                          bool has_more,
                          bool error) const;

  
  void OnGetFileInfoToReadBytes(
      const MTPDeviceAsyncDelegate::ReadBytesRequest& request,
      const MtpFileEntry& file_entry,
      bool error);

  
  
  
  // is written to, and the success callback within |request| is invoked on the
  
  
  
  
  
  void OnDidReadBytes(
      const MTPDeviceAsyncDelegate::ReadBytesRequest& request,
      const base::File::Info& file_info,
      const std::string& data,
      bool error) const;

  
  
  
  
  void HandleDeviceError(const ErrorCallback& error_callback,
                         base::File::Error error) const;

  
  std::string device_handle_;

  
  scoped_ptr<MTPReadFileWorker> read_file_worker_;

  
  base::WeakPtrFactory<MTPDeviceTaskHelper> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MTPDeviceTaskHelper);
};

#endif  
