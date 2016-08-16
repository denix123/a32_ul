// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BOOKMARKS_CHROME_BOOKMARK_CLIENT_H_
#define CHROME_BROWSER_BOOKMARKS_CHROME_BOOKMARK_CLIENT_H_

#include <set>
#include <vector>

#include "base/callback_list.h"
#include "base/deferred_sequenced_task_runner.h"
#include "base/macros.h"
#include "components/bookmarks/browser/base_bookmark_model_observer.h"
#include "components/bookmarks/browser/bookmark_client.h"
#include "components/policy/core/browser/managed_bookmarks_tracker.h"

class BookmarkModel;
class GURL;
class HistoryService;
class HistoryServiceFactory;
class Profile;

class ChromeBookmarkClient : public bookmarks::BookmarkClient,
                             public BaseBookmarkModelObserver {
 public:
  explicit ChromeBookmarkClient(Profile* profile);
  virtual ~ChromeBookmarkClient();

  void Init(BookmarkModel* model);

  
  virtual void Shutdown() OVERRIDE;

  
  const BookmarkNode* managed_node() { return managed_node_; }

  
  bool IsDescendantOfManagedNode(const BookmarkNode* node);

  
  bool HasDescendantsOfManagedNode(
      const std::vector<const BookmarkNode*>& list);

  
  virtual bool PreferTouchIcon() OVERRIDE;
  virtual base::CancelableTaskTracker::TaskId GetFaviconImageForPageURL(
      const GURL& page_url,
      favicon_base::IconType type,
      const favicon_base::FaviconImageCallback& callback,
      base::CancelableTaskTracker* tracker) OVERRIDE;
  virtual bool SupportsTypedCountForNodes() OVERRIDE;
  virtual void GetTypedCountForNodes(
      const NodeSet& nodes,
      NodeTypedCountPairs* node_typed_count_pairs) OVERRIDE;
  virtual bool IsPermanentNodeVisible(
      const BookmarkPermanentNode* node) OVERRIDE;
  virtual void RecordAction(const base::UserMetricsAction& action) OVERRIDE;
  virtual bookmarks::LoadExtraCallback GetLoadExtraNodesCallback() OVERRIDE;
  virtual bool CanSetPermanentNodeTitle(
      const BookmarkNode* permanent_node) OVERRIDE;
  virtual bool CanSyncNode(const BookmarkNode* node) OVERRIDE;
  virtual bool CanBeEditedByUser(const BookmarkNode* node) OVERRIDE;

 private:
  friend class HistoryServiceFactory;
  void SetHistoryService(HistoryService* history_service);

  
  virtual void BookmarkModelChanged() OVERRIDE;
  virtual void BookmarkNodeRemoved(BookmarkModel* model,
                                   const BookmarkNode* parent,
                                   int old_index,
                                   const BookmarkNode* node,
                                   const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void BookmarkAllUserNodesRemoved(
      BookmarkModel* model,
      const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) OVERRIDE;

  
  static bookmarks::BookmarkPermanentNodeList LoadExtraNodes(
      scoped_ptr<BookmarkPermanentNode> managed_node,
      scoped_ptr<base::ListValue> initial_managed_bookmarks,
      int64* next_node_id);

  
  
  std::string GetManagedBookmarksDomain();

  Profile* profile_;

  
  
  
  HistoryService* history_service_;

  scoped_ptr<base::CallbackList<void(const std::set<GURL>&)>::Subscription>
      favicon_changed_subscription_;

  
  
  BookmarkModel* model_;

  scoped_ptr<policy::ManagedBookmarksTracker> managed_bookmarks_tracker_;
  BookmarkPermanentNode* managed_node_;

  DISALLOW_COPY_AND_ASSIGN(ChromeBookmarkClient);
};

#endif  
