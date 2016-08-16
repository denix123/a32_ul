// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PERF_REGISTRY_TESTING_PREF_SERVICE_SYNCABLE_H_
#define COMPONENTS_PERF_REGISTRY_TESTING_PREF_SERVICE_SYNCABLE_H_

#include "base/basictypes.h"
#include "base/prefs/testing_pref_service.h"

namespace user_prefs {

class PrefRegistrySyncable;

class TestingPrefServiceSyncable
    : public TestingPrefServiceBase<PrefService, PrefRegistrySyncable> {
 public:
  TestingPrefServiceSyncable();
  TestingPrefServiceSyncable(TestingPrefStore* managed_prefs,
                             TestingPrefStore* user_prefs,
                             TestingPrefStore* recommended_prefs,
                             PrefRegistrySyncable* pref_registry,
                             PrefNotifierImpl* pref_notifier);
  virtual ~TestingPrefServiceSyncable();

  
  
  
  PrefRegistrySyncable* registry();

 private:
  DISALLOW_COPY_AND_ASSIGN(TestingPrefServiceSyncable);
};

}  

#endif  
