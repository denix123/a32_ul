// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_MDNS_MDNS_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_MDNS_MDNS_API_H_

#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "chrome/browser/extensions/api/mdns/dns_sd_registry.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class DnsSdRegistry;

class MDnsAPI : public BrowserContextKeyedAPI,
                public EventRouter::Observer,
                public DnsSdRegistry::DnsSdObserver {
 public:
  explicit MDnsAPI(content::BrowserContext* context);
  virtual ~MDnsAPI();

  static MDnsAPI* Get(content::BrowserContext* context);

  
  static BrowserContextKeyedAPIFactory<MDnsAPI>* GetFactoryInstance();

  
  void SetDnsSdRegistryForTesting(scoped_ptr<DnsSdRegistry> registry);

 protected:
  
  virtual DnsSdRegistry* dns_sd_registry();

 private:
  friend class BrowserContextKeyedAPIFactory<MDnsAPI>;

  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

  
  virtual void OnDnsSdEvent(
      const std::string& service_type,
      const DnsSdRegistry::DnsSdServiceList& services) OVERRIDE;

  
  static const char* service_name() {
    return "MDnsAPI";
  }

  static const bool kServiceIsCreatedWithBrowserContext = true;
  static const bool kServiceIsNULLWhileTesting = true;

  
  void UpdateMDnsListeners(const EventListenerInfo& details);

  
  base::ThreadChecker thread_checker_;
  content::BrowserContext* const browser_context_;
  
  scoped_ptr<DnsSdRegistry> dns_sd_registry_;
  
  std::set<std::string> service_types_;

  DISALLOW_COPY_AND_ASSIGN(MDnsAPI);
};

}  

#endif  