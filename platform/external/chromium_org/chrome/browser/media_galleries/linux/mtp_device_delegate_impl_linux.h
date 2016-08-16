// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_LINUX_MTP_DEVICE_DELEGATE_IMPL_LINUX_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_LINUX_MTP_DEVICE_DELEGATE_IMPL_LINUX_H_

#include <deque>
#include <map>
#include <set>
#include <string>

#include "base/callback.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/files/file_path.h"
#include "base/location.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/media_galleries/fileapi/mtp_device_async_delegate.h"
#include "content/public/browser/browser_thread.h"
#include "storage/browser/fileapi/async_file_util.h"

struct SnapshotRequestInfo;

class MTPDeviceDelegateImplLinux : public MTPDeviceAsyncDelegate {
 private:
  friend void CreateMTPDeviceAsyncDelegate(
      const std::string&,
      const CreateMTPDeviceAsyncDelegateCallback&);

  enum InitializationState {
    UNINITIALIZED = 0,
    PENDING_INIT,
    INITIALIZED
  };

  
  struct PendingTaskInfo {
    PendingTaskInfo(const base::FilePath& path,
                    content::BrowserThread::ID thread_id,
                    const tracked_objects::Location& location,
                    const base::Closure& task);
    ~PendingTaskInfo();

    base::FilePath path;
    base::FilePath cached_path;
    const content::BrowserThread::ID thread_id;
    const tracked_objects::Location location;
    const base::Closure task;
  };

  class MTPFileNode;

  
  typedef std::map<uint32, MTPFileNode*> FileIdToMTPFileNodeMap;

  
  typedef std::map<base::FilePath, storage::DirectoryEntry> FileInfoCache;

  
  
  
  explicit MTPDeviceDelegateImplLinux(const std::string& device_location);

  
  virtual ~MTPDeviceDelegateImplLinux();

  
  virtual void GetFileInfo(const base::FilePath& file_path,
                           const GetFileInfoSuccessCallback& success_callback,
                           const ErrorCallback& error_callback) OVERRIDE;
  virtual void ReadDirectory(
      const base::FilePath& root,
      const ReadDirectorySuccessCallback& success_callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void CreateSnapshotFile(
      const base::FilePath& device_file_path,
      const base::FilePath& local_path,
      const CreateSnapshotFileSuccessCallback& success_callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual bool IsStreaming() OVERRIDE;
  virtual void ReadBytes(const base::FilePath& device_file_path,
                         const scoped_refptr<net::IOBuffer>& buf,
                         int64 offset,
                         int buf_len,
                         const ReadBytesSuccessCallback& success_callback,
                         const ErrorCallback& error_callback) OVERRIDE;
  virtual void CancelPendingTasksAndDeleteDelegate() OVERRIDE;

  
  
  virtual void GetFileInfoInternal(
      const base::FilePath& file_path,
      const GetFileInfoSuccessCallback& success_callback,
      const ErrorCallback& error_callback);
  virtual void ReadDirectoryInternal(
      const base::FilePath& root,
      const ReadDirectorySuccessCallback& success_callback,
      const ErrorCallback& error_callback);
  virtual void CreateSnapshotFileInternal(
      const base::FilePath& device_file_path,
      const base::FilePath& local_path,
      const CreateSnapshotFileSuccessCallback& success_callback,
      const ErrorCallback& error_callback);
  virtual void ReadBytesInternal(
      const base::FilePath& device_file_path,
      net::IOBuffer* buf, int64 offset, int buf_len,
      const ReadBytesSuccessCallback& success_callback,
      const ErrorCallback& error_callback);

  
  
  
  
  
  
  void EnsureInitAndRunTask(const PendingTaskInfo& task_info);

  
  
  
  
  void RunTask(const PendingTaskInfo& task_info);

  
  
  
  
  
  void WriteDataIntoSnapshotFile(const base::File::Info& snapshot_file_info);

  
  void PendingRequestDone();

  
  void ProcessNextPendingRequest();

  
  
  
  
  void OnInitCompleted(bool succeeded);

  
  
  
  void OnDidGetFileInfo(const GetFileInfoSuccessCallback& success_callback,
                        const base::File::Info& file_info);

  
  
  
  
  
  
  
  
  
  void OnDidGetFileInfoToReadDirectory(
      uint32 dir_id,
      const ReadDirectorySuccessCallback& success_callback,
      const ErrorCallback& error_callback,
      const base::File::Info& file_info);

  
  
  
  
  
  
  void OnDidGetFileInfoToCreateSnapshotFile(
      scoped_ptr<SnapshotRequestInfo> snapshot_request_info,
      const base::File::Info& file_info);

  
  
  
  
  
  
  
  void OnDidReadDirectory(uint32 dir_id,
                          const ReadDirectorySuccessCallback& success_callback,
                          const storage::AsyncFileUtil::EntryList& file_list,
                          bool has_more);

  
  
  
  
  
  
  void OnDidWriteDataIntoSnapshotFile(
      const base::File::Info& snapshot_file_info,
      const base::FilePath& snapshot_file_path);

  
  
  
  
  
  
  void OnWriteDataIntoSnapshotFileError(base::File::Error error);

  
  
  
  
  void OnDidReadBytes(const ReadBytesSuccessCallback& success_callback,
                      const base::File::Info& file_info, int bytes_read);

  
  void OnDidFillFileCache(const base::FilePath& path,
                          const storage::AsyncFileUtil::EntryList& file_list,
                          bool has_more);

  
  void OnFillFileCacheFailed(base::File::Error error);

  
  
  void HandleDeviceFileError(const ErrorCallback& error_callback,
                             uint32 file_id,
                             base::File::Error error);

  
  
  
  base::FilePath NextUncachedPathComponent(
      const base::FilePath& path,
      const base::FilePath& cached_path) const;

  
  void FillFileCache(const base::FilePath& uncached_path);

  
  
  bool CachedPathToId(const base::FilePath& path, uint32* id) const;

  
  InitializationState init_state_;

  
  
  
  bool task_in_progress_;

  
  
  const base::FilePath device_path_;

  
  std::string storage_name_;

  
  
  std::deque<PendingTaskInfo> pending_tasks_;

  
  
  
  
  
  scoped_ptr<SnapshotRequestInfo> current_snapshot_request_info_;

  
  
  
  FileIdToMTPFileNodeMap file_id_to_node_map_;

  
  
  scoped_ptr<MTPFileNode> root_node_;

  
  
  std::set<std::string> child_nodes_seen_;

  
  
  
  FileInfoCache file_info_cache_;

  
  base::WeakPtrFactory<MTPDeviceDelegateImplLinux> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MTPDeviceDelegateImplLinux);
};

#endif  
