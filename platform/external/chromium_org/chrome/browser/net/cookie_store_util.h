// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_COOKIE_STORE_UTIL_H_
#define CHROME_BROWSER_NET_COOKIE_STORE_UTIL_H_

#include "content/public/browser/browser_context.h"
#include "content/public/browser/cookie_store_factory.h"

class Profile;

namespace net {
class CookieMonsterDelegate;
}  

namespace chrome_browser_net {

bool IsCookieRecordMode();

bool ShouldUseInMemoryCookiesAndCache();

net::CookieMonsterDelegate* CreateCookieDelegate(Profile* profile);

content::CookieCryptoDelegate* GetCookieCryptoDelegate();

}  

#endif  
