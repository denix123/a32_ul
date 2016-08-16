// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_SEARCH_METRICS_H_
#define COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_SEARCH_METRICS_H_

#include "build/build_config.h"

class GoogleSearchMetrics {
 public:
  
  
  enum AccessPoint {
    AP_OMNIBOX,
    AP_OMNIBOX_INSTANT,
    AP_DIRECT_NAV,
    AP_DIRECT_NAV_INSTANT,
    AP_HOME_PAGE,
    AP_HOME_PAGE_INSTANT,
    AP_SEARCH_APP,
    AP_SEARCH_APP_INSTANT,
    AP_OTHER,
    AP_OTHER_INSTANT,
    AP_BOUNDARY,
  };

  GoogleSearchMetrics();
  virtual ~GoogleSearchMetrics();

  
  virtual void RecordGoogleSearch(AccessPoint ap) const;

#if defined(OS_ANDROID)
  
  
  virtual void RecordAndroidGoogleSearch(AccessPoint ap,
                                         bool prerender_enabled) const;
#endif
};

#endif  
