// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_ACCOUNT_MAPPING_H_
#define GOOGLE_APIS_GCM_ENGINE_ACCOUNT_MAPPING_H_

#include <string>

#include "base/basictypes.h"
#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"

namespace gcm {

struct GCM_EXPORT AccountMapping {
  
  enum MappingStatus {
    NEW,       
    ADDING,    
               
    MAPPED,    
               
    REMOVING,  
               
  };

  AccountMapping();
  ~AccountMapping();

  
  
  std::string SerializeAsString() const;
  
  
  bool ParseFromString(const std::string& value);

  
  std::string account_id;
  
  std::string email;
  
  std::string access_token;
  
  MappingStatus status;
  
  base::Time status_change_timestamp;
  
  std::string last_message_id;
};

}  

#endif  
