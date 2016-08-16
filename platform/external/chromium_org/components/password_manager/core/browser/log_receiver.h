// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOG_RECEIVER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOG_RECEIVER_H_

#include <string>
#include "base/macros.h"

namespace password_manager {

class LogReceiver {
 public:
  LogReceiver() {}
  virtual ~LogReceiver() {}

  virtual void LogSavePasswordProgress(const std::string& text) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(LogReceiver);
};

}  

#endif  
