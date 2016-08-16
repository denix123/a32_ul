// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_CLIENT_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_CLIENT_H_

#include "base/strings/string16.h"
#include "components/history/core/browser/keyword_id.h"
#include "components/metrics/proto/omnibox_event.pb.h"

struct AutocompleteMatch;
class AutocompleteSchemeClassifier;
class GURL;

namespace history {
class URLDatabase;
}

namespace net {
class URLRequestContextGetter;
}

class AutocompleteProviderClient {
 public:
  virtual ~AutocompleteProviderClient() {}

  
  virtual net::URLRequestContextGetter* RequestContext() = 0;

  
  virtual bool IsOffTheRecord() = 0;

  
  
  virtual std::string AcceptLanguages() = 0;

  
  virtual bool SearchSuggestEnabled() = 0;

  
  virtual bool ShowBookmarkBar() = 0;

  
  virtual const AutocompleteSchemeClassifier& SchemeClassifier() = 0;

  
  
  virtual void Classify(
      const base::string16& text,
      bool prefer_keyword,
      bool allow_exact_keyword_match,
      metrics::OmniboxEventProto::PageClassification page_classification,
      AutocompleteMatch* match,
      GURL* alternate_nav_url) = 0;

  
  virtual history::URLDatabase* InMemoryDatabase() = 0;

  
  
  virtual void DeleteMatchingURLsForKeywordFromHistory(
      history::KeywordID keyword_id,
      const base::string16& term) = 0;

  
  virtual bool TabSyncEnabledAndUnencrypted() = 0;

  
  virtual void PrefetchImage(const GURL& url) = 0;
};

#endif  
