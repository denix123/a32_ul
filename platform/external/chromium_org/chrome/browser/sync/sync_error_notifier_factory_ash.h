// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_SYNC_ERROR_NOTIFIER_FACTORY_ASH_H_
#define CHROME_BROWSER_SYNC_SYNC_ERROR_NOTIFIER_FACTORY_ASH_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class SyncErrorNotifier;
class Profile;

class SyncErrorNotifierFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  
  static SyncErrorNotifier* GetForProfile(Profile* profile);

  
  static SyncErrorNotifierFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<SyncErrorNotifierFactory>;

  SyncErrorNotifierFactory();
  virtual ~SyncErrorNotifierFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(SyncErrorNotifierFactory);
};

#endif  
