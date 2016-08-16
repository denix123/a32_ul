// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_TAB_HELPERS_H_
#define CHROME_BROWSER_UI_TAB_HELPERS_H_

namespace content {
class WebContents;
}

namespace chrome {
class BrowserTabStripModelDelegate;

namespace android {
class ChromeWebContentsDelegateAndroid;
}
}

namespace prerender {
class PrerenderContents;
}

class TabHelpers {
 private:
  
  
  friend class Browser;
  friend class chrome::BrowserTabStripModelDelegate;

  
  friend class TabAndroid;
  friend class chrome::android::ChromeWebContentsDelegateAndroid;

  
  
  
  friend class BrowserNavigatorWebContentsAdoption;

  
  
  friend class prerender::PrerenderContents;

  
  
  
  
  static void AttachTabHelpers(content::WebContents* web_contents);
};

#endif  
