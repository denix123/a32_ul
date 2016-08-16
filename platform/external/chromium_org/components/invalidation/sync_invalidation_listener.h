// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_SYNC_INVALIDATION_LISTENER_H_
#define COMPONENTS_INVALIDATION_SYNC_INVALIDATION_LISTENER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "components/invalidation/ack_handler.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidation_state_tracker.h"
#include "components/invalidation/invalidator_state.h"
#include "components/invalidation/state_writer.h"
#include "components/invalidation/sync_system_resources.h"
#include "components/invalidation/unacked_invalidation_set.h"
#include "google/cacheinvalidation/include/invalidation-listener.h"

namespace buzz {
class XmppTaskParentInterface;
}  

namespace notifier {
class PushClient;
}  

namespace syncer {

class ObjectIdInvalidationMap;
class RegistrationManager;

class INVALIDATION_EXPORT_PRIVATE SyncInvalidationListener
    : public NON_EXPORTED_BASE(invalidation::InvalidationListener),
      public StateWriter,
      public SyncNetworkChannel::Observer,
      public AckHandler,
      public base::NonThreadSafe {
 public:
  typedef base::Callback<invalidation::InvalidationClient*(
      invalidation::SystemResources*,
      int,
      const invalidation::string&,
      const invalidation::string&,
      invalidation::InvalidationListener*)> CreateInvalidationClientCallback;

  class INVALIDATION_EXPORT_PRIVATE Delegate {
   public:
    virtual ~Delegate();

    virtual void OnInvalidate(
        const ObjectIdInvalidationMap& invalidations) = 0;

    virtual void OnInvalidatorStateChange(InvalidatorState state) = 0;
  };

  explicit SyncInvalidationListener(
      scoped_ptr<SyncNetworkChannel> network_channel);

  
  virtual ~SyncInvalidationListener();

  
  
  void Start(
      const CreateInvalidationClientCallback&
          create_invalidation_client_callback,
      const std::string& client_id,
      const std::string& client_info,
      const std::string& invalidation_bootstrap_data,
      const UnackedInvalidationsMap& initial_object_states,
      const base::WeakPtr<InvalidationStateTracker>& invalidation_state_tracker,
      const scoped_refptr<base::SequencedTaskRunner>&
          invalidation_state_tracker_task_runner,
      Delegate* delegate);

  void UpdateCredentials(const std::string& email, const std::string& token);

  
  
  void UpdateRegisteredIds(const ObjectIdSet& ids);

  
  virtual void Ready(
      invalidation::InvalidationClient* client) OVERRIDE;
  virtual void Invalidate(
      invalidation::InvalidationClient* client,
      const invalidation::Invalidation& invalidation,
      const invalidation::AckHandle& ack_handle) OVERRIDE;
  virtual void InvalidateUnknownVersion(
      invalidation::InvalidationClient* client,
      const invalidation::ObjectId& object_id,
      const invalidation::AckHandle& ack_handle) OVERRIDE;
  virtual void InvalidateAll(
      invalidation::InvalidationClient* client,
      const invalidation::AckHandle& ack_handle) OVERRIDE;
  virtual void InformRegistrationStatus(
      invalidation::InvalidationClient* client,
      const invalidation::ObjectId& object_id,
      invalidation::InvalidationListener::RegistrationState reg_state) OVERRIDE;
  virtual void InformRegistrationFailure(
      invalidation::InvalidationClient* client,
      const invalidation::ObjectId& object_id,
      bool is_transient,
      const std::string& error_message) OVERRIDE;
  virtual void ReissueRegistrations(
      invalidation::InvalidationClient* client,
      const std::string& prefix,
      int prefix_length) OVERRIDE;
  virtual void InformError(
      invalidation::InvalidationClient* client,
      const invalidation::ErrorInfo& error_info) OVERRIDE;

  
  virtual void Acknowledge(
      const invalidation::ObjectId& id,
      const syncer::AckHandle& handle) OVERRIDE;
  virtual void Drop(
      const invalidation::ObjectId& id,
      const syncer::AckHandle& handle) OVERRIDE;

  
  virtual void WriteState(const std::string& state) OVERRIDE;

  
  virtual void OnNetworkChannelStateChanged(
      InvalidatorState invalidator_state) OVERRIDE;

  void DoRegistrationUpdate();

  void RequestDetailedStatus(
      base::Callback<void(const base::DictionaryValue&)> callback) const;

  void StopForTest();

 private:
  void Stop();

  InvalidatorState GetState() const;

  void EmitStateChange();

  
  
  
  
  
  
  
  void DispatchInvalidations(const ObjectIdInvalidationMap& invalidations);

  
  
  
  
  
  void SaveInvalidations(const ObjectIdInvalidationMap& to_save);

  
  void EmitSavedInvalidations(const ObjectIdInvalidationMap& to_emit);

  
  scoped_ptr<base::DictionaryValue> CollectDebugData() const;

  base::WeakPtr<AckHandler> AsWeakPtr();

  scoped_ptr<SyncNetworkChannel> sync_network_channel_;
  SyncSystemResources sync_system_resources_;
  UnackedInvalidationsMap unacked_invalidations_map_;
  base::WeakPtr<InvalidationStateTracker> invalidation_state_tracker_;
  scoped_refptr<base::SequencedTaskRunner>
      invalidation_state_tracker_task_runner_;
  Delegate* delegate_;
  scoped_ptr<invalidation::InvalidationClient> invalidation_client_;
  scoped_ptr<RegistrationManager> registration_manager_;
  
  ObjectIdSet registered_ids_;

  
  InvalidatorState ticl_state_;
  InvalidatorState push_client_state_;

  base::WeakPtrFactory<SyncInvalidationListener> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncInvalidationListener);
};

}  

#endif  
