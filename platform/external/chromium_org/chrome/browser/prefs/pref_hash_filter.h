// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PREF_HASH_FILTER_H_
#define CHROME_BROWSER_PREFS_PREF_HASH_FILTER_H_

#include <map>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/prefs/interceptable_pref_filter.h"
#include "chrome/browser/prefs/tracked/tracked_preference.h"

class PrefHashStore;
class PrefService;
class PrefStore;
class TrackedPreferenceValidationDelegate;

namespace base {
class DictionaryValue;
class Time;
class Value;
}  

namespace user_prefs {
class PrefRegistrySyncable;
}  

class PrefHashFilter : public InterceptablePrefFilter {
 public:
  enum EnforcementLevel {
    NO_ENFORCEMENT,
    ENFORCE_ON_LOAD
  };

  enum PrefTrackingStrategy {
    
    TRACKING_STRATEGY_ATOMIC,
    
    
    
    TRACKING_STRATEGY_SPLIT,
  };

  struct TrackedPreferenceMetadata {
    size_t reporting_id;
    const char* name;
    EnforcementLevel enforcement_level;
    PrefTrackingStrategy strategy;
  };

  
  
  
  
  
  
  
  
  
  PrefHashFilter(
      scoped_ptr<PrefHashStore> pref_hash_store,
      const std::vector<TrackedPreferenceMetadata>& tracked_preferences,
      const base::Closure& on_reset_on_load,
      TrackedPreferenceValidationDelegate* delegate,
      size_t reporting_ids_count,
      bool report_super_mac_validity);

  virtual ~PrefHashFilter();

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  static base::Time GetResetTime(PrefService* user_prefs);

  
  
  static void ClearResetTime(PrefService* user_prefs);

  
  
  
  void Initialize(base::DictionaryValue* pref_store_contents);

  
  virtual void FilterUpdate(const std::string& path) OVERRIDE;
  virtual void FilterSerializeData(
      base::DictionaryValue* pref_store_contents) OVERRIDE;

 private:
  
  virtual void FinalizeFilterOnLoad(
      const PostFilterOnLoadCallback& post_filter_on_load_callback,
      scoped_ptr<base::DictionaryValue> pref_store_contents,
      bool prefs_altered) OVERRIDE;

  
  
  
  FilterOnLoadInterceptor filter_on_load_interceptor_;

  
  
  typedef base::ScopedPtrHashMap<std::string, TrackedPreference>
      TrackedPreferencesMap;
  
  
  typedef std::map<std::string, const TrackedPreference*> ChangedPathsMap;

  scoped_ptr<PrefHashStore> pref_hash_store_;

  
  const base::Closure on_reset_on_load_;

  TrackedPreferencesMap tracked_paths_;

  
  
  ChangedPathsMap changed_paths_;

  
  bool report_super_mac_validity_;

  DISALLOW_COPY_AND_ASSIGN(PrefHashFilter);
};

#endif  
