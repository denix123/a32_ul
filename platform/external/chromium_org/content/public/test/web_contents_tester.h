// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_WEB_CONTENTS_TESTER_H_
#define CONTENT_PUBLIC_TEST_WEB_CONTENTS_TESTER_H_

#include "ui/base/page_transition_types.h"

class GURL;

namespace content {

class BrowserContext;
class RenderFrameHost;
class RenderViewHost;
class SiteInstance;
class WebContents;
struct Referrer;
struct WebPreferences;

class WebContentsTester {
 public:
  
  
  
  
  static WebContentsTester* For(WebContents* contents);

  
  static WebContents* CreateTestWebContents(
      BrowserContext* browser_context,
      SiteInstance* instance);

  
  
  virtual void CommitPendingNavigation() = 0;

  
  
  virtual RenderFrameHost* GetPendingMainFrame() const = 0;

  
  
  
  virtual void NavigateAndCommit(const GURL& url) = 0;

  
  virtual void TestSetIsLoading(bool value) = 0;

  
  
  
  virtual void ProceedWithCrossSiteNavigation() = 0;

  virtual void TestDidNavigate(RenderFrameHost* render_frame_host,
                               int page_id,
                               const GURL& url,
                               ui::PageTransition transition) = 0;

  virtual void TestDidNavigateWithReferrer(
      RenderFrameHost* render_frame_host,
      int page_id,
      const GURL& url,
      const Referrer& referrer,
      ui::PageTransition transition) = 0;

  
  virtual WebPreferences TestComputeWebkitPrefs() = 0;
};

}  

#endif  
