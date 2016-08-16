// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_METRICS_USER_METRICS_ACTION_H_
#define BASE_METRICS_USER_METRICS_ACTION_H_

namespace base {

struct UserMetricsAction {
  const char* str_;
  explicit UserMetricsAction(const char* str) : str_(str) {}
};

}  

#endif  
