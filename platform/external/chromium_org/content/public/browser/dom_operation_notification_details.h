// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DOM_OPERATION_NOTIFICATION_DETAILS_H_
#define CONTENT_PUBLIC_BROWSER_DOM_OPERATION_NOTIFICATION_DETAILS_H_

namespace content {

struct DomOperationNotificationDetails {
 public:
  DomOperationNotificationDetails(const std::string& json, int automation_id)
    : json(json), automation_id(automation_id) { }

  std::string json;
  int automation_id;
};

}  

#endif  