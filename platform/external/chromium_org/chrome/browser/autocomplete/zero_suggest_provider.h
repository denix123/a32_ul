// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_ZERO_SUGGEST_PROVIDER_H_
#define CHROME_BROWSER_AUTOCOMPLETE_ZERO_SUGGEST_PROVIDER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "components/history/core/browser/history_types.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/base_search_provider.h"
#include "components/omnibox/search_provider.h"
#include "net/url_request/url_fetcher_delegate.h"

class AutocompleteProviderListener;
class Profile;
class TemplateURLService;

namespace base {
class ListValue;
class Value;
}

namespace net {
class URLFetcher;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class ZeroSuggestProvider : public BaseSearchProvider,
                            public net::URLFetcherDelegate {
 public:
  
  static ZeroSuggestProvider* Create(AutocompleteProviderListener* listener,
                                     TemplateURLService* template_url_service,
                                     Profile* profile);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;
  virtual void Stop(bool clear_cached_results) OVERRIDE;
  virtual void DeleteMatch(const AutocompleteMatch& match) OVERRIDE;
  virtual void AddProviderInfo(ProvidersInfo* provider_info) const OVERRIDE;

  
  virtual void ResetSession() OVERRIDE;

 private:
  ZeroSuggestProvider(AutocompleteProviderListener* listener,
                      TemplateURLService* template_url_service,
                      Profile* profile);

  virtual ~ZeroSuggestProvider();

  
  virtual const TemplateURL* GetTemplateURL(bool is_keyword) const OVERRIDE;
  virtual const AutocompleteInput GetInput(bool is_keyword) const OVERRIDE;
  virtual bool ShouldAppendExtraParams(
      const SearchSuggestionParser::SuggestResult& result) const OVERRIDE;
  virtual void RecordDeletionResult(bool success) OVERRIDE;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  
  
  bool StoreSuggestionResponse(const std::string& json_data,
                               const base::Value& parsed_data);

  
  
  void AddSuggestResultsToMap(
      const SearchSuggestionParser::SuggestResults& results,
      MatchMap* map);

  
  AutocompleteMatch NavigationToMatch(
      const SearchSuggestionParser::NavigationResult& navigation);

  
  void Run(const GURL& suggest_url);

  
  
  
  void ConvertResultsToAutocompleteMatches();

  
  
  
  AutocompleteMatch MatchForCurrentURL();

  
  
  
  void OnMostVisitedUrlsAvailable(const history::MostVisitedURLList& urls);

  
  int GetVerbatimRelevance() const;

  
  
  bool CanShowZeroSuggestWithoutSendingURL(const GURL& suggest_url,
                                           const GURL& current_page_url) const;

  
  
  void MaybeUseCachedSuggestions();

  AutocompleteProviderListener* listener_;
  Profile* profile_;

  
  std::string current_query_;

  
  
  metrics::OmniboxEventProto::PageClassification current_page_classification_;

  
  base::string16 permanent_text_;

  
  scoped_ptr<net::URLFetcher> fetcher_;

  
  AutocompleteMatch current_url_match_;

  
  
  SearchSuggestionParser::Results results_;

  
  bool results_from_cache_;

  history::MostVisitedURLList most_visited_urls_;

  
  base::WeakPtrFactory<ZeroSuggestProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ZeroSuggestProvider);
};

#endif  
