// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_THREAD_H
#define CRAZY_LINKER_THREAD_H

#include <stdarg.h>
#include <stddef.h>

namespace crazy {

class ThreadData {

 public:
  ThreadData() {}

  
  void Init();

  
  
  
  
  const char* GetError() const { return dlerror_; }

  
  void SwapErrorBuffers();

  
  void SetError(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    SetErrorArgs(fmt, args);
    va_end(args);
  }

  void SetErrorArgs(const char* fmt, va_list args);

  
  void AppendError(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    AppendErrorArgs(fmt, args);
    va_end(args);
  }

  void AppendErrorArgs(const char* fmt, va_list args);

 private:
  
  
  
  char* dlerror_;

  
  static const size_t kBufferSize = 512;

  
  char dlerror_buffers_[2][kBufferSize];
};

ThreadData* GetThreadData();

ThreadData* GetThreadDataFast();

void SetLinkerErrorString(const char* str);

void SetLinkerError(const char* fmt, ...);

}  

#endif  
