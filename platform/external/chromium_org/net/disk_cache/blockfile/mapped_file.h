// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_MAPPED_FILE_H_
#define NET_DISK_CACHE_BLOCKFILE_MAPPED_FILE_H_

#include "net/base/net_export.h"
#include "net/disk_cache/blockfile/file.h"
#include "net/disk_cache/blockfile/file_block.h"

namespace base {
class FilePath;
}

namespace disk_cache {

class NET_EXPORT_PRIVATE MappedFile : public File {
 public:
  MappedFile() : File(true), init_(false) {}

  
  
  
  void* Init(const base::FilePath& name, size_t size);

  void* buffer() const {
    return buffer_;
  }

  
  bool Load(const FileBlock* block);
  bool Store(const FileBlock* block);

  
  
  bool Load(const FileBlock* block, FileIOCallback* callback, bool* completed);
  bool Store(const FileBlock* block, FileIOCallback* callback, bool* completed);

  
  void Flush();

  
  
  bool Preload();

 private:
  virtual ~MappedFile();

  bool init_;
#if defined(OS_WIN)
  HANDLE section_;
#endif
  void* buffer_;  
  size_t view_size_;  
#if defined(POSIX_AVOID_MMAP)
  void* snapshot_;  
#endif

  DISALLOW_COPY_AND_ASSIGN(MappedFile);
};

class ScopedFlush {
 public:
  explicit ScopedFlush(MappedFile* file) : file_(file) {}
  ~ScopedFlush() {
    file_->Flush();
  }
 private:
  MappedFile* file_;
};

}  

#endif  
