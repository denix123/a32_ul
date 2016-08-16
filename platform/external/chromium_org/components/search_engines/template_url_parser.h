// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PARSER_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PARSER_H_

#include <string>

#include "base/basictypes.h"

class SearchTermsData;
class TemplateURL;

class TemplateURLParser {
 public:
  class ParameterFilter {
   public:
    
    
    virtual bool KeepParameter(const std::string& key,
                               const std::string& value) = 0;

   protected:
    virtual ~ParameterFilter() {}
  };

  
  
  
  
  
  
  
  
  
  static TemplateURL* Parse(const SearchTermsData& search_terms_data,
                            bool show_in_default_list,
                            const char* data,
                            size_t length,
                            ParameterFilter* parameter_filter);

 private:
  
  TemplateURLParser();

  DISALLOW_COPY_AND_ASSIGN(TemplateURLParser);
};

#endif  
