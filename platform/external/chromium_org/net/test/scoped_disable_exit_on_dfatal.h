// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_TEST_TOOLS_SCOPED_DISABLE_EXIT_ON_DFATAL_H_
#define NET_QUIC_TEST_TOOLS_SCOPED_DISABLE_EXIT_ON_DFATAL_H_

#include "base/logging.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {
namespace test {


class ScopedDisableExitOnDFatal {
 public:
  ScopedDisableExitOnDFatal();
  ~ScopedDisableExitOnDFatal();

 private:
  
  static ScopedDisableExitOnDFatal* g_instance_;

  
  
  static void LogAssertHandler(const std::string& msg);

  DISALLOW_COPY_AND_ASSIGN(ScopedDisableExitOnDFatal);
};

}  
}  

#endif  
