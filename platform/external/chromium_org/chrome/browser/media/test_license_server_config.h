// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_TEST_LICENSE_SERVER_CONFIG_H_
#define CHROME_BROWSER_MEDIA_TEST_LICENSE_SERVER_CONFIG_H_

#include <string>
#include "base/basictypes.h"


namespace base {
class CommandLine;
class FilePath;
}

// Class used to start a test license server.
class TestLicenseServerConfig {
 public:
  TestLicenseServerConfig() {}
  virtual ~TestLicenseServerConfig() {}

  
  // This URL is directly used by the Web app to request a license, example:
  // http://localhost:8888/license_server
  virtual std::string GetServerURL() = 0;

  // Returns true if it successfully sets the command line to run the license
  
  virtual bool GetServerCommandLine(base::CommandLine* command_line) = 0;

  
  virtual bool IsPlatformSupported() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(TestLicenseServerConfig);
};

#endif  // CHROME_BROWSER_MEDIA_TEST_LICENSE_SERVER_CONFIG_H_
