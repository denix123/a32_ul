// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_ENVIRONMENT_DATA_COLLECTION_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_ENVIRONMENT_DATA_COLLECTION_H_

namespace safe_browsing {

class ClientIncidentReport_EnvironmentData;

void CollectEnvironmentData(ClientIncidentReport_EnvironmentData* data);

}  

#endif  
