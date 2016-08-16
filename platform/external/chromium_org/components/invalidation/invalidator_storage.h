// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATOR_STORAGE_H_
#define COMPONENTS_INVALIDATION_INVALIDATOR_STORAGE_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/threading/thread_checker.h"
#include "components/invalidation/invalidation_state_tracker.h"

class PrefRegistrySimple;
class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace invalidation {

class InvalidatorStorage : public syncer::InvalidationStateTracker {
 public:
  
  explicit InvalidatorStorage(PrefService* pref_service);
  virtual ~InvalidatorStorage();

  
  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual void ClearAndSetNewClientId(const std::string& client_id) OVERRIDE;
  virtual std::string GetInvalidatorClientId() const OVERRIDE;
  virtual void SetBootstrapData(const std::string& data) OVERRIDE;
  virtual std::string GetBootstrapData() const OVERRIDE;
  virtual void SetSavedInvalidations(
      const syncer::UnackedInvalidationsMap& map) OVERRIDE;
  virtual syncer::UnackedInvalidationsMap GetSavedInvalidations()
      const OVERRIDE;
  virtual void Clear() OVERRIDE;

 private:
  base::ThreadChecker thread_checker_;

  PrefService* const pref_service_;

  DISALLOW_COPY_AND_ASSIGN(InvalidatorStorage);
};

}  

#endif  
