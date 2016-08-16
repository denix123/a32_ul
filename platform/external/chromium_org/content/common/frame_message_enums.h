// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_FRAME_MESSAGES_ENUMS_H_
#define CONTENT_COMMON_FRAME_MESSAGES_ENUMS_H_

#include "content/common/accessibility_mode_enums.h"

struct FrameMsg_Navigate_Type {
 public:
  enum Value {
    
    RELOAD,

    
    RELOAD_IGNORING_CACHE,

    
    RELOAD_ORIGINAL_REQUEST_URL,

    
    
    
    
    
    RESTORE,

    
    RESTORE_WITH_POST,

    
    NORMAL,

    
    NAVIGATE_TYPE_LAST = NORMAL,
  };
};

#endif  
