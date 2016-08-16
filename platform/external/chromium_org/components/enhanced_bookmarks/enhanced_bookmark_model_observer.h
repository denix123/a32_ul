// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_MODEL_OBSERVER_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_MODEL_OBSERVER_H_

#include <string>

class BookmarkNode;

namespace enhanced_bookmarks {

class EnhancedBookmarkModelObserver {
 public:
  
  virtual void EnhancedBookmarkModelLoaded() = 0;

  
  virtual void EnhancedBookmarkModelShuttingDown() = 0;

  
  virtual void EnhancedBookmarkAdded(const BookmarkNode* node) = 0;

  
  virtual void EnhancedBookmarkRemoved(const BookmarkNode* node) = 0;

  
  virtual void EnhancedBookmarkAllUserNodesRemoved() = 0;

  
  
  
  virtual void EnhancedBookmarkRemoteIdChanged(const BookmarkNode* node,
                                               const std::string& old_remote_id,
                                               const std::string& remote_id) {};

 protected:
  virtual ~EnhancedBookmarkModelObserver() {}
};

}  
#endif  
