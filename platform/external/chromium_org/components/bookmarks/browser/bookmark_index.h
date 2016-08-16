// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_INDEX_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_INDEX_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "components/query_parser/query_parser.h"

class BookmarkNode;

namespace bookmarks {

class BookmarkClient;
struct BookmarkMatch;

class BookmarkIndex {
 public:
  
  BookmarkIndex(BookmarkClient* client,
                const std::string& languages);
  ~BookmarkIndex();

  
  void Add(const BookmarkNode* node);

  
  void Remove(const BookmarkNode* node);

  
  
  void GetBookmarksMatching(
      const base::string16& query,
      size_t max_count,
      std::vector<BookmarkMatch>* results);

 private:
  typedef std::vector<const BookmarkNode*> Nodes;
  typedef std::set<const BookmarkNode*> NodeSet;
  typedef std::map<base::string16, NodeSet> Index;

  struct Match;
  typedef std::vector<Match> Matches;

  
  
  void SortMatches(const Matches& matches, Nodes* sorted_nodes) const;

  
  void AddMatchToResults(
      const BookmarkNode* node,
      query_parser::QueryParser* parser,
      const query_parser::QueryNodeStarVector& query_nodes,
      std::vector<BookmarkMatch>* results);

  
  
  
  bool GetBookmarksMatchingTerm(const base::string16& term,
                                bool first_term,
                                Matches* matches);

  
  
  
  
  
  void CombineMatchesInPlace(const Index::const_iterator& index_i,
                             Matches* matches);

  
  
  
  
  
  
  
  
  
  void CombineMatches(const Index::const_iterator& index_i,
                      const Matches& current_matches,
                      Matches* result);

  
  std::vector<base::string16> ExtractQueryWords(const base::string16& query);

  
  void RegisterNode(const base::string16& term, const BookmarkNode* node);

  
  void UnregisterNode(const base::string16& term, const BookmarkNode* node);

  Index index_;

  BookmarkClient* const client_;

  
  const std::string languages_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkIndex);
};

}  

#endif  
