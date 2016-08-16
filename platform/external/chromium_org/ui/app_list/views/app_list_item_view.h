// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_APP_LIST_ITEM_VIEW_H_
#define UI_APP_LIST_VIEWS_APP_LIST_ITEM_VIEW_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/app_list_item_observer.h"
#include "ui/app_list/views/cached_label.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/controls/button/custom_button.h"

class SkBitmap;

namespace views {
class ImageView;
class Label;
class MenuRunner;
}

namespace app_list {

class AppListItem;
class AppsGridView;
class ProgressBarView;

class APP_LIST_EXPORT AppListItemView : public views::CustomButton,
                                        public views::ContextMenuController,
                                        public AppListItemObserver {
 public:
  
  static const char kViewClassName[];

  AppListItemView(AppsGridView* apps_grid_view, AppListItem* item);
  virtual ~AppListItemView();

  
  void SetIcon(const gfx::ImageSkia& icon, bool has_shadow);

  
  void SetItemName(const base::string16& display_name,
                   const base::string16& full_name);
  void SetItemIsInstalling(bool is_installing);
  void SetItemIsHighlighted(bool is_highlighted);
  void SetItemPercentDownloaded(int percent_downloaded);

  void Prerender();

  void CancelContextMenu();

  gfx::ImageSkia GetDragImage();
  void OnDragEnded();
  gfx::Point GetDragImageOffset();

  void SetAsAttemptedFolderTarget(bool is_target_folder);

  AppListItem* item() const { return item_weak_; }

  views::ImageView* icon() const { return icon_; }

  const views::Label* title() const { return title_; }

  
  
  void OnSyncDragEnd();

  
  const gfx::Rect& GetIconBounds() const;

  
  void SetDragUIState();

  
  
  gfx::Rect GetIconBoundsForTargetViewBounds(const gfx::Rect& target_bounds);

 private:
  enum UIState {
    UI_STATE_NORMAL,    
    UI_STATE_DRAGGING,  
    UI_STATE_DROPPING_IN_FOLDER,  
  };

  
  void UpdateIcon();

  
  void UpdateTooltip();

  void SetUIState(UIState state);

  
  void SetTouchDragging(bool touch_dragging);

  
  void OnMouseDragTimer();

  
  
  void SetTitleSubpixelAA();

  
  virtual const char* GetClassName() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void SchedulePaintInRect(const gfx::Rect& r) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  virtual void ShowContextMenuForView(views::View* source,
                                      const gfx::Point& point,
                                      ui::MenuSourceType source_type) OVERRIDE;

  
  virtual void StateChanged() OVERRIDE;
  virtual bool ShouldEnterPushedState(const ui::Event& event) OVERRIDE;

  
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseCaptureLost() OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;

  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual void ItemIconChanged() OVERRIDE;
  virtual void ItemNameChanged() OVERRIDE;
  virtual void ItemHighlightedChanged() OVERRIDE;
  virtual void ItemIsInstallingChanged() OVERRIDE;
  virtual void ItemPercentDownloadedChanged() OVERRIDE;
  virtual void ItemBeingDestroyed() OVERRIDE;

  const bool is_folder_;
  const bool is_in_folder_;

  AppListItem* item_weak_;  

  AppsGridView* apps_grid_view_;   
  views::ImageView* icon_;         
  CachedLabel* title_;             
  ProgressBarView* progress_bar_;  

  scoped_ptr<views::MenuRunner> context_menu_runner_;

  UIState ui_state_;

  
  bool touch_dragging_;

  bool is_installing_;
  bool is_highlighted_;

  
  base::OneShotTimer<AppListItemView> mouse_drag_timer_;

  DISALLOW_COPY_AND_ASSIGN(AppListItemView);
};

}  

#endif  
