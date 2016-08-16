// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_WEBSTORE_INSTALL_RESULT_H_
#define CHROME_COMMON_EXTENSIONS_WEBSTORE_INSTALL_RESULT_H_

namespace extensions {

namespace webstore_install {

enum Result {
  
  SUCCESS,

  
  OTHER_ERROR,

  
  ABORTED,

  
  INSTALL_IN_PROGRESS,

  
  NOT_PERMITTED,

  
  INVALID_ID,

  
  WEBSTORE_REQUEST_ERROR,

  
  INVALID_WEBSTORE_RESPONSE,

  
  
  INVALID_MANIFEST,

  
  
  ICON_ERROR,

  
  USER_CANCELLED,

  
  BLACKLISTED,

  
  MISSING_DEPENDENCIES,

  
  REQUIREMENT_VIOLATIONS,

  
  BLOCKED_BY_POLICY,

  
  LAUNCH_FEATURE_DISABLED,

  
  LAUNCH_UNSUPPORTED_EXTENSION_TYPE,

  
  LAUNCH_IN_PROGRESS,

  
  
  RESULT_LAST = LAUNCH_IN_PROGRESS,
};

}  

}  

#endif  
