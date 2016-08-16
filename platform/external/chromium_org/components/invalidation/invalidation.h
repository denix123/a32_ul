// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "base/values.h"
#include "components/invalidation/ack_handle.h"
#include "components/invalidation/invalidation_export.h"
#include "google/cacheinvalidation/include/types.h"

namespace syncer {

class DroppedInvalidationTracker;
class AckHandler;

class INVALIDATION_EXPORT Invalidation {
 public:
  
  static Invalidation Init(const invalidation::ObjectId& id,
                           int64 version,
                           const std::string& payload);
  static Invalidation InitUnknownVersion(const invalidation::ObjectId& id);
  static Invalidation InitFromDroppedInvalidation(const Invalidation& dropped);
  static scoped_ptr<Invalidation> InitFromValue(
      const base::DictionaryValue& value);

  ~Invalidation();

  
  bool Equals(const Invalidation& other) const;

  invalidation::ObjectId object_id() const;
  bool is_unknown_version() const;

  
  int64 version() const;

  
  const std::string& payload() const;

  const AckHandle& ack_handle() const;

  
  
  
  
  
  
  
  void SetAckHandler(
      base::WeakPtr<AckHandler> handler,
      scoped_refptr<base::SequencedTaskRunner> handler_task_runner);

  
  
  
  
  
  
  
  bool SupportsAcknowledgement() const;

  
  
  
  
  
  
  void Acknowledge() const;

  
  
  
  
  
  
  
  
  
  void Drop();

  scoped_ptr<base::DictionaryValue> ToValue() const;
  std::string ToString() const;

 private:
  Invalidation(const invalidation::ObjectId& id,
               bool is_unknown_version,
               int64 version,
               const std::string& payload,
               AckHandle ack_handle);

  
  invalidation::ObjectId id_;

  
  bool is_unknown_version_;

  
  
  int64 version_;

  
  
  std::string payload_;

  
  AckHandle ack_handle_;

  
  base::WeakPtr<AckHandler> ack_handler_;
  scoped_refptr<base::SequencedTaskRunner> ack_handler_task_runner_;
};

}  

#endif  
