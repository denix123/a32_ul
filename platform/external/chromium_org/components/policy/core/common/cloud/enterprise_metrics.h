// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_CLOUD_ENTERPRISE_METRICS_H_
#define COMPONENTS_POLICY_CORE_COMMON_CLOUD_ENTERPRISE_METRICS_H_

#include "components/policy/policy_export.h"

namespace policy {


enum MetricToken {
  
  kMetricTokenLoadSucceeded = 0,
  
  kMetricTokenLoadFailed = 1,

  
  kMetricTokenFetchRequested = 2,
  
  kMetricTokenFetchRequestFailed = 3,
  
  kMetricTokenFetchServerFailed = 4,
  
  kMetricTokenFetchResponseReceived = 5,
  
  
  kMetricTokenFetchBadResponse = 6,
  
  kMetricTokenFetchManagementNotSupported = 7,
  
  kMetricTokenFetchDeviceNotFound = 8,
  
  kMetricTokenFetchOK = 9,

  
  kMetricTokenStoreSucceeded = 10,
  
  kMetricTokenStoreFailed = 11,

  
  kMetricTokenFetchDeviceIdConflict = 12,
  
  kMetricTokenFetchInvalidSerialNumber = 13,
  // DM server reported that the licenses for the domain have expired or been
  
  kMetricMissingLicenses = 14,

  kMetricTokenSize  
};

enum MetricPolicy {
  
  kMetricPolicyLoadSucceeded = 0,
  
  kMetricPolicyLoadFailed = 1,

  
  kMetricPolicyFetchRequested = 2,
  
  kMetricPolicyFetchRequestFailed = 3,
  
  kMetricPolicyFetchServerFailed = 4,
  
  kMetricPolicyFetchNotFound = 5,
  
  kMetricPolicyFetchInvalidToken = 6,
  
  kMetricPolicyFetchResponseReceived = 7,
  
  
  kMetricPolicyFetchBadResponse = 8,
  
  kMetricPolicyFetchInvalidPolicy = 9,
  
  kMetricPolicyFetchBadSignature = 10,
  
  kMetricPolicyFetchTimestampInFuture = 11,
  
  kMetricPolicyFetchNonEnterpriseDevice = 12,
  
  
  kMetricPolicyFetchUserMismatch = 13,
  
  
  
  kMetricPolicyFetchOtherFailed = 14,
  
  kMetricPolicyFetchOK = 15,
  
  
  kMetricPolicyFetchNotModified = 16,

  
  kMetricPolicyStoreSucceeded = 17,
  
  kMetricPolicyStoreFailed = 18,

  kMetricPolicySize  
};

enum MetricEnrollment {
  
  kMetricEnrollmentCancelled = 0,
  
  kMetricEnrollmentStarted = 1,
  
  kMetricEnrollmentNetworkFailed = 2,
  
  kMetricEnrollmentLoginFailed = 3,
  
  
  kMetricEnrollmentNotSupported = 4,
  
  
  
  kMetricEnrollmentOK = 7,
  
  
  kMetricEnrollmentRegisterPolicyInvalidSerial = 8,
  
  kMetricEnrollmentAutoStarted = 9,
  
  kMetricEnrollmentAutoFailed = 10,
  
  kMetricEnrollmentAutoRestarted = 11,
  
  kMetricEnrollmentAutoCancelled = 12,
  
  kMetricEnrollmentAutoOK = 13,
  
  kMetricEnrollmentInvalidEnrollmentMode = 14,
  
  
  kMetricEnrollmentAutoEnrollmentNotSupported = 15,
  
  kMetricEnrollmentLockboxTimeoutError = 16,
  
  kMetricEnrollmentLockDomainMismatch = 17,
  // Registration / policy fetch failed: DM server reports licenses expired or
  
  kMetricEnrollmentRegisterPolicyMissingLicenses = 18,
  
  kMetricEnrollmentRobotAuthCodeFetchFailed = 19,
  
  kMetricEnrollmentRobotRefreshTokenFetchFailed = 20,
  
  kMetricEnrollmentRobotRefreshTokenStoreFailed = 21,
  
  
  kMetricEnrollmentRegisterPolicyDeprovisioned = 22,
  
  kMetricEnrollmentRegisterPolicyDomainMismatch = 23,
  
  kMetricEnrollmentTriggered = 24,
  
  
  kMetricEnrollmentRestarted = 25,
  
  kMetricEnrollmentStoreTokenAndIdFailed = 26,
  
  kMetricEnrollmentNoStateKeys = 27,
  
  kMetricEnrollmentPolicyValidationFailed = 28,
  
  kMetricEnrollmentCloudPolicyStoreError = 29,
  
  kMetricEnrollmentLockBackendError = 30,
  
  
  kMetricEnrollmentRegisterPolicyPayloadInvalid = 31,
  
  kMetricEnrollmentRegisterPolicyDeviceNotFound = 32,
  
  kMetricEnrollmentRegisterPolicyDMTokenInvalid = 33,
  
  kMetricEnrollmentRegisterPolicyActivationPending = 34,
  
  kMetricEnrollmentRegisterPolicyDeviceIdConflict = 35,
  
  kMetricEnrollmentRegisterPolicyNotFound = 36,
  
  kMetricEnrollmentRegisterPolicyRequestFailed = 37,
  
  kMetricEnrollmentRegisterPolicyTempUnavailable = 38,
  
  
  kMetricEnrollmentRegisterPolicyHttpError = 39,
  
  kMetricEnrollmentRegisterPolicyResponseInvalid = 40,
  
  kMetricEnrollmentAccountNotSignedUp = 41,
  
  kMetricEnrollmentAccountDeleted = 42,
  
  kMetricEnrollmentAccountDisabled = 43,
  
  kMetricEnrollmentPrecheckDomainMismatch = 44
};

enum MetricPolicyRefresh {
  
  
  METRIC_POLICY_REFRESH_CHANGED = 0,
  
  
  METRIC_POLICY_REFRESH_CHANGED_NO_INVALIDATIONS = 1,
  
  
  METRIC_POLICY_REFRESH_UNCHANGED = 2,
  
  
  METRIC_POLICY_REFRESH_INVALIDATED_CHANGED = 3,
  
  
  METRIC_POLICY_REFRESH_INVALIDATED_UNCHANGED = 4,

  METRIC_POLICY_REFRESH_SIZE  
};

enum PolicyInvalidationType {
  
  POLICY_INVALIDATION_TYPE_NO_PAYLOAD = 0,
  
  POLICY_INVALIDATION_TYPE_NORMAL = 1,
  
  POLICY_INVALIDATION_TYPE_NO_PAYLOAD_EXPIRED = 3,
  
  POLICY_INVALIDATION_TYPE_EXPIRED = 4,

  POLICY_INVALIDATION_TYPE_SIZE  
};

POLICY_EXPORT extern const char kMetricToken[];
POLICY_EXPORT extern const char kMetricPolicy[];
POLICY_EXPORT extern const char kMetricUserPolicyRefresh[];
POLICY_EXPORT extern const char kMetricUserPolicyInvalidations[];
POLICY_EXPORT extern const char kMetricDevicePolicyRefresh[];
POLICY_EXPORT extern const char kMetricDevicePolicyInvalidations[];

}  

#endif  
