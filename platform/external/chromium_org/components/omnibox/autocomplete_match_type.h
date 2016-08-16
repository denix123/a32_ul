// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_MATCH_TYPE_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_MATCH_TYPE_H_

#include <string>

struct AutocompleteMatchType {
  
  
  
  
  
  enum Type {
    URL_WHAT_YOU_TYPED    = 0,  
    HISTORY_URL           = 1,  
    HISTORY_TITLE         = 2,  
    HISTORY_BODY          = 3,  
    HISTORY_KEYWORD       = 4,  
                                
    NAVSUGGEST            = 5,  
    SEARCH_WHAT_YOU_TYPED = 6,  
                                
    SEARCH_HISTORY        = 7,  
                                
    SEARCH_SUGGEST        = 8,  
                                
                                
    SEARCH_SUGGEST_ENTITY = 9,  
    SEARCH_SUGGEST_INFINITE     = 10,  
                                       
    SEARCH_SUGGEST_PERSONALIZED = 11,  
    SEARCH_SUGGEST_PROFILE      = 12,  
                                       
    SEARCH_OTHER_ENGINE         = 13,  
    EXTENSION_APP               = 14,  
                                       
    CONTACT_DEPRECATED          = 15,  
                                       
    BOOKMARK_TITLE              = 16,  
                                       
    NAVSUGGEST_PERSONALIZED     = 17,  
    SEARCH_SUGGEST_ANSWER       = 18,  
    NUM_TYPES,
  };

  
  static std::string ToString(AutocompleteMatchType::Type type);
};

#endif  
