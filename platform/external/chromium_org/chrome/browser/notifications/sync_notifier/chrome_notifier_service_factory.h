// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_SYNC_NOTIFIER_CHROME_NOTIFIER_SERVICE_FACTORY_H_
#define CHROME_BROWSER_NOTIFICATIONS_SYNC_NOTIFIER_CHROME_NOTIFIER_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
class CommandLine;
}

namespace notifier {

class ChromeNotifierService;

class ChromeNotifierServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static ChromeNotifierService* GetForProfile(
      Profile* profile, Profile::ServiceAccessType service_access_type);

  static ChromeNotifierServiceFactory* GetInstance();

  
  
  
  
  static bool UseSyncedNotifications(base::CommandLine* command_line);

 private:
  friend struct DefaultSingletonTraits<ChromeNotifierServiceFactory>;

  ChromeNotifierServiceFactory();
  virtual ~ChromeNotifierServiceFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;
};

}  

#endif  