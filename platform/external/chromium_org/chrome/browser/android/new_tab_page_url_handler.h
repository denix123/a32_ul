// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_NEW_TAB_PAGE_URL_HANDLER_H_
#define CHROME_BROWSER_ANDROID_NEW_TAB_PAGE_URL_HANDLER_H_

class GURL;

namespace content {
class BrowserContext;
}

namespace chrome {
namespace android {

bool HandleAndroidNewTabURL(GURL* url,
                            content::BrowserContext* browser_context);

}  
}  

#endif  
