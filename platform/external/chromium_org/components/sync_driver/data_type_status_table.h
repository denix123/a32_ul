// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DATA_TYPE_STATUS_TABLE_H_
#define COMPONENTS_SYNC_DRIVER_DATA_TYPE_STATUS_TABLE_H_

#include <string>

#include "components/sync_driver/data_type_manager.h"

namespace sync_driver {

class DataTypeStatusTable {
 public:
  typedef std::map<syncer::ModelType, syncer::SyncError> TypeErrorMap;

  DataTypeStatusTable();
  ~DataTypeStatusTable();

  

  
  
  bool UpdateFailedDataTypes(const TypeErrorMap& errors);

  
  void Reset();

  
  void ResetCryptoErrors();

  
  void ResetPersistenceErrorsFrom(syncer::ModelTypeSet purged_types);

  
  
  
  bool ResetDataTypeErrorFor(syncer::ModelType type);

  
  
  
  bool ResetUnreadyErrorFor(syncer::ModelType type);

  
  TypeErrorMap GetAllErrors() const;

  
  
  syncer::ModelTypeSet GetFailedTypes() const;

  
  syncer::ModelTypeSet GetFatalErrorTypes() const;

  
  syncer::ModelTypeSet GetCryptoErrorTypes() const;

  
  syncer::ModelTypeSet GetPersistenceErrorTypes() const;

  
  syncer::ModelTypeSet GetUnreadyErrorTypes() const;

  
  syncer::ModelTypeSet GetUnrecoverableErrorTypes() const;

  
  syncer::SyncError GetUnrecoverableError() const;

 private:
  
  bool AnyFailedDataType() const;

  
  
  TypeErrorMap unrecoverable_errors_;

  
  
  
  TypeErrorMap data_type_errors_;

  
  TypeErrorMap crypto_errors_;

  
  
  TypeErrorMap persistence_errors_;

  
  
  TypeErrorMap unready_errors_;
};

}  

#endif  
