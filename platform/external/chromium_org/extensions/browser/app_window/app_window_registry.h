// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_REGISTRY_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_REGISTRY_H_

#include <list>
#include <set>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ui/gfx/native_widget_types.h"

namespace content {
class BrowserContext;
class DevToolsAgentHost;
class RenderViewHost;
}

namespace extensions {

class AppWindow;

class AppWindowRegistry : public KeyedService {
 public:
  class Observer {
   public:
    
    virtual void OnAppWindowAdded(AppWindow* app_window);
    
    virtual void OnAppWindowIconChanged(AppWindow* app_window);
    
    virtual void OnAppWindowRemoved(AppWindow* app_window);
    
    
    
    virtual void OnAppWindowHidden(AppWindow* app_window);
    
    virtual void OnAppWindowShown(AppWindow* app_window);

   protected:
    virtual ~Observer();
  };

  typedef std::list<AppWindow*> AppWindowList;
  typedef AppWindowList::const_iterator const_iterator;
  typedef std::set<std::string> InspectedWindowSet;

  explicit AppWindowRegistry(content::BrowserContext* context);
  virtual ~AppWindowRegistry();

  
  
  
  static AppWindowRegistry* Get(content::BrowserContext* context);

  void AddAppWindow(AppWindow* app_window);
  void AppWindowIconChanged(AppWindow* app_window);
  
  void AppWindowActivated(AppWindow* app_window);
  void AppWindowHidden(AppWindow* app_window);
  void AppWindowShown(AppWindow* app_window);
  void RemoveAppWindow(AppWindow* app_window);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  AppWindowList GetAppWindowsForApp(const std::string& app_id) const;
  const AppWindowList& app_windows() const { return app_windows_; }

  
  void CloseAllAppWindowsForApp(const std::string& app_id);

  
  AppWindow* GetAppWindowForRenderViewHost(
      content::RenderViewHost* render_view_host) const;
  AppWindow* GetAppWindowForNativeWindow(gfx::NativeWindow window) const;
  
  
  
  AppWindow* GetCurrentAppWindowForApp(const std::string& app_id) const;
  
  
  
  
  AppWindow* GetAppWindowForAppAndKey(const std::string& app_id,
                                      const std::string& window_key) const;

  
  
  
  bool HadDevToolsAttached(content::RenderViewHost* render_view_host) const;

  class Factory : public BrowserContextKeyedServiceFactory {
   public:
    static AppWindowRegistry* GetForBrowserContext(
        content::BrowserContext* context,
        bool create);

    static Factory* GetInstance();

   private:
    friend struct DefaultSingletonTraits<Factory>;

    Factory();
    virtual ~Factory();

    
    virtual KeyedService* BuildServiceInstanceFor(
        content::BrowserContext* context) const OVERRIDE;
    virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE;
    virtual bool ServiceIsNULLWhileTesting() const OVERRIDE;
    virtual content::BrowserContext* GetBrowserContextToUse(
        content::BrowserContext* context) const OVERRIDE;
  };

 protected:
  void OnDevToolsStateChanged(content::DevToolsAgentHost*, bool attached);

 private:
  
  
  void AddAppWindowToList(AppWindow* app_window);

  
  
  void BringToFront(AppWindow* app_window);

  content::BrowserContext* context_;
  AppWindowList app_windows_;
  InspectedWindowSet inspected_windows_;
  ObserverList<Observer> observers_;
  base::Callback<void(content::DevToolsAgentHost*, bool)> devtools_callback_;
};

}  

#endif  
