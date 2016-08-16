// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APPS_APP_LIFETIME_MONITOR_H_
#define APPS_APP_LIFETIME_MONITOR_H_

#include <string>
#include <vector>

#include "base/observer_list.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/app_window/app_window_registry.h"

namespace extensions {
class Extension;
}

class Profile;

namespace apps {

class AppLifetimeMonitor : public KeyedService,
                           public content::NotificationObserver,
                           public extensions::AppWindowRegistry::Observer {
 public:
  class Observer {
   public:
    
    virtual void OnAppStart(Profile* profile, const std::string& app_id) {}
    
    virtual void OnAppActivated(Profile* profile, const std::string& app_id) {}
    
    virtual void OnAppDeactivated(Profile* profile, const std::string& app_id) {
    }
    
    virtual void OnAppStop(Profile* profile, const std::string& app_id) {}
    
    
    
    virtual void OnChromeTerminating() {}

   protected:
    virtual ~Observer() {}
  };

  explicit AppLifetimeMonitor(Profile* profile);
  virtual ~AppLifetimeMonitor();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnAppWindowRemoved(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowHidden(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowShown(extensions::AppWindow* app_window) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

  bool HasVisibleAppWindows(extensions::AppWindow* app_window) const;

  void NotifyAppStart(const std::string& app_id);
  void NotifyAppActivated(const std::string& app_id);
  void NotifyAppDeactivated(const std::string& app_id);
  void NotifyAppStop(const std::string& app_id);
  void NotifyChromeTerminating();

  content::NotificationRegistrar registrar_;
  Profile* profile_;
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(AppLifetimeMonitor);
};

}  

#endif  
