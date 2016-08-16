// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PPAPI_CDM_FILE_IO_IMPL_H_
#define MEDIA_CDM_PPAPI_CDM_FILE_IO_IMPL_H_

#include <algorithm>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "media/cdm/ppapi/api/content_decryption_module.h"
#include "ppapi/c/ppb_file_io.h"
#include "ppapi/cpp/file_io.h"
#include "ppapi/cpp/file_ref.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/private/isolated_file_system_private.h"
#include "ppapi/utility/completion_callback_factory.h"

namespace media {

class CdmFileIOImpl : public cdm::FileIO {
 public:
  
  
  
  class ResourceTracker {
   public:
    ResourceTracker();
    ~ResourceTracker();
   private:
    DISALLOW_COPY_AND_ASSIGN(ResourceTracker);
  };

  
  
  
  CdmFileIOImpl(cdm::FileIOClient* client,
                PP_Instance pp_instance,
                const pp::CompletionCallback& first_file_read_cb);

  
  virtual void Open(const char* file_name, uint32_t file_name_size) OVERRIDE;
  virtual void Read() OVERRIDE;
  virtual void Write(const uint8_t* data, uint32_t data_size) OVERRIDE;
  virtual void Close() OVERRIDE;

 private:
  
  enum State {
    STATE_UNOPENED,
    STATE_OPENING_FILE_SYSTEM,
    STATE_FILE_SYSTEM_OPENED,
    STATE_READING,
    STATE_WRITING,
    STATE_CLOSED,
    STATE_ERROR
  };

  enum ErrorType {
    OPEN_WHILE_IN_USE,
    READ_WHILE_IN_USE,
    WRITE_WHILE_IN_USE,
    OPEN_ERROR,
    READ_ERROR,
    WRITE_ERROR
  };

  
  virtual ~CdmFileIOImpl();

  
  
  
  // - Pros: When the same file is read or written repeatedly, we don't need to
  
  
  
  
  
  typedef std::map<std::string, bool> FileLockMap;

  
  
  
  
  
  
  
  
  
  static FileLockMap* file_lock_map_;

  
  
  bool SetFileID();

  
  
  
  bool AcquireFileLock();

  
  
  void ReleaseFileLock();

  
  void OpenFileSystem();
  void OnFileSystemOpened(int32_t result, pp::FileSystem file_system);

  
  void OpenFileForRead();
  void OnFileOpenedForRead(int32_t result);
  void ReadFile();
  void OnFileRead(int32_t bytes_read);

  
  
  
  
  // RenameTempFile(), we may still end up with an empty, partially written or
  // fully written temporary file in the file system. This temporary file will
  

  void OpenTempFileForWrite();
  void OnTempFileOpenedForWrite(int32_t result);
  void WriteTempFile();
  void OnTempFileWritten(int32_t bytes_written);
  
  // exists, Rename() will succeed and the target file will be overwritten.
  
  void RenameTempFile();
  void OnTempFileRenamed(int32_t result);

  
  void Reset();

  
  
  
  
  void OnError(ErrorType error_type);

  
  void NotifyClientOfError(int32_t result, ErrorType error_type);

  State state_;

  
  cdm::FileIOClient* const client_;

  const pp::InstanceHandle pp_instance_handle_;

  
  std::string file_name_;

  
  
  
  
  std::string file_id_;

  pp::IsolatedFileSystemPrivate isolated_file_system_;
  pp::FileSystem file_system_;

  
  
  
  pp::FileIO file_io_;
  pp::FileRef file_ref_;

  
  
  
  
  std::vector<char> io_buffer_;

  
  
  size_t io_offset_;

  
  
  std::vector<char> cumulative_read_buffer_;

  bool first_file_read_reported_;

  
  pp::CompletionCallback first_file_read_cb_;

  pp::CompletionCallbackFactory<CdmFileIOImpl> callback_factory_;

  DISALLOW_COPY_AND_ASSIGN(CdmFileIOImpl);
};

}  

#endif  
