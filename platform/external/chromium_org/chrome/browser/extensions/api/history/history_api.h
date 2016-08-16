// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_HISTORY_HISTORY_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_HISTORY_HISTORY_API_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/task/cancelable_task_tracker.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/history/history_notifications.h"
#include "chrome/browser/history/history_service.h"
#include "chrome/common/extensions/api/history.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace base {
class ListValue;
}

namespace extensions {

class HistoryEventRouter : public content::NotificationObserver {
 public:
  explicit HistoryEventRouter(Profile* profile);
  virtual ~HistoryEventRouter();

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  void HistoryUrlVisited(Profile* profile,
                         const history::URLVisitedDetails* details);

  void HistoryUrlsRemoved(Profile* profile,
                          const history::URLsDeletedDetails* details);

  void DispatchEvent(Profile* profile,
                     const std::string& event_name,
                     scoped_ptr<base::ListValue> event_args);

  
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(HistoryEventRouter);
};

class HistoryAPI : public BrowserContextKeyedAPI, public EventRouter::Observer {
 public:
  explicit HistoryAPI(content::BrowserContext* context);
  virtual ~HistoryAPI();

  
  virtual void Shutdown() OVERRIDE;

  
  static BrowserContextKeyedAPIFactory<HistoryAPI>* GetFactoryInstance();

  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<HistoryAPI>;

  content::BrowserContext* browser_context_;

  
  static const char* service_name() {
    return "HistoryAPI";
  }
  static const bool kServiceIsNULLWhileTesting = true;

  
  scoped_ptr<HistoryEventRouter> history_event_router_;
};

template <>
void BrowserContextKeyedAPIFactory<HistoryAPI>::DeclareFactoryDependencies();

class HistoryFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~HistoryFunction() {}

  bool ValidateUrl(const std::string& url_string, GURL* url);
  bool VerifyDeleteAllowed();
  base::Time GetTime(double ms_from_epoch);
};

class HistoryFunctionWithCallback : public HistoryFunction {
 public:
  HistoryFunctionWithCallback();

 protected:
  virtual ~HistoryFunctionWithCallback();

  
  virtual bool RunAsync() OVERRIDE;

  
  virtual bool RunAsyncImpl() = 0;

  
  
  virtual void SendAsyncResponse();

  
  base::CancelableTaskTracker task_tracker_;

 private:
  
  
  void SendResponseToCallback();
};

class HistoryGetVisitsFunction : public HistoryFunctionWithCallback {
 public:
  DECLARE_EXTENSION_FUNCTION("history.getVisits", HISTORY_GETVISITS)

 protected:
  virtual ~HistoryGetVisitsFunction() {}

  
  virtual bool RunAsyncImpl() OVERRIDE;

  
  void QueryComplete(bool success,
                     const history::URLRow& url_row,
                     const history::VisitVector& visits);
};

class HistorySearchFunction : public HistoryFunctionWithCallback {
 public:
  DECLARE_EXTENSION_FUNCTION("history.search", HISTORY_SEARCH)

 protected:
  virtual ~HistorySearchFunction() {}

  
  virtual bool RunAsyncImpl() OVERRIDE;

  
  void SearchComplete(history::QueryResults* results);
};

class HistoryAddUrlFunction : public HistoryFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("history.addUrl", HISTORY_ADDURL)

 protected:
  virtual ~HistoryAddUrlFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class HistoryDeleteAllFunction : public HistoryFunctionWithCallback {
 public:
  DECLARE_EXTENSION_FUNCTION("history.deleteAll", HISTORY_DELETEALL)

 protected:
  virtual ~HistoryDeleteAllFunction() {}

  
  virtual bool RunAsyncImpl() OVERRIDE;

  
  void DeleteComplete();
};


class HistoryDeleteUrlFunction : public HistoryFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("history.deleteUrl", HISTORY_DELETEURL)

 protected:
  virtual ~HistoryDeleteUrlFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class HistoryDeleteRangeFunction : public HistoryFunctionWithCallback {
 public:
  DECLARE_EXTENSION_FUNCTION("history.deleteRange", HISTORY_DELETERANGE)

 protected:
  virtual ~HistoryDeleteRangeFunction() {}

  
  virtual bool RunAsyncImpl() OVERRIDE;

  
  void DeleteComplete();
};

}  

#endif  
