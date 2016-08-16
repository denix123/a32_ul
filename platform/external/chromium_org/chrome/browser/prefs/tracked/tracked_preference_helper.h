// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_HELPER_H_
#define CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_HELPER_H_

#include <string>

#include "base/macros.h"
#include "chrome/browser/prefs/pref_hash_filter.h"
#include "chrome/browser/prefs/pref_hash_store_transaction.h"

class TrackedPreferenceHelper {
 public:
  enum ResetAction {
    DONT_RESET,
    
    
    WANTED_RESET,
    DO_RESET,
  };

  TrackedPreferenceHelper(const std::string& pref_path,
                          size_t reporting_id,
                          size_t reporting_ids_count,
                          PrefHashFilter::EnforcementLevel enforcement_level);

  
  
  
  
  ResetAction GetAction(
      PrefHashStoreTransaction::ValueState value_state) const;

  
  void ReportValidationResult(
      PrefHashStoreTransaction::ValueState value_state) const;

  
  void ReportAction(ResetAction reset_action) const;

  
  
  void ReportSplitPreferenceChangedCount(size_t count) const;

 private:
  const std::string pref_path_;

  const size_t reporting_id_;
  const size_t reporting_ids_count_;

  
  const bool enforce_;

  DISALLOW_COPY_AND_ASSIGN(TrackedPreferenceHelper);
};

#endif  
