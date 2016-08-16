// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PDF_PDF_BROWSERTEST_BASE_H_
#define CHROME_BROWSER_UI_PDF_PDF_BROWSERTEST_BASE_H_

#include <string>

#include "base/files/file_path.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/browser/notification_observer.h"
#include "net/test/embedded_test_server/embedded_test_server.h"

namespace base {
class CommandLine;
}

class SkBitmap;

class PDFBrowserTest : public InProcessBrowserTest,
                       public testing::WithParamInterface<int>,
                       public content::NotificationObserver {
 public:
  PDFBrowserTest();
  virtual ~PDFBrowserTest();

 protected:
  
  net::test_server::EmbeddedTestServer* pdf_test_server() {
    return &pdf_test_server_;
  }

  int load_stop_notification_count() const {
    return load_stop_notification_count_;
  }

  void Load();
  void WaitForResponse();
  bool VerifySnapshot(const std::string& expected_filename);

 private:
  void CopyFromBackingStoreCallback(bool success, const SkBitmap& bitmap);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  
  bool snapshot_different_;
  
  int next_dummy_search_value_;
  
  std::string expected_filename_;
  
  base::FilePath snapshot_filename_;
  
  int load_stop_notification_count_;

  net::test_server::EmbeddedTestServer pdf_test_server_;

  DISALLOW_COPY_AND_ASSIGN(PDFBrowserTest);
};

#endif  
