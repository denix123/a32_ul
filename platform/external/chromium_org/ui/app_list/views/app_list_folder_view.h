// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_APP_LIST_FOLDER_VIEW_H_
#define UI_APP_LIST_VIEWS_APP_LIST_FOLDER_VIEW_H_

#include <string>

#include "ui/app_list/app_list_item_list_observer.h"
#include "ui/app_list/views/apps_grid_view.h"
#include "ui/app_list/views/apps_grid_view_folder_delegate.h"
#include "ui/app_list/views/folder_header_view.h"
#include "ui/app_list/views/folder_header_view_delegate.h"
#include "ui/compositor/layer_animation_observer.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/view.h"

namespace views {
class ViewModel;
}

namespace app_list {

class AppsContainerView;
class AppsGridView;
class AppListFolderItem;
class AppListItemView;
class AppListMainView;
class AppListModel;
class FolderHeaderView;

class AppListFolderView : public views::View,
                          public FolderHeaderViewDelegate,
                          public AppListModelObserver,
                          public ui::ImplicitAnimationObserver,
                          public AppsGridViewFolderDelegate {
 public:
  AppListFolderView(AppsContainerView* container_view,
                    AppListModel* model,
                    AppListMainView* app_list_main_view);
  virtual ~AppListFolderView();

  void SetAppListFolderItem(AppListFolderItem* folder);

  
  
  
  void ScheduleShowHideAnimation(bool show, bool hide_for_reparent);

  
  
  gfx::Rect GetItemIconBoundsAt(int index);

  void UpdateFolderNameVisibility(bool visible);

  
  void HideViewImmediately();

  
  void CloseFolderPage();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;

  
  virtual void OnAppListItemWillBeDeleted(AppListItem* item) OVERRIDE;

  
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;

  AppsGridView* items_grid_view() { return items_grid_view_; }

 private:
  void CalculateIdealBounds();

  
  
  
  void StartSetupDragInRootLevelAppsGridView(
      AppListItemView* original_drag_view,
      const gfx::Point& drag_point_in_root_grid);

  
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  
  virtual void NavigateBack(AppListFolderItem* item,
                            const ui::Event& event_flags) OVERRIDE;
  virtual void GiveBackFocusToSearchBox() OVERRIDE;
  virtual void SetItemName(AppListFolderItem* item,
                           const std::string& name) OVERRIDE;

  
  virtual void UpdateFolderViewBackground(bool show_bubble) OVERRIDE;
  virtual void ReparentItem(AppListItemView* original_drag_view,
                            const gfx::Point& drag_point_in_folder_grid)
      OVERRIDE;
  virtual void DispatchDragEventForReparent(
      AppsGridView::Pointer pointer,
      const gfx::Point& drag_point_in_folder_grid) OVERRIDE;
  virtual void DispatchEndDragEventForReparent(
      bool events_forwarded_to_drag_drop_host,
      bool cancel_drag) OVERRIDE;
  virtual bool IsPointOutsideOfFolderBoundary(const gfx::Point& point) OVERRIDE;
  virtual bool IsOEMFolder() const OVERRIDE;
  virtual void SetRootLevelDragViewVisible(bool visible) OVERRIDE;

  AppsContainerView* container_view_;  
  AppListMainView* app_list_main_view_;   
  FolderHeaderView* folder_header_view_;  
  AppsGridView* items_grid_view_;  

  scoped_ptr<views::ViewModel> view_model_;

  AppListModel* model_;  
  AppListFolderItem* folder_item_;  

  bool hide_for_reparent_;

  base::string16 accessible_name_;

  DISALLOW_COPY_AND_ASSIGN(AppListFolderView);
};

}  

#endif  
