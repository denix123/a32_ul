// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_INTERNALS_UTIL_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_INTERNALS_UTIL_H_

#include <map>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/values.h"

namespace signin_internals_util {

extern const char kSigninPrefPrefix[];
extern const char kTokenPrefPrefix[];

const size_t kTruncateTokenStringLength = 6;

enum {
  SIGNIN_FIELDS_BEGIN = 0,
  UNTIMED_FIELDS_BEGIN = SIGNIN_FIELDS_BEGIN
};

enum UntimedSigninStatusField {
  USERNAME = UNTIMED_FIELDS_BEGIN,
  UNTIMED_FIELDS_END
};

enum {
  UNTIMED_FIELDS_COUNT = UNTIMED_FIELDS_END - UNTIMED_FIELDS_BEGIN,
  TIMED_FIELDS_BEGIN = UNTIMED_FIELDS_END
};

enum TimedSigninStatusField {
  SIGNIN_TYPE = TIMED_FIELDS_BEGIN,
  AUTHENTICATION_RESULT_RECEIVED,
  REFRESH_TOKEN_RECEIVED,
  GET_USER_INFO_STATUS,
  UBER_TOKEN_STATUS,
  MERGE_SESSION_STATUS,
  TIMED_FIELDS_END
};

enum {
  TIMED_FIELDS_COUNT = TIMED_FIELDS_END - TIMED_FIELDS_BEGIN,
  SIGNIN_FIELDS_END = TIMED_FIELDS_END,
  SIGNIN_FIELDS_COUNT = SIGNIN_FIELDS_END - SIGNIN_FIELDS_BEGIN
};

std::string TokenPrefPath(const std::string& service_name);

std::string SigninStatusFieldToString(UntimedSigninStatusField field);
std::string SigninStatusFieldToString(TimedSigninStatusField field);

class SigninDiagnosticsObserver {
 public:
  
  virtual void NotifySigninValueChanged(const UntimedSigninStatusField& field,
                                        const std::string& value) {}
  virtual void NotifySigninValueChanged(const TimedSigninStatusField& field,
                                        const std::string& value) {}
  
  virtual void NotifyTokenReceivedSuccess(const std::string& token_name,
                                          const std::string& token,
                                          bool update_time) {}
  virtual void NotifyTokenReceivedFailure(const std::string& token_name,
                                          const std::string& error) {}
  virtual void NotifyClearStoredToken(const std::string& token_name) {}};

std::string GetTruncatedHash(const std::string& str);

} 

#endif  
