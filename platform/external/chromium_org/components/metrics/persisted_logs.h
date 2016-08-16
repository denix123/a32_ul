// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_PERSISTED_LOGS_H_
#define COMPONENTS_METRICS_PERSISTED_LOGS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/values.h"

class PrefService;

namespace metrics {

// Maintains a list of unsent logs that are written and restored from disk.
class PersistedLogs {
 public:
  
  
  enum LogReadStatus {
    RECALL_SUCCESS,         
    LIST_EMPTY,             
    LIST_SIZE_MISSING,      
    LIST_SIZE_TOO_SMALL,    
    LIST_SIZE_CORRUPTION,   
    LOG_STRING_CORRUPTION,  
    CHECKSUM_CORRUPTION,    
    CHECKSUM_STRING_CORRUPTION,  
                                 
    DECODE_FAIL,            
    DEPRECATED_XML_PROTO_MISMATCH,  
                                    
    END_RECALL_STATUS       
  };

  
  
  
  
  
  
  
  
  
  
  PersistedLogs(PrefService* local_state,
                const char* pref_name,
                size_t min_log_count,
                size_t min_log_bytes,
                size_t max_log_size);
  ~PersistedLogs();

  
  void SerializeLogs() const;

  
  LogReadStatus DeserializeLogs();

  
  void StoreLog(const std::string& log_data);

  
  
  void StageLog();

  
  void DiscardStagedLog();

  
  bool has_staged_log() const { return staged_log_index_ != -1; }

  
  const std::string& staged_log() const {
    DCHECK(has_staged_log());
    return list_[staged_log_index_].compressed_log_data;
  }

  
  const std::string& staged_log_hash() const {
    DCHECK(has_staged_log());
    return list_[staged_log_index_].hash;
  }

  
  size_t size() const { return list_.size(); }

  
  bool empty() const { return list_.empty(); }

 private:
  
  void WriteLogsToPrefList(base::ListValue* list) const;

  
  LogReadStatus ReadLogsFromPrefList(const base::ListValue& list);

  
  
  
  PrefService* local_state_;

  
  const char* pref_name_;

  
  
  
  const size_t min_log_count_;
  const size_t min_log_bytes_;

  // Logs greater than this size will not be written to disk.
  const size_t max_log_size_;

  struct LogHashPair {
    
    void Init(const std::string& log_data);

    
    std::string compressed_log_data;

    
    std::string hash;
  };
  
  
  std::vector<LogHashPair> list_;

  
  
  int staged_log_index_;

  DISALLOW_COPY_AND_ASSIGN(PersistedLogs);
};

}  

#endif  
