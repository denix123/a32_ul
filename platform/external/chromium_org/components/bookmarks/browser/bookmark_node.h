// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_NODE_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_NODE_H_

#include "base/memory/scoped_ptr.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "components/favicon_base/favicon_types.h"
#include "ui/base/models/tree_node_model.h"
#include "ui/gfx/image/image.h"
#include "url/gurl.h"

class BookmarkModel;


class BookmarkNode : public ui::TreeNode<BookmarkNode> {
 public:
  enum Type {
    URL,
    FOLDER,
    BOOKMARK_BAR,
    OTHER_NODE,
    MOBILE
  };

  enum FaviconState {
    INVALID_FAVICON,
    LOADING_FAVICON,
    LOADED_FAVICON,
  };

  typedef std::map<std::string, std::string> MetaInfoMap;

  static const int64 kInvalidSyncTransactionVersion;

  
  explicit BookmarkNode(const GURL& url);
  
  BookmarkNode(int64 id, const GURL& url);

  virtual ~BookmarkNode();

  
  
  
  virtual void SetTitle(const base::string16& title) OVERRIDE;

  
  
  
  int64 id() const { return id_; }
  void set_id(int64 id) { id_ = id; }

  const GURL& url() const { return url_; }
  void set_url(const GURL& url) { url_ = url; }

  
  
  const GURL& icon_url() const { return icon_url_; }

  Type type() const { return type_; }
  void set_type(Type type) { type_ = type; }

  
  const base::Time& date_added() const { return date_added_; }
  void set_date_added(const base::Time& date) { date_added_ = date; }

  
  
  const base::Time& date_folder_modified() const {
    return date_folder_modified_;
  }
  void set_date_folder_modified(const base::Time& date) {
    date_folder_modified_ = date;
  }

  
  
  bool is_folder() const { return type_ != URL; }
  bool is_url() const { return type_ == URL; }

  bool is_favicon_loaded() const { return favicon_state_ == LOADED_FAVICON; }

  
  
  
  
  
  virtual bool IsVisible() const;

  
  
  
  bool GetMetaInfo(const std::string& key, std::string* value) const;
  bool SetMetaInfo(const std::string& key, const std::string& value);
  bool DeleteMetaInfo(const std::string& key);
  void SetMetaInfoMap(const MetaInfoMap& meta_info_map);
  
  const MetaInfoMap* GetMetaInfoMap() const;

  void set_sync_transaction_version(int64 sync_transaction_version) {
    sync_transaction_version_ = sync_transaction_version;
  }
  int64 sync_transaction_version() const {
    return sync_transaction_version_;
  }

  
  

 private:
  friend class BookmarkModel;

  
  void Initialize(int64 id);

  
  void InvalidateFavicon();

  
  void set_icon_url(const GURL& icon_url) {
    icon_url_ = icon_url;
  }

  
  
  
  const gfx::Image& favicon() const { return favicon_; }
  void set_favicon(const gfx::Image& icon) { favicon_ = icon; }

  favicon_base::IconType favicon_type() const { return favicon_type_; }
  void set_favicon_type(favicon_base::IconType type) { favicon_type_ = type; }

  FaviconState favicon_state() const { return favicon_state_; }
  void set_favicon_state(FaviconState state) { favicon_state_ = state; }

  base::CancelableTaskTracker::TaskId favicon_load_task_id() const {
    return favicon_load_task_id_;
  }
  void set_favicon_load_task_id(base::CancelableTaskTracker::TaskId id) {
    favicon_load_task_id_ = id;
  }

  
  int64 id_;

  
  
  GURL url_;

  
  Type type_;

  
  base::Time date_added_;

  
  base::Time date_folder_modified_;

  
  gfx::Image favicon_;

  
  favicon_base::IconType favicon_type_;

  
  GURL icon_url_;

  
  FaviconState favicon_state_;

  
  
  
  base::CancelableTaskTracker::TaskId favicon_load_task_id_;

  
  scoped_ptr<MetaInfoMap> meta_info_map_;

  
  int64 sync_transaction_version_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkNode);
};


class BookmarkPermanentNode : public BookmarkNode {
 public:
  explicit BookmarkPermanentNode(int64 id);
  virtual ~BookmarkPermanentNode();

  
  void set_visible(bool value) { visible_ = value; }

  
  virtual bool IsVisible() const OVERRIDE;

 private:
  bool visible_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkPermanentNode);
};

#endif  
