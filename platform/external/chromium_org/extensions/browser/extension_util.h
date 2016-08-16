// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_UTIL_H_
#define EXTENSIONS_BROWSER_EXTENSION_UTIL_H_

#include <string>

namespace content {
class BrowserContext;
}

namespace extensions {
namespace util {


bool IsExtensionInstalledPermanently(const std::string& extension_id,
                                     content::BrowserContext* context);

bool IsEphemeralApp(const std::string& extension_id,
                    content::BrowserContext* context);

}  
}  

#endif  
