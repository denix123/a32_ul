// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_MATCH_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_MATCH_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "components/omnibox/autocomplete_match_type.h"
#include "components/search_engines/template_url.h"
#include "ui/base/page_transition_types.h"
#include "url/gurl.h"

class AutocompleteProvider;
class TemplateURL;
class TemplateURLService;

namespace base {
class Time;
}  

const char kACMatchPropertyInputText[] = "input text";
const char kACMatchPropertyContentsPrefix[] = "match contents prefix";
const char kACMatchPropertyContentsStartIndex[] = "match contents start index";


struct AutocompleteMatch {
  
  
  
  
  
  
  
  
  
  
  
  
  
  struct ACMatchClassification {
    
    
    
    enum Style {
      NONE  = 0,
      URL   = 1 << 0,  
      MATCH = 1 << 1,  
      DIM   = 1 << 2,  
    };

    ACMatchClassification(size_t offset, int style)
        : offset(offset),
          style(style) {
    }

    
    size_t offset;

    int style;
  };

  typedef std::vector<ACMatchClassification> ACMatchClassifications;

  
  
  typedef std::map<std::string, std::string> AdditionalInfo;

  
  typedef AutocompleteMatchType::Type Type;

  
  
  static const base::char16 kInvalidChars[];

  AutocompleteMatch();
  AutocompleteMatch(AutocompleteProvider* provider,
                    int relevance,
                    bool deletable,
                    Type type);
  AutocompleteMatch(const AutocompleteMatch& match);
  ~AutocompleteMatch();

  
  AutocompleteMatch& operator=(const AutocompleteMatch& match);

  
  
  static int TypeToIcon(Type type);

  
  static bool MoreRelevant(const AutocompleteMatch& elem1,
                           const AutocompleteMatch& elem2);

  
  
  
  
  static bool DestinationsEqual(const AutocompleteMatch& elem1,
                                const AutocompleteMatch& elem2);

  
  
  
  
  static void ClassifyMatchInString(const base::string16& find_text,
                                    const base::string16& text,
                                    int style,
                                    ACMatchClassifications* classifications);

  
  
  
  
  static void ClassifyLocationInString(size_t match_location,
                                       size_t match_length,
                                       size_t overall_length,
                                       int style,
                                       ACMatchClassifications* classifications);

  
  
  static ACMatchClassifications MergeClassifications(
      const ACMatchClassifications& classifications1,
      const ACMatchClassifications& classifications2);

  
  
  static std::string ClassificationsToString(
      const ACMatchClassifications& classifications);
  static ACMatchClassifications ClassificationsFromString(
      const std::string& serialized_classifications);

  
  
  
  static void AddLastClassificationIfNecessary(
      ACMatchClassifications* classifications,
      size_t offset,
      int style);

  
  
  
  static base::string16 SanitizeString(const base::string16& text);

  
  
  static bool IsSearchType(Type type);

  
  
  static bool IsSpecializedSearchType(Type type);

  
  
  
  
  static TemplateURL* GetTemplateURLWithKeyword(
      TemplateURLService* template_url_service,
      const base::string16& keyword,
      const std::string& host);

  
  
  
  
  
  
  
  
  
  
  static GURL GURLToStrippedGURL(const GURL& url,
                                 TemplateURLService* template_url_service,
                                 const base::string16& keyword);

  
  
  void ComputeStrippedDestinationURL(TemplateURLService* template_url_service);

  
  
  
  
  
  void EnsureUWYTIsAllowedToBeDefault(const GURL& canonical_input_url,
                                      TemplateURLService* template_url_service);

  
  
  
  
  
  
  
  
  
  
  
  
  void GetKeywordUIState(TemplateURLService* template_url_service,
                         base::string16* keyword,
                         bool* is_keyword_hint) const;

  
  
  
  
  
  
  base::string16 GetSubstitutingExplicitlyInvokedKeyword(
      TemplateURLService* template_url_service) const;

  
  
  
  
  
  
  TemplateURL* GetTemplateURL(TemplateURLService* template_url_service,
                              bool allow_fallback_to_destination_host) const;

  
  void RecordAdditionalInfo(const std::string& property,
                            const std::string& value);
  void RecordAdditionalInfo(const std::string& property, int value);
  void RecordAdditionalInfo(const std::string& property,
                            const base::Time& value);

  
  
  std::string GetAdditionalInfo(const std::string& property) const;

  
  
  
  
  
  
  
  
  bool IsVerbatimType() const;

  
  
  bool SupportsDeletion() const;

  
  
  
  AutocompleteProvider* provider;

  
  
  
  
  
  
  
  int relevance;

  
  
  
  
  int typed_count;

  
  bool deletable;

  
  
  
  base::string16 fill_into_edit;

  
  
  base::string16 inline_autocompletion;

  
  
  
  
  
  
  
  
  
  bool allowed_to_be_default_match;

  
  
  
  GURL destination_url;

  
  GURL stripped_destination_url;

  
  base::string16 contents;
  ACMatchClassifications contents_class;

  
  base::string16 description;
  ACMatchClassifications description_class;

  
  base::string16 answer_contents;
  base::string16 answer_type;

  
  
  
  ui::PageTransition transition;

  
  
  bool is_history_what_you_typed_match;

  
  Type type;

  
  
  
  scoped_ptr<AutocompleteMatch> associated_keyword;

  
  
  
  
  
  
  
  
  
  
  
  base::string16 keyword;

  
  bool from_previous;

  
  
  
  
  
  
  
  scoped_ptr<TemplateURLRef::SearchTermsArgs> search_terms_args;

  
  
  AdditionalInfo additional_info;

  
  
  std::vector<AutocompleteMatch> duplicate_matches;

#ifndef NDEBUG
  
  void Validate() const;

  
  void ValidateClassifications(
      const base::string16& text,
      const ACMatchClassifications& classifications) const;
#endif
};

typedef AutocompleteMatch::ACMatchClassification ACMatchClassification;
typedef std::vector<ACMatchClassification> ACMatchClassifications;
typedef std::vector<AutocompleteMatch> ACMatches;

#endif  
