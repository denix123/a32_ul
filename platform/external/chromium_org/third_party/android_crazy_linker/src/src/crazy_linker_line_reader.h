// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_LINE_READER_H
#define CRAZY_LINKER_LINE_READER_H

#include <string.h>

#include "crazy_linker_system.h"

namespace crazy {


class LineReader {
 public:
  LineReader();
  explicit LineReader(const char* path);
  ~LineReader();

  
  
  void Open(const char* file_path);

  
  bool GetNextLine();

  
  
  
  const char* line() const;

  
  
  size_t length() const;

 private:
  void Reset();

  FileDescriptor fd_;
  bool eof_;
  size_t line_start_;
  size_t line_len_;
  size_t buff_size_;
  size_t buff_capacity_;
  char* buff_;
  char buff0_[128];
};

}  

#endif  
