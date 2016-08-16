// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_BROWSING_DATA_CANONICAL_COOKIE_HASH_H_
#define CHROME_BROWSER_BROWSING_DATA_CANONICAL_COOKIE_HASH_H_

#if defined(COMPILER_MSVC)
#include <functional>
#endif  

#include "base/containers/hash_tables.h"
#include "net/cookies/canonical_cookie.h"

namespace canonical_cookie {

size_t FastHash(const net::CanonicalCookie& cookie);

#if defined(COMPILER_MSVC)
struct CanonicalCookieTraits {
  static const size_t bucket_size = 4;

  
  size_t operator()(const net::CanonicalCookie& cookie) const {
    return FastHash(cookie);
  }

  
  
  
  
  bool operator()(const net::CanonicalCookie& cookie1,
                  const net::CanonicalCookie& cookie2) const {
    std::less<std::string> less_than;
    if (less_than(cookie1.Name(), cookie2.Name()))
      return true;
    if (less_than(cookie2.Name(), cookie1.Name()))
      return false;
    if (less_than(cookie1.Path(), cookie2.Path()))
      return true;
    if (less_than(cookie2.Path(), cookie1.Path()))
      return false;
    if (less_than(cookie1.Domain(), cookie2.Domain()))
      return true;
    if (less_than(cookie2.Domain(), cookie1.Domain()))
      return false;

    
    return false;
  }
};

typedef base::hash_set<net::CanonicalCookie, CanonicalCookieTraits>
    CookieHashSet;

#else  

struct CanonicalCookieHasher {
  std::size_t operator()(const net::CanonicalCookie& cookie) const {
    return FastHash(cookie);
  }
};

struct CanonicalCookieComparer {
  bool operator()(const net::CanonicalCookie& cookie1,
                  const net::CanonicalCookie& cookie2) const {
    return cookie1.Name() == cookie2.Name() &&
           cookie1.Domain() == cookie2.Domain() &&
           cookie1.Path() == cookie2.Path();
  }
};

typedef base::hash_set<net::CanonicalCookie,
                       CanonicalCookieHasher,
                       CanonicalCookieComparer> CookieHashSet;

#endif  

};  

#endif  
