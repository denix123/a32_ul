// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_CHROME_BROWSER_INFO_H_
#define CHROME_TEST_CHROMEDRIVER_CHROME_BROWSER_INFO_H_

#include "chrome/test/chromedriver/chrome/status.h"

static const int kToTBuildNo = 9999;

static const int kToTBlinkRevision = 999999;

struct BrowserInfo {
  BrowserInfo();
  BrowserInfo(std::string browser_name_,
              std::string browser_version_,
              int build_no_,
              int blink_revision_);

  std::string browser_name;
  std::string browser_version;
  int build_no;
  int blink_revision;
};

Status ParseBrowserInfo(const std::string& data,
                        BrowserInfo* browser_info);

Status ParseBrowserString(const std::string& browser_string,
                          std::string* browser_name,
                          std::string* browser_version,
                          int* build_no);

Status ParseBlinkVersionString(const std::string& blink_version,
                               int* blink_revision);

bool IsGitHash(const std::string& revision);

#endif  
