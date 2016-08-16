// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_URL_ROW_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_URL_ROW_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/query_parser/snippet.h"
#include "url/gurl.h"

namespace history {

typedef int64 URLID;

class URLRow {
 public:
  URLRow();

  explicit URLRow(const GURL& url);

  
  
  URLRow(const GURL& url, URLID id);

  virtual ~URLRow();
  URLRow& operator=(const URLRow& other);

  URLID id() const { return id_; }

  
  
  
  
  void set_id(URLID id) { id_ = id; }

  const GURL& url() const { return url_; }

  const base::string16& title() const {
    return title_;
  }
  void set_title(const base::string16& title) {
    
    
    if (title != title_) {
      title_ = title;
    }
  }

  
  
  
  
  int visit_count() const {
    return visit_count_;
  }
  void set_visit_count(int visit_count) {
    visit_count_ = visit_count;
  }

  
  
  
  
  
  int typed_count() const {
    return typed_count_;
  }
  void set_typed_count(int typed_count) {
    typed_count_ = typed_count;
  }

  base::Time last_visit() const {
    return last_visit_;
  }
  void set_last_visit(base::Time last_visit) {
    last_visit_ = last_visit;
  }

  
  bool hidden() const {
    return hidden_;
  }
  void set_hidden(bool hidden) {
    hidden_ = hidden;
  }

  
  class URLRowHasURL {
   public:
    explicit URLRowHasURL(const GURL& url) : url_(url) {}

    bool operator()(const URLRow& row) {
      return row.url() == url_;
    }

   private:
    const GURL& url_;
  };

 protected:
  
  
  void Swap(URLRow* other);

 private:
  
  
  friend class URLDatabase;
  friend class HistoryBackend;

  
  
  void Initialize();

  
  
  
  URLID id_;

  
  
  
  GURL url_;

  base::string16 title_;

  
  int visit_count_;

  
  int typed_count_;

  
  
  base::Time last_visit_;

  
  
  bool hidden_;

  
};
typedef std::vector<URLRow> URLRows;


class URLResult : public URLRow {
 public:
  URLResult();
  URLResult(const GURL& url, base::Time visit_time);
  
  
  URLResult(const GURL& url,
            const query_parser::Snippet::MatchPositions& title_matches);
  explicit URLResult(const URLRow& url_row);
  virtual ~URLResult();

  base::Time visit_time() const { return visit_time_; }
  void set_visit_time(base::Time visit_time) { visit_time_ = visit_time; }

  const query_parser::Snippet& snippet() const { return snippet_; }

  bool blocked_visit() const { return blocked_visit_; }
  void set_blocked_visit(bool blocked_visit) {
    blocked_visit_ = blocked_visit;
  }

  
  
  
  const query_parser::Snippet::MatchPositions& title_match_positions() const {
    return title_match_positions_;
  }

  void SwapResult(URLResult* other);

  static bool CompareVisitTime(const URLResult& lhs, const URLResult& rhs);

 private:
  friend class HistoryBackend;

  
  base::Time visit_time_;

  
  query_parser::Snippet snippet_;
  query_parser::Snippet::MatchPositions title_match_positions_;

  
  bool blocked_visit_;

  
};

}  

#endif  
