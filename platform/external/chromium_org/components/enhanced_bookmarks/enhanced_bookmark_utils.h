// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_UTILS_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_UTILS_H_

#include <set>
#include <string>
#include <vector>

class BookmarkModel;
class BookmarkNode;

namespace enhanced_bookmarks {

std::vector<const BookmarkNode*> FindBookmarksWithQuery(
    BookmarkModel* bookmark_model,
    const std::string& query);

void SortBookmarksByName(std::vector<const BookmarkNode*>& nodes);

std::vector<const BookmarkNode*> PrimaryPermanentNodes(BookmarkModel* model);

std::vector<const BookmarkNode*> RootLevelFolders(BookmarkModel* model);

bool IsPrimaryPermanentNode(const BookmarkNode* node, BookmarkModel* model);

const BookmarkNode* RootLevelFolderForNode(const BookmarkNode* node,
                                           BookmarkModel* model);

}  

#endif  
