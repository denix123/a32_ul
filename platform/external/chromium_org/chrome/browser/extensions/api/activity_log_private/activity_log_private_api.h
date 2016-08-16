// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_EXTENSIONS_API_ACTIVITY_LOG_PRIVATE_ACTIVITY_LOG_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_ACTIVITY_LOG_PRIVATE_ACTIVITY_LOG_PRIVATE_API_H_

#include "base/synchronization/lock.h"
#include "chrome/browser/extensions/activity_log/activity_actions.h"
#include "chrome/browser/extensions/activity_log/activity_log.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace extensions {

class ActivityLog;

class ActivityLogAPI : public BrowserContextKeyedAPI,
                       public extensions::ActivityLog::Observer,
                       public EventRouter::Observer {
 public:
  explicit ActivityLogAPI(content::BrowserContext* context);
  virtual ~ActivityLogAPI();

  
  static BrowserContextKeyedAPIFactory<ActivityLogAPI>* GetFactoryInstance();

  virtual void Shutdown() OVERRIDE;

  
  static bool IsExtensionWhitelisted(const std::string& extension_id);

 private:
  friend class BrowserContextKeyedAPIFactory<ActivityLogAPI>;
  static const char* service_name() { return "ActivityLogPrivateAPI"; }

  
  
  virtual void OnExtensionActivity(scoped_refptr<Action> activity) OVERRIDE;

  
  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

  content::BrowserContext* browser_context_;
  ActivityLog* activity_log_;
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(ActivityLogAPI);
};

template <>
void
    BrowserContextKeyedAPIFactory<ActivityLogAPI>::DeclareFactoryDependencies();

class ActivityLogPrivateGetExtensionActivitiesFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("activityLogPrivate.getExtensionActivities",
                             ACTIVITYLOGPRIVATE_GETEXTENSIONACTIVITIES)

 protected:
  virtual ~ActivityLogPrivateGetExtensionActivitiesFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnLookupCompleted(
      scoped_ptr<std::vector<scoped_refptr<Action> > > activities);
};

class ActivityLogPrivateDeleteActivitiesFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("activityLogPrivate.deleteActivities",
                             ACTIVITYLOGPRIVATE_DELETEACTIVITIES)

 protected:
  virtual ~ActivityLogPrivateDeleteActivitiesFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class ActivityLogPrivateDeleteDatabaseFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("activityLogPrivate.deleteDatabase",
                             ACTIVITYLOGPRIVATE_DELETEDATABASE)

 protected:
  virtual ~ActivityLogPrivateDeleteDatabaseFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class ActivityLogPrivateDeleteUrlsFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("activityLogPrivate.deleteUrls",
                             ACTIVITYLOGPRIVATE_DELETEURLS)

 protected:
  virtual ~ActivityLogPrivateDeleteUrlsFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

}  

#endif  
