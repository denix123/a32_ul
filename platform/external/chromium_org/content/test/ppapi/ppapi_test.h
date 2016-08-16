// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_TEST_PPAPI_PPAPI_TEST_H_
#define CONTENT_TEST_PPAPI_PPAPI_TEST_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "content/public/test/content_browser_test.h"
#include "content/public/test/javascript_test_observer.h"
#include "net/test/spawned_test_server/spawned_test_server.h"
#include "url/gurl.h"


namespace base {
class CommandLine;
}

namespace content {

class PPAPITestMessageHandler : public content::TestMessageHandler {
 public:
  PPAPITestMessageHandler();

  virtual MessageResponse HandleMessage(const std::string& json) OVERRIDE;
  virtual void Reset() OVERRIDE;

  const std::string& message() const {
    return message_;
  }

 private:
  std::string message_;

  DISALLOW_COPY_AND_ASSIGN(PPAPITestMessageHandler);
};

class PPAPITestBase : public ContentBrowserTest {
 public:
  PPAPITestBase();

  
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  virtual std::string BuildQuery(const std::string& base,
                                 const std::string& test_case) = 0;

  
  GURL GetTestFileUrl(const std::string& test_case);
  virtual void RunTest(const std::string& test_case);

  
  
  virtual void RunTestAndReload(const std::string& test_case);

 protected:
  
  
  void RunTestURL(const GURL& test_url);
};

class PPAPITest : public PPAPITestBase {
 public:
  PPAPITest();

  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  virtual std::string BuildQuery(const std::string& base,
                                 const std::string& test_case) OVERRIDE;
 protected:
  bool in_process_;  
};

class OutOfProcessPPAPITest : public PPAPITest {
 public:
  OutOfProcessPPAPITest();

  virtual void SetUp() OVERRIDE;
  virtual void TearDown() OVERRIDE;
};

}  

#endif  
