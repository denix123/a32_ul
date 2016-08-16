// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_FOLDER_BACKGROUND_VIEW_H_
#define UI_APP_LIST_VIEWS_FOLDER_BACKGROUND_VIEW_H_

#include "ui/compositor/layer_animation_observer.h"
#include "ui/views/view.h"

namespace app_list {

class AppListFolderView;

class FolderBackgroundView : public views::View,
                             public ui::ImplicitAnimationObserver {
 public:
  enum ShowState {
    NO_BUBBLE,
    SHOW_BUBBLE,
    HIDE_BUBBLE,
  };

  FolderBackgroundView();
  virtual ~FolderBackgroundView();

  
  void UpdateFolderContainerBubble(ShowState state);

  
  int GetFolderContainerBubbleRadius() const;

  void set_folder_view(AppListFolderView* folder_view) {
    folder_view_ = folder_view;
  }

 private:
  
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;

  AppListFolderView* folder_view_;
  ShowState show_state_;

  DISALLOW_COPY_AND_ASSIGN(FolderBackgroundView);
};

}  

#endif  
