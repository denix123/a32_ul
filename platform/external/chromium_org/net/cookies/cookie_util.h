// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_COOKIES_COOKIE_UTIL_H_
#define NET_COOKIES_COOKIE_UTIL_H_

#include <string>
#include <utility>
#include <vector>

#include "base/strings/string_piece.h"
#include "base/time/time.h"
#include "net/base/net_export.h"

class GURL;

namespace net {
namespace cookie_util {

NET_EXPORT std::string GetEffectiveDomain(const std::string& scheme,
                                          const std::string& host);

NET_EXPORT bool GetCookieDomainWithString(const GURL& url,
                                          const std::string& domain_string,
                                          std::string* result);

NET_EXPORT bool DomainIsHostOnly(const std::string& domain_string);

NET_EXPORT base::Time ParseCookieTime(const std::string& time_string);

NET_EXPORT GURL CookieOriginToURL(const std::string& domain, bool is_https);

typedef std::pair<base::StringPiece, base::StringPiece> ParsedRequestCookie;
typedef std::vector<ParsedRequestCookie> ParsedRequestCookies;

// header is written by Chromium and therefore well-formed.
NET_EXPORT void ParseRequestCookieLine(const std::string& header_value,
                                       ParsedRequestCookies* parsed_cookies);

NET_EXPORT std::string SerializeRequestCookieLine(
    const ParsedRequestCookies& parsed_cookies);

}  
}  

#endif  
