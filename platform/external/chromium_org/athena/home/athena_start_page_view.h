// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_HOME_ATHENA_START_PAGE_VIEW_H_
#define ATHENA_HOME_ATHENA_START_PAGE_VIEW_H_

#include "athena/athena_export.h"
#include "base/memory/weak_ptr.h"
#include "ui/app_list/views/search_box_view_delegate.h"
#include "ui/gfx/animation/tween.h"
#include "ui/views/view.h"

namespace app_list {
class AppListViewDelegate;
class SearchBoxView;
class SearchResultListView;
}

namespace athena {

class ATHENA_EXPORT AthenaStartPageView
    : public views::View,
      public app_list::SearchBoxViewDelegate {
 public:
  explicit AthenaStartPageView(app_list::AppListViewDelegate* delegate);
  virtual ~AthenaStartPageView();

  
  void RequestFocusOnSearchBox();

  
  void SetLayoutState(float layout_state);

  
  
  void SetLayoutStateWithAnimation(float layout_state,
                                   gfx::Tween::Type tween_type);

 private:
  friend class AthenaStartPageViewTest;

  static const char kViewClassName[];

  
  struct LayoutData {
    gfx::Rect search_box;
    gfx::Rect icons;
    gfx::Rect controls;
    float system_info_opacity;
    float logo_opacity;
    float background_opacity;

    LayoutData();
  };

  
  LayoutData CreateBottomBounds(int width);

  
  LayoutData CreateCenteredBounds(int width);

  
  
  void LayoutSearchResults(bool should_show_search_results);

  
  
  void OnSearchResultLayoutAnimationCompleted(bool should_show_search_results);

  
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& key_event) OVERRIDE;

  
  virtual void QueryChanged(app_list::SearchBoxView* sender) OVERRIDE;

  
  app_list::AppListViewDelegate* delegate_;

  
  views::View* system_info_view_;
  views::View* app_icon_container_;
  views::View* search_box_container_;
  views::View* control_icon_container_;
  views::View* logo_;
  app_list::SearchBoxView* search_box_view_;
  app_list::SearchResultListView* search_results_view_;

  
  
  views::View* background_;

  
  int search_results_height_;

  
  
  float layout_state_;

  base::WeakPtrFactory<AthenaStartPageView> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AthenaStartPageView);
};

}  

#endif  
