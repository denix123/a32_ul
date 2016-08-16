// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_MEDIA_BROWSERTEST_H_
#define CHROME_BROWSER_MEDIA_MEDIA_BROWSERTEST_H_

#include <string>

#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/browser/web_contents_observer.h"
#include "media/base/test_data_util.h"

namespace content {
class TitleWatcher;
}

class MediaBrowserTest : public InProcessBrowserTest,
                         public content::WebContentsObserver {
 protected:
  
  static const char kEnded[];
  
  static const char kError[];
  static const char kFailed[];
  static const char kPluginCrashed[];

  MediaBrowserTest();
  virtual ~MediaBrowserTest();

  
  
  
  
  void RunMediaTestPage(const std::string& html_page,
                        const media::QueryParams& query_params,
                        const std::string& expected,
                        bool http);

  
  
  std::string RunTest(const GURL& gurl, const std::string& expected);

  virtual void AddWaitForTitles(content::TitleWatcher* title_watcher);

  
  
  virtual void PluginCrashed(const base::FilePath& plugin_path,
                             base::ProcessId plugin_pid) OVERRIDE;

  
  void IgnorePluginCrash();

 private:
  bool ignore_plugin_crash_;
};

#endif  
