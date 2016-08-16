// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#ifndef MOJO_PUBLIC_CPP_ENVIRONMENT_LOGGING_H_
#define MOJO_PUBLIC_CPP_ENVIRONMENT_LOGGING_H_

#include <sstream>

#include "mojo/public/c/environment/logger.h"
#include "mojo/public/cpp/environment/environment.h"
#include "mojo/public/cpp/system/macros.h"

#define MOJO_LOG_STREAM(level) \
    ::mojo::internal::LogMessage(__FILE__, __LINE__, \
                                 MOJO_LOG_LEVEL_ ## level).stream()

#define MOJO_LAZY_LOG_STREAM(level, condition) \
    !(condition) ? \
        (void) 0 : \
        ::mojo::internal::VoidifyOstream() & MOJO_LOG_STREAM(level)

#define MOJO_SHOULD_LOG(level) \
    (MOJO_LOG_LEVEL_ ## level >= \
     ::mojo::Environment::GetDefaultLogger()->GetMinimumLogLevel())

#define MOJO_LOG(level) \
    MOJO_LAZY_LOG_STREAM(level, MOJO_SHOULD_LOG(level))

#define MOJO_LOG_IF(level, condition) \
    MOJO_LAZY_LOG_STREAM(level, MOJO_SHOULD_LOG(level) && (condition))

#define MOJO_CHECK(condition) \
    MOJO_LAZY_LOG_STREAM(FATAL, !(condition)) \
        << "Check failed: " #condition ". "

#ifdef NDEBUG

#define MOJO_DLOG(level) MOJO_LAZY_LOG_STREAM(level, false)
#define MOJO_DLOG_IF(level, condition) MOJO_LAZY_LOG_STREAM(level, false)
#define MOJO_DCHECK(condition) MOJO_LAZY_LOG_STREAM(FATAL, false && (condition))

#else

#define MOJO_DLOG(level) MOJO_LOG(level)
#define MOJO_DLOG_IF(level, condition) MOJO_LOG_IF(level, condition)
#define MOJO_DCHECK(condition) MOJO_CHECK(condition)

#endif  

namespace mojo {
namespace internal {

class LogMessage {
 public:
  LogMessage(const char* file, int line, MojoLogLevel log_level);
  ~LogMessage();

  std::ostream& stream() { return stream_; }

 private:
  const MojoLogLevel log_level_;
  std::ostringstream stream_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(LogMessage);
};

struct VoidifyOstream {
  
  void operator&(std::ostream&) {}
};

}  
}  

#endif  
