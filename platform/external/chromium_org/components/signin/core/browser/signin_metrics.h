// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_METRICS_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_METRICS_H_

#include "base/time/time.h"

namespace signin_metrics {

enum DifferentPrimaryAccounts {
  
  ACCOUNTS_SAME = 0,
  
  UNUSED_ACCOUNTS_DIFFERENT,
  
  NO_COOKIE_PRESENT,
  
  COOKIE_AND_TOKEN_PRIMARIES_DIFFERENT,
  NUM_DIFFERENT_PRIMARY_ACCOUNT_METRICS,
};

enum ProfileSignout {
  
  SIGNOUT_TEST = 0,
  
  SIGNOUT_PREF_CHANGED = 0,
  
  GOOGLE_SERVICE_NAME_PATTERN_CHANGED,
  
  
  SIGNIN_PREF_CHANGED_DURING_SIGNIN,
  
  USER_CLICKED_SIGNOUT_SETTINGS,
  
  
  ABORT_SIGNIN,
  
  SERVER_FORCED_DISABLE,
  
  
  TRANSFER_CREDENTIALS,

  
  NUM_PROFILE_SIGNOUT_METRICS,
};

void LogSigninAccountReconciliation(int total_number_accounts,
                                    int count_added_to_cookie_jar,
                                    int count_removed_from_cookie_jar,
                                    bool primary_accounts_same,
                                    bool is_first_reconcile,
                                    int pre_count_gaia_cookies);

void LogSigninAddAccount();

void LogSigninProfile(bool is_first_run, base::Time install_date);

void LogSignout(ProfileSignout metric);

void LogExternalCcResultFetches(bool fetches_completed);

}  

#endif  
