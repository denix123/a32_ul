// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_MATCH_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_MATCH_H_

#include <deque>

#include "components/history/core/browser/url_row.h"

namespace history {

struct HistoryMatch {
  
  HistoryMatch();

  HistoryMatch(const URLRow& url_info,
               size_t input_location,
               bool match_in_scheme,
               bool innermost_match);

  static bool EqualsGURL(const HistoryMatch& h, const GURL& url);

  
  
  
  bool IsHostOnly() const;

  URLRow url_info;

  
  size_t input_location;

  
  
  
  
  
  
  
  
  bool match_in_scheme;

  
  
  
  
  
  bool innermost_match;
};
typedef std::deque<HistoryMatch> HistoryMatches;

}  

#endif  
