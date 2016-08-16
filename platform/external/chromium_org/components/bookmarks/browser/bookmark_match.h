// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_TITLE_MATCH_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_TITLE_MATCH_H_

#include <cstddef>
#include <utility>
#include <vector>

class BookmarkNode;

namespace bookmarks {

struct BookmarkMatch {
  
  
  typedef std::pair<size_t, size_t> MatchPosition;
  typedef std::vector<MatchPosition> MatchPositions;

  BookmarkMatch();
  ~BookmarkMatch();

  
  static std::vector<size_t> OffsetsFromMatchPositions(
      const MatchPositions& match_positions);

  
  
  
  static MatchPositions ReplaceOffsetsInMatchPositions(
      const MatchPositions& match_positions,
      const std::vector<size_t>& offsets);

  
  const BookmarkNode* node;

  
  MatchPositions title_match_positions;

  
  MatchPositions url_match_positions;
};

}  

#endif  
