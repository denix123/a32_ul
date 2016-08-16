// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_FOR_TEST_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_FOR_TEST_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/attachments/attachment_service_proxy.h"

namespace syncer {

class SYNC_EXPORT AttachmentServiceProxyForTest
    : public AttachmentServiceProxy {
 public:
  static AttachmentServiceProxy Create();
  virtual ~AttachmentServiceProxyForTest();

 private:
  
  class OwningCore : public AttachmentServiceProxy::Core {
   public:
    OwningCore(
        scoped_ptr<AttachmentService>,
        scoped_ptr<base::WeakPtrFactory<AttachmentService> > weak_ptr_factory);

   private:
    virtual ~OwningCore();

    scoped_ptr<AttachmentService> wrapped_;
    
    scoped_ptr<base::WeakPtrFactory<AttachmentService> > weak_ptr_factory_;

    DISALLOW_COPY_AND_ASSIGN(OwningCore);
  };

  AttachmentServiceProxyForTest(
      const scoped_refptr<base::SequencedTaskRunner>& wrapped_task_runner,
      const scoped_refptr<Core>& core);
};

}  

#endif  
