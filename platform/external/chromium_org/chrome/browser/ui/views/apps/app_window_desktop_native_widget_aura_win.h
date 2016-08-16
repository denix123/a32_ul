// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_APP_WINDOW_DESKTOP_NATIVE_WIDGET_AURA_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_APP_WINDOW_DESKTOP_NATIVE_WIDGET_AURA_WIN_H_

#include "base/basictypes.h"
#include "ui/views/widget/desktop_aura/desktop_native_widget_aura.h"

class BrowserFrame;
class BrowserView;
class ChromeNativeAppWindowViewsWin;

namespace wm {
class VisibilityController;
}

class AppWindowDesktopNativeWidgetAuraWin
    : public views::DesktopNativeWidgetAura {
 public:
  explicit AppWindowDesktopNativeWidgetAuraWin(
      ChromeNativeAppWindowViewsWin* app_window);

 protected:
  virtual ~AppWindowDesktopNativeWidgetAuraWin();

  
  virtual void InitNativeWidget(
      const views::Widget::InitParams& params) OVERRIDE;

 private:
  
  ChromeNativeAppWindowViewsWin* app_window_;

  DISALLOW_COPY_AND_ASSIGN(AppWindowDesktopNativeWidgetAuraWin);
};

#endif  
