// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_H_

class BrowserFrame;
class BrowserView;
namespace gfx {
class Rect;
}
namespace views {
class DesktopNativeWidgetAura;
class DesktopWindowTreeHost;
namespace internal {
class NativeWidgetDelegate;
}
}

class BrowserDesktopWindowTreeHost {
 public:
  
  static BrowserDesktopWindowTreeHost* CreateBrowserDesktopWindowTreeHost(
      views::internal::NativeWidgetDelegate* native_widget_delegate,
      views::DesktopNativeWidgetAura* desktop_native_widget_aura,
      BrowserView* browser_view,
      BrowserFrame* browser_frame);

  virtual views::DesktopWindowTreeHost* AsDesktopWindowTreeHost() = 0;

  virtual int GetMinimizeButtonOffset() const = 0;

  
  
  virtual bool UsesNativeSystemMenu() const = 0;
};


#endif  
