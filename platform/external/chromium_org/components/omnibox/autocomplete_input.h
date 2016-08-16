// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_INPUT_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_INPUT_H_

#include <string>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/metrics/proto/omnibox_input_type.pb.h"
#include "url/gurl.h"
#include "url/url_parse.h"

class AutocompleteSchemeClassifier;

class AutocompleteInput {
 public:
  AutocompleteInput();
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  AutocompleteInput(const base::string16& text,
                    size_t cursor_position,
                    const base::string16& desired_tld,
                    const GURL& current_url,
                    metrics::OmniboxEventProto::PageClassification
                        current_page_classification,
                    bool prevent_inline_autocomplete,
                    bool prefer_keyword,
                    bool allow_exact_keyword_match,
                    bool want_asynchronous_matches,
                    const AutocompleteSchemeClassifier& scheme_classifier);
  ~AutocompleteInput();

  
  
  static size_t RemoveForcedQueryStringIfNecessary(
      metrics::OmniboxInputType::Type type,
      base::string16* text);

  
  static std::string TypeToString(metrics::OmniboxInputType::Type type);

  
  
  
  
  
  
  
  static metrics::OmniboxInputType::Type Parse(
      const base::string16& text,
      const base::string16& desired_tld,
      const AutocompleteSchemeClassifier& scheme_classifier,
      url::Parsed* parts,
      base::string16* scheme,
      GURL* canonicalized_url);

  
  
  
  
  static void ParseForEmphasizeComponents(
      const base::string16& text,
      const AutocompleteSchemeClassifier& scheme_classifier,
      url::Component* scheme,
      url::Component* host);

  
  
  
  
  
  
  
  
  static base::string16 FormattedStringWithEquivalentMeaning(
      const GURL& url,
      const base::string16& formatted_url,
      const AutocompleteSchemeClassifier& scheme_classifier);

  
  static int NumNonHostComponents(const url::Parsed& parts);

  
  static bool HasHTTPScheme(const base::string16& text);

  
  const base::string16& text() const { return text_; }

  
  
  size_t cursor_position() const { return cursor_position_; }

  
  
  
  void UpdateText(const base::string16& text,
                  size_t cursor_position,
                  const url::Parsed& parts);

  
  const GURL& current_url() const { return current_url_; }

  
  
  metrics::OmniboxEventProto::PageClassification current_page_classification()
      const {
    return current_page_classification_;
  }

  
  metrics::OmniboxInputType::Type type() const { return type_; }

  
  const url::Parsed& parts() const { return parts_; }

  
  
  const base::string16& scheme() const { return scheme_; }

  
  const GURL& canonicalized_url() const { return canonicalized_url_; }

  
  bool prevent_inline_autocomplete() const {
    return prevent_inline_autocomplete_;
  }

  
  
  bool prefer_keyword() const { return prefer_keyword_; }

  
  
  
  bool allow_exact_keyword_match() const { return allow_exact_keyword_match_; }

  
  
  bool want_asynchronous_matches() const { return want_asynchronous_matches_; }

  
  void Clear();

 private:
  FRIEND_TEST_ALL_PREFIXES(AutocompleteProviderTest, GetDestinationURL);

  
  
  base::string16 text_;
  size_t cursor_position_;
  GURL current_url_;
  metrics::OmniboxEventProto::PageClassification current_page_classification_;
  metrics::OmniboxInputType::Type type_;
  url::Parsed parts_;
  base::string16 scheme_;
  GURL canonicalized_url_;
  bool prevent_inline_autocomplete_;
  bool prefer_keyword_;
  bool allow_exact_keyword_match_;
  bool want_asynchronous_matches_;
};

#endif  
