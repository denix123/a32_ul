// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_HANDLER_UTIL_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_HANDLER_UTIL_H_

#include <stdint.h>

namespace google {
namespace protobuf {

class MessageLite;

}  
}  

namespace safe_browsing {

uint32_t HashMessage(const google::protobuf::MessageLite& message);

}  

#endif  
