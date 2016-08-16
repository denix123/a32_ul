// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUGGESTIONS_SUGGESTIONS_STORE_H_
#define COMPONENTS_SUGGESTIONS_SUGGESTIONS_STORE_H_

#include "base/macros.h"
#include "components/suggestions/proto/suggestions.pb.h"

class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}  

namespace suggestions {

class SuggestionsStore {
 public:
  explicit SuggestionsStore(PrefService* profile_prefs);
  virtual ~SuggestionsStore();

  
  
  
  
  virtual bool LoadSuggestions(SuggestionsProfile* suggestions);

  
  
  virtual bool StoreSuggestions(const SuggestionsProfile& suggestions);

  
  virtual void ClearSuggestions();

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

 protected:
  
  SuggestionsStore() {}

 private:
  
  PrefService* pref_service_;

  DISALLOW_COPY_AND_ASSIGN(SuggestionsStore);

  
  void FilterExpiredSuggestions(SuggestionsProfile* suggestions);
};

}  

#endif  
