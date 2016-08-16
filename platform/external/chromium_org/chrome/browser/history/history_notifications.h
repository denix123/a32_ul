// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_HISTORY_HISTORY_NOTIFICATIONS_H__
#define CHROME_BROWSER_HISTORY_HISTORY_NOTIFICATIONS_H__

#include <set>

#include "chrome/browser/history/history_details.h"
#include "components/history/core/browser/history_types.h"
#include "components/history/core/browser/keyword_id.h"
#include "url/gurl.h"

namespace history {

struct URLVisitedDetails : public HistoryDetails {
  URLVisitedDetails();
  virtual ~URLVisitedDetails();

  ui::PageTransition transition;

  
  
  URLRow row;

  
  
  
  
  history::RedirectList redirects;

  base::Time visit_time;
};

struct URLsModifiedDetails : public HistoryDetails {
  URLsModifiedDetails();
  virtual ~URLsModifiedDetails();

  
  
  URLRows changed_urls;
};

struct URLsDeletedDetails : public HistoryDetails {
  URLsDeletedDetails();
  virtual ~URLsDeletedDetails();

  
  bool all_history;

  
  
  bool expired;

  
  
  
  
  URLRows rows;

  
  
  std::set<GURL> favicon_urls;
};

struct KeywordSearchUpdatedDetails : public HistoryDetails {
  KeywordSearchUpdatedDetails(const URLRow& url_row,
                              KeywordID keyword_id,
                              const base::string16& term);
  virtual ~KeywordSearchUpdatedDetails();

  
  
  URLRow url_row;
  KeywordID keyword_id;
  base::string16 term;
};

struct KeywordSearchDeletedDetails : public HistoryDetails {
  explicit KeywordSearchDeletedDetails(URLID url_row_id);
  virtual ~KeywordSearchDeletedDetails();

  
  URLID url_row_id;
};

}  

#endif  
