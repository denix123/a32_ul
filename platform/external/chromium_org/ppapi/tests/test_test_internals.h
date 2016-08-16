// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_TESTS_TEST_TEST_INTERNALS_H_
#define PPAPI_TESTS_TEST_TEST_INTERNALS_H_

#include <string>

#include "ppapi/tests/test_case.h"

class TestTestInternals : public TestCase {
 public:
  explicit TestTestInternals(TestingInstance* instance) : TestCase(instance) {}

 private:
  
  virtual bool Init();
  virtual void RunTests(const std::string& filter);

  std::string TestToString();
  std::string TestPassingComparisons();
  std::string TestFailingComparisons();
  std::string TestEvaluateOnce();
};

#endif  
