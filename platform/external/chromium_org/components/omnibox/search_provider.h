// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_SEARCH_PROVIDER_H_
#define COMPONENTS_OMNIBOX_SEARCH_PROVIDER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "components/metrics/proto/omnibox_input_type.pb.h"
#include "components/omnibox/answers_cache.h"
#include "components/omnibox/base_search_provider.h"
#include "components/search_engines/template_url.h"
#include "net/url_request/url_fetcher_delegate.h"

class AutocompleteProviderClient;
class AutocompleteProviderListener;
class AutocompleteResult;
class SearchProviderTest;
class TemplateURLService;

namespace history {
struct KeywordSearchTermVisit;
}

namespace net {
class URLFetcher;
}

class SearchProvider : public BaseSearchProvider,
                       public net::URLFetcherDelegate {
 public:
  SearchProvider(AutocompleteProviderListener* listener,
                 TemplateURLService* template_url_service,
                 scoped_ptr<AutocompleteProviderClient> client);

  
  
  static std::string GetSuggestMetadata(const AutocompleteMatch& match);

  
  
  void RegisterDisplayedAnswers(const AutocompleteResult& result);

  
  virtual void ResetSession() OVERRIDE;

  
  void set_current_page_url(const GURL& current_page_url) {
    current_page_url_ = current_page_url;
  }

 protected:
  virtual ~SearchProvider();

 private:
  friend class SearchProviderTest;
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, CanSendURL);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest,
                           DontInlineAutocompleteAsynchronously);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, NavigationInline);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, NavigationInlineDomainClassify);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, NavigationInlineSchemeSubstring);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, SuggestRelevanceExperiment);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, TestDeleteMatch);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, SuggestQueryUsesToken);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, SessionToken);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, AnswersCache);
  FRIEND_TEST_ALL_PREFIXES(SearchProviderTest, RemoveExtraAnswers);
  FRIEND_TEST_ALL_PREFIXES(AutocompleteProviderTest, GetDestinationURL);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedPrefetchTest, ClearPrefetchedResults);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedPrefetchTest, SetPrefetchQuery);

  
  
  
  
  
  
  class Providers {
   public:
    explicit Providers(TemplateURLService* template_url_service);

    
    
    bool equal(const base::string16& default_provider,
               const base::string16& keyword_provider) const {
      return (default_provider == default_provider_) &&
          (keyword_provider == keyword_provider_);
    }

    
    void set(const base::string16& default_provider,
             const base::string16& keyword_provider) {
      default_provider_ = default_provider;
      keyword_provider_ = keyword_provider;
    }

    TemplateURLService* template_url_service() { return template_url_service_; }
    const base::string16& default_provider() const { return default_provider_; }
    const base::string16& keyword_provider() const { return keyword_provider_; }

    
    const TemplateURL* GetDefaultProviderURL() const;
    const TemplateURL* GetKeywordProviderURL() const;

    
    bool has_keyword_provider() const { return !keyword_provider_.empty(); }

   private:
    TemplateURLService* template_url_service_;

    
    
    base::string16 default_provider_;
    base::string16 keyword_provider_;

    DISALLOW_COPY_AND_ASSIGN(Providers);
  };

  class CompareScoredResults;

  typedef std::vector<history::KeywordSearchTermVisit> HistoryResults;

  
  
  static int CalculateRelevanceForKeywordVerbatim(
      metrics::OmniboxInputType::Type type,
      bool prefer_keyword);

  
  static void UpdateOldResults(bool minimal_changes,
                               SearchSuggestionParser::Results* results);

  
  static ACMatches::iterator FindTopMatch(ACMatches* matches);

  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;
  virtual void Stop(bool clear_cached_results) OVERRIDE;

  
  virtual const TemplateURL* GetTemplateURL(bool is_keyword) const OVERRIDE;
  virtual const AutocompleteInput GetInput(bool is_keyword) const OVERRIDE;
  virtual bool ShouldAppendExtraParams(
      const SearchSuggestionParser::SuggestResult& result) const OVERRIDE;
  virtual void RecordDeletionResult(bool success) OVERRIDE;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  
  void StopSuggest();

  
  void ClearAllResults();

  
  
  void UpdateMatchContentsClass(const base::string16& input_text,
                                SearchSuggestionParser::Results* results);

  
  void SortResults(bool is_keyword, SearchSuggestionParser::Results* results);

  
  void LogFetchComplete(bool success, bool is_keyword);

  
  
  void UpdateMatches();

  
  void Run();

  
  
  void DoHistoryQuery(bool minimal_changes);

  
  
  
  void StartOrStopSuggestQuery(bool minimal_changes);

  
  
  
  bool IsQuerySuitableForSuggest() const;

  
  
  
  void UpdateAllOldResults(bool minimal_changes);

  
  
  void PersistTopSuggestions(SearchSuggestionParser::Results* results);

  
  void ApplyCalculatedSuggestRelevance(
      SearchSuggestionParser::SuggestResults* list);
  void ApplyCalculatedNavigationRelevance(
      SearchSuggestionParser::NavigationResults* list);

  
  
  net::URLFetcher* CreateSuggestFetcher(int id,
                                        const TemplateURL* template_url,
                                        const AutocompleteInput& input);

  
  void ConvertResultsToAutocompleteMatches();

  
  
  static void RemoveExtraAnswers(ACMatches* matches);

  
  
  ACMatches::const_iterator FindTopMatch() const;

  
  
  
  bool IsTopMatchSearchWithURLInput() const;

  
  
  void AddNavigationResultsToMatches(
      const SearchSuggestionParser::NavigationResults& navigation_results,
      ACMatches* matches);

  
  
  
  void AddRawHistoryResultsToMap(bool is_keyword,
                                 int did_not_accept_suggestion,
                                 MatchMap* map);

  
  void AddTransformedHistoryResultsToMap(
      const SearchSuggestionParser::SuggestResults& results,
      int did_not_accept_suggestion,
      MatchMap* map);

  
  SearchSuggestionParser::SuggestResults ScoreHistoryResultsHelper(
      const HistoryResults& results,
      bool base_prevent_inline_autocomplete,
      bool input_multiple_words,
      const base::string16& input_text,
      bool is_keyword);

  
  
  
  void ScoreHistoryResults(
      const HistoryResults& results,
      bool is_keyword,
      SearchSuggestionParser::SuggestResults* scored_results);

  
  void AddSuggestResultsToMap(
      const SearchSuggestionParser::SuggestResults& results,
      const std::string& metadata,
      MatchMap* map);

  
  
  
  
  int GetVerbatimRelevance(bool* relevance_from_server) const;

  
  
  
  int CalculateRelevanceForVerbatim() const;

  
  
  
  
  
  int CalculateRelevanceForVerbatimIgnoringKeywordModeState() const;

  
  
  
  
  
  int GetKeywordVerbatimRelevance(bool* relevance_from_server) const;

  
  
  
  
  
  
  int CalculateRelevanceForHistory(const base::Time& time,
                                   bool is_keyword,
                                   bool use_aggressive_method,
                                   bool prevent_search_history_inlining) const;

  
  AutocompleteMatch NavigationToMatch(
      const SearchSuggestionParser::NavigationResult& navigation);

  
  void UpdateDone();

  
  std::string GetSessionToken();

  
  
  
  
  AnswersQueryData FindAnswersPrefetchData();

  
  
  static int kMinimumTimeBetweenSuggestQueriesMs;

  AutocompleteProviderListener* listener_;

  
  
  int suggest_results_pending_;

  
  Providers providers_;

  
  AutocompleteInput input_;

  
  AutocompleteInput keyword_input_;

  
  HistoryResults raw_keyword_history_results_;
  HistoryResults raw_default_history_results_;

  
  
  SearchSuggestionParser::SuggestResults transformed_keyword_history_results_;
  SearchSuggestionParser::SuggestResults transformed_default_history_results_;

  
  
  base::OneShotTimer<SearchProvider> timer_;

  
  base::TimeTicks time_suggest_request_sent_;

  
  scoped_ptr<net::URLFetcher> keyword_fetcher_;
  scoped_ptr<net::URLFetcher> default_fetcher_;

  
  SearchSuggestionParser::Results default_results_;
  SearchSuggestionParser::Results keyword_results_;

  
  base::string16 top_query_suggestion_match_contents_;
  
  GURL top_navigation_suggestion_;

  GURL current_page_url_;

  
  std::string current_token_;
  base::TimeTicks token_expiration_time_;

  
  AnswersCache answers_cache_;  
  AnswersQueryData prefetch_data_;  

  DISALLOW_COPY_AND_ASSIGN(SearchProvider);
};

#endif  
