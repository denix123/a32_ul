// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef DEVICE_MEDIA_TRANSFER_PROTOCOL_MEDIA_TRANSFER_PROTOCOL_DAEMON_CLIENT_H_
#define DEVICE_MEDIA_TRANSFER_PROTOCOL_MEDIA_TRANSFER_PROTOCOL_DAEMON_CLIENT_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "build/build_config.h"

#if !defined(OS_LINUX)
#error "Only used on Linux and ChromeOS"
#endif

class MtpFileEntry;
class MtpStorageInfo;

namespace dbus {
class Bus;
}

namespace device {

class MediaTransferProtocolDaemonClient {
 public:
  
  typedef base::Closure ErrorCallback;

  
  
  typedef base::Callback<void(const std::vector<std::string>& storage_names)
                         > EnumerateStoragesCallback;

  
  
  typedef base::Callback<void(const MtpStorageInfo& storage_info)
                         > GetStorageInfoCallback;

  
  
  typedef base::Callback<void(const std::string& handle)> OpenStorageCallback;

  
  typedef base::Closure CloseStorageCallback;

  
  
  typedef base::Callback<void(const std::vector<uint32>& file_ids)
                         > ReadDirectoryEntryIdsCallback;

  
  
  typedef base::Callback<void(const std::vector<MtpFileEntry>& file_entries)
                         > GetFileInfoCallback;

  
  
  typedef base::Callback<void(const std::string& data)> ReadFileCallback;

  
  
  
  typedef base::Callback<void(bool is_attach,
                              const std::string& storage_name)
                         > MTPStorageEventHandler;

  virtual ~MediaTransferProtocolDaemonClient();

  
  
  virtual void EnumerateStorages(
      const EnumerateStoragesCallback& callback,
      const ErrorCallback& error_callback) = 0;

  
  
  virtual void GetStorageInfo(const std::string& storage_name,
                              const GetStorageInfoCallback& callback,
                              const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void OpenStorage(const std::string& storage_name,
                           const std::string& mode,
                           const OpenStorageCallback& callback,
                           const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void CloseStorage(const std::string& handle,
                            const CloseStorageCallback& callback,
                            const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void ReadDirectoryEntryIds(
      const std::string& handle,
      uint32 file_id,
      const ReadDirectoryEntryIdsCallback& callback,
      const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  virtual void GetFileInfo(const std::string& handle,
                           const std::vector<uint32>& file_ids,
                           size_t offset,
                           size_t entries_to_read,
                           const GetFileInfoCallback& callback,
                           const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  virtual void ReadFileChunk(const std::string& handle,
                             uint32 file_id,
                             uint32 offset,
                             uint32 bytes_to_read,
                             const ReadFileCallback& callback,
                             const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void ListenForChanges(const MTPStorageEventHandler& handler) = 0;

  
  static MediaTransferProtocolDaemonClient* Create(dbus::Bus* bus);

 protected:
  
  MediaTransferProtocolDaemonClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaTransferProtocolDaemonClient);
};

}  

#endif  
