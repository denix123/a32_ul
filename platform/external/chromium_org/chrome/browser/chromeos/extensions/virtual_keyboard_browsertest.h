// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_VIRTUAL_KEYBOARD_BROWSERTEST_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_VIRTUAL_KEYBOARD_BROWSERTEST_H_

#include "base/files/file_path.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "url/gurl.h"

namespace base {
class CommandLine;
class FilePath;
}

namespace content {
class RenderViewHost;
class WebContents;
}

struct VirtualKeyboardBrowserTestConfig {
  VirtualKeyboardBrowserTestConfig();

  ~VirtualKeyboardBrowserTestConfig();

  
  std::string base_framework_;

  
  std::string extension_id_;

  
  std::string test_dir_;

  
  std::string url_;
};

class VirtualKeyboardBrowserTest : public InProcessBrowserTest {
 public:
  
  
  void RunTest(const base::FilePath& file,
               const VirtualKeyboardBrowserTestConfig& config);

  void ShowVirtualKeyboard();

  
  content::RenderViewHost* GetKeyboardRenderViewHost(const std::string& id);

  
  
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

 protected:
  
  
  void InjectJavascript(const base::FilePath& dir, const base::FilePath& file);

 private:
  std::string utf8_content_;
};

#endif  
