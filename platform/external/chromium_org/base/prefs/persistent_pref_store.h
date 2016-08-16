// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_PERSISTENT_PREF_STORE_H_
#define BASE_PREFS_PERSISTENT_PREF_STORE_H_

#include <string>

#include "base/prefs/base_prefs_export.h"
#include "base/prefs/writeable_pref_store.h"

class BASE_PREFS_EXPORT PersistentPrefStore : public WriteablePrefStore {
 public:
  
  
  
  
  enum PrefReadError {
    PREF_READ_ERROR_NONE = 0,
    PREF_READ_ERROR_JSON_PARSE = 1,
    PREF_READ_ERROR_JSON_TYPE = 2,
    PREF_READ_ERROR_ACCESS_DENIED = 3,
    PREF_READ_ERROR_FILE_OTHER = 4,
    PREF_READ_ERROR_FILE_LOCKED = 5,
    PREF_READ_ERROR_NO_FILE = 6,
    PREF_READ_ERROR_JSON_REPEAT = 7,
    
    PREF_READ_ERROR_FILE_NOT_SPECIFIED = 9,
    
    
    PREF_READ_ERROR_ASYNCHRONOUS_TASK_INCOMPLETE = 10,
    PREF_READ_ERROR_LEVELDB_IO = 11,
    PREF_READ_ERROR_LEVELDB_CORRUPTION_READ_ONLY = 12,
    PREF_READ_ERROR_LEVELDB_CORRUPTION = 13,
    PREF_READ_ERROR_MAX_ENUM
  };

  class ReadErrorDelegate {
   public:
    virtual ~ReadErrorDelegate() {}

    virtual void OnError(PrefReadError error) = 0;
  };

  
  
  
  virtual bool ReadOnly() const = 0;

  
  virtual PrefReadError GetReadError() const = 0;

  
  
  virtual PrefReadError ReadPrefs() = 0;

  
  
  
  
  virtual void ReadPrefsAsync(ReadErrorDelegate* error_delegate) = 0;

  
  virtual void CommitPendingWrite() = 0;

 protected:
  virtual ~PersistentPrefStore() {}
};

#endif  
