// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_ATTACHMENTS_ATTACHMENT_H_
#define SYNC_API_ATTACHMENTS_ATTACHMENT_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_ptr.h"
#include "sync/api/attachments/attachment_id.h"
#include "sync/base/sync_export.h"

namespace syncer {

class SYNC_EXPORT Attachment {
 public:
  ~Attachment();

  

  
  
  
  static Attachment Create(const scoped_refptr<base::RefCountedMemory>& data);

  
  
  
  
  static Attachment CreateWithId(
      const AttachmentId& id,
      const scoped_refptr<base::RefCountedMemory>& data);

  
  const AttachmentId& GetId() const;

  
  const scoped_refptr<base::RefCountedMemory>& GetData() const;

 private:
  AttachmentId id_;
  scoped_refptr<base::RefCountedMemory> data_;

  Attachment(const AttachmentId& id,
             const scoped_refptr<base::RefCountedMemory>& data);
};

typedef std::vector<syncer::Attachment> AttachmentList;
typedef std::map<AttachmentId, Attachment> AttachmentMap;

}  

#endif  
