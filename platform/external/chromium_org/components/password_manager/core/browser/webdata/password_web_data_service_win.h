// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_WEBDATA_PASSWORD_WEB_DATA_SERVICE_WIN_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_WEBDATA_PASSWORD_WEB_DATA_SERVICE_WIN_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "components/webdata/common/web_data_results.h"
#include "components/webdata/common/web_data_service_base.h"
#include "components/webdata/common/web_data_service_consumer.h"
#include "components/webdata/common/web_database.h"

class GURL;
struct IE7PasswordInfo;
class Profile;
class WebDatabaseService;

namespace base {
class MessageLoopProxy;
class Thread;
}

namespace content {
class BrowserContext;
}


class WebDataServiceConsumer;

class PasswordWebDataService : public WebDataServiceBase {
 public:
  
  static scoped_refptr<PasswordWebDataService> FromBrowserContext(
      content::BrowserContext* context);

  PasswordWebDataService(scoped_refptr<WebDatabaseService> wdbs,
                         scoped_refptr<base::MessageLoopProxy> ui_thread,
                         const ProfileErrorCallback& callback);

  
  void AddIE7Login(const IE7PasswordInfo& info);

  
  void RemoveIE7Login(const IE7PasswordInfo& info);

  
  
  
  
  
  Handle GetIE7Login(const IE7PasswordInfo& info,
                     WebDataServiceConsumer* consumer);

 protected:
  
  PasswordWebDataService(scoped_refptr<base::MessageLoopProxy> ui_thread);

  virtual ~PasswordWebDataService();

 private:
  
  WebDatabase::State AddIE7LoginImpl(const IE7PasswordInfo& info,
                                     WebDatabase* db);
  WebDatabase::State RemoveIE7LoginImpl(const IE7PasswordInfo& info,
                                        WebDatabase* db);
  scoped_ptr<WDTypedResult> GetIE7LoginImpl(const IE7PasswordInfo& info,
                                            WebDatabase* db);

  DISALLOW_COPY_AND_ASSIGN(PasswordWebDataService);
};

#endif  
