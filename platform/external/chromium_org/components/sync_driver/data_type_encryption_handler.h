// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DATA_TYPE_ENCRYPTION_HANDLER_H_
#define COMPONENTS_SYNC_DRIVER_DATA_TYPE_ENCRYPTION_HANDLER_H_

#include "base/basictypes.h"
#include "sync/internal_api/public/base/model_type.h"

namespace sync_driver {

class DataTypeEncryptionHandler {
 public:
  DataTypeEncryptionHandler();
  virtual ~DataTypeEncryptionHandler();

  
  
  virtual bool IsPassphraseRequired() const = 0;

  
  virtual syncer::ModelTypeSet GetEncryptedDataTypes() const = 0;
};

} 

#endif  
