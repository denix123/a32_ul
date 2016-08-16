// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_DEVTOOLS_DEVTOOLS_AGENT_FILTER_H_
#define CONTENT_RENDERER_DEVTOOLS_DEVTOOLS_AGENT_FILTER_H_

#include <set>
#include <string>

#include "ipc/message_filter.h"

struct DevToolsMessageData;

namespace base {
class MessageLoop;
class MessageLoopProxy;
}

namespace content {

class DevToolsAgentFilter : public IPC::MessageFilter {
 public:
  
  DevToolsAgentFilter();

  static void SendRpcMessage(const DevToolsMessageData& data);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void AddEmbeddedWorkerRouteOnMainThread(int32 routing_id);
  void RemoveEmbeddedWorkerRouteOnMainThread(int32 routing_id);

 protected:
  virtual ~DevToolsAgentFilter();

 private:
  void OnDispatchOnInspectorBackend(const std::string& message);

  
  void AddEmbeddedWorkerRoute(int32 routing_id);
  void RemoveEmbeddedWorkerRoute(int32 routing_id);

  bool message_handled_;
  base::MessageLoop* render_thread_loop_;
  
  scoped_refptr<base::MessageLoopProxy> io_message_loop_proxy_;
  int current_routing_id_;

  std::set<int32> embedded_worker_routes_;

  DISALLOW_COPY_AND_ASSIGN(DevToolsAgentFilter);
};

}  

#endif  
