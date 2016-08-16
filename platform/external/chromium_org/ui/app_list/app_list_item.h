// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_ITEM_H_
#define UI_APP_LIST_APP_LIST_ITEM_H_

#include <string>

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "sync/api/string_ordinal.h"
#include "ui/app_list/app_list_export.h"
#include "ui/gfx/image/image_skia.h"

class FastShowPickler;

namespace ui {
class MenuModel;
}

namespace app_list {

class AppListItemList;
class AppListItemListTest;
class AppListItemObserver;
class AppListModel;

class APP_LIST_EXPORT AppListItem {
 public:
  explicit AppListItem(const std::string& id);
  virtual ~AppListItem();

  void SetIcon(const gfx::ImageSkia& icon, bool has_shadow);
  const gfx::ImageSkia& icon() const { return icon_; }
  bool has_shadow() const { return has_shadow_; }

  const std::string& GetDisplayName() const {
    return short_name_.empty() ? name_ : short_name_;
  }

  const std::string& name() const { return name_; }
  
  const std::string& short_name() const { return short_name_; }

  void SetHighlighted(bool highlighted);
  bool highlighted() const { return highlighted_; }

  void SetIsInstalling(bool is_installing);
  bool is_installing() const { return is_installing_; }

  void SetPercentDownloaded(int percent_downloaded);
  int percent_downloaded() const { return percent_downloaded_; }

  bool IsInFolder() const { return !folder_id_.empty(); }

  const std::string& id() const { return id_; }
  const std::string& folder_id() const { return folder_id_; }
  const syncer::StringOrdinal& position() const { return position_; }

  void AddObserver(AppListItemObserver* observer);
  void RemoveObserver(AppListItemObserver* observer);

  
  virtual void Activate(int event_flags);

  
  
  virtual const char* GetItemType() const;

  
  
  
  virtual ui::MenuModel* GetContextMenuModel();

  
  
  virtual AppListItem* FindChildItem(const std::string& id);

  
  virtual size_t ChildItemCount() const;

  
  
  virtual void OnExtensionPreferenceChanged();

  
  virtual bool CompareForTest(const AppListItem* other) const;
  virtual std::string ToDebugString() const;

 protected:
  friend class ::FastShowPickler;
  friend class AppListItemList;
  friend class AppListItemListTest;
  friend class AppListModel;

  
  

  
  void SetName(const std::string& name);

  
  
  void SetNameAndShortName(const std::string& name,
                           const std::string& short_name);

  void set_position(const syncer::StringOrdinal& new_position) {
    DCHECK(new_position.IsValid());
    position_ = new_position;
  }

  void set_folder_id(const std::string& folder_id) { folder_id_ = folder_id; }

 private:
  friend class AppListModelTest;

  const std::string id_;
  std::string folder_id_;  
  syncer::StringOrdinal position_;
  gfx::ImageSkia icon_;
  bool has_shadow_;

  
  std::string name_;

  
  std::string short_name_;

  bool highlighted_;
  bool is_installing_;
  int percent_downloaded_;

  ObserverList<AppListItemObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(AppListItem);
};

}  

#endif  
