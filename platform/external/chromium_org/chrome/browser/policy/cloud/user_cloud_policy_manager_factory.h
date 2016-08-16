// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CLOUD_USER_CLOUD_POLICY_MANAGER_FACTORY_H_
#define CHROME_BROWSER_POLICY_CLOUD_USER_CLOUD_POLICY_MANAGER_FACTORY_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_base_factory.h"

namespace base {
class SequencedTaskRunner;
}

namespace content {
class BrowserContext;
}

namespace policy {

class UserCloudPolicyManager;

class UserCloudPolicyManagerFactory : public BrowserContextKeyedBaseFactory {
 public:
  
  static UserCloudPolicyManagerFactory* GetInstance();

  
  static UserCloudPolicyManager* GetForBrowserContext(
      content::BrowserContext* context);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static scoped_ptr<UserCloudPolicyManager> CreateForOriginalBrowserContext(
      content::BrowserContext* context,
      bool force_immediate_load,
      const scoped_refptr<base::SequencedTaskRunner>& background_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& file_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);

  static UserCloudPolicyManager* RegisterForOffTheRecordBrowserContext(
      content::BrowserContext* original_context,
      content::BrowserContext* off_the_record_context);

  typedef UserCloudPolicyManager*
      (*TestingFactoryFunction)(content::BrowserContext* context);

  
  
  
  
  
  void RegisterTestingFactory(TestingFactoryFunction factory);
  void ClearTestingFactory();

 private:
  class ManagerWrapper;
  friend struct DefaultSingletonTraits<UserCloudPolicyManagerFactory>;

  UserCloudPolicyManagerFactory();
  virtual ~UserCloudPolicyManagerFactory();

  
  UserCloudPolicyManager* GetManagerForBrowserContext(
      content::BrowserContext* context);

  scoped_ptr<UserCloudPolicyManager> CreateManagerForOriginalBrowserContext(
      content::BrowserContext* context,
      bool force_immediate_load,
      const scoped_refptr<base::SequencedTaskRunner>& background_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& file_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);

  UserCloudPolicyManager* RegisterManagerForOffTheRecordBrowserContext(
      content::BrowserContext* original_context,
      content::BrowserContext* off_the_record_context);

  
  virtual void BrowserContextShutdown(
      content::BrowserContext* context) OVERRIDE;
  virtual void BrowserContextDestroyed(
      content::BrowserContext* context) OVERRIDE;
  virtual void SetEmptyTestingFactory(
      content::BrowserContext* context) OVERRIDE;
  virtual bool HasTestingFactory(content::BrowserContext* context) OVERRIDE;
  virtual void CreateServiceNow(content::BrowserContext* context) OVERRIDE;
  virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE;


  typedef std::map<content::BrowserContext*, ManagerWrapper*> ManagerWrapperMap;

  ManagerWrapperMap manager_wrappers_;
  TestingFactoryFunction testing_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserCloudPolicyManagerFactory);
};

}  

#endif  
