// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_COMMON_TEST_MULTIPROCESS_TEST_HELPER_H_
#define MOJO_COMMON_TEST_MULTIPROCESS_TEST_HELPER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/process/process_handle.h"
#include "base/test/multiprocess_test.h"
#include "base/test/test_timeouts.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "testing/multiprocess_func_list.h"

namespace mojo {

namespace embedder {
class PlatformChannelPair;
}

namespace test {

class MultiprocessTestHelper {
 public:
  MultiprocessTestHelper();
  ~MultiprocessTestHelper();

  
  
  
  void StartChild(const std::string& test_child_name);
  
  
  
  
  
  
  int WaitForChildShutdown();

  
  
  
  
  bool WaitForChildTestShutdown();

  
  static void ChildSetup();

  
  embedder::ScopedPlatformHandle server_platform_handle;

  
  static embedder::ScopedPlatformHandle client_platform_handle;

 private:
  scoped_ptr<embedder::PlatformChannelPair> platform_channel_pair_;

  
  base::ProcessHandle test_child_handle_;

  DISALLOW_COPY_AND_ASSIGN(MultiprocessTestHelper);
};

#define MOJO_MULTIPROCESS_TEST_CHILD_MAIN(test_child_name) \
    MULTIPROCESS_TEST_MAIN_WITH_SETUP( \
        test_child_name ## TestChildMain, \
        ::mojo::test::MultiprocessTestHelper::ChildSetup)

#define MOJO_MULTIPROCESS_TEST_CHILD_TEST(test_child_name) \
    void test_child_name ## TestChildTest(); \
    MOJO_MULTIPROCESS_TEST_CHILD_MAIN(test_child_name) { \
      test_child_name ## TestChildTest(); \
      return (::testing::Test::HasFatalFailure() || \
              ::testing::Test::HasNonfatalFailure()) ? 1 : 0; \
    } \
    void test_child_name ## TestChildTest()

}  
}  

#endif  
