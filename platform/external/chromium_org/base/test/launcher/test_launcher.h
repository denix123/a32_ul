// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_LAUNCHER_TEST_LAUNCHER_H_
#define BASE_TEST_LAUNCHER_TEST_LAUNCHER_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/test/launcher/test_result.h"
#include "base/test/launcher/test_results_tracker.h"
#include "base/time/time.h"
#include "base/timer/timer.h"

namespace testing {
class TestCase;
class TestInfo;
}

namespace base {

class CommandLine;
struct LaunchOptions;
class SequencedWorkerPoolOwner;
class TestLauncher;

extern const char kGTestFilterFlag[];
extern const char kGTestHelpFlag[];
extern const char kGTestListTestsFlag[];
extern const char kGTestRepeatFlag[];
extern const char kGTestRunDisabledTestsFlag[];
extern const char kGTestOutputFlag[];

class TestLauncherDelegate {
 public:
  
  
  
  virtual bool ShouldRunTest(const testing::TestCase* test_case,
                             const testing::TestInfo* test_info) = 0;

  
  
  
  
  
  virtual size_t RunTests(TestLauncher* test_launcher,
                          const std::vector<std::string>& test_names) = 0;

  
  
  
  
  
  virtual size_t RetryTests(TestLauncher* test_launcher,
                            const std::vector<std::string>& test_names) = 0;

 protected:
  virtual ~TestLauncherDelegate();
};

class TestLauncher {
 public:
  
  enum LaunchChildGTestProcessFlags {
    
    
    USE_JOB_OBJECTS = (1 << 0),

    
    
    
    ALLOW_BREAKAWAY_FROM_JOB = (1 << 1),
  };

  
  
  TestLauncher(TestLauncherDelegate* launcher_delegate, size_t parallel_jobs);
  ~TestLauncher();

  
  bool Run() WARN_UNUSED_RESULT;

  
  
  
  
  typedef Callback<void(int, const TimeDelta&, bool, const std::string&)>
      LaunchChildGTestProcessCallback;

  
  
  
  
  
  void LaunchChildGTestProcess(const CommandLine& command_line,
                               const std::string& wrapper,
                               base::TimeDelta timeout,
                               int flags,
                               const LaunchChildGTestProcessCallback& callback);

  
  void OnTestFinished(const TestResult& result);

  
  static std::string FormatFullTestName(const std::string& test_case_name,
                                        const std::string& test_name);

 private:
  bool Init() WARN_UNUSED_RESULT;

  
  void RunTests();

  void RunTestIteration();

  
  void MaybeSaveSummaryAsJSON();

  
  void OnLaunchTestProcessFinished(
      const LaunchChildGTestProcessCallback& callback,
      int exit_code,
      const TimeDelta& elapsed_time,
      bool was_timeout,
      const std::string& output);

  
  void OnTestIterationFinished();

  
  void OnOutputTimeout();

  
  
  
  
  
  ThreadChecker thread_checker_;

  TestLauncherDelegate* launcher_delegate_;

  
  int32 total_shards_;  
  int32 shard_index_;   

  int cycles_;  

  
  std::vector<std::string> positive_test_filter_;
  std::vector<std::string> negative_test_filter_;

  
  size_t test_started_count_;

  
  size_t test_finished_count_;

  
  size_t test_success_count_;

  
  
  size_t test_broken_count_;

  
  size_t retry_count_;

  
  size_t retry_limit_;

  
  std::set<std::string> tests_to_retry_;

  
  bool run_result_;

  TestResultsTracker results_tracker_;

  
  DelayTimer<TestLauncher> watchdog_timer_;

  
  size_t parallel_jobs_;

  
  scoped_ptr<SequencedWorkerPoolOwner> worker_pool_owner_;

  DISALLOW_COPY_AND_ASSIGN(TestLauncher);
};

std::string GetTestOutputSnippet(const TestResult& result,
                                 const std::string& full_output);

}  

#endif  
