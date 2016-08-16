// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BLACKLIST_LOAD_INCIDENT_HANDLERS_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_BLACKLIST_LOAD_INCIDENT_HANDLERS_H_

#include <stdint.h>

#include <string>

namespace safe_browsing {

class ClientIncidentReport_IncidentData;

std::string GetBlacklistLoadIncidentKey(
    const ClientIncidentReport_IncidentData& incident_data);

uint32_t GetBlacklistLoadIncidentDigest(
    const ClientIncidentReport_IncidentData& incident_data);

}  

#endif  