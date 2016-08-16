// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_BOOKMARKS_BOOKMARK_API_HELPERS_H_
#define CHROME_BROWSER_EXTENSIONS_API_BOOKMARKS_BOOKMARK_API_HELPERS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "chrome/common/extensions/api/bookmarks.h"

class BookmarkModel;
class BookmarkNode;
class ChromeBookmarkClient;

namespace extensions {
namespace bookmark_api_helpers {

api::bookmarks::BookmarkTreeNode* GetBookmarkTreeNode(
    ChromeBookmarkClient* client,
    const BookmarkNode* node,
    bool recurse,
    bool only_folders);

void AddNode(ChromeBookmarkClient* client,
             const BookmarkNode* node,
             std::vector<linked_ptr<api::bookmarks::BookmarkTreeNode> >* nodes,
             bool recurse);

void AddNodeFoldersOnly(ChromeBookmarkClient* client,
                        const BookmarkNode* node,
                        std::vector<linked_ptr<
                            api::bookmarks::BookmarkTreeNode> >* nodes,
                        bool recurse);

bool RemoveNode(BookmarkModel* model,
                ChromeBookmarkClient* client,
                int64 id,
                bool recursive,
                std::string* error);

void GetMetaInfo(const BookmarkNode& node,
                 base::DictionaryValue* id_to_meta_info_map);

}  
}  

#endif  
