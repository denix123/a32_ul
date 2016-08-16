// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_KEYWORD_PROVIDER_H_
#define COMPONENTS_OMNIBOX_KEYWORD_PROVIDER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "components/metrics/proto/omnibox_input_type.pb.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_provider.h"
#include "components/omnibox/keyword_extensions_delegate.h"

class AutocompleteProviderListener;
class KeywordExtensionsDelegate;
class TemplateURL;
class TemplateURLService;

class KeywordProvider : public AutocompleteProvider {
 public:
  KeywordProvider(AutocompleteProviderListener* listener,
                  TemplateURLService* model);

  void set_extensions_delegate(
      scoped_ptr<KeywordExtensionsDelegate> extensions_delegate) {
    extensions_delegate_ = extensions_delegate.Pass();
  }

  
  
  
  
  
  static base::string16 SplitKeywordFromInput(const base::string16& input,
                                              bool trim_leading_whitespace,
                                              base::string16* remaining_input);

  
  
  
  
  
  static base::string16 SplitReplacementStringFromInput(
      const base::string16& input,
      bool trim_leading_whitespace);

  
  
  
  static const TemplateURL* GetSubstitutingTemplateURLForInput(
      TemplateURLService* model,
      AutocompleteInput* input);

  
  
  
  base::string16 GetKeywordForText(const base::string16& text) const;

  
  AutocompleteMatch CreateVerbatimMatch(const base::string16& text,
                                        const base::string16& keyword,
                                        const AutocompleteInput& input);

  
  virtual void Start(const AutocompleteInput& input,
                     bool minimal_changes) OVERRIDE;
  virtual void Stop(bool clear_cached_results) OVERRIDE;

 private:
  friend class KeywordExtensionsDelegateImpl;

  virtual ~KeywordProvider();

  
  
  
  
  
  
  
  static bool ExtractKeywordFromInput(const AutocompleteInput& input,
                                      base::string16* keyword,
                                      base::string16* remaining_input);

  
  
  
  
  
  static int CalculateRelevance(metrics::OmniboxInputType::Type type,
                                bool complete,
                                bool support_replacement,
                                bool prefer_keyword,
                                bool allow_exact_keyword_match);

  
  
  AutocompleteMatch CreateAutocompleteMatch(
      const TemplateURL* template_url,
      const AutocompleteInput& input,
      size_t prefix_length,
      const base::string16& remaining_input,
      bool allowed_to_be_default_match,
      int relevance);

  
  
  void FillInURLAndContents(const base::string16& remaining_input,
                            const TemplateURL* element,
                            AutocompleteMatch* match) const;

  TemplateURLService* GetTemplateURLService() const;

  AutocompleteProviderListener* listener_;

  
  TemplateURLService* model_;

  
  
  scoped_ptr<KeywordExtensionsDelegate> extensions_delegate_;

  DISALLOW_COPY_AND_ASSIGN(KeywordProvider);
};

#endif  
