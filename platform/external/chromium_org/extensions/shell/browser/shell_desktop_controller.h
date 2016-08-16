// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_SHELL_DESKTOP_CONTROLLER_H_
#define EXTENSIONS_SHELL_BROWSER_SHELL_DESKTOP_CONTROLLER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/shell/browser/desktop_controller.h"
#include "ui/aura/client/window_tree_client.h"
#include "ui/aura/window_tree_host_observer.h"

#if defined(OS_CHROMEOS)
#include "chromeos/dbus/power_manager_client.h"
#include "ui/display/chromeos/display_configurator.h"
#endif

namespace aura {
class TestScreen;
class Window;
class WindowTreeHost;
namespace client {
class DefaultCaptureClient;
class FocusClient;
}
}

namespace content {
class BrowserContext;
}

namespace gfx {
class Size;
}

#if defined(OS_CHROMEOS)
namespace ui {
class UserActivityPowerManagerNotifier;
}
#endif

namespace wm {
class CompoundEventFilter;
class CursorManager;
class InputMethodEventFilter;
class UserActivityDetector;
}

namespace extensions {
class AppWindowClient;
class Extension;

class ShellDesktopController : public DesktopController,
                               public aura::client::WindowTreeClient,
#if defined(OS_CHROMEOS)
                               public chromeos::PowerManagerClient::Observer,
                               public ui::DisplayConfigurator::Observer,
#endif
                               public aura::WindowTreeHostObserver {
 public:
  ShellDesktopController();
  virtual ~ShellDesktopController();

  
  virtual aura::WindowTreeHost* GetHost() OVERRIDE;
  virtual AppWindow* CreateAppWindow(content::BrowserContext* context,
                                     const Extension* extension) OVERRIDE;
  virtual void AddAppWindow(aura::Window* window) OVERRIDE;
  virtual void CloseAppWindows() OVERRIDE;

  
  virtual aura::Window* GetDefaultParent(aura::Window* context,
                                         aura::Window* window,
                                         const gfx::Rect& bounds) OVERRIDE;

#if defined(OS_CHROMEOS)
  
  virtual void PowerButtonEventReceived(bool down,
                                        const base::TimeTicks& timestamp)
      OVERRIDE;

  
  virtual void OnDisplayModeChanged(const std::vector<
      ui::DisplayConfigurator::DisplayState>& displays) OVERRIDE;
#endif

  
  virtual void OnHostCloseRequested(const aura::WindowTreeHost* host) OVERRIDE;

 protected:
  
  
  virtual void InitWindowManager();

 private:
  
  void CreateRootWindow();

  
  void DestroyRootWindow();

  
  
  gfx::Size GetPrimaryDisplaySize();

#if defined(OS_CHROMEOS)
  scoped_ptr<ui::DisplayConfigurator> display_configurator_;
#endif

  scoped_ptr<aura::TestScreen> test_screen_;

  scoped_ptr<aura::WindowTreeHost> host_;

  scoped_ptr<wm::CompoundEventFilter> root_window_event_filter_;

  scoped_ptr<aura::client::DefaultCaptureClient> capture_client_;

  scoped_ptr<wm::InputMethodEventFilter> input_method_filter_;

  scoped_ptr<aura::client::FocusClient> focus_client_;

  scoped_ptr<wm::CursorManager> cursor_manager_;

  scoped_ptr<wm::UserActivityDetector> user_activity_detector_;
#if defined(OS_CHROMEOS)
  scoped_ptr<ui::UserActivityPowerManagerNotifier> user_activity_notifier_;
#endif

  scoped_ptr<AppWindowClient> app_window_client_;

  
  AppWindow* app_window_;  

  DISALLOW_COPY_AND_ASSIGN(ShellDesktopController);
};

}  

#endif  
