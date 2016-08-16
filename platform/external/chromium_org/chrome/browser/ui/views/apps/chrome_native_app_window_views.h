// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APPS_CHROME_NATIVE_APP_WINDOW_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_APPS_CHROME_NATIVE_APP_WINDOW_VIEWS_H_

#include "base/memory/scoped_ptr.h"
#include "components/native_app_window/native_app_window_views.h"
#include "ui/views/context_menu_controller.h"

namespace apps {
class AppWindowFrameView;
}

#if defined(USE_ASH)
namespace ash {
class ImmersiveFullscreenController;
}
#endif

class ExtensionKeybindingRegistryViews;

namespace views {
class MenuRunner;
}

class ChromeNativeAppWindowViews
    : public native_app_window::NativeAppWindowViews,
      public views::ContextMenuController {
 public:
  ChromeNativeAppWindowViews();
  virtual ~ChromeNativeAppWindowViews();

  SkRegion* shape() { return shape_.get(); }

 protected:
  
  
  virtual void OnBeforeWidgetInit(views::Widget::InitParams* init_params,
                                  views::Widget* widget);

  virtual void InitializeDefaultWindow(
      const extensions::AppWindow::CreateParams& create_params);
  virtual void InitializePanelWindow(
      const extensions::AppWindow::CreateParams& create_params);
  virtual views::NonClientFrameView* CreateStandardDesktopAppFrame();

 private:
  FRIEND_TEST_ALL_PREFIXES(ShapedAppWindowTargeterTest,
                           ResizeInsetsWithinBounds);

  apps::AppWindowFrameView* CreateNonStandardAppFrame();

  
  virtual gfx::Rect GetRestoredBounds() const OVERRIDE;
  virtual ui::WindowShowState GetRestoredState() const OVERRIDE;
  virtual bool IsAlwaysOnTop() const OVERRIDE;

  
  virtual void ShowContextMenuForView(views::View* source,
                                      const gfx::Point& p,
                                      ui::MenuSourceType source_type) OVERRIDE;

  
  virtual gfx::ImageSkia GetWindowAppIcon() OVERRIDE;
  virtual gfx::ImageSkia GetWindowIcon() OVERRIDE;
  virtual views::NonClientFrameView* CreateNonClientFrameView(
      views::Widget* widget) OVERRIDE;
  virtual bool WidgetHasHitTestMask() const OVERRIDE;
  virtual void GetWidgetHitTestMask(gfx::Path* mask) const OVERRIDE;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;

  
  virtual void SetFullscreen(int fullscreen_types) OVERRIDE;
  virtual bool IsFullscreenOrPending() const OVERRIDE;
  virtual void UpdateBadgeIcon() OVERRIDE;
  virtual void UpdateShape(scoped_ptr<SkRegion> region) OVERRIDE;
  virtual bool HasFrameColor() const OVERRIDE;
  virtual SkColor ActiveFrameColor() const OVERRIDE;
  virtual SkColor InactiveFrameColor() const OVERRIDE;

  
  virtual void InitializeWindow(
      extensions::AppWindow* app_window,
      const extensions::AppWindow::CreateParams& create_params) OVERRIDE;

  
  bool is_fullscreen_;

  
  
  scoped_ptr<SkRegion> shape_;

  bool has_frame_color_;
  SkColor active_frame_color_;
  SkColor inactive_frame_color_;
  gfx::Size preferred_size_;

  
  scoped_ptr<ExtensionKeybindingRegistryViews> extension_keybinding_registry_;

#if defined(USE_ASH)
  
  
  
  
  scoped_ptr<ash::ImmersiveFullscreenController>
      immersive_fullscreen_controller_;
#endif  

  
  scoped_ptr<views::MenuRunner> menu_runner_;

  DISALLOW_COPY_AND_ASSIGN(ChromeNativeAppWindowViews);
};

#endif  
