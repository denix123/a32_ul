// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_MODEL_H_
#define UI_APP_LIST_APP_LIST_MODEL_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/app_list_item_list.h"
#include "ui/app_list/app_list_item_list_observer.h"
#include "ui/app_list/search_result.h"
#include "ui/base/models/list_model.h"

namespace app_list {

class AppListFolderItem;
class AppListItem;
class AppListItemList;
class AppListModelObserver;
class SearchBoxModel;

class APP_LIST_EXPORT AppListModel : public AppListItemListObserver {
 public:
  enum Status {
    STATUS_NORMAL,
    STATUS_SYNCING,  
  };

  typedef ui::ListModel<SearchResult> SearchResults;

  AppListModel();
  virtual ~AppListModel();

  void AddObserver(AppListModelObserver* observer);
  void RemoveObserver(AppListModelObserver* observer);

  void SetStatus(Status status);

  
  AppListItem* FindItem(const std::string& id);

  
  AppListFolderItem* FindFolderItem(const std::string& id);

  
  
  AppListItem* AddItem(scoped_ptr<AppListItem> item);

  
  
  
  AppListItem* AddItemToFolder(scoped_ptr<AppListItem> item,
                               const std::string& folder_id);

  
  
  
  
  
  
  
  
  const std::string MergeItems(const std::string& target_item_id,
                               const std::string& source_item_id);

  
  
  
  void MoveItemToFolder(AppListItem* item, const std::string& folder_id);

  
  
  
  
  
  
  
  bool MoveItemToFolderAt(AppListItem* item,
                          const std::string& folder_id,
                          syncer::StringOrdinal position);

  
  
  
  void SetItemPosition(AppListItem* item,
                       const syncer::StringOrdinal& new_position);

  
  void SetItemName(AppListItem* item, const std::string& name);

  
  void SetItemNameAndShortName(AppListItem* item,
                               const std::string& name,
                               const std::string& short_name);

  
  
  void DeleteItem(const std::string& id);

  
  void NotifyExtensionPreferenceChanged();

  
  
  void SetFoldersEnabled(bool folders_enabled);

  
  
  static std::vector<SearchResult*> FilterSearchResultsByDisplayType(
      SearchResults* results,
      SearchResult::DisplayType display_type,
      size_t max_results);

  AppListItemList* top_level_item_list() { return top_level_item_list_.get(); }

  SearchBoxModel* search_box() { return search_box_.get(); }
  SearchResults* results() { return results_.get(); }
  Status status() const { return status_; }
  bool folders_enabled() const { return folders_enabled_; }

 private:
  
  virtual void OnListItemMoved(size_t from_index,
                               size_t to_index,
                               AppListItem* item) OVERRIDE;

  
  AppListFolderItem* FindOrCreateFolderItem(const std::string& folder_id);

  
  AppListItem* AddItemToItemListAndNotify(
      scoped_ptr<AppListItem> item_ptr);

  
  
  AppListItem* AddItemToItemListAndNotifyUpdate(
      scoped_ptr<AppListItem> item_ptr);

  
  AppListItem* AddItemToFolderItemAndNotify(AppListFolderItem* folder,
                                            scoped_ptr<AppListItem> item_ptr);

  
  
  scoped_ptr<AppListItem> RemoveItem(AppListItem* item);

  
  
  
  scoped_ptr<AppListItem> RemoveItemFromFolder(AppListFolderItem* folder,
                                               AppListItem* item);

  scoped_ptr<AppListItemList> top_level_item_list_;

  scoped_ptr<SearchBoxModel> search_box_;
  scoped_ptr<SearchResults> results_;

  Status status_;
  ObserverList<AppListModelObserver, true> observers_;
  bool folders_enabled_;

  DISALLOW_COPY_AND_ASSIGN(AppListModel);
};

}  

#endif  
