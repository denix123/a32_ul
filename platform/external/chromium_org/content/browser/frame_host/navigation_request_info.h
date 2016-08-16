// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_NAVIGATION_REQUEST_INFO_H_
#define CONTENT_BROWSER_FRAME_HOST_NAVIGATION_REQUEST_INFO_H_

#include <string>

#include "base/basictypes.h"
#include "content/common/frame_messages.h"
#include "content/public/common/referrer.h"
#include "url/gurl.h"

namespace content {

struct NavigationRequestInfo {
  NavigationRequestInfo(const FrameHostMsg_BeginNavigation_Params& params);

  const FrameHostMsg_BeginNavigation_Params navigation_params;

  
  
  

  
  
  GURL first_party_for_cookies;
  bool is_main_frame;
  bool parent_is_main_frame;
};

}  

#endif  
