// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_CHROME_TEST_LAUNCHER_H_
#define CHROME_TEST_BASE_CHROME_TEST_LAUNCHER_H_

#include "base/memory/scoped_ptr.h"

class ChromeTestSuite;

class ChromeTestSuiteRunner {
 public:
  virtual int RunTestSuite(int argc, char** argv) = 0;
};

int LaunchChromeTests(int default_jobs,
                      ChromeTestSuiteRunner* runner,
                      int argc,
                      char** argv);

#endif  
