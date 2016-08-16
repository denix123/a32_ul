// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_SYNC_GLOBAL_ERROR_FACTORY_H_
#define CHROME_BROWSER_SYNC_SYNC_GLOBAL_ERROR_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class SyncGlobalError;
class Profile;

class SyncGlobalErrorFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  
  static SyncGlobalError* GetForProfile(Profile* profile);

  
  static SyncGlobalErrorFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<SyncGlobalErrorFactory>;

  SyncGlobalErrorFactory();
  virtual ~SyncGlobalErrorFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(SyncGlobalErrorFactory);
};

#endif  
