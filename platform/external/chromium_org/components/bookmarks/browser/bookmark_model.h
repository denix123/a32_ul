// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_H_

#include <map>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "components/bookmarks/browser/bookmark_client.h"
#include "components/bookmarks/browser/bookmark_node.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ui/gfx/image/image.h"
#include "url/gurl.h"

class BookmarkModelObserver;
class PrefService;

namespace base {
class FilePath;
class SequencedTaskRunner;
}

namespace bookmarks {
class BookmarkCodecTest;
class BookmarkExpandedStateTracker;
class BookmarkIndex;
class BookmarkLoadDetails;
class BookmarkStorage;
class ScopedGroupBookmarkActions;
class TestBookmarkClient;
struct BookmarkMatch;
}

namespace favicon_base {
struct FaviconImageResult;
}


class BookmarkModel : public KeyedService {
 public:
  struct URLAndTitle {
    GURL url;
    base::string16 title;
  };

  explicit BookmarkModel(bookmarks::BookmarkClient* client);
  virtual ~BookmarkModel();

  
  virtual void Shutdown() OVERRIDE;

  
  
  
  
  void Load(PrefService* pref_service,
            const std::string& accept_languages,
            const base::FilePath& profile_path,
            const scoped_refptr<base::SequencedTaskRunner>& io_task_runner,
            const scoped_refptr<base::SequencedTaskRunner>& ui_task_runner);

  
  bool loaded() const { return loaded_; }

  
  
  const BookmarkNode* root_node() const { return &root_; }

  
  const BookmarkNode* bookmark_bar_node() const { return bookmark_bar_node_; }

  
  const BookmarkNode* other_node() const { return other_node_; }

  
  const BookmarkNode* mobile_node() const { return mobile_node_; }

  bool is_root_node(const BookmarkNode* node) const { return node == &root_; }

  
  
  
  bool is_permanent_node(const BookmarkNode* node) const {
    return node && (node == &root_ || node->parent() == &root_);
  }

  
  
  const BookmarkNode* GetParentForNewNodes();

  void AddObserver(BookmarkModelObserver* observer);
  void RemoveObserver(BookmarkModelObserver* observer);

  
  
  
  void BeginExtensiveChanges();
  void EndExtensiveChanges();

  
  
  
  
  bool IsDoingExtensiveChanges() const { return extensive_changes_ > 0; }

  
  
  void Remove(const BookmarkNode* parent, int index);

  
  
  
  void RemoveAllUserBookmarks();

  
  void Move(const BookmarkNode* node,
            const BookmarkNode* new_parent,
            int index);

  
  void Copy(const BookmarkNode* node,
            const BookmarkNode* new_parent,
            int index);

  
  
  const gfx::Image& GetFavicon(const BookmarkNode* node);

  
  
  favicon_base::IconType GetFaviconType(const BookmarkNode* node);

  
  void SetTitle(const BookmarkNode* node, const base::string16& title);

  
  void SetURL(const BookmarkNode* node, const GURL& url);

  
  void SetDateAdded(const BookmarkNode* node, base::Time date_added);

  
  void GetNodesByURL(const GURL& url, std::vector<const BookmarkNode*>* nodes);

  
  
  
  const BookmarkNode* GetMostRecentlyAddedUserNodeForURL(const GURL& url);

  
  
  bool HasBookmarks();

  
  
  
  bool IsBookmarked(const GURL& url);

  
  
  
  
  
  
  void GetBookmarks(std::vector<BookmarkModel::URLAndTitle>* urls);

  
  
  void BlockTillLoaded();

  
  const BookmarkNode* AddFolder(const BookmarkNode* parent,
                                int index,
                                const base::string16& title);

  
  const BookmarkNode* AddFolderWithMetaInfo(
      const BookmarkNode* parent,
      int index,
      const base::string16& title,
      const BookmarkNode::MetaInfoMap* meta_info);

  
  const BookmarkNode* AddURL(const BookmarkNode* parent,
                             int index,
                             const base::string16& title,
                             const GURL& url);

  
  const BookmarkNode* AddURLWithCreationTimeAndMetaInfo(
      const BookmarkNode* parent,
      int index,
      const base::string16& title,
      const GURL& url,
      const base::Time& creation_time,
      const BookmarkNode::MetaInfoMap* meta_info);

  
  
  void SortChildren(const BookmarkNode* parent);

  
  
  
  
  void ReorderChildren(const BookmarkNode* parent,
                       const std::vector<const BookmarkNode*>& ordered_nodes);

  
  void SetDateFolderModified(const BookmarkNode* node, const base::Time time);

  
  
  
  void ResetDateFolderModified(const BookmarkNode* node);

  
  
  void GetBookmarksMatching(const base::string16& text,
                            size_t max_count,
                            std::vector<bookmarks::BookmarkMatch>* matches);

  
  
  
  void ClearStore();

  
  int64 next_node_id() const { return next_node_id_; }

  
  
  bookmarks::BookmarkExpandedStateTracker* expanded_state_tracker() {
    return expanded_state_tracker_.get();
  }

  
  
  
  void SetPermanentNodeVisible(BookmarkNode::Type type, bool value);

  
  const BookmarkPermanentNode* PermanentNode(BookmarkNode::Type type);

  
  void SetNodeMetaInfo(const BookmarkNode* node,
                       const std::string& key,
                       const std::string& value);
  void SetNodeMetaInfoMap(const BookmarkNode* node,
                          const BookmarkNode::MetaInfoMap& meta_info_map);
  void DeleteNodeMetaInfo(const BookmarkNode* node,
                          const std::string& key);

  
  void SetNodeSyncTransactionVersion(const BookmarkNode* node,
                                     int64 sync_transaction_version);

  
  
  void OnFaviconChanged(const std::set<GURL>& urls);

  
  bookmarks::BookmarkClient* client() const { return client_; }

 private:
  friend class bookmarks::BookmarkCodecTest;
  friend class bookmarks::BookmarkStorage;
  friend class bookmarks::ScopedGroupBookmarkActions;
  friend class bookmarks::TestBookmarkClient;

  
  class NodeURLComparator {
   public:
    bool operator()(const BookmarkNode* n1, const BookmarkNode* n2) const {
      return n1->url() < n2->url();
    }
  };

  
  
  bool IsBookmarkedNoLock(const GURL& url);

  
  
  
  
  void RemoveNode(BookmarkNode* node, std::set<GURL>* removed_urls);

  
  
  void DoneLoading(scoped_ptr<bookmarks::BookmarkLoadDetails> details);

  
  void PopulateNodesByURL(BookmarkNode* node);

  
  
  
  
  void RemoveNodeAndGetRemovedUrls(BookmarkNode* node,
                                   std::set<GURL>* removed_urls);

  
  
  void RemoveAndDeleteNode(BookmarkNode* delete_me);

  
  void RemoveNodeFromURLSet(BookmarkNode* node);

  
  
  BookmarkNode* AddNode(BookmarkNode* parent,
                        int index,
                        BookmarkNode* node);

  
  bool IsValidIndex(const BookmarkNode* parent, int index, bool allow_end);

  
  
  BookmarkPermanentNode* CreatePermanentNode(BookmarkNode::Type type);

  
  
  void OnFaviconDataAvailable(
      BookmarkNode* node,
      favicon_base::IconType icon_type,
      const favicon_base::FaviconImageResult& image_result);

  
  
  void LoadFavicon(BookmarkNode* node, favicon_base::IconType icon_type);

  
  void FaviconLoaded(const BookmarkNode* node);

  
  void CancelPendingFaviconLoadRequests(BookmarkNode* node);

  
  
  void BeginGroupedChanges();
  void EndGroupedChanges();

  
  int64 generate_next_node_id();

  
  
  
  void set_next_node_id(int64 id) { next_node_id_ = id; }

  
  
  scoped_ptr<bookmarks::BookmarkLoadDetails> CreateLoadDetails(
      const std::string& accept_languages);

  bookmarks::BookmarkClient* const client_;

  
  bool loaded_;

  
  
  BookmarkNode root_;

  BookmarkPermanentNode* bookmark_bar_node_;
  BookmarkPermanentNode* other_node_;
  BookmarkPermanentNode* mobile_node_;

  
  int64 next_node_id_;

  
  ObserverList<BookmarkModelObserver> observers_;

  
  
  
  
  typedef std::multiset<BookmarkNode*, NodeURLComparator> NodesOrderedByURLSet;
  NodesOrderedByURLSet nodes_ordered_by_url_set_;
  base::Lock url_lock_;

  
  base::CancelableTaskTracker cancelable_task_tracker_;

  
  scoped_ptr<bookmarks::BookmarkStorage> store_;

  scoped_ptr<bookmarks::BookmarkIndex> index_;

  base::WaitableEvent loaded_signal_;

  
  int extensive_changes_;

  scoped_ptr<bookmarks::BookmarkExpandedStateTracker> expanded_state_tracker_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkModel);
};

#endif  
