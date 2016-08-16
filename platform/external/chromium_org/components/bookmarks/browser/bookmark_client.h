// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_CLIENT_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_CLIENT_H_

#include <set>
#include <utility>
#include <vector>

#include "base/callback_forward.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/bookmarks/browser/bookmark_storage.h"
#include "components/favicon_base/favicon_callback.h"
#include "components/favicon_base/favicon_types.h"
#include "components/keyed_service/core/keyed_service.h"

class BookmarkNode;
class BookmarkPermanentNode;
class GURL;

namespace base {
struct UserMetricsAction;
}

namespace bookmarks {

class BookmarkClient : public KeyedService {
 public:
  
  
  
  typedef std::set<const BookmarkNode*> NodeSet;
  typedef std::pair<const BookmarkNode*, int> NodeTypedCountPair;
  typedef std::vector<NodeTypedCountPair> NodeTypedCountPairs;

  
  virtual bool PreferTouchIcon();

  
  
  
  
  
  
  
  
  virtual base::CancelableTaskTracker::TaskId GetFaviconImageForPageURL(
      const GURL& page_url,
      favicon_base::IconType type,
      const favicon_base::FaviconImageCallback& callback,
      base::CancelableTaskTracker* tracker);

    
  virtual bool SupportsTypedCountForNodes();

  
  
  virtual void GetTypedCountForNodes(
      const NodeSet& nodes,
      NodeTypedCountPairs* node_typed_count_pairs);

  
  
  virtual bool IsPermanentNodeVisible(const BookmarkPermanentNode* node) = 0;

  
  
  virtual void RecordAction(const base::UserMetricsAction& action) = 0;

  
  
  virtual LoadExtraCallback GetLoadExtraNodesCallback() = 0;

  
  virtual bool CanSetPermanentNodeTitle(const BookmarkNode* permanent_node) = 0;

  
  virtual bool CanSyncNode(const BookmarkNode* node) = 0;

  
  
  
  
  virtual bool CanBeEditedByUser(const BookmarkNode* node) = 0;

 protected:
  virtual ~BookmarkClient() {}
};

}  

#endif  
