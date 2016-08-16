// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_MOCK_VALIDATION_DELEGATE_H_
#define CHROME_BROWSER_PREFS_MOCK_VALIDATION_DELEGATE_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/prefs/pref_hash_filter.h"
#include "chrome/browser/prefs/pref_hash_store_transaction.h"
#include "chrome/browser/prefs/tracked/tracked_preference_helper.h"
#include "chrome/browser/prefs/tracked/tracked_preference_validation_delegate.h"

class MockValidationDelegate : public TrackedPreferenceValidationDelegate {
 public:
  struct ValidationEvent {
    ValidationEvent(const std::string& path,
                    PrefHashStoreTransaction::ValueState state,
                    TrackedPreferenceHelper::ResetAction action,
                    PrefHashFilter::PrefTrackingStrategy tracking_strategy)
        : pref_path(path),
          value_state(state),
          reset_action(action),
          strategy(tracking_strategy) {}

    std::string pref_path;
    PrefHashStoreTransaction::ValueState value_state;
    TrackedPreferenceHelper::ResetAction reset_action;
    PrefHashFilter::PrefTrackingStrategy strategy;
  };

  MockValidationDelegate();
  virtual ~MockValidationDelegate();

  
  size_t recorded_validations_count() const { return validations_.size(); }

  
  size_t CountValidationsOfState(
      PrefHashStoreTransaction::ValueState value_state) const;

  
  const ValidationEvent* GetEventForPath(const std::string& pref_path) const;

  
  virtual void OnAtomicPreferenceValidation(
      const std::string& pref_path,
      const base::Value* value,
      PrefHashStoreTransaction::ValueState value_state,
      TrackedPreferenceHelper::ResetAction reset_action) OVERRIDE;
  virtual void OnSplitPreferenceValidation(
      const std::string& pref_path,
      const base::DictionaryValue* dict_value,
      const std::vector<std::string>& invalid_keys,
      PrefHashStoreTransaction::ValueState value_state,
      TrackedPreferenceHelper::ResetAction reset_action) OVERRIDE;

 private:
  
  void RecordValidation(const std::string& pref_path,
                        PrefHashStoreTransaction::ValueState value_state,
                        TrackedPreferenceHelper::ResetAction reset_action,
                        PrefHashFilter::PrefTrackingStrategy strategy);

  std::vector<ValidationEvent> validations_;

  DISALLOW_COPY_AND_ASSIGN(MockValidationDelegate);
};

#endif  
