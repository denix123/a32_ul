// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUGGESTIONS_BLACKLIST_STORE_H_
#define COMPONENTS_SUGGESTIONS_BLACKLIST_STORE_H_

#include "base/macros.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "url/gurl.h"

class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}  

namespace suggestions {

class BlacklistStore {
 public:
  explicit BlacklistStore(PrefService* profile_prefs);
  virtual ~BlacklistStore();

  
  virtual bool BlacklistUrl(const GURL& url);

  
  
  virtual bool GetFirstUrlFromBlacklist(GURL* url);

  
  
  virtual bool RemoveUrl(const GURL& url);

  
  virtual void FilterSuggestions(SuggestionsProfile* suggestions);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

 protected:
  
  BlacklistStore() {}

  
  
  
  
  bool LoadBlacklist(SuggestionsBlacklist* blacklist);

  
  
  bool StoreBlacklist(const SuggestionsBlacklist& blacklist);

  
  void ClearBlacklist();

 private:
  
  PrefService* pref_service_;

  DISALLOW_COPY_AND_ASSIGN(BlacklistStore);
};

}  

#endif  
