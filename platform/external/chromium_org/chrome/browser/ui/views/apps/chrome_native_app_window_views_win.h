// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_CHROME_NATIVE_APP_WINDOW_VIEWS_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_CHROME_NATIVE_APP_WINDOW_VIEWS_WIN_H_

#include "chrome/browser/ui/views/apps/chrome_native_app_window_views.h"

namespace web_app {
struct ShortcutInfo;
}

class GlassAppWindowFrameViewWin;

class ChromeNativeAppWindowViewsWin : public ChromeNativeAppWindowViews {
 public:
  ChromeNativeAppWindowViewsWin();

  GlassAppWindowFrameViewWin* glass_frame_view() {
    return glass_frame_view_;
  }

 private:
  void ActivateParentDesktopIfNecessary();

  void OnShortcutInfoLoaded(
      const web_app::ShortcutInfo& shortcut_info);

  HWND GetNativeAppWindowHWND() const;
  bool IsRunningInAsh();
  void EnsureCaptionStyleSet();

  
  virtual void OnBeforeWidgetInit(views::Widget::InitParams* init_params,
                                  views::Widget* widget) OVERRIDE;
  virtual void InitializeDefaultWindow(
      const extensions::AppWindow::CreateParams& create_params) OVERRIDE;
  virtual views::NonClientFrameView* CreateStandardDesktopAppFrame() OVERRIDE;

  
  virtual void Show() OVERRIDE;
  virtual void Activate() OVERRIDE;

  
  virtual void UpdateShelfMenu() OVERRIDE;

  
  
  
  
  GlassAppWindowFrameViewWin* glass_frame_view_;

  
  
  base::string16 app_model_id_;

  base::WeakPtrFactory<ChromeNativeAppWindowViewsWin> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromeNativeAppWindowViewsWin);
};

#endif  
