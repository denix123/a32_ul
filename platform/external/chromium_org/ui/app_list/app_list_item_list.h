// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_ITEM_LIST_H_
#define UI_APP_LIST_APP_LIST_ITEM_LIST_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "sync/api/string_ordinal.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/app_list_item_list_observer.h"

namespace app_list {

class AppListItem;

class APP_LIST_EXPORT AppListItemList {
 public:
  AppListItemList();
  virtual ~AppListItemList();

  void AddObserver(AppListItemListObserver* observer);
  void RemoveObserver(AppListItemListObserver* observer);

  
  
  
  AppListItem* FindItem(const std::string& id);

  
  
  
  bool FindItemIndex(const std::string& id, size_t* index);

  
  
  void MoveItem(size_t from_index, size_t to_index);

  
  
  
  void SetItemPosition(AppListItem* item, syncer::StringOrdinal new_position);

  AppListItem* item_at(size_t index) {
    DCHECK_LT(index, app_list_items_.size());
    return app_list_items_[index];
  }
  const AppListItem* item_at(size_t index) const {
    DCHECK_LT(index, app_list_items_.size());
    return app_list_items_[index];
  }
  size_t item_count() const { return app_list_items_.size(); }

 private:
  friend class AppListItemListTest;
  friend class AppListModel;

  
  
  syncer::StringOrdinal CreatePositionBefore(
      const syncer::StringOrdinal& position);

  
  
  
  AppListItem* AddItem(scoped_ptr<AppListItem> item_ptr);

  
  
  
  void DeleteItem(const std::string& id);

  
  
  scoped_ptr<AppListItem> RemoveItem(const std::string& id);

  
  
  scoped_ptr<AppListItem> RemoveItemAt(size_t index);

  
  void DeleteItemAt(size_t index);

  
  
  void EnsureValidItemPosition(AppListItem* item);

  
  
  size_t GetItemSortOrderIndex(const syncer::StringOrdinal& position,
                               const std::string& id);

  
  
  void FixItemPosition(size_t index);

  ScopedVector<AppListItem> app_list_items_;
  ObserverList<AppListItemListObserver, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(AppListItemList);
};

}  

#endif  
