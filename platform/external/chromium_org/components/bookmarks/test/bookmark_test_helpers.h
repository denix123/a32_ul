// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_TEST_BOOKMARK_TEST_HELPERS_H_
#define COMPONENTS_BOOKMARKS_TEST_BOOKMARK_TEST_HELPERS_H_

#include <string>

class BookmarkModel;
class BookmarkNode;

namespace test {

void WaitForBookmarkModelToLoad(BookmarkModel* model);

std::string ModelStringFromNode(const BookmarkNode* node);

void AddNodesFromModelString(BookmarkModel* model,
                             const BookmarkNode* node,
                             const std::string& model_string);
}  

#endif  
