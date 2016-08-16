// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_MEDIA_BROWSERTEST_H_
#define CONTENT_BROWSER_MEDIA_MEDIA_BROWSERTEST_H_

#include <string>

#include "content/public/test/content_browser_test.h"
#include "media/base/test_data_util.h"

namespace content {

class TitleWatcher;

class MediaBrowserTest : public ContentBrowserTest {
 public:
  
  static const char kEnded[];
  static const char kError[];
  static const char kFailed[];

  
  
  
  
  void RunMediaTestPage(const std::string& html_page,
                        const media::QueryParams& query_params,
                        const std::string& expected,
                        bool http);

  
  
  std::string RunTest(const GURL& gurl, const std::string& expected);

  virtual void AddWaitForTitles(content::TitleWatcher* title_watcher);
};

}  

#endif  
