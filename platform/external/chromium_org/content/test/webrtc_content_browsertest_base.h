// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/test/content_browser_test.h"

namespace base {
class CommandLine;
}

namespace content {

class WebRtcContentBrowserTest: public ContentBrowserTest {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
  virtual void SetUp() OVERRIDE;
  virtual void TearDown() OVERRIDE;

 protected:
  
  
  std::string ExecuteJavascriptAndReturnResult(
      const std::string& javascript);

  
  
  void ExecuteJavascriptAndWaitForOk(const std::string& javascript);

  void DisableOpusIfOnAndroid();

  
  std::string GenerateGetUserMediaCall(const char* function_name,
                                       int min_width,
                                       int max_width,
                                       int min_height,
                                       int max_height,
                                       int min_frame_rate,
                                       int max_frame_rate) const;
};

}  
