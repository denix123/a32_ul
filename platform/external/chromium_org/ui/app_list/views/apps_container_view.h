// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_APPS_CONTAINER_VIEW_H_
#define UI_APP_LIST_VIEWS_APPS_CONTAINER_VIEW_H_

#include <vector>

#include "ui/app_list/app_list_folder_item.h"
#include "ui/app_list/views/top_icon_animation_view.h"
#include "ui/views/view.h"

namespace app_list {

class AppsGridView;
class ApplicationDragAndDropHost;
class AppListFolderItem;
class AppListFolderView;
class AppListMainView;
class AppListModel;
class ContentsView;
class FolderBackgroundView;

class AppsContainerView : public views::View,
                          public TopIconAnimationObserver {
 public:
  AppsContainerView(AppListMainView* app_list_main_view,
                    AppListModel* model);
  virtual ~AppsContainerView();

  
  void ShowActiveFolder(AppListFolderItem* folder_item);

  
  
  void ShowApps(AppListFolderItem* folder_item);

  
  
  
  
  void ResetForShowApps();

  
  
  void SetDragAndDropHostOfCurrentAppList(
      ApplicationDragAndDropHost* drag_and_drop_host);

  
  
  void ReparentFolderItemTransit(AppListFolderItem* folder_item);

  
  bool IsInFolderView() const;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;

  
  virtual void OnTopIconAnimationsComplete() OVERRIDE;

  AppsGridView* apps_grid_view() { return apps_grid_view_; }
  FolderBackgroundView* folder_background_view() {
     return folder_background_view_;
  }
  AppListFolderView* app_list_folder_view() { return app_list_folder_view_; }

 private:
  enum ShowState {
    SHOW_NONE,  
    SHOW_APPS,
    SHOW_ACTIVE_FOLDER,
    SHOW_ITEM_REPARENT,
  };

  void SetShowState(ShowState show_state, bool show_apps_with_animation);

  
  
  
  
  Rects GetTopItemIconBoundsInActiveFolder();

  
  
  void CreateViewsForFolderTopItemsAnimation(
      AppListFolderItem* active_folder, bool open_folder);

  void PrepareToShowApps(AppListFolderItem* folder_item);

  AppListModel* model_;
  AppsGridView* apps_grid_view_;  
  AppListFolderView* app_list_folder_view_;  
  FolderBackgroundView* folder_background_view_;  
  ShowState show_state_;

  
  
  std::vector<views::View*> top_icon_views_;

  size_t top_icon_animation_pending_count_;

  DISALLOW_COPY_AND_ASSIGN(AppsContainerView);
};

}  


#endif  
