// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_DEPENDENCY_MANAGER_H_
#define COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_DEPENDENCY_MANAGER_H_

#include "base/callback_forward.h"
#include "base/callback_list.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/core/dependency_graph.h"
#include "components/keyed_service/core/keyed_service_export.h"

#ifndef NDEBUG
#include <set>
#endif

class BrowserContextKeyedBaseFactory;

namespace content {
class BrowserContext;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class KEYED_SERVICE_EXPORT BrowserContextDependencyManager {
 public:
  
  
  void AddComponent(BrowserContextKeyedBaseFactory* component);
  void RemoveComponent(BrowserContextKeyedBaseFactory* component);

  
  void AddEdge(BrowserContextKeyedBaseFactory* depended,
               BrowserContextKeyedBaseFactory* dependee);

  
  
  
  
  void RegisterProfilePrefsForServices(
      const content::BrowserContext* context,
      user_prefs::PrefRegistrySyncable* registry);

  
  
  
  
  
  
  void CreateBrowserContextServices(content::BrowserContext* context);

  
  
  
  
  void CreateBrowserContextServicesForTest(content::BrowserContext* context);

  
  
  void DestroyBrowserContextServices(content::BrowserContext* context);

  
  
  
  
  scoped_ptr<base::CallbackList<void(content::BrowserContext*)>::Subscription>
  RegisterWillCreateBrowserContextServicesCallbackForTesting(
      const base::Callback<void(content::BrowserContext*)>& callback);

#ifndef NDEBUG
  
  
  
  void AssertBrowserContextWasntDestroyed(content::BrowserContext* context);

  
  
  
  
  
  void MarkBrowserContextLiveForTesting(content::BrowserContext* context);
#endif

  static BrowserContextDependencyManager* GetInstance();

 private:
  friend class BrowserContextDependencyManagerUnittests;
  friend struct DefaultSingletonTraits<BrowserContextDependencyManager>;

  
  void DoCreateBrowserContextServices(content::BrowserContext* context,
                                      bool is_testing_context);

  BrowserContextDependencyManager();
  virtual ~BrowserContextDependencyManager();

#ifndef NDEBUG
  void DumpBrowserContextDependencies(content::BrowserContext* context);
#endif

  DependencyGraph dependency_graph_;

  
  
  base::CallbackList<void(content::BrowserContext*)>
      will_create_browser_context_services_callbacks_;

#ifndef NDEBUG
  
  
  
  
  std::set<content::BrowserContext*> dead_context_pointers_;
#endif
};

#endif  
