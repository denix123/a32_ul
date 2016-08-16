// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_REMOVE_USER_DELEGATE_H_
#define COMPONENTS_USER_MANAGER_REMOVE_USER_DELEGATE_H_

#include "components/user_manager/user_manager_export.h"

namespace user_manager {

class USER_MANAGER_EXPORT RemoveUserDelegate {
 public:
  
  virtual void OnBeforeUserRemoved(const std::string& username) = 0;

  
  virtual void OnUserRemoved(const std::string& username) = 0;
};

}  

#endif  
