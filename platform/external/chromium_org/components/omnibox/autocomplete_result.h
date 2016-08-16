// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_RESULT_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_RESULT_H_

#include <stddef.h>

#include <map>

#include "base/basictypes.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/autocomplete_match.h"
#include "url/gurl.h"

class AutocompleteInput;
class AutocompleteProvider;
class TemplateURLService;

class AutocompleteResult {
 public:
  typedef ACMatches::const_iterator const_iterator;
  typedef ACMatches::iterator iterator;

  
  
  struct Selection {
    Selection()
        : provider_affinity(NULL),
          is_history_what_you_typed_match(false) {
    }

    
    void Clear();

    
    bool empty() const {
      return destination_url.is_empty() && !provider_affinity &&
          !is_history_what_you_typed_match;
    }

    
    GURL destination_url;

    
    
    const AutocompleteProvider* provider_affinity;

    
    
    
    
    bool is_history_what_you_typed_match;
  };

  
  static const size_t kMaxMatches;

  AutocompleteResult();
  ~AutocompleteResult();

  
  
  void CopyOldMatches(const AutocompleteInput& input,
                      const AutocompleteResult& old_matches,
                      TemplateURLService* template_url_service);

  
  void AppendMatches(const ACMatches& matches);

  
  
  
  void SortAndCull(const AutocompleteInput& input,
                   TemplateURLService* template_url_service);

  
  bool HasCopiedMatches() const;

  
  size_t size() const;
  bool empty() const;
  const_iterator begin() const;
  iterator begin();
  const_iterator end() const;
  iterator end();

  
  const AutocompleteMatch& match_at(size_t index) const;
  AutocompleteMatch* match_at(size_t index);

  
  
  const_iterator default_match() const { return default_match_; }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool ShouldHideTopMatch() const;

  
  
  
  bool TopMatchIsStandaloneVerbatimMatch() const;

  const GURL& alternate_nav_url() const { return alternate_nav_url_; }

  
  void Reset();

  void Swap(AutocompleteResult* other);

#ifndef NDEBUG
  
  void Validate() const;
#endif

  
  
  
  static GURL ComputeAlternateNavUrl(const AutocompleteInput& input,
                                     const AutocompleteMatch& match);

  
  
  
  
  
  static void DedupMatchesByDestination(
      metrics::OmniboxEventProto::PageClassification page_classification,
      bool set_duplicate_matches,
      ACMatches* matches);

 private:
  friend class AutocompleteProviderTest;

  typedef std::map<AutocompleteProvider*, ACMatches> ProviderToMatches;

#if defined(OS_ANDROID)
  
  
  typedef int matches_difference_type;
#else
  typedef ACMatches::iterator::difference_type matches_difference_type;
#endif

  
  
  static bool HasMatchByDestination(const AutocompleteMatch& match,
                                    const ACMatches& matches);

  
  void CopyFrom(const AutocompleteResult& rhs);

  
  void BuildProviderToMatches(ProviderToMatches* provider_to_matches) const;

  
  
  void MergeMatchesByProvider(
      metrics::OmniboxEventProto::PageClassification page_classification,
      const ACMatches& old_matches,
      const ACMatches& new_matches);

  ACMatches matches_;

  const_iterator default_match_;

  
  
  
  
  
  
  
  GURL alternate_nav_url_;

  DISALLOW_COPY_AND_ASSIGN(AutocompleteResult);
};

#endif  
