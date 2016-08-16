// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "base/task_runner.h"
#include "sync/api/attachments/attachment.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/attachments/attachment_service.h"

namespace syncer {

class SYNC_EXPORT AttachmentServiceProxy : public AttachmentService {
 public:
  

  
  AttachmentServiceProxy();

  
  
  
  
  
  AttachmentServiceProxy(
      const scoped_refptr<base::SequencedTaskRunner>& wrapped_task_runner,
      const base::WeakPtr<syncer::AttachmentService>& wrapped);

  virtual ~AttachmentServiceProxy();

  
  
  
  virtual AttachmentStore* GetStore() OVERRIDE;
  virtual void GetOrDownloadAttachments(
      const AttachmentIdList& attachment_ids,
      const GetOrDownloadCallback& callback) OVERRIDE;
  virtual void DropAttachments(const AttachmentIdList& attachment_ids,
                               const DropCallback& callback) OVERRIDE;
  virtual void UploadAttachments(
      const AttachmentIdSet& attachment_ids) OVERRIDE;

 protected:
  
  
  
  
  
  
  
  
  
  
  
  
  
  class SYNC_EXPORT Core : public AttachmentService,
                           public base::RefCountedThreadSafe<Core> {
   public:
    
    Core(const base::WeakPtr<syncer::AttachmentService>& wrapped);

    
    virtual AttachmentStore* GetStore() OVERRIDE;
    virtual void GetOrDownloadAttachments(
        const AttachmentIdList& attachment_ids,
        const GetOrDownloadCallback& callback) OVERRIDE;
    virtual void DropAttachments(const AttachmentIdList& attachment_ids,
                                 const DropCallback& callback) OVERRIDE;
    virtual void UploadAttachments(
        const AttachmentIdSet& attachment_ids) OVERRIDE;

   protected:
    friend class base::RefCountedThreadSafe<Core>;
    virtual ~Core();

   private:
    base::WeakPtr<AttachmentService> wrapped_;

    DISALLOW_COPY_AND_ASSIGN(Core);
  };

  
  AttachmentServiceProxy(
      const scoped_refptr<base::SequencedTaskRunner>& wrapped_task_runner,
      const scoped_refptr<Core>& core);

 private:
  scoped_refptr<base::SequencedTaskRunner> wrapped_task_runner_;
  scoped_refptr<Core> core_;
};

}  

#endif  
