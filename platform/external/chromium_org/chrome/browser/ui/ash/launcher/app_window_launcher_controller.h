// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_LAUNCHER_APP_WINDOW_LAUNCHER_CONTROLLER_H_
#define CHROME_BROWSER_UI_ASH_LAUNCHER_APP_WINDOW_LAUNCHER_CONTROLLER_H_

#include <list>
#include <map>
#include <string>

#include "extensions/browser/app_window/app_window_registry.h"
#include "ui/aura/window_observer.h"
#include "ui/wm/public/activation_change_observer.h"

namespace aura {

class Window;

namespace client {
class ActivationClient;
}
}

namespace extensions {
class AppWindow;
}

class ChromeLauncherController;
class Profile;
class AppWindowLauncherItemController;

class AppWindowLauncherController
    : public extensions::AppWindowRegistry::Observer,
      public aura::WindowObserver,
      public aura::client::ActivationChangeObserver {
 public:
  explicit AppWindowLauncherController(ChromeLauncherController* owner);
  virtual ~AppWindowLauncherController();

  
  
  virtual void ActiveUserChanged(const std::string& user_email) {}

  
  
  virtual void AdditionalUserAddedToSession(Profile* profile);

  
  virtual void OnAppWindowIconChanged(
      extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowShown(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowHidden(extensions::AppWindow* app_window) OVERRIDE;

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_active,
                                 aura::Window* lost_active) OVERRIDE;

 protected:
  
  void RegisterApp(extensions::AppWindow* app_window);

  
  void UnregisterApp(aura::Window* window);

  
  bool IsRegisteredApp(aura::Window* window);

 private:
  typedef std::map<std::string, AppWindowLauncherItemController*>
      AppControllerMap;
  typedef std::map<aura::Window*, std::string> WindowToAppShelfIdMap;

  AppWindowLauncherItemController* ControllerForWindow(aura::Window* window);

  ChromeLauncherController* owner_;
  
  
  
  std::set<extensions::AppWindowRegistry*> registry_;
  aura::client::ActivationClient* activation_client_;

  
  AppControllerMap app_controller_map_;

  
  WindowToAppShelfIdMap window_to_app_shelf_id_map_;

  DISALLOW_COPY_AND_ASSIGN(AppWindowLauncherController);
};

#endif  
