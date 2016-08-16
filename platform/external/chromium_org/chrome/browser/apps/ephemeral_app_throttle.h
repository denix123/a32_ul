// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_EPHEMERAL_APP_THROTTLE_H_
#define CHROME_BROWSER_APPS_EPHEMERAL_APP_THROTTLE_H_

#include "base/basictypes.h"

namespace content {
class ResourceThrottle;
}

namespace net {
class URLRequest;
}

class ProfileIOData;

class EphemeralAppThrottle {
 public:
  static content::ResourceThrottle* MaybeCreateThrottleForLaunch(
      net::URLRequest* request,
      ProfileIOData* profile_io_data);

 private:
  DISALLOW_COPY_AND_ASSIGN(EphemeralAppThrottle);
};

#endif  
