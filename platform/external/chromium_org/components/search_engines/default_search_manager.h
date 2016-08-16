// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_DEFAULT_SEARCH_MANAGER_H_
#define COMPONENTS_SEARCH_ENGINES_DEFAULT_SEARCH_MANAGER_H_

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_change_registrar.h"

namespace base {
class DictionaryValue;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefService;
class PrefValueMap;
struct TemplateURLData;

class DefaultSearchManager {
 public:
  static const char kDefaultSearchProviderDataPrefName[];

  static const char kID[];
  static const char kShortName[];
  static const char kKeyword[];
  static const char kPrepopulateID[];
  static const char kSyncGUID[];

  static const char kURL[];
  static const char kSuggestionsURL[];
  static const char kInstantURL[];
  static const char kImageURL[];
  static const char kNewTabURL[];
  static const char kFaviconURL[];
  static const char kOriginatingURL[];

  static const char kSearchURLPostParams[];
  static const char kSuggestionsURLPostParams[];
  static const char kInstantURLPostParams[];
  static const char kImageURLPostParams[];

  static const char kSafeForAutoReplace[];
  static const char kInputEncodings[];

  static const char kDateCreated[];
  static const char kLastModified[];

  static const char kUsageCount[];
  static const char kAlternateURLs[];
  static const char kSearchTermsReplacementKey[];
  static const char kCreatedByPolicy[];
  static const char kDisabledByPolicy[];

  enum Source {
    FROM_FALLBACK = 0,
    FROM_USER,
    FROM_EXTENSION,
    FROM_POLICY,
  };

  typedef base::Callback<void(const TemplateURLData*, Source)> ObserverCallback;

  DefaultSearchManager(PrefService* pref_service,
                       const ObserverCallback& change_observer);

  ~DefaultSearchManager();

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  static void AddPrefValueToMap(base::DictionaryValue* value,
                                PrefValueMap* pref_value_map);

  
  
  
  static void SetFallbackSearchEnginesDisabledForTesting(bool disabled);

  
  
  
  TemplateURLData* GetDefaultSearchEngine(Source* source) const;

  
  Source GetDefaultSearchEngineSource() const;

  
  void SetUserSelectedDefaultSearchEngine(const TemplateURLData& data);

  
  void SetExtensionControlledDefaultSearchEngine(const TemplateURLData& data);

  
  
  
  void ClearExtensionControlledDefaultSearchEngine();

  
  
  
  void ClearUserSelectedDefaultSearchEngine();

 private:
  
  
  
  void OnDefaultSearchPrefChanged();

  
  
  
  void OnOverridesPrefChanged();

  
  
  void MergePrefsDataWithPrepopulated();

  
  
  
  void LoadDefaultSearchEngineFromPrefs();

  
  
  
  void LoadPrepopulatedDefaultSearch();

  
  void NotifyObserver();

  PrefService* pref_service_;
  const ObserverCallback change_observer_;
  PrefChangeRegistrar pref_change_registrar_;

  
  
  
  scoped_ptr<TemplateURLData> fallback_default_search_;

  
  
  scoped_ptr<TemplateURLData> extension_default_search_;

  
  
  
  scoped_ptr<TemplateURLData> prefs_default_search_;

  
  bool default_search_controlled_by_policy_;

  DISALLOW_COPY_AND_ASSIGN(DefaultSearchManager);
};

#endif  
