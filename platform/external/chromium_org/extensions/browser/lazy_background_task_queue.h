// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_LAZY_BACKGROUND_TASK_QUEUE_H_
#define EXTENSIONS_BROWSER_LAZY_BACKGROUND_TASK_QUEUE_H_

#include <map>
#include <string>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
class ExtensionHost;
class ExtensionRegistry;

class LazyBackgroundTaskQueue : public content::NotificationObserver,
                                public ExtensionRegistryObserver {
 public:
  typedef base::Callback<void(ExtensionHost*)> PendingTask;

  explicit LazyBackgroundTaskQueue(content::BrowserContext* browser_context);
  virtual ~LazyBackgroundTaskQueue();

  
  size_t extensions_with_pending_tasks() { return pending_tasks_.size(); }

  
  
  
  
  bool ShouldEnqueueTask(content::BrowserContext* context,
                         const Extension* extension);

  
  
  
  
  
  void AddPendingTask(
      content::BrowserContext* context,
      const std::string& extension_id,
      const PendingTask& task);

 private:
  FRIEND_TEST_ALL_PREFIXES(LazyBackgroundTaskQueueTest, ProcessPendingTasks);

  
  
  typedef std::string ExtensionID;
  typedef std::pair<content::BrowserContext*, ExtensionID> PendingTasksKey;
  typedef std::vector<PendingTask> PendingTasksList;
  typedef std::map<PendingTasksKey,
                   linked_ptr<PendingTasksList> > PendingTasksMap;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  
  void ProcessPendingTasks(
      ExtensionHost* host,
      content::BrowserContext* context,
      const Extension* extension);

  content::BrowserContext* browser_context_;
  content::NotificationRegistrar registrar_;
  PendingTasksMap pending_tasks_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;
};

}  

#endif  
