// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_BASE_INVALIDATION_INTERFACE_H_
#define SYNC_INTERNAL_API_PUBLIC_BASE_INVALIDATION_INTERFACE_H_

#include <string>

#include "base/basictypes.h"
#include "sync/base/sync_export.h"

namespace syncer {

class SYNC_EXPORT InvalidationInterface {
 public:
  
  static bool LessThanByVersion(const InvalidationInterface& a,
                                const InvalidationInterface& b);

  InvalidationInterface();
  virtual ~InvalidationInterface();

  
  
  virtual bool IsUnknownVersion() const = 0;

  
  
  virtual const std::string& GetPayload() const = 0;

  
  
  
  
  
  virtual int64 GetVersion() const = 0;

  
  
  virtual void Acknowledge() = 0;

  
  
  
  
  
  virtual void Drop() = 0;
};

}  

#endif
