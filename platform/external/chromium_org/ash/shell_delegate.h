// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELL_DELEGATE_H_
#define ASH_SHELL_DELEGATE_H_

#include <string>

#include "ash/ash_export.h"
#include "ash/shell.h"
#include "base/callback.h"
#include "base/strings/string16.h"

namespace app_list {
class AppListViewDelegate;
}

namespace aura {
class RootWindow;
class Window;
}

namespace content {
class BrowserContext;
}

namespace ui {
class MenuModel;
}

namespace views {
class Widget;
}

namespace keyboard {
class KeyboardControllerProxy;
}

namespace ash {

class AccessibilityDelegate;
class MediaDelegate;
class NewWindowDelegate;
class SessionStateDelegate;
class ShelfDelegate;
class ShelfItemDelegate;
class ShelfModel;
class SystemTrayDelegate;
class UserWallpaperDelegate;
struct ShelfItem;

class ASH_EXPORT VirtualKeyboardStateObserver {
 public:
  
  virtual void OnVirtualKeyboardStateChanged(bool activated) {}

 protected:
  virtual ~VirtualKeyboardStateObserver() {}
};

class ASH_EXPORT ShellDelegate {
 public:
  
  virtual ~ShellDelegate() {}

  
  
  
  virtual bool IsFirstRunAfterBoot() const = 0;

  
  virtual bool IsMultiProfilesEnabled() const = 0;

  
  
  virtual bool IsIncognitoAllowed() const = 0;

  
  virtual bool IsRunningInForcedAppMode() const = 0;

  
  virtual bool IsMultiAccountEnabled() const = 0;

  
  
  virtual void PreInit() = 0;

  
  
  virtual void PreShutdown() = 0;

  
  virtual void Exit() = 0;

  
  virtual keyboard::KeyboardControllerProxy*
      CreateKeyboardControllerProxy() = 0;

  
  virtual void VirtualKeyboardActivated(bool activated) = 0;

  
  virtual void AddVirtualKeyboardStateObserver(
      VirtualKeyboardStateObserver* observer) = 0;
  virtual void RemoveVirtualKeyboardStateObserver(
      VirtualKeyboardStateObserver* observer) = 0;

  
  
  virtual content::BrowserContext* GetActiveBrowserContext() = 0;

  
  
  virtual app_list::AppListViewDelegate* GetAppListViewDelegate() = 0;

  
  
  virtual ShelfDelegate* CreateShelfDelegate(ShelfModel* model) = 0;

  
  virtual SystemTrayDelegate* CreateSystemTrayDelegate() = 0;

  
  virtual UserWallpaperDelegate* CreateUserWallpaperDelegate() = 0;

  
  virtual SessionStateDelegate* CreateSessionStateDelegate() = 0;

  
  virtual AccessibilityDelegate* CreateAccessibilityDelegate() = 0;

  
  virtual NewWindowDelegate* CreateNewWindowDelegate() = 0;

  
  virtual MediaDelegate* CreateMediaDelegate() = 0;

  
  
  
  virtual ui::MenuModel* CreateContextMenu(
      aura::Window* root_window,
      ash::ShelfItemDelegate* item_delegate,
      ash::ShelfItem* item) = 0;

  
  virtual GPUSupport* CreateGPUSupport() = 0;

  
  virtual base::string16 GetProductName() const = 0;
};

}  

#endif  
