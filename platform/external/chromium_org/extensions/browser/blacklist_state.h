// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_BLACKLIST_STATE_H_
#define EXTENSIONS_BROWSER_BLACKLIST_STATE_H_

namespace extensions {

enum BlacklistState {
  NOT_BLACKLISTED = 0,
  BLACKLISTED_MALWARE = 1,
  BLACKLISTED_SECURITY_VULNERABILITY = 2,
  BLACKLISTED_CWS_POLICY_VIOLATION = 3,
  BLACKLISTED_POTENTIALLY_UNWANTED = 4,
  BLACKLISTED_UNKNOWN  
                       
};

} 

#endif  
