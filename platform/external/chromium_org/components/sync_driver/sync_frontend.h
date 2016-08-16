// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_SYNC_FRONTEND_H_
#define COMPONENTS_SYNC_DRIVER_SYNC_FRONTEND_H_

#include "base/basictypes.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/sync_encryption_handler.h"
#include "sync/internal_api/public/sync_manager.h"
#include "sync/internal_api/public/util/weak_handle.h"
#include "sync/protocol/sync_protocol_error.h"

namespace syncer {
class DataTypeDebugInfoListener;
class JsBackend;
class ProtocolEvent;
struct CommitCounters;
struct StatusCounters;
struct UpdateCounters;
}  

namespace sync_pb {
class EncryptedData;
}  

namespace sync_driver {

class SyncFrontend {
 public:
  SyncFrontend();
  virtual ~SyncFrontend();

  
  
  
  
  
  
  
  virtual void OnBackendInitialized(
      const syncer::WeakHandle<syncer::JsBackend>& js_backend,
      const syncer::WeakHandle<syncer::DataTypeDebugInfoListener>&
          debug_info_listener,
      const std::string& cache_guid,
      bool success) = 0;

  
  virtual void OnSyncCycleCompleted() = 0;

  
  
  virtual void OnSyncConfigureRetry() = 0;

  
  
  
  
  
  
  virtual void OnProtocolEvent(const syncer::ProtocolEvent& event) = 0;

  
  
  
  
  virtual void OnDirectoryTypeCommitCounterUpdated(
      syncer::ModelType type,
      const syncer::CommitCounters& counters) = 0;

  
  
  
  
  virtual void OnDirectoryTypeUpdateCounterUpdated(
      syncer::ModelType type,
      const syncer::UpdateCounters& counters) = 0;

  
  
  
  
  virtual void OnDirectoryTypeStatusCounterUpdated(
      syncer::ModelType type,
      const syncer::StatusCounters& counters) = 0;

  
  virtual void OnConnectionStatusChange(
      syncer::ConnectionStatus status) = 0;

  
  
  
  
  
  
  virtual void OnPassphraseRequired(
      syncer::PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) = 0;

  
  
  
  virtual void OnPassphraseAccepted() = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void OnEncryptedTypesChanged(
      syncer::ModelTypeSet encrypted_types,
      bool encrypt_everything) = 0;

  
  
  virtual void OnEncryptionComplete() = 0;

  
  virtual void OnMigrationNeededForTypes(syncer::ModelTypeSet types) = 0;

  
  virtual void OnExperimentsChanged(
      const syncer::Experiments& experiments) = 0;

  
  virtual void OnActionableError(const syncer::SyncProtocolError& error) = 0;
};

}  

#endif  
