// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_MOCK_ACK_HANDLER_H_
#define COMPONENTS_INVALIDATION_MOCK_ACK_HANDLER_H_

#include <map>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "components/invalidation/ack_handler.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_util.h"

namespace syncer {

class Invalidation;

class INVALIDATION_EXPORT MockAckHandler
  : public AckHandler,
    public base::SupportsWeakPtr<MockAckHandler> {
 public:
  MockAckHandler();
  virtual ~MockAckHandler();

  
  
  void RegisterInvalidation(Invalidation* invalidation);

  
  
  void RegisterUnsentInvalidation(Invalidation* invalidation);

  
  
  bool IsUnacked(const Invalidation& invalidation) const;

  
  
  bool IsAcknowledged(const Invalidation& invalidation) const;

  
  
  bool IsDropped(const Invalidation& invalidation) const;

  
  bool IsUnsent(const Invalidation& invalidation) const;

  
  bool AllInvalidationsAccountedFor() const;

  
  virtual void Acknowledge(
      const invalidation::ObjectId& id,
      const AckHandle& handle) OVERRIDE;
  virtual void Drop(
      const invalidation::ObjectId& id,
      const AckHandle& handle) OVERRIDE;

 private:
  typedef std::vector<syncer::Invalidation> InvalidationVector;
  typedef std::map<invalidation::ObjectId,
                   AckHandle,
                   ObjectIdLessThan> IdHandleMap;

  InvalidationVector unsent_invalidations_;
  InvalidationVector unacked_invalidations_;
  InvalidationVector acked_invalidations_;
  InvalidationVector dropped_invalidations_;

  IdHandleMap unrecovered_drop_events_;
};

}  

#endif  
