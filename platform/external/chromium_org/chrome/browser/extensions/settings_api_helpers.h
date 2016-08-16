// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_SETTINGS_API_HELPERS_H_
#define CHROME_BROWSER_EXTENSIONS_SETTINGS_API_HELPERS_H_

#include "chrome/common/extensions/manifest_handlers/settings_overrides_handler.h"

namespace content {
class BrowserContext;
}

namespace extensions {

const Extension* GetExtensionOverridingHomepage(
    content::BrowserContext* browser_context);

const Extension* GetExtensionOverridingStartupPages(
    content::BrowserContext* browser_context);

const Extension* GetExtensionOverridingSearchEngine(
    content::BrowserContext* browser_context);

const Extension* GetExtensionOverridingProxy(
    content::BrowserContext* browser_context);

}  

#endif  
