// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_FILE_SYSTEM_ENTRY_WATCHER_SERVICE_FACTORY_H_
#define CHROME_BROWSER_EXTENSIONS_API_FILE_SYSTEM_ENTRY_WATCHER_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace content {
class BrowserContext;
}  

namespace extensions {

class EntryWatcherService;

class EntryWatcherServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  
  static EntryWatcherService* Get(content::BrowserContext* context);

  
  
  static EntryWatcherService* FindExisting(content::BrowserContext* context);

  
  static EntryWatcherServiceFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<EntryWatcherServiceFactory>;

  EntryWatcherServiceFactory();
  virtual ~EntryWatcherServiceFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;
  virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(EntryWatcherServiceFactory);
};

}  

#endif  
