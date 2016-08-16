// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_BASE_SEARCH_PROVIDER_H_
#define COMPONENTS_OMNIBOX_BASE_SEARCH_PROVIDER_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_match.h"
#include "components/omnibox/autocomplete_provider.h"
#include "components/omnibox/search_suggestion_parser.h"

class AutocompleteProviderClient;
class GURL;
class SearchTermsData;
class SuggestionDeletionHandler;
class TemplateURL;
class TemplateURLService;

namespace base {
class DictionaryValue;
class ListValue;
class Value;
}

class BaseSearchProvider : public AutocompleteProvider {
 public:
  
  static const int kDefaultProviderURLFetcherID;

  
  static const int kKeywordProviderURLFetcherID;

  
  static const int kDeletionURLFetcherID;

  BaseSearchProvider(TemplateURLService* template_url_service,
                     scoped_ptr<AutocompleteProviderClient> client,
                     AutocompleteProvider::Type type);

  
  static bool ShouldPrefetch(const AutocompleteMatch& match);

  
  
  
  
  
  static AutocompleteMatch CreateSearchSuggestion(
      const base::string16& suggestion,
      AutocompleteMatchType::Type type,
      bool from_keyword_provider,
      const TemplateURL* template_url,
      const SearchTermsData& search_terms_data);

  
  virtual void DeleteMatch(const AutocompleteMatch& match) OVERRIDE;
  virtual void AddProviderInfo(ProvidersInfo* provider_info) const OVERRIDE;

  bool field_trial_triggered_in_session() const {
    return field_trial_triggered_in_session_;
  }

 protected:
  

  
  
  static const char kRelevanceFromServerKey[];

  
  static const char kShouldPrefetchKey[];

  
  
  static const char kSuggestMetadataKey[];

  
  static const char kDeletionUrlKey[];

  
  static const char kTrue[];
  static const char kFalse[];

  virtual ~BaseSearchProvider();

  typedef std::pair<base::string16, std::string> MatchKey;
  typedef std::map<MatchKey, AutocompleteMatch> MatchMap;
  typedef ScopedVector<SuggestionDeletionHandler> SuggestionDeletionHandlers;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static AutocompleteMatch CreateSearchSuggestion(
      AutocompleteProvider* autocomplete_provider,
      const AutocompleteInput& input,
      const bool in_keyword_mode,
      const SearchSuggestionParser::SuggestResult& suggestion,
      const TemplateURL* template_url,
      const SearchTermsData& search_terms_data,
      int accepted_suggestion,
      bool append_extra_query_params);

  
  
  
  
  
  
  
  
  
  
  
  static bool ZeroSuggestEnabled(
     const GURL& suggest_url,
     const TemplateURL* template_url,
     metrics::OmniboxEventProto::PageClassification page_classification,
     const SearchTermsData& search_terms_data,
     AutocompleteProviderClient* client);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static bool CanSendURL(
      const GURL& current_page_url,
      const GURL& suggest_url,
      const TemplateURL* template_url,
      metrics::OmniboxEventProto::PageClassification page_classification,
      const SearchTermsData& search_terms_data,
      AutocompleteProviderClient* client);

  
  
  
  void SetDeletionURL(const std::string& deletion_url,
                      AutocompleteMatch* match);

  
  
  
  
  
  
  
  
  
  void AddMatchToMap(const SearchSuggestionParser::SuggestResult& result,
                     const std::string& metadata,
                     int accepted_suggestion,
                     bool mark_as_deletable,
                     bool in_keyword_mode,
                     MatchMap* map);

  
  
  
  
  
  
  bool ParseSuggestResults(const base::Value& root_val,
                           int default_result_relevance,
                           bool is_keyword_result,
                           SearchSuggestionParser::Results* results);

  
  
  virtual const TemplateURL* GetTemplateURL(bool is_keyword) const = 0;

  
  
  virtual const AutocompleteInput GetInput(bool is_keyword) const = 0;

  
  
  virtual bool ShouldAppendExtraParams(
      const SearchSuggestionParser::SuggestResult& result) const = 0;

  
  virtual void RecordDeletionResult(bool success) = 0;

  TemplateURLService* template_url_service_;
  scoped_ptr<AutocompleteProviderClient> client_;

  
  
  
  
  bool field_trial_triggered_;

  
  
  bool field_trial_triggered_in_session_;

 private:
  friend class SearchProviderTest;
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, TestDeleteMatch);

  
  void DeleteMatchFromMatches(const AutocompleteMatch& match);

  
  
  
  void OnDeletionComplete(bool success,
                          SuggestionDeletionHandler* handler);

  
  
  
  SuggestionDeletionHandlers deletion_handlers_;

  DISALLOW_COPY_AND_ASSIGN(BaseSearchProvider);
};

#endif  
