// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_HISTORY_QUICK_PROVIDER_H_
#define CHROME_BROWSER_AUTOCOMPLETE_HISTORY_QUICK_PROVIDER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/autocomplete/history_provider.h"
#include "chrome/browser/history/in_memory_url_index.h"
#include "components/history/core/browser/history_types.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_match.h"

class Profile;

namespace history {
class ScoredHistoryMatch;
}  

class HistoryQuickProvider : public HistoryProvider {
 public:
  explicit HistoryQuickProvider(Profile* profile);

  
  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;

  
  
  
  
  
  static void set_disabled(bool disabled) { disabled_ = disabled; }

 private:
  friend class HistoryQuickProviderTest;
  FRIEND_TEST_ALL_PREFIXES(HistoryQuickProviderTest, Spans);
  FRIEND_TEST_ALL_PREFIXES(HistoryQuickProviderTest, Relevance);

  virtual ~HistoryQuickProvider();

  
  void DoAutocomplete();

  
  
  AutocompleteMatch QuickMatchToACMatch(
      const history::ScoredHistoryMatch& history_match,
      int score);

  
  history::InMemoryURLIndex* GetIndex();

  
  void set_index(history::InMemoryURLIndex* index) {
    index_for_testing_.reset(index);
  }

  AutocompleteInput autocomplete_input_;
  std::string languages_;

  
  scoped_ptr<history::InMemoryURLIndex> index_for_testing_;

  
  static bool disabled_;

  DISALLOW_COPY_AND_ASSIGN(HistoryQuickProvider);
};

#endif  
