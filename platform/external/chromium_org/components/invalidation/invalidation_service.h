// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_SERVICE_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_SERVICE_H_

#include "base/callback_forward.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/invalidator_state.h"

class IdentityProvider;

namespace syncer {
class InvalidationHandler;
}  

namespace invalidation {
class InvalidationLogger;

class InvalidationService {
 public:
  virtual ~InvalidationService() {}

  
  
  
  
  virtual void RegisterInvalidationHandler(
      syncer::InvalidationHandler* handler) = 0;

  
  
  
  
  
  virtual void UpdateRegisteredInvalidationIds(
      syncer::InvalidationHandler* handler,
      const syncer::ObjectIdSet& ids) = 0;

  
  
  
  
  
  virtual void UnregisterInvalidationHandler(
      syncer::InvalidationHandler* handler) = 0;

  
  
  
  virtual syncer::InvalidatorState GetInvalidatorState() const = 0;

  
  
  virtual std::string GetInvalidatorClientId() const = 0;

  
  virtual InvalidationLogger* GetInvalidationLogger() = 0;

  
  virtual void RequestDetailedStatus(
      base::Callback<void(const base::DictionaryValue&)> post_caller) const = 0;

  
  virtual IdentityProvider* GetIdentityProvider() = 0;
};

}  

#endif  
