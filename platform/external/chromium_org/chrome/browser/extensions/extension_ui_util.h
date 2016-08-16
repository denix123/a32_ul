// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_UI_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_UI_UTIL_H_

namespace content {
class BrowserContext;
}

namespace extensions {

class Extension;

namespace ui_util {

bool ShouldDisplayInAppLauncher(const Extension* extension,
                                content::BrowserContext* context);

bool CanDisplayInAppLauncher(const Extension* extension,
                             content::BrowserContext* context);

bool ShouldDisplayInNewTabPage(const Extension* extension,
                               content::BrowserContext* context);

bool ShouldDisplayInExtensionSettings(const Extension* extension,
                                      content::BrowserContext* context);

bool ShouldNotBeVisible(const Extension* extension,
                        content::BrowserContext* context);

}  
}  

#endif  
