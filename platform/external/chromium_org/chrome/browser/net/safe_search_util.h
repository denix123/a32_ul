// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_SAFE_SEARCH_UTIL_H_
#define CHROME_BROWSER_NET_SAFE_SEARCH_UTIL_H_

class GURL;

namespace net {
class HttpRequestHeaders;
class URLRequest;
}

namespace safe_search_util {

void ForceGoogleSafeSearch(const net::URLRequest* request, GURL* new_url);

void ForceYouTubeSafetyMode(const net::URLRequest* request,
                            net::HttpRequestHeaders* headers);

}  

#endif  
