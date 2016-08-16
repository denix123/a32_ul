// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_LAUNCHER_APP_WINDOW_LAUNCHER_ITEM_CONTROLLER_H_
#define CHROME_BROWSER_UI_ASH_LAUNCHER_APP_WINDOW_LAUNCHER_ITEM_CONTROLLER_H_

#include <list>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/ui/ash/launcher/launcher_item_controller.h"
#include "ui/aura/window_observer.h"

namespace aura {
class Window;
}

namespace extensions {
class AppWindow;
}

namespace gfx {
class Image;
}

class ChromeLauncherController;

class AppWindowLauncherItemController : public LauncherItemController,
                                        public aura::WindowObserver {
 public:
  AppWindowLauncherItemController(Type type,
                                  const std::string& app_shelf_id,
                                  const std::string& app_id,
                                  ChromeLauncherController* controller);

  virtual ~AppWindowLauncherItemController();

  void AddAppWindow(extensions::AppWindow* app_window,
                    ash::ShelfItemStatus status);

  void RemoveAppWindowForWindow(aura::Window* window);

  void SetActiveWindow(aura::Window* window);

  const std::string& app_shelf_id() const { return app_shelf_id_; }

  
  virtual bool IsOpen() const OVERRIDE;
  virtual bool IsVisible() const OVERRIDE;
  virtual void Launch(ash::LaunchSource source, int event_flags) OVERRIDE;
  virtual bool Activate(ash::LaunchSource source) OVERRIDE;
  virtual ChromeLauncherAppMenuItems GetApplicationList(int event_flags)
      OVERRIDE;
  virtual bool ItemSelected(const ui::Event& eent) OVERRIDE;
  virtual base::string16 GetTitle() OVERRIDE;
  virtual ui::MenuModel* CreateContextMenu(aura::Window* root_window) OVERRIDE;
  virtual ash::ShelfMenuModel* CreateApplicationMenu(int event_flags) OVERRIDE;
  virtual bool IsDraggable() OVERRIDE;
  virtual bool ShouldShowTooltip() OVERRIDE;
  virtual void Close() OVERRIDE;

  
  virtual void OnWindowPropertyChanged(aura::Window* window,
                                       const void* key,
                                       intptr_t old) OVERRIDE;

  
  size_t app_window_count() const { return app_windows_.size(); }

  
  void ActivateIndexedApp(size_t index);

  
  
  void InstallApp();

 private:
  typedef std::list<extensions::AppWindow*> AppWindowList;

  void ShowAndActivateOrMinimize(extensions::AppWindow* app_window);

  
  
  void ActivateOrAdvanceToNextAppWindow(extensions::AppWindow* window_to_show);

  
  AppWindowList app_windows_;

  
  extensions::AppWindow* last_active_app_window_;

  
  
  const std::string app_shelf_id_;

  
  ScopedObserver<aura::Window, aura::WindowObserver> observed_windows_;

  DISALLOW_COPY_AND_ASSIGN(AppWindowLauncherItemController);
};

#endif  
