// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_DEBUG_H_
#define TOOLS_RELOCATION_PACKER_SRC_DEBUG_H_

#include <limits.h>
#include <ostream>
#include <sstream>

namespace relocation_packer {

class Logger {
 public:
  enum Severity {INFO = 0, WARNING, ERROR, FATAL};

  
  
  
  
  
  Logger(Severity severity, int level, bool predicate);

  
  ~Logger();

  
  std::ostream& GetStream() { return stream_; }

  
  
  static void SetVerbose(int level) { max_level_ = level; }

  
  static void SetStreams(std::ostream* info_stream,
                         std::ostream* error_stream) {
    info_stream_ = info_stream;
    error_stream_ = error_stream;
  }

  
  static void Reset();

 private:
  
  Severity severity_;
  int level_;
  bool predicate_;

  
  std::ostringstream stream_;

  
  static int max_level_;

  
  static std::ostream* info_stream_;
  static std::ostream* error_stream_;
};

}  

typedef relocation_packer::Logger::Severity LogSeverity;
const LogSeverity INFO = relocation_packer::Logger::INFO;
const LogSeverity WARNING = relocation_packer::Logger::WARNING;
const LogSeverity ERROR = relocation_packer::Logger::ERROR;
const LogSeverity FATAL = relocation_packer::Logger::FATAL;

#define LOG(severity) \
    (relocation_packer::Logger(severity, INT_MIN, true).GetStream())
#define LOG_IF(severity, predicate) \
    (relocation_packer::Logger(severity, INT_MIN, (predicate)).GetStream())

#define VLOG(level) \
    (relocation_packer::Logger(INFO, (level), true).GetStream())
#define VLOG_IF(level, predicate) \
    (relocation_packer::Logger(INFO, (level), (predicate)).GetStream())

#define CHECK(predicate) (LOG_IF(FATAL, !(predicate)) \
    << __FILE__ << ":" << __LINE__ << ": " \
    << __FUNCTION__ << ": CHECK '" #predicate "' failed")

#define NOTREACHED(_) (LOG(FATAL) \
    << __FILE__ << ":" << __LINE__ << ": " \
    << __FUNCTION__ << ": NOTREACHED() hit")

#endif  
