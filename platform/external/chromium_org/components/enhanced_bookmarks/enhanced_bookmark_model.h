// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_MODEL_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_ENHANCED_BOOKMARK_MODEL_H_

#include <map>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "components/bookmarks/browser/base_bookmark_model_observer.h"
#include "components/bookmarks/browser/bookmark_node.h"
#include "components/keyed_service/core/keyed_service.h"

namespace base {
class Time;
}  

class BookmarkModel;
class BookmarkNode;
class GURL;

FORWARD_DECLARE_TEST(EnhancedBookmarkModelTest, SetMultipleMetaInfo);

namespace enhanced_bookmarks {

class EnhancedBookmarkModelObserver;

class EnhancedBookmarkModel : public KeyedService,
                              public BaseBookmarkModelObserver {
 public:
  EnhancedBookmarkModel(BookmarkModel* bookmark_model,
                        const std::string& version);
  virtual ~EnhancedBookmarkModel();

  virtual void Shutdown() OVERRIDE;

  void AddObserver(EnhancedBookmarkModelObserver* observer);
  void RemoveObserver(EnhancedBookmarkModelObserver* observer);

  
  void Move(const BookmarkNode* node,
            const BookmarkNode* new_parent,
            int index);

  
  const BookmarkNode* AddFolder(const BookmarkNode* parent,
                                int index,
                                const base::string16& title);

  
  const BookmarkNode* AddURL(const BookmarkNode* parent,
                             int index,
                             const base::string16& title,
                             const GURL& url,
                             const base::Time& creation_time);

  
  std::string GetRemoteId(const BookmarkNode* node);

  
  
  const BookmarkNode* BookmarkForRemoteId(const std::string& remote_id);

  
  void SetDescription(const BookmarkNode* node, const std::string& description);

  
  std::string GetDescription(const BookmarkNode* node);

  
  
  
  bool SetOriginalImage(const BookmarkNode* node,
                        const GURL& url,
                        int width,
                        int height);

  
  
  
  bool GetOriginalImage(const BookmarkNode* node,
                        GURL* url,
                        int* width,
                        int* height);

  
  
  
  bool GetThumbnailImage(const BookmarkNode* node,
                         GURL* url,
                         int* width,
                         int* height);

  
  
  std::string GetSnippet(const BookmarkNode* node);

  
  
  void SetVersionSuffix(const std::string& version_suffix);

  

  
  
  
  
  
  bool SetAllImages(const BookmarkNode* node,
                    const GURL& image_url,
                    int image_width,
                    int image_height,
                    const GURL& thumbnail_url,
                    int thumbnail_width,
                    int thumbnail_height);

  
  
  BookmarkModel* bookmark_model() { return bookmark_model_; }

  
  bool loaded() { return loaded_; }

 private:
  FRIEND_TEST_ALL_PREFIXES(::EnhancedBookmarkModelTest, SetMultipleMetaInfo);

  typedef std::map<std::string, const BookmarkNode*> IdToNodeMap;
  typedef std::map<const BookmarkNode*, std::string> NodeToIdMap;

  
  virtual void BookmarkModelChanged() OVERRIDE;
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) OVERRIDE;
  virtual void BookmarkNodeAdded(BookmarkModel* model,
                                 const BookmarkNode* parent,
                                 int index) OVERRIDE;
  virtual void BookmarkNodeRemoved(BookmarkModel* model,
                                   const BookmarkNode* parent,
                                   int old_index,
                                   const BookmarkNode* node,
                                   const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void OnWillChangeBookmarkMetaInfo(BookmarkModel* model,
                                            const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkMetaInfoChanged(BookmarkModel* model,
                                       const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkAllUserNodesRemoved(
      BookmarkModel* model,
      const std::set<GURL>& removed_urls) OVERRIDE;

  
  void InitializeIdMap();

  
  
  void AddToIdMap(const BookmarkNode* node);

  
  
  void ScheduleResetDuplicateRemoteIds();

  
  void ResetDuplicateRemoteIds();

  
  
  void SetMetaInfo(const BookmarkNode* node,
                   const std::string& field,
                   const std::string& value);

  
  
  
  void SetMultipleMetaInfo(const BookmarkNode* node,
                           BookmarkNode::MetaInfoMap meta_info);

  
  std::string GetVersionString();

  BookmarkModel* bookmark_model_;
  bool loaded_;

  ObserverList<EnhancedBookmarkModelObserver> observers_;

  base::WeakPtrFactory<EnhancedBookmarkModel> weak_ptr_factory_;

  IdToNodeMap id_map_;
  NodeToIdMap nodes_to_reset_;

  
  std::string prev_remote_id_;

  std::string version_;
  std::string version_suffix_;
};

}  

#endif  
