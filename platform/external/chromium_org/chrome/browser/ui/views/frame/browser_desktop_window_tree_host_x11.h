// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_X11_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_X11_H_

#include "ui/views/widget/desktop_aura/desktop_window_tree_host_x11.h"
#include "chrome/browser/ui/views/frame/browser_desktop_window_tree_host.h"
#include "chrome/browser/ui/views/frame/global_menu_bar_x11.h"

class BrowserFrame;
class BrowserView;

namespace views {
class DesktopNativeWidgetAura;
}

class BrowserDesktopWindowTreeHostX11
    : public BrowserDesktopWindowTreeHost,
      public views::DesktopWindowTreeHostX11 {
 public:
  BrowserDesktopWindowTreeHostX11(
      views::internal::NativeWidgetDelegate* native_widget_delegate,
      views::DesktopNativeWidgetAura* desktop_native_widget_aura,
      BrowserView* browser_view,
      BrowserFrame* browser_frame);
  virtual ~BrowserDesktopWindowTreeHostX11();

 private:
  
  virtual DesktopWindowTreeHost* AsDesktopWindowTreeHost() OVERRIDE;
  virtual int GetMinimizeButtonOffset() const OVERRIDE;
  virtual bool UsesNativeSystemMenu() const OVERRIDE;

  
  virtual void Init(
      aura::Window* content_window,
      const views::Widget::InitParams& params) OVERRIDE;
  virtual void CloseNow() OVERRIDE;

  BrowserView* browser_view_;

  
  
  
  scoped_ptr<GlobalMenuBarX11> global_menu_bar_x11_;

  DISALLOW_COPY_AND_ASSIGN(BrowserDesktopWindowTreeHostX11);
};

#endif  
