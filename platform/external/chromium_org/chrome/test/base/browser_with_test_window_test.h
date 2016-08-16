// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_BROWSER_WITH_TEST_WINDOW_TEST_H_
#define CHROME_TEST_BASE_BROWSER_WITH_TEST_WINDOW_TEST_H_

#include "base/at_exit.h"
#include "base/message_loop/message_loop.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/host_desktop.h"
#include "chrome/test/base/test_browser_window.h"
#include "chrome/test/base/testing_profile.h"
#include "content/public/test/test_browser_thread_bundle.h"
#include "content/public/test/test_renderer_host.h"
#include "testing/gtest/include/gtest/gtest.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/login/users/scoped_test_user_manager.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#endif

#if defined(OS_WIN)
#include "ui/base/win/scoped_ole_initializer.h"
#endif

class GURL;

#if defined(USE_ASH)
namespace ash {
namespace test {
class AshTestHelper;
}
}
#endif

#if defined(USE_AURA)
namespace aura {
namespace test {
class AuraTestHelper;
}
}
#endif

#if defined(TOOLKIT_VIEWS)
namespace views {
class ViewsDelegate;
}
#endif

namespace content {
class NavigationController;
class WebContents;
}

class BrowserWithTestWindowTest : public testing::Test {
 public:
  
  
  BrowserWithTestWindowTest();

  
  
  BrowserWithTestWindowTest(Browser::Type browser_type,
                            chrome::HostDesktopType host_desktop_type,
                            bool hosted_app);

  virtual ~BrowserWithTestWindowTest();

  virtual void SetUp() OVERRIDE;
  virtual void TearDown() OVERRIDE;

 protected:
  BrowserWindow* window() const { return window_.get(); }

  Browser* browser() const { return browser_.get(); }
  void set_browser(Browser* browser) {
    browser_.reset(browser);
  }
  Browser* release_browser() WARN_UNUSED_RESULT {
    return browser_.release();
  }

  TestingProfile* profile() const { return profile_; }

  TestingProfile* GetProfile() { return profile_; }

  BrowserWindow* release_browser_window() WARN_UNUSED_RESULT {
    return window_.release();
  }

  
  
  void AddTab(Browser* browser, const GURL& url);

  
  
  void CommitPendingLoad(content::NavigationController* controller);

  
  
  
  
  void NavigateAndCommit(content::NavigationController* controller,
                         const GURL& url);

  
  void NavigateAndCommitActiveTab(const GURL& url);

  
  void NavigateAndCommitActiveTabWithTitle(Browser* browser,
                                           const GURL& url,
                                           const base::string16& title);

  
  
  void DestroyBrowserAndProfile();

  
  virtual TestingProfile* CreateProfile();

  
  virtual void DestroyProfile(TestingProfile* profile);

  
  
  virtual BrowserWindow* CreateBrowserWindow();

  
  
  virtual Browser* CreateBrowser(Profile* profile,
                                 Browser::Type browser_type,
                                 bool hosted_app,
                                 chrome::HostDesktopType host_desktop_type,
                                 BrowserWindow* browser_window);

 private:
#if !defined(OS_CHROMEOS) && defined(TOOLKIT_VIEWS)
  
  
  views::ViewsDelegate* CreateViewsDelegate();
#endif

  
  content::TestBrowserThreadBundle thread_bundle_;
  base::ShadowingAtExitManager at_exit_manager_;

#if defined(OS_CHROMEOS)
  chromeos::ScopedTestDeviceSettingsService test_device_settings_service_;
  chromeos::ScopedTestCrosSettings test_cros_settings_;
  chromeos::ScopedTestUserManager test_user_manager_;
#endif

  
  // |DestroyProfile()| function - which can be overwritten by derived testing
  
  TestingProfile* profile_;
  scoped_ptr<BrowserWindow> window_;  
  scoped_ptr<Browser> browser_;

  
  
  content::RenderViewHostTestEnabler rvh_test_enabler_;

#if defined(USE_ASH)
  scoped_ptr<ash::test::AshTestHelper> ash_test_helper_;
#endif
#if defined(USE_AURA)
  scoped_ptr<aura::test::AuraTestHelper> aura_test_helper_;
#endif

#if defined(TOOLKIT_VIEWS)
  scoped_ptr<views::ViewsDelegate> views_delegate_;
#endif

#if defined(OS_WIN)
  ui::ScopedOleInitializer ole_initializer_;
#endif

  
  Browser::Type browser_type_;

  
  chrome::HostDesktopType host_desktop_type_;

  
  bool hosted_app_;

  DISALLOW_COPY_AND_ASSIGN(BrowserWithTestWindowTest);
};

#endif  
