// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_DELAYED_ANALYSIS_CALLBACK_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_DELAYED_ANALYSIS_CALLBACK_H_

#include "base/callback_forward.h"
#include "chrome/browser/safe_browsing/incident_reporting/add_incident_callback.h"

namespace safe_browsing {

typedef base::Callback<void(const AddIncidentCallback&)>
    DelayedAnalysisCallback;

}  

#endif  
