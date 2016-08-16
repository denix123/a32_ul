// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_SHARED_MEMORY_H_
#define BASE_MEMORY_SHARED_MEMORY_H_

#include "build/build_config.h"

#include <string>

#if defined(OS_POSIX)
#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#endif

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/process/process_handle.h"

#if defined(OS_POSIX)
#include "base/file_descriptor_posix.h"
#include "base/files/file_util.h"
#include "base/files/scoped_file.h"
#endif

namespace base {

class FilePath;

#if defined(OS_WIN)
typedef HANDLE SharedMemoryHandle;
#elif defined(OS_POSIX)
typedef FileDescriptor SharedMemoryHandle;
typedef ino_t SharedMemoryId;
#endif

struct SharedMemoryCreateOptions {
  SharedMemoryCreateOptions()
      : name_deprecated(NULL),
        size(0),
        open_existing_deprecated(false),
        executable(false),
        share_read_only(false) {}

  
  
  
  const std::string* name_deprecated;

  
  
  size_t size;

  
  
  
  
  
  bool open_existing_deprecated;

  
  bool executable;

  
  bool share_read_only;
};

class BASE_EXPORT SharedMemory {
 public:
  SharedMemory();

#if defined(OS_WIN)
  
  
  
  explicit SharedMemory(const std::wstring& name);
#endif

  
  
  
  
  
  
  
  SharedMemory(SharedMemoryHandle handle, bool read_only);

  
  
  
  SharedMemory(SharedMemoryHandle handle, bool read_only,
               ProcessHandle process);

  
  ~SharedMemory();

  
  
  static bool IsHandleValid(const SharedMemoryHandle& handle);

  
  static SharedMemoryHandle NULLHandle();

  
  static void CloseHandle(const SharedMemoryHandle& handle);

  
  static size_t GetHandleLimit();

  
  
  bool Create(const SharedMemoryCreateOptions& options);

  
  
  bool CreateAndMapAnonymous(size_t size);

  
  
  bool CreateAnonymous(size_t size) {
    SharedMemoryCreateOptions options;
    options.size = size;
    return Create(options);
  }

  
  
  
  
  
  
  
  bool CreateNamedDeprecated(
      const std::string& name, bool open_existing, size_t size) {
    SharedMemoryCreateOptions options;
    options.name_deprecated = &name;
    options.open_existing_deprecated = open_existing;
    options.size = size;
    return Create(options);
  }

  
  
  bool Delete(const std::string& name);

  
  
  
  bool Open(const std::string& name, bool read_only);

  
  
  
  
  
  bool Map(size_t bytes) {
    return MapAt(0, bytes);
  }

  
  
  
  bool MapAt(off_t offset, size_t bytes);
  enum { MAP_MINIMUM_ALIGNMENT = 32 };

  
  
  
  bool Unmap();

  
  size_t requested_size() const { return requested_size_; }

  
  size_t mapped_size() const { return mapped_size_; }

  
  
  void *memory() const { return memory_; }

  
  
  
  SharedMemoryHandle handle() const;

#if defined(OS_POSIX) && !defined(OS_NACL)
  
  
  
  
  SharedMemoryId id() const { return inode_; }
#endif

  
  
  void Close();

  
  
  
  
  
  
  
  
  
  
  bool ShareReadOnlyToProcess(ProcessHandle process,
                              SharedMemoryHandle* new_handle) {
    return ShareToProcessCommon(process, new_handle, false, SHARE_READONLY);
  }

  
  
  
  
  
  
  bool GiveReadOnlyToProcess(ProcessHandle process,
                             SharedMemoryHandle* new_handle) {
    return ShareToProcessCommon(process, new_handle, true, SHARE_READONLY);
  }

  
  
  
  
  
  
  bool ShareToProcess(ProcessHandle process,
                      SharedMemoryHandle* new_handle) {
    return ShareToProcessCommon(process, new_handle, false, SHARE_CURRENT_MODE);
  }

  
  
  
  
  
  
  bool GiveToProcess(ProcessHandle process,
                     SharedMemoryHandle* new_handle) {
    return ShareToProcessCommon(process, new_handle, true, SHARE_CURRENT_MODE);
  }

  
  
  
  
  
  
  
  void LockDeprecated();

  
  
  void UnlockDeprecated();

 private:
#if defined(OS_POSIX) && !defined(OS_NACL)
#if !defined(OS_ANDROID)
  bool PrepareMapFile(ScopedFILE fp, ScopedFD readonly);
  bool FilePathForMemoryName(const std::string& mem_name, FilePath* path);
#endif
  void LockOrUnlockCommon(int function);
#endif  
  enum ShareMode {
    SHARE_READONLY,
    SHARE_CURRENT_MODE,
  };
  bool ShareToProcessCommon(ProcessHandle process,
                            SharedMemoryHandle* new_handle,
                            bool close_self,
                            ShareMode);

#if defined(OS_WIN)
  std::wstring       name_;
  HANDLE             mapped_file_;
#elif defined(OS_POSIX)
  int                mapped_file_;
  int                readonly_mapped_file_;
  ino_t              inode_;
#endif
  size_t             mapped_size_;
  void*              memory_;
  bool               read_only_;
  size_t             requested_size_;
#if !defined(OS_POSIX)
  HANDLE             lock_;
#endif

  DISALLOW_COPY_AND_ASSIGN(SharedMemory);
};

class SharedMemoryAutoLockDeprecated {
 public:
  explicit SharedMemoryAutoLockDeprecated(SharedMemory* shared_memory)
      : shared_memory_(shared_memory) {
    shared_memory_->LockDeprecated();
  }

  ~SharedMemoryAutoLockDeprecated() {
    shared_memory_->UnlockDeprecated();
  }

 private:
  SharedMemory* shared_memory_;
  DISALLOW_COPY_AND_ASSIGN(SharedMemoryAutoLockDeprecated);
};

}  

#endif  
