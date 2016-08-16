// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CAPTIVE_PORTAL_CAPTIVE_PORTAL_TESTING_UTILS_H_
#define COMPONENTS_CAPTIVE_PORTAL_CAPTIVE_PORTAL_TESTING_UTILS_H_

#include <string>

#include "base/basictypes.h"
#include "components/captive_portal/captive_portal_detector.h"
#include "net/url_request/test_url_fetcher_factory.h"

namespace base {
class Time;
}

namespace captive_portal {

class CaptivePortalDetectorTestBase {
 public:
  CaptivePortalDetectorTestBase();
  virtual ~CaptivePortalDetectorTestBase();

  
  void SetTime(const base::Time& time);

  
  void AdvanceTime(const base::TimeDelta& time_delta);

  bool FetchingURL();

  
  void CompleteURLFetch(int net_error,
                        int status_code,
                        const char* response_headers);

  void set_detector(CaptivePortalDetector* detector) { detector_ = detector; }

  CaptivePortalDetector* detector() { return detector_; }

  net::TestURLFetcher* fetcher() { return factory_.GetFetcherByID(0); }

 protected:
  CaptivePortalDetector* detector_;

  net::TestURLFetcherFactory factory_;

  DISALLOW_COPY_AND_ASSIGN(CaptivePortalDetectorTestBase);
};

}  

#endif  
