// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BLACKLIST_LOAD_ANALYZER_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BLACKLIST_LOAD_ANALYZER_H_

#include <vector>

#include "base/strings/string16.h"
#include "chrome/browser/safe_browsing/incident_reporting/add_incident_callback.h"

namespace safe_browsing {

void RegisterBlacklistLoadAnalysis();

bool GetLoadedBlacklistedModules(std::vector<base::string16>* module_names);

void VerifyBlacklistLoadState(const AddIncidentCallback& callback);

}  

#endif  
