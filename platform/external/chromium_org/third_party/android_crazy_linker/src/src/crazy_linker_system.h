// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_SYSTEM_H
#define CRAZY_LINKER_SYSTEM_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "crazy_linker_util.h"  


namespace crazy {

enum FileOpenMode {
  FILE_OPEN_READ_ONLY = 0,
  FILE_OPEN_READ_WRITE,
  FILE_OPEN_WRITE
};

class FileDescriptor {
 public:
#ifdef UNIT_TESTS
#define kEmptyFD NULL
  typedef void* HandleType;
#else
#define kEmptyFD (-1)
  typedef int HandleType;
#endif

  FileDescriptor() : fd_(kEmptyFD) {}

  FileDescriptor(const char* path) : fd_(kEmptyFD) { OpenReadOnly(path); }

  ~FileDescriptor() { Close(); }

  bool IsOk() const { return fd_ != kEmptyFD; }
  HandleType Get() const { return fd_; }
  bool OpenReadOnly(const char* path);
  bool OpenReadWrite(const char* path);
  int Read(void* buffer, size_t buffer_size);
  int SeekTo(off_t offset);
  void* Map(void* address,
            size_t length,
            int prot_flags,
            int flags,
            off_t offset);
  void Close();

 private:
  HandleType fd_;
};

bool PathExists(const char* path_name);

bool PathIsFile(const char* path_name);

String GetCurrentDirectory();

const char* GetEnv(const char* var_name);

bool IsSystemLibrary(const char* lib_name);

}  

#endif  
