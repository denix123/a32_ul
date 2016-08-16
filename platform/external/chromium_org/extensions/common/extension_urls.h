// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_EXTENSION_URLS_H_
#define EXTENSIONS_COMMON_EXTENSION_URLS_H_

#include <string>

#include "base/strings/string16.h"

class GURL;

namespace extensions {

extern const char kEventBindings[];

extern const char kSchemaUtils[];

bool IsSourceFromAnExtension(const base::string16& source);

}  

namespace extension_urls {

extern const char kChromeWebstoreBaseURL[];
extern const char kChromeWebstoreUpdateURL[];

std::string GetWebstoreLaunchURL();

std::string GetWebstoreExtensionsCategoryURL();

std::string GetWebstoreItemDetailURLPrefix();

GURL GetWebstoreItemJsonDataURL(const std::string& extension_id);

GURL GetWebstoreJsonSearchUrl(const std::string& query,
                              const std::string& host_language_code);

GURL GetWebstoreSearchPageUrl(const std::string& query);

GURL GetWebstoreUpdateUrl();

bool IsWebstoreUpdateUrl(const GURL& update_url);

bool IsBlacklistUpdateUrl(const GURL& url);

}  

#endif  
