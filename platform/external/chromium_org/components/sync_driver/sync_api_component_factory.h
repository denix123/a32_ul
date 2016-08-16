// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_SYNC_API_COMPONENT_FACTORY_H_
#define COMPONENTS_SYNC_DRIVER_SYNC_API_COMPONENT_FACTORY_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "sync/api/syncable_service.h"
#include "sync/internal_api/public/attachments/attachment_service.h"
#include "sync/internal_api/public/base/model_type.h"

namespace sync_driver {

class SyncApiComponentFactory {
 public:
  virtual ~SyncApiComponentFactory() {}

  
  
  
  virtual base::WeakPtr<syncer::SyncableService> GetSyncableServiceForType(
      syncer::ModelType type) = 0;

  
  
  
  
  
  
  virtual scoped_ptr<syncer::AttachmentService> CreateAttachmentService(
      const scoped_refptr<syncer::AttachmentStore>& attachment_store,
      const syncer::UserShare& user_share,
      syncer::AttachmentService::Delegate* delegate) = 0;
};

}  

#endif  
