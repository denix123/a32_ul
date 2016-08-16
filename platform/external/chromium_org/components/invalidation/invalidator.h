// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATOR_H_
#define COMPONENTS_INVALIDATION_INVALIDATOR_H_

#include <string>

#include "base/callback.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"
#include "components/invalidation/invalidator_state.h"

namespace syncer {
class InvalidationHandler;

class INVALIDATION_EXPORT Invalidator {
 public:
  Invalidator();
  virtual ~Invalidator();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  
  
  virtual void RegisterHandler(InvalidationHandler* handler) = 0;

  
  
  
  virtual void UpdateRegisteredIds(InvalidationHandler* handler,
                                   const ObjectIdSet& ids) = 0;

  
  
  
  virtual void UnregisterHandler(InvalidationHandler* handler) = 0;

  
  
  
  virtual InvalidatorState GetInvalidatorState() const = 0;

  
  
  
  virtual void UpdateCredentials(
      const std::string& email, const std::string& token) = 0;

  
  virtual void RequestDetailedStatus(
      base::Callback<void(const base::DictionaryValue&)> callback) const = 0;
};
}  

#endif  
