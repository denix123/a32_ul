// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_HISTORY_URL_PROVIDER_H_
#define CHROME_BROWSER_AUTOCOMPLETE_HISTORY_URL_PROVIDER_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/synchronization/cancellation_flag.h"
#include "chrome/browser/autocomplete/history_provider.h"
#include "components/history/core/browser/history_match.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/omnibox_field_trial.h"
#include "components/search_engines/template_url.h"

class AutocompleteProviderListener;
class Profile;
class SearchTermsData;

namespace base {
class MessageLoop;
}

namespace history {
class HistoryBackend;
class URLDatabase;
}


struct HistoryURLProviderParams {
  
  enum PromoteType {
    WHAT_YOU_TYPED_MATCH,
    FRONT_HISTORY_MATCH,
    NEITHER,
  };

  HistoryURLProviderParams(const AutocompleteInput& input,
                           bool trim_http,
                           const AutocompleteMatch& what_you_typed_match,
                           const std::string& languages,
                           TemplateURL* default_search_provider,
                           const SearchTermsData& search_terms_data);
  ~HistoryURLProviderParams();

  base::MessageLoop* message_loop;

  
  
  AutocompleteInput input;

  
  
  
  bool prevent_inline_autocomplete;

  
  bool trim_http;

  
  AutocompleteMatch what_you_typed_match;

  
  
  
  
  base::CancellationFlag cancel_flag;

  
  
  
  
  bool failed;

  // List of matches written by DoAutocomplete().  Upon its return the provider
  
  history::HistoryMatches matches;

  
  
  
  
  
  
  
  
  bool exact_suggestion_is_in_history;

  
  
  
  
  
  
  
  
  PromoteType promote_type;

  
  
  
  bool have_what_you_typed_match;

  
  std::string languages;

  
  
  
  
  
  
  
  scoped_ptr<TemplateURL> default_search_provider;
  scoped_ptr<SearchTermsData> search_terms_data;

 private:
  DISALLOW_COPY_AND_ASSIGN(HistoryURLProviderParams);
};

class HistoryURLProvider : public HistoryProvider {
 public:
  
  
  static const int kScoreForBestInlineableResult;
  static const int kScoreForUnvisitedIntranetResult;
  static const int kScoreForWhatYouTypedResult;
  static const int kBaseScoreForNonInlineableResult;

  HistoryURLProvider(AutocompleteProviderListener* listener, Profile* profile);

  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;
  virtual void Stop(bool clear_cached_results) OVERRIDE;

  
  
  
  
  
  
  
  AutocompleteMatch SuggestExactInput(const base::string16& text,
                                      const GURL& destination_url,
                                      bool trim_http);

  
  
  
  
  void ExecuteWithDB(HistoryURLProviderParams* params,
                     history::HistoryBackend* backend,
                     history::URLDatabase* db);

 private:
  FRIEND_TEST_ALL_PREFIXES(HistoryURLProviderTest, HUPScoringExperiment);

  enum MatchType {
    NORMAL,
    WHAT_YOU_TYPED,
    INLINE_AUTOCOMPLETE,
    UNVISITED_INTRANET,  
  };
  class VisitClassifier;

  ~HistoryURLProvider();

  
  
  
  
  
  static int CalculateRelevance(MatchType match_type, int match_number);

  
  
  static ACMatchClassifications ClassifyDescription(
      const base::string16& input_text,
      const base::string16& description);

  
  
  
  void DoAutocomplete(history::HistoryBackend* backend,
                      history::URLDatabase* db,
                      HistoryURLProviderParams* params);

  
  
  
  void PromoteMatchesIfNecessary(const HistoryURLProviderParams& params);

  
  
  
  void QueryComplete(HistoryURLProviderParams* params_gets_deleted);

  
  
  
  
  
  bool FixupExactSuggestion(history::URLDatabase* db,
                            const VisitClassifier& classifier,
                            HistoryURLProviderParams* params) const;

  
  
  
  bool CanFindIntranetURL(history::URLDatabase* db,
                          const AutocompleteInput& input) const;

  
  
  
  
  
  
  
  
  bool PromoteOrCreateShorterSuggestion(
      history::URLDatabase* db,
      bool have_what_you_typed_match,
      HistoryURLProviderParams* params);

  
  
  
  
  
  
  void CullPoorMatches(HistoryURLProviderParams* params) const;

  
  
  void CullRedirects(history::HistoryBackend* backend,
                     history::HistoryMatches* matches,
                     size_t max_results) const;

  
  
  
  
  
  
  
  
  size_t RemoveSubsequentMatchesOf(history::HistoryMatches* matches,
                                   size_t source_index,
                                   const std::vector<GURL>& remove) const;

  
  
  
  
  AutocompleteMatch HistoryMatchToACMatch(
      const HistoryURLProviderParams& params,
      size_t match_number,
      MatchType match_type,
      int relevance);

  AutocompleteProviderListener* listener_;

  
  
  
  
  HistoryURLProviderParams* params_;

  
  HUPScoringParams scoring_params_;

  DISALLOW_COPY_AND_ASSIGN(HistoryURLProvider);
};

#endif  
