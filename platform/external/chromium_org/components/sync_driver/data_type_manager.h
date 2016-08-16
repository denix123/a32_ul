// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DATA_TYPE_MANAGER_H__
#define COMPONENTS_SYNC_DRIVER_DATA_TYPE_MANAGER_H__

#include <list>
#include <set>
#include <string>

#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/data_type_status_table.h"
#include "sync/api/sync_error.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/configure_reason.h"

namespace sync_driver {

class DataTypeManager {
 public:
  enum State {
    STOPPED,           
    DOWNLOAD_PENDING,  
                       
                       

    CONFIGURING,       
    RETRYING,          

    CONFIGURED,        
    STOPPING           
  };

  
  
  enum ConfigureStatus {
    UNKNOWN = -1,
    OK,                  
    ABORTED,             
                         
    UNRECOVERABLE_ERROR  
  };

  
  struct ConfigureResult {
    ConfigureResult();
    ConfigureResult(ConfigureStatus status,
                    syncer::ModelTypeSet requested_types);
    ~ConfigureResult();

    ConfigureStatus status;
    syncer::ModelTypeSet requested_types;
    DataTypeStatusTable data_type_status_table;
  };

  virtual ~DataTypeManager() {}

  
  static std::string ConfigureStatusToString(ConfigureStatus status);

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Configure(syncer::ModelTypeSet desired_types,
                         syncer::ConfigureReason reason) = 0;

  
  
  virtual void ReenableType(syncer::ModelType type) = 0;

  
  virtual void ResetDataTypeErrors() = 0;

  virtual void PurgeForMigration(syncer::ModelTypeSet undesired_types,
                                 syncer::ConfigureReason reason) = 0;

  
  
  
  
  virtual void Stop() = 0;

  
  virtual State state() const = 0;
};

}  

#endif  
