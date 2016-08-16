// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_TESTS_SCOPED_TEMPORARY_FILE_H_
#define SANDBOX_LINUX_TESTS_SCOPED_TEMPORARY_FILE_H_

#include "base/macros.h"

namespace sandbox {
class ScopedTemporaryFile {
 public:
  ScopedTemporaryFile();
  ~ScopedTemporaryFile();

  int fd() const { return fd_; }
  const char* full_file_name() const { return full_file_name_; }

 private:
  int fd_;
  char full_file_name_[128];
  DISALLOW_COPY_AND_ASSIGN(ScopedTemporaryFile);
};

}  

#endif  
