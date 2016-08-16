// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_ATTACHMENTS_ATTACHMENT_STORE_H_
#define SYNC_API_ATTACHMENTS_ATTACHMENT_STORE_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "sync/api/attachments/attachment.h"
#include "sync/api/attachments/attachment_id.h"
#include "sync/base/sync_export.h"

namespace base {
class RefCountedMemory;
}  

namespace syncer {

class Attachment;
class AttachmentId;

class SYNC_EXPORT AttachmentStore : public base::RefCounted<AttachmentStore> {
 public:
  AttachmentStore();

  
  

  enum Result {
    SUCCESS,            
    UNSPECIFIED_ERROR,  
  };

  typedef base::Callback<void(const Result&,
                              scoped_ptr<AttachmentMap>,
                              scoped_ptr<AttachmentIdList>)> ReadCallback;
  typedef base::Callback<void(const Result&)> WriteCallback;
  typedef base::Callback<void(const Result&)> DropCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Read(const AttachmentIdList& ids,
                    const ReadCallback& callback) = 0;

  
  
  
  
  
  
  // not be written |callback|'s Result will be UNSPECIFIED_ERROR. When this
  // happens, some or none of the attachments may have been written
  
  virtual void Write(const AttachmentList& attachments,
                     const WriteCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  virtual void Drop(const AttachmentIdList& ids,
                    const DropCallback& callback) = 0;

 protected:
  friend class base::RefCounted<AttachmentStore>;
  virtual ~AttachmentStore();
};

}  

#endif  
