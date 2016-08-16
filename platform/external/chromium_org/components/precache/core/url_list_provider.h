// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PRECACHE_CORE_URL_LIST_PROVIDER_H_
#define COMPONENTS_PRECACHE_CORE_URL_LIST_PROVIDER_H_

#include <list>

#include "base/callback.h"
#include "url/gurl.h"

namespace precache {

class URLListProvider {
 public:
  typedef base::Callback<void(const std::list<GURL>&)> GetURLsCallback;

  
  
  
  virtual void GetURLs(const GetURLsCallback& callback) = 0;
};

}  

#endif  
