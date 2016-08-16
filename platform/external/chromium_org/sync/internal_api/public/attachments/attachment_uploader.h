// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_UPLOADER_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_UPLOADER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "sync/api/attachments/attachment.h"
#include "sync/base/sync_export.h"

namespace syncer {

class SYNC_EXPORT AttachmentUploader {
 public:
  
  enum UploadResult {
    UPLOAD_SUCCESS,            
                               
    UPLOAD_TRANSIENT_ERROR,    
    UPLOAD_UNSPECIFIED_ERROR,  
  };

  typedef base::Callback<void(const UploadResult&, const AttachmentId&)>
      UploadCallback;

  AttachmentUploader();
  virtual ~AttachmentUploader();

  
  
  
  
  
  
  
  virtual void UploadAttachment(const Attachment& attachment,
                                const UploadCallback& callback) = 0;
};

}  

#endif  
