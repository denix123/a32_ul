// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DESKTOP_BACKGROUND_DESKTOP_BACKGROUND_CONTROLLER_H_
#define ASH_DESKTOP_BACKGROUND_DESKTOP_BACKGROUND_CONTROLLER_H_

#include "ash/ash_export.h"
#include "ash/display/display_controller.h"
#include "ash/shell_observer.h"
#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/image/image_skia.h"

typedef unsigned int SkColor;

namespace aura {
class Window;
}

namespace ash {

enum WallpaperLayout {
  
  
  WALLPAPER_LAYOUT_CENTER,
  
  
  WALLPAPER_LAYOUT_CENTER_CROPPED,
  
  
  WALLPAPER_LAYOUT_STRETCH,
  
  WALLPAPER_LAYOUT_TILE
};

const SkColor kLoginWallpaperColor = 0xFEFEFE;

class DesktopBackgroundControllerObserver;
class WallpaperResizer;

class ASH_EXPORT DesktopBackgroundController
    : public DisplayController::Observer,
      public ShellObserver {
 public:
  class TestAPI;

  enum BackgroundMode {
    BACKGROUND_NONE,
    BACKGROUND_IMAGE,
  };

  DesktopBackgroundController();
  virtual ~DesktopBackgroundController();

  BackgroundMode desktop_background_mode() const {
    return desktop_background_mode_;
  }

  
  void AddObserver(DesktopBackgroundControllerObserver* observer);
  void RemoveObserver(DesktopBackgroundControllerObserver* observer);

  
  
  gfx::ImageSkia GetWallpaper() const;

  WallpaperLayout GetWallpaperLayout() const;

  
  
  
  
  bool SetWallpaperImage(const gfx::ImageSkia& image, WallpaperLayout layout);

  
  
  
  
  
  
  void CreateEmptyWallpaper();

  
  
  bool MoveDesktopToLockedContainer();

  
  
  bool MoveDesktopToUnlockedContainer();

  
  virtual void OnDisplayConfigurationChanged() OVERRIDE;

  
  virtual void OnRootWindowAdded(aura::Window* root_window) OVERRIDE;

  
  
  
  
  static gfx::Size GetMaxDisplaySizeInNative();

  
  
  
  bool WallpaperIsAlreadyLoaded(const gfx::ImageSkia& image,
                                bool compare_layouts,
                                WallpaperLayout layout) const;

 private:
  friend class DesktopBackgroundControllerTest;
  
  FRIEND_TEST_ALL_PREFIXES(DesktopBackgroundControllerTest, GetMaxDisplaySize);

  
  
  void SetDesktopBackgroundImageMode();

  
  
  void InstallDesktopController(aura::Window* root_window);

  
  
  void InstallDesktopControllerForAllWindows();

  
  
  bool ReparentBackgroundWidgets(int src_container, int dst_container);

  
  int GetBackgroundContainerId(bool locked);

  
  void NotifyAnimationFinished();

  
  void UpdateWallpaper();

  void set_wallpaper_reload_delay_for_test(bool value) {
    wallpaper_reload_delay_ = value;
  }

  
  bool locked_;

  BackgroundMode desktop_background_mode_;

  SkColor background_color_;

  ObserverList<DesktopBackgroundControllerObserver> observers_;

  
  scoped_ptr<WallpaperResizer> current_wallpaper_;

  gfx::Size current_max_display_size_;

  base::OneShotTimer<DesktopBackgroundController> timer_;

  int wallpaper_reload_delay_;

  DISALLOW_COPY_AND_ASSIGN(DesktopBackgroundController);
};

}  

#endif  
