// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_OBSERVER_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_OBSERVER_H_

#include <set>

class BookmarkModel;
class BookmarkNode;
class GURL;

class BookmarkModelObserver {
 public:
  
  
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) = 0;

  
  virtual void BookmarkModelBeingDeleted(BookmarkModel* model) {}

  
  virtual void BookmarkNodeMoved(BookmarkModel* model,
                                 const BookmarkNode* old_parent,
                                 int old_index,
                                 const BookmarkNode* new_parent,
                                 int new_index) = 0;

  
  virtual void BookmarkNodeAdded(BookmarkModel* model,
                                 const BookmarkNode* parent,
                                 int index) = 0;

  
  
  
  
  virtual void OnWillRemoveBookmarks(BookmarkModel* model,
                                     const BookmarkNode* parent,
                                     int old_index,
                                     const BookmarkNode* node) {}

  
  
  
  
  
  
  
  virtual void BookmarkNodeRemoved(BookmarkModel* model,
                                   const BookmarkNode* parent,
                                   int old_index,
                                   const BookmarkNode* node,
                                   const std::set<GURL>& removed_urls) = 0;

  
  virtual void OnWillChangeBookmarkNode(BookmarkModel* model,
                                        const BookmarkNode* node) {}

  
  virtual void BookmarkNodeChanged(BookmarkModel* model,
                                   const BookmarkNode* node) = 0;

  
  virtual void OnWillChangeBookmarkMetaInfo(BookmarkModel* model,
                                            const BookmarkNode* node) {}

  
  virtual void BookmarkMetaInfoChanged(BookmarkModel* model,
                                       const BookmarkNode* node) {}

  
  virtual void BookmarkNodeFaviconChanged(BookmarkModel* model,
                                          const BookmarkNode* node) = 0;

  
  
  virtual void OnWillReorderBookmarkNode(BookmarkModel* model,
                                         const BookmarkNode* node) {}

  
  
  virtual void BookmarkNodeChildrenReordered(BookmarkModel* model,
                                             const BookmarkNode* node) = 0;

  
  
  
  
  
  
  virtual void ExtensiveBookmarkChangesBeginning(BookmarkModel* model) {}

  
  
  
  virtual void ExtensiveBookmarkChangesEnded(BookmarkModel* model) {}

  
  
  virtual void OnWillRemoveAllUserBookmarks(BookmarkModel* model) {}

  
  
  
  
  virtual void BookmarkAllUserNodesRemoved(
      BookmarkModel* model,
      const std::set<GURL>& removed_urls) = 0;

  
  
  
  virtual void GroupedBookmarkChangesBeginning(BookmarkModel* model) {}

  
  
  virtual void GroupedBookmarkChangesEnded(BookmarkModel* model) {}

 protected:
  virtual ~BookmarkModelObserver() {}
};

#endif  
