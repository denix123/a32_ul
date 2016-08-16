// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_ENVIRONMENT_DATA_COLLECTION_WIN_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_ENVIRONMENT_DATA_COLLECTION_WIN_H_

namespace safe_browsing {

class ClientIncidentReport_EnvironmentData_Process;

bool CollectDlls(ClientIncidentReport_EnvironmentData_Process* process);

void RecordLspFeature(ClientIncidentReport_EnvironmentData_Process* process);

void CollectModuleVerificationData(
    const wchar_t* const modules_to_verify[],
    size_t num_modules_to_verify,
    ClientIncidentReport_EnvironmentData_Process* process);

void CollectDllBlacklistData(
    ClientIncidentReport_EnvironmentData_Process* process);

}  

#endif  
