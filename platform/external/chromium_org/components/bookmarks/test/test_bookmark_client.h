// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_TEST_TEST_BOOKMARK_CLIENT_H_
#define COMPONENTS_BOOKMARKS_TEST_TEST_BOOKMARK_CLIENT_H_

#include "base/memory/scoped_ptr.h"
#include "components/bookmarks/browser/bookmark_client.h"

class BookmarkModel;

namespace bookmarks {

class TestBookmarkClient : public BookmarkClient {
 public:
  TestBookmarkClient();
  virtual ~TestBookmarkClient();

  
  
  scoped_ptr<BookmarkModel> CreateModel();

  
  
  void SetExtraNodesToLoad(BookmarkPermanentNodeList extra_nodes);

  
  const std::vector<BookmarkPermanentNode*>& extra_nodes() {
    return extra_nodes_;
  }

  
  bool IsExtraNodeRoot(const BookmarkNode* node);

  
  bool IsAnExtraNode(const BookmarkNode* node);

 private:
  
  virtual bool IsPermanentNodeVisible(
      const BookmarkPermanentNode* node) OVERRIDE;
  virtual void RecordAction(const base::UserMetricsAction& action) OVERRIDE;
  virtual LoadExtraCallback GetLoadExtraNodesCallback() OVERRIDE;
  virtual bool CanSetPermanentNodeTitle(
      const BookmarkNode* permanent_node) OVERRIDE;
  virtual bool CanSyncNode(const BookmarkNode* node) OVERRIDE;
  virtual bool CanBeEditedByUser(const BookmarkNode* node) OVERRIDE;

  
  static BookmarkPermanentNodeList LoadExtraNodes(
      BookmarkPermanentNodeList extra_nodes,
      int64* next_id);

  BookmarkPermanentNodeList extra_nodes_to_load_;
  std::vector<BookmarkPermanentNode*> extra_nodes_;

  DISALLOW_COPY_AND_ASSIGN(TestBookmarkClient);
};

}  

#endif  
