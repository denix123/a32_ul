// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef SYNC_PROTOCOL_SYNC_PROTOCOL_ERROR_H_
#define SYNC_PROTOCOL_SYNC_PROTOCOL_ERROR_H_

#include <string>

#include "base/values.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"

namespace syncer{

enum SyncProtocolErrorType {
  
  SYNC_SUCCESS,

  
  NOT_MY_BIRTHDAY,

  
  THROTTLED,

  
  CLEAR_PENDING,

  
  TRANSIENT_ERROR,

  
  
  NON_RETRIABLE_ERROR,

  
  
  MIGRATION_DONE,

  
  INVALID_CREDENTIAL,

  
  DISABLED_BY_ADMIN,

  
  USER_ROLLBACK,

  
  UNKNOWN_ERROR
};

enum ClientAction {
  
  UPGRADE_CLIENT,

  
  CLEAR_USER_DATA_AND_RESYNC,

  
  ENABLE_SYNC_ON_ACCOUNT,

  
  STOP_AND_RESTART_SYNC,

  
  DISABLE_SYNC_ON_CLIENT,

  
  
  STOP_SYNC_FOR_DISABLED_ACCOUNT,

  
  DISABLE_SYNC_AND_ROLLBACK,

  
  
  ROLLBACK_DONE,

  
  UNKNOWN_ACTION
};

struct SYNC_EXPORT SyncProtocolError {
  SyncProtocolErrorType error_type;
  std::string error_description;
  std::string url;
  ClientAction action;
  ModelTypeSet error_data_types;
  SyncProtocolError();
  ~SyncProtocolError();
  base::DictionaryValue* ToValue() const;
};

SYNC_EXPORT const char* GetSyncErrorTypeString(SyncProtocolErrorType type);
SYNC_EXPORT const char* GetClientActionString(ClientAction action);
}  
#endif  
