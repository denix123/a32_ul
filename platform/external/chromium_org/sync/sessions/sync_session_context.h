// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef SYNC_SESSIONS_SYNC_SESSION_CONTEXT_H_
#define SYNC_SESSIONS_SYNC_SESSION_CONTEXT_H_

#include <string>

#include "sync/base/sync_export.h"
#include "sync/engine/sync_engine_event_listener.h"
#include "sync/sessions/debug_info_getter.h"
#include "sync/sessions/model_type_registry.h"

namespace syncer {

class ExtensionsActivity;
class ModelTypeRegistry;
class ServerConnectionManager;

namespace syncable {
class Directory;
}

static const int kDefaultMaxCommitBatchSize = 25;

namespace sessions {
class TestScopedSessionEventListener;

class SYNC_EXPORT_PRIVATE SyncSessionContext {
 public:
  SyncSessionContext(
      ServerConnectionManager* connection_manager,
      syncable::Directory* directory,
      ExtensionsActivity* extensions_activity,
      const std::vector<SyncEngineEventListener*>& listeners,
      DebugInfoGetter* debug_info_getter,
      ModelTypeRegistry* model_type_registry,
      bool keystore_encryption_enabled,
      bool client_enabled_pre_commit_update_avoidance,
      const std::string& invalidator_client_id);

  ~SyncSessionContext();

  ServerConnectionManager* connection_manager() {
    return connection_manager_;
  }
  syncable::Directory* directory() {
    return directory_;
  }

  ModelTypeSet GetEnabledTypes() const;

  void SetRoutingInfo(const ModelSafeRoutingInfo& routing_info);

  ExtensionsActivity* extensions_activity() {
    return extensions_activity_.get();
  }

  DebugInfoGetter* debug_info_getter() {
    return debug_info_getter_;
  }

  
  void set_notifications_enabled(bool enabled) {
    notifications_enabled_ = enabled;
  }
  bool notifications_enabled() { return notifications_enabled_; }

  
  void set_account_name(const std::string& name) {
    DCHECK(account_name_.empty());
    account_name_ = name;
  }
  const std::string& account_name() const { return account_name_; }

  void set_max_commit_batch_size(int batch_size) {
    max_commit_batch_size_ = batch_size;
  }
  int32 max_commit_batch_size() const { return max_commit_batch_size_; }

  ObserverList<SyncEngineEventListener>* listeners() {
    return &listeners_;
  }

  bool keystore_encryption_enabled() const {
    return keystore_encryption_enabled_;
  }

  void set_hierarchy_conflict_detected(bool value) {
    client_status_.set_hierarchy_conflict_detected(value);
  }

  const sync_pb::ClientStatus& client_status() const {
    return client_status_;
  }

  const std::string& invalidator_client_id() const {
    return invalidator_client_id_;
  }

  bool ShouldFetchUpdatesBeforeCommit() const {
    return !(server_enabled_pre_commit_update_avoidance_ ||
             client_enabled_pre_commit_update_avoidance_);
  }

  void set_server_enabled_pre_commit_update_avoidance(bool value) {
    server_enabled_pre_commit_update_avoidance_ = value;
  }

  ModelTypeRegistry* model_type_registry() {
    return model_type_registry_;
  }

 private:
  
  
  
  friend class TestScopedSessionEventListener;

  ObserverList<SyncEngineEventListener> listeners_;

  ServerConnectionManager* const connection_manager_;
  syncable::Directory* const directory_;

  
  
  scoped_refptr<ExtensionsActivity> extensions_activity_;

  
  
  bool notifications_enabled_;

  
  std::string account_name_;

  
  int max_commit_batch_size_;

  
  
  DebugInfoGetter* const debug_info_getter_;

  ModelTypeRegistry* model_type_registry_;

  
  sync_pb::ClientStatus client_status_;

  
  
  
  bool keystore_encryption_enabled_;

  
  
  
  
  const std::string invalidator_client_id_;

  
  
  
  bool server_enabled_pre_commit_update_avoidance_;

  
  
  const bool client_enabled_pre_commit_update_avoidance_;

  DISALLOW_COPY_AND_ASSIGN(SyncSessionContext);
};

}  
}  

#endif  
