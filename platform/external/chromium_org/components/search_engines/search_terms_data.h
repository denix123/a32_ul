// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_SEARCH_TERMS_DATA_H_
#define COMPONENTS_SEARCH_ENGINES_SEARCH_TERMS_DATA_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"

class SearchTermsData {
 public:
  SearchTermsData();
  virtual ~SearchTermsData();

  
  
  virtual std::string GoogleBaseURLValue() const;

  
  
  std::string GoogleBaseSuggestURLValue() const;

  
  
  virtual std::string GetApplicationLocale() const;

  
  
  virtual base::string16 GetRlzParameterValue(bool from_app_list) const;

  
  
  virtual std::string GetSearchClient() const;

  
  
  
  virtual std::string GetSuggestClient() const;

  
  
  
  
  virtual std::string GetSuggestRequestIdentifier() const;

  
  virtual bool EnableAnswersInSuggest() const;

  
  
  virtual bool IsShowingSearchTermsOnSearchResultsPages() const;

  
  virtual std::string InstantExtendedEnabledParam(bool for_search) const;

  
  
  virtual std::string ForceInstantResultsParam(bool for_prerender) const;

  
  virtual int OmniboxStartMargin() const;

  
  
  
  
  
  virtual std::string NTPIsThemedParam() const;

  
  
  virtual std::string GoogleImageSearchSource() const;

 private:
  DISALLOW_COPY_AND_ASSIGN(SearchTermsData);
};

#endif  
