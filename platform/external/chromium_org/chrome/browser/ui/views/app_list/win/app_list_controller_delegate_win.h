// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_APP_LIST_CONTROLLER_DELEGATE_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_APP_LIST_CONTROLLER_DELEGATE_WIN_H_

#include "chrome/browser/ui/app_list/app_list_controller_delegate_views.h"

class AppListControllerDelegateWin : public AppListControllerDelegateViews {
 public:
  explicit AppListControllerDelegateWin(AppListServiceViews* service);
  virtual ~AppListControllerDelegateWin();

  
  virtual bool ForceNativeDesktop() const OVERRIDE;
  virtual gfx::ImageSkia GetWindowIcon() OVERRIDE;

 private:
  
  virtual void FillLaunchParams(AppLaunchParams* params) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(AppListControllerDelegateWin);
};

#endif  