// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_IMPL_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_IMPL_H_

#include <deque>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "net/base/network_change_notifier.h"
#include "sync/api/attachments/attachment_store.h"
#include "sync/internal_api/public/attachments/attachment_downloader.h"
#include "sync/internal_api/public/attachments/attachment_service.h"
#include "sync/internal_api/public/attachments/attachment_service_proxy.h"
#include "sync/internal_api/public/attachments/attachment_uploader.h"
#include "sync/internal_api/public/attachments/task_queue.h"

namespace syncer {

class SYNC_EXPORT AttachmentServiceImpl
    : public AttachmentService,
      public net::NetworkChangeNotifier::NetworkChangeObserver,
      public base::NonThreadSafe {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  AttachmentServiceImpl(scoped_refptr<AttachmentStore> attachment_store,
                        scoped_ptr<AttachmentUploader> attachment_uploader,
                        scoped_ptr<AttachmentDownloader> attachment_downloader,
                        Delegate* delegate,
                        const base::TimeDelta& initial_backoff_delay,
                        const base::TimeDelta& max_backoff_delay);
  virtual ~AttachmentServiceImpl();

  
  static scoped_ptr<syncer::AttachmentService> CreateForTest();

  
  virtual AttachmentStore* GetStore() OVERRIDE;
  virtual void GetOrDownloadAttachments(
      const AttachmentIdList& attachment_ids,
      const GetOrDownloadCallback& callback) OVERRIDE;
  virtual void DropAttachments(const AttachmentIdList& attachment_ids,
                               const DropCallback& callback) OVERRIDE;
  virtual void UploadAttachments(
      const AttachmentIdSet& attachment_ids) OVERRIDE;

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  
  
  void SetTimerForTest(scoped_ptr<base::Timer> timer);

 private:
  class GetOrDownloadState;

  void ReadDone(const scoped_refptr<GetOrDownloadState>& state,
                const AttachmentStore::Result& result,
                scoped_ptr<AttachmentMap> attachments,
                scoped_ptr<AttachmentIdList> unavailable_attachment_ids);
  void DropDone(const DropCallback& callback,
                const AttachmentStore::Result& result);
  void UploadDone(const AttachmentUploader::UploadResult& result,
                  const AttachmentId& attachment_id);
  void DownloadDone(const scoped_refptr<GetOrDownloadState>& state,
                    const AttachmentId& attachment_id,
                    const AttachmentDownloader::DownloadResult& result,
                    scoped_ptr<Attachment> attachment);
  void BeginUpload(const AttachmentId& attachment_id);
  void ReadDoneNowUpload(
      const AttachmentStore::Result& result,
      scoped_ptr<AttachmentMap> attachments,
      scoped_ptr<AttachmentIdList> unavailable_attachment_ids);

  scoped_refptr<AttachmentStore> attachment_store_;

  
  const scoped_ptr<AttachmentUploader> attachment_uploader_;

  
  const scoped_ptr<AttachmentDownloader> attachment_downloader_;

  
  Delegate* delegate_;

  scoped_ptr<TaskQueue<AttachmentId> > upload_task_queue_;

  
  base::WeakPtrFactory<AttachmentServiceImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AttachmentServiceImpl);
};

}  

#endif  
