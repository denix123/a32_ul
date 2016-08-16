// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_GENERIC_CHANGE_PROCESSOR_H_
#define COMPONENTS_SYNC_DRIVER_GENERIC_CHANGE_PROCESSOR_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "components/sync_driver/change_processor.h"
#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/data_type_error_handler.h"
#include "sync/api/attachments/attachment_store.h"
#include "sync/api/sync_change_processor.h"
#include "sync/api/sync_merge_result.h"
#include "sync/internal_api/public/attachments/attachment_service.h"
#include "sync/internal_api/public/attachments/attachment_service_proxy.h"

namespace syncer {
class SyncData;
class SyncableService;
class WriteNode;
class WriteTransaction;

typedef std::vector<syncer::SyncData> SyncDataList;
}  

namespace sync_driver {
class SyncApiComponentFactory;

class GenericChangeProcessor : public ChangeProcessor,
                               public syncer::SyncChangeProcessor,
                               public syncer::AttachmentService::Delegate,
                               public base::NonThreadSafe {
 public:
  
  
  
  GenericChangeProcessor(
      syncer::ModelType type,
      DataTypeErrorHandler* error_handler,
      const base::WeakPtr<syncer::SyncableService>& local_service,
      const base::WeakPtr<syncer::SyncMergeResult>& merge_result,
      syncer::UserShare* user_share,
      SyncApiComponentFactory* sync_factory,
      const scoped_refptr<syncer::AttachmentStore>& attachment_store);
  virtual ~GenericChangeProcessor();

  
  
  virtual void ApplyChangesFromSyncModel(
      const syncer::BaseTransaction* trans,
      int64 version,
      const syncer::ImmutableChangeRecordList& changes) OVERRIDE;
  
  
  virtual void CommitChangesFromSyncModel() OVERRIDE;

  
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(syncer::ModelType type)
      const OVERRIDE;
  virtual syncer::SyncError UpdateDataTypeContext(
      syncer::ModelType type,
      syncer::SyncChangeProcessor::ContextRefreshStatus refresh_status,
      const std::string& context) OVERRIDE;

  
  virtual void OnAttachmentUploaded(
      const syncer::AttachmentId& attachment_id) OVERRIDE;

  
  
  virtual syncer::SyncError GetAllSyncDataReturnError(
      syncer::SyncDataList* data) const;

  
  
  
  virtual bool GetDataTypeContext(std::string* context) const;

  
  virtual int GetSyncCount();

  
  
  virtual bool SyncModelHasUserCreatedNodes(bool* has_nodes);
  virtual bool CryptoReadyIfNecessary();

 protected:
  
  virtual void StartImpl() OVERRIDE;  
  virtual syncer::UserShare* share_handle() const OVERRIDE;

 private:
  
  
  
  
  syncer::SyncError HandleActionAdd(const syncer::SyncChange& change,
                                    const std::string& type_str,
                                    const syncer::WriteTransaction& trans,
                                    syncer::WriteNode* sync_node,
                                    syncer::AttachmentIdSet* new_attachments);

  
  
  
  
  syncer::SyncError HandleActionUpdate(
      const syncer::SyncChange& change,
      const std::string& type_str,
      const syncer::WriteTransaction& trans,
      syncer::WriteNode* sync_node,
      syncer::AttachmentIdSet* new_attachments);

  
  
  void UploadAllAttachmentsNotOnServer();

  const syncer::ModelType type_;

  
  const base::WeakPtr<syncer::SyncableService> local_service_;

  
  
  
  
  const base::WeakPtr<syncer::SyncMergeResult> merge_result_;

  
  
  
  
  syncer::SyncChangeList syncer_changes_;

  
  
  
  
  
  syncer::UserShare* const share_handle_;

  
  
  scoped_ptr<syncer::AttachmentService> attachment_service_;

  
  
  
  scoped_ptr<base::WeakPtrFactory<syncer::AttachmentService> >
      attachment_service_weak_ptr_factory_;
  scoped_ptr<syncer::AttachmentServiceProxy> attachment_service_proxy_;

  base::WeakPtrFactory<GenericChangeProcessor> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GenericChangeProcessor);
};

}  

#endif  
