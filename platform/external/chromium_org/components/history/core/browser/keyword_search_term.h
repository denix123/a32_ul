// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_KEYWORD_SEARCH_TERM_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_KEYWORD_SEARCH_TERM_H_

#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/history/core/browser/keyword_id.h"
#include "components/history/core/browser/url_row.h"

namespace history {

struct KeywordSearchTermVisit {
  KeywordSearchTermVisit();
  ~KeywordSearchTermVisit();

  base::string16 term;  
  int visits;  
  base::Time time;  
};

struct KeywordSearchTermRow {
  KeywordSearchTermRow();
  ~KeywordSearchTermRow();

  KeywordID keyword_id;  
  URLID url_id;  
  base::string16 term;  
};

}  

#endif  
