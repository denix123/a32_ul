// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_MULTI_USER_MULTI_USER_WINDOW_MANAGER_CHROMEOS_H_
#define CHROME_BROWSER_UI_ASH_MULTI_USER_MULTI_USER_WINDOW_MANAGER_CHROMEOS_H_

#include <map>
#include <string>

#include "ash/session/session_state_observer.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/ui/ash/multi_user/multi_user_window_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/aura/window_observer.h"
#include "ui/wm/core/transient_window_observer.h"

class Browser;
class MultiUserNotificationBlockerChromeOS;
class MultiUserNotificationBlockerChromeOSTest;

namespace content {
class BrowserContext;
}

namespace aura {
class Window;
}  

namespace ash {
namespace test {
class MultiUserWindowManagerChromeOSTest;
}  
}  

namespace chrome {

class AppObserver;
class UserSwichAnimatorChromeOS;

// overwritten to match new ways of doing this.
class MultiUserWindowManagerChromeOS
    : public MultiUserWindowManager,
      public ash::SessionStateObserver,
      public aura::WindowObserver,
      public content::NotificationObserver,
      public wm::TransientWindowObserver {
 public:
  
  enum AnimationSpeed {
    ANIMATION_SPEED_NORMAL,   
    ANIMATION_SPEED_FAST,     
    ANIMATION_SPEED_DISABLED  
  };

  
  explicit MultiUserWindowManagerChromeOS(const std::string& active_user_id);
  virtual ~MultiUserWindowManagerChromeOS();

  
  virtual void SetWindowOwner(
      aura::Window* window, const std::string& user_id) OVERRIDE;
  virtual const std::string& GetWindowOwner(
      aura::Window* window) const OVERRIDE;
  virtual void ShowWindowForUser(
      aura::Window* window, const std::string& user_id) OVERRIDE;
  virtual bool AreWindowsSharedAmongUsers() const OVERRIDE;
  virtual void GetOwnersOfVisibleWindows(
      std::set<std::string>* user_ids) const OVERRIDE;
  virtual bool IsWindowOnDesktopOfUser(
      aura::Window* window,
      const std::string& user_id) const OVERRIDE;
  virtual const std::string& GetUserPresentingWindow(
      aura::Window* window) const OVERRIDE;
  virtual void AddUser(content::BrowserContext* context) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;

  
  virtual void ActiveUserChanged(const std::string& user_id) OVERRIDE;

  
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;
  virtual void OnWindowVisibilityChanging(aura::Window* window,
                                          bool visible) OVERRIDE;
  virtual void OnWindowVisibilityChanged(aura::Window* window,
                                         bool visible) OVERRIDE;

  
  virtual void OnTransientChildAdded(aura::Window* window,
                                     aura::Window* transient) OVERRIDE;
  virtual void OnTransientChildRemoved(aura::Window* window,
                                       aura::Window* transient) OVERRIDE;

  
  virtual void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) OVERRIDE;

  
  void SetAnimationSpeedForTest(AnimationSpeed speed);

  
  bool IsAnimationRunningForTest();

  
  const std::string& GetCurrentUserForTest() const;

 protected:
  friend class UserSwichAnimatorChromeOS;

  class WindowEntry {
   public:
    explicit WindowEntry(const std::string& user_id)
        : owner_(user_id),
          show_for_user_(user_id),
          show_(true) {}
    virtual ~WindowEntry() {}

    
    const std::string& owner() const { return owner_; }

    
    const std::string& show_for_user() const { return show_for_user_; }

    
    bool show() const { return show_; }

    
    
    void set_show_for_user(const std::string& user_id) {
      show_for_user_ = user_id.empty() ? owner_ : user_id;
    }

    
    void set_show(bool show) { show_ = show; }

   private:
    
    const std::string owner_;

    
    std::string show_for_user_;

    
    bool show_;

    DISALLOW_COPY_AND_ASSIGN(WindowEntry);
  };

  typedef std::map<aura::Window*, WindowEntry*> WindowToEntryMap;

  
  
  bool ShowWindowForUserIntern(aura::Window* window,
                               const std::string& user_id);

  
  
  
  
  
  
  
  void SetWindowVisibility(aura::Window* window,
                           bool visible,
                           int animation_time_in_ms);

  const WindowToEntryMap& window_to_entry() { return window_to_entry_; }
  MultiUserNotificationBlockerChromeOS* notification_blocker() {
    return notification_blocker_.get();
  }

 private:
  friend class ::MultiUserNotificationBlockerChromeOSTest;
  friend class ash::test::MultiUserWindowManagerChromeOSTest;

  typedef std::map<std::string, AppObserver*> UserIDToAppWindowObserver;
  typedef std::map<aura::Window*, bool> TransientWindowToVisibility;

  
  void AddBrowserWindow(Browser* browser);

  
  
  
  void ShowWithTransientChildrenRecursive(aura::Window* window,
                                          int animation_time_in_ms);

  
  
  aura::Window* GetOwningWindowInTransientChain(aura::Window* window) const;

  
  
  
  void AddTransientOwnerRecursive(aura::Window* window,
                                  aura::Window* owning_parent);

  
  
  void RemoveTransientOwnerRecursive(aura::Window* window);

  
  void SetWindowVisible(aura::Window* window,
                        bool visible,
                        int aimation_time_in_ms);

  
  
  int GetAdjustedAnimationTimeInMS(int default_time_in_ms) const;

  
  
  WindowToEntryMap window_to_entry_;

  
  UserIDToAppWindowObserver user_id_to_app_observer_;

  
  ObserverList<Observer> observers_;

  
  TransientWindowToVisibility transient_window_to_visibility_;

  
  
  
  std::string current_user_id_;

  
  
  scoped_ptr<MultiUserNotificationBlockerChromeOS> notification_blocker_;

  
  content::NotificationRegistrar registrar_;

  
  bool suppress_visibility_changes_;

  
  
  static MultiProfileMode multi_user_mode_;

  
  AnimationSpeed animation_speed_;

  
  scoped_ptr<UserSwichAnimatorChromeOS> animation_;

  DISALLOW_COPY_AND_ASSIGN(MultiUserWindowManagerChromeOS);
};

}  

#endif  
