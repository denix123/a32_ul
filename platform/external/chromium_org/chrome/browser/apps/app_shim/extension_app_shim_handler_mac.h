// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_APP_SHIM_EXTENSION_APP_SHIM_HANDLER_MAC_H_
#define CHROME_BROWSER_APPS_APP_SHIM_EXTENSION_APP_SHIM_HANDLER_MAC_H_

#include <map>
#include <string>
#include <vector>

#include "apps/app_lifetime_monitor.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/apps/app_shim/app_shim_handler_mac.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/app_window/app_window_registry.h"

class Profile;

namespace base {
class FilePath;
}

namespace content {
class WebContents;
}

namespace extensions {
class AppWindow;
class Extension;
}

namespace apps {

class ExtensionAppShimHandler : public AppShimHandler,
                                public content::NotificationObserver,
                                public AppLifetimeMonitor::Observer {
 public:
  class Delegate {
   public:
    virtual ~Delegate() {}

    virtual bool ProfileExistsForPath(const base::FilePath& path);
    virtual Profile* ProfileForPath(const base::FilePath& path);
    virtual void LoadProfileAsync(const base::FilePath& path,
                                  base::Callback<void(Profile*)> callback);

    virtual extensions::AppWindowRegistry::AppWindowList GetWindows(
        Profile* profile,
        const std::string& extension_id);

    virtual const extensions::Extension* GetAppExtension(
        Profile* profile, const std::string& extension_id);
    virtual void EnableExtension(Profile* profile,
                                 const std::string& extension_id,
                                 const base::Callback<void()>& callback);
    virtual void LaunchApp(Profile* profile,
                           const extensions::Extension* extension,
                           const std::vector<base::FilePath>& files);
    virtual void LaunchShim(Profile* profile,
                            const extensions::Extension* extension);

    virtual void MaybeTerminate();
  };

  ExtensionAppShimHandler();
  virtual ~ExtensionAppShimHandler();

  AppShimHandler::Host* FindHost(Profile* profile, const std::string& app_id);

  static void QuitAppForWindow(extensions::AppWindow* app_window);

  static void HideAppForWindow(extensions::AppWindow* app_window);

  static void FocusAppForWindow(extensions::AppWindow* app_window);

  
  
  static bool ActivateAndRequestUserAttentionForWindow(
      extensions::AppWindow* app_window);

  
  
  static void RequestUserAttentionForWindow(
      extensions::AppWindow* app_window,
      AppShimAttentionType attention_type);

  
  static void OnChromeWillHide();

  
  virtual void OnShimLaunch(Host* host,
                            AppShimLaunchType launch_type,
                            const std::vector<base::FilePath>& files) OVERRIDE;
  virtual void OnShimClose(Host* host) OVERRIDE;
  virtual void OnShimFocus(Host* host,
                           AppShimFocusType focus_type,
                           const std::vector<base::FilePath>& files) OVERRIDE;
  virtual void OnShimSetHidden(Host* host, bool hidden) OVERRIDE;
  virtual void OnShimQuit(Host* host) OVERRIDE;

  
  virtual void OnAppStart(Profile* profile, const std::string& app_id) OVERRIDE;
  virtual void OnAppActivated(Profile* profile,
                              const std::string& app_id) OVERRIDE;
  virtual void OnAppDeactivated(Profile* profile,
                                const std::string& app_id) OVERRIDE;
  virtual void OnAppStop(Profile* profile, const std::string& app_id) OVERRIDE;
  virtual void OnChromeTerminating() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 protected:
  typedef std::map<std::pair<Profile*, std::string>, AppShimHandler::Host*>
      HostMap;

  
  void set_delegate(Delegate* delegate);
  HostMap& hosts() { return hosts_; }
  content::NotificationRegistrar& registrar() { return registrar_; }

 private:
  
  static ExtensionAppShimHandler* GetInstance();

  
  
  void OnProfileLoaded(Host* host,
                       AppShimLaunchType launch_type,
                       const std::vector<base::FilePath>& files,
                       Profile* profile);

  
  
  void OnExtensionEnabled(const base::FilePath& profile_path,
                          const std::string& app_id,
                          const std::vector<base::FilePath>& files);

  scoped_ptr<Delegate> delegate_;

  HostMap hosts_;

  content::NotificationRegistrar registrar_;

  base::WeakPtrFactory<ExtensionAppShimHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionAppShimHandler);
};

}  

#endif  
