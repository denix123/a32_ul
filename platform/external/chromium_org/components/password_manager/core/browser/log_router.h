// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOG_ROUTER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOG_ROUTER_H_

#include <set>
#include <string>

#include "base/macros.h"
#include "base/observer_list.h"

namespace password_manager {

class LogReceiver;
class PasswordManagerClient;

class LogRouter {
 public:
  LogRouter();
  virtual ~LogRouter();

  
  void ProcessLog(const std::string& text);

  
  
  

  
  
  
  bool RegisterClient(PasswordManagerClient* client);
  
  void UnregisterClient(PasswordManagerClient* client);

  
  
  
  
  std::string RegisterReceiver(LogReceiver* receiver);
  
  void UnregisterReceiver(LogReceiver* receiver);

 private:
  
  
  
  ObserverList<PasswordManagerClient, true> clients_;
  ObserverList<LogReceiver, true> receivers_;

  
  std::string accumulated_logs_;

  DISALLOW_COPY_AND_ASSIGN(LogRouter);
};

}  

#endif  
