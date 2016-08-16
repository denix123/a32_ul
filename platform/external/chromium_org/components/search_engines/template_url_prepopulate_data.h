// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PREPOPULATE_DATA_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PREPOPULATE_DATA_H_

#include <stddef.h>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "components/search_engines/search_engine_type.h"

class GURL;
class PrefService;
class Profile;
class SearchTermsData;
class TemplateURL;
struct TemplateURLData;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace TemplateURLPrepopulateData {

extern const int kMaxPrepopulatedEngineID;

#if defined(OS_ANDROID)
void InitCountryCode(const std::string& country_code);
#endif

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

int GetDataVersion(PrefService* prefs);

ScopedVector<TemplateURLData> GetPrepopulatedEngines(
    PrefService* prefs,
    size_t* default_search_provider_index);

void ClearPrepopulatedEnginesInPrefs(PrefService* prefs);

scoped_ptr<TemplateURLData> GetPrepopulatedDefaultSearch(PrefService* prefs);

SearchEngineType GetEngineType(const TemplateURL& template_url,
                               const SearchTermsData& search_terms_data);

SearchEngineType GetEngineType(const GURL& url);

}  

#endif  
