// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_REDIRECT_INFO_H_
#define NET_URL_REQUEST_REDIRECT_INFO_H_

#include <string>

#include "net/base/net_export.h"
#include "url/gurl.h"

namespace net {

struct NET_EXPORT RedirectInfo {
  RedirectInfo();
  ~RedirectInfo();

  
  
  
  int status_code;

  
  
  std::string new_method;

  
  GURL new_url;

  
  GURL new_first_party_for_cookies;

  
  std::string new_referrer;
};

}  

#endif  
