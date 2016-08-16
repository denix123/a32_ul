// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_REMOTING_QUNIT_BROWSER_TEST_RUNNER_H_
#define CHROME_TEST_REMOTING_QUNIT_BROWSER_TEST_RUNNER_H_

#include "chrome/test/base/in_process_browser_test.h"

namespace content {
class WebContents;
}

class QUnitBrowserTestRunner : public InProcessBrowserTest {
 public:
  
  void RunTest(const base::FilePath& file);

 private:
  void QUnitStart(content::WebContents* web_contents);
};

#endif  
