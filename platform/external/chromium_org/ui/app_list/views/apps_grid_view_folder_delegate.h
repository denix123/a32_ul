// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_APPS_GRID_VIEW_FOLDER_DELEGATE_H_
#define UI_APP_LIST_VIEWS_APPS_GRID_VIEW_FOLDER_DELEGATE_H_

#include "ui/app_list/app_list_export.h"
#include "ui/app_list/views/apps_grid_view.h"

namespace gfx {
class Point;
}

namespace ui {
class LocatedEvent;
}

namespace app_list {

class AppListItemView;

class APP_LIST_EXPORT AppsGridViewFolderDelegate {
 public:
  
  
  virtual void UpdateFolderViewBackground(bool show_bubble) = 0;

  
  
  
  
  virtual void ReparentItem(AppListItemView* original_drag_view,
                            const gfx::Point& drag_point_in_folder_grid) = 0;

  
  
  virtual void DispatchDragEventForReparent(
      AppsGridView::Pointer pointer,
      const gfx::Point& drag_point_in_folder_grid) = 0;

  
  
  
  
  
  virtual void DispatchEndDragEventForReparent(
      bool events_forwarded_to_drag_drop_host,
      bool cancel_drag) = 0;

  
  virtual bool IsPointOutsideOfFolderBoundary(const gfx::Point& point) = 0;

  
  virtual bool IsOEMFolder() const = 0;

  
  
  virtual void SetRootLevelDragViewVisible(bool visible) = 0;

 protected:
  virtual ~AppsGridViewFolderDelegate() {}
};

}  

#endif  
