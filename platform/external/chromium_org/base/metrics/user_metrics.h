// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_METRICS_USER_METRICS_H_
#define BASE_METRICS_USER_METRICS_H_

#include <string>

#include "base/base_export.h"
#include "base/callback.h"
#include "base/metrics/user_metrics_action.h"

namespace base {


BASE_EXPORT void RecordAction(const UserMetricsAction& action);

BASE_EXPORT void RecordComputedAction(const std::string& action);

typedef base::Callback<void(const std::string&)> ActionCallback;

BASE_EXPORT void AddActionCallback(const ActionCallback& callback);
BASE_EXPORT void RemoveActionCallback(const ActionCallback& callback);

}  

#endif  
