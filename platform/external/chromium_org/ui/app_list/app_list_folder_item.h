// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_FOLDER_ITEM_H_
#define UI_APP_LIST_APP_LIST_FOLDER_ITEM_H_

#include <string>
#include <vector>

#include "ui/app_list/app_list_export.h"
#include "ui/app_list/app_list_item.h"
#include "ui/app_list/app_list_item_list_observer.h"
#include "ui/app_list/app_list_item_observer.h"
#include "ui/gfx/geometry/rect.h"

namespace app_list {

class AppListItemList;

typedef std::vector<gfx::Rect> Rects;

class APP_LIST_EXPORT AppListFolderItem : public AppListItem,
                                          public AppListItemListObserver,
                                          public AppListItemObserver {
 public:
  
  enum FolderType {
    
    FOLDER_TYPE_NORMAL,
    
    FOLDER_TYPE_OEM
  };

  static const char kItemType[];

  AppListFolderItem(const std::string& id, FolderType folder_type);
  virtual ~AppListFolderItem();

  
  void UpdateIcon();

  
  const gfx::ImageSkia& GetTopIcon(size_t item_index);

  
  
  
  
  
  
  gfx::Rect GetTargetIconRectInFolderForItem(
      AppListItem* item, const gfx::Rect& folder_icon_bounds);

  AppListItemList* item_list() { return item_list_.get(); }
  const AppListItemList* item_list() const { return item_list_.get(); }

  FolderType folder_type() const { return folder_type_; }

  
  virtual void Activate(int event_flags) OVERRIDE;
  virtual const char* GetItemType() const OVERRIDE;
  virtual ui::MenuModel* GetContextMenuModel() OVERRIDE;
  virtual AppListItem* FindChildItem(const std::string& id) OVERRIDE;
  virtual size_t ChildItemCount() const OVERRIDE;
  virtual void OnExtensionPreferenceChanged() OVERRIDE;
  virtual bool CompareForTest(const AppListItem* other) const OVERRIDE;

  
  
  
  static Rects GetTopIconsBounds(const gfx::Rect& folder_icon_bounds);

  
  static std::string GenerateId();

 private:
  
  virtual void ItemIconChanged() OVERRIDE;

  
  virtual void OnListItemAdded(size_t index, AppListItem* item) OVERRIDE;
  virtual void OnListItemRemoved(size_t index,
                                 AppListItem* item) OVERRIDE;;
  virtual void OnListItemMoved(size_t from_index,
                               size_t to_index,
                               AppListItem* item) OVERRIDE;

  void UpdateTopItems();

  
  const FolderType folder_type_;

  
  scoped_ptr<AppListItemList> item_list_;

  
  std::vector<AppListItem*> top_items_;

  DISALLOW_COPY_AND_ASSIGN(AppListFolderItem);
};

}  

#endif  
