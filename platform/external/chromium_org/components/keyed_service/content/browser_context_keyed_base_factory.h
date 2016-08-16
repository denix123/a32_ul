// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_KEYED_BASE_FACTORY_H_
#define COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_KEYED_BASE_FACTORY_H_

#include <set>

#include "base/threading/non_thread_safe.h"
#include "components/keyed_service/core/dependency_node.h"
#include "components/keyed_service/core/keyed_service_export.h"

class BrowserContextDependencyManager;
class PrefService;

namespace content {
class BrowserContext;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class KEYED_SERVICE_EXPORT BrowserContextKeyedBaseFactory
    : public base::NonThreadSafe,
      NON_EXPORTED_BASE(public DependencyNode) {
 public:
  
  
  
  
  
  
  
  void RegisterUserPrefsOnBrowserContextForTest(
      content::BrowserContext* context);

#ifndef NDEBUG
  
  const char* name() const { return service_name_; }
#endif

 protected:
  BrowserContextKeyedBaseFactory(const char* name,
                                 BrowserContextDependencyManager* manager);
  virtual ~BrowserContextKeyedBaseFactory();

  
  
  void DependsOn(BrowserContextKeyedBaseFactory* rhs);

  
  
  
  
  void RegisterProfilePrefsIfNecessaryForContext(
      const content::BrowserContext* context,
      user_prefs::PrefRegistrySyncable* registry);

  

  
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const;

  
  
  
  virtual bool ServiceIsCreatedWithBrowserContext() const;

  
  
  
  
  
  virtual bool ServiceIsNULLWhileTesting() const;

  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void BrowserContextShutdown(content::BrowserContext* context) = 0;
  virtual void BrowserContextDestroyed(content::BrowserContext* context);

  
  bool ArePreferencesSetOn(content::BrowserContext* context) const;

  
  void MarkPreferencesSetOn(content::BrowserContext* context);

  
  
  
  
  BrowserContextDependencyManager* dependency_manager_;

 private:
  friend class BrowserContextDependencyManager;
  friend class BrowserContextDependencyManagerUnittests;

  
  
  
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) {}

  
  

  
  
  virtual void SetEmptyTestingFactory(content::BrowserContext* context) = 0;

  
  virtual bool HasTestingFactory(content::BrowserContext* context) = 0;

  
  
  virtual void CreateServiceNow(content::BrowserContext* context) = 0;

  
  std::set<const content::BrowserContext*> registered_preferences_;

#if !defined(NDEBUG)
  
  
  
  const char* service_name_;
#endif
};

#endif  
