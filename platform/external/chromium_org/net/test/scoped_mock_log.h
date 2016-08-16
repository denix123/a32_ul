// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_TEST_TOOLS_SCOPED_MOCK_LOG_H_
#define NET_QUIC_TEST_TOOLS_SCOPED_MOCK_LOG_H_

#include "base/logging.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {
namespace test {

class ScopedMockLog {
 public:
  
  
  
  
  
  
  ScopedMockLog();

  
  ~ScopedMockLog();

  
  
  
  
  
  void StartCapturingLogs();

  
  
  
  
  
  void StopCapturingLogs();

  
  
  
  
  MOCK_METHOD5(Log, bool(int severity,
                         const char* file,
                         int line,
                         size_t message_start,
                         const std::string& str));

 private:
  
  static ScopedMockLog* g_instance_;

  
  
  static bool LogMessageHandler(int severity,
                                const char* file,
                                int line,
                                size_t message_start,
                                const std::string& str);

  
  bool is_capturing_logs_;

  
  logging::LogMessageHandlerFunction previous_handler_;
};

}  
}  

#endif  
