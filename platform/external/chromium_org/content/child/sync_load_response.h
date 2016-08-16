// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_SYNC_LOAD_RESPONSE_H_
#define CONTENT_CHILD_SYNC_LOAD_RESPONSE_H_

#include <string>

#include "content/public/common/resource_response_info.h"
#include "url/gurl.h"

namespace content {

struct SyncLoadResponse : ResourceResponseInfo {
  SyncLoadResponse();
  ~SyncLoadResponse();

  
  int error_code;

  
  
  GURL url;

  
  std::string data;
};

}  

#endif  
