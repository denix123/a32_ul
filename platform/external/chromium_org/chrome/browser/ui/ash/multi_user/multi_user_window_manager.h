// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_MULTI_USER_MULTI_USER_WINDOW_MANAGER_H_
#define CHROME_BROWSER_UI_ASH_MULTI_USER_MULTI_USER_WINDOW_MANAGER_H_

#include <map>
#include <set>
#include <string>

class Browser;

namespace content {
class BrowserContext;
}

namespace aura {
class Window;
}

namespace chrome {

class MultiUserWindowManagerChromeOS;

class MultiUserWindowManager {
 public:
  
  class Observer {
   public:
    
    
    virtual void OnOwnerEntryAdded(aura::Window* window) {}
    
    virtual void OnOwnerEntryChanged(aura::Window* window) {}
    
    
    virtual void OnOwnerEntryRemoved(aura::Window* window) {}

   protected:
    virtual ~Observer() {}
  };

  
  enum MultiProfileMode {
    MULTI_PROFILE_MODE_UNINITIALIZED,  
    MULTI_PROFILE_MODE_OFF,            
    MULTI_PROFILE_MODE_SEPARATED,      
    MULTI_PROFILE_MODE_MIXED           
  };

  
  
  
  static MultiUserWindowManager* CreateInstance();

  
  
  static MultiUserWindowManager* GetInstance();

  
  
  
  static MultiProfileMode GetMultiProfileMode();

  
  
  
  static bool ShouldShowAvatar(aura::Window* window);

  
  static void DeleteInstance();

  
  
  static void SetInstanceForTest(MultiUserWindowManager* instance,
                                 MultiProfileMode mode);

  
  
  
  
  
  virtual void SetWindowOwner(
      aura::Window* window, const std::string& user_id) = 0;

  
  
  virtual const std::string& GetWindowOwner(aura::Window* window) const = 0;

  
  
  
  
  
  
  virtual void ShowWindowForUser(
      aura::Window* window, const std::string& user_id) = 0;

  
  virtual bool AreWindowsSharedAmongUsers() const = 0;

  
  virtual void GetOwnersOfVisibleWindows(
      std::set<std::string>* user_ids) const = 0;

  
  
  virtual bool IsWindowOnDesktopOfUser(aura::Window* window,
                                       const std::string& user_id) const = 0;

  
  
  virtual const std::string& GetUserPresentingWindow(
      aura::Window* window) const = 0;

  
  
  
  
  
  virtual void AddUser(content::BrowserContext* profile) = 0;

  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

 protected:
  virtual ~MultiUserWindowManager() {}

 private:
  
  static MultiProfileMode multi_user_mode_;
};

}  

#endif  
