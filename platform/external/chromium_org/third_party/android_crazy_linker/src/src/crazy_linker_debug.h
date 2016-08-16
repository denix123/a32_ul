// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_DEBUG_H
#define CRAZY_LINKER_DEBUG_H

#ifndef CRAZY_DEBUG
#define CRAZY_DEBUG 0
#endif

namespace crazy {

#if CRAZY_DEBUG

void Log(const char* fmt, ...);
void LogErrno(const char* fmt, ...);

#define LOG(...) ::crazy::Log(__VA_ARGS__)
#define LOG_ERRNO(...) ::crazy::LogErrno(__VA_ARGS__)

#else

#define LOG(...) ((void)0)
#define LOG_ERRNO(...) ((void)0)

#endif

#define LOG_IF(cond, ...) \
  do {                    \
    if ((cond))           \
      LOG(__VA_ARGS__);   \
  } while (0)

#define LOG_ERRNO_IF(cond, ...) \
  do {                          \
    if ((cond))                 \
      LOG_ERRNO(__VA_ARGS__);   \
  } while (0)

}  

#endif  
