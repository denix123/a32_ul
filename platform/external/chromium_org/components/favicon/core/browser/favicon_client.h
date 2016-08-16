// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_CORE_BROWSER_FAVICON_CLIENT_H_
#define COMPONENTS_FAVICON_CORE_BROWSER_FAVICON_CLIENT_H_

#include "components/keyed_service/core/keyed_service.h"

class FaviconService;
class GURL;

class FaviconClient : public KeyedService {
 public:
  virtual ~FaviconClient() {};

  virtual FaviconService* GetFaviconService() = 0;

  
  virtual bool IsBookmarked(const GURL& url) = 0;
};

#endif  
