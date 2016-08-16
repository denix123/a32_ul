// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_CONTENTS_VIEW_H_
#define UI_APP_LIST_VIEWS_CONTENTS_VIEW_H_

#include <map>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/pagination_model.h"
#include "ui/app_list/pagination_model_observer.h"
#include "ui/views/view.h"

namespace gfx {
class Rect;
}

namespace views {
class ViewModel;
}

namespace app_list {

class AppsGridView;
class ApplicationDragAndDropHost;
class AppListFolderItem;
class AppListMainView;
class AppListModel;
class AppListViewDelegate;
class AppsContainerView;
class ContentsSwitcherView;
class PaginationModel;
class SearchResultListView;
class StartPageView;

class APP_LIST_EXPORT ContentsView : public views::View,
                                     public PaginationModelObserver {
 public:
  
  
  enum NamedPage {
    NAMED_PAGE_APPS,
    NAMED_PAGE_SEARCH_RESULTS,
    NAMED_PAGE_START,
  };

  ContentsView(AppListMainView* app_list_main_view);
  virtual ~ContentsView();

  
  
  
  void InitNamedPages(AppListModel* model, AppListViewDelegate* view_delegate);

  
  void CancelDrag();

  
  
  void SetDragAndDropHostOfCurrentAppList(
      ApplicationDragAndDropHost* drag_and_drop_host);

  void SetContentsSwitcherView(ContentsSwitcherView* contents_switcher_view);

  
  
  
  void ShowSearchResults(bool show);
  bool IsShowingSearchResults() const;

  void ShowFolderContent(AppListFolderItem* folder);

  
  void SetActivePage(int page_index);

  
  int GetActivePageIndex() const;

  
  bool IsNamedPageActive(NamedPage named_page) const;

  
  
  int GetPageIndexForNamedPage(NamedPage named_page) const;

  int NumLauncherPages() const;

  void Prerender();

  AppsContainerView* apps_container_view() { return apps_container_view_; }
  StartPageView* start_page_view() { return start_page_view_; }
  SearchResultListView* search_results_view() { return search_results_view_; }
  views::View* GetPageView(int index);

  
  void AddBlankPageForTesting();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;

  
  virtual void TotalPagesChanged() OVERRIDE;
  virtual void SelectedPageChanged(int old_selected, int new_selected) OVERRIDE;
  virtual void TransitionStarted() OVERRIDE;
  virtual void TransitionChanged() OVERRIDE;

  
  const PaginationModel& pagination_model() { return pagination_model_; }

 private:
  
  
  void SetActivePageInternal(int page_index, bool show_search_results);

  
  void ActivePageChanged(bool show_search_results);

  
  
  gfx::Rect GetOffscreenPageBounds(int page_index) const;

  
  
  void UpdatePageBounds();

  
  
  
  
  int AddLauncherPage(views::View* view, int resource_id);

  
  
  
  
  int AddLauncherPage(views::View* view, int resource_id, NamedPage named_page);

  
  
  
  PaginationModel* GetAppsPaginationModel();

  
  AppsContainerView* apps_container_view_;
  SearchResultListView* search_results_view_;
  StartPageView* start_page_view_;

  AppListMainView* app_list_main_view_;     
  
  ContentsSwitcherView* contents_switcher_view_;

  scoped_ptr<views::ViewModel> view_model_;
  
  std::map<NamedPage, int> named_page_to_view_;

  
  int page_before_search_;

  
  PaginationModel pagination_model_;

  DISALLOW_COPY_AND_ASSIGN(ContentsView);
};

}  

#endif  
