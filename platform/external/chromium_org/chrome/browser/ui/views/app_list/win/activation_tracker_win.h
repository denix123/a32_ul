// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_ACTIVATION_TRACKER_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_ACTIVATION_TRACKER_WIN_H_

#include "base/macros.h"
#include "base/timer/timer.h"
#include "ui/app_list/views/app_list_view_observer.h"

class AppListServiceWin;

class ActivationTrackerWin : public app_list::AppListViewObserver {
 public:
  explicit ActivationTrackerWin(AppListServiceWin* service);
  ~ActivationTrackerWin();

  
  virtual void OnActivationChanged(views::Widget* widget, bool active) OVERRIDE;

  void OnViewHidden();

 private:
  
  
  void MaybeDismissAppList();

  
  
  
  
  bool ShouldDismissAppList();

  AppListServiceWin* service_;  

  
  
  
  
  
  bool taskbar_has_focus_;

  
  
  
  base::RepeatingTimer<ActivationTrackerWin> timer_;

  DISALLOW_COPY_AND_ASSIGN(ActivationTrackerWin);
};

#endif  
