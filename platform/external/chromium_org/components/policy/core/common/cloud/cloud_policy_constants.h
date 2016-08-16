// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_CLOUD_CLOUD_POLICY_CONSTANTS_H_
#define COMPONENTS_POLICY_CORE_COMMON_CLOUD_CLOUD_POLICY_CONSTANTS_H_

#include <string>
#include <utility>

#include "components/policy/policy_export.h"

namespace policy {

namespace dm_protocol {

POLICY_EXPORT extern const char kParamAgent[];
POLICY_EXPORT extern const char kParamAppType[];
POLICY_EXPORT extern const char kParamDeviceID[];
POLICY_EXPORT extern const char kParamDeviceType[];
POLICY_EXPORT extern const char kParamOAuthToken[];
POLICY_EXPORT extern const char kParamPlatform[];
POLICY_EXPORT extern const char kParamRequest[];
POLICY_EXPORT extern const char kParamUserAffiliation[];

POLICY_EXPORT extern const char kValueAppType[];
POLICY_EXPORT extern const char kValueDeviceType[];
POLICY_EXPORT extern const char kValueRequestAutoEnrollment[];
POLICY_EXPORT extern const char kValueRequestPolicy[];
POLICY_EXPORT extern const char kValueRequestRegister[];
POLICY_EXPORT extern const char kValueRequestApiAuthorization[];
POLICY_EXPORT extern const char kValueRequestUnregister[];
POLICY_EXPORT extern const char kValueRequestUploadCertificate[];
POLICY_EXPORT extern const char kValueRequestDeviceStateRetrieval[];
POLICY_EXPORT extern const char kValueUserAffiliationManaged[];
POLICY_EXPORT extern const char kValueUserAffiliationNone[];

POLICY_EXPORT extern const char kChromeDevicePolicyType[];
POLICY_EXPORT extern const char kChromeUserPolicyType[];
POLICY_EXPORT extern const char kChromePublicAccountPolicyType[];
POLICY_EXPORT extern const char kChromeExtensionPolicyType[];

enum PolicyFetchStatus {
  POLICY_FETCH_SUCCESS = 200,
  POLICY_FETCH_ERROR_NOT_FOUND = 902,
};

}  

POLICY_EXPORT extern const char kChromePolicyHeader[];

POLICY_EXPORT std::string GetPolicyVerificationKey();
POLICY_EXPORT extern const char kPolicyVerificationKeyHash[];

enum UserAffiliation {
  
  USER_AFFILIATION_MANAGED,
  
  USER_AFFILIATION_NONE,
};

enum DeviceManagementStatus {
  
  DM_STATUS_SUCCESS = 0,
  
  DM_STATUS_REQUEST_INVALID = 1,
  
  DM_STATUS_REQUEST_FAILED = 2,
  
  DM_STATUS_TEMPORARY_UNAVAILABLE = 3,
  
  DM_STATUS_HTTP_STATUS_ERROR = 4,
  
  DM_STATUS_RESPONSE_DECODING_ERROR = 5,
  
  DM_STATUS_SERVICE_MANAGEMENT_NOT_SUPPORTED = 6,
  
  DM_STATUS_SERVICE_DEVICE_NOT_FOUND = 7,
  
  DM_STATUS_SERVICE_MANAGEMENT_TOKEN_INVALID = 8,
  
  DM_STATUS_SERVICE_ACTIVATION_PENDING = 9,
  
  DM_STATUS_SERVICE_INVALID_SERIAL_NUMBER = 10,
  
  DM_STATUS_SERVICE_DEVICE_ID_CONFLICT = 11,
  // Service error: The licenses have expired or have been exhausted.
  DM_STATUS_SERVICE_MISSING_LICENSES = 12,
  
  DM_STATUS_SERVICE_DEPROVISIONED = 13,
  
  DM_STATUS_SERVICE_DOMAIN_MISMATCH = 14,
  
  DM_STATUS_SERVICE_POLICY_NOT_FOUND = 902,
};

enum DeviceMode {
  DEVICE_MODE_PENDING,         
  DEVICE_MODE_NOT_SET,         
  DEVICE_MODE_CONSUMER,        
                               
  DEVICE_MODE_ENTERPRISE,      
                               
  DEVICE_MODE_RETAIL_KIOSK,    
  DEVICE_MODE_CONSUMER_KIOSK_AUTOLAUNCH,  
                                          
                                          
};

typedef std::pair<std::string, std::string> PolicyNamespaceKey;

POLICY_EXPORT const char* GetChromeUserPolicyType();

}  

#endif  
