// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_LAUNCHER_TEST_RESULTS_TRACKER_H_
#define BASE_TEST_LAUNCHER_TEST_RESULTS_TRACKER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/test/launcher/test_result.h"
#include "base/threading/thread_checker.h"

namespace base {

class CommandLine;
class FilePath;

class TestResultsTracker {
 public:
  TestResultsTracker();
  ~TestResultsTracker();

  
  
  bool Init(const CommandLine& command_line) WARN_UNUSED_RESULT;

  
  void OnTestIterationStarting();

  
  
  void AddTest(const std::string& test_name);

  
  void AddDisabledTest(const std::string& test_name);

  
  void AddTestResult(const TestResult& result);

  
  void PrintSummaryOfCurrentIteration() const;

  
  void PrintSummaryOfAllIterations() const;

  
  
  void AddGlobalTag(const std::string& tag);

  
  
  bool SaveSummaryAsJSON(const FilePath& path) const WARN_UNUSED_RESULT;

  
  
  typedef std::map<TestResult::Status, std::set<std::string> > TestStatusMap;

  
  TestStatusMap GetTestStatusMapForCurrentIteration() const;

  
  TestStatusMap GetTestStatusMapForAllIterations() const;

 private:
  void GetTestStatusForIteration(int iteration, TestStatusMap* map) const;

  struct AggregateTestResult {
    AggregateTestResult();
    ~AggregateTestResult();

    std::vector<TestResult> test_results;
  };

  struct PerIterationData {
    PerIterationData();
    ~PerIterationData();

    
    typedef std::map<std::string, AggregateTestResult> ResultsMap;
    ResultsMap results;
  };

  ThreadChecker thread_checker_;

  
  
  std::set<std::string> global_tags_;

  
  std::set<std::string> all_tests_;

  
  std::set<std::string> disabled_tests_;

  
  std::vector<PerIterationData> per_iteration_data_;

  
  
  int iteration_;

  
  FILE* out_;

  DISALLOW_COPY_AND_ASSIGN(TestResultsTracker);
};

}  

#endif  
