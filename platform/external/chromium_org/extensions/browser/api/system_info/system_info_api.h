// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SYSTEM_INFO_SYSTEM_INFO_API_H_
#define EXTENSIONS_BROWSER_API_SYSTEM_INFO_SYSTEM_INFO_API_H_

#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace extensions {

class SystemInfoAPI : public BrowserContextKeyedAPI,
                      public EventRouter::Observer {
 public:
  
  static BrowserContextKeyedAPIFactory<SystemInfoAPI>* GetFactoryInstance();

  explicit SystemInfoAPI(content::BrowserContext* context);
  virtual ~SystemInfoAPI();

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<SystemInfoAPI>;

  
  static const char* service_name() { return "SystemInfoAPI"; }
  static const bool kServiceIsNULLWhileTesting = true;

  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(SystemInfoAPI);
};

}  

#endif  
