// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_SEARCH_RESULT_LIST_VIEW_H_
#define UI_APP_LIST_VIEWS_SEARCH_RESULT_LIST_VIEW_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "ui/app_list/app_list_model.h"
#include "ui/base/models/list_model_observer.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/views/view.h"

namespace gfx {
class LinearAnimation;
}

namespace app_list {
namespace test {
class SearchResultListViewTest;
}

class AppListViewDelegate;
class SearchResultListViewDelegate;
class SearchResultView;

class APP_LIST_EXPORT SearchResultListView : public views::View,
                                             public gfx::AnimationDelegate,
                                             public ui::ListModelObserver {
 public:
  SearchResultListView(SearchResultListViewDelegate* delegate,
                       AppListViewDelegate* view_delegate);
  virtual ~SearchResultListView();

  void SetResults(AppListModel::SearchResults* results);

  void SetSelectedIndex(int selected_index);

  void UpdateAutoLaunchState();

  bool IsResultViewSelected(const SearchResultView* result_view) const;

  void SearchResultActivated(SearchResultView* view, int event_flags);

  void SearchResultActionActivated(SearchResultView* view,
                                   size_t action_index,
                                   int event_flags);

  void OnSearchResultInstalled(SearchResultView* view);

  void OnSearchResultUninstalled(SearchResultView* view);

  
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

 private:
  friend class test::SearchResultListViewTest;

  
  void SetAutoLaunchTimeout(const base::TimeDelta& timeout);
  void CancelAutoLaunchTimeout();

  
  SearchResultView* GetResultViewAt(int index);

  
  void Update();

  
  
  void ScheduleUpdate();

  
  void ForceAutoLaunchForTest();

  
  virtual void Layout() OVERRIDE;
  virtual int GetHeightForWidth(int w) const OVERRIDE;
  virtual void VisibilityChanged(
      views::View* starting_from, bool is_visible) OVERRIDE;

  
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

  
  virtual void ListItemsAdded(size_t start, size_t count) OVERRIDE;
  virtual void ListItemsRemoved(size_t start, size_t count) OVERRIDE;
  virtual void ListItemMoved(size_t index, size_t target_index) OVERRIDE;
  virtual void ListItemsChanged(size_t start, size_t count) OVERRIDE;

  SearchResultListViewDelegate* delegate_;  
  AppListViewDelegate* view_delegate_;  
  AppListModel::SearchResults* results_;  

  views::View* results_container_;
  views::View* auto_launch_indicator_;
  scoped_ptr<gfx::LinearAnimation> auto_launch_animation_;

  int last_visible_index_;
  int selected_index_;

  
  base::WeakPtrFactory<SearchResultListView> update_factory_;

  DISALLOW_COPY_AND_ASSIGN(SearchResultListView);
};

}  

#endif  
