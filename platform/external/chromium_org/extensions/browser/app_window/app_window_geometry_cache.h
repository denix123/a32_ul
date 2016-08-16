// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_GEOMETRY_CACHE_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_GEOMETRY_CACHE_H_

#include <map>
#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "base/scoped_observer.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/extension_registry_observer.h"
#include "ui/base/ui_base_types.h"
#include "ui/gfx/rect.h"

namespace extensions {

class ExtensionPrefs;
class ExtensionRegistry;

class AppWindowGeometryCache : public KeyedService,
                               public ExtensionRegistryObserver {
 public:
  class Factory : public BrowserContextKeyedServiceFactory {
   public:
    static AppWindowGeometryCache* GetForContext(
        content::BrowserContext* context,
        bool create);

    static Factory* GetInstance();

   private:
    friend struct DefaultSingletonTraits<Factory>;

    Factory();
    virtual ~Factory();

    
    virtual KeyedService* BuildServiceInstanceFor(
        content::BrowserContext* context) const OVERRIDE;
    virtual bool ServiceIsNULLWhileTesting() const OVERRIDE;
    virtual content::BrowserContext* GetBrowserContextToUse(
        content::BrowserContext* context) const OVERRIDE;
  };

  class Observer {
   public:
    virtual void OnGeometryCacheChanged(const std::string& extension_id,
                                        const std::string& window_id,
                                        const gfx::Rect& bounds) = 0;

   protected:
    virtual ~Observer() {}
  };

  AppWindowGeometryCache(content::BrowserContext* context,
                         ExtensionPrefs* prefs);

  virtual ~AppWindowGeometryCache();

  
  static AppWindowGeometryCache* Get(content::BrowserContext* context);

  
  void SaveGeometry(const std::string& extension_id,
                    const std::string& window_id,
                    const gfx::Rect& bounds,
                    const gfx::Rect& screen_bounds,
                    ui::WindowShowState state);

  
  
  
  bool GetGeometry(const std::string& extension_id,
                   const std::string& window_id,
                   gfx::Rect* bounds,
                   gfx::Rect* screen_bounds,
                   ui::WindowShowState* state);

  
  virtual void Shutdown() OVERRIDE;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  static const size_t kMaxCachedWindows = 100;

 protected:
  friend class AppWindowGeometryCacheTest;

  
  
  
  void SetSyncDelayForTests(int timeout_ms);

 private:
  
  struct WindowData {
    WindowData();
    ~WindowData();
    gfx::Rect bounds;
    gfx::Rect screen_bounds;
    ui::WindowShowState window_state;
    base::Time last_change;
  };

  
  typedef std::map<std::string, WindowData> ExtensionData;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  void LoadGeometryFromStorage(const std::string& extension_id);
  void SyncToStorage();

  
  ExtensionPrefs* prefs_;

  
  std::map<std::string, ExtensionData> cache_;

  
  std::set<std::string> unsynced_extensions_;

  
  base::OneShotTimer<AppWindowGeometryCache> sync_timer_;

  
  base::TimeDelta sync_delay_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  ObserverList<Observer> observers_;
};

}  

#endif  
