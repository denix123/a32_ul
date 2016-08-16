// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_SHELL_BROWSER_TEST_CHROMECAST_BROWSER_TEST_H_
#define CHROMECAST_SHELL_BROWSER_TEST_CHROMECAST_BROWSER_TEST_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_base.h"

namespace content {
class WebContents;
}

namespace chromecast {
namespace shell {

class ChromecastBrowserTest : public content::BrowserTestBase {
 protected:
  ChromecastBrowserTest();
  virtual ~ChromecastBrowserTest();

  
  virtual void SetUp() OVERRIDE;

  
  virtual void RunTestOnMainThreadLoop() OVERRIDE;

 protected:
  void NavigateToURL(content::WebContents* window, const GURL& gurl);

  
  content::WebContents* CreateBrowser();

  
  content::WebContents* web_contents() const { return web_contents_.get(); }

 private:
  scoped_ptr<content::WebContents> web_contents_;

  bool setup_called_;

  DISALLOW_COPY_AND_ASSIGN(ChromecastBrowserTest);
};

}  
}  

#endif  
