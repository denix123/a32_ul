// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ROOT_WINDOW_CONTROLLER_H_
#define ASH_ROOT_WINDOW_CONTROLLER_H_

#include <map>

#include "ash/ash_export.h"
#include "ash/shelf/shelf_types.h"
#include "ash/shell_observer.h"
#include "ash/system/user/login_status.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window.h"
#include "ui/aura/window_tree_host.h"
#include "ui/base/ui_base_types.h"

class SkBitmap;

namespace aura {
class EventFilter;
class Window;
}

namespace gfx {
class Point;
}

namespace keyboard {
class KeyboardController;
}

namespace ui {
class EventHandler;
}

namespace views {
class Widget;
}

namespace wm {
class InputMethodEventFilter;
class RootWindowEventFilter;
class ScopedCaptureClient;
}

namespace ash {
class AshWindowTreeHost;
class AlwaysOnTopController;
class AnimatingDesktopController;
class DesktopBackgroundWidgetController;
class DockedWindowLayoutManager;
class PanelLayoutManager;
class RootWindowLayoutManager;
class ScreenDimmer;
class ShelfLayoutManager;
class ShelfWidget;
class StackingController;
class StatusAreaWidget;
class SystemBackgroundController;
class SystemModalContainerLayoutManager;
class SystemTray;
class TouchHudDebug;
class TouchHudProjection;
class WorkspaceController;

#if defined(OS_CHROMEOS)
class BootSplashScreen;
class AshTouchExplorationManager;
#endif

class ASH_EXPORT RootWindowController : public ShellObserver {
 public:
  
  static void CreateForPrimaryDisplay(AshWindowTreeHost* host);

  
  static void CreateForSecondaryDisplay(AshWindowTreeHost* host);

  
  
  static void CreateForVirtualKeyboardDisplay(AshWindowTreeHost* host);

  
  
  
  
  static RootWindowController* ForShelf(const aura::Window* window);

  
  static RootWindowController* ForWindow(const aura::Window* window);

  
  static RootWindowController* ForTargetRootWindow();

  
  static aura::Window* GetContainerForWindow(aura::Window* window);

  virtual ~RootWindowController();

  AshWindowTreeHost* ash_host() { return ash_host_.get(); }
  const AshWindowTreeHost* ash_host() const { return ash_host_.get(); }

  aura::WindowTreeHost* GetHost();
  const aura::WindowTreeHost* GetHost() const;
  aura::Window* GetRootWindow();
  const aura::Window* GetRootWindow() const;

  RootWindowLayoutManager* root_window_layout() { return root_window_layout_; }

  WorkspaceController* workspace_controller() {
    return workspace_controller_.get();
  }

  AlwaysOnTopController* always_on_top_controller() {
    return always_on_top_controller_.get();
  }

  ScreenDimmer* screen_dimmer() { return screen_dimmer_.get(); }

  
  
  ShelfWidget* shelf() { return shelf_.get(); }

  
  TouchHudDebug* touch_hud_debug() const {
    return touch_hud_debug_;
  }
  TouchHudProjection* touch_hud_projection() const {
    return touch_hud_projection_;
  }

  
  
  
  
  void set_touch_hud_debug(TouchHudDebug* hud) {
    touch_hud_debug_ = hud;
  }
  void set_touch_hud_projection(TouchHudProjection* hud) {
    touch_hud_projection_ = hud;
  }

  DesktopBackgroundWidgetController* wallpaper_controller() {
    return wallpaper_controller_.get();
  }
  void SetWallpaperController(DesktopBackgroundWidgetController* controller);
  AnimatingDesktopController* animating_wallpaper_controller() {
    return animating_wallpaper_controller_.get();
  }
  void SetAnimatingWallpaperController(AnimatingDesktopController* controller);

  
  
  ShelfLayoutManager* GetShelfLayoutManager();

  
  
  
  SystemTray* GetSystemTray();

  
  
  void ShowContextMenu(const gfx::Point& location_in_screen,
                       ui::MenuSourceType source_type);

  
  
  
  
  
  
  
  SystemModalContainerLayoutManager* GetSystemModalLayoutManager(
      aura::Window* window);

  aura::Window* GetContainer(int container_id);
  const aura::Window* GetContainer(int container_id) const;

  
  void ShowShelf();

  
  void OnShelfCreated();

  
  
  void UpdateAfterLoginStatusChange(user::LoginStatus status);

  
  
  
  void HandleInitialDesktopBackgroundAnimationStarted();

  
  
  
  
  void OnWallpaperAnimationFinished(views::Widget* widget);

  
  
  
  
  void Shutdown();

  
  void CloseChildWindows();

  
  void MoveWindowsTo(aura::Window* dest);

  
  void UpdateShelfVisibility();

  
  void InitTouchHuds();

  
  
  const aura::Window* GetWindowForFullscreenMode() const;

  
  void ActivateKeyboard(keyboard::KeyboardController* keyboard_controller);

  
  void DeactivateKeyboard(keyboard::KeyboardController* keyboard_controller);

  
  bool IsVirtualKeyboardWindow(aura::Window* window);

 private:
  explicit RootWindowController(AshWindowTreeHost* host);
  enum RootWindowType {
    PRIMARY,
    SECONDARY
  };

  
  
  
  void Init(RootWindowType root_window_type, bool first_run_after_boot);

  void InitLayoutManagers();

  
  
  void CreateSystemBackground(bool is_first_run_after_boot);

  
  
  void CreateContainersInRootWindow(aura::Window* root_window);

  
  void EnableTouchHudProjection();

  
  void DisableTouchHudProjection();

  
  virtual void OnLoginStateChanged(user::LoginStatus status) OVERRIDE;
  virtual void OnTouchHudProjectionToggled(bool enabled) OVERRIDE;

  scoped_ptr<AshWindowTreeHost> ash_host_;
  RootWindowLayoutManager* root_window_layout_;

  scoped_ptr<StackingController> stacking_controller_;

  
  scoped_ptr<ShelfWidget> shelf_;

  
  
  
  
  
  scoped_ptr<aura::Window> mouse_event_target_;

  
  DockedWindowLayoutManager* docked_layout_manager_;

  
  PanelLayoutManager* panel_layout_manager_;

  scoped_ptr<SystemBackgroundController> system_background_;

#if defined(OS_CHROMEOS)
  scoped_ptr<BootSplashScreen> boot_splash_screen_;
  
  
  scoped_ptr<AshTouchExplorationManager> touch_exploration_manager_;
#endif

  scoped_ptr<ScreenDimmer> screen_dimmer_;
  scoped_ptr<WorkspaceController> workspace_controller_;
  scoped_ptr<AlwaysOnTopController> always_on_top_controller_;

  
  
  TouchHudDebug* touch_hud_debug_;
  TouchHudProjection* touch_hud_projection_;

  
  scoped_ptr<ui::EventHandler> panel_container_handler_;

  scoped_ptr<DesktopBackgroundWidgetController> wallpaper_controller_;
  scoped_ptr<AnimatingDesktopController> animating_wallpaper_controller_;
  scoped_ptr< ::wm::ScopedCaptureClient> capture_client_;

  DISALLOW_COPY_AND_ASSIGN(RootWindowController);
};


ASH_EXPORT RootWindowController* GetRootWindowController(
    const aura::Window* root_window);

}  

#endif  
