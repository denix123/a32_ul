// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_METRICS_REPORTING_STATE_H_
#define CHROME_BROWSER_METRICS_METRICS_REPORTING_STATE_H_

#include "base/callback.h"

typedef base::Callback<void(bool)> OnMetricsReportingCallbackType;

void InitiateMetricsReportingChange(
    bool enabled,
    const OnMetricsReportingCallbackType& callback_fn);

bool IsMetricsReportingUserChangable();

#endif  
