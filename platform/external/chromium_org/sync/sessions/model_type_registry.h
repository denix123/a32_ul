// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_MODEL_TYPE_REGISTRY_H_
#define SYNC_ENGINE_MODEL_TYPE_REGISTRY_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "sync/base/sync_export.h"
#include "sync/engine/nudge_handler.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/internal_api/public/sessions/type_debug_info_observer.h"
#include "sync/internal_api/public/sync_context.h"
#include "sync/internal_api/public/sync_encryption_handler.h"

namespace syncer {

namespace syncable {
class Directory;
}  

class CommitContributor;
class DirectoryCommitContributor;
class DirectoryUpdateHandler;
class DirectoryTypeDebugInfoEmitter;
class ModelTypeSyncWorkerImpl;
class ModelTypeSyncProxyImpl;
class UpdateHandler;

typedef std::map<ModelType, UpdateHandler*> UpdateHandlerMap;
typedef std::map<ModelType, CommitContributor*> CommitContributorMap;
typedef std::map<ModelType, DirectoryTypeDebugInfoEmitter*>
    DirectoryTypeDebugInfoEmitterMap;

class SYNC_EXPORT_PRIVATE ModelTypeRegistry
    : public SyncContext,
      public SyncEncryptionHandler::Observer {
 public:
  
  ModelTypeRegistry(const std::vector<scoped_refptr<ModelSafeWorker> >& workers,
                    syncable::Directory* directory,
                    NudgeHandler* nudge_handler);
  virtual ~ModelTypeRegistry();

  
  void SetEnabledDirectoryTypes(const ModelSafeRoutingInfo& routing_info);

  
  
  
  
  virtual void ConnectSyncTypeToWorker(
      syncer::ModelType type,
      const DataTypeState& data_type_state,
      const syncer::UpdateResponseDataList& saved_pending_updates,
      const scoped_refptr<base::SequencedTaskRunner>& type_task_runner,
      const base::WeakPtr<ModelTypeSyncProxyImpl>& proxy) OVERRIDE;

  
  
  
  
  virtual void DisconnectSyncWorker(syncer::ModelType type) OVERRIDE;

  
  virtual void OnPassphraseRequired(
      PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) OVERRIDE;
  virtual void OnPassphraseAccepted() OVERRIDE;
  virtual void OnBootstrapTokenUpdated(const std::string& bootstrap_token,
                                       BootstrapTokenType type) OVERRIDE;
  virtual void OnEncryptedTypesChanged(ModelTypeSet encrypted_types,
                                       bool encrypt_everything) OVERRIDE;
  virtual void OnEncryptionComplete() OVERRIDE;
  virtual void OnCryptographerStateChanged(
      Cryptographer* cryptographer) OVERRIDE;
  virtual void OnPassphraseTypeChanged(PassphraseType type,
                                       base::Time passphrase_time) OVERRIDE;

  
  ModelTypeSet GetEnabledTypes() const;

  
  UpdateHandlerMap* update_handler_map();
  CommitContributorMap* commit_contributor_map();
  DirectoryTypeDebugInfoEmitterMap* directory_type_debug_info_emitter_map();

  void RegisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer);
  void UnregisterDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer);
  bool HasDirectoryTypeDebugInfoObserver(
      syncer::TypeDebugInfoObserver* observer);
  void RequestEmitDebugInfo();

  base::WeakPtr<SyncContext> AsWeakPtr();

 private:
  void OnEncryptionStateChanged();

  ModelTypeSet GetEnabledNonBlockingTypes() const;
  ModelTypeSet GetEnabledDirectoryTypes() const;

  
  ScopedVector<DirectoryCommitContributor> directory_commit_contributors_;
  ScopedVector<DirectoryUpdateHandler> directory_update_handlers_;
  ScopedVector<DirectoryTypeDebugInfoEmitter>
      directory_type_debug_info_emitters_;

  ScopedVector<ModelTypeSyncWorkerImpl> model_type_sync_workers_;

  
  
  UpdateHandlerMap update_handler_map_;
  CommitContributorMap commit_contributor_map_;

  
  
  
  DirectoryTypeDebugInfoEmitterMap directory_type_debug_info_emitter_map_;

  
  std::map<ModelSafeGroup, scoped_refptr<ModelSafeWorker> > workers_map_;

  
  syncable::Directory* directory_;

  
  scoped_ptr<Cryptographer> cryptographer_;

  
  ModelTypeSet encrypted_types_;

  
  SyncEncryptionHandler* encryption_handler_;

  
  NudgeHandler* nudge_handler_;

  
  ModelTypeSet enabled_directory_types_;

  
  
  
  
  
  
  ObserverList<TypeDebugInfoObserver> type_debug_info_observers_;

  base::WeakPtrFactory<ModelTypeRegistry> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ModelTypeRegistry);
};

}  

#endif 
