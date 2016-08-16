// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_SHELL_BROWSER_DEVTOOLS_REMOTE_DEBUGGING_SERVER_H_
#define CHROMECAST_SHELL_BROWSER_DEVTOOLS_REMOTE_DEBUGGING_SERVER_H_

#include "base/prefs/pref_member.h"

namespace content {
class DevToolsHttpHandler;
}  

namespace chromecast {
namespace shell {

class RemoteDebuggingServer {
 public:
  RemoteDebuggingServer();
  ~RemoteDebuggingServer();

 private:
  
  void OnPortChanged();

  
  
  bool ShouldStartImmediately();

  content::DevToolsHttpHandler* devtools_http_handler_;

  IntegerPrefMember pref_port_;
  int port_;

  DISALLOW_COPY_AND_ASSIGN(RemoteDebuggingServer);
};

}  
}  

#endif  
