// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_APP_LIST_SERVICE_VIEWS_H_
#define CHROME_BROWSER_UI_APP_LIST_APP_LIST_SERVICE_VIEWS_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/app_list/app_list_service_impl.h"
#include "chrome/browser/ui/app_list/app_list_shower_delegate.h"
#include "chrome/browser/ui/app_list/app_list_shower_views.h"

class AppListControllerDelegate;

class AppListServiceViews : public AppListServiceImpl,
                            public AppListShowerDelegate {
 public:
  explicit AppListServiceViews(
      scoped_ptr<AppListControllerDelegate> controller_delegate);
  virtual ~AppListServiceViews();

  
  
  void set_can_dismiss(bool can_dismiss) { can_dismiss_ = can_dismiss; }

  AppListShower& shower() { return shower_; }

  
  
  virtual void OnViewBeingDestroyed();

  
  virtual void Init(Profile* initial_profile) OVERRIDE;
  virtual void CreateForProfile(Profile* requested_profile) OVERRIDE;
  virtual void ShowForProfile(Profile* requested_profile) OVERRIDE;
  virtual void DismissAppList() OVERRIDE;
  virtual bool IsAppListVisible() const OVERRIDE;
  virtual gfx::NativeWindow GetAppListWindow() OVERRIDE;
  virtual Profile* GetCurrentAppListProfile() OVERRIDE;
  virtual AppListControllerDelegate* GetControllerDelegate() OVERRIDE;

  
  virtual void DestroyAppList() OVERRIDE;

  
  virtual AppListViewDelegate* GetViewDelegateForCreate() OVERRIDE;

 private:
  
  AppListShower shower_;

  bool can_dismiss_;
  scoped_ptr<AppListControllerDelegate> controller_delegate_;

  DISALLOW_COPY_AND_ASSIGN(AppListServiceViews);
};

#endif  
