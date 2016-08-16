// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_SHUTDOWN_REASON_H_
#define SYNC_INTERNAL_API_PUBLIC_SHUTDOWN_REASON_H_

#include "sync/base/sync_export.h"

namespace syncer {

enum SYNC_EXPORT ShutdownReason {
  STOP_SYNC,         
  DISABLE_SYNC,      
  BROWSER_SHUTDOWN,  
  SWITCH_MODE_SYNC,  
                     
};

}  

#endif  
