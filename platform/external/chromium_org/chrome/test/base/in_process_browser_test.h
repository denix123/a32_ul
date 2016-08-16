// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_IN_PROCESS_BROWSER_TEST_H_
#define CHROME_TEST_BASE_IN_PROCESS_BROWSER_TEST_H_

#include "base/compiler_specific.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_base.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/base/page_transition_types.h"

namespace base {

class CommandLine;

#if defined(OS_MACOSX)
namespace mac {
class ScopedNSAutoreleasePool;
}  
#endif  

#if defined(OS_WIN)
namespace win {
class ScopedCOMInitializer;
}
#endif  
}  

class Browser;
class Profile;

namespace content {
class ContentRendererClient;
}


class InProcessBrowserTest : public content::BrowserTestBase {
 public:
  InProcessBrowserTest();
  virtual ~InProcessBrowserTest();

  
  
  virtual void SetUp() OVERRIDE;

  
  virtual void TearDown() OVERRIDE;

 protected:
  
  Browser* browser() const { return browser_; }

  
  void AddTabAtIndexToBrowser(Browser* browser,
                              int index,
                              const GURL& url,
                              ui::PageTransition transition);
  void AddTabAtIndex(int index, const GURL& url,
                     ui::PageTransition transition);

  
  
  
  
  
  virtual bool SetUpUserDataDirectory() WARN_UNUSED_RESULT;

  
  virtual void RunTestOnMainThreadLoop() OVERRIDE;

  
  
  
  
  Browser* CreateBrowser(Profile* profile);

  
  Browser* CreateIncognitoBrowser();

  
  
  Browser* CreateBrowserForPopup(Profile* profile);

  
  
  Browser* CreateBrowserForApp(const std::string& app_name, Profile* profile);

  
  
  void AddBlankTabAndShow(Browser* browser);

#if !defined OS_MACOSX
  
  
  
  
  
  
  base::CommandLine GetCommandLineForRelaunch();
#endif

#if defined(OS_MACOSX)
  
  base::mac::ScopedNSAutoreleasePool* AutoreleasePool() const {
    return autorelease_pool_;
  }
#endif  

  void set_exit_when_last_browser_closes(bool value) {
    exit_when_last_browser_closes_ = value;
  }

  void set_open_about_blank_on_browser_launch(bool value) {
    open_about_blank_on_browser_launch_ = value;
  }

  
  void set_multi_desktop_test(bool multi_desktop_test) {
    multi_desktop_test_ = multi_desktop_test;
  }

 private:
  
  
  virtual bool CreateUserDataDirectory() WARN_UNUSED_RESULT;

  
  void QuitBrowsers();

  
  
  void PrepareTestCommandLine(base::CommandLine* command_line);

  
  Browser* browser_;

  
  
  base::ScopedTempDir temp_user_data_dir_;

  
  bool exit_when_last_browser_closes_;

  
  bool open_about_blank_on_browser_launch_;

  
  
  bool multi_desktop_test_;

#if defined(OS_MACOSX)
  base::mac::ScopedNSAutoreleasePool* autorelease_pool_;
#endif  

#if defined(OS_WIN)
  scoped_ptr<base::win::ScopedCOMInitializer> com_initializer_;
#endif
};

#endif  
