// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_SYNC_NOTIFIER_CHROME_NOTIFIER_SERVICE_H_
#define CHROME_BROWSER_NOTIFICATIONS_SYNC_NOTIFIER_CHROME_NOTIFIER_SERVICE_H_

#include "base/memory/weak_ptr.h"
#include "components/keyed_service/core/keyed_service.h"

class Profile;
class SyncedNotificationsShim;

namespace extensions {
struct Event;
}

namespace notifier {

class ChromeNotifierService : public KeyedService {
 public:
  explicit ChromeNotifierService(Profile* profile);
  virtual ~ChromeNotifierService();

  
  virtual void Shutdown() OVERRIDE;

  
  
  SyncedNotificationsShim* GetSyncedNotificationsShim();

 private:
  
  void FireSyncJSEvent(scoped_ptr<extensions::Event> event);

  
  void NotifyRefreshNeeded();

  
  Profile* const profile_;

  
  
  scoped_ptr<SyncedNotificationsShim> synced_notifications_shim_;

  base::WeakPtrFactory<ChromeNotifierService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromeNotifierService);
};

}  

#endif  
