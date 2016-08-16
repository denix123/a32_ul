// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_BOOKMARK_PROVIDER_H_
#define CHROME_BROWSER_AUTOCOMPLETE_BOOKMARK_PROVIDER_H_

#include <string>

#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_match.h"
#include "components/omnibox/autocomplete_provider.h"
#include "components/query_parser/snippet.h"

class BookmarkModel;
class Profile;

namespace bookmarks {
struct BookmarkMatch;
}

class BookmarkProvider : public AutocompleteProvider {
 public:
  explicit BookmarkProvider(Profile* profile);

  
  
  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;

  
  void set_bookmark_model_for_testing(BookmarkModel* bookmark_model) {
    bookmark_model_ = bookmark_model;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(BookmarkProviderTest, InlineAutocompletion);

  virtual ~BookmarkProvider();

  
  
  void DoAutocomplete(const AutocompleteInput& input);

  
  
  
  
  
  AutocompleteMatch BookmarkMatchToACMatch(
      const AutocompleteInput& input,
      const base::string16& fixed_up_input_text,
      const bookmarks::BookmarkMatch& match);

  
  
  
  
  static ACMatchClassifications ClassificationsFromMatch(
      const query_parser::Snippet::MatchPositions& positions,
      size_t text_length,
      bool is_url);

  Profile* profile_;
  BookmarkModel* bookmark_model_;

  
  std::string languages_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkProvider);
};

#endif  
