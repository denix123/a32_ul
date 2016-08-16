// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_ATTACHMENTS_FAKE_ATTACHMENT_STORE_H_
#define SYNC_API_ATTACHMENTS_FAKE_ATTACHMENT_STORE_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/stl_util.h"
#include "sync/api/attachments/attachment_store.h"
#include "sync/base/sync_export.h"

namespace base {
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}  

namespace sync_pb {
class AttachmentId;
}  

namespace syncer {

class Attachment;

class SYNC_EXPORT FakeAttachmentStore : public AttachmentStore {
 public:
  
  
  explicit FakeAttachmentStore(
      const scoped_refptr<base::SequencedTaskRunner>& backend_task_runner);

  
  virtual void Read(const AttachmentIdList& id,
                    const ReadCallback& callback) OVERRIDE;
  virtual void Write(const AttachmentList& attachments,
                     const WriteCallback& callback) OVERRIDE;
  virtual void Drop(const AttachmentIdList& id,
                    const DropCallback& callback) OVERRIDE;

 private:
  class Backend;

  virtual ~FakeAttachmentStore();

  scoped_refptr<Backend> backend_;
  scoped_refptr<base::SequencedTaskRunner> backend_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(FakeAttachmentStore);
};

}  

#endif  
