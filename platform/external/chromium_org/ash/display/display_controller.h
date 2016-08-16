// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_DISPLAY_CONTROLLER_H_
#define ASH_DISPLAY_DISPLAY_CONTROLLER_H_

#include <map>
#include <vector>

#include "ash/ash_export.h"
#include "ash/display/display_manager.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "ui/aura/window.h"
#include "ui/aura/window_tree_host_observer.h"
#include "ui/gfx/display_observer.h"
#include "ui/gfx/point.h"

namespace aura {
class Display;
class WindowTreeHost;
}

namespace base {
class Value;
template <typename T> class JSONValueConverter;
}

namespace gfx {
class Display;
class Insets;
}

namespace ash {
class AshWindowTreeHost;
struct AshWindowTreeHostInitParams;
class CursorWindowController;
class DisplayInfo;
class DisplayManager;
class FocusActivationStore;
class MirrorWindowController;
class RootWindowController;

class ASH_EXPORT DisplayController : public gfx::DisplayObserver,
                                     public aura::WindowTreeHostObserver,
                                     public DisplayManager::Delegate {
 public:
  class ASH_EXPORT Observer {
   public:
    
    
    virtual void OnDisplaysInitialized() {}

    
    
    virtual void OnDisplayConfigurationChanging() {}

    
    
    virtual void OnDisplayConfigurationChanged() {};

   protected:
    virtual ~Observer() {}
  };

  DisplayController();
  virtual ~DisplayController();

  void Start();
  void Shutdown();

  
  
  static int64 GetPrimaryDisplayId();

  CursorWindowController* cursor_window_controller() {
    return cursor_window_controller_.get();
  }

  MirrorWindowController* mirror_window_controller() {
    return mirror_window_controller_.get();
  }

  
  
  void CreatePrimaryHost(const AshWindowTreeHostInitParams& init_params);

  
  void InitDisplays();

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  aura::Window* GetPrimaryRootWindow();

  
  aura::Window* GetRootWindowForDisplayId(int64 id);

  
  void ToggleMirrorMode();

  
  void SwapPrimaryDisplay();

  
  
  void SetPrimaryDisplayId(int64 id);

  
  
  void SetPrimaryDisplay(const gfx::Display& display);

  
  void CloseChildWindows();

  
  
  aura::Window::Windows GetAllRootWindows();

  
  
  std::vector<RootWindowController*> GetAllRootWindowControllers();

  
  
  gfx::Insets GetOverscanInsets(int64 display_id) const;
  void SetOverscanInsets(int64 display_id, const gfx::Insets& insets_in_dip);

  
  
  void EnsurePointerInDisplays();

  
  bool UpdateWorkAreaOfDisplayNearestWindow(const aura::Window* window,
                                            const gfx::Insets& insets);
  
  virtual void OnDisplayAdded(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  
  virtual void OnHostResized(const aura::WindowTreeHost* host) OVERRIDE;

  
  virtual void CreateOrUpdateNonDesktopDisplay(const DisplayInfo& info)
      OVERRIDE;
  virtual void CloseNonDesktopDisplay() OVERRIDE;
  virtual void PreDisplayConfigurationChange(bool clear_focus) OVERRIDE;
  virtual void PostDisplayConfigurationChange() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(DisplayControllerTest, BoundsUpdated);
  FRIEND_TEST_ALL_PREFIXES(DisplayControllerTest, SecondaryDisplayLayout);
  friend class DisplayManager;
  friend class MirrorWindowController;

  
  
  AshWindowTreeHost* AddWindowTreeHostForDisplay(
      const gfx::Display& display,
      const AshWindowTreeHostInitParams& params);

  void OnFadeOutForSwapDisplayFinished();

  void SetMirrorModeAfterAnimation(bool mirror);

  void UpdateHostWindowNames();

  class DisplayChangeLimiter {
   public:
    DisplayChangeLimiter();

    
    void SetThrottleTimeout(int64 throttle_ms);

    bool IsThrottled() const;

   private:
    
    base::Time throttle_timeout_;

    DISALLOW_COPY_AND_ASSIGN(DisplayChangeLimiter);
  };

  
  
  scoped_ptr<DisplayChangeLimiter> limiter_;

  typedef std::map<int64, AshWindowTreeHost*> WindowTreeHostMap;
  
  WindowTreeHostMap window_tree_hosts_;

  ObserverList<Observer> observers_;

  
  
  AshWindowTreeHost* primary_tree_host_for_replace_;

  scoped_ptr<FocusActivationStore> focus_activation_store_;

  scoped_ptr<CursorWindowController> cursor_window_controller_;
  scoped_ptr<MirrorWindowController> mirror_window_controller_;

  
  
  
  gfx::Point cursor_location_in_native_coords_for_restore_;

  base::WeakPtrFactory<DisplayController> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DisplayController);
};

}  

#endif  
