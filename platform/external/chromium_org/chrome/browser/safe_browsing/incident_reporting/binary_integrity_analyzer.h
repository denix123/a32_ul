// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BINARY_INTEGRITY_ANALYZER_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BINARY_INTEGRITY_ANALYZER_H_

#include <vector>

#include "chrome/browser/safe_browsing/incident_reporting/add_incident_callback.h"

namespace base {
class FilePath;
}  

namespace safe_browsing {

void RegisterBinaryIntegrityAnalysis();

void VerifyBinaryIntegrity(const AddIncidentCallback& callback);

std::vector<base::FilePath> GetCriticalBinariesPath();

}  

#endif  
