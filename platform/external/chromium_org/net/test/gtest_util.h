// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_TEST_TOOLS_GTEST_UTIL_H_
#define NET_QUIC_TEST_TOOLS_GTEST_UTIL_H_

#include "net/test/scoped_disable_exit_on_dfatal.h"
#include "net/test/scoped_mock_log.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {
namespace test {

#define GTEST_DFATAL_(statement, matcher, fail)                         \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                         \
  if (true) {                                                           \
    ::net::test::ScopedMockLog gtest_log;                               \
    ::net::test::ScopedDisableExitOnDFatal gtest_disable_exit;          \
    using ::testing::_;                                                 \
    EXPECT_CALL(gtest_log, Log(_, _, _, _, _))                          \
        .WillRepeatedly(::testing::Return(false));                      \
    EXPECT_CALL(gtest_log, Log(logging::LOG_DFATAL, _, _, _, matcher))  \
        .Times(::testing::AtLeast(1))                                   \
        .WillOnce(::testing::Return(false));                            \
    gtest_log.StartCapturingLogs();                                     \
    { statement; }                                                      \
    gtest_log.StopCapturingLogs();                                      \
    if (!testing::Mock::VerifyAndClear(&gtest_log)) {                   \
      goto GTEST_CONCAT_TOKEN_(gtest_label_dfatal_, __LINE__);          \
    }                                                                   \
  } else                                                                \
    GTEST_CONCAT_TOKEN_(gtest_label_dfatal_, __LINE__):                 \
        fail("")


#define EXPECT_DFATAL_WITH(statement, matcher) \
  GTEST_DFATAL_(statement, matcher, GTEST_NONFATAL_FAILURE_)

#define ASSERT_DFATAL_WITH(statement, matcher) \
  GTEST_DFATAL_(statement, matcher, GTEST_FATAL_FAILURE_)

#define EXPECT_DFATAL(statement, regex) \
  EXPECT_DFATAL_WITH(statement, ::testing::ContainsRegex(regex))

#define ASSERT_DFATAL(statement, regex) \
  ASSERT_DFATAL_WITH(statement, ::testing::ContainsRegex(regex))


#ifndef NDEBUG

#define EXPECT_DEBUG_DFATAL(statement, regex) \
  EXPECT_DFATAL(statement, regex)
#define ASSERT_DEBUG_DFATAL(statement, regex) \
  ASSERT_DFATAL(statement, regex)

#else  

#define EXPECT_DEBUG_DFATAL(statement, regex) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_               \
  if (true) {                                 \
    (void)(regex);                            \
    statement;                                \
  } else                                      \
    GTEST_NONFATAL_FAILURE_("")
#define ASSERT_DEBUG_DFATAL(statement, regex) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_               \
  if (true) {                                 \
    (void)(regex);                            \
    statement;                                \
  } else                                      \
    GTEST_NONFATAL_FAILURE_("")

#endif  

}  
}  

#endif  
