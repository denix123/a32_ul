// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_SIGNED_IN_DEVICES_SIGNED_IN_DEVICES_MANAGER_H__
#define CHROME_BROWSER_EXTENSIONS_API_SIGNED_IN_DEVICES_SIGNED_IN_DEVICES_MANAGER_H__

#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/scoped_observer.h"
#include "components/sync_driver/device_info_tracker.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

namespace content {
class BrowserContext;
class NotificationDetails;
class NotificationObserver;
class NotificationRegistrar;
}  

namespace extensions {
class BrowserContextKeyedAPI;
class ExtensionRegistry;

struct EventListenerInfo;

class SignedInDevicesChangeObserver
    : public sync_driver::DeviceInfoTracker::Observer {
 public:
  SignedInDevicesChangeObserver(const std::string& extension_id,
                                Profile* profile);
  virtual ~SignedInDevicesChangeObserver();

  virtual void OnDeviceInfoChange() OVERRIDE;

  const std::string& extension_id() {
    return extension_id_;
  }

 private:
  std::string extension_id_;
  Profile* const profile_;
  content::NotificationRegistrar registrar_;
};

class SignedInDevicesManager : public BrowserContextKeyedAPI,
                               public ExtensionRegistryObserver,
                               public EventRouter::Observer {
 public:
  
  SignedInDevicesManager();
  explicit SignedInDevicesManager(content::BrowserContext* context);
  virtual ~SignedInDevicesManager();

  
  static BrowserContextKeyedAPIFactory<SignedInDevicesManager>*
      GetFactoryInstance();

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<SignedInDevicesManager>;

  
  static const char* service_name() {
    return "SignedInDevicesManager";
  }
  static const bool kServiceHasOwnInstanceInIncognito = true;

  void RemoveChangeObserverForExtension(const std::string& extension_id);

  Profile* const profile_;
  ScopedVector<SignedInDevicesChangeObserver> change_observers_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  FRIEND_TEST_ALL_PREFIXES(SignedInDevicesManager, UpdateListener);

  DISALLOW_COPY_AND_ASSIGN(SignedInDevicesManager);
};

}  

#endif  
