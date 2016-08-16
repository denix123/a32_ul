// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_WEBSHAREDWORKER_PROXY_H_
#define CONTENT_RENDERER_WEBSHAREDWORKER_PROXY_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ipc/ipc_listener.h"
#include "third_party/WebKit/public/web/WebSharedWorkerConnector.h"
#include "url/gurl.h"

namespace content {

class MessageRouter;

class WebSharedWorkerProxy : public blink::WebSharedWorkerConnector,
                             private IPC::Listener {
 public:
  
  WebSharedWorkerProxy(MessageRouter* router,
                       unsigned long long document_id,
                       int route_id,
                       int render_frame_route_id);
  virtual ~WebSharedWorkerProxy();

  
  virtual void connect(blink::WebMessagePortChannel* channel,
                       ConnectListener* listener);

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void Disconnect();

  
  
  bool Send(IPC::Message*);

  
  bool HasQueuedMessages() { return !queued_messages_.empty(); }

  
  void SendQueuedMessages();

  void OnWorkerCreated();
  void OnWorkerScriptLoadFailed();
  void OnWorkerConnected();

  
  
  
  
  int route_id_;

  
  int render_frame_route_id_;

  MessageRouter* const router_;

  
  
  unsigned long long document_id_;

  
  std::vector<IPC::Message*> queued_messages_;

  
  
  
  int pending_route_id_;
  ConnectListener* connect_listener_;
  bool created_;

  DISALLOW_COPY_AND_ASSIGN(WebSharedWorkerProxy);
};

}  

#endif  
