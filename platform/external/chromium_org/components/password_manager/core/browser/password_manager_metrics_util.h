// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_METRICS_UTIL_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_METRICS_UTIL_H_

#include <string>

class PrefService;

namespace password_manager {

namespace metrics_util {

enum ResponseType {
  NO_RESPONSE = 0,
  REMEMBER_PASSWORD,
  NEVER_REMEMBER_PASSWORD,
  INFOBAR_DISMISSED,
  NUM_RESPONSE_TYPES,
};

enum UIDisplayDisposition {
  AUTOMATIC_WITH_PASSWORD_PENDING = 0,
  MANUAL_WITH_PASSWORD_PENDING,
  MANUAL_MANAGE_PASSWORDS,
  MANUAL_BLACKLISTED,
  AUTOMATIC_GENERATED_PASSWORD_CONFIRMATION,
  NUM_DISPLAY_DISPOSITIONS
};

enum UIDismissalReason {
  
  
  NO_DIRECT_INTERACTION = 0,
  CLICKED_SAVE,
  CLICKED_NOPE,
  CLICKED_NEVER,
  CLICKED_MANAGE,
  CLICKED_DONE,
  CLICKED_UNBLACKLIST,
  CLICKED_OK,
  NUM_UI_RESPONSES,

  
  
  
  NOT_DISPLAYED
};


const size_t kGroupsPerDomain = 10u;

size_t MonitoredDomainGroupId(const std::string& url_host,
                              PrefService* pref_service);

void LogUMAHistogramEnumeration(const std::string& name,
                                int sample,
                                int boundary_value);

void LogUMAHistogramBoolean(const std::string& name, bool sample);

std::string GroupIdToString(size_t group_id);

void LogUIDismissalReason(UIDismissalReason reason);

void LogUIDismissalReason(ResponseType type);

void LogUIDisplayDisposition(UIDisplayDisposition disposition);

}  

}  

#endif  
