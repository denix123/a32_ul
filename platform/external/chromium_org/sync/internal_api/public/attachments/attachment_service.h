// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_SERVICE_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "sync/api/attachments/attachment.h"
#include "sync/base/sync_export.h"

namespace syncer {

class AttachmentStore;
class SyncData;

class SYNC_EXPORT AttachmentService {
 public:
  
  enum GetOrDownloadResult {
    GET_SUCCESS,            
    GET_UNSPECIFIED_ERROR,  
  };

  typedef base::Callback<
      void(const GetOrDownloadResult&, scoped_ptr<AttachmentMap> attachments)>
      GetOrDownloadCallback;

  
  enum DropResult {
    DROP_SUCCESS,            
    DROP_UNSPECIFIED_ERROR,  
                             
  };

  typedef base::Callback<void(const DropResult&)> DropCallback;

  
  
  
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    virtual void OnAttachmentUploaded(const AttachmentId& attachment_id) = 0;
  };

  AttachmentService();
  virtual ~AttachmentService();

  
  
  
  virtual AttachmentStore* GetStore() = 0;

  
  virtual void GetOrDownloadAttachments(
      const AttachmentIdList& attachment_ids,
      const GetOrDownloadCallback& callback) = 0;

  
  virtual void DropAttachments(const AttachmentIdList& attachment_ids,
                               const DropCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  virtual void UploadAttachments(const AttachmentIdSet& attachment_ids) = 0;
};

}  

#endif  
