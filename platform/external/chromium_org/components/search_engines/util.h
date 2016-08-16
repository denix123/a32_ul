// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_UTIL_H_
#define COMPONENTS_SEARCH_ENGINES_UTIL_H_

#include <set>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/search_engines/template_url_service.h"

class KeywordWebDataService;
class PrefService;
class TemplateURL;
class WDTypedResult;

base::string16 GetDefaultSearchEngineName(TemplateURLService* service);

GURL GetDefaultSearchURLForSearchTerms(TemplateURLService* service,
                                       const base::string16& terms);

TemplateURL* FindURLByPrepopulateID(
    const TemplateURLService::TemplateURLVector& template_urls,
    int prepopulate_id);

void MergeIntoPrepopulatedEngineData(const TemplateURL* original_turl,
                                     TemplateURLData* prepopulated_url);


typedef std::pair<TemplateURL*, TemplateURLData> EditedSearchEngine;
typedef std::vector<EditedSearchEngine> EditedEngines;

struct ActionsFromPrepopulateData {
  ActionsFromPrepopulateData();
  ~ActionsFromPrepopulateData();

  TemplateURLService::TemplateURLVector removed_engines;
  EditedEngines edited_engines;
  std::vector<TemplateURLData> added_engines;
};

ActionsFromPrepopulateData CreateActionsFromCurrentPrepopulateData(
    ScopedVector<TemplateURLData>* prepopulated_urls,
    const TemplateURLService::TemplateURLVector& existing_urls,
    const TemplateURL* default_search_provider);

void GetSearchProvidersUsingKeywordResult(
    const WDTypedResult& result,
    KeywordWebDataService* service,
    PrefService* prefs,
    TemplateURLService::TemplateURLVector* template_urls,
    TemplateURL* default_search_provider,
    const SearchTermsData& search_terms_data,
    int* new_resource_keyword_version,
    std::set<std::string>* removed_keyword_guids);

void GetSearchProvidersUsingLoadedEngines(
    KeywordWebDataService* service,
    PrefService* prefs,
    TemplateURLService::TemplateURLVector* template_urls,
    TemplateURL* default_search_provider,
    const SearchTermsData& search_terms_data,
    int* resource_keyword_version,
    std::set<std::string>* removed_keyword_guids);

bool DeDupeEncodings(std::vector<std::string>* encodings);

void RemoveDuplicatePrepopulateIDs(
    KeywordWebDataService* service,
    const ScopedVector<TemplateURLData>& prepopulated_urls,
    TemplateURL* default_search_provider,
    TemplateURLService::TemplateURLVector* template_urls,
    const SearchTermsData& search_terms_data,
    std::set<std::string>* removed_keyword_guids);

#endif  
