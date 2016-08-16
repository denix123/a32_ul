// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_TEST_APP_LIST_TEST_MODEL_H_
#define UI_APP_LIST_TEST_APP_LIST_TEST_MODEL_H_

#include <string>

#include "ui/app_list/app_list_folder_item.h"
#include "ui/app_list/app_list_item.h"
#include "ui/app_list/app_list_model.h"

namespace app_list {

namespace test {

class AppListTestModel : public AppListModel {
 public:
  class AppListTestItem : public AppListItem {
   public:
    AppListTestItem(const std::string& id, AppListTestModel* model);
    virtual ~AppListTestItem();
    virtual void Activate(int event_flags) OVERRIDE;
    virtual const char* GetItemType() const OVERRIDE;

    void SetPosition(const syncer::StringOrdinal& new_position);

   private:
    AppListTestModel* model_;

    DISALLOW_COPY_AND_ASSIGN(AppListTestItem);
  };

  static const char kItemType[];

  AppListTestModel();

  
  AppListItem* AddItem(AppListItem* item);
  AppListItem* AddItemToFolder(AppListItem* item, const std::string& folder_id);
  void MoveItemToFolder(AppListItem* item, const std::string& folder_id);

  
  std::string GetItemName(int id);

  
  void PopulateApps(int n);

  
  AppListFolderItem* CreateAndPopulateFolderWithApps(int n);

  AppListFolderItem* CreateAndAddOemFolder(const std::string& id);

  AppListFolderItem* CreateSingleItemFolder(const std::string& folder_id,
                                            const std::string& item_id);

  
  void PopulateAppWithId(int id);

  
  std::string GetModelContent();

  
  AppListTestItem* CreateItem(const std::string& id);

  
  
  AppListTestItem* CreateAndAddItem(const std::string& id);

  
  void HighlightItemAt(int index);

  int activate_count() { return activate_count_; }
  AppListItem* last_activated() { return last_activated_; }

 private:
  void ItemActivated(AppListTestItem* item);

  int activate_count_;
  AppListItem* last_activated_;

  DISALLOW_COPY_AND_ASSIGN(AppListTestModel);
};

}  
}  

#endif  
