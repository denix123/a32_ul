// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_TYPE_H_
#define COMPONENTS_USER_MANAGER_USER_TYPE_H_

namespace user_manager {

typedef enum {
  
  USER_TYPE_REGULAR = 0,
  
  USER_TYPE_GUEST = 1,
  
  
  USER_TYPE_RETAIL_MODE = 2,
  
  
  USER_TYPE_PUBLIC_ACCOUNT = 3,
  
  USER_TYPE_SUPERVISED = 4,
  
  USER_TYPE_KIOSK_APP = 5,
  
  NUM_USER_TYPES = 6
} UserType;

}  

#endif  
