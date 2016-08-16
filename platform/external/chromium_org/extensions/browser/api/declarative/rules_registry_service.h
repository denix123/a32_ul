// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_DECLARATIVE_RULES_REGISTRY_SERVICE_H__
#define EXTENSIONS_BROWSER_API_DECLARATIVE_RULES_REGISTRY_SERVICE_H__

#include <map>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/api/declarative/rules_registry.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class BrowserContext;
class NotificationSource;
}

namespace extensions {
class ContentRulesRegistry;
class ExtensionRegistry;
class RulesRegistryStorageDelegate;
}

namespace extensions {

class RulesRegistryService : public BrowserContextKeyedAPI,
                             public content::NotificationObserver,
                             public ExtensionRegistryObserver {
 public:
  typedef RulesRegistry::WebViewKey WebViewKey;
  struct RulesRegistryKey {
    std::string event_name;
    WebViewKey webview_key;
    RulesRegistryKey(const std::string event_name,
                     const WebViewKey& webview_key)
        : event_name(event_name),
          webview_key(webview_key) {}
    bool operator<(const RulesRegistryKey& other) const {
      return (event_name < other.event_name) ||
          ((event_name == other.event_name) &&
          (webview_key < other.webview_key));
    }
  };

  explicit RulesRegistryService(content::BrowserContext* context);
  virtual ~RulesRegistryService();

  
  
  virtual void Shutdown() OVERRIDE;

  
  static BrowserContextKeyedAPIFactory<RulesRegistryService>*
      GetFactoryInstance();

  
  static RulesRegistryService* Get(content::BrowserContext* context);

  
  void EnsureDefaultRulesRegistriesRegistered(const WebViewKey& webview_key);

  
  void RegisterRulesRegistry(scoped_refptr<RulesRegistry> rule_registry);

  
  
  
  scoped_refptr<RulesRegistry> GetRulesRegistry(const WebViewKey& webview_key,
                                                const std::string& event_name);

  
  ContentRulesRegistry* content_rules_registry() const {
    CHECK(content_rules_registry_);
    return content_rules_registry_;
  }

  
  void RemoveWebViewRulesRegistries(int process_id);

  
  void SimulateExtensionUninstalled(const std::string& extension_id);

 private:
  friend class BrowserContextKeyedAPIFactory<RulesRegistryService>;

  
  
  typedef std::map<RulesRegistryKey, scoped_refptr<RulesRegistry> >
      RulesRegistryMap;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  
  
  
  void NotifyRegistriesHelper(
      void (RulesRegistry::*notification_callback)(const std::string&),
      const std::string& extension_id);

  
  static const char* service_name() {
    return "RulesRegistryService";
  }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  RulesRegistryMap rule_registries_;

  
  ScopedVector<RulesCacheDelegate> cache_delegates_;

  
  
  ContentRulesRegistry* content_rules_registry_;

  content::NotificationRegistrar registrar_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(RulesRegistryService);
};

}  

#endif  
