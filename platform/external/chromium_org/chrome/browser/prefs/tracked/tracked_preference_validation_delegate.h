// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_VALIDATION_DELEGATE_H_
#define CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_VALIDATION_DELEGATE_H_

#include <string>
#include <vector>

#include "chrome/browser/prefs/pref_hash_store_transaction.h"
#include "chrome/browser/prefs/tracked/tracked_preference_helper.h"

namespace base {
class DictionaryValue;
class Value;
}

class TrackedPreferenceValidationDelegate {
 public:
  virtual ~TrackedPreferenceValidationDelegate() {}

  
  
  
  
  virtual void OnAtomicPreferenceValidation(
      const std::string& pref_path,
      const base::Value* value,
      PrefHashStoreTransaction::ValueState value_state,
      TrackedPreferenceHelper::ResetAction reset_action) = 0;

  
  
  
  
  virtual void OnSplitPreferenceValidation(
      const std::string& pref_path,
      const base::DictionaryValue* dict_value,
      const std::vector<std::string>& invalid_keys,
      PrefHashStoreTransaction::ValueState value_state,
      TrackedPreferenceHelper::ResetAction reset_action) = 0;
};

#endif  
