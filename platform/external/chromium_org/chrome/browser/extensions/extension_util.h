// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_UTIL_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "url/gurl.h"

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
}

namespace gfx {
class ImageSkia;
}

namespace extensions {

class Extension;
struct ExtensionInfo;

namespace util {

bool IsIncognitoEnabled(const std::string& extension_id,
                        content::BrowserContext* context);

void SetIsIncognitoEnabled(const std::string& extension_id,
                           content::BrowserContext* context,
                           bool enabled);

bool CanCrossIncognito(const extensions::Extension* extension,
                       content::BrowserContext* context);

bool CanLoadInIncognito(const extensions::Extension* extension,
                        content::BrowserContext* context);

bool AllowFileAccess(const std::string& extension_id,
                     content::BrowserContext* context);

void SetAllowFileAccess(const std::string& extension_id,
                        content::BrowserContext* context,
                        bool allow);

bool AllowedScriptingOnAllUrls(const std::string& extension_id,
                               content::BrowserContext* context);

void SetAllowedScriptingOnAllUrls(const std::string& extension_id,
                                  content::BrowserContext* context,
                                  bool allowed);

bool ScriptsMayRequireActionForExtension(const Extension* extension);

bool IsAppLaunchable(const std::string& extension_id,
                     content::BrowserContext* context);

bool IsAppLaunchableWithoutEnabling(const std::string& extension_id,
                                    content::BrowserContext* context);

bool ShouldSyncExtension(const Extension* extension,
                         content::BrowserContext* context);

bool ShouldSyncApp(const Extension* app, content::BrowserContext* context);

bool IsExtensionIdle(const std::string& extension_id,
                     content::BrowserContext* context);

GURL GetSiteForExtensionId(const std::string& extension_id,
                           content::BrowserContext* context);

scoped_ptr<base::DictionaryValue> GetExtensionInfo(const Extension* extension);

bool HasIsolatedStorage(const ExtensionInfo& info);

bool SiteHasIsolatedStorage(const GURL& extension_site_url,
                            content::BrowserContext* context);

const gfx::ImageSkia& GetDefaultExtensionIcon();
const gfx::ImageSkia& GetDefaultAppIcon();

bool IsStreamlinedHostedAppsEnabled();

}  
}  

#endif  
