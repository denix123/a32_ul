// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_UTILS_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_UTILS_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "base/strings/utf_offset_string_conversions.h"
#include "components/bookmarks/browser/bookmark_node_data.h"

class BookmarkModel;
class BookmarkNode;
class GURL;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace bookmarks {

class BookmarkClient;

struct QueryFields {
  QueryFields();
  ~QueryFields();

  scoped_ptr<base::string16> word_phrase_query;
  scoped_ptr<base::string16> url;
  scoped_ptr<base::string16> title;
};

void CloneBookmarkNode(BookmarkModel* model,
                       const std::vector<BookmarkNodeData::Element>& elements,
                       const BookmarkNode* parent,
                       int index_to_add_at,
                       bool reset_node_times);

void CopyToClipboard(BookmarkModel* model,
                     const std::vector<const BookmarkNode*>& nodes,
                     bool remove_nodes);

void PasteFromClipboard(BookmarkModel* model,
                        const BookmarkNode* parent,
                        int index);

bool CanPasteFromClipboard(BookmarkModel* model, const BookmarkNode* node);

std::vector<const BookmarkNode*> GetMostRecentlyModifiedUserFolders(
    BookmarkModel* model, size_t max_count);

void GetMostRecentlyAddedEntries(BookmarkModel* model,
                                 size_t count,
                                 std::vector<const BookmarkNode*>* nodes);

bool MoreRecentlyAdded(const BookmarkNode* n1, const BookmarkNode* n2);

void GetBookmarksMatchingProperties(BookmarkModel* model,
                                    const QueryFields& query,
                                    size_t max_count,
                                    const std::string& languages,
                                    std::vector<const BookmarkNode*>* nodes);

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

const BookmarkNode* GetParentForNewNodes(
    const BookmarkNode* parent,
    const std::vector<const BookmarkNode*>& selection,
    int* index);

void DeleteBookmarkFolders(BookmarkModel* model, const std::vector<int64>& ids);

void AddIfNotBookmarked(BookmarkModel* model,
                        const GURL& url,
                        const base::string16& title);

void RemoveAllBookmarks(BookmarkModel* model, const GURL& url);

base::string16 CleanUpUrlForMatching(
    const GURL& gurl,
    const std::string& languages,
    base::OffsetAdjuster::Adjustments* adjustments);

base::string16 CleanUpTitleForMatching(const base::string16& title);

bool CanAllBeEditedByUser(BookmarkClient* client,
                          const std::vector<const BookmarkNode*>& nodes);

bool IsBookmarkedByUser(BookmarkModel* model, const GURL& url);

const BookmarkNode* GetBookmarkNodeByID(const BookmarkModel* model, int64 id);

}  

#endif  
