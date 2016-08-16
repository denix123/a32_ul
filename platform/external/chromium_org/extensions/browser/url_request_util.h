// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_URL_REQUEST_UTIL_H_
#define EXTENSIONS_BROWSER_URL_REQUEST_UTIL_H_

namespace net {
class URLRequest;
}

namespace extensions {
class Extension;
class InfoMap;

namespace url_request_util {

bool AllowCrossRendererResourceLoad(net::URLRequest* request,
                                    bool is_incognito,
                                    const Extension* extension,
                                    InfoMap* extension_info_map,
                                    bool* allowed);

bool IsWebViewRequest(net::URLRequest* request);

}  
}  

#endif  
