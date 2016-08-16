// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_PROVIDED_FILE_SYSTEM_INTERFACE_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_PROVIDED_FILE_SYSTEM_INTERFACE_H_

#include <string>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/async_file_util.h"

class EventRouter;

namespace base {
class Time;
}  

namespace net {
class IOBuffer;
}  

namespace chromeos {
namespace file_system_provider {

class ProvidedFileSystemInfo;
class RequestManager;

struct EntryMetadata {
  EntryMetadata();
  ~EntryMetadata();

  bool is_directory;
  std::string name;
  int64 size;
  base::Time modification_time;
  std::string mime_type;
  std::string thumbnail;

 private:
  DISALLOW_COPY_AND_ASSIGN(EntryMetadata);
};

class ProvidedFileSystemInterface {
 public:
  
  enum OpenFileMode { OPEN_FILE_MODE_READ, OPEN_FILE_MODE_WRITE };

  
  enum MetadataField {
    METADATA_FIELD_DEFAULT = 0,
    METADATA_FIELD_THUMBNAIL = 1 << 0
  };

  typedef base::Callback<void(int file_handle, base::File::Error result)>
      OpenFileCallback;

  typedef base::Callback<
      void(int chunk_length, bool has_more, base::File::Error result)>
      ReadChunkReceivedCallback;

  typedef base::Callback<void(scoped_ptr<EntryMetadata> entry_metadata,
                              base::File::Error result)> GetMetadataCallback;

  typedef base::Callback<void(
      const storage::AsyncFileUtil::StatusCallback& callback)> AbortCallback;

  
  typedef int MetadataFieldMask;

  virtual ~ProvidedFileSystemInterface() {}

  
  
  virtual AbortCallback RequestUnmount(
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  
  virtual AbortCallback GetMetadata(const base::FilePath& entry_path,
                                    MetadataFieldMask fields,
                                    const GetMetadataCallback& callback) = 0;

  
  
  virtual AbortCallback ReadDirectory(
      const base::FilePath& directory_path,
      const storage::AsyncFileUtil::ReadDirectoryCallback& callback) = 0;

  
  
  virtual AbortCallback OpenFile(const base::FilePath& file_path,
                                 OpenFileMode mode,
                                 const OpenFileCallback& callback) = 0;

  
  
  virtual AbortCallback CloseFile(
      int file_handle,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  
  
  virtual AbortCallback ReadFile(int file_handle,
                                 net::IOBuffer* buffer,
                                 int64 offset,
                                 int length,
                                 const ReadChunkReceivedCallback& callback) = 0;

  
  
  
  virtual AbortCallback CreateDirectory(
      const base::FilePath& directory_path,
      bool recursive,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  virtual AbortCallback CreateFile(
      const base::FilePath& file_path,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  virtual AbortCallback DeleteEntry(
      const base::FilePath& entry_path,
      bool recursive,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  virtual AbortCallback CopyEntry(
      const base::FilePath& source_path,
      const base::FilePath& target_path,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  
  virtual AbortCallback MoveEntry(
      const base::FilePath& source_path,
      const base::FilePath& target_path,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  virtual AbortCallback Truncate(
      const base::FilePath& file_path,
      int64 length,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  virtual AbortCallback WriteFile(
      int file_handle,
      net::IOBuffer* buffer,
      int64 offset,
      int length,
      const storage::AsyncFileUtil::StatusCallback& callback) = 0;

  
  virtual const ProvidedFileSystemInfo& GetFileSystemInfo() const = 0;

  
  virtual RequestManager* GetRequestManager() = 0;

  
  virtual base::WeakPtr<ProvidedFileSystemInterface> GetWeakPtr() = 0;
};

}  
}  

#endif  
