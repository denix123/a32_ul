// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_AGENT_HOST_IMPL_H_
#define CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_AGENT_HOST_IMPL_H_

#include <string>

#include "base/compiler_specific.h"
#include "content/common/content_export.h"
#include "content/public/browser/devtools_agent_host.h"

namespace IPC {
class Message;
}

namespace content {

class BrowserContext;

class CONTENT_EXPORT DevToolsAgentHostImpl : public DevToolsAgentHost {
 public:
  
  static std::vector<WebContents*> GetInspectableWebContents();

  
  virtual void Attach() = 0;

  
  virtual void Detach() = 0;

  
  virtual void DispatchProtocolMessage(const std::string& message) = 0;

  
  void Inspect(BrowserContext* browser_context);

  
  virtual void AttachClient(DevToolsAgentHostClient* client) OVERRIDE;
  virtual void DetachClient() OVERRIDE;
  virtual bool IsAttached() OVERRIDE;
  virtual void InspectElement(int x, int y) OVERRIDE;
  virtual std::string GetId() OVERRIDE;
  virtual WebContents* GetWebContents() OVERRIDE;
  virtual void DisconnectWebContents() OVERRIDE;
  virtual void ConnectWebContents(WebContents* wc) OVERRIDE;
  virtual bool IsWorker() const OVERRIDE;

 protected:
  DevToolsAgentHostImpl();
  virtual ~DevToolsAgentHostImpl();

  void HostClosed();
  void SendMessageToClient(const std::string& message);
  static void NotifyCallbacks(DevToolsAgentHostImpl* agent_host, bool attached);

 private:
  friend class DevToolsAgentHost; 

  const std::string id_;
  DevToolsAgentHostClient* client_;
};

}  

#endif  
